#include "gen_and_rec_shares.h"
#include <random>
#include <numeric>
#include <iostream>

u_int32_t generateRandomNumber(u_int32_t fieldSize)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, fieldSize - 1);
    return dist(rd);
}

// 加法シェアを生成
std::vector<u_int32_t> getAdditiveShares(u_int32_t secret, int N, u_int32_t fieldSize)
{
    std::vector<u_int32_t> shares;
    shares.reserve(N);

    // N-1 個のシェアを生成
    for (int i = 0; i < N - 1; i++)
    {
        shares.push_back(generateRandomNumber(fieldSize));
    }

    // 最後のシェアを生成(秘密値から全てのシェアの合計を引いたもの)
    u_int32_t sumShares = std::accumulate(shares.begin(), shares.end(), 0) % fieldSize;
    u_int32_t last_one_share = (secret >= sumShares) ? secret - sumShares : secret - sumShares + fieldSize;
    shares.push_back(last_one_share);

    return shares;
}

void printShares(std::vector<u_int32_t> shares, std::string shares_name, int shares_num, u_int32_t fieldSize)
{
    std::cout << "Shares of " << shares_name << " are: ";
    for (int i = 0; i < shares_num; i++)
    {
        std::cout << shares[i] << " ";
    }
    std::cout << "(mod " << fieldSize << ")" << std::endl;
}

// シェアから秘密値を復元
u_int32_t reconstructSecret(std::vector<u_int32_t> shares, u_int32_t fieldSize)
{
    u_int32_t sumShares = std::accumulate(shares.begin(), shares.end(), 0);
    return sumShares % fieldSize;
}
