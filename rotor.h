#ifndef ROTOR_H
#define ROTOR_H

#include <vector>

// Enigma component: rotor class.
class Rotor {

public:

    // The status of current implementation storing the error codes.
    int status = 0;

    // Defalt constructor.
    // @param config_path: the configuration file path.
    // @param start_pos: the starting position of the rotor. 
    // @param nth_pos: the 0-based index of the rotor from right to left.
    Rotor(char* config_path, int start_pos, int nth_pos);

    // A pointer to the next rotor (the one on the left).
    Rotor* next = nullptr;

    // Load the the configuration file.
	// @param config_path: The configuration file path.
	// @return: The error codes.
	int load(char* config_path);

    // Encrypt the input letter from right to left (towards reflector).
	// @param input: the letter to be encrypted.
	// @return: The encrypted letter. 
	char encrypt_forward(char input);

    // Encrypt the input letter from left to right (away from reflector).
	// @param input: the letter to be encrypted.
	// @return: The encrypted letter. 
	char encrypt_backward(char input);

    // Rotate the rotor.
    bool rotate();

private:

    // The 0-based index of the rotor from right to left.
    int nth_pos = 0;

    // Current rotation times count (always in the range of 0-25).
    int rot_count = 0;

    // The notch positions.
    // When rotate into this position, the next rotor will rotate.
    std::vector<int> notch_pos;

    // The mapping for encryption from right to left (towards reflector).
    int offset_forward[ALPHABET_COUNT];

	// The mapping for encryption from left to right (away from reflector).
    int offset_backward[ALPHABET_COUNT];
};

#endif //ROTOR_H