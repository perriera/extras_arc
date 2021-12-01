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

#include <extras_arc/parcel/Parcel.hpp>
#include <extras_arc/parcel/Wrap.hpp>
#include <extras_arc/imploder/Imploder.hpp>
#include <extras/filesystem/system.hpp>
#include <extras/filesystem/files.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace arc {

        /**
         * @brief wrap()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::wrap(const Filename& filename) const {
            ng::Imploder arc(filename);
            arc.implode();
            arc::Parcel parcel(arc.imploded());
            parcel.pack();
            return parcel.packed();
        }

        Filename ParcelImploder::wrapped(const Filename& filename) const {
            ng::Imploder arc(filename);
            arc::Parcel parcel(arc.imploded());
            return parcel.packed();
        }

        /**
         * @brief unWrap()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::unWrap(const Filename& filename) const {
            ng::Imploder arc(filename);
            arc::Parcel parcel(arc.imploded());
            parcel.unpack();
            parcel.merge();
            parcel.clean();
            if (fs::exists(arc.original())) {
                arc.explode();
                return arc.exploded();
            }
            return parcel.original();
        }

        Filename ParcelImploder::unWrapped(const Filename& filename) const {
            ng::Imploder arc(filename);
            arc::Parcel parcel(arc.imploded());
            return arc.exploded();
        }

        /**
         * @brief merge()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::merge(const Filename& filename) const {
            ng::Imploder arc(filename);
            if (fs::exists(arc.original())) {
                arc.merge();
                return filename;
            }
            FileNotFoundException::assertion(arc.imploded(), __INFO__);
            auto a = arc.imploded();
            auto b = arc.original();
            auto cmd = "mv " + a + " " + b;
            SystemException::assertion(cmd, __INFO__);
            arc.clean();
            return filename;
        }

        /**
         * @brief clean()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::clean(const Filename& filename) const {
            ng::Imploder arc(filename);
            arc::Parcel parcel(arc.imploded());
            parcel.clean();
            arc.clean();
            return filename;
        }


    }
}
