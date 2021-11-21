
#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ImploderInterface: part1", "[ImploderInterface]") {

    ng::Filename original = ~extras::Paths("data/exparx.webflow.zip");
    ng::Path originalDir = original + ".dir";
    ng::Filename imploded = original + "_imploded.zip";
    ng::Filename exploded = original + "_exploded.zip";
    Mock<ng::ImploderInterface> mock;
    When(Method(mock, original)).Return(original);
    When(Method(mock, imploded)).Return(imploded);
    When(Method(mock, exploded)).Return(exploded);
    When(Method(mock, unzip)).AlwaysDo([](const ng::Filename& filename, const ng::Path& dir) {
        auto cmd = "unzip -o " + filename + " -d " + dir + " >/dev/null";
        SystemException::assertion(cmd.c_str(), __INFO__);
        });
    When(Method(mock, rezip)).AlwaysDo([&original](const ng::Filename& imploded, const ng::Path& dir) {
        // std::cout << "hello" << std::endl;
        auto script = imploded + ".sh";
        std::ofstream ss(script);
        ss << "cp " + original << ' ' << imploded << std::endl;
        ss << "cd " + dir << std::endl;
        ss << "zip -r " + imploded + " . " << " >/dev/null" << std::endl;
        ss.close();
        ScriptException::assertion(script.c_str(), __INFO__);
        });
    When(Method(mock, rmdir)).AlwaysDo([](const ng::Path& dir) {
        fs::remove_all(dir);
        });
    When(Method(mock, rm)).AlwaysDo([](const ng::Filename& filename) {
        fs::remove(filename);
        });
    When(Method(mock, implode)).Return();
    When(Method(mock, explode)).Return();

    ng::ImploderInterface& i = mock.get();

    REQUIRE(i.original() == original);
    REQUIRE(i.imploded() == imploded);
    REQUIRE(i.exploded() == exploded);
    i.unzip(original, originalDir);
    i.implode();
    i.explode();
    i.rezip(imploded, originalDir);
    i.rmdir(originalDir);
    i.rm(imploded);
    Verify(Method(mock, original));
    Verify(Method(mock, imploded));
    Verify(Method(mock, exploded));
    Verify(Method(mock, unzip));
    Verify(Method(mock, implode));
    Verify(Method(mock, explode));
    Verify(Method(mock, rezip));
}

