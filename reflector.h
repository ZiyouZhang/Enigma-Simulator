#ifndef REFLECTOR_H
#define REFLECTOR_H

// Enigma component: refector class.
class Reflector {

public:

	// The status of current implementation storing the error codes.
	int status = 0;

	// Default constructor.
	// @param config_path: the configuration file path.
	Reflector(char* config_path);

	// Load the the configuration file.
	// @param config_path: The configuration file path.
	// @return: The error codes.
	int load(char* config_path);

	// Encrypt the input letter.
	// @param input: the letter to be encrypted.
	// @return: The encrypted letter. 
	char encrypt(char input);

private:

	// The mapping for encryption.
	int cipher[ALPHABET_COUNT];

};

#endif //REFLECTOR_H