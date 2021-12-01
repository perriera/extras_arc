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

#include <ng_imploder/parcel/Wrap.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <ng_imploder/parcel/Parcel.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Mock WrapInterface: ParcelImploder", "[WrapInterface]") {

    imploder::Parameter testdata = ~extras::Paths("data/exparx.webflow.zip");

    SystemException::assertion("rm -rf data/client", __INFO__);
    SystemException::assertion("rm -rf data/server", __INFO__);
    SystemException::assertion("mkdir data/client", __INFO__);
    SystemException::assertion("mkdir data/server", __INFO__);
    auto copydata = "cp " + testdata + " " + "data/client";
    SystemException::assertion(copydata, __INFO__);

    imploder::Parameter original = extras::replace_all(testdata, "data/", "data/client/");
    imploder::Parameter wrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip_packed.txt");
    imploder::Parameter unwrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip");
    imploder::Parameter duplicate = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
    imploder::Parameter wrapped_onServer;
    imploder::Parameter filename_onServer;
    Mock<imploder::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [](const imploder::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder.implode();
                imploder::Parcel parcel(imploder.imploded());
                parcel.pack();
                return parcel.packed();
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [&wrapped_onServer](const imploder::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder::Parcel parcel(imploder.imploded());
                parcel.unpack();
                parcel.merge();
                parcel.clean();
                if (fs::exists(imploder.original())) {
                    imploder.explode();
                    return imploder.exploded();
                }
                return parcel.original();
            });

    When(Method(mock, merge))
        .AlwaysDo(
            [](const imploder::Filename& filename) {
                ng::Imploder imploder(filename);
                if (fs::exists(imploder.original())) {
                    imploder.merge();
                    return filename;
                }
                FileNotFoundException::assertion(imploder.imploded(), __INFO__);
                auto a = imploder.imploded();
                auto b = imploder.original();
                auto cmd = "mv " + a + " " + b;
                SystemException::assertion(cmd, __INFO__);
                imploder.clean();
                return filename;
            });

    When(Method(mock, clean))
        .AlwaysDo(
            [](const imploder::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder::Parcel parcel(imploder.imploded());
                parcel.clean();
                imploder.clean();
                return filename;
            });

    imploder::WrapInterface& i = mock.get();

    i.clean(original);

    REQUIRE(fs::exists(original));
    REQUIRE(i.wrap(original) == wrapped);
    {
        auto copydata = "cp " + wrapped + " " + "data/server";
        SystemException::assertion(copydata, __INFO__);
        wrapped_onServer = extras::replace_all(wrapped, "data/client", "data/server");
        filename_onServer = extras::replace_all(original, "data/client", "data/server");
        unwrapped = extras::replace_all(unwrapped, "data/client", "data/server");
    }

    REQUIRE(i.unWrap(filename_onServer) == unwrapped);
    REQUIRE(fs::exists(unwrapped));
    REQUIRE(i.merge(filename_onServer) == filename_onServer);
    REQUIRE(!fs::exists(unwrapped));
    REQUIRE(fs::exists(filename_onServer));
    REQUIRE(i.clean(filename_onServer) == filename_onServer);
    REQUIRE(fs::exists(filename_onServer));
    REQUIRE(fs::exists(original));
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));
    Verify(Method(mock, clean));

}
