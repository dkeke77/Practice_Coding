#include <vector>
#include <iostream>

using namespace std;

/*
@문제
    조건을 만족하는 숫자들을 찾기
    그 숫자는 문자열 s의 인덱스
    문자열 s에 포함되는 문자열 a을 찾고, 그 시작 인덱스 i.
    그리고 마찬가지로 s에 포함되는 문자열 b을 찾고, 그 시작 인덱스 j.
    이 두 인덱스 i와 j에 대해 |j-i| <= k를 만족하는 i들을 찾기
     ㄴ 문제의 조건1~4 전부 문자열 a와 문자열 b가 문자열 s에 포함된다는 의미임

@접근
    정석적인 KMP 구현을 목표했음
    KMP는 핵심은 문자열의 각 인덱스에서 불일치가 발생하면, 어디로 fallback할 것인지 알려주는 p배열임
    이 p배열은 부분 문자열(0~인덱스)의 prefix와 suffix가 얼마나 겹치는지 알려줌
    즉, p배열을 만드는 데 prefix와 suffix를 확인해야함
    그리고 KMP로 s 내 a,b 문자열의 시작지점을 알아도, 최종 정답은 b 시작리스트를 탐색해야함
    이 때, 단순히 탐색하면 O(a*b)만큼 걸리게 됨
    따라서 b를 이진탐색하여야 O(a*log(b))정도로 줄어들게 됨

@실패1
    이진탐색 구현을 잘못하고 있었음
    우선 ptrR가 size()이면, 최악의 경우에 범위를 벗어나는 인덱스 참조가 발생할 것이라고 생각함
    그러나 실제로는 발생하지 않는데, mid = (ptrL + ptrR) / 2에서 size()가 나올 수 있는 경우는 ptrL,ptrR 둘다 size()인 경우임
    하지만 그런 경우엔 이미 while의 조건문에 의해 반복문에서 나온 상태이기에 발생할 가능성이 없음
    또한 ptrL을 재조정할때, mid+1이 아닌 mid로 하여 무한반복이 발생하는 경우도 있었음

@실패2
    KMP에서 p배열을 생성할때, p배열을 이용하지 않고 일일히 비교하며 생성함
    때문에 O(l^3)만큼의 시간복잡도가 발생하여 시간초과가 발생했었음
    따라서 이를 해결하기 위해 p배열을 생성할때도 p배열을 이용하여 만들도록 함
    prefix와 suffix는 겹치지 않는다는 잘못 인식하기도 했으나, prefix와 suffix는 겹칠 수 있음
    
    우선 직전 p가 0이었으면 prefix와 suffix가 줄곧 겹치지 않았다는 의미임
    따라서 현재 문자가 첫번째 문자와 동일한지 여부만 검사하면 됨
    만약 0이 아니라면 현재 문자와 p가 가르키는 문자가 동일한지 검사하면 됨
    만약 동일하다면, 이전 prefix가 계속 이어진다는 의미임
    만약 다르다면 일치하는 prefix를 찾아야함

@성공
    첫번째 성공은 다르다면 p를 0으로 하는 것이었음
    하지만 이는 잘못된 구현이지만 운좋게 테스트케이스를 통과한 것임
    만약 aabbaacaabbaab와 같은 케이스에서 잘못될 수 있음
    따라서 다르다면 일치하는 prefix를 찾아야함

    두번째 성공은 일치하는 prefix를 이전처럼 일일히 비교해가며 찾았음
    72ms(over 70.73%), 90MB(over 93.29%)를 기록함
    해당 탐색이 자주 발생하지 않는 점과, 탐색 범위를 p만큼으로 줄였기에 그렇게 느리진 않았던 것으로 보임

    세번째 성공은 일치하는 prefix를 p배열을 이용하여 찾았음
    61ms(over 84.76%), 90MB(over 83.54%)를 기록함
    해당 방법이 유효한지 몰라 다른 사람의 구현을 참고했음
    이 방법이 유효한 이유는 다음과 같음
    우선 직전까지 prefix와 suffix는 계속 일치했으나, 새로 들어온 문자로 인해 일치하지 않게 됨
    그러면 p배열을 이용하여 현재 prefix에서 과거 찾았던 prefix를 가져올 수 있음
     ㄴ 현재 prefix는 곧 과거에 p배열 계산에 쓰였던 부분 문자열임
    그리고 그 prefix 다음과 새로 들어온 문자를 비교하여 prefix가 이어질 수 있는지 평가함
    만약 아니라면 다시 p배열을 참조하여 과거의 prefix를 가져오길 반복함
    끝까지 일치하는 prefix를 발견 못하여 0이 된다면, p가 0일때와 동일하게 처리하면 됨
    
    위 로직만 이용하여 p배열을 만들 수 있으나, 직전 p가 0인지 먼저 검사하는 방식이 더 빨랐음
    아무래도 유망하지 않은 경우를 빠르게 제외할 수 있기 때문으로 보임
*/

struct KMP
{
    KMP(string& s) : str(s), p(s.length(),0), pointer(0)
    {
        for (int i = 1; i < s.length(); ++i)
        {
            if (p[i-1] == 0)
            {
                if (s[i] == s[0])
                    p[i] = 1;
            }
            else
            {
                int prefixP = p[i-1];
                while(prefixP > 0 && str[prefixP] != str[i])
                {
                    prefixP = p[prefixP-1];
                }
                if (str[prefixP] == str[i])
                {
                    p[i] = prefixP + 1;
                }
            }
        }
    }

    bool advance(char c)
    {
        if (str[pointer] == c)
            pointer++;
        else if (pointer > 0)
        {
            pointer = p[pointer-1];
            while(pointer > 0)
            {
                if (str[pointer] == c)
                {
                    pointer++;
                    break;
                }
                else
                    pointer = p[pointer-1];
            }
            if (pointer == 0 && str[0] == c)
                pointer++;
        }

        if (pointer >= str.length())
        {
            pointer = p[pointer-1];
            return true;
        }
        else
            return false;
    }

    const string& str;
    vector<int> p;
    int pointer = 0;
};

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> result;
        vector<int> rA;
        vector<int> rB;

        KMP kmpA(a);
        KMP kmpB(b);

        for (int i = 0; i < s.length(); ++i)
        {
            if (kmpA.advance(s[i]))
                rA.push_back(i - a.length() + 1);
            if (kmpB.advance(s[i]))
                rB.push_back(i - b.length() + 1);
        }

        for (const auto& elemA : rA)
        {
            if (rB.size() > 0)
            {
                int ptrR = rB.size();
                int ptrL = 0;

                while (ptrR != ptrL)
                {
                    int mid = (ptrL + ptrR) / 2;

                    if (abs(elemA - rB[mid]) <= k)
                    {
                        result.push_back(elemA);
                        break;
                    }
                    else if(elemA < rB[mid])
                        ptrR = mid;
                    else
                        ptrL = mid+1;
                }
            }
        }

        return result;
    }
};

int main()
{
    Solution s;

    // auto r1 = s.beautifulIndices("isawsquirrelnearmysquirrelhouseohmy", "my", "squirrel", 15);
    // for (auto q : r1)
    //     cout << q << " ";
    // cout << endl;

    auto r2 = s.beautifulIndices("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaa", "aaaaaaaaaaaaaaaaa", 5000);
    for (auto q : r2)
        cout << q << " ";
    cout << endl;

    // auto r3 = s.beautifulIndices("lrtsi", "lrts", "i", 3);
    // for (auto q : r3)
    //     cout << q << " ";
    // cout << endl;

    return 0;
}