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
#include <extras/docking/DockIt.hpp>

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Dock WrapInterface: ParcelImploder", "[WrapInterface]") {

    auto cpCmd = "cp data/exparx.webflow_original.zip data/exparx.webflow.zip";
    SystemException::assertion(cpCmd, __INFO__);
    Parameter testdata = ~extras::Paths("data/exparx.webflow.zip");
    Dock<arc::WrapInterface> dock;

    When(Method(dock, original))
        .AlwaysDo(
            [&testdata]() {
                return testdata;
            });

    When(Method(dock, wrap))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc.implode();
                arc::Parcel parcel(arc.imploded());
                parcel.pack();
                return parcel.packed();
            });

    When(Method(dock, wrapped))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc::Parcel parcel(arc.imploded());
                return parcel.packed();
            });

    When(Method(dock, unWrap))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc::Parcel parcel(arc.imploded());
                parcel.unpack();
                parcel.merge();
                parcel.clean();
                if (fs::exists(arc.original())) {
                    arc.explode();
                    return arc.exploded();;
                }
                return arc.imploded();;
            });

    When(Method(dock, unWrapped))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc::Parcel parcel(arc.imploded());
                if (fs::exists(arc.original()))
                    return arc.exploded();
                else
                    return arc.imploded();
            });

    When(Method(dock, merge))
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

    When(Method(dock, clean))
        .AlwaysDo(
            [&testdata]() {
                arc::Imploder arc(testdata);
                arc::Parcel parcel(arc.imploded());
                parcel.clean();
                arc.clean();
                return testdata;
            });

    arc::WrapInterface& i = dock.get();

    //
    // Scenario 1: Original exists
    //

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

    //
    // Scenario 2: Original does not exist
    //

    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    REQUIRE(i.wrap() == i.wrapped());
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(fs::exists(i.wrapped()));

    REQUIRE(fs::exists(testdata));
    REQUIRE(fs::exists(i.wrapped()));
    auto rmCmd = "rm data/exparx.webflow.zip";
    SystemException::assertion(rmCmd, __INFO__);
    REQUIRE(!fs::exists(testdata));
    REQUIRE(fs::exists(i.wrapped()));

    REQUIRE(i.unWrap() == i.unWrapped());
    REQUIRE(!fs::exists(testdata));
    REQUIRE(fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    REQUIRE(i.merge() == testdata);
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(fs::exists(testdata));

    REQUIRE(i.clean() == testdata);
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    // 

    Verify(Method(dock, wrap));
    Verify(Method(dock, unWrap));
    Verify(Method(dock, wrapped));
    Verify(Method(dock, unWrapped));
    Verify(Method(dock, merge));
    Verify(Method(dock, clean));

}
