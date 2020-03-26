
#ifndef FILEINPUT_FACTORY_NAMEFACTORY
#define FILEINPUT_FACTORY_NAMEFACTORY

#include "../tokenFactory.h"

namespace FileInput {
	
	class NameFactory : public TokenFactory {
	private:
		auto customReset() -> void override;

		auto customCheck(int, char) -> CheckReturn override;

	public:
		NameFactory();

	};

}

#endif
