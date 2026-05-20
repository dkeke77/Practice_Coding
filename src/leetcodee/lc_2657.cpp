#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
@접근
    아래와 같이 경우를 나눌 수 있음
    두 수가 같다면
     ㄴ 양쪽 전부 새로운 수일밖에 없음
     ㄴ 따라서 result++
    두 수가 다르다면
     ㄴ 전부 새로운 수라면 seen 체크만
     ㄴ 한쪽만 새롭다면 result++
     ㄴ 전부 봤던 수라면 result+=2
    이에 따라 루프문 작성
    실행 결과, 0ms(over 100%), 86MB(over 76.50%)
    해시 2개를 이용할 수도 있겠지만, 더 많은 메모리와 성능을 소모할 수 있음
    혹은 2개 비트마스크를 이용하여 서로의 등장 여부를 평가하는 것도 유효함

    두 수가 다른 경우의 분기 처리를 아래와 같이 더 압축할 수 있음
*/

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        const int n = A.size();
        vector<bool> numSeen(n+1,false);
        vector<int> result(n,0);

        numSeen[A[0]] = true;
        numSeen[B[0]] = true;
        if (A[0] == B[0])
            result[0] = 1;

        for (int i=1; i<n; ++i)
        {
            result[i] = result[i-1];

            if (A[i] == B[i])
            {
                result[i]++;
            }
            else
            {
                if(numSeen[A[i]])
                    result[i]++;
                if(numSeen[B[i]])
                    result[i]++;
            }

            numSeen[A[i]] = true;
            numSeen[B[i]] = true;
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}