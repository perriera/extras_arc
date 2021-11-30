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
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
 *
 */

#ifndef _EXTRAS_NG_IMPLODER_HPP
#define _EXTRAS_NG_IMPLODER_HPP

#include <iostream>
#include <extras/interfaces.hpp>

namespace extras {
  namespace ng {

    /**
     * @brief interface ImploderInterfac
     *
     */

    using Filename = std::string;
    using Path = std::string;

    interface ImploderInterface {

      /**
       * @brief original/imploded/exploded
       *
       * @return const Filename&
       */
      virtual const Filename& original() const pure;
      virtual Filename imploded() const pure;
      virtual Filename exploded() const pure;

      /**
       * @brief unzip/rezip
       *
       * @return const Filename&
       */
      virtual void unzip(const Filename&, const Path& to) const pure;
      virtual void rezip(const Filename&, const Path& from) const pure;

      /**
       * @brief implode/explode
       *
       * @return const Filename&
       */
      virtual void implode() const pure;
      virtual bool isImplodable(const Filename&) const pure;
      virtual void explode() const pure;
      virtual void merge() const pure;
      virtual void clean() const pure;

      /**
       * @brief rm/rmdir
       *
       * @return const Filename&
       */
      virtual void rm(const Filename& to) const pure;
      virtual void rmdir(const Path& to) const pure;
    };

    /**
     * @brief class Imploder
     *
     */

    concrete class Imploder implements ImploderInterface {
      Filename _original;

    public:
      Imploder(const Filename& original) :
        _original(original) {}

      virtual const Filename& original() const override {
        return _original;
      }
      virtual Filename imploded() const override {
        return _original + "_imploded.zip";
      }
      virtual Filename exploded() const override {
        return _original + "_exploded.zip";;
      }

      virtual void unzip(const Filename&, const Path& to) const override;
      virtual bool isImplodable(const Filename&) const override;

      virtual void implode() const override;
      virtual void explode() const override;
      virtual void rezip(const Filename&, const Path& from) const override;
      virtual void rm(const Filename& to) const override;
      virtual void rmdir(const Path& to) const override;
      virtual void merge() const override;
      virtual void clean() const override;


    };

    /**
     * @brief class NGException
     *
     */
    concrete class ImploderException extends extras::AbstractCustomException {
    public:
      ImploderException(const char* msg, const extras::WhereAmI& whereAmI)
        : extras::AbstractCustomException(msg, whereAmI._file.c_str(),
          whereAmI._func.c_str(), whereAmI._line) {}
      static void assertion(const std::string& msg, const extras::WhereAmI& ref);
    };

  }
}

#endif // _EXTRAS_NG_IMPLODER_HPP
