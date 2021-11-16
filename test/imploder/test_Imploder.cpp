
#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace extras;

SCENARIO("Test ImploderInterface: toOctal", "[ImploderInterface]") {

    ng::Filename before = ~extras::Paths("data/exparx.webflow.zip");
    ng::Filename after = before + "_imploded";
    ng::Imploder imploder(before);

    ng::ImploderInterface& i = imploder;
    REQUIRE(i.before() == before);
    i.unzip();
    REQUIRE(fs::exists(i.tempDir()));
    i.implode();
    i.explode();
    i.rezip();
    REQUIRE(i.after() == after);
}

