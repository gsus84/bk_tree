// Interactive mode to find similar words
// Burkhard Keller tree is read from file. Creates a dot file of the tree 

#include <iostream>
#include <string>

#include "../include/bktree.hpp"


int main(int argc, char** argv)
{
    // Check number of command line arguments
    if (argc != 3) {
        std::cerr << "USAGE: BKTree TEXTFILE [< TESTPATHES] DOTFILE [< DOTFILEPATH]\n";
        std::cerr << "TEXTINFILE is a ISO-encoded textfile with a single token per line.\n";
        std::cerr << "Reads all words into a BK tree and starts an interactive modus.\n";
        exit(1);
    }
    // Read file paths from command line
    std::string textfile = std::string(argv[1]);
    std::string dotfile = std::string(argv[2]);
    // Read bk tree
    BKTree bk(textfile);
    bk.generate_dot_file(dotfile);
    std::cout << "\nGenerated a Burkard-Keller-Tree"
              << "\nGenerated a dot file for BK tree"
              << "\n=================================\n"
              << "\nTree Basic information:"
              << "\n_________________________________"
              << "\nmax height: " << bk.height()
              << "\nnumber words: " << bk.number_words()
              << "\n=================================\n";
    // Start interactive mode
    std::string word_input;
    int ldist_input = 1;
    std::string buffer;
    while (word_input != " ")
    {
        std::cout << "\nPlease enter a word: ";
        std::getline(std::cin, word_input);
        std::cout << "Please enter the number of the Levenstein distance: ";
        std::cin >> ldist_input;
        // Query wrong input for Levenshtein distance again
        while (ldist_input < 1 || ldist_input > 3 || !std::cin)
        {
            // Clean cin stream
            std::cin.clear();
            while (std::cin.get() != '\n')
                continue;
            // Ask for new input
            std::cout << "\nBad input for Levenstein distance!"
                      << "\nPlease enter a number between 1 and 3: ";
            std::cin >> ldist_input;
        }
        // Return similar words
        bk.show_near_words(word_input, ldist_input);
        std::cout << "\n_________________________________\n";
        // Clean cin stream
        while (std::cin.get() != '\n') 
        {
            continue;
        }
        std::cin.clear();
    } // while
    std::cout << "\n=================================\n"
              << "program closed"
              << "\n=================================\n";

}
