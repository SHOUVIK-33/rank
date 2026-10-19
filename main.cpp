#include <iostream>
#include <string>
#include "database.hpp"
#include "rank.hpp"

static std::string readWord(const char* prompt) {
    std::string s;
    std::cout << prompt;
    std::cin >> s;
    for (auto& c : s) c = std::tolower((unsigned char)c);
    return s;
}

int main() {
    WordDatabase db;
    while (true) {
        std::cout << "\n===== WORD RANK PROJECT =====\n"
                  << "1. Rank nikalo (formula)\n"
                  << "2. Database banao (saare arrangements serially)\n"
                  << "3. Rank nikalo (database se)\n"
                  << "4. Rank se word nikalo\n"
                  << "5. Verify: formula vs database\n"
                  << "0. Exit\n"
                  << "Choice: ";
        int ch;
        if (!(std::cin >> ch) || ch == 0) break;
        try {
            if (ch == 1) {
                std::string w = readWord("Word: ");
                std::cout << "Rank of " << w << " = " << rankOfWord(w) << "\n";
            } else if (ch == 2) {
                std::string w = readWord("Letters (max 9): ");
                if (WordDatabase::build(w))
                    std::cout << "Database ban gaya: " << WordDatabase::pathFor(w, "data") << "\n";
                else
                    std::cout << "Database nahi bana (length 1-9 rakho)\n";
            } else if (ch == 3) {
                std::string w = readWord("Word: ");
                if (!db.load(w)) { std::cout << "Pehle option 2 se database banao.\n"; continue; }
                ull r = db.rankOf(w);
                std::cout << "Rank of " << w << " = " << r << " (database se)\n";
            } else if (ch == 4) {
                std::string w = readWord("Letters: ");
                ull k;
                std::cout << "Rank: ";
                std::cin >> k;
                std::cout << "Word at rank " << k << " = " << wordAtRank(w, k) << "\n";
            } else if (ch == 5) {
                std::string w = readWord("Letters (max 9): ");
                WordDatabase::build(w);
                if (!db.load(w)) { std::cout << "Load fail\n"; continue; }
                bool ok = true;
                for (ull k = 1; k <= db.size(); k++)
                    if (rankOfWord(db.wordAt(k)) != k) { ok = false; break; }
                std::cout << (ok ? "PASS: dono methods same hain (" : "FAIL (")
                          << db.size() << " words)\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
