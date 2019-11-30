#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>
#include "errors.h"
#include "constants.h"
#include "enigma.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

Enigma::Enigma(int argc, char** argv) {
    status = assemble(argc, argv);
}

int Enigma::assemble(int argc, char** argv) {
    
    plugboard = new Plugboard(argv[1]);
    if (plugboard -> status)
        return plugboard -> status;

    reflector = new Reflector(argv[2]);
    if (reflector -> status)
        return reflector -> status;

    num_of_rot = argc - 4;
    if (num_of_rot)
        rotors = new Rotor*[num_of_rot];

    int current_int;
    char* rot_pos_config = argv[argc-1];

    // Get all the start positions.
    std::ifstream in_stream;
    in_stream.open(rot_pos_config);
    if (in_stream.fail()) {
        std::cerr << "Oh no! An error uccured when opening the file: " << rot_pos_config << std::endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }

    // Check non-numerical char and index range.
    // Peek here first to raise eof() in case it's an empty file.
    in_stream.peek();
    while (!in_stream.eof()) {
        in_stream >> current_int >> std::ws;

        // Reading integer will fail if there is an non numerical character.
        if (in_stream.fail()) {
            std::cerr << "Non-numeric character in rotor positions file " << rot_pos_config << std::endl;
            return NON_NUMERIC_CHARACTER;
        }

        if (current_int < 0 || current_int > 25) {
            std::cerr << "Oh no! The index range is not valid in the file: " << rot_pos_config << std::endl;
            return INVALID_INDEX;
        }
        
        start_pos.push_back(current_int);
        in_stream.peek();
    }

    if (start_pos.size() < (size_t)num_of_rot) {
        std::cerr << "No starting position for rotor "<< start_pos.size() <<" in rotor position file: " << rot_pos_config << std::endl;
        return NO_ROTOR_STARTING_POSITION;
    }

    for (int i = 0; i < num_of_rot; i++) {
        rotors[i] = new Rotor(argv[argc-2-i], start_pos[num_of_rot-1-i], i);
        if (rotors[i] -> status)
            return rotors[i] -> status;
    }

    for (int i = 0; i < num_of_rot - 1; i++) {
        rotors[i] -> next = rotors[i+1];
    }

    return NO_ERROR;
}

Enigma::~Enigma() {
    if (plugboard)
        delete plugboard;
    if (reflector)
        delete reflector;
    // for (int i = 0; i < num_of_rot; i++) {
    //     if (rotors[i])
    //         delete rotors[i];
    // }
    if (rotors)
        delete[] rotors;
}

char Enigma::encrypt(char input) {
    letter = input;

    letter = plugboard -> encrypt(letter);

    // Pass here stands for whether to pass the rotation.
    bool pass = true;
    for (int i = 0; (i < (int)num_of_rot) && pass; i++)
        pass = rotors[i] -> rotate();
    for (int i = 0; i < num_of_rot; i++)
        letter = rotors[i] -> encrypt_forward(letter);
    letter = reflector -> encrypt(letter);
    for (int i = num_of_rot - 1; i >= 0; i--)
        letter = rotors[i] -> encrypt_backward(letter);
    letter = plugboard -> encrypt(letter);

    return letter;
}