#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    각 숫자에 어떤 문자를 매핑할지에 따라 push 횟수가 달라지기에, 최대한 균등하게 매핑하는 것이 유리함
    왜냐하면 두 문자를 같은 버튼에 매핑하는 것보다, 다른 버튼에 매핑하는 것이 이득이기 때문임
    또한 각 문자들이 최대 1번씩만 등장하므로, 빈도수 대신 문자열의 길이만으로 해결할 수 있음
     ㄴ 문자열의 길이가 곧 문자의 종류
    실행 결과, 0ms(over 100%), 8MB(over 77.73%)
*/

class Solution {
public:
    int minimumPushes(string word) {
        int n = word.length();
        int result = 0;

        while(n > 0)
        {
            result += n;
            n -= 8;
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}