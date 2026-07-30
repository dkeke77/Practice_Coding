#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    회문중 0~n/2 부분만 생각하면 됨
     ㄴ 어차피 나머지는 앞쪽의 반대니까
     ㄴ 이때 최대 길이는 5000
    이전처럼 freq를 구성해서 앞쪽에 어떤 문자들이 들어가는지는 알 수 있음
    그런데 해당 문자들의 조합 중에 k번째 문자열이 무엇인지 어떻게 알 수 있을까?
    무작정 모든 문자열을 확인하는 것은 불가능하리라 생각함
     ㄴ 이유는 딱히 없음
    생각할 수 있는 좋은 방법은 주어진 문자 조합에서 몇가지 조합이 나올 수 있는 것
     ㄴ 앞에서부터 문자를 하나씩 결정하면서 남은 문자 조합을 줄여나가면 됨
     ㄴ 그런데 중복되는 케이스는 세지 않는다는 규칙이 문제임
    힌트에 따르면 위 접근은 다 적절했고, 조합론을 이용해서 조합 개수를 세면 됨
    같은 것이 있는 순열의 공식은 찾아보니 아래와 같음
     ㄴ n!/(a!b!c!...z!)
    그렇다면 팩토리얼을 어떻게 잘 계산할지가 다른 문제로 다가옴

    팩토리얼을 어떻게든 계산해보기 위해, 분모와 분자에 각각 한 숫자씩 곱하고 약분하는 방식을 사용했음
    이는 작은 수에선 제대로 동작했지만, 수가 커지면서 약분만으로는 처리할 수 없었음
    특히 n/2이 26이며 각 문자가 1번씩 등장한 경우, 그 조합은 최대 26!이므로 처리할 수 없었음

    따라서 풀이를 참고한 결과, 다른 수학적 트릭을 사용하여 풀고 있었음
    위의 순열 공식은 조합의 곱으로 분해할 수 있음
     ㄴ nCa * (n-a)Cb * (n-a-b)Cc * ...
     ㄴ 분모와 분자 양쪽에 조합에 쓰이는 (n-r)!를 연쇄적으로 곱하면 유도할 수 있음
     ㄴ 혹은 남은 칸들중에서 어떤 문자가 들어갈 칸 q개를 선택하는 관점으로도 볼 수 있음
    그리고 조합은 C(n,i) = C(n,i-1)*(n-i+1)/i와 같은 점화식으로 빠르게 구할 수 있음
     ㄴ 이는 늘 정확히 정수로 나눠떨어진다고 함
    또한 마지막으로, 위와 같은 트릭을 적용하여도 그 결과가 굉장히 클 수 있음
    따라서 계산 과정에서 10^6보다 커지는 경우, 즉시 계산 종료하여 오버플로우를 방지하는 코드가 포함되어있음
    실행 결과, 195ms(over 15.27%), 15MB(over 96.18%)

    수학적 트릭을 적극 이용하는 문제이기 떄문에 그렇게 실용성이 있는 문제라고 보이진 않음
    더 나아가 감마함수를 이용하는 풀이도 있지만, 이는 더더욱 실용성이 없다고 보임
*/

class Solution {
public:
    const long long LIMIT = 1000000;

    int countSubComb(long long n, long long r)
    {
        int combs = 1;
        for (int i=1; i<=r; i++)
        {
            combs = combs * (n-r+i) / i;
            if (combs > LIMIT)
                return LIMIT;
        }

        return combs;
    }

    int countPerm(int n, const vector<int>& freq)
    {
        int remained = n;
        long long result = 1;

        for (const auto& f : freq)
        {
            if (f <= 0) continue;

            result *= countSubComb(remained, f);

            if (result > LIMIT)
                return LIMIT;
            else
                remained -= f;
        }        

        return result;
    }

    string smallestPalindrome(string s, int k) {
        const int n = s.length();
        vector<int> freq(26,0);
        int evenChIdx = -1;

        for (const auto& c : s)
            freq[c-'a']++;

        for (int i=0; i<26; i++)
        {
            if (freq[i] > 0 && freq[i] % 2 != 0)
                evenChIdx = i;
            freq[i] >>= 1;
        }

        if (countPerm(n/2, freq) < k)
            return "";
        
        for (int i=0; i<n/2; i++)
        {
            for (int j=0; j<26; j++)
            {
                if (freq[j] <= 0) continue;

                freq[j]--;
                int combCount = countPerm(n/2-i-1, freq);
                if (combCount < k)
                {
                    k -= combCount;
                    freq[j]++;
                }
                else
                {
                    s[i] = 'a'+j;
                    s[n-i-1] = 'a'+j;
                    break;
                }
            }
        }

        if (evenChIdx > 0)
            s[n/2] = 'a'+evenChIdx;

        return s;
    }
};

int main()
{
    Solution s;

    vector<int> freq(26,0);
    freq[0] = 4;
    freq[1] = 4;

    cout << s.countPerm(8, freq) << endl;

    return 0;
}