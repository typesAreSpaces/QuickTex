#include "Basic.h"

Basic::Basic(std::string const & project_name) :
  Basic(
      project_name, 
      "Author's name",
      "QuickTex sample file"
      ) 
{
}

Basic::Basic(std::string const & project_name,
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

void Basic::HeaderSection(std::ostream & out) const {
  out << 
    "\\documentclass{article}\n"
    << std::endl;
  return;
}

void Basic::PackageSection(std::ostream & out) const {
  out << 
    "\\usepackage{graphicx}\n"
    "\n"
    << std::endl;
  return;
}

void Basic::MainSection(std::ostream & out) const {
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
