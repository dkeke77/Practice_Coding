#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    n이 100 미만으로 작기 때문에, 단순하게 브루트 포스로 풀어낼 수 있음
    실행 결과, 0ms(over 100%), 9MB(over 5.46%)
    다른 방법으로는 t의 약수를 구하는 방법이 있겠으나, 이 풀이에선 다루지 않겠음
*/

class Solution {
public:
    int digitMul(int a)
    {
        int result = 1;
        while(a > 0)
        {
            result *= a % 10;
            a /= 10;
        }
        return result;
    }

    int smallestNumber(int n, int t) {
        for(int i=n; i<=max(100,n+9); i++)
        {
            if (digitMul(i) % t == 0)
                return i;
        }
        return -1;
    }
};

int main()
{
    Solution s;

    return 0;
}