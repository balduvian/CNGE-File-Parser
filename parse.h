
#ifndef FILEINPUT_PARSE
#define FILEINPUT_PARSE

#include <stdexcept>
#include <type_traits>
#include <charconv>

namespace FileInput {
	template <typename T>
	auto basicParse(std::vector<char>&& str) -> T {
		auto value = T();

		auto [ptr, err] = std::from_chars(str.data(), str.data() + str.size(), value);

		if (err != std::errc{})
			throw std::invalid_argument("invalid parse");

		return value;
	}
}

#endif
