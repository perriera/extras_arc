// #ifndef _LINUX_LINE_HPP
// #define _LINUX_LINE_HPP

// #include <iostream>
// #include <vector>

// #include "../ZipEntryInterface.hpp"
// #include <extras/interfaces.hpp>

// class ZipEntry implements ZipEntryInterface {
//   friend std::ostream& operator<<(std::ostream& out, const ZipEntry& obj);
//   friend std::istream& operator>>(std::istream& in, ZipEntry& obj);

//   long _id;
//   int _k;
//   std::string _permissions;
//   int _somenumber;
//   std::string _group;
//   std::string _user;
//   long _size;
//   std::string _month;
//   int _day;
//   std::string _time;
//   std::string _path;
//   bool _set = false;

// public:
//   bool isDirectory() const { return isSet() && _permissions[0] == 'd'; }
//   bool isSet() const { return _set; }
//   bool isHTML() const;
//   bool isCSS() const;
//   bool isJS() const;
//   bool isTS() const;
//   bool isImplodable() const;
//   bool isImage() const;
//   bool isUnzipped() const;
//   const std::string& path() const { return _path; }
// };

// typedef std::vector<ZipEntry> ZipEntrys;

// #endif // _LINUX_LINE_HPP
