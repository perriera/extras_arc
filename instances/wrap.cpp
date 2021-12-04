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

#include <iostream>
#include <filesystem>
#include <extras_arc/types.hpp>
#include <extras_arc/wrap.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/exceptions.hpp>

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

int main(int argc, const char** argv)
{
    if (argc < 3) {
        if (argc > 1) {
            std::string option = argv[1];
            if (option == "-help") {
                arc::ParcelImploder("ignore").help();
                return 0;
            }
        }
        else {
            cout << "wrap <filename> [-wrap|-unwrap|-merge|-clean|-help] " << endl;
            return -1;
        }
    }
    try {
        std::string option = argc == 2 ? "-pack" : argv[2];
        auto filename = argv[1];
        FileNotFoundException::assertion(filename, __INFO__);
        Parameter parameter = ~extras::Paths(filename);
        arc::ParcelCmdLine parcel(parameter);
        if (option == "-pack") {
            parcel.pack();
        }
        if (option == "-unpack") {
            parcel.unpack();
        }
        if (option == "-verify") {
            parcel.verify_integrity();
        }
        if (option == "-clean") {
            parcel.clean();
        }
        if (option == "-cat") {
            parcel.cat();
        }
        if (option == "-merge") {
            parcel.merge();
        }
        if (option == "-dir") {
            parcel.dir();
        }
        if (option == "-unzip") {
            parcel.unzip();
        }
        if (option == "-help") {
            parcel.help();
        }
        throw arc::UnknownOptionException(option, __INFO__);
    }
    catch (extras::exception& ex) {
        cout << ex << endl;
        return -1;
    }
    catch (std::exception& ex) {
        cout << ex.what() << endl;
        return -1;
    }
}
