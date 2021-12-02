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
#include <extras_arc/parcel/Parcel.hpp>
#include <extras_arc/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace arc {

        std::ostream& operator<<(std::ostream& out, const ParcelLine& obj) {
            out << " : " << std::hex << obj.lineNo();
            out << " / " << std::hex << obj.lineCount();
            out << " : " << obj.hexLine();
            out << " : " << std::hex << obj.checksum();
            return out;
        }

        std::istream& operator>>(std::istream& in, ParcelLine& obj) {
            std::string line;
            getline(in, line);
            if (line.length() == 0)
                return in;
            stringstream ss;
            ss << line;
            char c;
            ss >> std::skipws >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._lineNo;
            ParcelException::assertion(obj._lineNo, __INFO__);
            ss >> std::skipws >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._lineCount;
            ParcelException::assertion(obj._lineCount, __INFO__);
            ss >> std::skipws >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> obj._hexLine;
            ParcelException::assertion(obj._hexLine, __INFO__);
            ss >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._crc;
            ParcelException::assertion(obj._crc, obj._hexLine, __INFO__);
            return in;
        }

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
        }

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

        }

        bool Parcel::verify_integrity() const {
            FileNotFoundException::assertion(original(), __INFO__);
            FileNotFoundException::assertion(duplicate(), __INFO__);
            arc::ParcelException::assertion(original(), duplicate(), __INFO__);
            return true;
        }

        void Parcel::merge() const {
            FileNotFoundException::assertion(duplicate(), __INFO__);
            auto from = duplicate();
            auto to = original();
            auto cmd = "cp " + from + " " + to;
            extras::SystemException::assertion(cmd, __INFO__);
            fs::remove(from);
        }

        void Parcel::clean() const {
            if (fs::exists(packed()))
                fs::remove(packed());
            if (fs::exists(hexed()))
                fs::remove(hexed());
            if (fs::exists(duplicate()))
                fs::remove(duplicate());
        }

        void Parcel::cat() const {
            FileNotFoundException::assertion(packed(), __INFO__);
            std::string cmd = "cat " + packed();
            system(cmd.c_str());
        }

        void Parcel::dir() const {
            std::string cmd = "ls -la " + original() + "*";
            system(cmd.c_str());
        }

        void Parcel::unzip() const {
            FileNotFoundException::assertion(duplicate(), __INFO__);
            string cmd = "unzip -o " + duplicate() + " -d /tmp ";
            system(cmd.c_str());
        }


    }  // namespace arc
}  // namespace extras
