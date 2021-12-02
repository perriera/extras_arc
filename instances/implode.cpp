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
#include <extras_arc/imploder.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/exceptions.hpp>
#include <extras_arc/imploder.hpp>

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

int main(int argc, const char** argv)
{
    if (argc < 3) {
        cout << "implode <filename> [-explode|-merge|-clean|-help] " << endl;
        if (argc > 1) {
            std::string option = argv[1];
            if (option == "-help") {
                arc::Imploder("ignore").help();
                return 0;
            }
        }
        else
            return -1;
    }
    try {
        std::string option = argc == 2 ? "-implode" : argv[2];
        auto filename = argv[1];
        FileNotFoundException::assertion(filename, __INFO__);
        Parameter parameter = ~extras::Paths(filename);
        arc::ImploderCmdLine imploder(parameter);
        if (option == "-implode")
            imploder.implode();
        if (option == "-explode")
            imploder.explode();
        if (option == "-clean")
            imploder.clean();
        if (option == "-merge")
            imploder.merge();
        if (option == "-help")
            imploder.help();
        return 0;
    }
    catch (exception& ex) {
        cout << ex.what() << endl;
        return -1;
    }
}
