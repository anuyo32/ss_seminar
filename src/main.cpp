// cited from: https://www.geeksforgeeks.org/additive-secret-sharing-and-share-proactivization-using-python/

#include "gen_and_rec_shares.h"
#include "beaver_triple.h"
#include "print_communication_content.h"
#include <iostream>
#include <string>
#include <unistd.h>

int main()
{
    // ***************n-partyでのシェアの生成と復元***************
    // // シェアの生成
    // int secret = 1234;
    // std::cout << "secret:" << secret << std::endl;

    // int N = 5;
    // int fieldSize = 100000;
    // std::vector<int> shares = getAdditiveShares(secret, N, fieldSize);

    // // シェアの表示
    // std::cout << "Shares are: ";
    // for (int i = 0; i < N; i++)
    // {
    //     std::cout << shares[i] << " ";
    // }
    // std::cout << "(mod " << fieldSize << ")" << std::endl;

    // // 秘密値の復元
    // int reconstructedSecret = reconstructSecret(shares, fieldSize);
    // std::cout << "Reconstructed secret: " << reconstructedSecret << std::endl;

    // ***************Clientが2つのServerで加算***************
    // シェアの生成
    int secret1, secret2;
    std::cout << "secret1:";
    std::cin >> secret1;
    std::cout << "secret2:";
    std::cin >> secret2;

    int fieldSize = 100000;
    std::vector<int> shares1 = getAdditiveShares(secret1, 2, fieldSize);
    std::cout << "Shares of secret1 are: ";
    for (int i = 0; i < 2; i++)
    {
        std::cout << shares1[i] << " ";
    }
    std::cout << "(mod " << fieldSize << ")" << std::endl;
    std::vector<int> shares2 = getAdditiveShares(secret2, 2, fieldSize);
    std::cout << "Shares of secret2 are: ";
    for (int i = 0; i < 2; i++)
    {
        std::cout << shares2[i] << " ";
    }
    std::cout << "(mod " << fieldSize << ")" << std::endl;

    std::string choose_send_or_stop;
    while (true)
    {
        std::cout << "Enter 'send' to continue or 'stop' to exit: ";
        std::cin >> choose_send_or_stop;

        if (choose_send_or_stop == "send")
        {
            std::cout << "Sending shares..." << std::endl;
            break;
        }
        else if (choose_send_or_stop == "stop")
        {
            std::cout << "Stopping execution..." << std::endl;
            return 0; // プログラムを終了
        }
        else
        {
            std::cout << "Invalid input. Please enter 'send' or 'stop'." << std::endl;
        }
    }

    sleep(1);
    std::cout << std::endl;
    sleep(1);

    // 各Partyに送るシェアと、各Partyが以降の処理で使うシェア(*)を表示。返り値として、(*)を返す。
    std::pair<std::vector<int>, std::vector<int>> shares_of_each_party = printDistributionWhoSentToWho("Party 1", "Party 2", shares1, shares2);

    int party1_sum_of_shares = shareAddition(shares_of_each_party.first, fieldSize);
    int party2_sum_of_shares = shareAddition(shares_of_each_party.second, fieldSize);
    std::cout << std::endl;
    std::cout << "[Party 1] Sum of shares: " << party1_sum_of_shares << std::endl;
    std::cout << "[Party 2] Sum of shares: " << party2_sum_of_shares << std::endl;

    std::string choose_reconst_or_stop;
    while (true)
    {
        std::cout << "Enter 'reconst' to continue or 'stop' to exit: ";
        std::cin >> choose_reconst_or_stop;

        if (choose_reconst_or_stop == "reconst")
        {
            std::cout << "Reconst is in progress..." << std::endl;
            break;
        }
        else if (choose_reconst_or_stop == "stop")
        {
            std::cout << "Stopping execution..." << std::endl;
            return 0; // プログラムを終了
        }
        else
        {
            std::cout << "Invalid input. Please enter 'reconst' or 'stop'." << std::endl;
        }
    }

    sleep(1);
    std::cout << std::endl;
    sleep(1);

    int result = (party1_sum_of_shares + party2_sum_of_shares) % fieldSize;
    std::cout << "***Secret: " << result << " ***" << std::endl;

    // ***************Clientが2つのServerでかけ算(Beaver Multiplication Triples)***************
    // ここに書いていく

    return 0;
}