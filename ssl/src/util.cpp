#include "util.h"

namespace ssl::util {
	const char* charLookup = "0123456789abcdef";

	std::string hashToString(const uint8_t* bytes, unsigned int length) {
		char* str = new char[length * 2 + 1];

		for (unsigned int i = 0; i < length; ++i) {
			str[i * 2] = charLookup[(bytes[i] >> 4) & 0x0F];
			str[i * 2 + 1] = charLookup[bytes[i] & 0x0F];
		}

		str[length*2] = '\0'; // null-terminated
		std::string ret{ str };
		delete str;

		return ret;
	}

} // namespace ssl::util