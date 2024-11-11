﻿#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

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

/// gettok - Return the next token from standard input.
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

//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (aka Parse Tree)
//===----------------------------------------------------------------------===//

namespace {

// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
	virtual ~ExprAST() = default;
};

/// NumberExprAST - Expression class for number literals like "1.0".
class NumberExprAST : public ExprAST {
	double Val;

public:
	NumberExprAST(double Val) : Val(Val) {}
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
	std::string Name;

public:
	VariableExprAST(const std::string& Name) : Name(Name) {}
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
	char Op;
	std::unique_ptr<ExprAST> LHS, RHS;

public:
	BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
				  std::unique_ptr<ExprAST> RHS)
		: Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
	std::string Callee;
	std::vector <std::unique_ptr<ExprAST>> Args;

public:
	CallExprAST(const std::string &Callee,
				std::vector<std::unique_ptr<ExprAST>> Args)
		: Callee(Callee), Args(std::move(Args)) {}
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (this implicitly the number
/// of arguments the functino takes).
class PrototypeAST {
	std::string Name;
	std::vector<std::string> Args;

public:
	PrototypeAST(const std::string& Name, std::vector<std::string> Args)
		: Name(Name), Args(std::move(Args)) {}
	
	const std::string& getName() const { return Name; }
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
	std::unique_ptr<PrototypeAST> Proto;
	std::unique_ptr<ExprAST> Body;

public:
	FunctionAST(std::unique_ptr<PrototypeAST> Proto,
				std::unique_ptr<ExprAST> Body)
		: Proto(std::move(Proto)), Body(std::move(Body)) {}
};

} // End anonymous namespace


int main() {
	return 0;
}