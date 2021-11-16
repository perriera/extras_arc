// #ifndef _FREEFORMJS_EXPLODER_HPP
// #define _FREEFORMJS_EXPLODER_HPP

// #include <iostream>

// #include "../extra/include/Definitions.hpp"
// #include "../extra/include/Directory.hpp"
// #include "../extra/include/string_support.hpp"
// #include "../include/Imploder/Linux/Exploder.hpp"

// class FreeFormJSExploder implements ExploderInterface {
//   friend std::ostream &operator<<(std::ostream &out,
//                                   const FreeFormJSExploder &obj);
//   friend std::istream &operator>>(std::istream &in, FreeFormJSExploder &obj);

//   std::string _filename;
//   ZipEntrys _lines;
//   std::string _path = Directory(this->_filename).pathname();
//   std::string _tmpFilename = "/tmp/" + Directory(this->_filename).filename();
//   std::string _srcFn = _path + "src.zip";
//   std::string _srcImplodedFn = _path + "src.imploded.zip";
//   std::string _srcImplosionFn = _path + "src.implosion.zip";

// public:
//   FreeFormJSExploder(const std::string &filename) : _filename(filename){};
//   virtual void prerequisites() const;
//   virtual const std::string &Filename() const { return _filename; };
//   virtual void unzip() const;
//   virtual void execute();
//   virtual void rezip() const {};
// };

// #endif // _LINUX_EXPLODER_HPP
