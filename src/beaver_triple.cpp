#include "gen_and_rec_shares.hpp"
#include <tuple>
#include <iostream>

// c = a * bとなる3つ組のシェア(a,b,c)を生成
std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> generateTriples(u_int32_t fieldSize)
{
    u_int32_t a_original = generateRandomNumber(fieldSize);
    u_int32_t b_original = generateRandomNumber(fieldSize);
    u_int64_t temp_product = (uint64_t)a_original * (uint64_t)b_original; // 32ビット整数同士の乗算によるオーバーフローを避ける
    uint32_t c_original = (uint32_t)(temp_product % fieldSize);

    std::vector<u_int32_t> shares_a = getAdditiveShares(a_original, 2, fieldSize);
    std::vector<u_int32_t> shares_b = getAdditiveShares(b_original, 2, fieldSize);
    std::vector<u_int32_t> shares_c = getAdditiveShares(c_original, 2, fieldSize);
    
    return std::make_tuple(shares_a, shares_b, shares_c);
}

std::vector<u_int32_t> mult(std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> beaver_triples, std::vector<u_int32_t> shares1, std::vector<u_int32_t> shares2, u_int32_t fieldSize){ // (a,b,c)の三つ組と秘密値x,yのシェアを引数にとる
    std::vector<u_int32_t> shares_a = std::get<0>(beaver_triples);
    std::vector<u_int32_t> shares_b = std::get<1>(beaver_triples);
    std::vector<u_int32_t> shares_c = std::get<2>(beaver_triples);

    std::vector<u_int32_t> shares_d(2), shares_e(2);
    for (int i = 0; i < 2; i++)
    {
        shares_d[i] = (fieldSize + shares1[i] - shares_a[i]) % fieldSize;
        shares_e[i] = (fieldSize + shares2[i] - shares_b[i]) % fieldSize;
    }

    // ここでdとeの二つの中間値を復元するために通信が必要。
    u_int32_t d = (shares_d[0] + shares_d[1]) % fieldSize;
    u_int32_t e = (shares_e[0] + shares_e[1]) % fieldSize;

    std::vector<u_int32_t> result(2);
    for (int i = 0; i < 2; i++)
    {
        result[i] = (e * shares_a[i] + d * shares_b[i] + shares_c[i]) % fieldSize;
    }
    u_int64_t temp_product = (uint64_t)d * (uint64_t)e; // 32ビット整数同士の乗算によるオーバーフローを避ける
    result[0] += (uint32_t)(temp_product % fieldSize);

    return result;
}