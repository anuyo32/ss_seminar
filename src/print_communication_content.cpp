#include "print_communication_content.hpp"
#include <iostream>
#include <unistd.h>

void printSendMessage(std::string process_choice1, std::string choice1_message)
{
    std::string input_choice;
    while (true)
    {
        std::cout << "Enter '" << process_choice1 << "' to continue or 'stop' to exit: ";
        std::cin >> input_choice;

        if (input_choice == process_choice1)
        {
            std::cout << choice1_message << std::endl;
            break;
        }
        else if (input_choice == "stop")
        {
            std::cout << "Stopping execution..." << std::endl;
            std::exit(0); // プログラムを終了
        }
        else
        {
            std::cout << "Invalid input. Please enter '" << process_choice1 << "' or 'stop'." << std::endl;
        }
    }
    sleep(1);
    std::cout << std::endl;
}

std::pair<std::vector<u_int32_t>, std::vector<u_int32_t>> renewSharesAfterCommunication(std::vector<u_int32_t> shares1, std::vector<u_int32_t> shares2)
{
    u_int32_t temp = shares1[1];
    shares1[1] = shares2[0];
    shares2[0] = temp;

    return std::make_pair(shares1, shares2);
}

void printVector(std::vector<u_int32_t> vec)
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

std::pair<std::vector<u_int32_t>, std::vector<u_int32_t>> printDistributionWhoSentToWho(std::string party1_name, std::string party2_name, std::vector<u_int32_t> party1_before_shares, std::vector<u_int32_t> party2_before_shares)
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