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

#include <extras_arc/wrap.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras_arc/imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Mock WrapInterface: Imploder", "[WrapInterface]") {

    auto cpCmd = "cp data/exparx.webflow_original.zip data/exparx.webflow.zip";
    SystemException::assertion(cpCmd, __INFO__);

    Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    Parameter imploded = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip");
    Parameter exploded = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
    Mock<arc::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [&original]() {
                arc::Imploder arc(original);
                arc.implode();
                return arc.imploded();
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [&original]() {
                arc::Imploder arc(original);
                arc.explode();
                return arc.exploded();
            });

    arc::WrapInterface& i = mock.get();

    arc::Imploder arc(original);
    arc.clean();

    REQUIRE(fs::exists(arc.original()));
    REQUIRE(!fs::exists(arc.imploded()));
    REQUIRE(!fs::exists(arc.exploded()));
    REQUIRE(i.wrap() == imploded);
    REQUIRE(fs::exists(arc.original()));
    REQUIRE(fs::exists(arc.imploded()));
    REQUIRE(!fs::exists(arc.exploded()));
    REQUIRE(i.unWrap() == exploded);
    REQUIRE(fs::exists(arc.original()));
    REQUIRE(fs::exists(arc.imploded()));
    REQUIRE(fs::exists(arc.exploded()));
    arc.clean();
    REQUIRE(fs::exists(arc.original()));
    REQUIRE(!fs::exists(arc.imploded()));
    REQUIRE(!fs::exists(arc.exploded()));
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));

}
