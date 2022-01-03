/**
 * @file Line.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ParcelLineInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_PARCELLINE_HPP
#define _EXPARX_PARCELLINE_HPP

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
#include <extras/strings.hpp>
#include <extras/crcs.hpp>
#include <extras_arc/bin2hex/ConvertLine.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace arc {
        /**
         * @brief ParcelLineInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        using CRC = u_int16_t;

        interface ParcelLineInterface {
            virtual  int lineNo() const pure;
            virtual  int lineCount() const pure;
            virtual const HexLine& hexLine() const pure;
            virtual const CRC& checksum() const pure;
            virtual  std::string raw() const pure;

            bool operator==(const ParcelLineInterface& rhs) const {
                return checksum() == rhs.checksum();
            }

            bool operator!=(const ParcelLineInterface& rhs) const {
                return !(*this == rhs);
            }
        };

        /**
         * @brief ParcelLine class
         *
         */
        concrete class ParcelLine implements ParcelLineInterface {
            friend std::ostream& operator<<(std::ostream& out, const ParcelLine& obj);
            friend std::istream& operator>>(std::istream& in, ParcelLine& obj);
            int _lineNo = 0;
            int _lineCount = 0;
            HexLine _hexLine;
            CRC _crc = 0;
        public:

            /**
             * @brief Construct a new Parcel Line object
             *
             */
            ParcelLine() {};
            ParcelLine(int lineNo, int lineCount, const HexLine& hexLine);

            /**
             * @brief ParcelLineInterface
             *
             */
            virtual  int lineNo() const override { return _lineNo; };
            virtual  int lineCount() const override { return _lineCount; };
            virtual const HexLine& hexLine() const override { return _hexLine; };
            virtual const CRC& checksum() const override { return _crc; };

            virtual  std::string raw() const override {
                std::stringstream ss;
                ss << *this;
                return ss.str();
            };

            operator std::string() const {
                return raw();
            }
        };

        using PackedFile = std::vector<ParcelLine>;

    }  // namespace arc

}  // namespace extras

#endif  // _EXPARX_PARCELLINE_HPP
