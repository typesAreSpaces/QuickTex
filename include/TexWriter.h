#ifndef TEX_WRITER
#define TEX_WRITER

#include <iostream>
#include <fstream>
#include <string>

class TexWriter {
  std::string const & project_name;
  std::string const & author_name;
  std::string const & title;
  char option;

  void BasicMakefile() const;

  void BasicFile(std::ostream &) const;
  void TechnicalReport(std::ostream &) const;
  void Presentation(std::ostream &) const;

  void WithBasicPackages(std::ostream &) const;
  void WithExtraPackages(std::ostream &) const;
  void WithPresentationPackages(std::ostream &) const;

  void BasicFileMain(std::ostream &) const;
  void TechnicalReportMain(std::ostream &) const;
  void PresentationMain(std::ostream &) const;

  std::string BasicTexSectionContent(
      std::string const &, 
      std::string const &, 
      std::string const &) const ;

  public:
  TexWriter(std::string const &);
  TexWriter(
      std::string const &, 
      std::string const &, 
      std::string const &,
      char);
};

#endif
