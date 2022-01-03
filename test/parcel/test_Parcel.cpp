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
#include <extras_arc/bin2hex/ConvertFile.hpp>
#include <extras_arc/parcel.hpp>
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Test ParcelInterface: hexToBin", "[ParcelInterface]") {

    Parameter imploded = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");

    arc::Parcel parcel(imploded);

    if (fs::exists(parcel.packed()))
        fs::remove(parcel.packed());
    if (fs::exists(parcel.hexed()))
        fs::remove(parcel.hexed());
    if (fs::exists(parcel.duplicate()))
        fs::remove(parcel.duplicate());

    arc::ParcelInterface& i = parcel;
    REQUIRE(i.original() == parcel.original());
    REQUIRE(i.hexed() == parcel.hexed());
    REQUIRE(i.packed() == parcel.packed());
    REQUIRE(i.duplicate() == parcel.duplicate());
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(!fs::exists(parcel.hexed()));
    REQUIRE(!fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));
    i.pack();
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(fs::exists(parcel.hexed()));
    REQUIRE(fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));
    i.unpack();
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(fs::exists(parcel.hexed()));
    REQUIRE(fs::exists(parcel.packed()));
    REQUIRE(fs::exists(parcel.duplicate()));
    REQUIRE(i.verify_integrity());
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(fs::exists(parcel.duplicate()));
    i.clean();
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(!fs::exists(parcel.hexed()));
    REQUIRE(!fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));

}

