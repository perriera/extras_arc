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


#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace extras;


SCENARIO("Test ImploderInterface: rezip webflow", "[ImploderInterface]") {

    ng::Filename before = ~extras::Paths("data/exparx.webflow.zip");
    ng::Filename after = before + "_imploded";
    ng::Imploder imploder(before);

    ng::ImploderInterface& i = imploder;

    REQUIRE(fs::exists(i.original()));
    i.clean();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.imploded()));
    REQUIRE(!fs::exists(i.exploded()));
    i.implode();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.imploded()));
    REQUIRE(!fs::exists(i.exploded()));
    i.explode();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.imploded()));
    REQUIRE(fs::exists(i.exploded()));
    i.clean();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.imploded()));
    REQUIRE(!fs::exists(i.exploded()));
}
