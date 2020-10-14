#include "TexWriter.h"

TexWriter::TexWriter(std::string const & project_name) :
  project_name(project_name) 
{
  system(("mkdir -p " + project_name).c_str());
  system(("mkdir -p " + project_name + "/figures").c_str());
  BasicMakefile();
  //WithBasicPackages();
  WithExtraPackages();
  BasicTexContent();
}

void TexWriter::BasicMakefile(){
  std::ofstream out((project_name + "/Makefile").c_str());
  out << 
    "SRC=$(wildcard *.tex)\n"
    "PAPER=main.tex\n"
    "OUTPUT=$(PAPER:.tex=.pdf)\n"
    "FILES=$(wildcard ./*.tex)\n"
    "SHELL=/bin/zsh\n"

    "all: $(FILES)\n"
    "\techo $(SRC)\n"
    "\trubber --pdf $(PAPER)\n"

    ".PHONY: clean\n"
    "\tclean:\n"
    "\trubber --clean $(PAPER)\n"
    "\trm -rf $(OUTPUT)\n"

    "watch:\n"
    "\t@while [ 1 ]; do; inotifywait $(SRC); sleep 0.01; make all; done\n"
    << std::endl;
  return;
}

void TexWriter::WithBasicPackages(){
  std::ofstream out((project_name + "/main.tex").c_str());
  out << 
    "\\documentclass{article}\n"
    "\\usepackage{graphicx}\n"
    "\n"
    << std::endl;
  out.close();
  return;
}

void TexWriter::WithExtraPackages(){
  std::ofstream out((project_name + "/main.tex").c_str());
  out << 
    "\\documentclass{article}\n"
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
    "\\DeclarePairedDelimiter{\\ceil}{\\lceil}{\rceil}\n"
    ""
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
    "\n"
    "\\lstset{style=code-style}\n"
    "\n"
    "% Keywords command\n"
    "\\providecommand{\\keywords}[1]\n"
    "{\n"
    "  \\small	\n"
    "  \\textbf{\textit{Keywords---}} #1\n"
    "}"
    ""
    "\\newcommand{\\real}[0]{\\mathbb{R}}\n"
    "\\newcommand{\\integer}[0]{\\mathbb{Z}}\n"
    "\\newcommand{\\nat}[0]{\\mathbb{N}}\n"
    "\\newcommand{\\grob}[0]{Gr\\\"obner }\n"
    "\\newcommand{\\bigO}[1]{$\\mathcal{O}(#1)$}\n"
    "\\newcommand{\\floor}[1]{\\lfloor #1 \\rfloor}\n"
    "\\newcommand{\\cev}[1]{\\underline{#1}}\n"
    ""
    "%\\DeclarePairedDelimiter\\floor{\\lfloor}{\\rfloor}\n"
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
  out.close();
  return;
}

void TexWriter::BasicTexContent(){
  std::ofstream out((project_name + "/main.tex").c_str(), std::ios_base::app);
  out << 
    "\\begin{document}\n"
    "\n"
    "\\title{Introduction to \\LaTeX{}}\n"
    "\\author{Author's Name}\n"
    "\n"
    "\\maketitle\n"
    "\n"
    "\\begin{abstract}\n"
    "The abstract text goes here.\n"
    "\\end{abstract}\n"
    "\n"
    "\\section{Introduction}\n"
    "Here is the text of your introduction.\n"
    "\n"
    "\\subsection{Subsection Heading Here}\n"
    "Write your subsection text here.\n"
    "\n"
    "\\section{Conclusion}\n"
    "Write your conclusion here.\n"
    "\n"
    "\\end{document}\n"
    << std::endl;
  out.close();
  return;
}
