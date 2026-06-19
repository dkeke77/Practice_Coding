#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    단순히 분침과 시침이 가르키는 각도를 구하고, 이들의 차이를 구하면 됨
    실행 결과, 0ms(over 100%), 8MB(over 74.16%)
*/

class Solution {
public:
    double angleClock(int hour, int minutes) {
        double mHand = minutes * 6;
        double hHand = hour * 30 + minutes / 2.0;
        double angle = abs(mHand - hHand);

        return min(angle, 360 - angle);
    }
};

int main()
{
    Solution s;

    return 0;
}