#include <vector>
#include <iostream>

using namespace std;

/*
@접근
    단순히 비트별로 확인하면 끝임
    그런데 1비트 오른쪽 시프트하고 이를 비교하는 방법도 있음
     ㄴ (n>>1)^n+1 시, 제일 앞 다음 비트를 제외하고 0이 됨
     ㄴ 이를 원본 n과 &하여 0이 나오는지 검사하는 방식
    하지만 그렇게 할 경우, 오버플로우에 유의해야할것
*/

class Solution {
public:
    bool hasAlternatingBits(int n) {        
        while(n >> 1)
        {
            if ((n>>1)&1 ^ n&1)
                n >>= 1;
            else
                return false;
        }
        
        return true;
    }
};

int main()
{
    Solution s;

    return 0;
}
