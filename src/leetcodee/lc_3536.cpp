#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    각 숫자들의 freq를 확인한 뒤, freq 배열의 뒤에서부터 큰 숫자 2개를 고르면 됨
    실행 결과, 0ms(over 100%), 9MB(over 59.37%)
    혹은 각 숫자들을 벡터에 push 및 정렬한 다음에, 제일 뒤의 2개 숫자만 확인하는 것도 방법임
*/

class Solution {
public:
    int maxProduct(int n) {
        vector<int> freq(10, 0);

        while(n > 0)
        {
            freq[n%10]++;
            n /= 10;
        }

        int answer = 1;
        int mulCount = 0;
        int ptr = 9;
        while (mulCount < 2)
        {
            if (freq[ptr] > 0)
            {
                answer *= ptr;
                mulCount++;
                freq[ptr]--;
            }
            else
                ptr--;
        }

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}