#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    prefix sum으로 접근하면 되지 않을까 생각됨
    혹은 투 포인터로 접근하는 것도 좋을듯
    ptrL과 ptrR로 만드는 문자열을 조건에 맞는 최소한의 길이로 유지시키는 것이 핵심
    이때, ptrL까지의 문자 개수만큼 부분 문자열을 만들 수 있으므로 해당 개수만큼 정답에 가산
    그러면서 ptrR을 한칸씩 전진하면 됨
    단, 해당 부분문자열이 당장 조건에 맞지 않는다면 ptrL 관련 동작은 스킵
    실행 결과, 2ms(over 91.13%), 11MB(over 81.80%)

    다른 풀이로는, ptrR만 전진하면서 a,b,c의 등장 위치 중 제일 작은 것만큼 부분문자열을 생성할 수 있음
    즉, a,b,c 중 제일 먼저 등장했던 위치만 기억하면 위의 슬라이딩 윈도우와 똑같은 원리를 적용할 수 있음
    더욱이 이 방법은 ptrR만 전진하면 되므로, 상수항까지 따져보아도 n으로 굉장히 빠름
*/

class Solution {
public:
    int numberOfSubstrings(string s) {
        const int n = s.length();
        int answer = 0;
        int ptrL = 0;
        int ptrR = 0;
        vector<int> counter(3,0);

        for (ptrR; ptrR < 2; ptrR++)
            counter[s[ptrR]-'a']++;
        
        while(ptrR < n)
        {
            counter[s[ptrR]-'a']++;
            if (counter[0] > 0 && counter[1] > 0 && counter[2] > 0)
            {
                for (ptrL; ptrL<ptrR-2; ptrL++)
                {
                    if (counter[s[ptrL]-'a'] == 1)
                        break;
                    else
                        counter[s[ptrL]-'a']--;
                }
                answer += ptrL+1;
            }
            ptrR++;
        }
        
        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}