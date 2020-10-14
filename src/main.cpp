#include "TexWriter.h"

int main(int argc, char * argv[]){
  if(argc == 2){
    TexWriter what(argv[1]);
    return 0;
  }

  std::string project_name;
  std::cin >> project_name;
  TexWriter what(project_name);

  return 0;
}
