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

#include <extras_arc/parcel/Parcel.hpp>
#include <extras_arc/parcel/Exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace imploder {

        void ParcelException::assertion(const Filename& parcel, const Filename& unpacked, const extras::WhereAmI& ref) {
            FileNotFoundException::assertion(parcel, ref);
            FileNotFoundException::assertion(unpacked, ref);
            auto cmd = "xxd " + parcel + " /tmp/b1.hex";
            (void)system(cmd.c_str());
            cmd = "xxd " + unpacked + " /tmp/b2.hex";
            (void)system(cmd.c_str());
            std::string outFile = "/tmp/out.txt";
            cmd = "diff /tmp/b1.hex /tmp/b2.hex >" + outFile;
            (void)system(cmd.c_str());
            if (!fs::exists(outFile) || fs::file_size(outFile) != 0)
                throw ParcelException("Files are different: (see /tmp/out.txt)", ref);
        }

    }  // namespace imploder
}  // namespace extras
