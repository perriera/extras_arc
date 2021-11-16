// #include <fstream>
// #include <iostream> // std::cout
// #include <sstream>  // std::stringstream
// #include <string>   // std::string

// #include "../extra/include/Directory.hpp"
// #include "../extra/include/ansi_colors.hpp"
// #include "../extra/include/crc32_support.hpp"
// #include "../extra/include/crc64_support.hpp"
// #include "../extra/include/string_support.hpp"
// #include "../include/Imploder/Linux/Exploder.hpp"
// #include "../include/Imploder/Linux/Imploder.hpp"
// #include "catch.hpp"

// using namespace std;

// SCENARIO("Verify LinuxExploder (webflow.zip)", "[Exploder]") {

//   string fn = "data/homesite/perry-anderson.webflow.zip";
//   LinuxImploder imploder(fn);
//   imploder.execute();
//   REQUIRE(!Directory("/tmp/perry-anderson.webflow.zip").fileExists());
//   REQUIRE(!Directory("/tmp/perry-anderson.webflow.imploded.zip").fileExists());
//   REQUIRE(!Directory("/tmp/perry-anderson.webflow.implosion.zip").fileExists());
//   REQUIRE(Directory(fn).fileExists());
//   REQUIRE(Directory(replace_all(fn, ".zip", ".imploded.zip")).fileExists());
//   REQUIRE(Directory(replace_all(fn, ".zip", ".implosion.zip")).fileExists());

//   LinuxExploder exploder(fn);
//   exploder.execute();
//   REQUIRE(!Directory("/tmp/perry-anderson.webflow.upgrades.zip").fileExists());
//   REQUIRE(!Directory("/tmp/perry-anderson.webflow.zip").fileExists());
//   REQUIRE(!Directory("/tmp/perry-anderson.webflow.imploded.zip").fileExists());
//   REQUIRE(!Directory("/tmp/perry-anderson.webflow.implosion.zip").fileExists());
//   REQUIRE(Directory(fn).fileExists());
//   REQUIRE(Directory(replace_all(fn, ".zip", ".upgrades.zip")).fileExists());
// }

// SCENARIO("Verify LinuxExploder (src.zip)", "[Exploder]") {

//   string fn = "data/homesite/src.zip";
//   LinuxImploder imploder(fn);
//   imploder.execute();
//   REQUIRE(!Directory("/tmp/src.zip").fileExists());
//   REQUIRE(!Directory("/tmp/src.imploded.zip").fileExists());
//   REQUIRE(!Directory("/tmp/src.implosion.zip").fileExists());
//   REQUIRE(Directory(fn).fileExists());
//   REQUIRE(Directory(replace_all(fn, ".zip", ".imploded.zip")).fileExists());
//   REQUIRE(Directory(replace_all(fn, ".zip", ".implosion.zip")).fileExists());

//   LinuxExploder exploder(fn);
//   exploder.execute();
//   REQUIRE(!Directory("/tmp/src.upgrades.zip").fileExists());
//   REQUIRE(!Directory("/tmp/src.zip").fileExists());
//   REQUIRE(!Directory("/tmp/src.imploded.zip").fileExists());
//   REQUIRE(!Directory("/tmp/src.implosion.zip").fileExists());
//   REQUIRE(Directory(fn).fileExists());
//   REQUIRE(Directory(replace_all(fn, ".zip", ".upgrades.zip")).fileExists());
// }
