// cited from: https://www.geeksforgeeks.org/additive-secret-sharing-and-share-proactivization-using-python/

#include "gen_and_rec_shares.h"
#include <iostream>

int main()
{
    // シェアの生成
    int secret = 1234;
    std::cout << "secret:" << secret << std::endl;

    int N = 5;
    int fieldSize = 100000;
    std::vector<int> shares = getAdditiveShares(secret, N, fieldSize);

    // シェアの表示
    std::cout << "Shares are: ";
    for (int i = 0; i < N; i++)
    {
        std::cout << shares[i] << " ";
    }
    std::cout << "(mod " << fieldSize << ")" << std::endl;

    // 秘密値の復元
    int reconstructedSecret = reconstructSecret(shares, fieldSize);
    std::cout << "Reconstructed secret: " << reconstructedSecret << std::endl;

    return 0;
}