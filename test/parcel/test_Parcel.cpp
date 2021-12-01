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

#include <ng_imploder/parcel/Wrap.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <ng_imploder/parcel/Parcel.hpp>
#include <ng_imploder/bin2hex/ConvertFile.hpp>
#include <ng_imploder/parcel/Parcel.hpp>
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

    imploder::Parameter parcel = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");

    imploder::Parcel packed(parcel);

    if (fs::exists(packed.packed()))
        fs::remove(packed.packed());
    if (fs::exists(packed.hexed()))
        fs::remove(packed.hexed());
    if (fs::exists(packed.duplicate()))
        fs::remove(packed.duplicate());

    imploder::ParcelInterface& i = packed;
    REQUIRE(i.original() == packed.original());
    REQUIRE(i.hexed() == packed.hexed());
    REQUIRE(i.packed() == packed.packed());
    REQUIRE(i.duplicate() == packed.duplicate());
    REQUIRE(fs::exists(packed.original()));
    REQUIRE(!fs::exists(packed.hexed()));
    REQUIRE(!fs::exists(packed.packed()));
    REQUIRE(!fs::exists(packed.duplicate()));
    i.pack();
    REQUIRE(fs::exists(packed.original()));
    REQUIRE(fs::exists(packed.hexed()));
    REQUIRE(fs::exists(packed.packed()));
    REQUIRE(!fs::exists(packed.duplicate()));
    i.unpack();
    REQUIRE(fs::exists(packed.original()));
    REQUIRE(fs::exists(packed.hexed()));
    REQUIRE(fs::exists(packed.packed()));
    REQUIRE(fs::exists(packed.duplicate()));
    REQUIRE(i.verify_integrity());
    REQUIRE(fs::exists(packed.original()));
    REQUIRE(fs::exists(packed.duplicate()));
    i.clean();
    REQUIRE(fs::exists(packed.original()));
    REQUIRE(!fs::exists(packed.hexed()));
    REQUIRE(!fs::exists(packed.packed()));
    REQUIRE(!fs::exists(packed.duplicate()));
}
