#include "blockchain.h"
#include "block.h"
#include "gtest/gtest.h"

TEST(TestAddBlock, AddBlockFail) {
	Blockchain blockchain{};
	Block block{"data", "074F349C303B4D508D61FE84F020F5314018C2924BA99839F46525A60699ADD2"};

	EXPECT_FALSE(blockchain.add(block));
}

TEST(TestAddBlock, AddBlockSuccess) {
	Blockchain blockchain{};
	const Block& tipOfChain = blockchain.getNewestBlock();
	Block block("data", tipOfChain.getHash());
	Block block2("data2", block.getHash());

	EXPECT_TRUE(blockchain.add(block));
	EXPECT_TRUE(blockchain.add(block2));
}

TEST(TestValidate, ValidateFail) {
	Blockchain bc{};
	Block b{"data", "074F349C303B4D508D61FE84F020F5314018C2924BA99839F46525A60699ADD2"};

	EXPECT_FALSE(bc.isValidNewBlock(b));
}

TEST(TestValidate, ValidateOk) {
	Blockchain blockchain{};
	const Block& tipOfChain = blockchain.getNewestBlock();
	Block block("data", tipOfChain.getHash());

	EXPECT_TRUE(blockchain.isValidNewBlock(block));
}

TEST(TestValidChain, ChainIsValid) {
	Blockchain blockchain{};
	const Block& tipOfChain = blockchain.getNewestBlock();
	Block block("data", tipOfChain.getHash());
	Block block2("data2", block.getHash());
	Block block3("violet", block2.getHash());
	Block block4("evergarden", block3.getHash());
	blockchain.add(block);
	blockchain.add(block2);
	blockchain.add(block3);
	blockchain.add(block4);

	EXPECT_TRUE(blockchain.isValid());
}
