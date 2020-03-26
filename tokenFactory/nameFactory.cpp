
#include "nameFactory.h"
#include "../util.h"

namespace FileInput {
	
	auto NameFactory::customReset() -> void {}

	auto NameFactory::customCheck(int position, char current) -> CheckReturn {
		/* all length words satisfy the name */
		if (position == 0)
			/* the first character may not be a number */
			return { wordChar(current), true };

		else
			return { wordChar(current) || decimalChar(current), true };
	}

	NameFactory::NameFactory()
		: TokenFactory(Token::Type::NAME) {}

}
