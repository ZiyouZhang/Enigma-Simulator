#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>
#include "errors.h"
#include "constants.h"
#include "rotor.h"

// A helper function used for mapping character indices.
char map_input (char c);

Rotor::Rotor(char* config_path, int the_start_pos, int the_nth_pos) {
    for (int i = 0; i < 26; i++) 
        offset_forward[i] = i;
    for (int i = 0; i < 26; i++) 
        offset_backward[i] = i;
    nth_pos = the_nth_pos;
    status = load(config_path);
    rot_count += the_start_pos;
}   

int Rotor::load(char* config_path) {
    
    std::vector<int> mapping;
    int current_int;

    std::ifstream in_stream;
    in_stream.open(config_path);
    if (in_stream.fail()) {
        std::cerr << "Oh no! An error uccured when opening the file: " << config_path << std::endl;
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }

    // Check if the mapping is valid
    for (int i = 0; i < 26; i++) {
        in_stream >> current_int >> std::ws;

        // Reading integer will fail if there is an non numerical character.
        if (in_stream.fail()) {
            std::cerr << "Non-numeric character for mapping in rotor file " << config_path << std::endl;
            return NON_NUMERIC_CHARACTER;
        }

        // If fewer than 26 rules provided.
        if (in_stream.eof()) {
            std::cerr << "Not all inputs mapped in rotor file: " << config_path << std::endl;
            return INVALID_ROTOR_MAPPING;
        }

        if (current_int < 0 || current_int > 25) {
            std::cerr << "Oh no! The index range is not valid in the file: " << config_path << std::endl;
            return INVALID_INDEX;
        }

        if (std::find(mapping.begin(), mapping.end(), current_int) != mapping.end()) {
            int temp = 0;
            while (mapping[temp] != *std::find(mapping.begin(), mapping.end(), current_int)) {
                temp++;
            }
            std::cerr << "Invalid mapping of input " << i << " to output " << current_int << " (output " << current_int << " is already mapped to from input " << temp << ") in rotor file: " << config_path << std::endl;
            return INVALID_ROTOR_MAPPING;
        }

        mapping.push_back(current_int);
    }

    while (!in_stream.eof()) {
        in_stream >> current_int >> std::ws;
        if (current_int < 0 || current_int > 25) {
            std::cerr << "Oh no! The index range is not valid in the file: " << config_path << std::endl;
            return INVALID_INDEX;
        }

        notch_pos.push_back(current_int);
    }


    for (std::size_t i = 0; i < 26; i++) {
        offset_forward[i] = mapping[i] - i;
    }

    for (std::size_t i = 0; i < 26; i++) {
        offset_backward[mapping[i]] =  i - mapping[i];
    }

    return NO_ERROR;
}

char Rotor::encrypt_forward(char input) {
    return map_input(input + offset_forward[(int)(input - 'A' + rot_count + 26) % 26]);
}

char Rotor::encrypt_backward(char input) {
    return map_input(input + offset_backward[(int)(input - 'A' + rot_count + 26) % 26]);
}

bool Rotor::rotate() {
    rot_count = (rot_count + 1) % 26;
    for (auto notch : notch_pos) {
        if (notch == ((rot_count) % 26)) {
            return true;
        }
    }
    return false;
}

char map_input (char c) {
    return (c - 'A' + 26) % 26 + 'A';
}