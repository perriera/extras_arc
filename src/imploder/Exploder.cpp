// #include "../include/Imploder/Linux/Exploder.hpp"
// #include "../extra/include/Directory.hpp"
// #include "../extra/include/string_support.hpp"
// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <vector>

// using namespace std;

// std::ostream &operator<<(std::ostream &out, const LinuxExploder &obj) {
//   for (auto line : obj._lines) {
//     if (line.isImplodable()) {
//       out << obj.delete_stub(line) << endl;
//       out << obj.move_content(line) << endl;
//     }
//   }
//   return out;
// }

// std::istream &operator>>(std::istream &in, LinuxExploder &obj) {
//   while (in.good()) {
//     ZipEntry line;
//     in >> line;
//     if (in.good())
//       obj._lines.push_back(line);
//   }
//   return in;
// }

// void LinuxExploder::prerequisites() const {
//   FileNotFoundException::assertion(_filename);
//   FileNotFoundException::assertion(_implodedFn);
//   FileNotFoundException::assertion(_implosionFn);
// }

// void LinuxExploder::unzip() const {
//   string script_name = "./unzipit.sh";
//   {
//     ofstream script(script_name);
//     script << "cp " << _filename << " /tmp/" << _fn << endl;
//     script << "cp " << _implodedFn << " " << _tmpImplodedFn << endl;
//     script << "cp " << _implosionFn << " " << _tmpImplosionFn << endl;
//     script << "rm -rf /tmp/t1" << endl;
//     script << "mkdir /tmp/t1" << endl;
//     script << "mkdir /tmp/t1/t2" << endl;
//     script << "mkdir /tmp/t1/t3" << endl;
//     script << "unzip " << _tmpImplodedFn << " -d /tmp/t1/t2" << endl;
//     script << "unzip " << _tmpImplosionFn << " -d /tmp/t1/t3" << endl;
//     script << "find /tmp/t1/t2 -ls >/tmp/t1/listing.txt" << endl;
//   }
//   string chmod = "chmod +x " + script_name;
//   string rm_script = "rm " + script_name;
//   system(chmod.c_str());
//   system(script_name.c_str());
//   system(rm_script.c_str());
// }

// void LinuxExploder::execute() {
//   prerequisites();
//   unzip();
//   {
//     ifstream listing("/tmp/t1/listing.txt");
//     ofstream script("/tmp/t1/listing.sh");
//     listing >> *this;
//     script << *this;
//   }
//   system("chmod +x /tmp/t1/listing.sh");
//   system("/tmp/t1/listing.sh");
//   rezip();
// }

// void LinuxExploder::rezip() const {
//   string script_name = "./rezip.sh";
//   string just_the_filename = Directory(_filename).filename();
//   string just_the_pathname = Directory(_filename).pathname();
//   string exploded_name =
//       replace_all(just_the_filename, ".zip", ".upgrades.zip");
//   {
//     ofstream script(script_name);
//     script << "cp /tmp/" << just_the_filename << " /tmp/" << exploded_name
//            << endl;
//     script << "cd /tmp/t1/t2" << endl;
//     script << "zip -r ../../" << exploded_name << " . " << endl;
//     script << "rm -rf /tmp/t1" << endl;
//     script << "rm " << this->_tmpFn << endl;
//     script << "rm " << this->_tmpImplodedFn << endl;
//     script << "rm " << this->_tmpImplosionFn << endl;
//   }
//   string chmod = "chmod +x " + script_name;
//   string rm_script = "rm " + script_name;
//   system(chmod.c_str());
//   system(script_name.c_str());
//   system(rm_script.c_str());
//   {
//     Directory cp1("/tmp/" + exploded_name);
//     cp1.copyTo(Directory(just_the_pathname + exploded_name));
//     cp1.remove();
//   }
// }

// std::string LinuxExploder::move_content(const std::string &path) const {
//   stringstream ss;
//   ss << "mv " << replace_all(path, "/tmp/t1/t2/", "/tmp/t1/t3/") << " " << path;
//   return ss.str();
// }

// std::string LinuxExploder::delete_stub(const std::string &path) const {
//   stringstream ss;
//   ss << "rm " << path;
//   return ss.str();
// }