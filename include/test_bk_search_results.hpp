// Test class for word search

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include "bktree.hpp"


/// Test class to check search words in bk tree
class TestBKTreeWordMatches
{
public:
    /// Constructor
    TestBKTreeWordMatches(std::string filename_in, bool dbg = true)
    {
        input_file = filename_in;
        debug = dbg;
        std::cerr << "\nRead \"" << filename_in << "\" and generate BK tree with file words";
        bk_tree = BKTree(filename_in, debug);
    }

    /// check word and matches
    bool test_word_search(std::string search_word, const std::vector <std::string> &word_matches)
    {
        bool test_result = true;
        std::vector <std::string> search_results;
        std::cerr << "\nFind matching words for \"" << search_word << "\"\n";
        bk_tree.find_near_words(search_word, 1, search_results);
        std::cerr << "\nSearch results are: ";
        if (search_results.size() == word_matches.size())
        {
            for (int i = 0; i < search_results.size(); ++i)
            {
                assert(search_results[i] == word_matches[i]);
                std::cerr << search_results[i] << " ";
                // Test result does not match test data
                if (search_results[i] != word_matches[i])
                {
                    test_result = false;
                }
            }
            return test_result;
        }
        return false;
    }

private:
    BKTree bk_tree;
    std::string input_file;
    bool debug;
};
