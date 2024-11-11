#include "llvm_getting_started_tutorial.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	return 0;
}

// The lexer returns token [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
	tok_eof = -1,

	// Commands
	tok_def = -2,
	tok_extern = -3,

	// Primary
	tok_identifier = -4,
	tok_number = -5,
};

static std::string IdentifierStr;	// Filled in if tok_identifier
static double NumVal;				// Filled in if tok_number

// gettok - Return the next token from standard input.
static int gettok() {
	static int LastChar = ' ';

	// Skip any whitespace
	while (isspace(LastChar)) {
		LastChar = getchar();
	}

	if (isalpha(LastChar)) { // Identifier: [a-zA-Z][a-zA-Z0-9]*
		IdentifierStr = LastChar;
		while (isalnum((LastChar = getchar()))) {
			IdentifierStr += LastChar;
		}

		if (IdentifierStr == "def") {
			return tok_def;
		}

		if (IdentifierStr == "extern") {
			return tok_extern;
		}

		return tok_identifier;
	}

	if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
		std::string NumStr;
		do {
			NumStr += LastChar;
			LastChar = getchar();
		} while (isdigit(LastChar) || LastChar == '.');

		NumVal = strtod(NumStr.c_str(), 0);
		return tok_number;
	}

	if (LastChar == '#') {
		// Comment until EoL
		do {
			LastChar = getchar();
		} while (LastChar != EOF && LastChar != '\n');

		if (LastChar != EOF) {
			return gettok();
		}
	}

	// Check for EOF. Don't eat the EOF
	if (LastChar == EOF) {
		return tok_eof;
	}

	// Otherwise, just return the character as its ASCII value.
	int ThisChar = LastChar;
	LastChar = getchar();
	return ThisChar;
}


