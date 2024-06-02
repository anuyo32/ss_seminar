#ifndef BEAVER_TRIPLE_H
#define BEAVER_TRIPLE_H

#include <vector>

u_int32_t shareAddition(std::vector<u_int32_t> shares, u_int32_t fieldSize);

std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> generateTriples(u_int32_t fieldSize);

#endif // BEAVER_TRIPLE_H