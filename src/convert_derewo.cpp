// Reads a DeReWo List and saves all word forms

#include <string>
#include "../include/helper.hpp"

int main(int argc, char** argv)
{
    // Check number of command line arguments
    if (argc != 3) {
        std::cerr << "USAGE: convert_derewo TEXTINFILE [< TESTINPATHES] TEXTOUTFILE [< TEXTOUTPATHES]\n";
        std::cerr << "TEXTINFILE is a ISO-encoded textfile with a single token per line.\n";
        std::cerr << "Writes all word forms of a derewo file into an outputfile, which the BK tree can read.\n";
        exit(1);
    }

    // Read file paths from command line arguments
    std::string in_filename = std::string(argv[1]);
    std::string out_filename = std::string(argv[2]);
    // Read DeReWo file and word form file to create a bk tree
    convert_derewo(in_filename, out_filename);
}
