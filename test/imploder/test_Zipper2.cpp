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

#include <extras_arc/zipper.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/filesystem.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <string.h>

#include "../vendor/catch.hpp"

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Test ZipperInterface: command line", "[MockZipperInterface]") {

    Filename zipFile = "testit/src.zip";
    Pathname zipTo = "testit/";

    //
    // prepare test files
    //
    SystemException::assertion("rm -rf testit && mkdir testit", __INFO__);
    SystemException::assertion("cp data/src.zip testit/src.zip", __INFO__);

    // test unzip
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(!fs::exists("testit/src"));
    REQUIRE(!fs::exists("testit/src/app/app.component.ts"));
    auto unzip = "build/zipper " + zipFile + " " + zipTo + " -unzip";
    SystemException::assertion(unzip, __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app/app.component.ts"));

    // test rezip
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app/app.component.ts"));
    auto rezip = "build/zipper " + zipFile + " " + zipTo + " -rezip";
    SystemException::assertion(rezip, __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app/app.component.ts"));

    // test create
    fs::remove("testit/src.zip");
    REQUIRE(!fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    auto create = "build/zipper " + zipFile + " " + zipTo + " -create";
    SystemException::assertion(create, __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));

    // test append
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app"));
    SystemException::assertion("rm -rf testit/src/app", __INFO__);
    REQUIRE(!fs::exists("testit/src/app"));
    auto append = "build/zipper " + zipFile + " " + zipTo + " -append";
    SystemException::assertion(append, __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app"));

    // test help
    // REQUIRE(fs::exists("HOWTO-zipper.md"));
    // auto help = "build/zipper -help";
    // SystemException::assertion(help, __INFO__);

    SystemException::assertion("rm -rf testit", __INFO__);





}

