
#ifndef FILEINPUT_FACTORY_NUMBERFACTORY
#define FILEINPUT_FACTORY_NUMBERFACTORY

#include "../tokenFactory.h"

namespace FileInput {
	
	class NumberFactory : public TokenFactory {
	private:
		auto customReset() -> void override;

		auto customCheck(int, char) -> CheckReturn override;

	public:
		NumberFactory();

	};

}

#endif
