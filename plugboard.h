#ifndef PLUGBOARD_H
#define PLUGBOARD_H

// Enigma component: plugboard class.
class Plugboard {

public:

	// The status of current implementation storing the error codes.
	int status = 0;

	// Default constructor.
	// @param config_path: the configuration file path.
	Plugboard(char* config_path);

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
	int cipher[26];
};

#endif //PLUGBOARD_H