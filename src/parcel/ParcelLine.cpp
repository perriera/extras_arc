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

        /**
         * @brief ParcelLine ostream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */
        std::ostream& operator<<(std::ostream& out, const ParcelLine& obj) {
            out << " : " << std::hex << obj.lineNo();
            out << " / " << std::hex << obj.lineCount();
            out << " : " << obj.hexLine();
            out << " : " << std::hex << obj.lenght();
            out << " / " << std::hex << obj.checksum();
            return out;
        }

        /**
         * @brief ParcelLine istream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */
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
            ss >> std::hex >> obj._lenght;
            ParcelException::assertion(obj._hexLine, __INFO__);
            ss >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._crc;
            ParcelException::assertion(obj, __INFO__);
            return in;
        }

        /**
         * @brief Construct a new Parcel Line:: Parcel Line object
         *
         * @param lineNo
         * @param lineCount
         * @param hexLine
         */
        ParcelLine::ParcelLine(
            int lineNo, int lineCount,
            const HexLine& hexLine, int redundancy) :
            _lineNo(lineNo), _lineCount(lineCount),
            _hexLine(hexLine), _redundancy(redundancy) {

            std::stringstream ss1;
            ss1 << *this;
            this->_lenght = ss1.str().size();

            std::stringstream ss2;
            ss2 << *this;
            std::string serialized = ss2.str();

            this->_crc = crc16().update(serialized);

        }


    }  // namespace arc
}  // namespace extras
