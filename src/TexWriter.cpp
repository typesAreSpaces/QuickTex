#include "TexWriter.h"

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
  system(("mkdir -p " + project_name).c_str());
  system(("mkdir -p " + project_name + "/figures").c_str());
  BasicMakefile();
  BasicGitIgnore();
  BasicDirLocals();
}

void TexWriter::BasicMakefile() const {
  std::ofstream out((project_name + "/Makefile").c_str());
  out << 
    "SRC=$(wildcard *.tex)\n"
    "PAPER=main.tex\n"
    "OUTPUT=$(PAPER:.tex=.pdf)\n"
    "all: $(SRC)\n"
    "\techo $(SRC)\n"
    "\tpdflatex -synctex=1 $(PAPER)\n"
    "\t#makeindex -s main.ist -o main.gls main.glo\n"
    "\tlatexmk -pdf -synctex=1 $(PAPER) \n"

    << project_name << ".pdf:\n"
    "\tif [ ! -f main.pdf ]; then make all; fi;\n"
    "\tcp main.pdf " << project_name << ".pdf\n"

    ".PHONY: clean\n"
    "clean:\n"
    "\tlatexmk -C\n"
    "\trm -rf main.ist main.gls main.glo main.toc \n"
    "\trm -rf main.diagnose main.kaux main.idx main.ilg main.out\n"
    "\trm -rf main.bbl\n"
    "\trm -rf *.fls\n"
    "\trm -rf main.log main.synctex\\(busy\\)\n"
    "\trm -rf main.fdb_latexmk main.fls\n"
    "\trm -rf $(OUTPUT)\n"

    "watch:\n"
    "\t@while true; do inotifywait $(SRC); sleep 0.01; make all; done\n"
    << std::endl;
  out.close(); 
  return;
}

void TexWriter::BasicGitInit() const {
  system(("git init " + project_name).c_str());
  system(("git -C ./" + project_name + "/ add -A").c_str());
  system(("git -C ./" + project_name + "/ commit -m 'Initial commit'").c_str());
}

void TexWriter::BasicGitIgnore() const {
  std::ofstream out((project_name + "/.gitignore").c_str());
  out << "_region_.*" << std::endl;
  out << "prv_main.*" << std::endl;
  out << "*.fls" << std::endl;
  out << "main.*" << std::endl;
  out << "!main.tex" << std::endl;
  out << "auto" << std::endl;
  out << project_name << ".pdf" << std::endl;
  out.close();
  return;
}

void TexWriter::BasicDirLocals() const {

  char curr_dir[256];
  getcwd(curr_dir, 256);

  std::ofstream out((project_name + "/.dir-locals.el").c_str());
  out << "((latex-mode (TeX-master . \"";
  out << curr_dir << "/";
  out << project_name << "/";
  out << "main.tex\")))" << std::endl;
  out.close();
  return;
}

std::string TexWriter::BasicTexSectionContent(
    std::string const & file_name,
    std::string const & section_name, 
    std::string const & content
    ) const {
  std::ofstream out((project_name + "/" + file_name + ".tex").c_str(), std::ios_base::app);
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
  std::ofstream out((project_name + "/kldb.tex").c_str(), std::ios_base::app);
  out.close();
  return;
}
