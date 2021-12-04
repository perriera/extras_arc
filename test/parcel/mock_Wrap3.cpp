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
namespace fs = std::filesystem;

SCENARIO("Mock WrapInterface: Parcel", "[WrapInterface]") {

    auto cpCmd = "cp data/exparx.webflow_original.zip data/exparx.webflow.zip";
    SystemException::assertion(cpCmd, __INFO__);

    Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    Parameter packed = extras::replace_all(original, "webflow.zip", "webflow.zip_packed.txt");
    Parameter unpacked = extras::replace_all(original, "webflow.zip", "webflow.zip_duplicate.bin");
    Mock<arc::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [&original]() {
                arc::Parcel parcel(original);
                parcel.pack();
                auto x = parcel.packed();
                return x;
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [&original]() {
                arc::Parcel parcel(original);
                parcel.unpack();
                auto y = parcel.duplicate();
                return y;
            });

    arc::WrapInterface& i = mock.get();

    arc::Parcel parcel(original);
    parcel.clean();

    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(!fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));
    REQUIRE(i.wrap() == packed);
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));
    REQUIRE(i.unWrap() == unpacked);
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(fs::exists(parcel.packed()));
    REQUIRE(fs::exists(parcel.duplicate()));
    parcel.clean();
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(!fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));

}
