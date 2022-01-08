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

#include <extras_arc/bin2hex/ConvertLine.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"
#include <extras/docking/DockIt.hpp>

using namespace extras;
using namespace fakeit;

SCENARIO("Dock ConvertLineInterface", "[ConvertInterface]") {

    Dock<arc::ConvertLineInterface> dock;
    When(Method(dock, hexToBin))
        .AlwaysDo(
            [](const arc::HexLine& hexLine) {
                arc::BinLine binLine = arc::hexToBytes(hexLine);
                return binLine;
            });
    When(Method(dock, binToHex))
        .AlwaysDo(
            [](const arc::BinLine& binLine) {
                arc::HexLine hexLine = arc::bytesToHex(binLine);
                return hexLine;
            });

    arc::ConvertLineInterface& i = dock.get();
    arc::BinLine binLine = { 'a', 'b', 'c' };
    arc::HexLine hexLine = i.binToHex(binLine);
    REQUIRE(i.hexToBin(hexLine) == binLine);
    REQUIRE(i.binToHex(binLine) == hexLine);
    Verify(Method(dock, hexToBin));
    Verify(Method(dock, binToHex));
}
