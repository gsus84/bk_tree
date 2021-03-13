// Helper classes and functions

#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>


/// Finds all word forms stored in DeReWo format and passes them to a vector
void find_word_forms(std::string derewo_in, std::vector <std::string> & word_form_list)
{
    // Vectors for token and suffixes of a DeReWo file
    std::vector <std::string> token;
    std::vector <std::string> suffixes = {""};
    int word_start = 0;
    int count_letters = -1;
    int suffix_start = derewo_in.length();
    // Find words from DeReWo file
    for (int i = 0; i < derewo_in.length(); ++i)
    {
        count_letters += 1;
        // Words are separated by a comma
        if (derewo_in[i] == ',')
        {
            token.push_back(derewo_in.substr(word_start, count_letters));
            word_start = i + 1;
            count_letters = -1;
        }
        // Last word finishes. Suffixes are in brackets
        else if(derewo_in[i] == '(')
        {
            token.push_back(derewo_in.substr(word_start, count_letters));
            suffix_start = i + 1;
            break;
        }
        // Last Word of a row
        else if(derewo_in[i] == ' ')
        {
            token.push_back(derewo_in.substr(word_start, count_letters));
            break;
        }

    }
    count_letters = -1;
    // Search for suffixes
    for (int i = suffix_start; i < derewo_in.length(); ++i)
    {
        count_letters += 1;
        // Suffixes are separated by comma – store the last suffix
        // Start with the next suffix
        if (derewo_in[i] == ',')
        {
            suffixes.push_back(derewo_in.substr(suffix_start, count_letters));
            suffix_start = i + 1;
            count_letters = -1;
        }
        // Found last suffix
        else if(derewo_in[i] == ')' || derewo_in[i] == ' ')
        {
            suffixes.push_back(derewo_in.substr(suffix_start, count_letters));
            break;
        }
    }
    // Save word forms with all suffixes found
    for (int i = 0; i < token.size(); ++i)
    {
        for (int j = 0; j < suffixes.size(); j++)
        {
            word_form_list.push_back(token[i] + suffixes[j]);
        }
    }
}


/// Finds all word forms of a file with DeReWo word forms
/// and saves all in a list of word forms
void convert_derewo(std::string in_filename, std::string out_filename)
{
    // Vector with word forms found
    std::vector <std::string> words;
    // Read DeReWo file
    std::ifstream file_content(in_filename.c_str());
    if (file_content) {
        std::string line;
        std::vector <std::string> possible_forms;
        while (std::getline(file_content, line))
        {
          // Save word forms
          if (!line.empty() && line.front() != '#')
            find_word_forms(line, words);
        } // while
    }
    else
    {
        std::cerr << "ERROR: Unable to open text file '" << in_filename << "'" << std::endl;
    }
    std::ofstream outfile(out_filename.c_str());
    if (!outfile) {
      std::cerr << "ERROR: Unable to open '" << out_filename << "' for writing" << std::endl;
      return;
    }

    // Output states and transitions
    for (int i = 0; i < words.size(); ++i)
    {
        outfile << words[i] << "\n";
    }

    std::cout << "\nwrote " << words.size() << " words into '" << out_filename << "'";
    std::cout << "\n=======================\n";
}

/// Give the smallest element of an array
int array_min(int array[], int arr_size){
    // Set first value as minimum
    int min_val = array[0];
    // Check all elements of the array
    for (int i = 1; i < arr_size; ++i)
    {
          if (array[i] < min_val){
              min_val = array[i];
          }
    }
    return min_val;
}

/// Read all lines of a file and saves them (as strings) in a vector
bool read_file_into_vector(std::string file_path, std::vector <std::string> & vec)
{
    std::ifstream file_content(file_path.c_str());
    if (file_content) {
        std::string line;
        while (std::getline(file_content, line))
        {
            // Save non-empty line in vector
            if (!line.empty())
                vec.push_back(line);
        } // while
        return true;
    }
    std::cerr << "ERROR: Unable to open text file '" << file_path << "'" << std::endl;
    return false;
}
