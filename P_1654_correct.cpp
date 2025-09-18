#include <iostream>
#include <vector>

using namespace std;

/*
    랜선 자르기 문제. 이분탐색의 변형이라고 생각하면 됨
    제일 신경써야하는 부분은 mid의 계산, whille 조건, lower/higher 값 변경임
    
    mid를 계산할때 주로 (lo+hi)/2로 할텐데, 이러면 무조건 mid는 lo에 더 가깝게 나옴
    왜냐면 저 계산은 내림과 동일하기 때문에 그럼
    이점을 유의하고 기억하고 있어야됨

    while 조건도 중요함
    lo < hi, lo <= hi 2가지 방안이 있는데
    안전하게 lo <= hi가 더 좋은듯
    n~n 범위 떴을때, n이 이전 단계에서 mid가 아니었다면 
    lo < hi라면 스킵을 당하면 확인해야하는 조건 하나를 못보게 되는 것

    low:mid-1,high:mid는 절대 하면 안되는 방안
    줄어들지 않는 범위가 생겨 무한루프에 빠질 수 있음
    low:mid-1,high:mid+1는 while 조건 lo <= hi일때 사용가능함
    lo < hi라면 체크되지 않는 케이스가 생기게 됨
    low:mid,high:mid+1는 while 조건 lo < hi일때 사용가능함
    lo <= hi라면 무한루프에 빠지게 됨

    다시 한번 강조하지만 while 조건문과 lo/hi 값 변경 규칙은 서로 긴밀하게 연관되어있음
    범위가 어떻게 줄어드냐에 따라 그 조건문에 따라 무한루프 혹은 불완전한 탐색이 발생할 수 있음
    사실 직관적인 lo<hi & low:mid,high:mid+1를 추천함

    그리고 자른 랜선 개수를 누적하는 counter 자료형도 주의깊게 봐야됨
    2^32라서 uint로 될 것으로 보이지만, counter엔 2^32*N만큼 저장될 수 있음
    최악의 경우, 10000*2^32가 들어갈 수 있는 것
    근데 어디서 잘못될지 모르니 안전하게 일단 다 long long으로 하자
*/

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	long long N, K, input;
    long long endPoint = INT64_MAX;
	long long beginPoint = 0;

	cin >> N >> K;
	vector<long long> lan;
	
	for (long long i=0; i<N; i++)
	{
		cin >> input;
		lan.push_back(input);
        if (endPoint < input)
            endPoint = input;
	}
    
	while(beginPoint < endPoint)
	{
		long long counter = 0;
		long long divider = (beginPoint + endPoint) / 2;
		for (auto elem : lan)
            counter += elem / divider;
		
		if (K>counter)
			endPoint = divider;
		else
            beginPoint = divider+1;
	}
	
	cout << beginPoint-1;
	
	return 0;
}