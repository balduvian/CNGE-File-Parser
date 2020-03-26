
#include "numberFactory.h"
#include "../util.h"

namespace FileInput {
	
	auto NumberFactory::customReset() -> void {}

	auto NumberFactory::customCheck(int position, char current) -> CheckReturn {
		if (position == 0) {
			/* the first character being a decimal will satify the number */
			if (decimalChar(current))
				return { true, true };

			/* first being a dot or negative sign will not satisfy the number */
			else
				return { negativeChar(current) || dotChar(current), false };

		}
		else
			return { decimalChar(current) || dotChar(current), true };

	}

	NumberFactory::NumberFactory() : TokenFactory(Token::Type::NUMBER) {}

}
