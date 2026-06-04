#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@풀이
    내림차순 정렬 후, 배열의 크기가 3의 배수에 맞게 뒤에 0을 추가
     ㄴ 차후 남은 사탕 처리를 간단하게 하기 위함
    그 후, 3개씩 끊어가며 앞의 2개만 answer에 가산
    시간 복잡도는 O(nlogn)임
    실행 결과, 0ms(over 100%), 14MB(over 49.81%)
    n이 최대 100 이하라서 어떻게 짜도 빠르게 나올 것으로 보여짐

    이 문제도 counting sort를 적용하면 더 좋은 시간복잡도를 가질 것으로 보여짐
    하지만 굳이라는 생각이 듦
*/

class Solution {
public:
    int minimumCost(vector<int>& cost) {
        int answer = 0;
        sort(cost.begin(),cost.end(),[](int a, int b){return a>b;});

        while(cost.size() % 3 != 0)
            cost.push_back(0);

        for (int i=0; i<cost.size(); i+=3)
            answer += cost[i] + cost[i+1];

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}