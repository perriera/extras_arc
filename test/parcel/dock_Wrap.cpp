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
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"
#include <extras/docking/DockIt.hpp>

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Dock WrapInterface: virgin", "[WrapInterface]") {

    auto cpCmd = "cp data/exparx.webflow_original.zip data/exparx.webflow.zip";
    SystemException::assertion(cpCmd, __INFO__);

    Parameter before = ~extras::Paths("data/exparx.webflow.zip");
    Parameter after = extras::replace_all(before, "webflow.zip", "webflow.imploded.zip");
    Dock<arc::WrapInterface> dock;

    When(Method(dock, wrap))
        .AlwaysDo(
            [&after]() {
                return after;
            });

    When(Method(dock, unWrap))
        .AlwaysDo(
            [&before]() {
                return before;
            });

    arc::WrapInterface& i = dock.get();
    REQUIRE(i.wrap() == after);
    REQUIRE(i.unWrap() == before);
    Verify(Method(dock, wrap));
    Verify(Method(dock, unWrap));

}
