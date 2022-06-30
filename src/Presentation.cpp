#include "Presentation.h"

Presentation::Presentation(std::string const & project_name) :
  TexWriter(project_name) 
{
}

Presentation::Presentation(std::string const & project_name,
    std::string const & author_name, 
    std::string const & title
    ) : TexWriter(project_name, author_name, title) 
{
  std::ofstream out((project_name + "/main.tex").c_str());
  HeaderSection(out);
  PackageSection(out);
  MainSection(out);
  out.close();
  BasicGitInit();
}

void Presentation::HeaderSection(std::ostream & out) const {
  out << 
    "\\documentclass{beamer}"
    << std::endl;
  return;
}

void Presentation::PackageSection(std::ostream & out) const {
  out << 
    "\\usepackage{presentation}\n"
    "\n"
    << std::endl;
  return;
}

void Presentation::MainSection(std::ostream & out) const {
  out << 
    "\\begin{document}\n"
    "\n"
    "\\title{" + title + "}  \n"
    "%\\subtitle{}\n"
    "\\author{" + author_name + "}\n"
    "\\date{\\today} \n"
    "\n"
    "\\frame{\\titlepage} \n"
    "\n"
    "\\begin{frame}[allowframebreaks]{Table of Contents}\n"
    "  \\tableofcontents[sections={1-2}]\n"
    "  \\framebreak\n"
    "  \\tableofcontents[sections={3-5}]\n"
    "\\end{frame}\n" << std::endl;


  out << BasicTexSectionContent(
      "preliminaries", 
      "Preliminaries", 
      "\\begin{frame}{Preliminaries}\n"
      "Here is the text for the preliminaries slide.\n"
      "\\end{frame}\n"
      ) 
    << std::endl;

  out << BasicTexSectionContent(
      "conclusion", 
      "Conclusions", 
      "\\begin{frame}{Conclusions}\n"
      "Here is the text for the conclusions slide.\n"
      "\\end{frame}\n"
      ) 
    << std::endl;

  out << 
    "\\begin{frame}[allowframebreaks]\n"
    "  \\frametitle{References}\n"
    "%  \\bibliographystyle{plain}\n"
    "%  \\bibliography{references}\n"
    "\\end{frame}\n"
    "\n"
    "\\end{document}\n"
    << std::endl;
  return;
}
