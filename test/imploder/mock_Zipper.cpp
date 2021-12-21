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
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ZipperInterface: unzip/rezip/create", "[MockZipperInterface]") {

    Filename zipFile = "testit/src.zip";
    Pathname zipTo = "testit/";

    Mock<arc::ZipperInterface> mock;
    When(Method(mock, unzip))
        .AlwaysDo(
            [&zipFile, &zipTo]() {
                FileNotFoundException::assertion(zipFile, __INFO__);
                auto fn = extras::FileSystem(zipFile).filename();
                auto target = zipTo;
                auto unzip = "unzip -o " + zipFile + " -d " + target + " >/dev/null";
                SystemException::assertion(unzip.c_str(), __INFO__);
            });
    When(Method(mock, rezip))
        .AlwaysDo(
            [&zipFile, &zipTo]() {
                FileNotFoundException::assertion(zipFile, __INFO__);
                PathNotFoundException::assertion(zipTo, __INFO__);
                auto fn1 = extras::FileSystem(zipFile).filename();
                Pathname fn2 = extras::FileSystem(zipTo).append(fn1);
                PathNotFoundException::assertion(fn2, __INFO__);
                auto script = "script.sh";
                std::ofstream ss(script);
                ss << "cd " + fn2 << std::endl;
                fs::path p = zipFile;
                std::string fn = p.filename();
                ss << "rm  ../" << fn << " >/dev/null" << std::endl;
                ss << "zip -r ../" << fn << " . " << ">/dev/null" << std::endl;
                ss.close();
                ScriptException::assertion(script, __INFO__);
            });
    When(Method(mock, create))
        .AlwaysDo(
            [&zipFile, &zipTo]() {
                PathNotFoundException::assertion(zipTo, __INFO__);
                auto fn1 = extras::FileSystem(zipFile).filename();
                Pathname fn2 = extras::FileSystem(zipTo).append(fn1);
                PathNotFoundException::assertion(fn2, __INFO__);
                auto script2 = "/tmp/script.sh";
                std::ofstream ss(script2);
                ss << "cd " + fn2 << std::endl;
                string tempFile = "/tmp/temp.zip";
                if (fs::exists(tempFile))
                    fs::remove(tempFile);
                ss << "zip -r " << tempFile << " . " << ">/dev/null" << std::endl;
                fs::path p = zipFile;
                ss << "cp " << tempFile << " " << fs::absolute(p) << " >/dev/null" << std::endl;
                ss << "rm " << tempFile << " >/dev/null" << std::endl;
                ss.close();
                ScriptException::assertion(script2, __INFO__);
            });
    When(Method(mock, append))
        .AlwaysDo(
            [&zipFile, &zipTo]() {
                PathNotFoundException::assertion(zipTo, __INFO__);
                FileNotFoundException::assertion(zipFile, __INFO__);
                auto fn1 = extras::FileSystem(zipFile).filename();
                Pathname fn2 = extras::FileSystem(zipTo).append(fn1);
                PathNotFoundException::assertion(fn2, __INFO__);
                char templatebuf[80];
                char* mkdirectory = mkdtemp(strcpy(templatebuf, "/tmp/mkprogXXXXXX"));
                std::string tempDir = mkdirectory;//std::tmpnam(nullptr);
                tempDir += ".dir";
                std::string zipSrcTempDir = tempDir + "/src/";
                auto unzip = "unzip -o " + zipFile + " -d " + tempDir + " >/dev/null";
                SystemException::assertion(unzip.c_str(), __INFO__);
                for (auto& p : fs::recursive_directory_iterator(tempDir))
                    if (!p.is_directory()) {
                        std::string from = p.path();
                        std::string to = extras::str::replace_first(from, tempDir, fn2);
                        auto cpCmd = "install -D " + from + " " + to + " >/dev/null";
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
    REQUIRE(!fs::exists("testit/src/app/app.component.ts"));
    i.unzip();
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app/app.component.ts"));

    // test rezip
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app/app.component.ts"));
    i.rezip();
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app/app.component.ts"));

    // test create
    fs::remove("testit/src.zip");
    REQUIRE(!fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    i.create();
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));

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
    Verify(Method(mock, rezip));
    Verify(Method(mock, create));
    Verify(Method(mock, append));

    SystemException::assertion("rm -rf testit", __INFO__);

}

