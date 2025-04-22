#ifndef NFT_H
#define NFT_H
#include <string>

class Nft {
public:
    Nft(std::string name, std::string hash);

    const std::string& getName() const noexcept;
    const std::string& getHash() const noexcept;

private:
    std::string name;
    std::string hash;
};

#endif
