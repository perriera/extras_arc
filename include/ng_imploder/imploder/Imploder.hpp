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
