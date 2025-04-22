#include "Nft.h"

Nft::Nft(std::string name, std::string hash)
  : name(std::move(name)), hash(std::move(hash))
{}

const std::string& Nft::getName() const noexcept {
    return name;
}

const std::string& Nft::getHash() const noexcept {
    return hash;
}
