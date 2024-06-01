#ifndef PRINT_COMMUNICATION_CONTENT_H
#define PRINT_COMMUNICATION_CONTENT_H

#include <vector>
#include <utility>
#include <string>

std::pair<std::vector<int>, std::vector<int>> renewSharesAfterCommunication(std::vector<int> shares1, std::vector<int> shares2);

void printVector(std::vector<int> vec);

std::pair<std::vector<int>, std::vector<int>> printDistributionWhoSentToWho(std::string party1_name, std::string party2_name, std::vector<int> party1_before_shares, std::vector<int> party2_before_shares);

#endif // PRINT_COMMUNICATION_CONTENT_H