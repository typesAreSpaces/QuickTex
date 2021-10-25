#include "TechnicalReport.h"

TechnicalReport::TechnicalReport(std::string const & project_name) :
  TexWriter(project_name) 
{
}

TechnicalReport::TechnicalReport(std::string const & project_name,
    std::string const & author_name, 
    std::string const & title
    ) : TexWriter(project_name, author_name, title) 
{
  std::ofstream out((project_name + "/main.tex").c_str());
  HeaderSection(out);
  PackageSection(out);
  MainSection(out);
  CreateKLDBFile();
  out.close();
}

void TechnicalReport::HeaderSection(std::ostream & out) const {
  out << 
    "\\documentclass[peerreview]{IEEEtran}\n"
    << std::endl;
  return;
}

void TechnicalReport::PackageSection(std::ostream & out) const {
  out << 
    "\\usepackage{symbols}\n"
    << std::endl;
  return;
}

void TechnicalReport::MainSection(std::ostream & out) const {
  out << 
    "\\input{kldb}\n"
    "\\makeindex\n"
    "\\makeglossaries\n\n"
    "\\begin{document}\n"
    "\n"
    "\\title{" + title + "}\n"
    "\\author{" + author_name + "\\\\Department of Computer Science\\\\University of New Mexico\\\\}\n"
    "\n"
    "\\date{\\today}\n"
    "\\maketitle\n"
    "%\\tableofcontents\n"
    "\n"
    "\\begin{abstract}\n"
    "The abstract text goes here.\n"
    "\\end{abstract}\n" 
    << std::endl;

  out << BasicTexSectionContent("introduction", "Introduction",
      "Here is the text of your introduction\n") << std::endl;
  out << BasicTexSectionContent("conclusion", "Conclusion",
      "Write your conclusion here\n") << std::endl;
  out << "%\\bibliographystyle{plain}" << std::endl;
  out << "%\\bibliography{./../../../references}" << std::endl;
  out << "%\\printglossaries" << std::endl;
  out << "%\\printindex" << std::endl;

  out << 
    "\\end{document}\n"
    << std::endl;
  return;
}
