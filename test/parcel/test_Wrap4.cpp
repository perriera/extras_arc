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
#include <extras_arc/imploder.hpp>
#include <extras_arc/parcel/Parcel.hpp>
#include <extras_arc/parcel/Parcel.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras_arc/imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>


#include "../vendor/catch.hpp"

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Test WrapInterface: ParcelImploder", "[WrapInterface]") {

    arc::Parameter testdata = ~extras::Paths("data/exparx.webflow.zip");

    SystemException::assertion("rm -rf data/client", __INFO__);
    SystemException::assertion("rm -rf data/server", __INFO__);
    SystemException::assertion("mkdir data/client", __INFO__);
    SystemException::assertion("mkdir data/server", __INFO__);
    auto copydata = "cp " + testdata + " " + "data/client";
    SystemException::assertion(copydata, __INFO__);

    arc::Parameter original = extras::replace_all(testdata, "data/", "data/client/");
    arc::Parameter wrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip_packed.txt");
    arc::Parameter unwrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip");
    arc::Parameter duplicate = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
    arc::Parameter wrapped_onServer;
    arc::Parameter filename_onServer;

    arc::ParcelImploder parcelImploder;
    arc::WrapInterface& i = parcelImploder;

    i.clean(original);

    REQUIRE(fs::exists(original));
    REQUIRE(i.wrap(original) == wrapped);
    {
        auto copydata = "cp " + wrapped + " " + "data/server";
        SystemException::assertion(copydata, __INFO__);
        wrapped_onServer = extras::replace_all(wrapped, "data/client", "data/server");
        filename_onServer = extras::replace_all(original, "data/client", "data/server");
        unwrapped = extras::replace_all(unwrapped, "data/client", "data/server");
    }

    REQUIRE(i.unWrap(filename_onServer) == unwrapped);
    REQUIRE(fs::exists(unwrapped));
    REQUIRE(i.merge(filename_onServer) == filename_onServer);
    REQUIRE(!fs::exists(unwrapped));
    REQUIRE(fs::exists(filename_onServer));
    REQUIRE(i.clean(filename_onServer) == filename_onServer);
    REQUIRE(fs::exists(filename_onServer));
    REQUIRE(fs::exists(original));

}
