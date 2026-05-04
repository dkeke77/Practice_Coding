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
    무조건 문자열 s를 순회하며 문자열 a,b를 식별해내야함
    구조체를 만들어, a,b에 대한 문자열 체크를 스트리밍으로 진행하도록 함
    내부 인덱스가 존재해 문자열에 대한 한 문자를 가르킴
    이 때, 입력받은 문자와 현재 인덱스의 문자가 일치하면 내부 인덱스가 이동함
    만약 아니라면 0으로 돌아감
     ㄴ 돌아간 후, 입력받은 문자가 문자열의 시작 문자와 일치하면 인덱스 이동
    
    이렇게 한 이후, 문자열의 앞뒤가 겹쳐지는 경우에 문제가 발생하는 것을 확인함
    예를 들어, ababa의 경우엔 ababababa에서 0,2가 나와야 함
    그러나 문자열 일치 후, 인덱스가 0으로 돌아가기 때문에 이런 문제가 발생함
    따라서 일치 후 0으로 돌아가지 않고, 생성자에서 일치 시 돌아갈 인덱스를 계산하여 저장
    돌아갈 인덱스는 앞에서부터 겹쳐짐을 따졌을 때, 더이상 겹쳐지지 않기 시작하는 지점임
     ㄴ 위 예시의 경우, 돌아갈 인덱스는 2이어야함
    해당 문제 수정 후, 모든 테스트 케이스를 통과함
     ㄴ 60ms(over 84.76%) / 75MB(over 99.39%)로 준수하게 나옴
    
    하지만 이 풀이엔 2가지 문제점이 있음
    1) 단일 j만 사용하기에, 이전 j였으면 통과될 케이스가 j의 덮어쓰임으로 인해 통과하지 못 할 수 있음
        ㄴ a의 길이가 50, b의 길이가 10, i=100, j=90,130, k=20인 경우가 그 반례임
        ㄴ 따라서 j를 더 이상 유효하지 않을 때까지 저장할 필요가 있음
    2) 불일치 발생시, 무조건 인덱스 0 혹은 1로 돌아가면 안됨
        ㄴ s가 aaaaaaab, a가 aaab인 상황에서 제대로 동작되지 않음
        ㄴ 따라서 fallback이 입력에 따라 다를 필요가 있음
    
    위 2가지 문제를 해결한 결과, 112ms(over 29.88%) / 79MB(over 98.17%)로 성능이 크게 감소함
    정석 풀이법인 KMP 방법도 나중에 도전해보는 것이 좋아보임
*/

struct AutoEvaluator
{
    AutoEvaluator(string& s) : str(s), index(0), nonOverlapped(0)
    {
        int maxIdx = 0;
        for (int i = 1; i < str.length(); ++i)
        {
            bool flag = true;
            for (int j = 0; j < str.length()-i; ++j)
            {
                if (str[i+j] != str[j])
                {
                    flag = false;
                    break;
                }
            }

            if (flag)
            {
                nonOverlapped = str.length()-i;
                break;
            }
        }
    }

    const string& str;
    int index = 0;
    int nonOverlapped;

    bool evaluate(char c)
    {
        
        bool flag = str[index] == c;
        if (str[index] == c)
        {
            index++;
            if(index == str.length())
            {
                index = nonOverlapped;
                return true;
            }
        }
        else
        {
            for (int i = index-1; i >= 0; --i)
            {
                if (str[i] == c)
                {
                    bool flag = true;
                    for(int j = 1; j <= i; ++j)
                    {
                        if (str[index-j] != str[i-j])
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (flag)
                    {
                        index = i+1;
                        return false;
                    }
                }
            }
            index = 0;
        }
        return false;
    }
};

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> result;
        vector<int> candidate;
        vector<int> listJ;
        AutoEvaluator autoA(a);
        AutoEvaluator autoB(b);

        int pointerI = 0;
        int pointerJ = 0;

        for (int idx = 0; idx < s.length(); ++idx)
        {
            if (autoA.evaluate(s[idx]))
                candidate.push_back(idx - a.length() + 1);

            if (autoB.evaluate(s[idx]))
                listJ.push_back(idx - b.length() + 1);

            for (int u = pointerI; u < candidate.size(); ++u)
            {
                for (int v = pointerJ; v < listJ.size(); ++v)
                {
                    if (abs(candidate[u]-listJ[v]) <= k)
                    {
                        result.push_back(candidate[u]);
                        pointerI = u+1;
                        break;
                    }
                    else if(candidate[u]-listJ[v] > k)
                        pointerJ = v+1;
                }
            }
        }

        for (auto a : candidate)
            cout << a << " ";
        cout << endl;

        for (auto a : listJ)
            cout << a << " ";
        cout << endl;

        return result;
    }
};

int main()
{
    Solution s;

    auto r1 = s.beautifulIndices("bkuftimiqgtmupiqgtmupiqgtmupiqgtmupbkuftimiqgtmupbkuftimbkuftimiqgtmupbkuftimbkuftimbkuftimiqgtmupbkuftimiqgtmupiqgtmupiqgtmupiqgtmupiqgtmupiqgtmup", "bkuftimiqgtmupiqgtmupiqgtmupiqgtmupbkuftimiqgtmupbkuftimbkuftimiqgtmupbkuftimbkuftimbkuftimiqgtmupbkuftimiqgtmupiqgtmupiqgtmupiqgtmupiqgtmupiqgtmup", "iqgtmupbkuftimiqgtmupbkuftimbkuftimiqgtmupiqgtmupiqgtmupiqgtmupbkuftimiqgtmupiqgtmupiqgtmupiqgtmupiqgtmupbkuftimiqgtmupbkuftimbkuftimbkuftimiqgtmup", 10);
    for (auto q : r1)
        cout << q << " ";
    cout << endl;

    auto r2 = s.beautifulIndices("lagopphhnl", "gopph", "hnl", 8);
    for (auto q : r2)
        cout << q << " ";
    cout << endl;

    string a("hnl");
    AutoEvaluator autoB(a);

    for (auto s:"lagopphhnl")
    {
        autoB.evaluate(s);
    }

    return 0;
}