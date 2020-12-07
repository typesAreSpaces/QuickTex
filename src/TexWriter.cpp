#include "TexWriter.h"

TexWriter::TexWriter(std::string const & project_name) :
  TexWriter(
      project_name, 
      "Author's name", 
      "QuickTex sample file",
      'd'
      ) {}

  TexWriter::TexWriter(
      std::string const & project_name,
      std::string const & author_name, 
      std::string const & title, 
      char option) :
    project_name(project_name), 
    author_name(author_name),
    title(title)
{
  system(("mkdir -p " + project_name).c_str());
  system(("mkdir -p " + project_name + "/figures").c_str());
  BasicMakefile();

  std::ofstream out((project_name + "/main.tex").c_str());
  switch(option){
    case 'r':
      TechnicalReport(out);
      WithExtraPackages(out);
      TechnicalReportMain(out);
      break;
    case 'p':
      Presentation(out);
      WithPresentationPackages(out);
      PresentationMain(out);
      break;
    case 'd':
    default:
      BasicFile(out);
      WithBasicPackages(out);
      BasicFileMain(out);
      break;
  }
  out.close();
}

void TexWriter::BasicMakefile() const {
  std::ofstream out((project_name + "/Makefile").c_str());
  out << 
    "SRC=$(wildcard *.tex)\n"
    "PAPER=main.tex\n"
    "OUTPUT=$(PAPER:.tex=.pdf)\n"
    "FILES=$(wildcard ./*.tex)\n"
    "all: $(FILES)\n"
    "\techo $(SRC)\n"
    "\trubber --pdf $(PAPER)\n"

    ".PHONY: clean\n"
    "clean:\n"
    "\trubber --clean $(PAPER)\n"
    "\trm -rf $(OUTPUT)\n"

    "watch:\n"
    "\t@while true; do inotifywait $(SRC); sleep 0.01; make all; done\n"
    << std::endl;
  return;
}

void TexWriter::BasicFile(std::ostream & out) const {
  out << 
    "\\documentclass{article}\n"
    << std::endl;
  return;
}

void TexWriter::TechnicalReport(std::ostream & out) const {
  out << 
    "\\documentclass[peerreview]{IEEEtran}\n"
    << std::endl;
  return;
}

void TexWriter::Presentation(std::ostream & out) const {
  out << 
    "\\documentclass{beamer}"
    << std::endl;
  return;
}

void TexWriter::WithBasicPackages(std::ostream & out) const {
  out << 
    "\\usepackage{graphicx}\n"
    "\n"
    << std::endl;
  return;
}

void TexWriter::WithExtraPackages(std::ostream & out) const {
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
    "\\newcommand{\\las}[1]{\\rightarrow_{#1}}\n"
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

void TexWriter::WithPresentationPackages(std::ostream & out) const {
  out << 
    "\\usepackage{beamerthemeshadow}\n"
    "\\usepackage[utf8]{inputenc}\n"
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
    "\n"
    "\\definecolor{codegreen}{rgb}{0,0.6,0}\n"
    "\\definecolor{codegray}{rgb}{0.5,0.5,0.5}\n"
    "\\definecolor{codepurple}{rgb}{0.58,0,0.82}\n"
    "\\definecolor{backcolour}{rgb}{0.97,0.97,0.97}\n"
    "\n"
    "\\lstdefinestyle{code-style}{\n"
    "  backgroundcolor=\\color{backcolour},   \n"
    "  commentstyle=\\color{codegreen},\n"
    "  keywordstyle=\\color{magenta},\n"
    "  numberstyle=\\tiny\\color{codegray},\n"
    "  stringstyle=\\color{codepurple},\n"
    "  basicstyle=\\ttfamily\\footnotesize,\n"
    "  breakatwhitespace=false,         \n"
    "  breaklines=true,                 \n"
    "  captionpos=b,                    \n"
    "  keepspaces=false,                 \n"
    "  numbers=left,                    \n"
    "  numbersep=5pt,                  \n"
    "  showspaces=false, \n"
    "  showstringspaces=false,\n"
    "  showtabs=false,                  \n"
    "  tabsize=2\n"
    "}\n"
    "\n"
    "\\lstset{style=code-style}\n"
    "\n"
    "% Keywords command\n"
    "\\providecommand{\\keywords}[1]\n"
    "{\n"
    "  \\small	\n"
    "  \\textbf{\\textit{Keywords---}} #1\n"
    "}\n"
    "\n"
    "\\newcommand{\\real}[0]{\\mathbb{R}}\n"
    "\\newcommand{\\integer}[0]{\\mathbb{Z}}\n"
    "\\newcommand{\\nat}[0]{\\mathbb{N}}\n"
    "\\newcommand{\\natext}[1]{\\mathbb{N}^#1}\n"
    "\\newcommand{\\join}[3]{#1 \\downarrow_{#3} #2}\n"
    "\\newcommand{\\grob}[0]{Gr\\\"obner}\n"
    "\\newcommand{\\bigO}[1]{$\\mathcal{O}(#1)$}\n"
    "\\newcommand{\\cev}[1]{\\underline{#1}}\n"
    "\\newcommand{\\fall}[2]{\\forall #1 . \text{ } #2}\n"
    "\\newcommand{\\eexists}[2]{\\exists #1 . \text{ } #2}\n"
    "\\newcommand{\\ras}[1]{\\rightarrow_{#1}}\n"
    "\\newcommand{\\las}[1]{\\rightarrow_{#1}}\n"
    "\\DeclarePairedDelimiter{\\ceil}{\\lceil}{\\rceil}\n"
    "\\DeclarePairedDelimiter{\\floor}{\\lfloor}{\\rfloor}\n"
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

void TexWriter::BasicFileMain(std::ostream & out) const {
  out << 
    "\\begin{document}\n"
    "\n"
    "\\title{" + title + "}\n"
    "\\author{" + author_name + "}\n"
    "\n"
    "\\maketitle\n"
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

void TexWriter::TechnicalReportMain(std::ostream & out) const {
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

void TexWriter::PresentationMain(std::ostream & out) const {
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
