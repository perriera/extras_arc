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

    interface ImploderInterface {
      virtual const Filename& tempDir() const pure;
      virtual const Filename& before() const pure;
      virtual const Filename& after() const pure;
      virtual void unzip() const pure;
      virtual void implode() const pure;
      virtual void explode() const pure;
      virtual void rezip() const pure;
    };

    /**
     * @brief class Imploder
     *
     */

    concrete class Imploder implements ImploderInterface {
      Filename _tempDir = "/tmp/tempDir";
      Filename _before;
      Filename _after;

    public:
      Imploder(const Filename& before) : _before(before), _after(before + "_imploded") {}
      virtual const Filename& tempDir() const override {
        return _tempDir;
      }
      virtual const Filename& before() const override {
        return _before;
      }
      virtual const Filename& after() const override {
        return _after;
      }
      virtual void unzip() const override;
      virtual void implode() const override {}
      virtual void explode() const override {}
      virtual void rezip() const override {}
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
