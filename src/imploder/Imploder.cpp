#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/files.hpp>
#include <extras/filesystem/system.hpp>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

namespace extras {
    namespace ng {

        /**
         * @brief unzip
         *
         * @param zipFile
         * @param to
         */
        void Imploder::unzip(const Filename& zipFile, const Path& to) const {
            FileNotFoundException::assertion(zipFile, __INFO__);
            auto unzip = "unzip -o " + zipFile + " -d " + to + " >/dev/null";
            SystemException::assertion(unzip.c_str(), __INFO__);
        }

        /**
         * @brief rezip()
         *
         * @param filename
         * @param from
         */
        void Imploder::rezip(const Filename& filename, const Path& from) const {
            FileNotFoundException::assertion(original(), __INFO__);
            FileNotFoundException::assertion(from, __INFO__);
            auto script = original() + ".sh";
            std::ofstream ss(script);
            ss << "cp " + original() << ' ' << filename << std::endl;
            ss << "cd " + from << std::endl;
            ss << "zip -r " + filename + " . " << ">/dev/null" << std::endl;
            ss.close();
            ScriptException::assertion(script.c_str(), __INFO__);
        }

        /**
         * @brief implode
         *
         */
        void Imploder::implode() const {
            FileNotFoundException::assertion(original(), __INFO__);
            unzip(original(), original() + ".dir");
            for (auto& p : fs::recursive_directory_iterator(original() + ".dir"))
                if (!p.is_directory() && isImplodable(p.path())) {
                    auto script = original() + ".sh";
                    std::string file = p.path();
                    std::ofstream ss(script);
                    ss << "echo *imploded* > " + file << std::endl;
                    ss.close();
                    ScriptException::assertion(script.c_str(), __INFO__);
                }
            rezip(imploded(), original() + ".dir");
            rmdir(original() + ".dir");
        }

        /**
         * @brief isImplodable()
         *
         * @param filename
         * @return true
         * @return false
         */
        bool Imploder::isImplodable(const Filename& filename) const {
            string lp = to_lower(filename);
            bool _isImage = ends_with(lp, ".png") || ends_with(lp, ".jpg") ||
                ends_with(lp, ".jpeg") || ends_with(lp, ".bmp") ||
                ends_with(lp, ".raw") || ends_with(lp, ".pdf") ||
                ends_with(lp, ".gif") || ends_with(lp, ".psd") ||
                ends_with(lp, ".eps") || ends_with(lp, ".ai") ||
                ends_with(lp, ".indd") || ends_with(lp, ".tiff")
                || ends_with(lp, ".svg");
            return _isImage;
        }

        /**
         * @brief explode()
         *
         */
        void Imploder::explode() const {
            FileNotFoundException::assertion(imploded(), __INFO__);
            auto cp = "cp " + imploded() + " " + exploded();
            SystemException::assertion(cp.c_str(), __INFO__);
            unzip(exploded(), exploded() + ".dir");
            unzip(original(), original() + ".dir");
            for (auto& p : fs::recursive_directory_iterator(exploded() + ".dir"))
                if (!p.is_directory() && isImplodable(p.path())) {
                    auto script = original() + ".sh";
                    std::string to = p.path();
                    std::string from = extras::replace_all(to, "_exploded.zip", "");
                    std::ofstream ss(script);
                    ss << "cp " + from << " " + to << std::endl;
                    ss.close();
                    ScriptException::assertion(script.c_str(), __INFO__);
                }
            rezip(exploded(), exploded() + ".dir");
            rmdir(exploded() + ".dir");
            rmdir(original() + ".dir");
        }

        /**
         * @brief rm/rmdir
         *
         * @param to
         */
        void Imploder::rm(const Filename& to) const {
            if (fs::exists(to))
                fs::remove(to);
        }

        void Imploder::rmdir(const Path& to) const {
            if (fs::exists(to))
                fs::remove_all(to);
        }

        void Imploder::merge() const {
            FileNotFoundException::assertion(exploded(), __INFO__);
            if (fs::exists(original()))
                fs::remove(original());
            fs::copy_file(exploded(), original());
            fs::remove(exploded());
        }

        void Imploder::clean() const {
            fs::remove(imploded());
            fs::remove(exploded());
            rmdir(exploded() + ".dir");
            rmdir(original() + ".dir");
        }

    }
}




// #include "../include/Imploder/Linux/Imploder.hpp"
// #include "../extra/include/Directory.hpp"
// #include "../extra/include/string_support.hpp"
// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <vector>

// using namespace std;

// std::ostream &operator<<(std::ostream &out, const LinuxImploder &obj) {
//   out << "rm -rf /tmp/t1/t3" << endl;
//   for (auto line : obj._lines) {
//     if (line.isImplodable()) {
//       out << obj.create_path(line) << endl;
//       out << obj.move_content(line) << endl;
//       out << obj.stub_content(line) << endl;
//     }
//   }
//   return out;
// }

// std::istream &operator>>(std::istream &in, LinuxImploder &obj) {
//   while (in.good()) {
//     ZipEntry line;
//     in >> line;
//     if (in.good())
//       obj._lines.push_back(line);
//   }
//   return in;
// }

// void LinuxImploder::prerequisites() const {
//   FileNotFoundException::assertion(this->_filename);
// }

// void LinuxImploder::unzip() const {
//   string script_name = "./unzipit.sh";
//   {
//     ofstream script(script_name);
//     script << "rm -rf /tmp/t1" << endl;
//     script << "mkdir /tmp/t1" << endl;
//     script << "cp " << _filename << " /tmp/t1 " << endl;
//     string just_the_filename = Directory(_filename).filename();
//     script << "unzip /tmp/t1/" << just_the_filename << " -d /tmp/t1/t2" << endl;
//     script << "find /tmp/t1 -ls >/tmp/t1/listing.txt" << endl;
//     script << "echo STUB >/tmp/t1/STUB.txt" << endl;
//   }
//   string chmod = "chmod +x " + script_name;
//   string rm_script = "rm " + script_name;
//   system(chmod.c_str());
//   system(script_name.c_str());
//   system(rm_script.c_str());
// }

// void LinuxImploder::execute() {
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
//   system("rm /tmp/t1/STUB.txt");
//   rezip();
// }

// void LinuxImploder::rezip() const {
//   string script_name = "./rezip.sh";
//   string just_the_filename = Directory(_filename).filename();
//   string just_the_pathname = Directory(_filename).pathname();
//   string imploded_name =
//       replace_all(just_the_filename, ".zip", ".imploded.zip");
//   string implosion_name =
//       replace_all(just_the_filename, ".zip", ".implosion.zip");
//   {
//     ofstream script(script_name);
//     script << "cd /tmp/t1/" << endl;
//     script << "cp " << just_the_filename << " " << imploded_name << endl;
//     script << "cd /tmp/t1/t2" << endl;
//     script << "zip -r ../" << imploded_name << " . " << endl;
//     script << "cd /tmp/t1/t3" << endl;
//     script << "zip -r ../" << implosion_name << " . " << endl;
//     script << "cp /tmp/t1/" << imploded_name << " "
//            << "/tmp/" << imploded_name << endl;
//     script << "cp /tmp/t1/" << implosion_name << " "
//            << "/tmp/" << implosion_name << endl;
//     script << "cp /tmp/t1/" << just_the_filename << " "
//            << "/tmp/" << just_the_filename << endl;
//     script << "rm -rf /tmp/t1/" << endl;
//   }
//   string chmod = "chmod +x " + script_name;
//   string rm_script = "rm " + script_name;
//   system(chmod.c_str());
//   system(script_name.c_str());
//   system(rm_script.c_str());
//   // manually copy the resulting files
//   {
//     Directory cp1("/tmp/" + implosion_name);
//     Directory cp2("/tmp/" + imploded_name);
//     Directory cp3("/tmp/" + just_the_filename);
//     cp1.copyTo(Directory(just_the_pathname + implosion_name));
//     cp2.copyTo(Directory(just_the_pathname + imploded_name));
//     cp1.remove();
//     cp2.remove();
//     cp3.remove();
//   }
// }

// std::string LinuxImploder::create_path(const std::string &path) const {
//   stringstream ss;
//   auto pathname = Directory(path).pathname();
//   ss << "mkdir -p " << replace_all(pathname, "/tmp/t1/t2/", "/tmp/t1/t3/");
//   string updated = ss.str();
//   return updated;
// }

// std::string LinuxImploder::move_content(const std::string &path) const {
//   stringstream ss;
//   ss << "mv " << path << " " << replace_all(path, "/tmp/t1/t2/", "/tmp/t1/t3/");
//   return ss.str();
// }

// std::string LinuxImploder::stub_content(const std::string &path) const {
//   stringstream ss;
//   ss << "cp /tmp/t1/STUB.txt " << path;
//   return ss.str();
// }