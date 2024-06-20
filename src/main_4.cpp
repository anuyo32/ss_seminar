#include "main_4.hpp"
#include "gen_and_rec_shares.hpp"
#include "beaver_triple.hpp"
#include <iostream>

int main_4()
{
    u_int32_t secret1, secret2, fieldSize;
    std::cout << "x(secret): ";
    std::cin >> secret1;
    std::cout << "y(secret): ";
    std::cin >> secret2;
    std::cout << "mod: ";
    std::cin >> fieldSize;

    std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> beaver_triples = generateTriples(fieldSize);
    std::vector<u_int32_t> shares1 =  getAdditiveShares(secret1, 2, fieldSize);
    std::vector<u_int32_t> shares2 =  getAdditiveShares(secret2, 2, fieldSize);

    std::vector<u_int32_t> result = mult(beaver_triples, shares1, shares2, fieldSize);

    std::cout << "result = " << (result[0] + result[1]) % fieldSize << std::endl;

    return 0;
}