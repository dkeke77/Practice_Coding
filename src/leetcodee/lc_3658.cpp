#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    단순하게 sumOdd와 sumEven을 구하고, 이의 GCD를 구하면 끝
    실행 결과, 0ms(over 100%), 8MB(over 85.02%)
    c++17이라면 std::gcd로 더 간결하게도 가능
*/

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int a = n * n + n;
        int b = n * n;

        while(a % b != 0)
        {
            int temp = a % b;
            a = b;
            b = temp;
        }

        return b;
    }
};

int main()
{
    Solution s;

    return 0;
}