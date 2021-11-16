// #ifndef _LINUX_EXPLODER_HPP
// #define _LINUX_EXPLODER_HPP

// #include <iostream>

// #include "../ExploderInterface.hpp"
// #include "../extra/include/Definitions.hpp"
// #include "../extra/include/Directory.hpp"
// #include "../extra/include/string_support.hpp"
// #include "ZipEntry.hpp"

// class LinuxExploder implements ExploderInterface {
//   friend std::ostream &operator<<(std::ostream &out, const LinuxExploder &obj);
//   friend std::istream &operator>>(std::istream &in, LinuxExploder &obj);

//   std::string _filename;
//   ZipEntrys _lines;
//   std::string _fn = Directory(this->_filename).filename();
//   std::string _path = Directory(this->_filename).pathname();
//   std::string _tmpFn = "/tmp/" + _fn;
//   std::string _tmpImplodedFn = replace_all(_tmpFn, ".zip", ".imploded.zip");
//   std::string _tmpImplosionFn = replace_all(_tmpFn, ".zip", ".implosion.zip");
//   std::string _implodedFn = _path + replace_all(_fn, ".zip", ".imploded.zip");
//   std::string _implosionFn = _path + replace_all(_fn, ".zip", ".implosion.zip");

//   std::string delete_stub(const std::string &path) const;
//   std::string move_content(const std::string &path) const;

// public:
//   LinuxExploder(const std::string &filename) : _filename(filename) {}
//   virtual void prerequisites() const;
//   virtual const std::string &Filename() const { return _filename; }
//   virtual void unzip() const;
//   virtual void execute();
//   virtual void rezip() const;
// };

// #endif // _LINUX_EXPLODER_HPP
