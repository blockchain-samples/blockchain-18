#include "block.h"
#include "sslevp.h"

Block::Block(const std::string& data, const std::string& prevHash) :
	data_(data),
	previous_hash_(prevHash),
	created_timestamp_(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {

	hash_ = generateHash();
}

time_t Block::getCreatedTimestamp() const {
	return created_timestamp_;
}

std::string Block::getHash() const {
	return hash_;
}

std::string Block::getData() const {
	return data_;
}

std::string Block::getPreviousHash() const {
	return previous_hash_;
}

bool Block::isValid() const {
	std::string hash = generateHash();
	return (hash_ == hash);
}

std::string Block::generateHash(const std::string& data, const std::string& previousHash, const time_t timestamp) {
	SslEvp evp{ SslEvp::EvpDigest::sha256 };
	evp.update(data);
	evp.update(previousHash);
	evp.update(std::to_string(timestamp));
	evp.finalize();

	return evp.toString();
}

std::string Block::generateHash() const {
	return generateHash(data_, previous_hash_, created_timestamp_);
}