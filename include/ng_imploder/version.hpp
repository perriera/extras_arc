#ifndef _NG_IMPLODER_VERSION_HPP
#define _NG_IMPLODER_VERSION_HPP

/**
 * @file version.hpp
 * @author Matt Williams (matt@perriera.com)
 * @author Perry Anderson (perry@perriera.com)
 * @brief Adds version support for Cmake script
 * @date 2021-08-08
 */

#define NG_IMPLODER_VER_MAJOR 0
#define NG_IMPLODER_VER_MINOR 4
#define NG_IMPLODER_VER_PATCH 1

#define NG_IMPLODER_VERSION \
  (NG_IMPLODER_VER_MAJOR * 10000 + NG_IMPLODER_VER_MINOR * 100 + NG_IMPLODER_VER_PATCH)

#endif// _NG_IMPLODER_VERSION_HPP
