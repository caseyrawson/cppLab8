#ifndef MANAGETOKENS_H
#define MANAGETOKENS_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Nft;

class ManageTokens {
public:
    // Mint a new token, return hash
    std::string mintToken(const std::string& walletName,
                          const std::string& assetName);

    // Move token, return bool
    bool transferToken(const std::string& srcWallet,
                       const std::string& destWallet,
                       const std::string& tokenHash);

    // Get a wallet's tokens
    const std::vector<std::unique_ptr<Nft>>&
      getWallet(const std::string& walletName) const;

private:
    std::unordered_map<std::string,
        std::vector<std::unique_ptr<Nft>>> wallets_;

    std::string generateUniqueHash();
};

#endif
