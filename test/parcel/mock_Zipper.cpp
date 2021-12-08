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

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ZipperInterface", "[ZipperInterface]") {

    SystemException::assertion("cp data/src.zip build/src.zip", __INFO__);
    SystemException::assertion("rm -rf build/src", __INFO__);

    Mock<arc::ZipperInterface> mock;
    When(Method(mock, unzip))
        .AlwaysDo(
            [](const Filename& zipFile, const Path& to) {
                FileNotFoundException::assertion(zipFile, __INFO__);
                auto unzip = "unzip -o " + zipFile + " -d " + to + " >/dev/null";
                SystemException::assertion(unzip.c_str(), __INFO__);
            });

    When(Method(mock, rezip))
        .AlwaysDo(
            [](const Filename& zipFile, const Path& from) {
                FileNotFoundException::assertion(zipFile, __INFO__);
                PathNotFoundException::assertion(from, __INFO__);
                auto script = zipFile + ".sh";
                std::ofstream ss(script);
                ss << "cd " + from << std::endl;
                fs::path p = zipFile;
                std::string fn = p.filename();
                ss << "zip -r ../" + fn + " . " << ">/dev/null" << std::endl;
                ss.close();
                ScriptException::assertion(script.c_str(), __INFO__);
            });

    {
        Paths path("~/Downloads");
        REQUIRE(fs::exists(path.c_str()));
    }

    arc::ZipperInterface& i = mock.get();
    REQUIRE(fs::exists("build/src.zip"));
    REQUIRE(!fs::exists("build/src"));
    i.unzip("build/src.zip", "build/");
    REQUIRE(fs::exists("build/src.zip"));
    REQUIRE(fs::exists("build/src"));
    i.rezip("build/src.zip", "build/");
    REQUIRE(fs::exists("build/src.zip"));
    REQUIRE(fs::exists("build/src"));
    Verify(Method(mock, unzip));
    Verify(Method(mock, rezip));

}
