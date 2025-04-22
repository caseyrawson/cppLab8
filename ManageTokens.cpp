#include "ManageTokens.h"
#include "Nft.h"
#include <openssl/sha.h>
#include <random>
#include <sstream>
#include <iomanip>

void transferNftVector(
    // helper function
    std::vector<std::unique_ptr<Nft>> & toVector,
    std::vector<std::unique_ptr<Nft>> & fromVector,
    std::vector<std::unique_ptr<Nft>>::iterator pos)
{
    toVector.push_back(std::move(*pos));
    fromVector.erase(pos);
}

std::string ManageTokens::generateUniqueHash() {
    // get a random 64‑bit number
    static bool seeded = []{
        std::srand(std::random_device{}());
        return true;
    }();
    uint64_t rnd = std::rand();

    // turn into string
    std::string input = std::to_string(rnd);

    // digest
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.data()),
           input.size(), digest);

    // convert to hex
    std::ostringstream oss;
    for (auto byte : digest) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(byte);
    }
    return oss.str();
}

std::string ManageTokens::mintToken(
    const std::string& walletName,
    const std::string& assetName)
{
    std::string hash = generateUniqueHash();
    auto token = std::make_unique<Nft>(assetName, hash);
    wallets_[walletName].push_back(std::move(token));
    return hash;
}

bool ManageTokens::transferToken(
    const std::string& srcWallet,
    const std::string& destWallet,
    const std::string& tokenHash)
{
    auto sit = wallets_.find(srcWallet);
    if (sit == wallets_.end()) return false;
    auto & src = sit->second;

    for (auto it = src.begin(); it != src.end(); ++it) {
        if ((*it)->getHash() == tokenHash) {
            // use the helper
            transferNftVector(wallets_[destWallet], src, it);
            return true;
        }
    }
    return false;
}

const std::vector<std::unique_ptr<Nft>>&
ManageTokens::getWallet(const std::string& walletName) const
{
    static const std::vector<std::unique_ptr<Nft>> empty;
    auto it = wallets_.find(walletName);
    return it != wallets_.end() ? it->second : empty;
}
