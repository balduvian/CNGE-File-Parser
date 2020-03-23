
#ifndef FILEINPUT_FACTORY_NAMEFACTORY
#define FILEINPUT_FACTORY_NAMEFACTORY

#include "../tokenFactory.h"

namespace FileInput {
	
	class NameFactory : public TokenFactory {
	private:
		bool seekFirst;

		auto customReset() -> void override;

		auto customCheck(char) -> bool override;

	public:
		NameFactory();

	};

}

#endif
