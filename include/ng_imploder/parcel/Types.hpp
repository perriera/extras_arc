/**
 * @file Parcel.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ParcelInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_PARCEL_TYPES_HPP
#define _EXPARX_PARCEL_TYPES_HPP

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
#include <iostream>
#include <sstream>
#include <ng_imploder/parcel/Exceptions.hpp>
#include <ng_imploder/parcel/Line.hpp>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace imploder {
        /**
         * @brief ParcelInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        using Parameter = std::string;
        using Parameters = std::deque<Parameter>;
        using Filename = std::string;

    }  // namespace imploder

}  // namespace extras

#endif  // _EXPARX_PARCEL_TYPES_HPP
