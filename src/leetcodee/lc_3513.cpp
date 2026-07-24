#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
@접근
    a XOR b XOR c 구조에서 유효한 a XOR b를 미리 계산해두고, 이 결과를 다시 사용하는 접근?
    하지만 이 접근도 결국 해당 사전배열을 구하는데 n^2이 발생하고, 이를 사용하여 다시 사용하는 것도 n^2이 발생함
    왠지 느낌상 수학적 규칙에 따른 것으로 예상됨

    힌트에 따르면 0~2^(msb(n)+1)-1 사이의 모든 수가 나온다고 함
     ㄴ 즉, 해당 최상위 비트 내의 모든 수
    일단 XOR 간 순서는 상관 없으므로, 순서는 신경을 쓰지 않아도 됨
     ㄴ a^b^c == c^b^a == b^c^a == ...
    그리고 XOR된 결과에 대해 생각해보면, 두 수를 분해한 것이라고 생각할 수 있음
     ㄴ 10110은 10000 ^ 00110의 결과
    따라서 1~n까지의 숫자가 모두 등장하기 때문에, 최상위 비트 내의 모든 수는 조립 가능한 상태임
    다만 XOR이 한번만 수행된다면 1인 비트가 1개인 숫자는 조립할 수 없으나, 두번 수행되므로 가능함
    그리고 n이 2 이하인 케이스는 서로 다른 세 수를 경우가 없으므로 따로 처리해줘야함
     ㄴ 이 때문에 중복된 수는 2번 XOR하여 소멸되고, 나머지 한 수만 남게 됨
    실행 결과, 0ms(over 100%), 199MB(over 98.14%)
*/

class Solution {
public:
    int msb(int a)
    {
        int m = 0;
        while(a > 0)
        {
            a >>= 1;
            m++;
        }
        return m-1;
    }
    int uniqueXorTriplets(vector<int>& nums) {
        const int n = nums.size();
        if (n <= 2) return n;

        return (2 << msb(n));
    }
};



int main()
{
    Solution s;

    return 0;
}