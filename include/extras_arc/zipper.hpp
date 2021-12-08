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

#ifndef _EXPARX_ZIPPER_HPP
#define _EXPARX_ZIPPER_HPP

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
         * @brief ZipperInterface
         *
         */

        interface ZipperInterface {

            virtual void unzip(const Filename&, const Path& to) const pure;
            virtual void rezip(const Filename&, const Path& from) const pure;

        };

    }  // namespace arc

}  // namespace extras

#endif  // _EXPARX_ZIPPER_HPP
