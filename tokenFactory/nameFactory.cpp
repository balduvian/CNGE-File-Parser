
#include "nameFactory.h"

#include "../util.h"

namespace FileInput {
	
	auto NameFactory::customReset() -> void {
		seekFirst = true;
	}

	NameFactory::NameFactory()
		: TokenFactory(Token::Type::NAME), seekFirst(true) {}

	auto NameFactory::customCheck(char current) -> bool {
		if (seekFirst) {
			return wordChar(current);

		} else {
			return wordChar(current) || decimalChar(current);
		}
	}

}
