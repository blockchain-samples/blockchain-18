#ifndef __block_hpp__
#define __block_hpp__

#include <chrono>
#include <string>

class Block {
public:
	Block(const std::string& data, const std::string& prevHash);

	time_t getCreatedTimestamp() const;
	std::string getHash() const;
	std::string getData() const;
	std::string getPreviousHash() const;

	bool isValid() const;

	static std::string generateHash(const std::string& data, const std::string& previousHash, const time_t timestamp);

private:
	time_t created_timestamp_;
	std::string previous_hash_;
	std::string hash_;
	std::string data_;

	std::string generateHash() const;
};

#endif