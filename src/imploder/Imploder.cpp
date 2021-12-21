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

#include <iostream>
#include <extras_arc/imploder.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/files.hpp>
#include <extras/filesystem/system.hpp>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

namespace extras {
    namespace arc {

        /**
         * @brief unzip
         *
         * @param zipFile
         * @param to
         */
        void Imploder::unzip(const Filename& zipFile, const Path& to) const {
            FileNotFoundException::assertion(zipFile, __INFO__);
            auto unzip = "unzip -o " + zipFile + " -d " + to + " >/dev/null";
            SystemException::assertion(unzip.c_str(), __INFO__);
        }

        /**
         * @brief rezip()
         *
         * @param filename
         * @param from
         */
        void Imploder::rezip(const Filename& filename, const Path& from) const {
            FileNotFoundException::assertion(original(), __INFO__);
            PathNotFoundException::assertion(from, __INFO__);
            auto script = original() + ".sh";
            std::ofstream ss(script);
            ss << "cp " + original() << ' ' << filename << std::endl;
            ss << "cd " + from << std::endl;
            fs::path p = filename;
            std::string fn = p.filename();
            ss << "zip -r ../" + fn + " . " << ">/dev/null" << std::endl;
            ss.close();
            ScriptException::assertion(script.c_str(), __INFO__);
        }

        /**
         * @brief implode
         *
         */
        void Imploder::implode() const {
            FileNotFoundException::assertion(original(), __INFO__);
            unzip(original(), original() + ".dir");
            for (auto& p : fs::recursive_directory_iterator(original() + ".dir"))
                if (!p.is_directory() && isImplodable(p.path())) {
                    auto script = original() + ".sh";
                    std::string file = p.path();
                    std::ofstream ss(script);
                    ss << "echo *imploded* > " + file << std::endl;
                    ss.close();
                    ScriptException::assertion(script.c_str(), __INFO__);
                }
            rezip(imploded(), original() + ".dir");
            rmdir(original() + ".dir");
            diagnostics("");
        }

        /**
         * @brief isImplodable()
         *
         * @param filename
         * @return true
         * @return false
         */
        bool Imploder::isImplodable(const Filename& filename) const {
            string lp = to_lower(filename);
            bool _isImage = ends_with(lp, ".png") || ends_with(lp, ".jpg") ||
                ends_with(lp, ".jpeg") || ends_with(lp, ".bmp") ||
                ends_with(lp, ".raw") || ends_with(lp, ".pdf") ||
                ends_with(lp, ".gif") || ends_with(lp, ".psd") ||
                ends_with(lp, ".eps") || ends_with(lp, ".ai") ||
                ends_with(lp, ".indd") || ends_with(lp, ".tiff")
                || ends_with(lp, ".svg");
            return _isImage;
        }

        /**
         * @brief explode()
         *
         */
        void Imploder::explode() const {
            FileNotFoundException::assertion(imploded(), __INFO__);
            auto cp = "cp " + imploded() + " " + exploded();
            SystemException::assertion(cp.c_str(), __INFO__);
            unzip(exploded(), exploded() + ".dir");
            unzip(original(), original() + ".dir");
            for (auto& p : fs::recursive_directory_iterator(exploded() + ".dir"))
                if (!p.is_directory() && isImplodable(p.path())) {
                    auto script = original() + ".sh";
                    std::string to = p.path();
                    std::string from = extras::replace_all(to, "_exploded.zip", "");
                    std::ofstream ss(script);
                    ss << "cp " + from << " " + to << std::endl;
                    ss.close();
                    ScriptException::assertion(script.c_str(), __INFO__);
                }
            rezip(exploded(), exploded() + ".dir");
            rmdir(exploded() + ".dir");
            rmdir(original() + ".dir");
            diagnostics("");
        }

        /**
         * @brief rm/rmdir
         *
         * @param to
         */
        void Imploder::rm(const Filename& to) const {
            if (fs::exists(to))
                fs::remove(to);
        }

        void Imploder::rmdir(const Path& to) const {
            if (fs::exists(to))
                fs::remove_all(to);
        }

        void Imploder::merge() const {
            FileNotFoundException::assertion(exploded(), __INFO__);
            if (fs::exists(original()))
                fs::remove(original());
            fs::copy_file(exploded(), original());
            fs::remove(exploded());
            clean();
        }

        void Imploder::clean() const {
            fs::remove(imploded());
            fs::remove(exploded());
            rmdir(exploded() + ".dir");
            rmdir(original() + ".dir");
            diagnostics("");
        }

        void Imploder::help() const {
            FileNotFoundException::assertion("HOWTO-implode.md", __INFO__);
            string cmd = "cat HOWTO-implode.md | less ";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

        void ImploderCmdLine::diagnostics(std::string msg) const {
            if (msg.size() > 0)
                std::cout << msg << std::endl;
            auto cmd = "ls -la " + original() + "*";
            extras::SystemException::assertion(cmd, __INFO__);
        }

    }
}


