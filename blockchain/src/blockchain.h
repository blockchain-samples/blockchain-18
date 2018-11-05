#ifndef __blockchain_hpp__
#define __blockchain_hpp__

#include <vector>

class Block;

class Blockchain {
public:
	Blockchain();

	bool add(const Block& block);
	bool isValidNewBlock(const Block& newBlock) const;
	bool isValid() const;

	const Block& getBlock(unsigned int index) const;
	const Block& getNewestBlock() const;

private:
	std::vector<Block> chain_;

	bool isValidNewBlock(const Block& oldBlock, const Block& newBLock) const;
};

#endif