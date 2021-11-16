#include <iostream>
#include <filesystem>

// #
// # CMakeLists.txt uses a GLOB_RECURSE macro which automatically includes ALL headers 
// # and sources under include/ and src/. So, to keep two or more main() declarations 
// # seperate, we place any sources that have a main() in the instances/ folder
// #

int main(int, const char**)
{
  std::cout << "Hello, world" << std::endl;
  return 0;
}
