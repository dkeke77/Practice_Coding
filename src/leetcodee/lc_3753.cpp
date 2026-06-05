#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
@접근
    저번 문제를 통해 이미 해법을 봐바렸지만, DP를 이용하여 풀면 됨
    3자리에 대해서만 미리 구해두고, 4이상의 n자리부터는 n-1자리의 정보를 통해 계산하면 됨
     ㄴ n-1자리 뒤에 숫자 하나를 추가한다는 개념
    그런데 10^15로 꽤 크기때문에 순회하는 방식보단 빠르게 처리할 방법이 있어야함...
     ㄴ O(n)으론 무조건 TLE 발생함
     ㄴ 앞에서 처리한 것을 이용한다고 해도, 앞자리수의 케이스 * 10번 해야됨
    그렇다면 각 앞 숫자마다 peak, valley, none을 기록하자
    그러면 앞에 자릿수 하나를 추가할때, 각 숫자마다 peak, valley, none이 얼마나 생길지 계산할 수 있음
    이를 기반으로 waviness를 순회없이 빠르게 계산할 수 있지 않을까?
    다만 n-1자리에 0이 들어가는 경우를 따로 처리해야함
     ㄴ 0자리를 따로 계산만 해두고, 다음 자릿수 계산 시에만 활용하도록 하는 편이 좋아보임
    그런데 1522와 같이 none으로 분류된 522가 나중에 waviness를 가질 수도 있음
    완벽히 none에서 peak와 valley를 분리해낼 수 없음
    따라서 위 접근은 잘못되었음

    아니면 맨 앞의 2자리수와 그 waviness를 저장하며 dp를 확장하는 방법...?
    단순하게 만든다면 각 0~9 반복하며 내부에서 0~99를 전부 확인하면 1000번 반복
    그러나 어떤 값에 대해 waviness를 계산하는건 또 다른 문제임
     ㄴ 어떤 값보다 낮은 값으로는 그 waviness를 계산해낼 수 있겠지만, 그 잔차를 계산하는건 좀 까다로울 수 있응ㅁ
     ㄴ 12999 같은 경우엔 보다 간단하게 계산할 수도 있겠지만... 13300 같은 경우엔 좀 어려워짐
    
@풀이
    도저히 뾰족한 수가 없어서 풀이를 보고 해법을 알아냄
    DP가 아니어도 슬라이딩 윈도우를 사용하여 풀어낼 수 있음
    우선 peak와 valley는 어떤 패턴이라고 볼 수 있음
    따라서 3칸짜리 윈도우로 캡쳐된 수가 패턴과 일치하면 해당 숫자는 적어도 waviness가 1이상임
    이를 이용하여 윈도우를 이동해가며 패턴마다 등장 가능한 숫자의 조합을 계산할 수 있음
    이 계산을 전체 자릿수에 대해 수행하면 됨
    그런데 등장 가능한 숫자의 조합은 캡쳐된 수와 패턴의 대소 관계에 따라 약간씩 다름
     ㄴ 패턴이 더 작다면, 모든 수를 자유롭게 배치할 수 있으므로 (prefix+1) * 10^s
        ㄴ s는 윈도우 시프트 횟수
     ㄴ 패턴과 캡쳐가 동일하면 원본 수가 최대이므로, prefix * 10^s + suffix + 1
     ㄴ 패턴이 더 크다면, prefix보다 작아야 배치할 수 있으므로 prefix * 10^s
    그리고 패턴 중엔 0으로 시작하는 것이 있음
    해당 패턴은 prefix가 000....00일때는 배치할 수 없으므로 해당 prefix를 제외하여야 함
    따라서 패턴이 0으로 시작한다면 위 연산들에서 prefix를 1 빼고 계산
    마지막으로 1000 미만 케이스는 위 방법으로 계산할 수 없으니, 따로 처리해야됨

    실행 결과, 11ms(over 93.35%), 21MB(over 14.56%)
    (자릿수-2) * patterns만큼 반복하는데, 최대 13 * 570로 7410이 끝임
     ㄴ patterns는 570로 고정
    실제 수를 순회하지 않고, 자릿수 중심으로 처리하는 발상 자체는 타당했었음
    하지만 그 발상을 구현까지 가져오지 못한 점이 아쉬움

    물론 DP로도 풀 수 있음
*/

class Solution {
public:
    bool isInited = false;
    vector<int> patterns;

    long long totalWaviness(long long num1, long long num2)
    {
        if (!isInited)
        {
            init();
            isInited = true;
        }

        return countWaviness(num2) - countWaviness(num1-1);
    }

    long long countWaviness(long long num)
    {
        long long result = 0;
        const long long windowCapture = 1000;
        long long windowPos = 1;

        if (num < 1000)
        {
            for (const auto& p : patterns)
            {
                if (p >= 100 && p <= num)
                    result++;
            }
            return result;
        }
        
        while(windowCapture * windowPos / 10 < num)
        {
            long long prefix = num / (windowCapture * windowPos);
            long long captured = num % (windowCapture * windowPos) / windowPos;
            long long suffix = num % windowPos;

            for (const auto& p : patterns)
            {
                int isZeroStart = p < 100;

                if (captured > p)
                    result += (prefix+1-isZeroStart) * windowPos;
                else if (captured == p)
                    result += (prefix-isZeroStart) * windowPos + suffix + 1;
                else
                    result += (prefix-isZeroStart) * windowPos;
            }

            windowPos *= 10;
        }

        return result;
    }

    void init()
    {
        for (int i = 0; i <= 999; i++) {
            int a = (i / 100) % 10;
            int b = (i / 10) % 10;
            int c = i % 10;
            if (a < b && c < b)
                patterns.push_back(i);
            else if (a > b && c > b)
                patterns.push_back(i);
        }
    }
};

int main()
{
    Solution s;

    return 0;
}