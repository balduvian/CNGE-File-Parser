
#include "token.h"

namespace FileInput {
	
	Token::Token() : type(Type()), length(0), value(nullptr) {}

	Token::Token(Type type, int length, char* value) : type(type), length(length), value(value) {}

	Token::Token(Token&& other) : type(other.type), length(other.length), value(other.value) {
		other.value = nullptr;
	}

	Token::~Token() {
		if (value)
			delete[] value;
	}

	auto Token::fromStream(Type type, std::istream& stream, int length) -> Token {
		auto value = new char[length];

		for (auto i = 0; i < length; ++i) {
			value[i] = stream.get();
		}

		return Token(type, length, value);
	}

	auto Token::isType(Type compare) -> bool {
		return type == compare;
	}

	auto Token::getLength() -> int {
		return length;
	}

	auto Token::getValue() -> char* {
		return value;
	}

}
