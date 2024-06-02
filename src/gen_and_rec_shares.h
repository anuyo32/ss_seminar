#ifndef GEN_AND_REC_SHARES_H
#define GEN_AND_REC_SHARES_H

#include <vector>

u_int32_t generateRandomNumber(u_int32_t fieldSize);

std::vector<u_int32_t> getAdditiveShares(u_int32_t secret, int N, u_int32_t fieldSize);

void printShares(std::vector<u_int32_t> shares, std::string shares_name, int N, u_int32_t fieldSize);

u_int32_t reconstructSecret(std::vector<u_int32_t> shares, u_int32_t fieldSize);

#endif // GEN_AND_REC_SHARES_H
