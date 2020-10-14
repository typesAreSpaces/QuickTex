#ifndef TEX_WRITER
#define TEX_WRITER

#include <iostream>
#include <fstream>
#include <string>

class TexWriter {
  std::string const & project_name;

  void BasicMakefile();
  void WithBasicPackages();
  void WithExtraPackages();
  void BasicTexContent();

  public:
  TexWriter(std::string const &);
};

#endif
