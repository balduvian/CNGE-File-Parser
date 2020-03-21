
#include <iostream>

#include "reader.h"

namespace FileInput {
	Single Reader::tagEnd = Single(':');
	Single Reader::lineEnd = Single(';');
	Single Reader::arrayStart = Single('[');
	Single Reader::arrayEnd = Single(']');
	Single Reader::scopeStart = Single('{');
	Single Reader::scopeEnd = Single('}');
	Single Reader::arraySeparator = Single(',');
	Single Reader::backSlash = Single('\\');
	Single Reader::stringBorder = Single('"');
	Single Reader::charBorder = Single('\'');
	Range Reader::whiteSpace = Range( 0x00, ' ' );
	Range Reader::number = Range('-', '9');
	Multiple Reader::arrayReadEnd = Multiple({ ',', ']' });
	Multiple Reader::scopeLineEnd = Multiple({ ';', '}' });

	Reader::Reader(const char* fileName) : input(fileName) {}

	auto Reader::hit(Filter* zero, Filter* one) -> hitReturn {
		while (input.good()) {	
			auto current = (char)input.get();

			if (zero->check(current))
				return { current, 0 };

			if (one->check(current))
				return { current, 1 };
		}

		throw std::runtime_error(FILE_ERROR);
	}

	auto Reader::hit(std::initializer_list<Filter*> list) -> hitReturn {
		while (input.good()) {
			auto current = (char)input.get();

			for (auto it = list.begin(); it < list.end(); ++it)
				if ((*it)->check(current))
					return { current, (int)(it - list.begin()) };
		}

		throw std::runtime_error(FILE_ERROR);
	}

	auto Reader::hit(Filter* end) -> hitReturn {
		while (input.good()) {
			auto current = (char)input.get();

			if (end->check(current))
				return { current, 0 };
		}

		throw std::runtime_error(FILE_ERROR);
	}

	auto Reader::hitRead(Filter* endFilter) -> std::vector<char> {
		auto start = input.tellg();

		/* find the end of read chunk */
		while (input.good() && !endFilter->check(input.get()));
		
		if (input.bad())
			throw std::runtime_error(FILE_ERROR);

		/* make a buffer of length of the chunk */
		auto length = input.tellg() - start - 1;
		auto buffer = std::vector<char>();
		buffer.reserve(length);

		/* go back to the start */
		input.seekg(start);

		/* read data into chunk */
		/* ignoring whitespace */
		for (auto i = 0; i < length; ++i) {
			auto current = (char)input.get();

			buffer.push_back(current);
		}

		return buffer;
	}

	auto Reader::stringRead() -> std::string {
		auto start = input.tellg();

		/* find the end of string */
		auto ignoreEnd = false;
		auto ignores = 0;

		while (input.good()) {
			auto current = input.get();

			if (ignoreEnd) {
				ignoreEnd = false;
				++ignores;

			} else {
				if (backSlash.check(current)) {
					ignoreEnd = true;

				} else if (stringBorder.check(current))
					break;
			}
		}

		if (input.bad())
			throw std::runtime_error(FILE_ERROR);

		/* make a buffer of length of the chunk */
		auto length = input.tellg() - start - 1 - ignores;
		auto str = std::string();
		str.reserve(length);

		/* go back to the start */
		input.seekg(start);

		/* read data into chunk */
		/* ignoring whitespace */
		auto ignoreLast = false;

		for (auto i = 0; i < length + ignores; ++i) {
			auto current = (char)input.get();

			if (ignoreLast) {
				str.push_back(current);

				ignoreLast = false;
			}
			else {
				if (backSlash.check(current))
					ignoreLast = true;
				else
					str.push_back(current);
			}
		}

		return str;
	}

	auto Reader::charRead() -> char {
		auto ret = '\0';

		/* find the end of char block */
		auto ignoreNow = false;
		auto length = 0;

		while (input.good()) {
			auto current = input.get();

			if (ignoreNow) {
				ignoreNow = false;
				ret = current;
				++length;

			} else {
				if (backSlash.check(current)) {
					ignoreNow = true;

				} else if (charBorder.check(current))
					break;

				else {
					ret = current;
					++length;
				}
			}

			if (length > 1)
				throw std::runtime_error("invalid char parse");
		}

		if (input.bad())
			throw std::runtime_error(FILE_ERROR);

		return ret;
	}

	auto Reader::stepBack(int i) -> void {
		input.seekg(-i, std::ios_base::cur);
	}

}
