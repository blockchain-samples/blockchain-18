#include "sslevp.h"
#include "util.h"
#include <stdexcept>

SslEvp::SslEvp(EvpDigest digest) : 
	digest_(digest),
	md_length_(0) {
	context_ = EVP_MD_CTX_new();
	if (!context_) {
		throw std::runtime_error("Cannot create EVP context.");
	}

	const EVP_MD* md = digestToEvpMd(digest);
	EVP_DigestInit_ex(context_, md, NULL);

	memset(md_value_, 0, EVP_MAX_MD_SIZE * sizeof(uint8_t));
}

SslEvp::~SslEvp() {
	EVP_MD_CTX_free(context_);
}

void SslEvp::update(const std::string& message) {
	if (message.length() > 0) {
		EVP_DigestUpdate(context_, message.c_str(), message.length());
	}
}

void SslEvp::finalize() {
	EVP_DigestFinal_ex(context_, md_value_, &md_length_);
}

const uint8_t* SslEvp::md() const {
	return md_value_;
}

unsigned int SslEvp::length() const {
	return md_length_;
}

const EVP_MD* SslEvp::digestToEvpMd(EvpDigest digest) {
	switch (digest) {
	case EvpDigest::sha256:
		return EVP_sha256();
	default:
		return nullptr;
	}
}

std::string SslEvp::toString() const {
	return ssl::util::hashToString(md_value_, md_length_);
}