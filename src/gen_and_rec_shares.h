#ifndef GEN_AND_REC_SHARES_H
#define GEN_AND_REC_SHARES_H

#include <vector>

int generateRandomNumber(int fieldSize);

std::vector<int> getAdditiveShares(int secret, int N, int fieldSize);

int reconstructSecret(std::vector<int> shares, int fieldSize);

#endif // GEN_AND_REC_SHARES_H
