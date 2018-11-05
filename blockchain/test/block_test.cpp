#include "block.h"
#include "gtest/gtest.h"
#include <thread>
#include <chrono>

TEST(TestBlockCreation, TestCreationTimeStamp) {
	std::string prevHash = "12345";
	std::string data = "violet evergarden";
	Block a{ data, prevHash };
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Block b{ data, prevHash };
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Block c{ data, prevHash };

	EXPECT_TRUE(a.getCreatedTimestamp() < b.getCreatedTimestamp());
	EXPECT_TRUE(b.getCreatedTimestamp() < c.getCreatedTimestamp());
}

TEST(TestBlockCreation, TestCreationHash) {
	std::string prevHash = "12345";
	std::string data = "violet evergarden";
	Block a{ data, prevHash };
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Block b{ data, prevHash };
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Block c{ data, prevHash };

	EXPECT_TRUE(a.getHash() != b.getHash());
	EXPECT_TRUE(b.getHash() != c.getHash());
}

TEST(TestBlockCreation, TestIsValid) {
	std::string prevHash = "12345";
	std::string data = "violet evergarden";
	Block a{ data, prevHash };

	EXPECT_TRUE(a.isValid());
}