#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>
#include "constants.h"
#include "errors.h"
#include "enigma.h"

// Main function for handling all the top level I/O.
int main(int argc, char** argv){

    // For storing the input data.
    // char input;
    std::string str;

    // Check if sufficient config files are provided.
    // If not, return error code 1: INSUFFICIENT_NUMBER_OF_PARAMETERS
    if (argc < 4) {
        std::cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions"  << std::endl;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }

    Enigma enigma(argc, argv);

    // Return the error code if there is any.
    if (enigma.status)
        return enigma.status;
    
    getline(std::cin >> std::ws, str);
    for (char& input : str) {
        if (!isalpha(input) || !isupper(input)) {
            std::cerr << input << " is not a valid input character (input characters must be upper case letters A-Z)!" << std::endl;
            return INVALID_INPUT_CHARACTER;
        } else {
            std::cout << enigma.encrypt(input);
        }
    }

    return NO_ERROR;
}