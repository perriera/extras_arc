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
#include <extras_arc/parcel/Parcel.hpp>
#include <extras_arc/imploder.hpp>

namespace extras {
    namespace arc {
        /**
         * @brief WrapInterface
         *
         */

        interface WrapInterface {

            virtual Filename wrap(const Filename& filename) const pure;
            virtual Filename unWrap(const Filename& filename) const pure;
            virtual Filename merge(const Filename& filename) const pure;
            virtual Filename clean(const Filename& filename) const pure;
            virtual Filename wrapped(const Filename& filename) const pure;
            virtual Filename unWrapped(const Filename& filename) const pure;

            bool operator==(const WrapInterface& rhs) const;
            bool operator!=(const WrapInterface& rhs) const {
                return !(*this == rhs);
            }
        };

        /**
         * @brief ParcelImploder
         *
         */
        concrete class ParcelImploder implements WrapInterface {

        public:
            virtual Filename wrap(const Filename& filename) const override;
            virtual Filename unWrap(const Filename& filename) const override;
            virtual Filename merge(const Filename& filename) const override;
            virtual Filename clean(const Filename& filename) const override;
            virtual Filename wrapped(const Filename& filename) const override;
            virtual Filename unWrapped(const Filename& filename) const override;

        };

    }  // namespace arc

}  // namespace extras

#endif  // _EXPARX_WRAP_HPP
