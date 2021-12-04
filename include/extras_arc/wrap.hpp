/**
 * @file Wrap.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief WrapInterface, ParcelImploder class
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_WRAP_HPP
#define _EXPARX_WRAP_HPP

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
#include <extras_arc/parcel.hpp>
#include <extras_arc/imploder.hpp>
#include <extras/status/help.hpp>
#include <extras/status/diagnostics.hpp>

namespace extras {
    namespace arc {
        /**
         * @brief WrapInterface
         *
         */

        interface WrapInterface {

            /**
             * @brief the name of the zip archive being wrapped
             *
             * @return Filename
             */
            virtual Filename original() const pure;

            /**
             * @brief performs a parcel.pack and implode.impode()
             * on the given zip archive
             *
             * @return Filename
             */
            virtual Filename wrap() const pure;
            virtual Filename unWrap() const pure;

            /**
             * @brief performs a parcel.merge and implode.merge
             * on the given zip archive
             *
             * @return Filename
             */
            virtual Filename merge() const pure;

            /**
             * @brief performs a parcel.clean and implode.clean
             * on the given zip archive
             *
             * @return Filename
             */
            virtual Filename clean() const pure;

            /**
             * @brief the name of the wrapped verison of the archive
             *
             * @return Filename
             */
            virtual Filename wrapped() const pure;
            virtual Filename unWrapped() const pure;

            bool operator==(const WrapInterface& rhs) const;
            bool operator!=(const WrapInterface& rhs) const {
                return !(*this == rhs);
            }

        };

        /**
         * @brief ParcelImploder
         *
         */
        concrete class ParcelImploder implements WrapInterface
            with HelpInterface with DiagnosticsInterface {
            Filename _filename;

        public:
            ParcelImploder(const Filename& filename) : _filename(filename) {}
            virtual Filename original() const override { return _filename; }
            virtual Filename wrap() const override;
            virtual Filename unWrap() const override;
            virtual Filename merge() const override;
            virtual Filename clean() const override;
            virtual Filename wrapped() const override;
            virtual Filename unWrapped() const override;

            virtual void help() const override;
            virtual void diagnostics(std::string) const override {};

        };

        concrete class ParcelImploderCmdLine extends  ParcelImploder {
            virtual void diagnostics(std::string) const override;
        public:
            ParcelImploderCmdLine(const Filename& filename) : ParcelImploder(filename) {}
        };


    }  // namespace arc

}  // namespace extras

#endif  // _EXPARX_WRAP_HPP
