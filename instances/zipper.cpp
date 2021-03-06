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
#include <extras_arc/zipper.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/exceptions.hpp>

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

int main(int argc, const char** argv)
{
    if (argc < 4) {
        if (argc > 1) {
            std::string option = argv[1];
            if (option == "-help") {
                arc::Zipper("ignore", "ignore").help();
                return 0;
            }
        }
        else {
            cout << "zipper <filename> <dir> [-unzip|-rezip|-create|-append|-help] " << endl;
            return -1;
        }
    }
    try {
        std::string option = (argc == 3 ? "-unzip" : argv[3]);
        auto zipFile = argv[1];
        auto zipDir = argv[2];
        arc::ZipperCmdLine zipper(zipFile, zipDir);
        if (option == "-unzip") {
            zipper.unzip();
            return 0;
        }
        if (option == "-rezip") {
            zipper.rezip();
            return 0;
        }
        if (option == "-create") {
            zipper.create();
            return 0;
        }
        if (option == "-append") {
            zipper.append();
            return 0;
        }
        if (option == "-help") {
            zipper.help();
            return 0;
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
