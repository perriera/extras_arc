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
#include <extras/strings.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <string.h>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ZipperInterface: unzip/rezip/create", "[ZipperInterface]") {

    Filename zipFile = "testit/src.zip";
    Pathname zipDir = "testit/";

    Mock<arc::ZipperInterface> mock;
    When(Method(mock, unzip))
        .AlwaysDo(
            [&zipFile, &zipDir]() {
                FileNotFoundException::assertion(zipFile, __INFO__);
                auto unzip = "unzip -o " + zipFile + " -d " + zipDir + " >/dev/null";
                SystemException::assertion(unzip.c_str(), __INFO__);
            });
    When(Method(mock, rezip))
        .AlwaysDo(
            [&zipFile, &zipDir]() {
                FileNotFoundException::assertion(zipFile, __INFO__);
                PathNotFoundException::assertion(zipDir, __INFO__);
                auto script = "/tmp/script.sh";
                std::ofstream ss(script);
                ss << "cd " + zipDir << std::endl;
                fs::path p = zipFile;
                std::string fn = p.filename();
                ss << "zip -r ../" + fn + " . " << ">/dev/null" << std::endl;
                ss.close();
                ScriptException::assertion(script, __INFO__);
            });
    When(Method(mock, create))
        .AlwaysDo(
            [&zipFile, &zipDir]() {
                PathNotFoundException::assertion(zipDir, __INFO__);
                auto script2 = "/tmp/script.sh";
                std::ofstream ss(script2);
                ss << "cd " + zipDir << std::endl;
                string tempFile = "/tmp/temp.zip";
                if (fs::exists(tempFile))
                    fs::remove(tempFile);
                ss << "zip -r " << tempFile << " . " << ">/dev/null" << std::endl;
                fs::path p = zipFile;
                ss << "cp " << tempFile << " " << fs::absolute(p) << ">/dev/null" << std::endl;
                ss << "rm " << tempFile << ">/dev/null" << std::endl;
                ss.close();
                ScriptException::assertion(script2, __INFO__);
            });

    //
    // prepare test files
    //
    SystemException::assertion("rm -rf testit && mkdir testit", __INFO__);
    SystemException::assertion("cp data/src.zip testit/src.zip", __INFO__);

    arc::ZipperInterface& i = mock.get();
    // test unzip
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(!fs::exists("testit/src"));
    i.unzip();
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));

    // // test rezip
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    i.rezip();
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));

    // test create
    fs::remove("testit/src.zip");
    REQUIRE(!fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    i.create();
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));

    Verify(Method(mock, unzip));
    Verify(Method(mock, rezip));
    Verify(Method(mock, create));

}


SCENARIO("Mock ZipperInterface: update/append", "[ZipperInterface]") {

    Filename zipFile = "testit/src.zip";
    Pathname zipDir1 = "testit/";
    Pathname zipDir = "testit/src";

    Mock<arc::ZipperInterface> mock;
    When(Method(mock, unzip))
        .AlwaysDo(
            [&zipFile, &zipDir1]() {
                FileNotFoundException::assertion(zipFile, __INFO__);
                auto unzip = "unzip -o " + zipFile + " -d " + zipDir1 + " >/dev/null";
                SystemException::assertion(unzip.c_str(), __INFO__);
            });
    When(Method(mock, append))
        .AlwaysDo(
            [&zipFile, &zipDir]() {
                PathNotFoundException::assertion(zipDir, __INFO__);
                FileNotFoundException::assertion(zipFile, __INFO__);
                char templatebuf[80];
                char* mkdirectory = mkdtemp(strcpy(templatebuf, "/tmp/mkprogXXXXXX"));
                std::string tempDir = mkdirectory;//std::tmpnam(nullptr);
                tempDir += ".dir";
                std::string zipSrcTempDir = tempDir + "/src/";
                auto unzip = "unzip -o " + zipFile + " -d " + tempDir + " >/dev/null";
                SystemException::assertion(unzip.c_str(), __INFO__);
                for (auto& p : fs::recursive_directory_iterator(tempDir))
                    if (!p.is_directory()) {
                        // auto script = original() + ".sh";
                        std::string pathA = p.path();
                        std::string fn = p.path().filename();
                        std::string pathB = extras::replace_all(pathA, fn, "");
                        std::string subDir = extras::replace_all(pathB, zipSrcTempDir, "/");
                        std::string pathC = zipDir + subDir + fn;
                        auto cpCmd = "install -D " + pathA + " " + pathC + " >/dev/null";
                        SystemException::assertion(cpCmd.c_str(), __INFO__);
                    }
                auto rmDir = "rm -rf " + tempDir + " >/dev/null";
                SystemException::assertion(rmDir.c_str(), __INFO__);
            });

    //
    // prepare test files
    //
    SystemException::assertion("rm -rf testit && mkdir testit", __INFO__);
    SystemException::assertion("cp data/src.zip testit/src.zip", __INFO__);

    arc::ZipperInterface& i = mock.get();

    // test unzip
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(!fs::exists("testit/src"));
    i.unzip();
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app"));

    // test append
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app"));
    SystemException::assertion("rm -rf testit/src/app", __INFO__);
    REQUIRE(!fs::exists("testit/src/app"));
    i.append();
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app"));

    Verify(Method(mock, unzip));
    Verify(Method(mock, append));

    SystemException::assertion("rm -rf testit", __INFO__);

}
