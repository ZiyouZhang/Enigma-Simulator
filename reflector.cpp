#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>
#include "errors.h"
#include "constants.h"
#include "reflector.h"

Reflector::Reflector(char* config_path) {
    for (int i = 0; i < 26; i++) 
        cipher[i] = i;
    status = load(config_path);
}

int Reflector::load(char* config_path) {
    
    std::vector<int> temp_v;
    int current_int;

    std::ifstream in_stream;
    in_stream.open(config_path);
    if (in_stream.fail()) {
        std::cerr << "Oh no! An error uccured when opening the file: " << config_path << std::endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }

    // Check non-numerical char, index range, duplicated item.
    in_stream.peek();
    while (!in_stream.eof() && temp_v.size() < 26) {
        in_stream >> current_int >> std::ws;

        // Reading integer will fail if there is an non numerical character.
        if (in_stream.fail()) {
            std::cerr << "Non-numeric character in reflector file " << config_path << std::endl;
            return NON_NUMERIC_CHARACTER;
        }

        if (current_int < 0 || current_int > 25) {
            std::cerr << "Oh no! The index range is not valid in the file: " << config_path << std::endl;
            return INVALID_INDEX;
        }

        if (std::find(temp_v.begin(), temp_v.end(), current_int) != temp_v.end()) {
            std::cerr << "Oh no! The refelctor configuration is not possible in the file: " << config_path << std::endl;
            return INVALID_REFLECTOR_MAPPING;
        }
        
        temp_v.push_back(current_int);
        in_stream.peek();
    }

    while (!in_stream.eof()) {
        in_stream >> current_int >> std::ws;
        temp_v.push_back(current_int);
    }

    if (temp_v.size() > 27 || temp_v.size() %2 != 0) {
        std::cerr << "Incorrect (odd) number of parameters in reflector file " << config_path << std::endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    // Check the number of items.
    if (temp_v.size() < 26) {
        std::cerr << "Insufficient number of mappings in reflector file: " << config_path << std::endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    in_stream.close();

    // Configure the cipher mapping rule.
    for (std::size_t i = 0; i < temp_v.size(); i += 2) {
        cipher[temp_v[i]] = temp_v[i+1];
        cipher[temp_v[i+1]] = temp_v[i];
    }

    return NO_ERROR;
}

char Reflector::encrypt(char input) {
    return (char)(cipher[input - INDEX_A] + INDEX_A);
}