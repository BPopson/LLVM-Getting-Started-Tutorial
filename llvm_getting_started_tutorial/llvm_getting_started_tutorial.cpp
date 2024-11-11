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
		Ident
	}
}


