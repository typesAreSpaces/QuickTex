#include "Basic.h"
#include "TechnicalReport.h"
#include "Presentation.h"

int main(int argc, char * argv[]){
  if(argc == 2){
    Basic quicktex(argv[1]);
    return 0;
  }
  if(argc == 3){
    switch(*argv[2]){
      case 'r':
        {
          TechnicalReport quicktex(argv[1], 
              "Jose Abel Castellanos Joo", 
              "Dissertation Seminar - Report \\# n");
          return 0;
        }
      case 'p':
        {
          Presentation quicktex(argv[1], 
              "Jose Abel Castellanos Joo", 
              "QuickTex Presentation");
          return 0;
        }

      case 'b':
        {
          Basic quicktex(argv[1], 
              "Jose Abel Castellanos Joo", 
              "QuickTex Presentation");
          return 0;
        }
      default:
        std::cerr << "Error: option not recognized" 
          "by quicktex" << std::endl;
        return 1;
    }
  }
  std::cerr << "Error: quicktex requires an argument" 
    "denoting the name of the project." << std::endl;
  return 1;
}
