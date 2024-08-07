#include "main_5.hpp"
#include "gen_and_rec_shares.hpp"
#include "beaver_triple.hpp"
#include "compare_integer.hpp"
#include <iostream>
#include <cmath>

int main_5()
{
    u_int32_t secret1, secret2, fieldSize;
    std::cout << "x(secret): ";
    std::cin >> secret1;
    std::cout << "y(secret): ";
    std::cin >> secret2;

    // modは32749で固定(2^15以下で最大の素数とした)
    fieldSize = 32749;

    std::vector<u_int32_t> shares1 =  getAdditiveShares(secret1, 2, fieldSize);
    std::vector<u_int32_t> shares2 =  getAdditiveShares(secret2, 2, fieldSize);

    std::vector<u_int32_t> result = compare(shares1, shares2, fieldSize);

    std::cout << "result = " << (result[0] + result[1]) % fieldSize << std::endl;

    return 0;
}