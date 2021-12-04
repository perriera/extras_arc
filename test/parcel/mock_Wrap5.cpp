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
#include <extras_arc/imploder.hpp>
#include <extras_arc/parcel.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras_arc/imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Mock WrapInterface: ParcelImploder", "[WrapInterface]") {

    Parameter testdata = ~extras::Paths("data/exparx.webflow.zip");
    Mock<arc::WrapInterface> mock;

    When(Method(mock, original))
        .AlwaysDo(
            [&testdata]() {
                return testdata;
            });

    When(Method(mock, wrap))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc.implode();
                arc::Parcel parcel(arc.imploded());
                parcel.pack();
                return parcel.packed();
            });

    When(Method(mock, wrapped))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc::Parcel parcel(arc.imploded());
                return parcel.packed();
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc::Parcel parcel(arc.imploded());
                parcel.unpack();
                parcel.merge();
                parcel.clean();
                if (fs::exists(arc.original())) {
                    arc.explode();
                    auto result = arc.exploded();
                    return result;
                }
                auto result = arc.imploded();
                return result;
            });

    When(Method(mock, unWrapped))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc::Parcel parcel(arc.imploded());
                return arc.exploded();
            });

    When(Method(mock, merge))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                if (fs::exists(arc.original())) {
                    arc.merge();
                    return testdata;
                }
                FileNotFoundException::assertion(arc.imploded(), __INFO__);
                auto a = arc.imploded();
                auto b = arc.original();
                auto cmd = "mv " + a + " " + b;
                SystemException::assertion(cmd, __INFO__);
                arc.clean();
                return testdata;
            });

    When(Method(mock, clean))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc::Parcel parcel(arc.imploded());
                parcel.clean();
                arc.clean();
                return testdata;
            });

    arc::WrapInterface& i = mock.get();

    REQUIRE(i.clean() == testdata);
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    REQUIRE(i.wrap() == i.wrapped());
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(fs::exists(i.wrapped()));

    REQUIRE(i.unWrap() == i.unWrapped());
    REQUIRE(fs::exists(testdata));
    REQUIRE(fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    REQUIRE(i.merge() == testdata);
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(fs::exists(testdata));

    REQUIRE(i.clean() == testdata);
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));
    Verify(Method(mock, clean));

}
