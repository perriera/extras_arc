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
#include <extras/strings.hpp>
#include <extras/filesystem/system.hpp>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ImploderInterface: part2", "[ImploderInterface]") {

    Filename original = ~extras::Paths("data/exparx.webflow.zip");
    arc::Imploder arc(original);

    Mock<arc::ImploderInterface> mock;
    When(Method(mock, implode)).AlwaysDo([&arc, &original]() {
        arc.unzip(original, original + ".dir");
        for (auto& p : fs::recursive_directory_iterator(original + ".dir"))
            if (!p.is_directory() && arc.isImplodable(p.path())) {
                auto script = original + ".sh";
                std::string file = p.path();
                std::ofstream ss(script);
                ss << "echo hello > " + file << std::endl;
                ss.close();
                ScriptException::assertion(script.c_str(), __INFO__);
            }
        arc.rezip(arc.imploded(), original + ".dir");
        arc.rmdir(original + ".dir");
        });

    When(Method(mock, explode)).AlwaysDo([&arc, &original]() {
        auto cp = "cp " + arc.imploded() + " " + arc.exploded();
        SystemException::assertion(cp.c_str(), __INFO__);
        arc.unzip(arc.exploded(), arc.exploded() + ".dir");
        arc.unzip(original, original + ".dir");
        for (auto& p : fs::recursive_directory_iterator(arc.exploded() + ".dir"))
            if (!p.is_directory() && arc.isImplodable(p.path())) {
                auto script = original + ".sh";
                std::string to = p.path();
                std::string from = extras::replace_all(to, "_exploded.zip", "");
                std::ofstream ss(script);
                ss << "cp " + from << " " + to << std::endl;
                ss.close();
                ScriptException::assertion(script.c_str(), __INFO__);
            }
        arc.rezip(arc.exploded(), arc.exploded() + ".dir");
        arc.rmdir(arc.exploded() + ".dir");
        arc.rmdir(original + ".dir");
        });

    arc::ImploderInterface& i = mock.get();
    i.implode();
    i.explode();
    Verify(Method(mock, implode));
    Verify(Method(mock, explode));
}

