
#ifndef FILEINPUT_LEXER
#define FILEINPUT_LEXER

#include <vector>
#include <fstream>

#include "token.h"
#include "tokenFactory.h"
#include "tokenFactory/nameFactory.h"
#include "tokenFactory/numberFactory.h"

namespace FileInput {
	
	class Lexer {
	private:
		static NameFactory nameFactory;
		static NumberFactory numberFactory;

		constexpr static int NUM_FACTORIES = 2;
		static TokenFactory* factories[NUM_FACTORIES];

		auto resetAll() -> void;

	public:
		Lexer();

		auto lex(std::istream&) -> std::vector<Token>;

	};

}

#endif
