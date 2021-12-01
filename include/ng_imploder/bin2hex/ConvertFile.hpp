/**
 * @file ConvertFile.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief Handles the conversion of binary files to hex format
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_IMPLODERCONVERTFILE_HPP
#define _EXPARX_IMPLODERCONVERTFILE_HPP

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

#include <extras/interfaces.hpp>
#include <ng_imploder/bin2hex/ConvertLine.hpp>
#include <iostream>

namespace extras {
    namespace imploder {

        /**
         * @brief ConvertFileInterface
         *
         */

        using HexFile = std::vector<HexLine>;
        using BinFile = std::vector<BinLine>;

        interface ConvertFileInterface {
            virtual BinFile hexToBin(const HexFile& hexFile) const pure;
            virtual HexFile binToHex(const BinFile& binFile) const pure;
            virtual BinFile loadBin(std::istream& in, int columns) const pure;
            virtual HexFile loadHex(std::istream& in) const pure;
            virtual void saveBin(std::ostream& in, const BinFile& binFile) const pure;
            virtual void saveHex(std::ostream& in, const HexFile& hexFile) const pure;
            virtual HexFile convertToHex(std::istream& inBin, std::ostream& outHex) const pure;
            virtual BinFile convertToBin(std::istream& inBin, std::ostream& outHex) const pure;
        };

        concrete class ConvertFile implements ConvertFileInterface {
        public:
            virtual BinFile hexToBin(const HexFile& hexFile) const override {
                imploder::BinFile binFile;
                imploder::ConvertLine converter;
                for (auto hexLine : hexFile) {
                    imploder::BinLine binline = converter.hexToBin(hexLine);
                    binFile.push_back(binline);
                }
                return binFile;
            }
            virtual HexFile binToHex(const BinFile& binFile) const override {
                imploder::HexFile hexFile;
                imploder::ConvertLine converter;
                for (auto binLine : binFile) {
                    imploder::HexLine hexline = converter.binToHex(binLine);
                    hexFile.push_back(hexline);
                }
                return hexFile;
            }
            virtual BinFile loadBin(std::istream& in, int columns = 40) const override;
            virtual HexFile loadHex(std::istream& in) const override;
            virtual void saveBin(std::ostream& in, const BinFile& binFile) const override;
            virtual void saveHex(std::ostream& in, const HexFile& hexFile) const override;
            virtual HexFile convertToHex(std::istream& inBin, std::ostream& outHex) const override;
            virtual BinFile convertToBin(std::istream& inHex, std::ostream& outBin) const override;
        };
    }
}

#endif // _EXPARX_IMPLODERCONVERTFILE_HPP


