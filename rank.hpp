// rank.hpp - Formula (factorial) based rank / unrank of a word
#pragma once
#include <algorithm>
#include <map>
#include <stdexcept>
#include <string>

typedef unsigned long long ull;

inline ull fact(int n) {
    if (n < 0 || n > 20) throw std::out_of_range("factorial supports 0..20");
    ull r = 1;
    for (int i = 2; i <= n; i++) r *= i;
    return r;
}

// Number of distinct arrangements of the letters in cnt: n! / (c1! * c2! * ...)
inline ull permCount(const std::map<char, int>& cnt) {
    int n = 0;
    ull d = 1;
    for (const auto& p : cnt) {
        n += p.second;
        d *= fact(p.second);
    }
    return fact(n) / d;
}

// Rank of a word among all its distinct arrangements (1-based, dictionary order)
inline ull rankOfWord(const std::string& w) {
    std::map<char, int> cnt;
    for (char c : w) cnt[c]++;
    ull rank = 1;
    for (size_t i = 0; i < w.size(); i++) {
        for (auto& p : cnt) {
            if (p.first >= w[i]) break;
            if (p.second == 0) continue;
            p.second--;                // is letter ko pehle rakho
            rank += permCount(cnt);    // to itne words chhote honge
            p.second++;
        }
        cnt[w[i]]--;
    }
    return rank;
}

// Reverse: given letters and a rank k, return the k-th word
inline std::string wordAtRank(const std::string& letters, ull k) {
    std::map<char, int> cnt;
    for (char c : letters) cnt[c]++;
    if (k < 1 || k > permCount(cnt)) throw std::out_of_range("rank out of range");
    std::string res;
    for (size_t i = 0; i < letters.size(); i++) {
        for (auto& p : cnt) {
            if (p.second == 0) continue;
            p.second--;
            ull c = permCount(cnt);
            if (k <= c) { res += p.first; break; }
            k -= c;
            p.second++;
        }
    }
    return res;
}
