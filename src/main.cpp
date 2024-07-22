#include "main_1.hpp"
#include "main_2.hpp"
#include "main_3.hpp"
#include "main_4.hpp"
#include "main_5.hpp"
#include <iostream>

int main()
{
    int choose_process;
    std::cout << "1: n-partyでシェアの生成と復元" << std::endl;
    std::cout << "2: 加算" << std::endl;
    std::cout << "3: かけ算(Beaver Multiplication Triples)" << std::endl;
    std::cout << "4: かけ算(動作確認)" << std::endl;
    std::cout << "5: 大小比較" << std::endl;
    std::cout << "Choose process: ";
    std::cin >> choose_process;

    switch (choose_process)
    {
    case 1:
        main_1(); // main1.cppに記載
        break;
    case 2:
        main_2(); // main2.cppに記載
        break;
    case 3:
        main_3(); // main3.cppに記載
        break;
    case 4:
        main_4(); // main4.cppに記載
        break;
    case 5:
        main_5(); // main5.cppに記載
        break;
    default:
        std::cout << "Invalid option." << std::endl;
        break;
    }

    return 0;
}