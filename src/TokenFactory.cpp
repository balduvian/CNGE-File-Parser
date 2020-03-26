
#include "tokenFactory.h"

namespace FileInput {
	
	TokenFactory::TokenFactory(Token::Type type) : values(CheckReturn()), type(type) {}

	auto TokenFactory::reset() -> void {
		values = CheckReturn();

		customReset();
	}

	auto TokenFactory::create(std::istream& stream, int length) -> Token {
		return Token::fromStream(type, stream, length);
	}

	auto TokenFactory::check(int position, char current) -> bool {
		auto [returnGood, returnSatisfied] = customCheck(position, current);

		/* factory can only be satisfied if the check is good */

		if (values.good = returnGood)
			values.satisfied = returnSatisfied;
		else
			values.satisfied = false;

		return values.good;
	}

	auto TokenFactory::getGood() -> bool {
		return values.good;
	}

	auto TokenFactory::getSatisfied() -> bool {
		return values.satisfied;
	}

}
