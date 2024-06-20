#include "beaver_triple_sub_function.hpp"
#include "gen_and_rec_shares.hpp"
#include <numeric>
#include <iostream>
#include <tuple>

// 2つのシェアの和を返す
u_int32_t shareAddition(std::vector<u_int32_t> shares, u_int32_t fieldSize)
{
    u_int32_t sumShares = std::accumulate(shares.begin(), shares.end(), 0);
    return sumShares % fieldSize;
}

// c = a * bとなる3つ組のシェア(a,b,c)を生成
std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> generateTriples(u_int32_t fieldSize)
{
    u_int32_t a_original = generateRandomNumber(fieldSize);
    u_int32_t b_original = generateRandomNumber(fieldSize);
    u_int32_t c_original = (a_original * b_original) % fieldSize; // これは普通にかけ算しているだけ
    std::cout << "(a,b,c) = (" << a_original << ", " << b_original << ", " << c_original << ")" << std::endl;

    std::vector<u_int32_t> shares_a = getAdditiveShares(a_original, 2, fieldSize);
    std::vector<u_int32_t> shares_b = getAdditiveShares(b_original, 2, fieldSize);
    std::vector<u_int32_t> shares_c = getAdditiveShares(c_original, 2, fieldSize);
    return std::make_tuple(shares_a, shares_b, shares_c);
}