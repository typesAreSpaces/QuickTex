#include "TechnicalReport.h"

TechnicalReport::TechnicalReport(std::string const & project_name) :
  TexWriter(project_name) 
{
}

TechnicalReport::TechnicalReport(std::string const & project_name,
    std::string const & author_name, 
    std::string const & title,
    bool enable_git) 
  : TexWriter(project_name, author_name, title) 
{
  std::ofstream out((project_name + "/main.tex").c_str());
  HeaderSection(out);
  PackageSection(out);
  MainSection(out);
  CreateKLDBFile();
  out.close();
  if(enable_git)
    BasicGitInit();
}

void TechnicalReport::HeaderSection(std::ostream & out) const {
  out << 
    //"\\documentclass[peerreview]{IEEEtran}\n"
    "\\documentclass{article}\n"
    << std::endl;
  return;
}

void TechnicalReport::PackageSection(std::ostream & out) const {
  out << 
    "\\usepackage{symbols}\n"
    "\\usepackage[style=numeric-comp]{biblatex}\n"
    << std::endl;
  return;
}

void TechnicalReport::MainSection(std::ostream & out) const {
  out << 
    "\\input{kldb}\n"
    "%\\addbibresource{references}\n"
    "%\\makeindex\n"
    "%\\makeglossaries\n\n"
    "\\begin{document}\n"
    "\n"
    "\\title{" + title + "}\n"
    "\\author{" + author_name + "\\\\\nDepartment of Computer Science\\\\\nUniversity "
    "of New Mexico}\n"
    "\n"
    "\\date{\\today}\n"
    "\\maketitle\n"
    "%\\tableofcontents\n"
    "\n"
    "\\begin{abstract}\n"
    "The abstract text goes here.\n"
    "\\end{abstract}\n" 
    << std::endl;

  out << "%\\printbibliography" << std::endl;
  out << "%\\printglossaries" << std::endl;
  out << "%\\printindex" << std::endl;

  out << 
    "\\end{document}\n"
    << std::endl;
  return;
}
