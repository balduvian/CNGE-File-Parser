
#ifndef FILEINPUT_TOKENFACTORY
#define FILEINPUT_TOKENFACTORY

#include <fstream>

#include "token.h"

namespace FileInput {

	class TokenFactory {
	protected:
		struct CheckReturn {
			bool good = true;
			bool satisfied = false;
		};

		virtual auto customReset() -> void = 0;

		virtual auto customCheck(int, char) -> CheckReturn = 0;

	private:
		CheckReturn values;

		Token::Type type;

	public:
		TokenFactory(Token::Type);

		TokenFactory(const TokenFactory&) = delete;
		void operator=(const TokenFactory&) = delete;

		auto reset() -> void;

		auto check(int, char) -> bool;

		auto create(std::istream&, int) -> Token;

		auto getGood() -> bool;

		auto getSatisfied() -> bool;

	};

}

#endif
