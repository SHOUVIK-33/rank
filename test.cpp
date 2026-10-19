#include <cassert>
#include <iostream>
#include "../src/database.hpp"
#include "../src/rank.hpp"

int main() {
    assert(rankOfWord("abcd") == 1);
    assert(rankOfWord("dcba") == 24);
    assert(rankOfWord("bacd") == 7);
    assert(wordAtRank("abcd", 7) == "bacd");

    // formula vs database, every word of each set (includes repeated letters)
    for (std::string s : {"aabcd", "abcde", "abcdef"}) {
        assert(WordDatabase::build(s, "data_test"));
        WordDatabase db;
        assert(db.load(s, "data_test"));
        for (ull k = 1; k <= db.size(); k++) {
            assert(rankOfWord(db.wordAt(k)) == k);
            assert(wordAtRank(s, k) == db.wordAt(k));
        }
    }
    std::cout << "ALL TESTS PASSED\n";
    return 0;
}
