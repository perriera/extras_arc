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
#include <extras/filesystem/filesystem.hpp>
#include <filesystem>
#include <fstream>
#include <stdlib.h>
#include <string.h>

namespace fs = std::filesystem;
using namespace std;

namespace extras {
    namespace arc {

        /**
         * @brief unzip
         *
         * @param zipFile()
         * @param zipDir()
         */
        void Zipper::unzip() const {
            FileNotFoundException::assertion(zipFile(), __INFO__);
            auto unzip = "unzip -o " + zipFile() + " -d " + zipDir() + " >/dev/null";
            SystemException::assertion(unzip.c_str(), __INFO__);
            diagnostics("");
        }

        /**
         * @brief rezip()
         *
         * @param zipFile()
         * @param zipDir()
         */
        void Zipper::rezip() const {
            FileNotFoundException::assertion(zipFile(), __INFO__);
            PathNotFoundException::assertion(zipDir(), __INFO__);
            auto fn1 = extras::FileSystem(zipFile()).filename();
            Pathname fn2 = extras::FileSystem(zipDir()).append(fn1);
            PathNotFoundException::assertion(fn2, __INFO__);
            auto script = "script.sh";
            std::ofstream ss(script);
            ss << "cd " + fn2 << std::endl;
            fs::path p = zipFile();
            std::string fn = p.filename();
            ss << "rm  ../" << fn << " >/dev/null" << std::endl;
            ss << "zip -r ../" << fn << " . " << ">/dev/null" << std::endl;
            ss.close();
            ScriptException::assertion(script, __INFO__);
            diagnostics("");
        }

        /**
         * @brief zipit
         *
         */
        void Zipper::create() const {
            PathNotFoundException::assertion(zipDir(), __INFO__);
            auto fn1 = extras::FileSystem(zipFile()).filename();
            Pathname fn2 = extras::FileSystem(zipDir()).append(fn1);
            PathNotFoundException::assertion(fn2, __INFO__);
            auto script2 = "/tmp/script.sh";
            std::ofstream ss(script2);
            ss << "cd " + fn2 << std::endl;
            string tempFile = "/tmp/temp.zip";
            if (fs::exists(tempFile))
                fs::remove(tempFile);
            ss << "zip -r " << tempFile << " . " << ">/dev/null" << std::endl;
            fs::path p = zipFile();
            ss << "cp " << tempFile << " " << fs::absolute(p) << " >/dev/null" << std::endl;
            ss << "rm " << tempFile << " >/dev/null" << std::endl;
            ss.close();
            ScriptException::assertion(script2, __INFO__);
            diagnostics("");
        }

        /**
         * @brief update
         *
         */
        void Zipper::append() const {
            PathNotFoundException::assertion(zipDir(), __INFO__);
            FileNotFoundException::assertion(zipFile(), __INFO__);
            auto fn1 = extras::FileSystem(zipFile()).filename();
            Pathname fn2 = extras::FileSystem(zipDir()).append(fn1);
            PathNotFoundException::assertion(fn2, __INFO__);
            char templatebuf[80];
            char* mkdirectory = mkdtemp(strcpy(templatebuf, "/tmp/mkprogXXXXXX"));
            std::string tempDir = mkdirectory;//std::tmpnam(nullptr);
            tempDir += ".dir";
            std::string zipSrcTempDir = tempDir + "/src/";
            auto unzip = "unzip -o " + zipFile() + " -d " + tempDir + " >/dev/null";
            SystemException::assertion(unzip.c_str(), __INFO__);
            for (auto& p : fs::recursive_directory_iterator(tempDir))
                if (!p.is_directory()) {
                    std::string from = p.path();
                    std::string to = extras::str::replace_first(from, tempDir, fn2);
                    auto cpCmd = "install -D " + from + " " + to + " >/dev/null";
                    SystemException::assertion(cpCmd.c_str(), __INFO__);
                }
            auto rmDir = "rm -rf " + tempDir + " >/dev/null";
            SystemException::assertion(rmDir.c_str(), __INFO__);
            diagnostics("");
        }


        void Zipper::help() const {
            FileNotFoundException::assertion("HOWTO-zipper.md", __INFO__);
            string cmd = "cat HOWTO-zipper.md | less ";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

        void ZipperCmdLine::diagnostics(std::string msg) const {
            if (msg.size() > 0)
                std::cout << msg << std::endl;
            auto cmd1 = "ls -la " + zipFile() + "*";
            extras::SystemException::assertion(cmd1, __INFO__);
            auto cmd2 = "ls -la " + zipDir() + "*";
            extras::SystemException::assertion(cmd2, __INFO__);
        }

    }
}


