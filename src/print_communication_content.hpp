#ifndef PRINT_COMMUNICATION_CONTENT_HPP
#define PRINT_COMMUNICATION_CONTENT_HPP

#include <vector>
#include <utility>
#include <string>

void printSendMessage(std::string process_choice1, std::string choice1_message);

std::pair<std::vector<u_int32_t>, std::vector<u_int32_t>> renewSharesAfterCommunication(std::vector<u_int32_t> shares1, std::vector<u_int32_t> shares2);

void printVector(std::vector<u_int32_t> vec);

std::pair<std::vector<u_int32_t>, std::vector<u_int32_t>> printDistributionWhoSentToWho(std::string party1_name, std::string party2_name, std::vector<u_int32_t> party1_before_shares, std::vector<u_int32_t> party2_before_shares);

#endif // PRINT_COMMUNICATION_CONTENT_HPP