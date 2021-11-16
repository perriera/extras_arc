#ifndef _IMPLODER_LINE_HPP
#define _IMPLODER_LINE_HPP

#include <iostream>

#include <extras/interfaces.hpp>

interface ZipEntryInterface {
  virtual bool isSet() const pure;
  virtual bool isDirectory() const pure;
  virtual bool isHTML() const pure;
  virtual bool isCSS() const pure;
  virtual bool isJS() const pure;
  virtual bool isTS() const pure;
  virtual bool isImplodable() const pure;
  virtual bool isUnzipped() const pure;
  virtual bool isImage() const pure;
  virtual const std::string& path() const pure;
};

#endif // _IMPLODER_LINE_HPP
