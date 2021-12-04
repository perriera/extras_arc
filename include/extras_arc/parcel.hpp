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

#ifndef _EXPARX_PARCEL_HPP
#define _EXPARX_PARCEL_HPP

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
#include <extras_arc/exceptions.hpp>
#include <extras_arc/parcel/Line.hpp>
#include <extras_arc/types.hpp>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace arc {
        /**
         * @brief ParcelInterface
         *
         */

        interface ParcelInterface {

            /**
             * @brief original(), hexed(), packed(), duplicate()
             *
             * @return the original filename
             * @return the original filename + "_hexed";
             * @return the original filename + "_packed";
             * @return the original filename + "_duplicate";
             */
            virtual const Parameter& original() const pure;
            virtual const Parameter& hexed() const pure;
            virtual const Parameter& packed() const pure;
            virtual const Parameter& duplicate() const pure;

            /**
             * @brief converts the original file into it's hexademical equivalent
             *
             */
            virtual void pack() const pure;
            virtual void unpack() const pure;

            /**
             * @brief makes the duplicate the original file
             *
             */
            virtual void merge() const pure;
            virtual bool verify_integrity() const pure;

            /**
             * @brief removes any files created with the original,
             * (other than the original file)
             *
             */
            virtual void clean() const pure;

            /**
             * @brief shows the content of the hexademical file
             *
             */
            virtual void cat() const pure;

            /**
             * @brief shows the directory of the original file
             *
             */
            virtual void dir() const pure;

            /**
             * @brief shows the cotents of the duplicate file
             *
             */
            virtual void unzip() const pure;

            /**
             * @brief displays the HOWTO-parcel.md file
             *
             */
            virtual void help() const pure;

            /**
             * @brief shows the directory of the original file
             *
             * @param msg
             */
            virtual void diagnostics(std::string msg) const pure;
        };

        concrete class Parcel  implements ParcelInterface {

            Parameter _parcel;
            Parameter _hexed;
            Parameter _packed;
            Parameter _unpacked;

        public:
            Parcel(const Parameter& parcel) : _parcel(parcel) {
                _hexed = _parcel + "_hexed.txt";
                _packed = _parcel + "_packed.txt";
                _unpacked = _parcel + "_duplicate.bin";
            }
            virtual const Parameter& original() const override { return _parcel; }
            virtual const Parameter& hexed() const override { return _hexed; }
            virtual const Parameter& packed() const override { return _packed; }
            virtual const Parameter& duplicate() const override { return _unpacked; }

            virtual void pack() const override;
            virtual void unpack() const override;
            virtual void merge() const override;
            virtual bool verify_integrity() const override;
            virtual void clean() const override;
            virtual void cat() const override;
            virtual void dir() const override;
            virtual void unzip() const override;

            virtual void help() const override;
            virtual void diagnostics(std::string) const override {};

        };

        concrete class ParcelCmdLine  extends Parcel {
        public:
            ParcelCmdLine(const Parameter& parcel) : Parcel(parcel) {
            }
            virtual void diagnostics(std::string msg = "") const override;

        };

    }  // namespace arc

}  // namespace extras

#endif  // _EXPARX_PARCEL_HPP
