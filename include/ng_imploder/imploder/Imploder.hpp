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
      virtual const Filename& original() const pure;
      virtual const Filename& imploded() const pure;
      virtual const Filename& exploded() const pure;
      virtual Filename originalDir() const pure;
      virtual Filename implodedDir() const pure;
      virtual Filename explodedDir() const pure;
      virtual void setup() const pure;
      virtual void reset() const pure;
      virtual void move(const Filename& file, const Path& path) const pure;
      virtual void backup(const Filename& file) const pure;
      virtual void restore(const Filename& file) const pure;
      virtual void unzip(const Filename&, const Path& to) const pure;
      virtual void implode() const pure;
      virtual void explode() const pure;
      virtual void rezip(const Filename&, const Path& from) const pure;
    };

    /**
     * @brief class Imploder
     *
     */

    concrete class Imploder implements ImploderInterface {
      Filename _original;
      Filename _imploded;
      Filename _exploded;

    public:
      Imploder(const Filename& original) :
        _original(original), _imploded(original + "_imploded"), _exploded(original + "_exploded") {}

      virtual const Filename& original() const override {
        return _original;
      }
      virtual const Filename& imploded() const override {
        return _imploded;
      }
      virtual const Filename& exploded() const override {
        return _exploded;
      }

      virtual Filename originalDir() const override {
        return _original + "Dir";
      }
      virtual Filename implodedDir() const override {
        return _imploded + "Dir";
      }
      virtual Filename explodedDir() const override {
        return _exploded + "Dir";
      }

      virtual void move(const Filename& file, const Path& path) const override;
      virtual void backup(const Filename& file) const override;
      virtual void restore(const Filename& file) const override;
      virtual void setup() const override;
      virtual void unzip(const Filename&, const Path& to) const override;
      virtual void implode() const override;
      virtual void explode() const override {}
      virtual void rezip(const Filename&, const Path& from) const override;
      virtual void reset() const override;
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
