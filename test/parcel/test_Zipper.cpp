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
// #include "../vendor/fakeit.hpp"

// using namespace extras;
// using namespace std;
// using namespace fakeit;
// namespace fs = std::filesystem;

// SCENARIO("Test ZipperInterface", "[ZipperInterface]") {

//     SystemException::assertion("cp data/src.zip testit/src.zip", __INFO__);
//     SystemException::assertion("rm -rf build/src", __INFO__);

//     Filename zipFile = "testit/src.zip";
//     Pathname zipDir = "testit/";
//     Pathname zipDir2 = "testit/src";

//     arc::ZipperCmdLine zipper(zipFile, zipDir);
//     arc::ZipperInterface& i = zipper;

//     // test unzip
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(!fs::exists("testit/src"));
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

//     SystemException::assertion("cp data/src.zip testit/src.zip", __INFO__);

//     // test update
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));
//     i.update();
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));

//     // test append
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));
//     i.append();
//     REQUIRE(fs::exists("testit/src.zip"));
//     REQUIRE(fs::exists("testit/src"));

// }
