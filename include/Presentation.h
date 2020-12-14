#ifndef _PRESENTATION_
#define _PRESENTATION_

#include "TexWriter.h"

class Presentation : public TexWriter {
  void HeaderSection(std::ostream &)  const;
  void PackageSection(std::ostream &) const;
  void MainSection(std::ostream &)    const;

  public:
  Presentation(std::string const &);
  Presentation(
      std::string const &, 
      std::string const &, 
      std::string const &);
};

#endif
