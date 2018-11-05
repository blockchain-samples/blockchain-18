#ifndef __ssl_evp_h__
#define __ssl_evp_h__

#include <openssl/evp.h>
#include <string>
#include <cstdint>

class SslEvp {
public:
	enum class EvpDigest{
		blake2b512,
		blake2s256,
		md2,
		md4,
		md5,
		md5_sha1,
		mdc2,
		ripemd160,
		sha1,
		sha224,
		sha256,
		sha512_224,
		sha512_256,
		sha384,
		sha512,
		sha3_224,
		sha3_256,
		sha3_384,
		sha3_512,
		shake128,
		shake256,
		sm3,
		whirlpool
	};

	SslEvp(EvpDigest digest);
	~SslEvp();

	void update(const std::string& message);

	void finalize();

	const uint8_t* md() const;
	unsigned int length() const;

	std::string toString() const;

private:
	EVP_MD_CTX* context_;
	EvpDigest digest_;
	uint8_t md_value_[EVP_MAX_MD_SIZE];
	unsigned int md_length_;

	static const EVP_MD* digestToEvpMd(EvpDigest digest);
};

#endif