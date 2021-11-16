
#include <iostream>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/paths.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ImploderInterface: toOctal", "[ImploderInterface]") {

    ng::Filename before = ~extras::Paths("data/exparx.webflow.zip");
    ng::Filename after = before += "_imploded";
    Mock<ng::ImploderInterface> mock;
    When(Method(mock, before)).Return(before);
    When(Method(mock, after)).Return(after);
    When(Method(mock, unzip)).Return();
    When(Method(mock, implode)).Return();
    When(Method(mock, explode)).Return();
    When(Method(mock, rezip)).Return();

    ng::ImploderInterface& i = mock.get();

    REQUIRE(i.before() == before);
    i.unzip();
    i.implode();
    i.explode();
    i.rezip();
    REQUIRE(i.after() == after);
    Verify(Method(mock, unzip));
    Verify(Method(mock, implode));
    Verify(Method(mock, explode));
    Verify(Method(mock, rezip));
}

