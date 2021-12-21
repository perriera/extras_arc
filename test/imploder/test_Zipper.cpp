// /**
//  * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
//  *
//  * Copyright (C) November 22, 2021 EXPARX INCORPORATED
//  *
//  * Permission is hereby  granted,  free of charge,  to  any  person
//  * obtaining a copy of this software and  associated  documentation
//  * files   (the  "Software"),  to deal  in   the  Software  without
//  * restriction, including  without  limitation the rights  to  use,
//  * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
//  * sell copies of the  Software, and to permit persons  to whom the
//  * Software  is  furnished to  do  so,  subject  to  the  following
//  * conditions:
//  *
//  * (See LICENSE.md for complete details)
//  *
//  */

// #include <extras_arc/zipper.hpp>
// #include <extras/filesystem/paths.hpp>
// #include <extras/strings.hpp>
// #include <iostream>
// #include <fstream>
// #include <filesystem>
// #include <stdlib.h>
// #include <string.h>

// #include "../vendor/catch.hpp"

// using namespace extras;
// using namespace std;
// namespace fs = std::filesystem;

// SCENARIO("Test ZipperInterface: unzip/rezip/create", "[TestZipperInterface]") {

//     Filename zipFile = "testit/src.zip";
//     Pathname zipTo = "testit/";
//     Pathname zipSrcDir = "testit/src";

//     //
//     // prepare test files
//     //
//     SystemException::assertion("rm -rf testit && mkdir testit", __INFO__);
//     SystemException::assertion("cp data/src.zip testit/src.zip", __INFO__);

//     arc::Zipper zipper1(zipFile, zipTo);
//     arc::Zipper zipper2(zipFile, zipSrcDir);
//     arc::ZipperInterface& i = zipper1;
//     arc::ZipperInterface& i2 = zipper2;
//     // test unzip
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(!fs::exists("testit/xyz"));
//     i.unzip();
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));

//     // // test rezip
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));
//     i.rezip();
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));

//     // test create
//     fs::remove("testit/src.zip");
//     REQUIRE(!fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));
//     i.create();
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));

//     // test append
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));
//     REQUIRE(fs::exists("testit/src/app"));
//     SystemException::assertion("rm -rf testit/src/app", __INFO__);
//     REQUIRE(!fs::exists("testit/src/app"));
//     i2.append();
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));
//     REQUIRE(fs::exists("testit/src/app"));

//     SystemException::assertion("rm -rf testit", __INFO__);

// }

