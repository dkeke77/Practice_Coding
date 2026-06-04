#include <vector>
#include <iostream>

using namespace std;

/*
@풀이
    브루트포스로 각 숫자에 대해 처리하면 됨
    각 자릿수를 분할하고, 그 자릿수마다 peak와 valley 여부를 판별하면 됨
    시간 복잡도는 O(n) : 널널하게 상한을 잡으면 8n정도 나온다고 봄
    실행 결과, 3ms(over 96.08%), 9MB(over 90.30%)
    실행시간은 최대 7ms까지 나옴

    다른 풀이로는 DP와 prefix sum을 이용한 방법이 있음
    미리 가능한 모든 케이스의 waviness를 계산해두는데, 여기에 dp를 활용함
    먼저 3자리수에 대해 waviness를 계산해두면, 4자리수에 대해 계산할때 활용할 수 있음
    그리고 마찬가지로 5자리수에서도 4자리와 3자리를 활용할 수 있음
    그리고 prefix sum으로 dp를 합산해두고, 메인 로직에서 prefix sum 간의 차로 구간합을 반환함
*/

class Solution {
public:
    const int DIGIT_DIV[5] =
    { 1, 10, 100, 1000, 10000 };

    int calcWaviness(int num1, int num2, int digit)
    {
        int arr[5] = {};
        int result = 0;

        int start = max(num1,DIGIT_DIV[digit-1]);
        int end = min(num2,DIGIT_DIV[digit-1]*10-1);

        for (int i=start; i<=end; ++i)
        {
            for (int j=0; j<digit; ++j)
                arr[j] = i / DIGIT_DIV[j] % 10;

            for (int j=1; j<digit-1; ++j)
            {
                if (arr[j] > arr[j-1] && arr[j] > arr[j+1])
                    result++;
                else if (arr[j] < arr[j-1] && arr[j] < arr[j+1])
                    result++;
            }
        }

        return result;
    }

    int totalWaviness(int num1, int num2) {
        
        int result = 0;

        result += calcWaviness(num1, num2, 3);
        result += calcWaviness(num1, num2, 4);
        result += calcWaviness(num1, num2, 5);        

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}