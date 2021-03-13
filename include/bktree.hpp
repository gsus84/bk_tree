// Burkhard Keller tree
// Can read words from files
// Can create a dot file with a tree
// Search for similar words
// Simple calculation of the Levenshtein distance 

# pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "helper.hpp"

/// Burkhard Keller tree with two vectors as base
class BKTree
{
public:
    /// Levenshtein distance
    typedef int LDist;

public:
    /// Constructor for empty bk tree
    BKTree(bool dbg=false){
        debug = dbg;
        number_tree_words = 0;
        max_height = 0;
    }
    /**
    \brief Creates a Burkhard Keller tree from the content of the file 'filename'
    \param filename Name of the text file (must contain one token per row, ISO-8859-encoding)
    \param dbg      Gives additionally stat information if dbg == true
    */
    BKTree(std::string filename, bool dbg=false) : BKTree(dbg)
      {
        std::ifstream words_in(filename.c_str());
        if (words_in) {
          std::string word;
          while (std::getline(words_in, word)) {
            if (!word.empty())
              add_word(word);
          } // while
        }
        else std::cerr << "ERROR: Unable to open text file '" << filename << "'" << std::endl;
      }

    /// Destructor
    ~BKTree()
    {
        // Show internal statistic
        if (debug) {
            std::cerr << "\nMaximale Höhe: " << max_height;
            std::cerr << "\nZahl der Wörter: " << number_tree_words;
            std::cerr << "\nAnzahl der Übergänge: " << number_transitions() <<"\n";
        }
    }

    /// Adds a word into the tree
    void add_word(std::string word)
    {
        int insert_height = 1;
        // Add word to node
        nodes.push_back(word);
        if (nodes.size() >= 2)
        {
            // Create new transition
            Transition new_transition(
            start_state(), calculate_levenstein(nodes[start_state()].word, word),
            nodes.size() - 1);
            // Find parent node
            for (int i = 0; i < transitions.size();)
            {
                // Distance to parent node is not equal
                if (transitions[i].dist != new_transition.dist)
                {
                    // No other transitions to parent nodes
                    if (transitions[i].next_trans_index < 0)
                     {
                         // Insert reference to new transition
                         transitions[i].next_trans_index = transitions.size();
                         insert_height += 1;
                         break;
                     }
                     // Next transition
                     i = transitions[i].next_trans_index;
                }
                else{
                    // A Parent node already exists with the same distance
                    // New transition inserts new parent node
                    new_transition.parent_state = transitions[i].child_state;
                    // Calculate Levenshtein distance to parent node
                    new_transition.dist = calculate_levenstein(nodes[new_transition.parent_state].word, word);
                    // New parent node has no children
                    if (nodes[new_transition.parent_state].tr_idx < 0)
                    {
                        // Mark new transition as the first transition of the parent node
                        nodes[new_transition.parent_state].tr_idx = transitions.size();
                        break;
                    }
                    // Check transitions of new parent node
                    i = nodes[new_transition.parent_state].tr_idx;
                    insert_height += 1;
                }
            }
            // Check if tree contains a word already
            if (new_transition.dist > 0)
            {
                // Add transition
                transitions.push_back(new_transition);
                number_tree_words += 1;
                if (insert_height > max_height)
                {
                    max_height = insert_height;
                }
            }
            // Tree does not contain word
            else
            {
                nodes.pop_back();
            }
        }
        else
        {
            // Root node points to (yet to be inserted) first transition
            nodes[0].tr_idx = transitions.size();
            number_tree_words += 1;
        }
    }

    /// Gives the number of nodes of the bk tree
    int number_nodes()
    {
       return nodes.size();
    }

    /// Gives max height of the bk tree
    int height()
    {
        return max_height;
    }

    /// Gives the number of words of the bk tree
    int number_words()
    {
        return number_tree_words;
    }

    /// Gives the number of transitions of the bk tree
    int number_transitions()
    {
        return transitions.size();
    }

    /// Gives all similar words within a Levenshtein distance
    void show_near_words(std::string word, LDist max_dist=1)
    {
        std::vector <std::string> near_words;
        find_near_words(word, max_dist, near_words);

        std::cout << "\nNear words of \"" << word << "\" with a Levenstein Distance of "
                  << max_dist << " are: \n\n";
        for (int i = 0; i < near_words.size(); ++i){
            std::cout << near_words[i] << "\n";
        }
    }

    /// Shows file output in the command line
    void show_dot_output()
    {
        std::cout << "\ndigraph BKTree {\n";
        for (int i = 0; i < transitions.size(); ++i)
        {
            std::cout << "\"" << nodes[transitions[i].parent_state].word
                      << "\" -> \""
                      << nodes[transitions[i].child_state].word << "\" [label="
                      << transitions[i].dist << "];\n";
        }
        std::cout << "}\n";
        std::cout << "\n___________________________________________\n";
    }

    /// Creates a dot representation of a tree in a file
    void generate_dot_file(std::string dot_filename)
    {
    std::ofstream dot_out(dot_filename.c_str());
    if (!dot_out) {
      std::cerr << "ERROR: Unable to open dot file for writing" << std::endl;
      return;
    }
    // Leader
    dot_out << "digraph BKTree {\n";

    // Output states and transitions
    for (int i = 0; i < transitions.size(); ++i)
    {
    dot_out << "\"" << nodes[transitions[i].parent_state].word
            << "\" -> \""
            << nodes[transitions[i].child_state].word << "\" [label="
            << transitions[i].dist << "];\n";
    }
    dot_out << "}\n";

    }

    /// Searches for all similar words and saves them in a vector
    void find_near_words(std::string word, LDist max_dist, std::vector <std::string> & near_words)
    {
        // Indices of possible nodes
        std::vector <int> possible_nodes;
        // Levenshtein distance between search word and bk tree root
        LDist node_dist = calculate_levenstein(nodes[0].word, word);
        add_near_word(nodes[0].word, node_dist, max_dist, near_words);

        // Search tree and save hits
        for (int i = 0; i < transitions.size();)
        {
            // Calculate distance to parent node
            node_dist = calculate_levenstein(nodes[transitions[i].parent_state].word, word);

            // Test if distance from parent node is within the range of the word
            if (transitions[i].dist >= node_dist - max_dist &&
                    transitions[i].dist <= node_dist + max_dist &&
                    nodes[transitions[i].child_state].tr_idx >= 0)
            {
                // Save possible child nodes
                possible_nodes.push_back(nodes[transitions[i].child_state].tr_idx);

            }
            // Calculate distance to child node
            node_dist = calculate_levenstein(nodes[transitions[i].child_state].word, word);
            add_near_word(nodes[transitions[i].child_state].word, node_dist, max_dist, near_words);

            // Check if node has other children
            if (transitions[i].next_trans_index >= 0)
            {
                // Next child node
                i = transitions[i].next_trans_index;
            }
            else
            {
                // Check next nodes
                if (possible_nodes.size() > 0)
                {
                    i = possible_nodes.back();
                    possible_nodes.pop_back();
                }
                else
                {
                    // BK tree has no other possible nodes within the maximum distance
                    i = transitions.size();
                }
            }
        }
    }
private:
    /// Nodes
    struct Node
    {
        /// Constructor with default values
        Node(std::string w = "", unsigned int idx = -1)
        {
            word = w;
            tr_idx = idx;
        }
        std::string word;       /// Word
        int tr_idx;             /// First transition to child node
    };

    /// Transition
    struct Transition
    {
        /// Constructor with default values
        Transition(int p_state = -1, int d = -1, int s = -1, int n = -1)
        {
            parent_state = 0;
            dist = d;
            child_state = s;
            next_trans_index = n;
        }
        int parent_state;           /// Index of parent node
        LDist dist;                 /// Levenshtein distance to parent node
        int child_state;            /// Index of child node
        int next_trans_index;       /// Next entry in adjacency list

        ///  Validates transition
        bool validate()
        {
            // Parent node, Levenshtein distance and child node are conclusive
            if (parent_state >= 0 && dist >= 1 && child_state >= 0)
                return true;
            // Transition is not conclusive
            return false;
        }

    };

    /// Adds word to hit list if it is within the correct Levenshtein distance
    void add_near_word(std::string word, LDist word_dist, LDist max_dist, std::vector <std::string> & near_words)
    {
        if (word_dist > 0 && word_dist <= max_dist)
        {
            near_words.push_back(word);
        }
    }

    /// Returns the start state
    int start_state()
    {
        return 0;
    }

    /// Calculates Levenshtein distance: each change has a valence of 1 
    /// (substitution, deletion, insertion)
    LDist calculate_levenstein(std::string word_1, std::string word_2)
    {
        int rows = word_1.length() + 1;
        int cols = word_2.length() + 1;

        //  Matrix for possible changes
        int dist[rows][cols];

        // Initialize matrix
        for (int row = 0; row < rows; ++row){
            for (int col = 0; col < cols; ++col){
                dist[row][col] = 0;
            }
        }

        // Prefixes can be converted to empty strings by deletion
        for (int i = 1; i < rows; ++i){
            dist[i][0] = i;
        }

        // Prefixes are created by insertion
        for (int i = 1; i < cols; ++i){
            dist[0][i] = i;
        }

        // Calculation of the smallest possible distance in the matrix
        for (int col = 1; col < cols; ++col){
            for (int row = 1; row < rows; ++row){
                int cost = 0;
                if (word_1[row - 1] != word_2[col - 1]){
                    cost = 1;
                }
                int change[3] = {dist[row-1][col] + 1, dist[row][col-1] + 1, dist[row-1][col-1] + cost};
                dist[row][col] = array_min(change, 3);
            }
        }

        return dist[rows-1][cols-1];
    }

private: // Instance variables
    std::vector <Node> nodes;
    std::vector <Transition> transitions;
    int max_height;
    int number_tree_words;
    bool debug;

};
