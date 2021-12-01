/**
 * @file ConvertLine.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief Handles the conversion of a single binary string to hex
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_IMPLODERCONVERTLINE_HPP
#define _EXPARX_IMPLODERCONVERTLINE_HPP

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
#include <ng_imploder/bin2hex/ConvertByte.hpp>
#include <iostream>

namespace extras {
    namespace imploder {

        /**
         * @brief ConvertLineInterface
         *
         */

        using HexLine = HexArray;
        using BinLine = ByteArray;

        interface ConvertLineInterface {
            virtual BinLine hexToBin(const HexLine& hexLine) const pure;
            virtual HexLine binToHex(const BinLine& binLine) const pure;
        };

        concrete class ConvertLine implements ConvertLineInterface {
        public:
            virtual BinLine hexToBin(const HexLine& hexLine) const override {
                return imploder::hexToBytes(hexLine);
            }
            virtual HexLine binToHex(const BinLine& binLine) const override {
                return imploder::bytesToHex(binLine);
            }
        };

    }
}

#endif // _EXPARX_IMPLODERCONVERTLINE_HPP


