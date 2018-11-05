#include "sslevp.h"
#include "gtest/gtest.h"
#include <iostream>

namespace SslEvp_Test {
	std::string hashToString(const uint8_t* hash, unsigned int len) {
		std::stringstream hashstr;

		for (unsigned int i = 0; i < len; ++i) {
			hashstr << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
		}
		return hashstr.str();
	}
} // namespace SslEvp_Test

TEST(SslEvp, TestConstructorAndDestructor) {
	SslEvp* evp = new SslEvp{ SslEvp::EvpDigest::sha256 };

	unsigned int mdlen = evp->length();

	EXPECT_TRUE(mdlen == 0);

	delete evp;
}

TEST(SslEvp, TestSHA256) {
	SslEvp evp{ SslEvp::EvpDigest::sha256 };

	evp.update("violet evergarden");
	evp.finalize();

	unsigned int mdlen = evp.length();
	const uint8_t* md = evp.md();

	EXPECT_TRUE(md != nullptr);
	EXPECT_TRUE(mdlen != 0);

	std::string hash = SslEvp_Test::hashToString(md, mdlen);

	std::cout << "hash: " << hash;
	std::cout << std::endl;

	const std::string goldenHash = "8D1824876BCEFEB5BFB25C1DEE061B42BAB5E738A8D928852015345E6F49F3F7";

	EXPECT_TRUE(_strcmpi(hash.c_str(), goldenHash.c_str()) == 0);
}

TEST(SslEvp, TestSHA256_MultiUpdate) {
	SslEvp evp{ SslEvp::EvpDigest::sha256 };

	evp.update("violet evergarden\n");
	evp.update("I will run as fast as I can to wherever my customer desires.\n");
	evp.update("I am the auto memories doll.\n");
	evp.update("12345");
	evp.finalize();

	unsigned int mdlen = evp.length();
	const uint8_t* md = evp.md();

	EXPECT_TRUE(md != nullptr);
	EXPECT_TRUE(mdlen != 0);

	std::string hash = SslEvp_Test::hashToString(md, mdlen);

	std::cout << "hash: " << hash;
	std::cout << std::endl;

	const std::string goldenHash = "A7D2627919444D1B234EE60A307854A187F2A7629C1B70FA78589E419915D8C1";

	EXPECT_TRUE(_strcmpi(hash.c_str(), goldenHash.c_str()) == 0);
}
