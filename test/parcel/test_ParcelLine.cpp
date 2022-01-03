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
#include <extras_arc/parcel/ParcelLine.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;

SCENARIO("Test ParcelLine", "[ParcelLine]") {

    arc::ConvertLine converter;
    arc::ConvertLineInterface& i = converter;
    arc::BinLine binLine = {
        'a', 'b', 'c', 'a', 'b', 'c', 'a', 'b', 'c',
        'a', 'b', 'c', 'a', 'b', 'c', 'a', 'b', 'c',
        'a', 'b', 'c', 'a', 'b', 'c', 'a', 'b', 'c' };
    arc::HexLine hexLine = i.binToHex(binLine);
    REQUIRE(i.hexToBin(hexLine) == binLine);
    REQUIRE(i.binToHex(binLine) == hexLine);

    int max = 10;
    for (int i = 0; i < max; i++) {
        arc::ParcelLine before(i, max, hexLine);
        std::stringstream ss;
        ss << before;
        std::string test1 = ss.str();
        std::cout << test1 << std::endl;
        std::stringstream ss2;
        ss2 << test1;
        arc::ParcelLine after(i, max, hexLine);
        ss2 >> after;
        std::string test2 = ss.str();
        std::cout << test2 << std::endl;
        REQUIRE(test1 == test2);
        REQUIRE(before == after);
        REQUIRE(before.hexLine() == hexLine);
        REQUIRE(after.hexLine() == hexLine);
    }

}

