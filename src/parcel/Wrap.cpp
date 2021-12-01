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

#include <ng_imploder/parcel/Parcel.hpp>
#include <ng_imploder/parcel/Wrap.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/filesystem/system.hpp>
#include <extras/filesystem/files.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace imploder {

        /**
         * @brief wrap()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::wrap(const Filename& filename) const {
            ng::Imploder imploder(filename);
            imploder.implode();
            imploder::Parcel parcel(imploder.imploded());
            parcel.pack();
            return parcel.packed();
        }

        Filename ParcelImploder::wrapped(const Filename& filename) const {
            ng::Imploder imploder(filename);
            imploder::Parcel parcel(imploder.imploded());
            return parcel.packed();
        }

        /**
         * @brief unWrap()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::unWrap(const Filename& filename) const {
            ng::Imploder imploder(filename);
            imploder::Parcel parcel(imploder.imploded());
            parcel.unpack();
            parcel.merge();
            parcel.clean();
            if (fs::exists(imploder.original())) {
                imploder.explode();
                return imploder.exploded();
            }
            return parcel.original();
        }

        Filename ParcelImploder::unWrapped(const Filename& filename) const {
            ng::Imploder imploder(filename);
            imploder::Parcel parcel(imploder.imploded());
            return imploder.exploded();
        }

        /**
         * @brief merge()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::merge(const Filename& filename) const {
            ng::Imploder imploder(filename);
            if (fs::exists(imploder.original())) {
                imploder.merge();
                return filename;
            }
            FileNotFoundException::assertion(imploder.imploded(), __INFO__);
            auto a = imploder.imploded();
            auto b = imploder.original();
            auto cmd = "mv " + a + " " + b;
            SystemException::assertion(cmd, __INFO__);
            imploder.clean();
            return filename;
        }

        /**
         * @brief clean()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::clean(const Filename& filename) const {
            ng::Imploder imploder(filename);
            imploder::Parcel parcel(imploder.imploded());
            parcel.clean();
            imploder.clean();
            return filename;
        }


    }
}
