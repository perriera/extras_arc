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

#include <extras_arc/parcel.hpp>
#include <extras_arc/wrap.hpp>
#include <extras_arc/imploder.hpp>
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
        Filename ParcelImploder::wrap() const {
            arc::Imploder arc(original());
            arc.implode();
            arc::Parcel parcel(arc.imploded());
            parcel.pack();
            return parcel.packed();
        }

        Filename ParcelImploder::wrapped() const {
            arc::Imploder arc(original());
            arc::Parcel parcel(arc.imploded());
            return parcel.packed();
        }

        /**
         * @brief unWrap()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::unWrap() const {
            arc::Imploder arc(original());
            arc::Parcel parcel(arc.imploded());
            parcel.unpack();
            parcel.merge();
            parcel.clean();
            if (fs::exists(arc.original())) {
                arc.explode();
                return arc.exploded();
            }
            return  arc.imploded();;
        }

        Filename ParcelImploder::unWrapped() const {
            arc::Imploder arc(original());
            arc::Parcel parcel(arc.imploded());
            if (fs::exists(arc.original()))
                return arc.exploded();
            else
                return arc.imploded();
        }

        /**
         * @brief merge()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::merge() const {
            arc::Imploder arc(original());
            if (fs::exists(arc.original())) {
                arc.merge();
                return original();
            }
            FileNotFoundException::assertion(arc.imploded(), __INFO__);
            auto a = arc.imploded();
            auto b = arc.original();
            auto cmd = "mv " + a + " " + b;
            SystemException::assertion(cmd, __INFO__);
            arc.clean();
            return original();
        }

        /**
         * @brief clean()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::clean() const {
            arc::Imploder arc(original());
            arc::Parcel parcel(arc.imploded());
            parcel.clean();
            arc.clean();
            return original();
        }

        void ParcelImploder::help() const {
            FileNotFoundException::assertion("HOWTO-wrap.md", __INFO__);
            string cmd = "cat HOWTO-wrap.md | less ";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

        void ParcelImploderCmdLine::diagnostics(std::string msg) const {
            if (msg.size() > 0)
                std::cout << msg << std::endl;
            auto cmd = "ls -la " + original() + "*";
            extras::SystemException::assertion(cmd, __INFO__);
        }

    }
}
