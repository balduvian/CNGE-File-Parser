
#ifndef FILEINPUT_UTIL
#define FILEINPUT_UTIL

namespace FileInput {

	auto wordChar(char current) -> bool;

	auto whiteChar(char current) -> bool;

	auto decimalChar(char current) -> bool;

	auto dotChar(char current) -> bool;

	auto negativeChar(char current) -> bool;

	auto objectOpenChar(char current) -> bool;

	auto objectCloseChar(char current) -> bool;

	auto arrayOpenChar(char current) -> bool;

	auto arrayCloseChar(char current) -> bool;

	auto stringChar(char current) -> bool;

	auto charChar(char current) -> bool;

}

#endif
