#include "TexWriter.h"
#include <iostream>

int main(int argc, char * argv[]){
  if(argc == 2){
    TexWriter quicktex(argv[1]);
    return 0;
  }
  if(argc == 3){
    switch(*argv[2]){
      case 'r':
        {
          TexWriter quicktex(argv[1], 
              "Jose Abel Castellanos Joo", 
              "Dissertation Seminar - Report \\# n", 
              'r');
          return 0;
        }
      default:
        return 0;
    }
  }
  std::cerr << "Error: quicktex requires an argument denoting the name of the project." << std::endl;
  return 1;
}
