/**
 * @file FECLine.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief FECLineInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_FECLINE_HPP
#define _EXPARX_FECLINE_HPP

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
#include <extras/parcel/ParcelLine.hpp>
#include <iostream>
#include <sstream>

namespace extras {
    namespace arc {
        /**
         * @brief FECLineInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        using ParcelLineList = std::vector<ParcelLine>;

        interface FECLineInterface {
            virtual  int lineNo() const pure;
            virtual  int lineCount() const pure;
            virtual const ParcelLineList& list() const pure;
            virtual int lenght() const pure;
            virtual  std::string raw() const pure;

            bool operator==(const ParcelLineInterface& rhs) const {
                return lenght() == rhs.lenght() && checksum() == rhs.checksum();
            }

            bool operator!=(const ParcelLineInterface& rhs) const {
                return !(*this == rhs);
            }
        };

    }  // namespace arc

}  // namespace extras

#endif  // _EXPARX_FECLINE_HPP
