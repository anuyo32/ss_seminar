// 参考: https://www.geeksforgeeks.org/additive-secret-sharing-and-share-proactivization-using-python/

// *************** n-partyでシェアの生成と復元 ***************

#include "main_1.hpp"
#include "gen_and_rec_shares.hpp"
#include <iostream>
int main_1()
{
    // 剰余環 (=mod)
    u_int32_t fieldSize = 100000;

    // 秘密値
    u_int32_t secret;
    std::cout << "secret: ";
    std::cin >> secret;

    // Party数
    int N;
    std::cout << "Number of parties: ";
    std::cin >> N;

    std::vector<u_int32_t> shares = getAdditiveShares(secret, N, fieldSize);

    // シェアの表示
    std::cout << "Shares are: ";
    for (int i = 0; i < N; i++)
    {
        std::cout << shares[i] << " ";
    }
    std::cout << "(mod " << fieldSize << ")" << std::endl;

    // 秘密値の復元
    u_int32_t reconstructedSecret = reconstructSecret(shares, fieldSize);
    std::cout << "Reconstructed secret: " << reconstructedSecret << std::endl;
    return 0;
}
