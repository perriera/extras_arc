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

    string script_name = "build/unzipit.sh";
    string angular_src_dir = "build/src";
    ofstream ss(script_name);
    ss << "cp data/src.zip build/src.zip" << endl;
    ss << "cd build" << endl;
    ss << "rm -rf src" << endl;
    ss << "unzip src.zip" << endl;
    ss.close();
    auto cpCmd = "cp data/src.zip build/src.zip";
    ScriptException::assertion(script_name, __INFO__);

    Parameter before = ~extras::Paths("build/src");

    Mock<arc::ZipperInterface> mock;

    When(Method(mock, unzip))
        .AlwaysDo(
            [](const Filename&, const Path& to) {

            });

    When(Method(mock, rezip))
        .AlwaysDo(
            [](const Filename&, const Path& t) {

            });

    arc::ZipperInterface& i = mock.get();
    i.unzip(angular_src_dir, "");
    i.rezip(angular_src_dir, "");
    Verify(Method(mock, unzip));
    Verify(Method(mock, rezip));

}
