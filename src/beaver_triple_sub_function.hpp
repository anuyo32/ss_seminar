#ifndef BEAVER_TRIPLE_SUB_FUNCTION_HPP
#define BEAVER_TRIPLE_SUB_FUNCTION_HPP

#include <vector>
#include <tuple>

u_int32_t shareAddition(std::vector<u_int32_t> shares, u_int32_t fieldSize);

std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> generateTriples_old(u_int32_t fieldSize);

#endif // BEAVER_TRIPLE_SUB_FUNCTION_HPP