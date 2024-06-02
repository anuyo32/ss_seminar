// cited from: https://www.geeksforgeeks.org/additive-secret-sharing-and-share-proactivization-using-python/

#include "gen_and_rec_shares.h"
#include "beaver_triple.h"
#include "print_communication_content.h"
#include <iostream>
#include <string>

int main()
{
    // *************** n-partyでのシェアの生成と復元 ***************
    // // シェアの生成
    // u_int32_t secret = 1234;
    // std::cout << "secret:" << secret << std::endl;

    // int N = 5;                    // N-party
    // u_int32_t fieldSize = 100000; // mod
    // std::vector<u_int32_t> shares = getAdditiveShares(secret, N, fieldSize);

    // // シェアの表示
    // std::cout << "Shares are: ";
    // for (int i = 0; i < N; i++)
    // {
    //     std::cout << shares[i] << " ";
    // }
    // std::cout << "(mod " << fieldSize << ")" << std::endl;

    // // 秘密値の復元
    // u_int32_t reconstructedSecret = reconstructSecret(shares, fieldSize);
    // std::cout << "Reconstructed secret: " << reconstructedSecret << std::endl;

    // *************** Clientが2つのServerで加算 ***************
    // // シェアの生成
    // u_int32_t secret1, secret2;
    // std::cout << "secret1:";
    // std::cin >> secret1;
    // std::cout << "secret2:";
    // std::cin >> secret2;

    // u_int32_t fieldSize = 100000;
    // std::vector<u_int32_t> shares1 = getAdditiveShares(secret1, 2, fieldSize);
    // std::cout << "Shares of secret1 are: ";
    // for (int i = 0; i < 2; i++)
    // {
    //     std::cout << shares1[i] << " ";
    // }
    // std::cout << "(mod " << fieldSize << ")" << std::endl;
    // std::vector<u_int32_t> shares2 = getAdditiveShares(secret2, 2, fieldSize);
    // std::cout << "Shares of secret2 are: ";
    // for (int i = 0; i < 2; i++)
    // {
    //     std::cout << shares2[i] << " ";
    // }
    // std::cout << "(mod " << fieldSize << ")" << std::endl;

    // printSendMessage("send", "Sending shares...");

    // // 各Partyに送るシェアと、各Partyが以降の処理で使うシェア(*)を表示。返り値として、(*)を返す。
    // std::pair<std::vector<u_int32_t>, std::vector<u_int32_t>> shares_of_each_party = printDistributionWhoSentToWho("Party 1", "Party 2", shares1, shares2);

    // u_int32_t party1_sum_of_shares = shareAddition(shares_of_each_party.first, fieldSize);
    // u_int32_t party2_sum_of_shares = shareAddition(shares_of_each_party.second, fieldSize);
    // std::cout << std::endl;
    // std::cout << "[Party 1] Sum of shares: " << party1_sum_of_shares << std::endl;
    // std::cout << "[Party 2] Sum of shares: " << party2_sum_of_shares << std::endl;

    // printSendMessage("reconst", "Reconst is in progress...");

    // u_int32_t result = (party1_sum_of_shares + party2_sum_of_shares) % fieldSize;
    // std::cout << "***Secret: " << result << " ***" << std::endl;

    // *************** Clientが2つのServerでかけ算(Beaver Multiplication Triples) ***************

    // Beaver Multiplication Triplesによるかけ算は、2-partyプロトコル
    u_int32_t fieldSize = 100;

    // c = a * bとなる3つ組のシェア(a,b,c)を生成。(a,b,c)を2-party間だけで生成する方法もある。
    std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> shares_of_abc = generateTriples(fieldSize);
    std::vector<u_int32_t> shares_a = std::get<0>(shares_of_abc);
    std::vector<u_int32_t> shares_b = std::get<1>(shares_of_abc);
    std::vector<u_int32_t> shares_c = std::get<2>(shares_of_abc);

    for (int i = 0; i < 2; i++)
    {
        std::cout << "Party " << i << ": (a,b,c) = (" << shares_a[i] << ", " << shares_b[i] << ", " << shares_c[i] << ")" << std::endl;
    }

    // 秘密値x,yのシェアを生成
    u_int32_t secret_x, secret_y;
    std::cout << "x(secret): ";
    std::cin >> secret_x;
    std::cout << "y(secret): ";
    std::cin >> secret_y;

    std::vector<u_int32_t> shares_x = getAdditiveShares(secret_x, 2, fieldSize);
    printShares(shares_x, "x", 2, fieldSize);
    std::vector<u_int32_t> shares_y = getAdditiveShares(secret_y, 2, fieldSize);
    printShares(shares_y, "y", 2, fieldSize);

    // ローカルでd,eを計算
    std::vector<u_int32_t> shares_d(2), shares_e(2);
    for (int i = 0; i < 2; i++)
    {
        shares_d[i] = (shares_x[i] - shares_a[i] + fieldSize) % fieldSize;
        shares_e[i] = (shares_y[i] - shares_b[i] + fieldSize) % fieldSize;
    }

    printSendMessage("send", "Sending shares...");
    u_int32_t d = reconstructSecret(shares_d, fieldSize);
    u_int32_t e = reconstructSecret(shares_e, fieldSize);
    std::cout << "*** Reconstructed d and e ***" << std::endl;
    std::cout << "d: " << d << ", e: " << e << std::endl;

    std::vector<u_int32_t> shares_z(2);
    for (int i = 0; i < 2; i++)
    {
        shares_z[i] = (e * shares_a[i] + d * shares_b[i] + shares_c[i]) % fieldSize;
    }
    shares_z[0] += d * e % fieldSize;

    // 結果を復元
    printSendMessage("reconst", "Reconst is in progress...");
    u_int32_t z = (shares_z[0] + shares_z[1]) % fieldSize;
    std::cout << "*** Result: " << z << " ***" << std::endl;

    return 0;
}