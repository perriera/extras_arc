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
#include <extras/docking/DockIt.hpp>

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Dock ImploderInterface: part1", "[ImploderInterface]") {

    Filename original = ~extras::Paths("data/exparx.webflow.zip");
    Path originalDir = original + ".dir";
    Filename imploded = original + "_imploded.zip";
    Filename exploded = original + "_exploded.zip";

    Dock<arc::ImploderInterface> dock;
    When(Method(dock, original)).Return(original);
    When(Method(dock, imploded)).Return(imploded);
    When(Method(dock, exploded)).Return(exploded);

    When(Method(dock, unzip)).AlwaysDo([](const Filename& filename, const Path& dir)
        {
            auto cmd = "unzip -o " + filename + " -d " + dir + " >/dev/null";
            SystemException::assertion(cmd.c_str(), __INFO__);
        });
    When(Method(dock, rezip)).AlwaysDo([&original](const Filename& imploded, const Path& dir)
        {
            // std::cout << "hello" << std::endl;
            auto script = imploded + ".sh";
            std::ofstream ss(script);
            ss << "cp " + original << ' ' << imploded << std::endl;
            ss << "cd " + dir << std::endl;
            ss << "zip -r " + imploded + " . " << " >/dev/null" << std::endl;
            ss.close();
            ScriptException::assertion(script.c_str(), __INFO__);
        });
    When(Method(dock, rmdir)).AlwaysDo([](const Path& dir)
        {
            fs::remove_all(dir);
        });
    When(Method(dock, rm)).AlwaysDo([](const Filename& filename)
        {
            fs::remove(filename);
        });
    When(Method(dock, implode)).Return();
    When(Method(dock, explode)).Return();

    arc::ImploderInterface& i = dock.get();

    REQUIRE(i.original() == original);
    REQUIRE(i.imploded() == imploded);
    REQUIRE(i.exploded() == exploded);
    i.unzip(original, originalDir);
    i.implode();
    i.explode();
    i.rezip(imploded, originalDir);
    i.rmdir(originalDir);
    i.rm(imploded);
    Verify(Method(dock, original));
    Verify(Method(dock, imploded));
    Verify(Method(dock, exploded));
    Verify(Method(dock, unzip));
    Verify(Method(dock, implode));
    Verify(Method(dock, explode));
    Verify(Method(dock, rezip));
}

