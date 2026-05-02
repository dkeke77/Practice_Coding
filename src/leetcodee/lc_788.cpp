#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@성공
    무조건 모든 숫자를 순회해야됨
    왜냐하면 앞의 숫자에 대한 정보가 뒤의 숫자에 대한 어떤 보장도 하지 않기 때문임
    또한 회전 가능한 숫자는 한쌍이므로 절반만 순회해도 될것처럼 생각할 수 있으나
    회전 가능한 숫자쌍 간의 거리는 규칙성이 없음
    따라서 모든 숫자를 순회할 수밖에 없음
    다만 최대 입력 수가 10^4이므로 각 숫자를 순회하는 것자체는 큰 부담이 없음
    그리고 각 자리수에 대한 검사를 수행하는 것 또한 최대 4자리수이므로 결국 O(n)를 가짐
     ㄴ 엄밀하게 O(log10(n)*n)임

    그래서 단순히 브루트포스 방법으로, 각 숫자를 회전시키고 회전된 숫자가 기존과 다르면 카운팅함
    만약 회전이 불가하면 해당 케이스는 스킵함

    처음에는 각 자리수에 대한 검사를 if문을 통해 각각 검사하도록 했으나,
    이는 if문을 8개나 쓰기에 이쁘지도 않고, 성능상 좋지 않다고 판단됐음
    그래서 각 숫자에 대한 회전을 배열에 저장해두고, 이를 참조하도록 함
    만약 불가한 케이스면 기존처럼 스킵하도록 함
    이를 통해 if문을 2개로 줄일 수 있었음
    성능은 0ms으로 올릴 수 있었으나, 기존 성능은 4~60ms로 편차가 컸기에 정확한 비교는 어려워 보임

@DP
    다른 사람의 풀이를 보니 DP를 이용하는 것도 꽤 인상적임
    각 숫자는 c=a*10+b (0<=a,b<=9)로 분해 가능함
    만약 이때, a,b 둘다 회전 가능할 때, a가 good number 혹은 b가 good number면 c는 good number임
    즉, 작은 문제의 해가 큰 문제의 해를 구하는 과정에서 활용될 수 있음
    따라서 DP를 적용할 수 있는 문제임
    구현에선 각 숫자를 3가지 타입으로 나눔 (0:회전불가, 1:회전가능하나 good number는 아님, 2:good number)
    만약 a와 b가 타입 1이라면 c는 타입 1
    만약 a와 b가 타입이 1이상이면 c는 타입 2 (위 조건문에 의해 둘다 1인 경우는 걸러짐)
    그외는 타입 0

    우아하고 멋진 풀이지만, 전체 시간복잡도에 큰 영향은 주진 않음
*/

class Solution {
public:
    int rotatedDigits(int n) {
        const int ROTATE_SET[10] = { 0,1,5,-1,-1, 2,9,-1,8,6 };
        int count = 0;
        for (int i = 1; i <= n; ++i)
        {
            int temp = i;
            int rotated = 0;
            int shift = 1;

            while (temp != 0)
            {
                int digit = temp%10;

                if (ROTATE_SET[digit] < 0)
                {
                    // is not a rotatable number, make it non-countable and break
                    rotated = i;
                    break;
                }

                rotated += ROTATE_SET[digit] * shift;
                temp /= 10;
                shift *= 10;
            }
            if (rotated != i)
                count++;
        }

        return count;
    }
};

int main()
{
    Solution s;

    cout << s.rotatedDigits(20) << endl;
    cout << s.rotatedDigits(1) << endl;
    cout << s.rotatedDigits(2) << endl;

    return 0;
}