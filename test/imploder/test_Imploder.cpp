
#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace extras;

SCENARIO("Test ImploderInterface: reset/setup", "[ImploderInterface]") {

    ng::Filename before = ~extras::Paths("data/exparx.webflow.zip");
    ng::Filename after = before + "_imploded";
    ng::Imploder imploder(before);

    ng::ImploderInterface& i = imploder;

    REQUIRE(fs::exists(i.original()));
    i.reset();
    REQUIRE(!fs::exists(i.imploded()));
    REQUIRE(!fs::exists(i.exploded()));
    REQUIRE(!fs::exists(i.implodedDir()));
    REQUIRE(!fs::exists(i.explodedDir()));

    i.setup();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.imploded()));
    REQUIRE(fs::exists(i.exploded()));

}

SCENARIO("Test ImploderInterface: unzip", "[ImploderInterface]") {

    ng::Filename before = ~extras::Paths("data/exparx.webflow.zip");
    ng::Filename after = before + "_imploded";
    ng::Imploder imploder(before);

    ng::ImploderInterface& i = imploder;

    REQUIRE(fs::exists(i.original()));
    i.setup();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.imploded()));
    REQUIRE(fs::exists(i.exploded()));

    REQUIRE(!fs::exists(i.implodedDir()));
    i.unzip(i.imploded(), i.implodedDir());
    REQUIRE(fs::exists(i.implodedDir()));
}

