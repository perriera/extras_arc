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

#include <extras_arc/parcel/Wrap.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras_arc/imploder/Imploder.hpp>
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

    arc::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    arc::Parameter imploded = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip");
    arc::Parameter exploded = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
    Mock<arc::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [](const arc::Filename& filename) {
                ng::Imploder arc(filename);
                arc.implode();
                return arc.imploded();
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [](const arc::Filename& filename) {
                ng::Imploder arc(filename);
                arc.explode();
                return arc.exploded();
            });

    arc::WrapInterface& i = mock.get();

    ng::Imploder arc(original);
    arc.clean();

    REQUIRE(fs::exists(arc.original()));
    REQUIRE(!fs::exists(arc.imploded()));
    REQUIRE(!fs::exists(arc.exploded()));
    REQUIRE(i.wrap(original) == imploded);
    REQUIRE(fs::exists(arc.original()));
    REQUIRE(fs::exists(arc.imploded()));
    REQUIRE(!fs::exists(arc.exploded()));
    REQUIRE(i.unWrap(original) == exploded);
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
