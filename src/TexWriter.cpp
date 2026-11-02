#include "TexWriter.h"

#include <cerrno>
#include <filesystem>
#include <iomanip>
#include <stdexcept>
#include <sys/wait.h>
#include <vector>

namespace {
namespace fs = std::filesystem;

std::string PdfName(std::string const & project) {
  std::string name = fs::path(project).filename().string();
  for (char & c : name) {
    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
          (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.'))
      c = '_';
  }
  return name + ".pdf";
}

void RunGit(std::vector<std::string> args) {
  std::vector<char *> argv;
  for (auto & arg : args) argv.push_back(&arg[0]);
  argv.push_back(nullptr);
  pid_t pid = fork();
  if (pid < 0) throw std::runtime_error("Could not start Git");
  if (pid == 0) {
    execvp("git", argv.data());
    _exit(127);
  }
  int status;
  while (waitpid(pid, &status, 0) < 0) {
    if (errno != EINTR) throw std::runtime_error("Could not wait for Git");
  }
  if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
    throw std::runtime_error("Git command failed; project files were retained");
}
}

std::ofstream TexWriter::OpenOutput(std::string const & name) const {
  std::ofstream out;
  out.exceptions(std::ios::failbit | std::ios::badbit);
  const auto path = fs::path(project_name) / name;
  try {
    out.open(path);
  } catch (std::ios_base::failure const &) {
    throw std::runtime_error("Could not open output file: " + path.string());
  }
  return out;
}

TexWriter::TexWriter(std::string const & project_name) :
  TexWriter(
      project_name, 
      "Author's name", 
      "QuickTex sample file"
      ) 
{}

TexWriter::TexWriter(
    std::string const & project_name,
    std::string const & author_name, 
    std::string const & title
    ) :
  project_name(project_name), 
  author_name(author_name),
  title(title)
{
  if (project_name.empty())
    throw std::runtime_error("Project path must name a new directory");
  fs::path destination = fs::absolute(project_name).lexically_normal();
  if (destination.filename().empty()) destination = destination.parent_path();
  // Create parents, then claim the destination exclusively before writing files.
  fs::create_directories(destination.parent_path());
  if (!fs::create_directory(destination))
    throw std::runtime_error("Destination already exists: " + destination.string());
  this->project_name = destination.string();
  fs::create_directory(destination / "figures");
  BasicMakefile();
  BasicGitIgnore();
  BasicDirLocals();
}

void TexWriter::BasicMakefile() const {
  auto out = OpenOutput("Makefile");
  const auto pdf = PdfName(project_name);
  out <<
    ".PHONY: all clean watch FORCE\n"
    "all: main.pdf\n\n"
    // Let latexmk track included TeX, bibliography, graphics and style files.
    "main.pdf: FORCE\n"
    "\tlatexmk -pdf -synctex=1 -interaction=nonstopmode -file-line-error -halt-on-error main.tex\n\n"
    "FORCE:\n\n";
  if (pdf != "main.pdf") {
    out << pdf << ": main.pdf\n"
        << "\tcp main.pdf ./" << pdf << "\n\n";
  }
  out <<
    "clean:\n"
    "\tlatexmk -C\n"
    "\trm -f main.ist main.gls main.glo main.toc main.diagnose main.kaux main.idx main.ilg main.out main.bbl\n"
    "\trm -f main.log main.synctex\\(busy\\) main.fdb_latexmk main.fls\n";
  if (pdf != "main.pdf") out << "\trm -f ./" << pdf << "\n";
  out <<
    "\nwatch:\n"
    "\tlatexmk -pdf -synctex=1 -interaction=nonstopmode -file-line-error -halt-on-error -pvc main.tex\n";
  out.close();
}

void TexWriter::BasicGitInit() const {
  RunGit({"git", "init", "--", project_name});
  RunGit({"git", "-C", project_name, "add", "-A"});
  RunGit({"git", "-C", project_name, "commit", "-m", "Initial commit"});
}

void TexWriter::BasicGitIgnore() const {
  auto out = OpenOutput(".gitignore");
  out << "_region_.*" << std::endl;
  out << "prv_main.*" << std::endl;
  out << "*.fls" << std::endl;
  out << "main.*" << std::endl;
  out << "!main.tex" << std::endl;
  out << "auto" << std::endl;
  out << "/" << PdfName(project_name) << std::endl;
  out.close();
  return;
}

void TexWriter::BasicDirLocals() const {

  auto out = OpenOutput(".dir-locals.el");
  out << "((latex-mode (TeX-master . ";
  out << std::quoted((fs::path(project_name) / "main.tex").string());
  out << ")))" << std::endl;
  out.close();
  return;
}

std::string TexWriter::BasicTexSectionContent(
    std::string const & file_name,
    std::string const & section_name, 
    std::string const & content
    ) const {
  auto out = OpenOutput(file_name + ".tex");
  out << 
    "\\section{" + section_name + "}\n";
  out << content;
  out << 
    "\n"
    "%%% Local Variables:\n"
    "%%% mode: latex\n"
    "%%% TeX-master: \"main\"\n"
    "%%% End:\n";
  out.close();
  return "\\input{" + file_name + "}\n";
}

void TexWriter::CreateKLDBFile() const {
  auto out = OpenOutput("kldb.tex");
  out.close();
  return;
}
