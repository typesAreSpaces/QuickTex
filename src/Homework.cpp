#include "Homework.h"

Homework::Homework(std::string const & project_name,
    std::string const & author_name, 
    std::string const & title, 
    std::string const & subject,
    std::string const & due_date,
    std::string const & prof_name
    ) : TexWriter(project_name, author_name, title), 
  subject(subject), due_date(due_date), prof_name(prof_name)
{
  std::ofstream out((project_name + "/main.tex").c_str());
  HeaderSection(out);
  PackageSection(out);
  MainSection(out);
  out.close();
}

void Homework::HeaderSection(std::ostream & out) const {
  out << 
    "\\documentclass[12pt, letterpaper]{article}"
    << std::endl;
  return;
}

void Homework::PackageSection(std::ostream & out) const {
  out <<
    "\\documentclass[12pt, letterpaper]{article}\n"
    "\\usepackage[utf8]{inputenc}\n"
    "\\usepackage{amsmath}\n"
    "\\usepackage{amsfonts}\n"
    "\\usepackage{amssymb}\n"
    "\\usepackage{titlesec}\n"
    "\\usepackage[left=3cm,right=3cm,top=4cm,bottom=4cm]{geometry}\n"
    "\\usepackage{fancyhdr}\n"
    "\\usepackage{extramarks}\n"
    "\\usepackage{symbols}\n"
    "\n"
    "%% Meta data"
    "\\newcommand{\\Name}{\\textbf{" + author_name + "}}\n"
    "\\newcommand{\\Title}{" + title + "}\n"
    "\\newcommand{\\Subject}{" + subject + "}\n"
    "\\newcommand{\\DueDate}{" + due_date + "}\n"
    "\\newcommand{\\Instructor}{" + prof_name + "}\n"
    "\n"
    "%% Set page header and footer"
    "\\pagestyle{fancy}\n"
    "\\lhead{\\Name}\n"
    "\\chead{\\Subject\\ -\\ \\Instructor\\ :\\ \\Title}\n"
    "\\rhead{\\DueDate}\n"
    "\n"
    "%% Problem Enviroment"
    "\\newenvironment{homeworkProblem}[1][0]{\n"
    "\\section{Problem: #1}\n"
    "}{\n"
    "}\n"
    << std::endl;

  return;
}

void Homework::MainSection(std::ostream & out) const {
  out <<
    "\\begin{document}\n"
    "\n"
    "\\begin{homeworkProblem}\n"
    "%%Problem text goes here.\n"
    "%%Solution text goes here.\n"
    "\\end{homeworkProblem}\n"
    "%%\\bibliographystyle{plain}\n"
    "%%\\bibliography{references}\n"
    "\\end{document}\n"
    << std::endl;

  return;
}
