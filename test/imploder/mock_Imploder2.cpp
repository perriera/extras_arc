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
#include <ng_imploder/imploder/Imploder.hpp>
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

    ng::Filename original = ~extras::Paths("data/exparx.webflow.zip");
    ng::Imploder imploder(original);
    Mock<ng::ImploderInterface> mock;

    When(Method(mock, implode)).AlwaysDo([&imploder, &original]() {
        imploder.unzip(original, original + ".dir");
        for (auto& p : fs::recursive_directory_iterator(original + ".dir"))
            if (!p.is_directory() && imploder.isImplodable(p.path())) {
                auto script = original + ".sh";
                std::string file = p.path();
                std::ofstream ss(script);
                ss << "echo hello > " + file << std::endl;
                ss.close();
                ScriptException::assertion(script.c_str(), __INFO__);
            }
        imploder.rezip(imploder.imploded(), original + ".dir");
        imploder.rmdir(original + ".dir");
        });

    When(Method(mock, explode)).AlwaysDo([&imploder, &original]() {
        auto cp = "cp " + imploder.imploded() + " " + imploder.exploded();
        SystemException::assertion(cp.c_str(), __INFO__);
        imploder.unzip(imploder.exploded(), imploder.exploded() + ".dir");
        imploder.unzip(original, original + ".dir");
        for (auto& p : fs::recursive_directory_iterator(imploder.exploded() + ".dir"))
            if (!p.is_directory() && imploder.isImplodable(p.path())) {
                auto script = original + ".sh";
                std::string to = p.path();
                std::string from = extras::replace_all(to, "_exploded.zip", "");
                std::ofstream ss(script);
                ss << "cp " + from << " " + to << std::endl;
                ss.close();
                ScriptException::assertion(script.c_str(), __INFO__);
            }
        imploder.rezip(imploder.exploded(), imploder.exploded() + ".dir");
        imploder.rmdir(imploder.exploded() + ".dir");
        imploder.rmdir(original + ".dir");
        });

    ng::ImploderInterface& i = mock.get();
    i.implode();
    i.explode();
    Verify(Method(mock, implode));
    Verify(Method(mock, explode));
}

