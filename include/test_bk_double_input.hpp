// Test class for multiple input of a word list

#pragma once

#include <iostream>
#include "bktree.hpp"
#include <cassert>


/// Tests input of a small tree with multiple input of the same word.
/// The tree must contain two nodes at the end and one transition.
class TestBKTreeDoubleInput
{
public:
    /// Constructor for test class:
    /// test file should contain words that creates a tree of two words and a transition. 
    /// The words should be present more than once in file.
    TestBKTreeDoubleInput(std::string filename_in, bool dbg = true)
    {
        input_file = filename_in;
        debug = dbg;
        std::cerr << "\nRead \"" << filename_in << "\" and generate BK tree with file words";
        BKTree bk(filename_in, debug);
        std::cerr << "\nShow dot out put\n";
        bk.show_dot_output();
        std::cerr << "\nAssert Anzahl Wörter und Übergänge";
        assert(bk.number_nodes() == 2);
        assert(bk.number_transitions() == 1);
        assert(bk.number_words() == 2);
        assert(bk.height() == 1);
    }

private:
    std::string input_file;
    bool debug;
};
