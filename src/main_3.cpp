// *************** かけ算(Beaver Multiplication Triples) ***************
// (Beaver Multiplication Triplesによるかけ算は、2-partyプロトコル)

#include "main_3.hpp"
#include "gen_and_rec_shares.hpp"
#include "print_communication_content.hpp"
#include "beaver_triple_sub_function.hpp"
#include <iostream>

int main_3()
{
    u_int32_t fieldSize = 1000; // あんまり大きいと、a*bがオーバーフローする (generateTriples内で生成する乱数の幅をfieldSize-1(現在)から適宜変えたらOK)

    // c = a * bとなる3つ組のシェア(a,b,c)を生成。(a,b,c)を2-party間だけで生成する方法もある。
    std::tuple<std::vector<u_int32_t>, std::vector<u_int32_t>, std::vector<u_int32_t>> shares_of_abc = generateTriples_old(fieldSize);
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

    // 各パーティが最終的に持つシェアを表示
    std::cout << std::endl;
    std::cout << "*** Each party has share of result ***" << std::endl;
    std::cout << "Party 1: " << shares_z[0] << ", Party 2: " << shares_z[1] << std::endl;
    std::cout << std::endl;

    // 結果を復元
    printSendMessage("reconst", "Reconst is in progress...");
    u_int32_t z = (shares_z[0] + shares_z[1]) % fieldSize;
    std::cout << "*** Result: " << z << " ***" << std::endl;

    return 0;
}