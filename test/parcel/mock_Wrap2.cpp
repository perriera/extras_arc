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

    imploder::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    imploder::Parameter imploded = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip");
    imploder::Parameter exploded = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
    Mock<imploder::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [](const imploder::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder.implode();
                return imploder.imploded();
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [](const imploder::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder.explode();
                return imploder.exploded();
            });

    imploder::WrapInterface& i = mock.get();

    ng::Imploder imploder(original);
    imploder.clean();

    REQUIRE(fs::exists(imploder.original()));
    REQUIRE(!fs::exists(imploder.imploded()));
    REQUIRE(!fs::exists(imploder.exploded()));
    REQUIRE(i.wrap(original) == imploded);
    REQUIRE(fs::exists(imploder.original()));
    REQUIRE(fs::exists(imploder.imploded()));
    REQUIRE(!fs::exists(imploder.exploded()));
    REQUIRE(i.unWrap(original) == exploded);
    REQUIRE(fs::exists(imploder.original()));
    REQUIRE(fs::exists(imploder.imploded()));
    REQUIRE(fs::exists(imploder.exploded()));
    imploder.clean();
    REQUIRE(fs::exists(imploder.original()));
    REQUIRE(!fs::exists(imploder.imploded()));
    REQUIRE(!fs::exists(imploder.exploded()));
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));

}
