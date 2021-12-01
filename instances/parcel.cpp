/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <iostream>
#include <filesystem>
#include <extras_arc/parcel/Types.hpp>
#include <extras_arc/parcel/Parcel.hpp>
#include <extras/filesystem/paths.hpp>

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

int main(int argc, const char** argv)
{
  if (argc < 3) {
    cout << "parcel [-pack|-unpack|-verify|-clean|-unzip] <filename>" << endl;
    return 0;
  }
  try {
    std::string option = argv[1];
    auto filename = argv[2];
    FileNotFoundException::assertion(filename, __INFO__);
    arc::Parameter parameter = ~extras::Paths(filename);
    arc::Parcel parcel(parameter);
    if (option == "-pack")
      parcel.pack();
    if (option == "-unpack")
      parcel.unpack();
    if (option == "-verify")
      parcel.verify_integrity();
    if (option == "-clean")
      parcel.clean();
    if (option == "-cat")
      parcel.cat();
    if (option == "-dir")
      parcel.dir();
    if (option == "-unzip")
      parcel.unzip();
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
  }
  return 0;
}
