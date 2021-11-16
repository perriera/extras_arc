// #include "../include/Imploder/Linux/ZipEntry.hpp"
// #include "../extra/include/string_support.hpp"
// #include "../include/Imploder/Linux/Imploder.hpp"
// #include <iostream>
// #include <sstream>
// #include <vector>

// using namespace std;

// std::istream &operator>>(std::istream &in, ZipEntry &line) {

//   in >> line._id;
//   in >> line._k;
//   in >> line._permissions;
//   in >> line._somenumber;
//   in >> line._group;
//   in >> line._user;
//   in >> line._size;
//   in >> line._month;
//   in >> line._day;
//   in >> line._time;
//   in >> line._path;
//   line._set = true;

//   return in;
// }

// bool ZipEntry::isHTML() const {
//   { return isSet() && ends_with(to_lower(_path), "html"); }
// }

// bool ZipEntry::isCSS() const {
//   { return isSet() && ends_with(to_lower(_path), ".css"); }
// }

// bool ZipEntry::isJS() const {
//   { return isSet() && ends_with(to_lower(_path), ".js"); }
// }

// bool ZipEntry::isTS() const {
//   { return isSet() && ends_with(to_lower(_path), ".ts"); }
// }

// bool ZipEntry::isImage() const {
//   string lp = to_lower(_path);
//   bool _isImage = ends_with(lp, ".png") || ends_with(lp, ".jpg") ||
//                   ends_with(lp, ".jpeg") || ends_with(lp, ".bmp") ||
//                   ends_with(lp, ".raw") || ends_with(lp, ".pdf") ||
//                   ends_with(lp, ".gif") || ends_with(lp, ".psd") ||
//                   ends_with(lp, ".eps") || ends_with(lp, ".ai") ||
//                   ends_with(lp, ".indd") || ends_with(lp, ".tiff");
//   return _isImage;
// }

// bool ZipEntry::isUnzipped() const {
//   { return isSet() && starts_with(to_lower(_path), "/tmp/t1/t2"); }
// }

// bool ZipEntry::isImplodable() const {
//   return isSet() && !isDirectory() && !isHTML() && !isCSS() && !isJS() &&
//          !isTS() && isUnzipped();
// }
