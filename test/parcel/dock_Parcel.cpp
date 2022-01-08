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

#include <extras_arc/bin2hex/ConvertFile.hpp>
#include <extras_arc/parcel.hpp>
#include <extras_arc/exceptions.hpp>
#include <extras_arc/parcel/ParcelLine.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/files.hpp>
#include <extras/filesystem/system.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"
#include <extras/docking/DockIt.hpp>

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Dock ParcelInterface: hexToBin", "[ParcelInterface]") {

    Parameter original = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");
    Parameter hexed = original + "_hexed";
    Parameter packed = original + "_packed";
    Parameter duplicate = original + "_unpacked";
    Dock<arc::ParcelInterface> dock;
    When(Method(dock, original)).AlwaysReturn(original);
    When(Method(dock, hexed)).AlwaysReturn(hexed);
    When(Method(dock, packed)).AlwaysReturn(packed);
    When(Method(dock, duplicate)).AlwaysReturn(duplicate);

    When(Method(dock, pack))
        .AlwaysDo(
            [&original, &packed, &hexed]() {
                FileNotFoundException::assertion(original, __INFO__);
                std::ifstream inBin(original);
                std::ofstream outHex(hexed);
                arc::HexFile hexFile = arc::ConvertFile().convertToHex(inBin, outHex);
                arc::PackedFile packedFile;
                int cnt = 0;
                for (auto hexLine : hexFile) {
                    arc::ParcelLine packedLine(cnt, hexFile.size(), hexLine);
                    cnt++;
                    packedFile.push_back(packedLine);
                }
                std::ofstream outPacked(packed);
                for (auto packedLine : packedFile)
                    outPacked << packedLine << std::endl;
                outPacked.close();
                FileNotFoundException::assertion(packed, __INFO__);

            });

    When(Method(dock, unpack))
        .AlwaysDo(
            [&packed, &duplicate, &hexed]() {
                auto name = packed;
                FileNotFoundException::assertion(name, __INFO__);
                std::ifstream in(name);

                arc::HexFile hexFile;
                arc::PackedFile badCRC;

                arc::HexFile buffer;
                while (in.good()) {
                    arc::HexLine line;
                    getline(in, line);
                    if (line == "JUNK")
                        break;
                    if (line.size() > 0)
                        buffer.push_back(line);
                }

                for (auto text : buffer) {
                    std::stringstream ss;
                    ss << text;
                    arc::ParcelLine line;
                    try {
                        ss >> line;
                        hexFile.push_back(line.hexLine());
                        if (line.eof())
                            break;
                    }
                    catch (exception& ex) {
                        std::cout << ex.what() << std::endl;
                        std::cout << line << std::endl;
                        badCRC.push_back(line);
                    }
                }

                if (badCRC.size() > 0)
                    std::cout << "BadCRC count: " << badCRC.size() << std::endl;
                std::ofstream outHex(hexed);
                arc::ConvertFile().saveHex(outHex, hexFile);
                outHex.close();
                std::ifstream inHex(hexed);
                std::ofstream outBin(duplicate);
                arc::ConvertFile().convertToBin(inHex, outBin);
                outBin.close();
                FileNotFoundException::assertion(duplicate, __INFO__);
            }
    );

    When(Method(dock, verify_integrity))
        .AlwaysDo(
            [&original, &duplicate]() {
                FileNotFoundException::assertion(original, __INFO__);
                FileNotFoundException::assertion(duplicate, __INFO__);
                arc::ParcelException::assertion(original, duplicate, __INFO__);
                return true;
            }
    );

    When(Method(dock, merge))
        .AlwaysDo(
            [&original, &duplicate]() {
                FileNotFoundException::assertion(duplicate, __INFO__);
                auto cmd = "cp " + duplicate + " " + original;
                extras::SystemException::assertion(cmd, __INFO__);
                fs::remove(duplicate);
            }
    );

    When(Method(dock, clean))
        .AlwaysDo(
            [&hexed, &packed, &duplicate]() {
                if (fs::exists(hexed))
                    fs::remove(hexed);
                if (fs::exists(packed))
                    fs::remove(packed);
                if (fs::exists(duplicate))
                    fs::remove(duplicate);
            }
    );

    if (fs::exists(packed))
        fs::remove(packed);
    if (fs::exists(hexed))
        fs::remove(hexed);
    if (fs::exists(duplicate))
        fs::remove(duplicate);

    arc::ParcelInterface& i = dock.get();
    REQUIRE(i.original() == original);
    REQUIRE(i.hexed() == hexed);
    REQUIRE(i.packed() == packed);
    REQUIRE(i.duplicate() == duplicate);
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.hexed()));
    REQUIRE(!fs::exists(i.packed()));
    REQUIRE(!fs::exists(i.duplicate()));
    i.pack();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.hexed()));
    REQUIRE(fs::exists(i.packed()));
    REQUIRE(!fs::exists(i.duplicate()));
    i.unpack();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.hexed()));
    REQUIRE(fs::exists(i.packed()));
    REQUIRE(fs::exists(i.duplicate()));
    i.verify_integrity();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.duplicate()));
    i.merge();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.duplicate()));
    i.clean();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.hexed()));
    REQUIRE(!fs::exists(i.packed()));
    REQUIRE(!fs::exists(i.duplicate()));

    /**
     * @brief NI-6, (remove extra chars at end of the line)
     *
     */
     // original = "assets/badkitty/extra_char/src.zip_imploded.zip";
     // hexed = original + "_hexed.txt";
     // packed = original + "_packed.txt";
     // duplicate = original + "_unpacked.txt";

     // REQUIRE(fs::exists(i.packed()));
     // i.unpack();

     // Verify(Method(dock, pack));
     // Verify(Method(dock, unpack));
     // Verify(Method(dock, verify_integrity));
}

