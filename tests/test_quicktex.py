import os
from pathlib import Path
import resource
import shutil
import signal
import subprocess
import tempfile
import unittest


BINARY = Path(__file__).resolve().parents[1] / "bin" / "quicktex"


class QuickTexTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="quicktex-test-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.env = os.environ.copy()
        self.env.update(
            GIT_CONFIG_GLOBAL=os.devnull,
            GIT_CONFIG_NOSYSTEM="1",
            GIT_AUTHOR_NAME="QuickTex Tests",
            GIT_AUTHOR_EMAIL="tests@example.com",
            GIT_COMMITTER_NAME="QuickTex Tests",
            GIT_COMMITTER_EMAIL="tests@example.com",
            GIT_CONFIG_COUNT="1",
            GIT_CONFIG_KEY_0="commit.gpgsign",
            GIT_CONFIG_VALUE_0="false",
            TEXMFHOME=str(self.root / "empty-texmf"),
        )

    def run_command(self, args, cwd=None, check=True):
        result = subprocess.run(
            args, cwd=cwd or self.root, env=self.env,
            capture_output=True, text=True, timeout=60,
        )
        if check:
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return result

    def generate(self, *args, check=True):
        return self.run_command([str(BINARY), *map(str, args)], check=check)

    def test_project_name_is_literal(self):
        for name in ["my project", "demo; touch SHELL_EXECUTED; #", "$(touch EXPANDED)", "-leading-option"]:
            with self.subTest(name=name):
                self.generate(name)
                self.assertTrue((self.root / name / "main.tex").is_file())
                self.assertTrue((self.root / name / "figures").is_dir())
        self.assertFalse((self.root / "SHELL_EXECUTED").exists())
        self.assertFalse((self.root / "EXPANDED").exists())

    def test_existing_destinations_are_untouched(self):
        for mode in ["b", "h", "p", "r"]:
            with self.subTest(mode=mode):
                self.generate(mode, mode)
                project = self.root / mode
                (project / "main.tex").write_text("user content\n")
                before = {p.name: p.read_bytes() for p in project.iterdir() if p.is_file()}
                result = self.generate(mode, mode, check=False)
                self.assertNotEqual(result.returncode, 0)
                after = {p.name: p.read_bytes() for p in project.iterdir() if p.is_file()}
                self.assertEqual(before, after)

    def test_existing_empty_directory_and_symlink_are_rejected(self):
        (self.root / "existing").mkdir()
        (self.root / "link").symlink_to(self.root / "existing", target_is_directory=True)
        for name in ["existing", "link"]:
            self.assertNotEqual(self.generate(name, check=False).returncode, 0)
        self.assertEqual(list((self.root / "existing").iterdir()), [])

    def test_filesystem_errors_return_failure(self):
        (self.root / "file").write_text("unchanged")
        result = self.generate("file/child", check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Error:", result.stderr)
        self.assertEqual((self.root / "file").read_text(), "unchanged")

    def test_output_write_errors_return_failure(self):
        def limit_output():
            signal.signal(signal.SIGXFSZ, signal.SIG_IGN)
            resource.setrlimit(resource.RLIMIT_FSIZE, (1, 1))

        result = subprocess.run(
            [str(BINARY), "write-failure"], cwd=self.root, env=self.env,
            preexec_fn=limit_output, capture_output=True, text=True, timeout=10,
        )
        self.assertEqual(result.returncode, 1)
        self.assertIn("Error:", result.stderr)

    def test_nested_path_with_trailing_slash(self):
        self.generate("parent/child/")
        self.assertTrue((self.root / "parent/child/main.tex").is_file())

    @unittest.skipUnless(shutil.which("git"), "Git is unavailable")
    def test_git_with_absolute_and_special_paths(self):
        for name in ["absolute", "spaces and 'quotes'; #"]:
            project = self.root / name
            self.generate(project, "b", "git")
            self.run_command(["git", "-C", str(project), "rev-parse", "--verify", "HEAD"])
            status = self.run_command(["git", "-C", str(project), "status", "--porcelain"])
            self.assertEqual(status.stdout, "")
            locals_file = (project / ".dir-locals.el").read_text()
            self.assertIn(str(project / "main.tex"), locals_file)

    def install_fake_tool(self, name, body):
        tools = self.root / "tools"
        tools.mkdir(exist_ok=True)
        tool = tools / name
        tool.write_text("#!/bin/sh\n" + body)
        tool.chmod(0o755)
        self.env["PATH"] = str(tools) + os.pathsep + os.environ["PATH"]

    def test_git_errors_return_failure_and_retain_project(self):
        self.install_fake_tool("git", "exit 23\n")
        result = self.generate("git-failure", "b", "git", check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertTrue((self.root / "git-failure" / "main.tex").is_file())

    def test_named_pdf_builds_from_sources_and_refreshes(self):
        # A deterministic compiler substitute exercises Make dependencies without TeX.
        self.install_fake_tool("latexmk", "cat main.tex introduction.tex > main.pdf\n")
        project = self.root / "parent" / "paper"
        self.generate(project)
        self.run_command(["make", "paper.pdf"], cwd=project)
        before = (project / "paper.pdf").read_bytes()
        with (project / "introduction.tex").open("a") as out:
            out.write("updated introduction\n")
        # Avoid filesystem timestamp granularity hiding the older copy.
        os.utime(project / "paper.pdf", (1, 1))
        self.run_command(["make", "paper.pdf"], cwd=project)
        self.assertNotEqual((project / "paper.pdf").read_bytes(), before)
        self.assertEqual((project / "paper.pdf").read_bytes(), (project / "main.pdf").read_bytes())

    def test_special_name_makefile_is_safe(self):
        self.install_fake_tool("latexmk", "cat main.tex > main.pdf\n")
        project = self.root / "paper; touch MAKE_EXECUTED; #"
        self.generate(project)
        self.run_command(["make", "paper__touch_MAKE_EXECUTED___.pdf"], cwd=project)
        self.assertFalse((project / "MAKE_EXECUTED").exists())

    def test_main_project_name_has_no_circular_pdf_target(self):
        self.install_fake_tool("latexmk", "cat main.tex > main.pdf\n")
        self.generate("main")
        result = self.run_command(["make", "main.pdf"], cwd=self.root / "main")
        self.assertNotIn("Circular", result.stderr)

    @unittest.skipUnless(shutil.which("pdflatex"), "pdflatex is unavailable")
    def test_templates_compile_without_personal_packages(self):
        for mode in ["b", "h", "p", "r"]:
            with self.subTest(mode=mode):
                self.generate(mode, mode)
                self.run_command(
                    ["pdflatex", "-interaction=nonstopmode", "-halt-on-error", "main.tex"],
                    cwd=self.root / mode,
                )
                self.assertTrue((self.root / mode / "main.pdf").is_file())


if __name__ == "__main__":
    unittest.main()
