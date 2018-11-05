#include "blockchain.h"
#include "block.h"
#include "sslevp.h"

Blockchain::Blockchain() {
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