#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    문자별 freq 기록하고 a부터 z순으로 회문을 구성하면 될듯?
    실행 결과, 31ms(over 67.25%), 61MB(over 81.32%)
*/

class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26,0);
        string result = "";
        result.reserve(s.length());
        int evenChIdx = -1;

        for (const auto& c : s)
            freq[c-'a']++;

        for (int i=0; i<26; i++)
        {
            if (freq[i] > 0 && freq[i] % 2 != 0)
                evenChIdx = i;
            for (int j=0; j<freq[i]/2; j++)
                result += 'a'+i;
            freq[i] >>= 1;
        }
        if (evenChIdx >= 0)
            result += 'a'+evenChIdx;

        for (int i=25; i>=0; i--)
        {
            for (int j=0; j<freq[i]; j++)
                result += 'a'+i;
        }

        return result;
    }
};
int main()
{
    Solution s;

    return 0;
}