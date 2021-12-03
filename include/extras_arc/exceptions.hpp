/**
 * @file Exceptions.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief C++ defined custom exceptions specific to this package
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_PARCEL_EXCEPTIONS_HPP
#define _EXPARX_PARCEL_EXCEPTIONS_HPP

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
#include <extras/filesystem/files.hpp>
#include <extras/strings.hpp>
#include <extras/crcs.hpp>
#include <extras_arc/types.hpp>
#include <extras_arc/parcel/Line.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace arc {

        concrete class ArcException extends AbstractCustomException {
        public:

            ArcException(std::string msg, const extras::WhereAmI& whereAmI)
                : AbstractCustomException(msg.c_str(), whereAmI) {}
        };

        /**s
         * @brief ParcelException
         *
         */
        concrete class ParcelException extends ArcException {
        public:

            ParcelException(std::string msg, const extras::WhereAmI& whereAmI)
                : ArcException(msg.c_str(), whereAmI) {}

            static void assertion(char delimiter, const extras::WhereAmI& ref) {
                if (delimiter != ':' && delimiter != '/')
                    throw ParcelException("Bad delimiter:" + delimiter, ref);
            }

            static void assertion(const ParcelLine& line1, const ParcelLine& line2, const extras::WhereAmI& ref) {
                if (line1 != line2)
                    throw ParcelException("Corrupted save on line:" + std::to_string(line1.lineNo()), ref);
            }

            static void assertion(const BinLine& line1, const BinLine& line2, int line, const extras::WhereAmI& ref) {
                if (line1 != line2)
                    throw ParcelException("Corrupted save on line:" + std::to_string(line), ref);
            }

            static void assertion(int line_no, const extras::WhereAmI& ref) {
                if (line_no < 0)
                    throw ParcelException("Bad line number:" + std::to_string(line_no), ref);
            }

            static void assertion(int line_no1, int line_no2, const extras::WhereAmI& ref) {
                if (line_no1 != line_no2)
                    throw ParcelException("Line number out of sync:"
                        + std::to_string(line_no1) + std::to_string(line_no2), ref);
            }

            static void assertion(arc::HexLine hexLine, const extras::WhereAmI& ref) {
                for (auto c : hexLine)
                    if (!isxdigit(c))
                        throw ParcelException("Bad HexLine:" + hexLine, ref);
            }

            static void assertion(arc::CRC crc, arc::HexLine hexLine, const extras::WhereAmI& ref) {
                arc::ParcelLine check(0, 0, hexLine);
                if (check.checksum() != crc)
                    throw ParcelException("Bad CRC:" + hexLine, ref);
            }

            static void assertion(const Filename& parcel, const Filename& unpacked, const extras::WhereAmI& ref);
        };

        concrete class UnknownOptionException extends ArcException {
        public:
            UnknownOptionException(Parameter msg, const extras::WhereAmI& whereAmI)
                : ArcException(msg.c_str(), whereAmI) {}
        };

    }  // namespace arc

}  // namespace extras

#endif  // _EXPARX_PARCEL_EXCEPTIONS_HPP

