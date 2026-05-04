#include <vector>
#include <iostream>

using namespace std;

/*
@접근
    goal에서 s의 첫번째 문자를 탐색
    탐색된 인덱스부터, goal을 circular 스캔하며 각 문자별 s와 일치 여부 평가
    끝까지 일치한다면 true, 아니라면 false
    
    그러나 첫번째 문자가 goal에 여러 개 존재할 수 있는 케이스를 잘 처리하지 못함
    따라서 goal 내에 존재하는 모든 첫번째 문자를 탐색하고 각 인덱스를 저장
    그리고 저장된 인덱스에 대해 s와의 일치성을 평가함
    그 결과, 테스트 통과 성공
    0ms(over 100%), 8MB(over 84.78%)

    KMP처럼 fallback을 보다 정교하게 한다면 더 빠른 성능을 가져올 것으로 기대되나,
    각 문자열의 길이가 최대 100이기에 그 차이는 미미할 것으로 예상됨
    본 알고리즘의 시간복잡도는 O(s*goal) (s,goal은 각 문자열의 길이)
    KMP 방식으로 하면 O(s+goal)로 예상됨

    gpt는 이 문제는 s 문자열을 2개 이어붙이고, 이어붙인 문자열에서 goal을 탐색하는 것이 정석이라고 함
    이는 꽤나 명쾌한 해법이지만, 공간복잡도를 크게 늘릴 가능성이 있으며, circular 탐색으로 충분하다고 생각됨

    lc_3008_2에서 사용한 KMP를 적용해본 결과, 큰 차이는 없었음
*/

class Solution {
public:
    bool rotateString(string s, string goal) {
        vector<int> candidate;

        if (goal.size() != s.size())
            return false;

        for (int i = 0; i < goal.size(); ++i)
        {
            if (goal[i] == s[0])
                candidate.push_back(i);
        }
        if (candidate.empty())
            return false;

        for (const auto& startIdx : candidate)
        {
            bool isEqual = true;
            for (int i = 0; i < s.size(); ++i)
            {
                if (goal[(startIdx+i) % goal.size()] != s[i])
                {
                    isEqual = false;
                    break;
                }
            }
            if (isEqual)
                return true;
        }

        return false;
    }
};

int main()
{
    Solution s;

    cout << s.rotateString("abcde","cdeab") << endl;

    return 0;
}