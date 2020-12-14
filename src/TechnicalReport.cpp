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
    "\\usepackage{graphicx}\n"
    "\\usepackage[utf8]{inputenc}\n"
    "\\usepackage{cite}\n"
    "\\usepackage{url}\n"
    "\\usepackage[english]{babel}\n"
    "\\usepackage{verbatim}\n"
    "\\usepackage{etoolbox}\n"
    "\\makeatletter\n"
    "\\patchcmd{\\@verbatim}\n"
    "{\\verbatim@font}\n"
    "{\\verbatim@font\\tiny}\n"
    "{}{}\n"
    "\\makeatother\n"
    "\\usepackage{float}\n"
    "\\usepackage{amsthm}\n"
    "\\usepackage{amsmath}\n"
    "\\usepackage{amsfonts}\n"
    "\\usepackage{amssymb}\n"
    "\\usepackage{pdfpages}\n"
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
    "\n"
    "\\definecolor{codegreen}{rgb}{0,0.6,0}\n"
    "\\definecolor{codegray}{rgb}{0.5,0.5,0.5}\n"
    "\\definecolor{codepurple}{rgb}{0.58,0,0.82}\n"
    "\\definecolor{backcolour}{rgb}{0.97,0.97,0.97}\n"
    ""
    "\\lstdefinestyle{code-style}{\n"
    "  backgroundcolor=\\color{backcolour},\n"
    "  commentstyle=\\color{codegreen},\n"
    "  keywordstyle=\\color{magenta},\n"
    "  numberstyle=\\tiny\\color{codegray},\n"
    "  stringstyle=\\color{codepurple},\n"
    "  basicstyle=\\ttfamily\\footnotesize,\n"
    "  breakatwhitespace=false,\n"
    "  breaklines=true,\n"
    "  captionpos=b,\n"
    "  keepspaces=false,\n"
    "  numbers=left,\n"
    "  numbersep=5pt,\n"
    "  showspaces=false,\n"
    "  showstringspaces=false,\n"
    "  showtabs=false,\n"
    "  tabsize=2\n"
    "}\n"
    "\\lstset{style=code-style}\n"
    "\n"
    "% Keywords command\n"
    "\\providecommand{\\keywords}[1]\n"
    "{\n"
    "  \\small	\n"
    "  \\textbf{\textit{Keywords---}} #1\n"
    "}\n"
    "\\newcommand{\\real}[0]{\\mathbb{R}}\n"
    "\\newcommand{\\integer}[0]{\\mathbb{Z}}\n"
    "\\newcommand{\\nat}[0]{\\mathbb{N}}\n"
    "\\newcommand{\\natext}[1]{\\mathbb{N}^#1}\n"
    "\\newcommand{\\join}[3]{#1 \\downarrow_{#3} #2}\n"
    "\\newcommand{\\grob}[0]{Gr\\\"obner}\n"
    "\\newcommand{\\bigO}[1]{$\\mathcal{O}(#1)$}\n"
    "\\newcommand{\\cev}[1]{\\underline{#1}}\n"
    "\\newcommand{\\fall}[2]{\\forall #1 . \\text{ } #2}\n"
    "\\newcommand{\\eexists}[2]{\\exists #1 . \\text{ } #2}\n"
    "\\newcommand{\\ras}[1]{\\rightarrow_{#1}}\n"
    "\\newcommand{\\las}[1]{\\leftarrow_{#1}}\n"
    "\\newcommand{\\extcong}[3]{#1 \\cong #2 \\text{ } #3}\n"
    "\\DeclarePairedDelimiter{\\ceil}{\\lceil}{\\rceil}\n"
    "\\DeclarePairedDelimiter{\\floor}{\\lfloor}{\\rfloor}\n"
    "\n"
    "\\newcommand{\\separationline}[0]{0.75}\n"
    "\n"
    "\\newtheorem{theorem}{Theorem}[section]\n"
    "\\newtheorem{notation}{Notation}[section]\n"
    "\\newtheorem{corollary}{Corollary}[theorem]\n"
    "\\newtheorem{lemma}[theorem]{Lemma}\n"
    "\\newtheorem{definition}{Definition}[section]\n"
    "\\newtheorem{example}{Example}[definition]\n"
    "\n"
    "\\tikzset{\n"
    "  module/.style={%\n"
    "    draw, rounded corners,\n"
    "    minimum width=#1,\n"
    "    minimum height=7mm,\n"
    "    font=\\sffamily\n"
    "  },\n"
    "  module/.default=2cm,\n"
    "  >=LaTeX\n"
    "}\n"
    << std::endl;
  return;
}

void TechnicalReport::MainSection(std::ostream & out) const {
  out << 
    "\\begin{document}\n"
    "\n"
    "\\title{" + title + "}\n"
    "\\author{" + author_name + "\\\\Department of Computer Science\\\\University of New Mexico\\\\}\n"
    "\n"
    "\\date{\\today}\n"
    "\\maketitle\n"
    "\\tableofcontents\n"
    "\n"
    "\\IEEEpeerreviewmaketitle\n"
    "\n"
    "\\begin{abstract}\n"
    "The abstract text goes here.\n"
    "\\end{abstract}\n" 
    << std::endl;

  out << BasicTexSectionContent("introduction", "Introduction",
      "Here is the text of your introduction\n") << std::endl;

  out << BasicTexSectionContent("conclusion", "Conclusion",
      "Write your conclusion here\n") << std::endl;

  out << 
    "\\end{document}\n"
    << std::endl;
  return;
}
