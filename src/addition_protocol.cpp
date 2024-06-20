#include "addition_protocol.hpp"

std::vector<u_int32_t> Add(std::vector<u_int32_t> shares1, std::vector<u_int32_t> shares2, u_int32_t fieldSize){
    std::vector<u_int32_t> result(2);
    for(int i = 0; i < 2; i++)
    {
        result[i] = (shares1[i] + shares2[i] )% fieldSize;
    }
    return result;
}
    