#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    단순하게 포인터를 이용하여 word2의 문자를 word1에서 하나씩 찾아내는 것은 정답을 보장하지 않음
    왜냐하면 최대 1개의 문자를 수정할 수 있기 때문임
    하지만 word2의 각 문자가 수정되는 경우를 따지면서 처리하면 n1*n2가 발생할 것
    때문에 다른 접근을 사용하는 것이 적당함
    먼저 word1를 순회하며 각 문자가 어느 인덱스들에서 등장했는지 기록
    그리고 그것을 기반으로 result를 구성하는 것
     ㄴ 먼저 이전 등장 문자의 인덱스보다 크도록 각 문자에 대한 인덱스를 채워넣음
     ㄴ 만약 등장하지 않은 문자는 1번만 -1로 기입
        ㄴ 2번 이상 등장하면 즉시 빈 vector 반환
     ㄴ 그리고 문자 수정을 수행함
        ㄴ -1인 문자 수정을 우선하고, 만약 없다면 가능한 제일 앞의 문자를 수정
     ㄴ 그리고 수정한 문자 이후 구간만 다시 result 재구성
    그런데 이 방법은 vbcca/abc와 같이 앞의 문자가 훨씬 뒤에 등장하는 경우를 해결하진 못함
    이 문제는 의외로 더 복잡한데, 앞의 문자가 수정해야하는지, 혹은 뒤의 문자를 수정해야하는지 판단해야됨
     ㄴ bacdc/abc의 경우엔 뒤의 문자를 수정하는 것이 맞음
    따라서 현재 접근은 이 문제를 풀 수 없음

    풀이를 본 결과, suffix를 이용하여 접근했어야 했음
    각 suffix에서 수정없이 일치하는 문자들의 개수를 기록해둠
    이를 통해, 현재 수정을 해야할지 판단할 수 있음
     ㄴ 이는 word1의 남은 문자열에 대해, 수정없이 남은 word2의 문자를 표현할 수 있는지 평가할 수 있음
     ㄴ 즉, 현재 문자가 일치하지 않는 상황에서, 후의 suffix에서 수정없이 남은 문자를 표현 가능하다면 수정하는 것이 유망함
     ㄴ 반면 suffix에서 수정없이 표현이 불가능하다면, 수정하여도 아무 영향을 주지 못하므로 수정할 필요가 없음
    또한 문자가 일치하면 바로 정답 vector에 추가하고, 일치하지 않는 경우에만 수정에 대한 평가를 시행함
    그리고 수정하는 것이 유망해지는 즉시 바로 수정을 시행함
    이를 통해 사전순으로 제일 작은 시퀸스를 생성할 수 있음
     ㄴ 일치하는 경우에 바로 추가하며, 수정 가능할때 바로 추가하기 때문에 자연스럽게 가능한 제일 앞의 인덱스로만 구성됨
    실행 결과, 45ms(over 54.26%), 107MB(over 57.45%)
*/

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        const int n1 = word1.length();
        const int n2 = word2.length();

        vector<int> suffixMatch(n1);
        int ptrW2 = n2-1;
        int countMatch = 0;
        for (int i=n1-1; i>=0; i--)
        {
            suffixMatch[i] = countMatch;
            if (ptrW2 >= 0 && word1[i] == word2[ptrW2])
            {
                countMatch++;
                ptrW2--;
            }
        }
        
        vector<int> result;
        result.reserve(n2);
        bool changed = false;
        ptrW2 = 0;

        for (int i=0; i<n1; i++)
        {
            if (word1[i] == word2[ptrW2])
            {
                result.push_back(i);
                ptrW2++;
            }
            else
            {
                if (!changed && suffixMatch[i] >= n2 - ptrW2 - 1)
                {
                    result.push_back(i);
                    ptrW2++;
                    changed = true;
                }
            }

            if (ptrW2 == n2)
                return result;
        }
        
        return {};
    }
};

int main()
{
    Solution s;

    for (auto a : s.validSequence("vbcca", "abc"))
        cout << a << " ";
    cout << endl;

    return 0;
}