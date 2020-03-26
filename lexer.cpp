
#include "lexer.h"

namespace FileInput {

	NameFactory Lexer::nameFactory = NameFactory();
	NumberFactory Lexer::numberFactory = NumberFactory();

	TokenFactory* Lexer::factories[2]{
		&nameFactory,
		&numberFactory
	};

	Lexer::Lexer() {}

	auto Lexer::resetAll() -> void {
		for (auto i = 0; i < NUM_FACTORIES; ++i)
			factories[i]->reset();
	}

	auto Lexer::lex(std::istream& stream) -> std::vector<Token> {
		auto tokenList = std::vector<Token>();

		/* create each token */
		while (stream.good()) {
			resetAll();

			auto length = 0;
			auto globalPosition = stream.tellg();
			auto usingFactory = (TokenFactory*)nullptr;

			auto numGood = int();
			auto current = int();
			do {
				numGood = 0;
				current = stream.get();

				/* end of file reached, don't try and check anymore */
				if (current == -1)
					break;

				for (auto i = 0; i < NUM_FACTORIES; ++i) {
					auto factory = factories[i];

					/* only check the good factories */
					/* then re check them if they're good */
					if (factory->getGood() && factories[i]->check(length, current)) {
						++numGood;

						/* grab the factory if it's satisfied */
						if (factory->getSatisfied())
							usingFactory = factory;
					}
				}

				++length;
			/* go until all tokens have been exhausted */
			} while (numGood != 0);

			if (usingFactory) {
				/* go back to the start of the current tokenization */
				/* then create the token by reading from the stream */
				stream.seekg(globalPosition);
				tokenList.push_back(usingFactory->create(stream, length));
			}
		}

		return tokenList;
	}

}