
struct block {
	int type;
	bool sides[4];
};

int numBlocks;
block* blocks;

#include "reader.h"
#include "lexer.h"

#include <charconv>
#include <iostream>
#include <charconv>

struct kek {
	std::vector<int> a;
	float b;

	friend std::ostream& operator<<(std::ostream& stream, kek& kek) {
		for (auto i : kek.a) {
			std::cout << i << ", ";
		}
		std::cout << std::endl << kek.b << std::endl;

		return stream;
	}
};

template <>
auto FileInput::Reader::read<kek>() -> kek {
	return {read<int*>(), read<float>()};
}

int main() {
	auto lexer = FileInput::Lexer();

	auto stream = std::ifstream("test2.txt");

	auto tokenList = lexer.lex(stream);

	for (auto &i : tokenList) {
		std::cout << (int)i.getType() << ", ";
	}
}
