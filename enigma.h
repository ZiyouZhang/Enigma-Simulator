#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

// Enigma machine: assemble all parts.
class Enigma {

public:
    
    // The status of current implementation storing the error codes.
    int status = 0;

    // Default constructor.
    // @param argc: the number of arguments provided.
    // @param argv: a series of file paths.
    Enigma(int argc, char** argv);

	// Load the the configuration files and assemble the enigma machine.
    // @param argc: the number of arguments provided.
	// @param argv: a series of file paths.
	// @return: The error codes.
    int assemble(int argc, char** argv);

    // Desctructor. Delete all dynamic allocated parts in memory.
    ~Enigma();

    // Encrypt the input letter.
    // @param input: the input letter.
    // @return: the encrypted character.
    char encrypt(char input);

private:

    // The letter travelling through different parts.
    char letter;

    // The plugborad component.
    Plugboard* plugboard = nullptr;

    // The reflector component.
    Reflector* reflector = nullptr;

    // Number of rotators.
    int num_of_rot;

    // A series of rotors.
    Rotor** rotors  = nullptr;

    // The start positions of rotors.
    std::vector<int> start_pos;
};

#endif //ENIGMA_H