#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    이전과 달리 각 문자가 중복해서 등장할 수 있으므로, 빈도수를 확인해야함
    그리고 빈도가 제일 컸던 것부터 버튼에 배정하면 됨
    실행 결과, 7ms(over 69.73%), 25MB(over 84.36%)
*/

class Solution {
public:
    int minimumPushes(string word) {
        vector<int> freq(26,0);
        int btnUsing = 0;
        int result = 0;

        for (const auto& c : word)
            freq[c-'a']++;

        sort(freq.begin(), freq.end(), greater<int>());

        for (const auto& f : freq)
            result += f*(btnUsing++/8+1);

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}