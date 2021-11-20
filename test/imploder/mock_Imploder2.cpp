
#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras/filesystem/system.hpp>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ImploderInterface: part2", "[ImploderInterface]") {

    ng::Filename original = ~extras::Paths("data/exparx.webflow.zip");
    ng::Path originalDir = original + ".dir";
    ng::Filename imploded = original + "_imploded.zip";
    ng::Filename exploded = original + "_exploded.zip";
    ng::Imploder imploder(original);
    Mock<ng::ImploderInterface> mock;
    When(Method(mock, original)).Return(original);
    When(Method(mock, imploded)).Return(imploded);
    When(Method(mock, exploded)).Return(exploded);
    When(Method(mock, implode)).AlwaysDo([&imploder, &original, &originalDir, &imploded]() {
        imploder.unzip(original, originalDir);
        for (auto& p : fs::recursive_directory_iterator(originalDir))
            if (!p.is_directory() && imploder.isImplodable(p.path())) {
                auto script = original + ".sh";
                std::string file = p.path();
                std::ofstream ss(script);
                ss << "echo hello > " + file << std::endl;
                ss.close();
                ScriptException::assertion(script.c_str(), __INFO__);
            }
        imploder.rezip(imploded, originalDir);
        imploder.rmdir(originalDir);
        });

    When(Method(mock, explode)).AlwaysDo([&imploder, &original, &imploded, &exploded]() {
        auto cp = "cp " + imploded + " " + exploded;
        SystemException::assertion(cp.c_str(), __INFO__);
        imploder.unzip(exploded, exploded + ".dir");
        imploder.unzip(original, original + ".dir");
        for (auto& p : fs::recursive_directory_iterator(exploded + ".dir"))
            if (!p.is_directory() && imploder.isImplodable(p.path())) {
                auto script = original + ".sh";
                std::string to = p.path();
                std::string from = extras::replace_all(to, "_exploded.zip", "");
                std::ofstream ss(script);
                ss << "cp " + from << " " + to << std::endl;
                ss.close();
                ScriptException::assertion(script.c_str(), __INFO__);
            }
        imploder.rezip(exploded, exploded + ".dir");
        imploder.rmdir(exploded + ".dir");
        imploder.rmdir(original + ".dir");
        });

    ng::ImploderInterface& i = mock.get();

    REQUIRE(i.original() == original);
    REQUIRE(i.imploded() == imploded);
    REQUIRE(i.exploded() == exploded);
    i.implode();
    i.explode();
    Verify(Method(mock, original));
    Verify(Method(mock, imploded));
    Verify(Method(mock, exploded));
    Verify(Method(mock, implode));
    Verify(Method(mock, explode));
}

