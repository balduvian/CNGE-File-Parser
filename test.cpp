
struct block {
	int type;
	bool sides[4];
};

int numBlocks;
block* blocks;

#include "reader.h"

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
	auto reader = FileInput::Reader("test.txt");

	try {
		auto array = reader.read<kek*>();
		
		for (auto i : array) {
			std::cout << i << std::endl;
		}

		auto str = reader.read<char*>();

		std::cout << str << std::endl;

		auto ch0 = reader.read<char>();
		auto ch1 = reader.read<char>();

		std::cout << ch0 << " " << ch1 << std::endl;

	} catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	for (auto i = 0; i < 256; ++i) {
		std::cout << (char)(i | 0x20);
	}
}
