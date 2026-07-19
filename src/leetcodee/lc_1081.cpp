#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    스택을 써서 문자열을 구성하자
    원본 str의 앞부터 한문자씩 스택에 넣되, 자신보다 뒷 문자이면 계속 pop
    하지만 해당 문자가 앞으로 더 없다면 pop 종료
    그리고 자신과 동일한 문자가 이미 들어갔었더라면 pop/push를 아예 생략
    실행 결과, 0ms(over 100%), 9MB(over 94.04%)

    되는대로 막 만들었는데, 의외로 통했음
    아무래도 가능한 제일 빠른 문자가 앞에 유지되는 것으로 보임
     ㄴ 만약 지금 문자가 앞에 있는 문자보다 크다면, 앞 문자를 뺄 이유가 없음
     ㄴ 그러나 지금 문자가 더 작다면, 앞 문자를 빼는 것이 더 이득임
     ㄴ 물론 앞 문자가 뒤에 더 나오지 않는다면, 빼서는 안됨
    또한 앞 문자를 무시하고 더 앞을 확인할 수 없기 때문에, 스택이 맞는 자료구조임
    이에 따라 당장 현재 앞 문자만 확인하면 됨
*/

class Solution {
public:
    string smallestSubsequence(string s) {
        string answer = "";
        vector<int> freq(26,0);
        vector<bool> freqAns(26,false);

        for (const auto& c : s)
            freq[c - 'a']++;
        
        for (const auto& c : s)
        {
            if (!freqAns[c - 'a'])
            {
                while(!answer.empty())
                {
                    if (answer.back() < c || freq[answer.back() - 'a'] == 0)
                        break;
                    freqAns[answer.back() - 'a'] = false;
                    answer.pop_back();
                }

                answer.push_back(c);
                freqAns[c - 'a'] = true;
            }
            
            freq[c - 'a']--;
        }

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}