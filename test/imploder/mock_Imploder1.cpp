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
#include <extras_arc/imploder.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ImploderInterface: part1", "[ImploderInterface]") {

    arc::Filename original = ~extras::Paths("data/exparx.webflow.zip");
    arc::Path originalDir = original + ".dir";
    arc::Filename imploded = original + "_imploded.zip";
    arc::Filename exploded = original + "_exploded.zip";
    Mock<arc::ImploderInterface> mock;
    When(Method(mock, original)).Return(original);
    When(Method(mock, imploded)).Return(imploded);
    When(Method(mock, exploded)).Return(exploded);
    When(Method(mock, unzip)).AlwaysDo([](const arc::Filename& filename, const arc::Path& dir) {
        auto cmd = "unzip -o " + filename + " -d " + dir + " >/dev/null";
        SystemException::assertion(cmd.c_str(), __INFO__);
        });
    When(Method(mock, rezip)).AlwaysDo([&original](const arc::Filename& imploded, const arc::Path& dir) {
        // std::cout << "hello" << std::endl;
        auto script = imploded + ".sh";
        std::ofstream ss(script);
        ss << "cp " + original << ' ' << imploded << std::endl;
        ss << "cd " + dir << std::endl;
        ss << "zip -r " + imploded + " . " << " >/dev/null" << std::endl;
        ss.close();
        ScriptException::assertion(script.c_str(), __INFO__);
        });
    When(Method(mock, rmdir)).AlwaysDo([](const arc::Path& dir) {
        fs::remove_all(dir);
        });
    When(Method(mock, rm)).AlwaysDo([](const arc::Filename& filename) {
        fs::remove(filename);
        });
    When(Method(mock, implode)).Return();
    When(Method(mock, explode)).Return();

    arc::ImploderInterface& i = mock.get();

    REQUIRE(i.original() == original);
    REQUIRE(i.imploded() == imploded);
    REQUIRE(i.exploded() == exploded);
    i.unzip(original, originalDir);
    i.implode();
    i.explode();
    i.rezip(imploded, originalDir);
    i.rmdir(originalDir);
    i.rm(imploded);
    Verify(Method(mock, original));
    Verify(Method(mock, imploded));
    Verify(Method(mock, exploded));
    Verify(Method(mock, unzip));
    Verify(Method(mock, implode));
    Verify(Method(mock, explode));
    Verify(Method(mock, rezip));
}

