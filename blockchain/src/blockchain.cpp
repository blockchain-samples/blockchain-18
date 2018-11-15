#include "blockchain.h"
#include "block.h"
#include "sslevp.h"
#include <cmath>

Blockchain::Blockchain(unsigned int difficulty) :
	difficulty_(difficulty) {
	// create genesis block.
	Block genesis{"Gensis block", ""};
	chain_.push_back(genesis);
}

bool Blockchain::add(const Block& block) {
	if (isValidNewBlock(block)) {
		chain_.push_back(block);
		return true;
	}

	return false;
}

bool Blockchain::isValidNewBlock(const Block& newBlock) const {
	return (isValidNewBlock(chain_.back(), newBlock));
}

bool Blockchain::isValidNewBlock(const Block& oldBlock, const Block& newBlock) const {
	// New block must have previous hash of old block
	if (oldBlock.getHash() != newBlock.getPreviousHash()) {
		return false;
	}
	// Hash generated using old block's hash and new block's member fields
	// should be the same as new block's hash
	else if (Block::generateHash(newBlock.getData(),
		oldBlock.getHash(),
		newBlock.getCreatedTimestamp()) != newBlock.getHash()) {
		return false;
	}
	// The new block itself is valid; hash generated from fields is correct
	else if (!newBlock.isValid()) {
		return false;
	}

	return true;
}

bool Blockchain::isValid() const {
	for (unsigned int i = 1; i < chain_.size(); ++i) {
		const Block& current = chain_[i - 1];
		const Block& next = chain_[i];

		// check if block itself is valid
		if (!next.isValid()) {
			return false;
		}
		else if (current.getHash() != next.getPreviousHash()) {
			return false;
		}
	}

	return true;
}

const Block& Blockchain::getBlock(unsigned int index) const {
	if (index < chain_.size()) {
		return chain_[index];
	}

	return chain_[0]; // there should always be a genesis block
}

const Block& Blockchain::getNewestBlock() const {
	return chain_.back();
}

const Block& Blockchain::mineBlock(std::string data) {
	return mineBlock(data, difficulty_);
}

const Block& Blockchain::mineBlock(std::string data, unsigned int difficulty) {
	const Block& tipOfChain = getNewestBlock();
	bool isBlockMined = false;
	do {
		Block block{ data, tipOfChain.getHash() };
		isBlockMined = isHashValid(block.getHash(), difficulty);

		if (isBlockMined) {
			add(block); // maybe check if this passes or not
		}
	} while (!isBlockMined);

	return chain_.back();
}

unsigned int Blockchain::getDifficulty() const {
	return difficulty_;
}

void Blockchain::setDifficulty(unsigned int difficulty) {
	difficulty_ = difficulty;
}

bool Blockchain::isHashValid(const std::string& hash, unsigned int difficulty) const {
	// is valid if leads with zeroes equal to difficulty.
	if (difficulty * 4 > hash.length()) {
		return false;
	}

	unsigned int nBytes = std::ceil(difficulty / 4);
	unsigned int nZeroBytes = std::floor(difficulty / 4);

	// we only need to check bits for 1 character.
	for (unsigned int i = 0; i < nZeroBytes; ++i) {
		if (hash[i] != '0') {
			return false;
		}
	}

	if (nZeroBytes < nBytes) {
		// mask off top part and shift up low 4 bits
		char c = (0x0F & hash[nBytes - 1]);

		// iterate through 4 bits.
		for (int i = 3; i > 0; --i) {
			if ((c >> i) == 1) {
				return false;
			}
		}
	}

	return true;
}