#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    trie를 써도 되겠지만, 과하다란 생각이 들음
    최악의 경우라도 p*n*l에 불과하므로 단순하게 string 내장함수로만 하여도 문제 없을 것으로 보임
    실행 결과, 0ms(over 100%), 12MB(over 98.30%)
    성능이 더 빠른 구현법은 충분히 많겠지만, 그 어떤 방법도 이보다 간결할 수 없을 것으로 생각됨
    더욱이 케이스가 작은 이 문제에선, 그 성능 차를 확인하기 어렵기 때문에 이 방법이 최적은 아닐지라도 적절하다고 판단됨
*/

class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int answer = 0;

        for (const auto& p : patterns)
            if (word.find(p) != string::npos) answer++;

        return answer;
    }
};
int main()
{
    Solution s;

    return 0;
}