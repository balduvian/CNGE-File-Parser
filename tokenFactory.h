
#ifndef FILEINPUT_TOKENFACTORY
#define FILEINPUT_TOKENFACTORY

#include <fstream>

#include "token.h"

namespace FileInput {

	class TokenFactory {
	private:
		bool good;
		
		Token::Type type;

	protected:
		virtual auto customReset() -> void = 0;

		virtual auto customCheck(char) -> bool = 0;

	public:
		TokenFactory(Token::Type);

		TokenFactory(const TokenFactory&) = delete;
		void operator=(const TokenFactory&) = delete;

		auto reset() -> void;

		auto check(char) -> void;

		auto create(std::istream&, int) -> Token;

	};

}

#endif
