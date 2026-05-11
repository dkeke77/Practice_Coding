#include <iostream>>
#include <vector>
#include <stack>

using namespace std;

/*
@성공
    정수를 각 자릿수로 분할하는 문제...
    각 정수를 10으로 나눈 나머지를 스택에 넣고, 해당 정수를 10으로 나눔
    이 과정을 그 정수가 0이 될때까지 반복하면 그 정수가 역순으로 스택에 저장하게 됨
     ㄴ 제일 큰 자릿수가 스택 제일 위에 위치하고, 1의 자리는 스택 제일 아래에 위치
    그리고 나서 결과 배열에 하나씩 pop하면서 추가하면 끝임

    시간 복잡도는 O(n)으로 예상
     ㄴ 최대 n*2*5 : 각 정수는 최대 5자리이므로 넣고 빼는 과정이 최대 5*2번 가능함
    실행 결과, 0ms(over 100%), 14MB(over 85.26%)

    다른 방법으로는 해당 수를 문자열로 바꾸고, 앞에서부터 한글자씩 다시 정수로 변환해서 저장하는 방법도 있음
    혹은 아예 뒤에서부터 nums 배열을 순회하면서, 10으로 나눈 나머지를 쭉쭉 넣은 뒤, 마지막에 전체 배열을 뒤집는 방법도 있음
     ㄴ 이 방법은 메모리를 더 절약할 수 있음
    두 방법 모두 유효하고 괜찮은 방법임
*/

class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> result;
        stack<int> temp;

        for (auto n : nums)
        {
            while (n > 0)
            {
                temp.push(n % 10);
                n /= 10;
            }

            while (!temp.empty())
            {
                result.push_back(temp.top());
                temp.pop();
            }
        }

        reverse(result.begin(),result.end());

        return result;
    }
};

int main()
{
    Solution s;
    vector<int> v = {13,25,83,77};

    for (auto i : s.separateDigits(v))
        cout << i << " ";
    cout << endl;

    return 0;
}