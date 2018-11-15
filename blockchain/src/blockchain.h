#ifndef __blockchain_hpp__
#define __blockchain_hpp__

#include <vector>

class Block;

class Blockchain {
public:
	Blockchain(unsigned int difficulty = 0);

	bool add(const Block& block);
	bool isValidNewBlock(const Block& newBlock) const;
	bool isValid() const;

	const Block& getBlock(unsigned int index) const;
	const Block& getNewestBlock() const;

	const Block& mineBlock(std::string data);
	const Block& mineBlock(std::string data, unsigned int difficulty);
	unsigned int getDifficulty() const;
	void setDifficulty(unsigned int difficulty);

	bool isHashValid(const std::string& hash, unsigned int difficulty) const;

private:
	std::vector<Block> chain_;
	unsigned int difficulty_;

	bool isValidNewBlock(const Block& oldBlock, const Block& newBLock) const;
};

#endif