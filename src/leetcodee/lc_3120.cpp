#include <vector>
#include <iostream>

using namespace std;

/*
@풀이
    전체 문자열을 검사하면서 대소문자가 동시에 등장한 케이스를 따로 기록해야됨
    즉, 각 문자에 대한 대소문자 등장 여부를 가져야 함
    bool 벡터 2개를 이용할 수도 있지만, 조금 기교적으로 비트마스크를 이용하여 만들 수도 있음
    영문자는 총 26개, 대소문자까지 하면 52개이므로 64비트 하나로 충분히 표현 가능함
    따라서 비트 연산만으로도 간단히 이를 표현할 수 있음
    단, 상수를 쓸땐 LL을 붙여 int로 인식되지 않게 하여야함
    실행 결과, 0ms(over 100%), 9MB(over 96.06%)가 나옴
*/

class Solution {
public:
    inline int convertCh(char c)
    { return (int(c)-65)%32; }

    inline bool isLower(char c)
    { return (int(c)-65)/32; }

    int numberOfSpecialChars(string word) {
        long long bitmask = 0;
        int count = 0;

        for (int i=0; i<word.length(); ++i)
        {
            if (isLower(word[i]))
                bitmask |= (1LL << convertCh(word[i])*2);
            else
                bitmask |= (2LL << convertCh(word[i])*2);
        }

        for (int i=0; i<26; ++i)
            count += bitmask & (1LL << i*2) && bitmask & (2LL << i*2);

        return count;
    }
};

int main()
{
    Solution s;

    return 0;
}