
#ifndef FILEINPUT_TOKEN
#define FILEINPUT_TOKEN

#include <fstream>

namespace FileInput {

	class Token {
	public:
		enum class Type {
			NAME,
			ARRAY_START,
			ARRAY_END,
			OBJECT_START,
			OBJECT_END,
			NUMBER,
			STRING_BOUNDARY,
			CHAR_BOUNDARY
		};

	private:
		Type type;

		int length;
		char* value;

		Token(Type, int, char*);

		Token(const Token&) = delete;
		Token& operator=(const Token&) = delete;

	public:
		Token();

		Token(Token&&) noexcept;

		~Token();

		static auto fromStream(Type, std::istream&, int) -> Token;

		auto isType(Type) -> bool;

		auto getLength() -> int;

		auto getValue() -> char*;

		auto getType() -> Type;

	};

}

#endif