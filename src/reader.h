
#ifndef FILEINPUT_READER
#define FILEINPUT_READER

#include <fstream>
#include <stdexcept>
#include <vector>

#include "filter.h"
#include "parse.h"

namespace FileInput {
	class Reader {
	private:
		struct hitReturn {
			char current;
			int value;
		};

		constexpr static const char* FILE_ERROR = "file reading had a problem";

		static Single tagEnd;
		static Single lineEnd;
		static Single arrayStart;
		static Single arrayEnd;
		static Single scopeStart;
		static Single scopeEnd;
		static Single arraySeparator;
		static Single backSlash;
		static Single stringBorder;
		static Single charBorder;
		static Range whiteSpace;
		static Range number;
		static Multiple arrayReadEnd;
		static Multiple scopeLineEnd;
		
		Filter* endOverride = &scopeLineEnd;
		std::ifstream input;

		auto hit(Filter*, Filter*)->hitReturn;
		auto hit(Filter*)->hitReturn;
		auto hit(std::initializer_list<Filter*>)->hitReturn;

		auto hitRead(Filter*)->std::vector<char>;
		auto stringRead()->std::string;
		auto charRead()->char;

		auto stepBack(int i = 1) -> void;

	public:
		template <typename T>
		struct readReturn {
			using type = T;
		};

		template <typename T>
		struct readReturn<T*> {
			using type = std::vector<T>;
		};

		template <>
		struct readReturn<char*> {
			using type = std::string;
		};

		Reader(const char*);
		
		/// base template for reading of non pointer type
		template <typename T>
		auto read() -> typename std::enable_if<!std::is_pointer<T>::value, typename readReturn<T>::type>::type {
			hit(&number);

			stepBack();

			return basicParse<T>(hitRead(endOverride));
		}

		/// base template for reading of pointer type
		template <typename TP>
		auto read() -> typename std::enable_if<std::is_pointer<TP>::value, typename readReturn<TP>::type>::type {
			using RawT = typename std::remove_pointer<TP>::type;

			/* get the length of the array to allocate */
			hit(&arrayStart);

			auto start = input.tellg();

			auto scope = 0;
			auto elementCount = 1;

			/* find the number of objects in this list */
			/* by counting commas, keeping track of scope */
			auto keepGoing = true;

			while (keepGoing) {
				auto [current, i] = hit({ &scopeStart, &scopeEnd, &arraySeparator, &arrayEnd });

				switch (i) {
				case 0: {
					++scope;
				} break;
				case 1: {
					--scope;
				} break;
				case 2: {
					if (scope == 0)
						++elementCount;
				} break;

				case 3: {
					if (scope == 0)
						keepGoing = false;
				} break;
				}
			}

			/* allocate array */
			auto ret = std::vector<RawT>();
			ret.reserve(elementCount);

			/* go back to start of array to read in data */
			input.seekg(start);

			/* fill in data */
			endOverride = &arrayReadEnd;

			for (auto i = 0; i < elementCount; ++i)
				ret.push_back(read<RawT>());

			endOverride = &scopeLineEnd;

			return ret;
		}

		template <>
		auto read<char>() -> typename readReturn<char>::type {
			hit(&charBorder);

			return charRead();
		}

		template <>
		auto read<char*>() -> typename readReturn<char*>::type {
			hit(&stringBorder);
			
			return stringRead();
		}

	};

}

#endif
