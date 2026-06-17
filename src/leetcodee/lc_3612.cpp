#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    문제에서 제시하는 기능을 그대로 구현하면 끝인 문제
    실행 결과, 0ms(over 100%), 40MB(over 69.70%)
*/

class Solution {
public:
    string processStr(string s) {
        string result = "";

        for (const auto& c : s)
        {
            if (c == '*')
            {
                // erase back 1
                if (!result.empty())
                    result.pop_back();
            }
            else if (c == '#')
            {
                // duplicate
                result += result;
            }
            else if (c == '%')
            {
                // reverse
                reverse(result.begin(), result.end());
            }
            else
            {
                result.push_back(c);
            }
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}