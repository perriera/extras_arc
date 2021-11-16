// #ifndef _LINUX_IMPLODER_HPP
// #define _LINUX_IMPLODER_HPP

// #include <iostream>

// #include "../ImploderInterface.hpp"
// #include "../extra/include/Definitions.hpp"
// #include "ZipEntry.hpp"

// class LinuxImploder implements ImploderInterface {
//   friend std::ostream& operator<<(std::ostream& out, const LinuxImploder& obj);
//   friend std::istream& operator>>(std::istream& in, LinuxImploder& obj);

//   std::string _filename;
//   ZipEntrys _lines;

//   std::string create_path(const std::string& path) const;
//   std::string move_content(const std::string& path) const;
//   std::string stub_content(const std::string& path) const;

// public:
//   LinuxImploder(const std::string& filename) : _filename(filename) {}
//   virtual void prerequisites() const;
//   virtual const std::string& Filename() const { return _filename; }
//   virtual void unzip() const;
//   virtual void execute();
//   virtual void rezip() const;
// };

// #endif // _LINUX_IMPLODER_HPP
