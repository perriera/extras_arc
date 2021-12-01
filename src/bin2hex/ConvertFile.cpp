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
#include <extras_arc/bin2hex/ConvertFile.hpp>

using namespace std;

namespace extras {
    namespace arc {

        arc::BinFile ConvertFile::loadBin(std::istream& in, int columns) const {
            arc::BinFile binFile;
            arc::ConvertLine converter;
            while (in.good()) {
                arc::BinLine line;
                for (int i = 0; i < columns && in.good();i++) {
                    byte b = 0;
                    in >> std::noskipws >> b;
                    if (in.good())
                        line.push_back(b);
                }
                binFile.push_back(line);
            }
            return binFile;
        }

        arc::HexFile ConvertFile::loadHex(std::istream& in) const {
            arc::HexFile hexFile;
            arc::ConvertLine converter;
            while (in.good()) {
                arc::HexLine line;
                getline(in, line);
                hexFile.push_back(line);
            }
            return hexFile;

        }

        void ConvertFile::saveBin(std::ostream& out, const BinFile& binFile) const {
            for (auto binLine : binFile) {
                for (auto b : binLine)
                    out << std::skipws << b;
            }
        }

        void ConvertFile::saveHex(std::ostream& out, const HexFile& hexFile) const {
            for (auto hexLine : hexFile) {
                out << hexLine << std::endl;
            }
        }

        HexFile ConvertFile::convertToHex(std::istream& inBin, std::ostream& outHex) const {
            arc::BinFile binFile = loadBin(inBin, 40);
            arc::HexFile hexFile = binToHex(binFile);
            saveHex(outHex, hexFile);
            return hexFile;
        }

        BinFile ConvertFile::convertToBin(std::istream& inHex, std::ostream& outBin) const {
            arc::HexFile hexFile = loadHex(inHex);
            arc::BinFile binFile = hexToBin(hexFile);
            saveBin(outBin, binFile);
            return binFile;
        }

    }
}
