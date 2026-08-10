#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    각 숫자는 명확하게 지는 숫자와 이기는 숫자로 나눠짐
    플레이어는 각자 상대에게 지는 숫자를 넘겨주는 것이 유리함
    또한 각 숫자에 대해 승패 여부를 기록해둔다면, 다른 숫자에 대해 확인할때 재사용할 수 있을것
    실행 결과, 1650ms(over 5.01%), 40MB(over 6.04%)
    이는 단순히 정적 멤버 변수가 아니었기에 발생하였거나, 혹은 play에서 작은 수부터 빼는 과정이 문제였을 수 있음
    
    정적 멤버 변수로 바꾸고 재귀 대신 반복으로 변경한 이후, 0ms(over 100%), 8MB(over 96.39%)
    처음엔 초기화를 즉시 실행 람다식으로 하였어도, 그 대상이 정적 멤버 변수가 아니었기에 성능 향상이 미미했던 것으로 보임
    따라서 정적 멤버 변수로 바꾸고, 동시에 inline static bool init 관용구로 무조건 한번만 초기화되도록 바꿈

    이 방식은 자주 쓰이나, 잘 사용하지 못했던 것은 현재 환경에서 계속 c++17로 빌드가 되지 않는 문제때문이었는데,
    tasks.json에서 /std:c++17 옵션을 명령어 인자에 추가하면 되는 것이었음
*/

class Solution {
public:
    static inline const int SIZE = 100'001;
    static inline const int NO_INIT = 0;
    static inline const int WIN = 1;
    static inline const int LOSE = -1;
    inline static int isWin[SIZE];

    inline static bool init = [](){
        isWin[0] = LOSE;

        for (int i=1; i<SIZE; i++)
        {
            for (int j=1; j*j<=i; j++)
            {
                if (isWin[i - j*j] == LOSE)
                {
                    isWin[i] = WIN;
                    break;
                }
            }
            if (isWin[i] == NO_INIT)
                isWin[i] = LOSE;
        }

        return true;
    }();

    bool winnerSquareGame(int n) {
        if (isWin[n] == WIN)
            return true;
        else
            return false;
    }
};
int main()
{
    Solution s;

    cout << s.winnerSquareGame(9) << endl;

    return 0;
}