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
#include <extras_arc/zipper.hpp>
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
        void Zipper::unzip(const Filename& zipFile, const Path& to) const {
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
        void Zipper::rezip(const Filename& filename, const Path& from) const {
            FileNotFoundException::assertion(filename, __INFO__);
            PathNotFoundException::assertion(from, __INFO__);
            auto script = filename + ".sh";
            std::ofstream ss(script);
            ss << "cp " + filename << ' ' << filename << std::endl;
            ss << "cd " + from << std::endl;
            fs::path p = filename;
            std::string fn = p.filename();
            ss << "zip -r ../" + fn + " . " << ">/dev/null" << std::endl;
            ss.close();
            ScriptException::assertion(script.c_str(), __INFO__);
        }

        /**
         * @brief zipit
         *
         */
        void Zipper::zipit(const Filename& filename, const Path& from) const {
            PathNotFoundException::assertion(from, __INFO__);
            auto script = "/tmp/script.sh";
            std::ofstream ss(script);
            ss << "cd " + from << std::endl;
            string tempFile = "/tmp/temp.zip";
            if (fs::exists(tempFile))
                fs::remove(tempFile);
            ss << "zip -r " << tempFile << " . " << ">/dev/null" << std::endl;
            fs::path p = filename;
            ss << "cp " << tempFile << " " << fs::absolute(p) << ">/dev/null" << std::endl;
            ss << "rm " << tempFile << ">/dev/null" << std::endl;
            ss.close();
            ScriptException::assertion(script, __INFO__);
        }

        /**
         * @brief update
         *
         */
        void Zipper::update(const Filename& filename, const Path& from) const {
            PathNotFoundException::assertion(from, __INFO__);
            FileNotFoundException::assertion(filename, __INFO__);
            std::string tempDir = std::tmpnam(nullptr);
            tempDir += ".dir";
            std::string zipSrcTempDir = tempDir + "/src/";
            auto unzip = "unzip -o " + filename + " -d " + tempDir + " >/dev/null";
            SystemException::assertion(unzip.c_str(), __INFO__);
            for (auto& p : fs::recursive_directory_iterator(from))
                if (!p.is_directory()) {
                    // auto script = original() + ".sh";
                    std::string pathA = p.path();
                    std::string fn = p.path().filename();
                    std::string pathB = extras::replace_all(pathA, fn, "");
                    std::string subDir = extras::replace_all(pathB, from + "/", "");
                    std::string pathC = zipSrcTempDir + subDir + fn;
                    auto cpCmd = "cp  " + pathC + " " + pathA + " >/dev/null";
                    SystemException::assertion(cpCmd.c_str(), __INFO__);
                }
            auto rmDir = "rm -rf " + tempDir + " >/dev/null";
            SystemException::assertion(rmDir.c_str(), __INFO__);
        }

        /**
         * @brief update
         *
         */
        void Zipper::append(const Filename& filename, const Path& from) const {
            PathNotFoundException::assertion(from, __INFO__);
            FileNotFoundException::assertion(filename, __INFO__);
            std::string tempDir = std::tmpnam(nullptr);
            tempDir += ".dir";
            std::string zipSrcTempDir = tempDir + "/src/";
            auto unzip = "unzip -o " + filename + " -d " + tempDir + " >/dev/null";
            SystemException::assertion(unzip.c_str(), __INFO__);
            for (auto& p : fs::recursive_directory_iterator(tempDir))
                if (!p.is_directory()) {
                    // auto script = original() + ".sh";
                    std::string pathA = p.path();
                    std::string fn = p.path().filename();
                    std::string pathB = extras::replace_all(pathA, fn, "");
                    std::string subDir = extras::replace_all(pathB, zipSrcTempDir, "/");
                    std::string pathC = from + subDir + fn;
                    auto cpCmd = "rsync -a " + pathA + " " + pathC + " >/dev/null";
                    SystemException::assertion(cpCmd.c_str(), __INFO__);
                }
            auto rmDir = "rm -rf " + tempDir + " >/dev/null";
            SystemException::assertion(rmDir.c_str(), __INFO__);
        }


        void Zipper::help() const {
            FileNotFoundException::assertion("HOWTO-implode.md", __INFO__);
            string cmd = "cat HOWTO-implode.md | less ";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

        void ZipperCmdLine::diagnostics(std::string msg) const {
            // if (msg.size() > 0)
            //     std::cout << msg << std::endl;
            // auto cmd = "ls -la " + original() + "*";
            // extras::SystemException::assertion(cmd, __INFO__);
        }

    }
}


