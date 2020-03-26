
#ifndef FILEINPUT_PARSER
#define FILEINPUT_PARSER

#include <initializer_list>
#include <vector>

namespace FileInput {
	class Filter {
	protected:
		virtual bool check(char) const = 0;

	public:
		friend class Reader;

	};

	class Single : public Filter {
	private:
		char single;

	protected:
		bool check(char) const;

	public:
		Single(char);

		friend class Reader;

	};

	class Multiple : public Filter {
	private:
		std::vector<char> list;

	protected:
		bool check(char) const;

	public:
		Multiple(std::initializer_list<char>);

		friend class Reader;

	};

	class Range : public Filter {
	private:
		char low;
		char high;

	protected:
		bool check(char) const;

	public:
		Range(char, char);

		friend class Reader;

	};

}

#endif
