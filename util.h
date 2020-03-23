
#ifndef FILEINPUT_UTIL
#define FILEINPUT_UTIL

namespace FileInput {

	auto wordChar(char current) -> bool {
		return (current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z');
	}

	auto whiteChar(char current) -> bool {
		return current <= ' ';
	}

	auto decimalChar(char current) -> bool {
		return (current >= '0') && (current <= '9');
	}

	auto dotChar(char current) -> bool {
		return current == '.';
	}

	auto negativeChar(char current) -> bool {
		return current == '-';
	}

	auto objectOpenChar(char current) -> bool {
		return current == '{';
	}

	auto objectCloseChar(char current) -> bool {
		return current == '}';
	}

	auto arrayOpenChar(char current) -> bool {
		return current == '[';
	}

	auto arrayCloseChar(char current) -> bool {
		return current == ']';
	}

	auto stringChar(char current) -> bool {
		return current == '"';
	}

	auto charChar(char current) -> bool {
		return current == '\'';
	}

}

#endif
