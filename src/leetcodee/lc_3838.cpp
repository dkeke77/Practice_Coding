#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    단순히 순회하며 각 문자에 대한 가중치를 누적하고,
    이에 대응하는 문자를 결과 문자열에 누적하면 끝
    실행 결과, 0ms(over 100%), 43MB(over 95.02%)
*/

class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result = "";

        for(const auto& word : words)
        {
            int sum = 0;
            for (char c : word)
                sum += weights[c-'a'];

            result += 'z' - (sum % 26);
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}