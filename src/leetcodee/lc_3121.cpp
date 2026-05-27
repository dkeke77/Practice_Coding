#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
@풀이
    처음엔 2개의 벡터를 이용하여, 마지막에 등장한 대소문자 위치를 비교하도록 하였음
     ㄴ 소문자 위치가 대문자보다 앞에 있어야 한다는 조건
    그러나 대문자 뒤에 소문자가 다시 등장하는 경우를 해결하진 못했음
    그래서 간단한 상태머신을 만들어서 이를 수행시킴
    실행 결과, 70ms(over 59.55%), 24MB(over 80.34%)
    생각보다 많이 느린 수치를 보여줌
    아무래도 if문이 많아 발생한 것으로 추측됨

@개선1
    처음에 작성했던 두 벡터를 이용한 대소문자 위치 비교를 수정하기로 함
    대문자를 마지막에 등장한 인덱스가 아닌, 처음에 등장한 인덱스를 저장토록 함
    실행 결과, 63ms(over 86.80%), 24MB(over 80.34%)
    여전히 생각보다 느린 수치를 보임

@개선2
    if문을 완전히 배제하고, 비트마스크만을 이용하여 구현함
     ㄴ 인라인이지만 함수조차 완전 배제하도록 함
    실행 결과, 50ms(over 98.03%), 24MB(over 93.54%)
    이 이상 더 줄여볼까 하였지만, over 100%였다는 코드를 복사하여 실행해보아도 40ms 아래는 나오지 않았음
     ㄴ 최소 48ms, 최대 68ms로 내 구현과 큰 차이는 없었음
    따라서 over 100%는 서버 상황에 크게 좌우된다고 생각됨
    마지막에서 1인 비트를 세는 함수로 __builtin_popcount가 있다고 함
     ㄴ 하지만 이걸 써도 성능 상승은 특별히 없었음
*/

class Solution {
public:
    int numberOfSpecialChars(string word) {
        int upper = 0;
        int lower = 0;

        for (auto ch : word)
        {
            int lowerBit = ((ch - 'A') >> 5) << ((ch - 'A') & 31);
            upper |= (((ch - 'A') >> 5)^1) << ((ch - 'A') & 31);
            lower = (lower & ~lowerBit) | (lowerBit & ~upper);
        }

        lower &= upper;
        int answer = 0;

        while(lower != 0)
        {
            answer += lower&1;
            lower >>= 1;
        }

        return answer;
    }
};
int main()
{
    Solution s;

    return 0;
}