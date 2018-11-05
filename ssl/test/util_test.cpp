#include "gtest/gtest.h"
#include "util.h"
#include "sslevp.h"
#include <iostream>

TEST(SslUtil, TestHashToString) {
	const std::string goldenHash = "8D1824876BCEFEB5BFB25C1DEE061B42BAB5E738A8D928852015345E6F49F3F7";

	uint8_t byteHash[] = { 0x8D, 0x18, 0x24, 0x87, 0x6B, 0xCE, 0xFE, 0xB5, 0xBF, 0xB2, 0x5C, 0x1D, 0xEE, 0x06,
							0x1B, 0x42, 0xBA, 0xB5, 0xE7, 0x38, 0xA8, 0xD9, 0x28, 0x85, 0x20, 0x15, 0x34, 0x5E,
							0x6F, 0x49, 0xF3, 0xF7 };

	std::string hashStr = ssl::util::hashToString(byteHash, 32);

	std::cout << "golden hash: " << goldenHash << std::endl;
	std::cout << "hash: " << hashStr << std::endl;
	std::cout << "size: " << sizeof(byteHash) << std::endl;

	EXPECT_TRUE(_strcmpi(hashStr.c_str(), goldenHash.c_str()) == 0);
}

TEST(SslUtil, TestHashToStringWithEvp) {
	SslEvp evp{ SslEvp::EvpDigest::sha256 };

	evp.update("violet evergarden");
	evp.finalize();

	unsigned int mdlen = evp.length();
	const uint8_t* md = evp.md();

	const std::string goldenHash = "8D1824876BCEFEB5BFB25C1DEE061B42BAB5E738A8D928852015345E6F49F3F7";

	std::string hash = ssl::util::hashToString(md, mdlen);
	EXPECT_TRUE(_strcmpi(hash.c_str(), goldenHash.c_str()) == 0);
}