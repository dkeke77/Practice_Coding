#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    가능한 케이스가 얼마 없기 때문에, 미리 케이스들을 전부 만들어두고 조건에 맞는 구간을 반환
    실행 결과, 0ms(over 100%), 8MB(over 97.69%)
    해당 케이스들을 컴퓨터가 생성하게끔 코드를 짜는 것도 가능하지만,
    그것보다 가능한 케이스를 직접 타이핑하는 편이 더 빠름
*/

class Solution {
public:
    vector<int> seqDig = {
        12,23,34,45,56,67,78,89,
        123,234,345,456,567,678,789,
        1234,2345,3456,4567,5678,6789,
        12345,23456,34567,45678,56789,
        123456,234567,345678,456789,
        1234567,2345678,3456789,
        12345678,23456789,
        123456789
    };
    const int n = seqDig.size();

    vector<int> sequentialDigits(int low, int high) {        
        return vector<int>(
            lower_bound(seqDig.begin(), seqDig.end(), low),
            upper_bound(seqDig.begin(), seqDig.end(), high)
        );
    }
};

int main()
{
    Solution s;

    return 0;
}