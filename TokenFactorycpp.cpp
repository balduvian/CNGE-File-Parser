
#include "tokenFactory.h"

namespace FileInput {
	
	TokenFactory::TokenFactory(Token::Type type) : good(true), type(type) {}

	auto TokenFactory::reset() -> void {
		good = true;

		customReset();
	}

	auto TokenFactory::create(std::istream& stream, int length) -> Token {
		return Token::fromStream(type, stream, length);
	}

	auto TokenFactory::check(char current) -> void {
		good = customCheck(current);
	}
}
