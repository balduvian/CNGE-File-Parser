
#include <iostream>

#include "filter.h"

namespace FileInput {
	Single::Single(char single) : single(single) {}

	bool Single::check(char input) const {
		return input == single;
	}

	Multiple::Multiple(std::initializer_list<char> init) : list(init) {}

	bool Multiple::check(char input) const {
		for (auto i : list)
			if (input == i)
				return true;

		return false;
	}

	Range::Range(char low, char high) : low(low), high(high) {}

	bool Range::check(char input) const {
		return input >= low && input <= high;
	}

}
