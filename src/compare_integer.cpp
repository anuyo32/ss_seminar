#include <cmath>
#include <vector>
#include <tuple>
#include "gen_and_rec_shares.hpp"
#include "compare_integer.hpp"
#include "beaver_triple.hpp"

std::vector<u_int32_t> compare(std::vector<u_int32_t> cV, std::vector<u_int32_t> rV, u_int32_t fieldSize) {
    u_int32_t u = 0, d;
    std::vector<u_int32_t> uBitShares1(15), uBitShares2(15), uShares(2), vShares(2), dShares(2), dBits(15), lambdaShares(2), tempShares1(2), tempShares2(2), d0u0XorShares(2), comparisonResult(2);

    // uのビットシェアを生成
    for (int i = 0; i < 15; i++) {
        u_int32_t uBit = generateRandomNumber(2);
        u += pow(2, i) * uBit;
        auto uBitShare = getAdditiveShares(uBit, 2, fieldSize);
        uBitShares1[i] = uBitShare[0];
        uBitShares2[i] = uBitShare[1];
    }
    uShares = getAdditiveShares(u, 2, fieldSize);

    // dを計算
    for (int i = 0; i < 2; i++) {
        vShares[i] = (fieldSize + cV[i] - rV[i]) % fieldSize;
        dShares[i] = (2 * vShares[i] + uShares[i]) % fieldSize;
    }
    d = (dShares[0] + dShares[1]) % fieldSize;

    // dをビット変換
    for (int i = 0; i < 15; i++) {
        dBits[i] = d % 2;
        d /= 2;
    }

    // d < u の比較
    lambdaShares[0] = (1 - dBits[0]) * uBitShares1[0];
    lambdaShares[1] = (1 - dBits[0]) * uBitShares2[0];
    std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> beaver_triples;
    for (int i = 1; i < 15; i++) {
        beaver_triples = generateTriples(fieldSize);
        if (dBits[i] == 0) {
            // tempShares は一時的な格納用ベクトル
            tempShares1[0] = (fieldSize + 1 - uBitShares1[i]) % fieldSize;
            tempShares1[1] = (fieldSize - uBitShares2[i]) % fieldSize;
            lambdaShares = mult(beaver_triples, tempShares1, lambdaShares, fieldSize);
            lambdaShares[0] = (lambdaShares[0] + uBitShares1[i]) % fieldSize;
            lambdaShares[1] = (lambdaShares[1] + uBitShares2[i]) % fieldSize;
        } else {
            tempShares1[0] = uBitShares1[i];
            tempShares1[1] = uBitShares2[i];
            lambdaShares = mult(beaver_triples, tempShares1, lambdaShares, fieldSize);
        }
    }

    // λ ⊕ d0 ⊕ u0
    if (dBits[0] == 0) {
        d0u0XorShares[0] = uBitShares1[0];
        d0u0XorShares[1] = uBitShares2[0];
    } else {
        d0u0XorShares[0] = (fieldSize + 1 - uBitShares1[0]) % fieldSize;
        d0u0XorShares[1] = (fieldSize - uBitShares2[0]) % fieldSize;
    }

    tempShares1[0] = (fieldSize + 1 - d0u0XorShares[0]) % fieldSize;
    tempShares1[1] = (fieldSize - d0u0XorShares[1]) % fieldSize;
    tempShares1 = mult(beaver_triples, tempShares1, lambdaShares, fieldSize);
    tempShares2[0] = (fieldSize + 1 - lambdaShares[0]) % fieldSize;
    tempShares2[1] = (fieldSize - lambdaShares[1]) % fieldSize;
    tempShares2 = mult(beaver_triples, d0u0XorShares, tempShares2, fieldSize);

    for (int i = 0; i < 2; i++) {
        comparisonResult[i] = (tempShares1[i] + tempShares2[i]) % fieldSize;
    }

    return comparisonResult;
}