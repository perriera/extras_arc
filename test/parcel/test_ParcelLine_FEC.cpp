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
#include <extras_arc/exceptions.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;

SCENARIO("Test ParcelLine (FEC)", "[ParcelLineFEC]") {

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
        arc::ParcelLine before(i, max, hexLine, 3);
        std::stringstream ss;
        ss << before;
        std::string test1 = ss.str();
        std::cout << test1 << std::endl;
        std::stringstream ss2;
        ss2 << test1;
        arc::ParcelLine after;
        ss2 >> after;
        std::string test2 = ss.str();
        std::cout << test2 << std::endl;
        REQUIRE(test1 == test2);
        REQUIRE(before == after);
        REQUIRE(before.hexLine() == hexLine);
        REQUIRE(after.hexLine() == hexLine);
    }

}

std::string corrupt_once(const std::string& before) {
    std::string after = before;
    {
        int i = rand() % after.length();
        after[i] = after[i] + 1;
    }
    return after;
}

std::string corrupt_multiple(const std::string& before) {
    std::string after = before;
    {
        int i = rand() % after.length() / 3;
        after[i] = after[i] + 1;
    }
    {
        int i = rand() % after.length() / 2;
        after[i] = after[i] + 1;
    }
    {
        int i = rand() % after.length() / 1;
        after[i] = after[i] + 1;
    }
    return after;
}

SCENARIO("Test ParcelLine (FEC) single bit failure ", "[ParcelLineFEC]") {

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
        arc::ParcelLine before(i, max, hexLine, 3);
        std::stringstream ss;
        ss << before;
        std::string test1 = ss.str();
        std::cout << test1 << std::endl;
        auto testX = corrupt_once(test1);
        REQUIRE(test1 != testX);
        std::stringstream ss2;
        ss2 << testX;
        arc::ParcelLine after;
        ss2 >> after;
        std::string test2 = ss.str();
        std::cout << test2 << std::endl;
        REQUIRE(test1 == test2);
        REQUIRE(test1 != testX);
        REQUIRE(test2 != testX);
        REQUIRE(before == after);
        REQUIRE(before.hexLine() == hexLine);
        REQUIRE(after.hexLine() == hexLine);
    }

}

void compare(const std::string& a, const std::string& b) {
    std::cout << std::endl;
    for (size_t i = 0; i < a.length();i++) {
        if (a[i] == b[i])
            std::cout << blue;
        else
            std::cout << yellow;
        std::cout << b[i] << std::flush;
    }
}

SCENARIO("Test ParcelLine (FEC) partial failure ", "[ParcelLineFEC]") {

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
    std::string test1;
    auto testX = test1;
    for (int i = 0; i < max; i++) {
        arc::ParcelLine before(i, max, hexLine, 3);
        std::stringstream ss;
        ss << before;
        test1 = ss.str();
        std::cout << test1 << std::endl;
        testX = test1;
        for (int i = 0; i < 10; i++) {
            testX = corrupt_multiple(testX);
        }
        REQUIRE(test1 != testX);
        std::stringstream ss2;
        ss2 << testX;
        arc::ParcelLine after;
        try {
            ss2 >> after;
            // FAILED TO THROW EXCEPTION
            compare(test1, testX);
            FAIL("arc::ParcelException not thrown");
        }
        catch (arc::ParcelException& ex) {
            std::cout << ex << std::endl;
            compare(test1, testX);
            SUCCEED(ex);
        }
    }

}

SCENARIO("Test ParcelLine (FEC) total failure ", "[ParcelLineFEC]") {

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
        arc::ParcelLine before(i, max, hexLine, 3);
        std::stringstream ss;
        ss << before;
        std::string test1 = ss.str();
        std::cout << test1 << std::endl;
        auto testX = "totally destroyed packet";
        REQUIRE(test1 != testX);
        std::stringstream ss2;
        ss2 << testX;
        arc::ParcelLine after;
        try {
            ss2 >> after;
            FAIL("arc::ParcelException not thrown");
        }
        catch (arc::ParcelException& ex) {
            SUCCEED(ex);
        }
    }

}

