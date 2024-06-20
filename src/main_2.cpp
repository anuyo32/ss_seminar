// *************** Clientが2つのServerで加算 ***************

#include "main_2.hpp"
#include "gen_and_rec_shares.hpp"
#include "print_communication_content.hpp"
#include "beaver_triple_sub_function.hpp"
#include <iostream>

int main_2()
{
    // シェアの生成
    u_int32_t secret1, secret2;
    std::cout << "secret1:";
    std::cin >> secret1;
    std::cout << "secret2:";
    std::cin >> secret2;

    u_int32_t fieldSize = 100000;
    std::vector<u_int32_t> shares1 = getAdditiveShares(secret1, 2, fieldSize);
    std::cout << "Shares of secret1 are: ";
    for (int i = 0; i < 2; i++)
    {
        std::cout << shares1[i] << " ";
    }
    std::cout << "(mod " << fieldSize << ")" << std::endl;
    std::vector<u_int32_t> shares2 = getAdditiveShares(secret2, 2, fieldSize);
    std::cout << "Shares of secret2 are: ";
    for (int i = 0; i < 2; i++)
    {
        std::cout << shares2[i] << " ";
    }
    std::cout << "(mod " << fieldSize << ")" << std::endl;

    printSendMessage("send", "Sending shares...");

    // 各Partyに送るシェアと、各Partyが以降の処理で使うシェア(*)を表示。返り値として、(*)を返す。
    std::pair<std::vector<u_int32_t>, std::vector<u_int32_t>> shares_of_each_party = printDistributionWhoSentToWho("Party 1", "Party 2", shares1, shares2);

    u_int32_t party1_sum_of_shares = shareAddition(shares_of_each_party.first, fieldSize);
    u_int32_t party2_sum_of_shares = shareAddition(shares_of_each_party.second, fieldSize);
    std::cout << std::endl;
    std::cout << "[Party 1] Sum of shares: " << party1_sum_of_shares << std::endl;
    std::cout << "[Party 2] Sum of shares: " << party2_sum_of_shares << std::endl;

    printSendMessage("reconst", "Reconst is in progress...");

    u_int32_t result = (party1_sum_of_shares + party2_sum_of_shares) % fieldSize;
    std::cout << "***Secret: " << result << " ***" << std::endl;
    return 0;
}