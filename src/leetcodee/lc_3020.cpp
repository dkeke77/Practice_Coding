#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
@접근1
    유효한 subset을 만드는 어떤 수들은 하나의 계열을 가짐
     ㄴ 2,4,16,256 ...
    이 계열은 중간부터 시작하여도 유효한 subset를 구성할 수 있음
    단, 유효한 subset은 최상위 수를 제외한 나머지가 2개 이상 있어야 유효해짐
    따라서 해시를 통해 한 계열에 대해 freq를 기록하고, 마지막에 freq를 보면서 최대 길이를 계산하면 될 것으로 보임
    하지만 어떤 숫자가 어떤 계열에 속하는지 빠르게 알 방법이 있어야함
     ㄴ 이것도 해시로 하는게 나을듯
     ㄴ 등장하는 수들이 너무 sparse함
    실행 결과, 196ms(over 8.57%), 146MB(over 5.14%)
    아무래도 등장하는 numFamily 식별을 위한 처리가 오래 걸리는 것으로 보임
     ㄴ 하지만 모든 수들에 대해서 계열 번호를 기록하기엔 10^9는 너무 큼
    그런데 가능한 수들에 대해서 전부 계열 번호를 기록할 필요는 없음
     ㄴ 어차피 subset이 끊기면 별개의 계열로 관리해도 상관이 없음

@접근2
    위 접근에 얻은 관찰을 이용하면 더 간결하게 구현할 수 있음
    모든 수들에 대한 freq를 구하고, 등장했던 수들에 대해 subset 구성을 시도해보면 됨
     ㄴ subset 제일 마지막은 1개, 이외는 전부 2개 이상이도록
    이 때, subset 구성은 최대 5번이므로 그렇게 비싸지 않음
    덕분에 subset의 일부를 다시 중복으로 구성하더라도 그 손실은 크지 않음
    그리고 max를 통해 answer를 업데이트하기 때문에 오염될 여지 또한 없음
    실행 결과, 73ms(over 76.57%), 119MB(over 77.14%)
    확실히 이전 구현보다 훨씬 성능과 메모리 모두 좋아졌음
    계열 해시와 계열 관리가 필요없어졌기 때문으로 보임 
*/

class Solution {
public:
    const int SQR_LIMIT = 31623;
    int maximumLength(vector<int>& nums) {
        int answer = 1;
        int count1 = 0;
        unordered_map<int,int> freqs;

        for (const auto& num : nums)
            freqs[num]++;

        answer = max(answer, freqs[1]-(freqs[1]+1)%2);

        for (const auto& freq : freqs)
        {
            int count = 0;
            int curNum = freq.first;

            if (curNum == 1) continue;

            while(true)
            {
                auto it = freqs.find(curNum);
                if (it == freqs.end())
                    break;
                
                if (freqs[curNum] >= 2)
                {
                    count++;
                    if (curNum < SQR_LIMIT)
                        curNum = curNum*curNum;
                    else
                        break;
                }
                else if (freqs[curNum] == 1)
                {
                    count++;
                    break;
                }
            }
            answer = max(answer, count*2-1);
        }

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}