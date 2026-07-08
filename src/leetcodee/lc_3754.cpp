#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    하라는대로 로직 작성하면 됨
    실행 결과, 0ms(over 100%), 9MB(over 89.09%)
*/

class Solution {
public:
    long long sumAndMultiply(int n) {
        int nonZero = 0;
        int digit = 1;
        int sum = 0;
        
        while(n > 0)
        {
            if (n % 10 != 0)
            {
                nonZero += digit * (n%10);
                sum += n%10;
                digit *= 10;
            }
            n /= 10;
        }

        return 1LL * nonZero * sum;
    }
};

int main()
{
    Solution s;

    return 0;
}