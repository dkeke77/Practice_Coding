#include <iostream>
#include <vector>

using namespace std;

/*
    1629번, 자연수 A를 B만큼 제곱하고 C로 나눈 나머지를 구하는 문제.
    이전에 풀었던 피보나치 문제에서 썼던 해법대로 함

    A^B = A^1 * A^2 * A^4 * A^8 ... 와 같이 표현할 수 있음에서 착안
    B를 좌측 시프트하며 제일 왼쪽 비트가 1이면 result에 mul을 곱합
    mul은 이와 상관없이 매 반복마다 제곱

    그리고 mul, result 둘다 C로 나눈 나머지로 함
    이것이 가능한 것은 직접 식 전개해보면 앎...
    아니면 n진수로 이해하면 됨
    C진법이라고 생각하면 우리는 첫번째 자리만 궁금한거임
    그런데 첫번째 자리에 영향을 끼치는건 첫번째 자리들임
    즉, 첫번째 자리만 있어도 상관이 없음
    따라서 첫번째 자리만 남긴다 -> C로 나눈 나머지
    이렇게 이해하면 됨
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    long long A, B, C;
    cin >> A >> B >> C;
    long long result=1, mul=A;

    while(B!=0)
    {
        if(B & 1)
            result = result * mul % C;
        mul = mul * mul % C;
        B >>= 1;
    }

    cout << result;

    return 0;
}