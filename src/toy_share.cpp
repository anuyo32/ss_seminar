// cited from: https://www.geeksforgeeks.org/additive-secret-sharing-and-share-proactivization-using-python/

#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <random>

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

    // 最後のシェアを追加 (秘密値から全てのシェアの合計を引いたもの)
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

int main()
{
    // シェアの生成
    int secret = 1234;
    int N = 5;
    int fieldSize = 100000;
    std::vector<int> shares = getAdditiveShares(secret, N, fieldSize);

    // シェアの表示
    std::cout << "Shares are: ";
    for (int i = 0; i < N; i++)
    {
        std::cout << shares[i] << " ";
    }

    std::cout << std::endl;

    // シェアから秘密値を復元
    int reconstructedSecret = reconstructSecret(shares, fieldSize);
    std::cout << "Reconstructed secret: " << reconstructedSecret << std::endl;

    return 0;
}
