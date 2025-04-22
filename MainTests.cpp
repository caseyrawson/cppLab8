#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"

#include "ManageTokens.h"
#include "Nft.h"

TEST_CASE("Check that mint places token in wallet") {
    ManageTokens mgr;
    auto h = mgr.mintToken("Casey", "MyArt");
    const auto& a = mgr.getWallet("Casey");
    CHECK(a[0]->getHash() == h);
    CHECK(a[0]->getName() == "MyArt");
}

TEST_CASE("Check that each mint makes different hash") {
    ManageTokens mgr;
    auto h1 = mgr.mintToken("Casey", "TokenA");
    auto h2 = mgr.mintToken("Casey", "TokenB");
    CHECK(h1 != h2);
}

TEST_CASE("Check that") {
    ManageTokens mgr;
    auto h = mgr.mintToken("Casey", "Asset");
    CHECK(mgr.getWallet("Bob").empty());

    bool ok = mgr.transferToken("Casey", "Bob", h);
    CHECK(ok);

    CHECK(mgr.getWallet("Casey").empty());
    CHECK(mgr.getWallet("Bob")[0]->getHash() == h);
}

TEST_CASE("Transfer of missing token fails") {
    ManageTokens mgr;
    CHECK_FALSE(mgr.transferToken("X", "Y", "nope"));
}
