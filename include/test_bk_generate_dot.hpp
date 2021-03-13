// Test class for generating a dot file

#pragma once

#include <iostream>
#include "bktree.hpp"

/// Test class which reads a bk tree and creates a dot file
class TestBKTreeGenerateDot
{
public:
    /// Constructor which creates a dot file
    TestBKTreeGenerateDot(std::string filename_in, std::string filename_dot, bool dbg = true)
    {
        input_file = filename_in;
        dot_file = filename_dot;
        debug = dbg;
        std::cerr << "\nRead \"" << filename_in << "\" and generate BK tree with file words\n";
        BKTree bk(filename_in, debug);
        std::cerr << "\nGenerate dot file: \"" << filename_dot << "\"\n";
        bk.generate_dot_file(filename_dot);
    }

private:
    std::string input_file;
    std::string dot_file;
    bool debug;
};
