#include "beaver_triple.h"
#include <numeric>

int shareAddition(std::vector<int> shares, int fieldSize)
{
    int sumShares = std::accumulate(shares.begin(), shares.end(), 0);
    return sumShares % fieldSize;
}