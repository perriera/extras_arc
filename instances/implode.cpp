// #include "../docopt/include/docopt.h"
// #include "../include/Imploder/Linux/Imploder.hpp"
// #include <fstream>
// #include <iostream>

// using namespace std;

// static const char USAGE[] =
//     R"(ChessMind.

// Usage:
//   chessmind [<name>]

// Options:
//   -h, --help           Show this screen.
//   --version            Show version.
// )";

// int main(int argc, const char *argv[]) {
//   std::map<std::string, docopt::value> args =
//       docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "ChessMind 1.0");

//   std::string name = "";

//   if (args["<name>"] && args["<name>"].isString()) {
//     name = args["<name>"].asString();
//     cout << name << endl;
//     ifstream myfile(name);
//     if (!myfile.good())
//       cout << "File not found: " << name << endl;
//     else {
//       cout << name << " found" << endl;
//       LinuxImploder imploder(name);
//       imploder.execute();
//     }
//   }

//   return 0;
// }
