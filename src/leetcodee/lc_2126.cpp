#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
@풀이
    아무래도 오름차순 정렬하고 순차적으로 더해가며 시뮬레이션하면 될듯?
    10^5라서 nlogn+n하면 대충 10*n 이하로 나온다고 생각됨
    그리고 전부 합하면 최대 10^10이 될텐데, 32비트로 다 표현하지 못할 수 있음
    따라서 long long을 쓰는 것이 맞음
    실행 결과, 33ms(over 54.06%), 107MB(over 81.83%)

@개선
    조금 더 빠른 풀이를 생각해본다면 다음과 같은 방법이 있음
    1차 순회를 돌며 당장 합칠 수 있는 것들만 합치고 아닌 것은 따로 모아둠
    그리고 남은 것들에 대해서만 정렬을 하거나 아니면 반복적으로 1차 순회때 했던 것처럼 할 수 있음
    그러나 이 방법은 그렇게 효율적인지 모르겠음
    아니면 pq에 남은 것들을 따로 모음과 동시에, 순회 시 기회가 될때마다 합치는 방법도 있음
    내림차순으로 정렬되어있다면 최악의 경우, nlogn이 나오겠지만 평균은 그보다 낮을 것
     ㄴ 아마 5n? 정확히 추정하긴 어렵다고 생각됨
    실행 결과, 19ms(over 94.46%), 109MB(over 8.12%)
    확실한 성능 향상을 볼 수 있었음
    또한 pq를 int에서 long long으로도 바꿔본  결과, 109MB->11MB로의 메모리 증가가 확인됨
    static_cast를 안쓰려면 1LL*를 붙이거나 마음 편하게 2MB 더 쓴다고 생각해도 좋을듯

    다른 풀이법으로는 소행성의 크기 별 등장회수를 기록하고, 나중에 소행성 크기 배열을 순회하는 것임
    소행성의 크기 분포가 좁을수록 더 빠를 것으로 예상됨
*/

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        long long sum = mass;
        priority_queue<int,vector<int>,greater<int>> pq;

        for (long long as : asteroids)
        {
            if (sum < as)
                pq.push(as);
            else
                sum += as;
            
            while(!pq.empty() && pq.top() <= sum)
            {
                sum += 1LL * pq.top();
                pq.pop();
            }
        }

        if (pq.empty())
            return true;
        else
            return false;
    }
};

int main()
{
    Solution s;

    return 0;
}