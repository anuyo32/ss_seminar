#include "print_communication_content.h"
#include <iostream>

std::pair<std::vector<int>, std::vector<int>> renewSharesAfterCommunication(std::vector<int> shares1, std::vector<int> shares2)
{
    int temp = shares1[1];
    shares1[1] = shares2[0];
    shares2[0] = temp;

    return std::make_pair(shares1, shares2);
}

void printVector(std::vector<int> vec)
{
    std::cout << "[";
    for (std::size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i];
        if (i < vec.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

std::pair<std::vector<int>, std::vector<int>> printDistributionWhoSentToWho(std::string party1_name, std::string party2_name, std::vector<int> party1_before_shares, std::vector<int> party2_before_shares)
{
    auto result = renewSharesAfterCommunication(party1_before_shares, party2_before_shares);
    std::cout << "Sent " << party1_before_shares[0] << " to " << party1_name << ". Sent " << party1_before_shares[1] << " to " << party2_name << "." << std::endl;
    std::cout << "Sent " << party2_before_shares[0] << " to " << party1_name << ". Sent " << party2_before_shares[1] << " to " << party2_name << "." << std::endl;

    std::cout << party1_name << " has ";
    printVector(result.first);
    std::cout << std::endl;
    std::cout << party2_name << " has ";
    printVector(result.second);
    std::cout << std::endl;
    return result;
}