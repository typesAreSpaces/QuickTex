#ifndef TEX_WRITER
#define TEX_WRITER

#include <iostream>
#include <fstream>
#include <string>

class TexWriter {
  std::string const & project_name;
  std::string const & author_name;
  std::string const & title;

  void BasicMakefile() const;
  void WithBasicPackages() const;
  void WithExtraPackages() const;
  void BasicTexMain() const;
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
