
#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace extras;




// SCENARIO("Test ImploderInterface: rezip webflow", "[ImploderInterface]") {

//     ng::Filename before = ~extras::Paths("data/exparx.webflow.zip");
//     ng::Filename after = before + "_imploded";
//     ng::Imploder imploder(before);

//     ng::ImploderInterface& i = imploder;

//     REQUIRE(fs::exists(i.original()));
//     i.setup();
//     REQUIRE(!fs::exists(i.implodedDir()));
//     REQUIRE(!i.unzipped(i.implodedDir()));
//     i.unzip(i.imploded(), i.implodedDir());
//     REQUIRE(i.unzipped(i.implodedDir()));
//     REQUIRE(fs::exists(i.implodedDir()));
//     i.rezip(i.imploded(), i.implodedDir());
//     REQUIRE(fs::exists(i.implodedDir()));
// }
