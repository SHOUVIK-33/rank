// database.hpp - Simple file database: stores all arrangements serially
// File format (data/<sortedletters>.db):  "<rank> <word>" one per line
#pragma once
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "rank.hpp"

class WordDatabase {
public:
    static const size_t MAX_LEN = 9;  // 9! = 362880 lines max

    static std::string keyOf(std::string s) {
        std::sort(s.begin(), s.end());
        return s;
    }

    static std::string pathFor(const std::string& letters, const std::string& dir) {
        return dir + "/" + keyOf(letters) + ".db";
    }

    // Create database file with all arrangements in serial (sorted) order
    static bool build(const std::string& letters, const std::string& dir = "data") {
        if (letters.empty() || letters.size() > MAX_LEN) return false;
        std::filesystem::create_directories(dir);
        std::string w = keyOf(letters);
        std::ofstream out(pathFor(letters, dir));
        if (!out) return false;
        ull r = 1;
        do {
            out << r++ << ' ' << w << '\n';
        } while (std::next_permutation(w.begin(), w.end()));
        return true;
    }

    bool load(const std::string& letters, const std::string& dir = "data") {
        std::ifstream in(pathFor(letters, dir));
        if (!in) return false;
        words_.clear();
        index_.clear();
        ull r;
        std::string w;
        while (in >> r >> w) {
            words_.push_back(w);
            index_[w] = r;
        }
        return !words_.empty();
    }

    // returns 0 if word not found
    ull rankOf(const std::string& w) const {
        auto it = index_.find(w);
        return it == index_.end() ? 0 : it->second;
    }

    std::string wordAt(ull k) const {
        if (k < 1 || k > words_.size()) return "";
        return words_[k - 1];
    }

    size_t size() const { return words_.size(); }

private:
    std::vector<std::string> words_;
    std::unordered_map<std::string, ull> index_;
};
