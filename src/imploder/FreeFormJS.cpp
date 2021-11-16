// #include "../include/Imploder/Linux/FreeFormJS.hpp"
// #include "../extra/include/Directory.hpp"
// #include "../extra/include/string_support.hpp"
// #include "../include/Imploder/Linux/Exploder.hpp"
// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <vector>

// using namespace std;

// void FreeFormJSExploder::prerequisites() const {
//   FileNotFoundException::assertion(_filename);
//   FileNotFoundException::assertion(_srcImplodedFn);
// }

// void FreeFormJSExploder::unzip() const {
//   string script_name = "./unzipit.sh";
//   {
//     ofstream script(script_name);
//     script << "cp " << _filename << " " << this->_srcImplodedFn << endl;
//   }
//   string chmod = "chmod +x " + script_name;
//   string rm_script = "rm " + script_name;
//   system(chmod.c_str());
//   system(script_name.c_str());
//   system(rm_script.c_str());
// }

// void FreeFormJSExploder::execute() {
//   prerequisites();
//   unzip();
//   LinuxExploder exploder(this->_srcFn);
//   exploder.execute();
// }