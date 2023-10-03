#include "MapParser.hpp"
#include <fstream>

namespace game {
    MapParser::MapParser(const std::string& filepath)
        : _map()
    {
        parse(filepath);
    }

    bool MapParser::isExist(const std::string& key) const {
        return _map.count(key);
    }

    std::string MapParser::getAsString(const std::string& key, const char* defaultValue) const {
        if (isExist(key)) {
            return _map.at(key);
        }
        return defaultValue;
    }

    int MapParser::getAsInteger(const std::string& key, int defaultValue) const {
        std::string value = getAsString(key);
        if (value == "") {
            return defaultValue;
        }
        return std::stoi(value);
    }

    float MapParser::getAsFloat(const std::string& key, float defaultValue) const {
        std::string value = getAsString(key);
        if (value == "") {
            return defaultValue;
        }
        return std::stof(value);
    }

    void MapParser::eraseSpace(std::string& line) {
        std::string::const_iterator read = line.begin();// 読み込み位置
        std::string::iterator push = line.begin();// 追加位置

        while (read != line.end()) {
            if (std::isspace(*read)) {
                ++read;
            }
            else {
                // 空白文字以外を追加
                *push = *read;
                ++push;
                ++read;
            }
        }
        // サイズを文字数に合わせる
        line.resize(push - line.begin());
        line.shrink_to_fit();
    }

    std::vector<std::string> MapParser::split(const std::string& str, char delim) {
        std::string::const_iterator read = str.begin();
        std::vector<std::string> result;
        std::string word = "";

        while (read != str.end()) {
            if (*read == delim) {
                result.push_back(word);
                word = "";
            }
            else {
                word.push_back(*read);
            }
            ++read;
        }
        // 余分に追加しないようにチェック
        if (word != "") {
            result.push_back(word);
        }
        return result;
    }

    void MapParser::parse(const std::string& filepath) {
        std::ifstream in(filepath);
        if (!in.is_open()) { throw std::invalid_argument("not exist map file"); }

        std::ofstream out("TEST.txt");

        std::string line;
        while (std::getline(in, line)) {
            // 空白の削除
            eraseSpace(line);
            
            auto words = split(line, '=');
            out << words[0] << ":" << words[1] << std::endl;
            // 追加
            _map[words[0]] = words[1];
        }

        in.close();
    }


}
