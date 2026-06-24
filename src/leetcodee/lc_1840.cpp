#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    휴리스틱하게 풀 수 있지 않나 생각됨
    주어지는 높이 제한을 앞에서부터 처리하면서 진행할 수 있지 않을까?
    i~j번 건물을 처리한다고 가정하자
    그러면 i번 건물의 높이 h부터 시작하여 j번 건물의 높이 제한 r에 도달하게 될것
    j-i의 크기에 따라 증가할 수 있는 범위 또한 정해짐
    이를 r과 함께 따져보면 그 사이의 최대 높이를 유추할 수 있을 것
     ㄴ 계속 증가/감소해도 되거나, 혹은 증가하다가 중간부터 감소하거나.

    하지만 이전에 결정지은 i번 건물의 높이에서 j번 건물의 r을 충족시킬 수 없다면?
     ㄴ j-i < r-h
    그렇다면 i번 건물의 높이를 수정해야만 할 것이고, 이는 단순히 앞에서부터 처리하면 진행하는 것이 불가능함을 의미
     ㄴ 이전의 결정을 앞에서 계속 수정해야되기 때문
     ㄴ 이는 뒤에서부터 진행하더라도 동일한 문제를 가짐
    하지만 n이 10^9이기에 O(n)을 충족해야함
    하지만 r의 개수가 최대 10^5이기에 r을 기준으로 처리하면 O(nlogn)도 가능함
    그렇다면 r을 수정하는 방법은 어떨까?
     ㄴ r[i]과 r[j]을 비교하여 불가능한 r을 감소시키는 느낌
     ㄴ 하지만 초기의 아이디어와 크게 다른 점이 없음

    혹은 최대 높이가 h였다면 h-1도 가능하므로 파라메트릭 탐색도 가능함
    해공간은 최대 10^9이므로 log(10^9)*10^5로 생각할 수 있음
    하지만 해 검증 과정이 좀 명확하지 않음

    DP를 이용하는 방법은 어떨까?
    그렇다면 어떤 정보를 저장할지 고르는 것이 중요함
     ㄴ 각 높이를 저장하는 것은 확실하겠지만, 최대 높이가 10^9이기에 좀 빡셈

    사실상 풀이를 알려준 힌트를 보고서야 r를 직접 수정하는 방안이 정답이라는 것을 앎
     ㄴ 앞과 뒤, 총 2번 진행하며 수정
    그런데 이것이 왜 성립할 수 있는지 고민해본 결과, 다음과 같은 결론을 내렸음
    수정된 r은 의미가 변화하여 인접한 r끼리 연결될 수 있는 경우가 최소 1개 이상 존재한다는 것
    이 의미는 모든 r에게 전파되어, 단순히 인접한 r간의 최고 높이만 생각하여도 되게 함
    하지만 처음 생각했던 앞 혹은 뒤, 한쪽으로만 진행하면 안되는 이유는 각각 증가/감소를 검사하게 되는 것
     ㄴ 보다 자세하겐, 앞으로 진행하면 불가능한 r를 감소시키는 행위는, 높이가 증가하는 경우를 처리하는 것
     ㄴ 마찬가지로 뒤에서 진행하는 것은 높이가 감소하는 경우를 처리하는 것임
     ㄴ 즉, 앞과 뒤를 순회하며 r를 감소시키면, 증가/감소로 도달 가능한 r로 수정하게 되는 것
    
    실행결과, 39ms(over 93.06%), 107MB(over 38.89%)
    이전 건물의 높이를 기준으로 처리하려고 했던 것에서 벗어나지 못해서 정답에 도달하지 못했던것같음
*/

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        if (restrictions.empty())
            return n-1;

        sort(restrictions.begin(),restrictions.end(),
            [](vector<int>& a, vector<int>& b){ return a[0] < b[0]; }
        );

        int prevNum = 1;
        int prevRstr = 0;
        for (auto it=restrictions.begin(); it!=restrictions.end(); it++)
        {
            auto& curNum = (*it)[0];
            auto& curRstr = (*it)[1];

            int diff = curNum - prevNum;

            if (curRstr >= prevRstr+diff)
                (*it)[1] = prevRstr+diff;

            prevNum = curNum;
            prevRstr = curRstr;
        }

        for (auto it=restrictions.rbegin(); it!=restrictions.rend(); it++)
        {
            auto& curNum = (*it)[0];
            auto& curRstr = (*it)[1];

            int diff = prevNum - curNum;

            if (curRstr > prevRstr+diff)
                (*it)[1] = prevRstr+diff;

            prevNum = curNum;
            prevRstr = curRstr;
        }

        int maxH = 0;
        prevNum = 1;
        prevRstr = 0;
        for (auto it=restrictions.begin(); it!=restrictions.end(); it++)
        {
            auto& curNum = (*it)[0];
            auto& curRstr = (*it)[1];

            int diff = (curNum-prevNum) - abs(curRstr-prevRstr);
            int localMaxH = max(curRstr,prevRstr);
            localMaxH += diff/2;
            maxH = max(maxH,localMaxH);

            prevNum = curNum;
            prevRstr = curRstr;
        }
        maxH = max(maxH, prevRstr + n - prevNum);

        return maxH;
    }
};

int main()
{
    Solution s;

    return 0;
}