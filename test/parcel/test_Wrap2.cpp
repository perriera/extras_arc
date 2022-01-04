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
#include <extras_arc/parcel.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras/exceptions.hpp>
#include <extras_arc/imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>
#include <extras/filesystem/filesystem.hpp>


#include "../vendor/catch.hpp"

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Test WrapInterface: ParcelImploder2", "[WrapInterface]") {

    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("cp data/src.zip testit; ", __INFO__);
    SystemException::assertion("cp data/exparx.webflow.zip testit; ", __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));

    Parameter testdata = ~extras::Paths("data/exparx.webflow.zip");
    auto lock = testdata;

    arc::ParcelImploder parcelImploder(lock);
    arc::WrapInterface& i = parcelImploder;

    FileNotFoundException::assertion(lock, __INFO__);
    auto wrapped = i.wrap();
    FileNotFoundException::assertion(wrapped, __INFO__);

}

SCENARIO("Test WrapInterface: ParcelImploder3", "[WrapInterface]") {

    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("cp data/src.zip testit; ", __INFO__);
    SystemException::assertion("cp data/exparx.webflow.zip testit; ", __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));

    Parameter testdata = ~extras::Paths("testit/src.zip");
    Parameter newdata = ~extras::Paths("testit/exparx.webflow.zip");
    auto lock = testdata;

    arc::ParcelImploder parcelImploder(lock);
    arc::WrapInterface& i = parcelImploder;

    FileNotFoundException::assertion(lock, __INFO__);

    FileSystem fs(newdata);
    auto pn = fs.pathname();
    auto unzipCmd = "unzip -o " + newdata + " -d " + pn;
    SystemException::assertion(unzipCmd, __INFO__);

    auto rezipCmd = "zip -ur " + testdata + " " + pn;
    SystemException::assertion(rezipCmd, __INFO__);

    auto wrapped = i.wrap();
    FileNotFoundException::assertion(wrapped, __INFO__);

}
