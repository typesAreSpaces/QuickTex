#ifndef TEX_WRITER
#define TEX_WRITER

#include <iostream>
#include <fstream>
#include <string>

class TexWriter {

  void BasicMakefile() const;

  virtual void HeaderSection(std::ostream &) const = 0;
  virtual void PackageSection(std::ostream &) const = 0;
  virtual void MainSection(std::ostream &) const = 0;

  protected:
  std::string const & project_name;
  std::string const & author_name;
  std::string const & title;

  std::string BasicTexSectionContent(
      std::string const &, 
      std::string const &, 
      std::string const &) const ;

  public:
  TexWriter(std::string const &);
  TexWriter(
      std::string const &, 
      std::string const &, 
      std::string const &);
};

#endif
