// Perform tests for bk tree class

#include <iostream>
#include <vector>
#include "../include/test_bk_generate_dot.hpp"
#include "../include/test_bk_double_input.hpp"
#include "../include/test_bk_search_results.hpp"
#include "../include/helper.hpp"


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "USAGE: test-bk-1 TEXTFILE [< TESTPATHES]\n";
        std::cerr << "TEXTINFILE is a ISO-encoded textfile with a single token per line.\n";
        std::cerr << "TODO – After bk tree construction, the words in TESTWORDSINFILE are being looked up.\n";
        exit(1);
    }
    bool debug = true;

    // Vector for test paths
    std::vector <std::string> pathes;

    // Read file path from command line
    std::string test_file_pathes = std::string(argv[1]);
    read_file_into_vector(test_file_pathes, pathes);

    // Read paths to text files
    std::string textfile_word_input = pathes[0];
    std::string textfile_dot_output = pathes[1];
    std::string textfile_double_word_input = pathes[2];
    std::string textfile_search_words = pathes[3];
    std::string textfile_word_matches = pathes[4];

    /// Test simple read of a file and generation of a dot file
    TestBKTreeGenerateDot(textfile_word_input, textfile_dot_output);
    /// Test input of double words
    TestBKTreeDoubleInput(textfile_double_word_input, debug);

    /// Test prepared inputs for word matches
    std::vector <std::string> search_words;
    read_file_into_vector(textfile_search_words, search_words);
    std::vector <std::string> control_words;
    read_file_into_vector(textfile_word_matches, control_words);
    TestBKTreeWordMatches test_word_matches(textfile_word_input);
    bool test_wm_result = test_word_matches.test_word_search(search_words[0], control_words);
    assert (test_wm_result);

    std::cerr << "\nTests finished\n"
              << "\n=============================\n";
}
