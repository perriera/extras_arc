
#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ImploderInterface: toOctal", "[ImploderInterface]") {

    ng::Filename original = ~extras::Paths("data/exparx.webflow.zip");
    ng::Path originalDir = original + ".dir";
    ng::Filename imploded = original + "_imploded";
    ng::Filename exploded = original + "_exploded";
    Mock<ng::ImploderInterface> mock;
    When(Method(mock, original)).Return(original);
    When(Method(mock, imploded)).Return(imploded);
    When(Method(mock, exploded)).Return(exploded);
    When(Method(mock, unzip)).AlwaysDo([](const ng::Filename& filename, const ng::Path& dir) {
        auto cmd = "unzip -o " + filename + " -d " + dir;
        SystemException::assertion(cmd.c_str(), __INFO__);
        });
    When(Method(mock, rezip)).AlwaysDo([](const ng::Filename&, const ng::Path&) {});
    When(Method(mock, implode)).Return();
    When(Method(mock, explode)).Return();
    When(Method(mock, rezip)).Return();

    ng::ImploderInterface& i = mock.get();

    REQUIRE(i.original() == original);
    REQUIRE(i.imploded() == imploded);
    REQUIRE(i.exploded() == exploded);
    i.unzip(original, originalDir);
    i.implode();
    i.explode();
    i.rezip(original, originalDir);
    Verify(Method(mock, original));
    Verify(Method(mock, imploded));
    Verify(Method(mock, exploded));
    Verify(Method(mock, unzip));
    Verify(Method(mock, implode));
    Verify(Method(mock, explode));
    Verify(Method(mock, rezip));
}

