#ifndef BEAVER_TRIPLE_HPP
#define BEAVER_TRIPLE_HPP

#include <vector>
#include <tuple>

std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> generateTriples(u_int32_t fieldSize);
std::vector<u_int32_t> mult(std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> beaver_triples, std::vector<u_int32_t> shares1, std::vector<u_int32_t> shares2, u_int32_t fieldSize);

#endif // BEAVER_TRIPLE_HPP
