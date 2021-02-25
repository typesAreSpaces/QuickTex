#include "Basic.h"
#include "TechnicalReport.h"
#include "Presentation.h"
#include "Homework.h"

int main(int argc, char * argv[]){
  if(argc == 2){
    Basic quicktex(argv[1]);
    return 0;
  }
  if(argc == 3){
    switch(*argv[2]){
      case 'b':
          Basic(argv[1], 
              "Jose Abel Castellanos Joo", 
              "QuickTex Presentation");
          return 0;
      case 'h':
          Homework(argv[1], 
              "Jose Abel C. J.", 
              "Homework\\ \\#n",
              "Math 439", 
              "Due date",
              "Prof. Billy Brown"
              );
          return 0;
      case 'p':
          Presentation(argv[1], 
              "Jose Abel Castellanos Joo", 
              "QuickTex Presentation");
          return 0;
      case 'r':
          TechnicalReport(argv[1], 
              "Jose Abel Castellanos Joo", 
              "Dissertation Seminar - Report \\# n");
          return 0;
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
