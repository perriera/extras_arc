// /**
//  * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
//  *
//  * Copyright (C) November 22, 2021 EXPARX INCORPORATED
//  *
//  * Permission is hereby  granted,  free of charge,  to  any  person
//  * obtaining a copy of this software and  associated  documentation
//  * files   (the  "Software"),  to deal  in   the  Software  without
//  * restriction, including  without  limitation the rights  to  use,
//  * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
//  * sell copies of the  Software, and to permit persons  to whom the
//  * Software  is  furnished to  do  so,  subject  to  the  following
//  * conditions:
//  *
//  * (See LICENSE.md for complete details)
//  *
//  */

// #include <extras_arc/wrap.hpp>
// #include <extras_arc/imploder.hpp>
// #include <extras_arc/parcel.hpp>
// #include <extras/filesystem/paths.hpp>
// #include <extras/strings.hpp>
// #include <extras_arc/imploder.hpp>
// #include <iostream>
// #include <fstream>
// #include <filesystem>
// #include <extras/filesystem/system.hpp>

// #include "../vendor/catch.hpp"
// #include "../vendor/fakeit.hpp"

// using namespace extras;
// using namespace fakeit;
// using namespace std;
// namespace fs = std::filesystem;

// SCENARIO("Mock WrapInterface: ParcelImploder", "[WrapInterface]") {

//     Parameter testdata = ~extras::Paths("data/exparx.webflow.zip");

//     SystemException::assertion("rm -rf data/client", __INFO__);
//     SystemException::assertion("rm -rf data/server", __INFO__);
//     SystemException::assertion("mkdir data/client", __INFO__);
//     SystemException::assertion("mkdir data/server", __INFO__);
//     auto copydata = "cp " + testdata + " " + "data/client";
//     SystemException::assertion(copydata, __INFO__);

//     Parameter original = extras::replace_all(testdata, "data/", "data/client/");
//     Parameter wrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip_packed.txt");
//     Parameter unwrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip");
//     Parameter duplicate = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
//     Parameter wrapped_onServer;
//     Parameter filename_onServer;
//     Mock<arc::WrapInterface> mock;

//     When(Method(mock, wrap))
//         .AlwaysDo(
//             [&original]() {
//                 arc::Imploder arc(original);
//                 arc.implode();
//                 arc::Parcel parcel(arc.imploded());
//                 parcel.pack();
//                 return parcel.packed();
//             });

//     When(Method(mock, unWrap))
//         .AlwaysDo(
//             [&wrapped_onServer, &original]() {
//                 arc::Imploder arc(original);
//                 arc::Parcel parcel(arc.imploded());
//                 parcel.unpack();
//                 parcel.merge();
//                 parcel.clean();
//                 if (fs::exists(arc.original())) {
//                     arc.explode();
//                     auto result = arc.imploded();
//                     return result;
//                 }
//                 auto result = arc.imploded();
//                 return result;
//             });

//     When(Method(mock, merge))
//         .AlwaysDo(
//             [&original]() {
//                 arc::Imploder arc(original);
//                 if (fs::exists(arc.original())) {
//                     arc.merge();
//                     return original;
//                 }
//                 FileNotFoundException::assertion(arc.imploded(), __INFO__);
//                 auto a = arc.imploded();
//                 auto b = arc.original();
//                 auto cmd = "mv " + a + " " + b;
//                 SystemException::assertion(cmd, __INFO__);
//                 arc.clean();
//                 return original;
//             });

//     When(Method(mock, clean))
//         .AlwaysDo(
//             [&original]() {
//                 arc::Imploder arc(original);
//                 arc::Parcel parcel(arc.imploded());
//                 parcel.clean();
//                 arc.clean();
//                 return original;
//             });

//     arc::WrapInterface& i = mock.get();

//     i.clean();

//     REQUIRE(fs::exists(original));
//     REQUIRE(i.wrap() == wrapped);
//     {
//         auto copydata = "cp " + wrapped + " " + "data/server";
//         SystemException::assertion(copydata, __INFO__);
//         wrapped_onServer = extras::replace_all(wrapped, "data/client", "data/server");
//         filename_onServer = extras::replace_all(original, "data/client", "data/server");
//         unwrapped = extras::replace_all(unwrapped, "data/client", "data/server");
//     }

//     REQUIRE(i.unWrap() == unwrapped);
//     REQUIRE(fs::exists(unwrapped));
//     REQUIRE(i.merge() == filename_onServer);
//     REQUIRE(!fs::exists(unwrapped));
//     REQUIRE(fs::exists(filename_onServer));
//     REQUIRE(i.clean() == filename_onServer);
//     REQUIRE(fs::exists(filename_onServer));
//     REQUIRE(fs::exists(original));
//     Verify(Method(mock, wrap));
//     Verify(Method(mock, unWrap));
//     Verify(Method(mock, clean));

// }
