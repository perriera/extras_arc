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

#include <extras_arc/bin2hex/ConvertFile.hpp>
#include <extras_arc/parcel.hpp>
#include <extras_arc/exceptions.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace arc {

        /**
         * @brief Parcel::pack()
         *
         */
        void Parcel::pack() const {
            FileNotFoundException::assertion(original(), __INFO__);
            std::ifstream inBin(original());
            std::ofstream outHex(hexed());
            arc::HexFile hexFile = arc::ConvertFile().convertToHex(inBin, outHex);
            arc::PackedFile packedFile;
            int cnt = 0;
            for (auto hexLine : hexFile) {
                arc::ParcelLine packedLine(++cnt, hexFile.size(), hexLine);
                packedFile.push_back(packedLine);
            }
            std::ofstream outPacked(packed());
            for (auto packedLine : packedFile)
                outPacked << packedLine << std::endl;
            outPacked.close();
            FileNotFoundException::assertion(packed(), __INFO__);
            diagnostics("");
        }

        /**
         * @brief  Parcel::unpack()
         *
         */
        void Parcel::unpack() const {
            auto name = packed();
            FileNotFoundException::assertion(name, __INFO__);
            std::ifstream in(name);

            arc::HexFile hexFile;
            arc::PackedFile badCRC;

            arc::HexFile buffer;
            while (in.good()) {
                arc::HexLine line;
                getline(in, line);
                if (line == "JUNK")
                    break;
                if (line.size() > 0)
                    buffer.push_back(line);
            }

            for (auto text : buffer) {
                std::stringstream ss;
                ss << text;
                arc::ParcelLine line;
                try {
                    ss >> line;
                    hexFile.push_back(line.hexLine());
                    if (line.eof())
                        break;
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                    cout << line << endl;
                    badCRC.push_back(line);
                }
            }

            if (badCRC.size() > 0)
                cout << "BadCRC count: " << badCRC.size() << endl;
            std::ofstream outHex(hexed());
            arc::ConvertFile().saveHex(outHex, hexFile);
            outHex.close();
            std::ifstream inHex(hexed());
            std::ofstream outBin(duplicate());
            arc::ConvertFile().convertToBin(inHex, outBin);
            outBin.close();
            FileNotFoundException::assertion(duplicate(), __INFO__);
            diagnostics("");
        }

        /**
         * @brief Parcel::verify_integrity()
         *
         * @return true
         * @return false
         */
        bool Parcel::verify_integrity() const {
            FileNotFoundException::assertion(original(), __INFO__);
            FileNotFoundException::assertion(duplicate(), __INFO__);
            arc::ParcelException::assertion(original(), duplicate(), __INFO__);
            diagnostics("No differences detected");
            return true;
        }

        /**
         * @brief Parcel::merge()
         *
         */
        void Parcel::merge() const {
            FileNotFoundException::assertion(duplicate(), __INFO__);
            auto from = duplicate();
            auto to = original();
            auto cmd = "cp " + from + " " + to;
            extras::SystemException::assertion(cmd, __INFO__);
            fs::remove(from);
            diagnostics("");
        }

        /**
         * @brief Parcel::clean()
         *
         */
        void Parcel::clean() const {
            if (fs::exists(packed()))
                fs::remove(packed());
            if (fs::exists(hexed()))
                fs::remove(hexed());
            if (fs::exists(duplicate()))
                fs::remove(duplicate());
            diagnostics("");
        }

        /**
         * @brief Parcel::cat()
         *
         */
        void Parcel::cat() const {
            FileNotFoundException::assertion(packed(), __INFO__);
            std::string cmd = "cat " + packed() + " | less";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

        /**
         * @brief Parcel::dir()
         *
         */
        void Parcel::dir() const {
            std::string cmd = "ls -la " + original() + "*";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

        /**
         * @brief Parcel::unzip()
         *
         */
        void Parcel::unzip() const {
            FileNotFoundException::assertion(duplicate(), __INFO__);
            string cmd = "unzip -o " + duplicate() + " -d /tmp ";
            SystemException::assertion(cmd.c_str(), __INFO__);
            diagnostics("");
        }

        /**
         * @brief Parcel::help()
         *
         */
        void Parcel::help() const {
            FileNotFoundException::assertion("HOWTO-parcel.md", __INFO__);
            string cmd = "cat HOWTO-parcel.md | less ";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

        /**
         * @brief Parcel::diagnostics()
         *
         */
        void ParcelCmdLine::diagnostics(std::string msg) const {
            if (msg.size() > 0)
                std::cout << msg << std::endl;
            auto cmd = "ls -la " + original() + "*";
            extras::SystemException::assertion(cmd, __INFO__);
        }

    }  // namespace arc
}  // namespace extras
