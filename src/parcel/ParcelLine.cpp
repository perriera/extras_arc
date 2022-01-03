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
#include <extras/devices/ansi_colors.hpp>
#include <extras/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace arc {

        std::ostream& operator<<(std::ostream& out, const ParcelLine& obj) {
            out << " : " << std::hex << obj.lineNo();
            out << " / " << std::hex << obj.lineCount();
            out << " : " << obj.hexLine();
            out << " : " << std::hex << obj.checksum();
            return out;
        }

        std::istream& operator>>(std::istream& in, ParcelLine& obj) {
            std::string line;
            getline(in, line);
            if (line.length() == 0)
                return in;
            stringstream ss;
            ss << line;
            char c;
            ss >> std::skipws >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._lineNo;
            ParcelException::assertion(obj._lineNo, __INFO__);
            ss >> std::skipws >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._lineCount;
            ParcelException::assertion(obj._lineCount, __INFO__);
            ss >> std::skipws >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> obj._hexLine;
            ParcelException::assertion(obj._hexLine, __INFO__);
            ss >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._crc;
            ParcelException::assertion(obj._crc, obj._hexLine, __INFO__);
            return in;
        }


    }  // namespace arc
}  // namespace extras
