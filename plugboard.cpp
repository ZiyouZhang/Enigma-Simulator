#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>
#include "errors.h"
#include "constants.h"
#include "plugboard.h"

Plugboard::Plugboard(char* config_path) {
    for (int i = 0; i < ALPHABET_COUNT; i++) 
        cipher[i] = i;
    status = load(config_path);
}

int Plugboard::load(char* config_path) {
    
    std::vector<int> temp_v;
    int current_int;

    std::ifstream in_stream;
    in_stream.open(config_path);
    if (in_stream.fail()) {
        std::cerr << "Oh no! An error uccured when opening the file: " << config_path << std::endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }

    // Check non-numerical char, index range, duplicated item.
    // Peek here first to raise eof() in case it's an empty file.
    in_stream.peek();
    while (!in_stream.eof() && temp_v.size() < ALPHABET_COUNT) {
        in_stream >> current_int >> std::ws;
        
        // Reading integer will fail if there is an non numerical character.
        if (in_stream.fail()) {
            std::cerr << "Non-numeric character in plugboard file " << config_path << std::endl;
            return NON_NUMERIC_CHARACTER;
        }
        
        if (current_int < 0 || current_int > 25) {
            std::cerr << "Oh no! The index range is not valid in the file: " << config_path << std::endl;
            return INVALID_INDEX;
        }

        if (std::find(temp_v.begin(), temp_v.end(), current_int) != temp_v.end()) {
            std::cerr << "Oh no! The plugboard configuration is not possible in the file: " << config_path << std::endl;
            return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        }
        
        temp_v.push_back(current_int);
        in_stream.peek();
    }

    while (!in_stream.eof()) {
        in_stream >> current_int >> std::ws;
        temp_v.push_back(current_int);
    }

    // Check the number of items and if it contains more than 26 numbers.
    if (temp_v.size() > ALPHABET_COUNT || (temp_v.size() % 2 != 0)) {
        std::cerr << "Incorrect number of parameters in plugboard file " << config_path << std::endl;
        return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }

    in_stream.close();

    // Configure the cipher mapping.
    for (std::size_t i = 0; i < temp_v.size(); i += 2) {
        cipher[temp_v[i]] = temp_v[i+1];
        cipher[temp_v[i+1]] = temp_v[i];
    }
    
    return NO_ERROR;
}

char Plugboard::encrypt(char input) {
    return (char)(cipher[input - INDEX_A] + INDEX_A);
}
