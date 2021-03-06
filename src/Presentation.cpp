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
}

void Presentation::HeaderSection(std::ostream & out) const {
  out << 
    "\\documentclass{beamer}"
    << std::endl;
  return;
}

void Presentation::PackageSection(std::ostream & out) const {
  out << 
    "\\usepackage{beamerthemeshadow}\n"
    "\\usepackage[utf8]{inputenc}\n"
    "\\usepackage[english]{babel}\n"
    "\\usepackage{verbatim}\n"
    "\\usepackage{etoolbox}\n"
    "\\makeatletter\n"
    "\\patchcmd{\\@verbatim}\n"
    "{\\verbatim@font}\n"
    "{\\verbatim@font\\tiny}{}{}\n"
    "\\makeatother\n"
    "\\usepackage{float}\n"
    "\\usepackage{amsthm}\n"
    "\\usepackage{amsmath}\n"
    "\\usepackage{amsfonts}\n"
    "\\usepackage{amssymb}\n"
    "\\usepackage{pdfpages}\n"
    "\\usepackage{graphicx}\n"
    "\\usepackage{rotating}\n"
    "\\usepackage{tikz}\n"
    "\\usetikzlibrary{positioning,fit,arrows.meta,backgrounds}\n"
    "\\usepackage{hyperref}\n"
    "\\usepackage{listings}\n"
    "\\usepackage{algpseudocode}\n"
    "\\usepackage{algorithm}\n"
    "\\usepackage{ebproof}\n"
    "\\usepackage{booktabs}\n"
    "\\usepackage{multirow}\n"
    "\\usepackage{listing}\n"
    "\\usepackage{xcolor}\n"
    "\\usepackage{mathtools}\n"
    "\\usepackage{fancyvrb}\n"
    "\\usepackage{symbols}\n"
    "\n"
    "% ----------------------------------------------------------------\n"
    "% UNM colors\n"
    "\\definecolor{unmwhite1}{rgb}{0.94,0.93,0.94}\n"
    "\\definecolor{unmgray1}{rgb}{0.44,0.4,0.42}\n"
    "\\definecolor{unmgray2}{rgb}{0.54,0.48,0.5}\n"
    "\\definecolor{unmgray3}{rgb}{0.59,0.6,0.6}\n"
    "\\definecolor{unmgray4}{rgb}{0.74,0.68,0.69}\n"
    "\\definecolor{unmgray5}{rgb}{0.75,0.76,0.76}\n"
    "\\definecolor{unmred1}{rgb}{0.73,0.14,0.21}\n"
    "\\definecolor{unmred2}{rgb}{0.8,0.61,0.62}\n"
    "\\definecolor{unmred3}{rgb}{0.79,0.29,0.39}\n"
    "\\definecolor{unmred4}{rgb}{0.92,0.75,0.76}\n"
    "\n"
    "\\setbeamercolor{structure}{bg=unmgray1,fg=unmred2}\n"
    "\\setbeamercolor{palette primary}{bg=unmred1, fg=unmwhite1}\n"
    "\\setbeamercolor{palette secondary}{bg=unmgray1, fg=unmgray1}\n"
    "\\setbeamercolor{palette tertiary}{bg=unmred2, fg=unmgray1}\n"
    "\\setbeamercolor{palette quaternary}{bg=unmred3, fg=unmwhite1}\n"
    "\\setbeamercolor{section in toc}{fg=black,bg=white}\n"
    "\\setbeamercolor{alerted text}{use=structure,fg=structure.fg!50!black!80!black}\n"
    "\\setbeamercolor{titlelike}{parent=palette primary,fg=structure.fg!50!black}\n"
    "\\setbeamercolor{frametitle}{bg=unmred1!10!unmwhite1,fg=unmgray1}\n"
    "% ----------------------------------------------------------------\n"
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
