#include "gen_and_rec_shares.h"
#include <random>
#include <numeric>

int generateRandomNumber(int fieldSize)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, fieldSize - 1);
    return dist(rd);
}

// 加法シェアを生成
std::vector<int> getAdditiveShares(int secret, int N, int fieldSize)
{
    std::vector<int> shares;
    shares.reserve(N);

    // N-1 個のシェアを生成
    for (int i = 0; i < N - 1; ++i)
    {
        shares.push_back(generateRandomNumber(fieldSize));
    }

    // 最後のシェアを生成(秘密値から全てのシェアの合計を引いたもの)
    int sumShares = std::accumulate(shares.begin(), shares.end(), 0);
    int last_one_share = (secret - sumShares) % fieldSize;
    if (last_one_share < 0)
    {
        shares.push_back(last_one_share + fieldSize);
    }
    else
    {
        shares.push_back(last_one_share);
    }

    return shares;
}

// シェアから秘密値を復元
int reconstructSecret(std::vector<int> shares, int fieldSize)
{
    int sumShares = std::accumulate(shares.begin(), shares.end(), 0);
    return sumShares % fieldSize;
}
