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
    "\\usepackage{amsmath}\n"
    "\\usepackage{amssymb}\n"
    "\\usepackage{graphics}\n"
    "\\usepackage{setspace}\n"
    "\\usepackage{caption}\n"
    "\\usepackage{graphicx}\n"
    "\\usepackage[utf8]{inputenc}\n"
    "\\usepackage{cite}\n"
    "\\usepackage{url}\n"
    "\\usepackage[english]{babel}\n"
    "\\usepackage{verbatim}\n"
    "\\usepackage{etoolbox}\n"
    "\\usepackage{float}\n"
    "\\usepackage{pdfpages}\n"
    "\\usepackage{rotating}\n"
    "\\usepackage{algpseudocode}\n"
    "\\usepackage{algorithm}\n"
    "\\usepackage{ebproof}\n"
    "\\usepackage{booktabs}\n"
    "\\usepackage{multirow}\n"
    "\\usepackage{listing}\n"
    "\\usepackage{symbols}\n"
    "\\usepackage{makeidx}\n"
    "\\usepackage[breaklinks,hidelinks]{hyperref} \n"
    "\\usepackage[xcolor, hyperref, notion, makeidx]{knowledge}\n"
    "\\usepackage{tikz}\n"
    "\\usepackage{tikz-cd}\n"
    "\\usepackage{glossaries}\n"
    "\\usetikzlibrary{positioning,fit,arrows.meta,backgrounds,cd}\n"
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
