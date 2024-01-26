#pragma warning(disable: 4996)
#include <iostream>
#include <list>
#include <set>
#include <iterator>
class Direct {
public:
	int time;
	char direct;

	Direct(int t, char d) {
		this->time = t;
		this->direct = d;
	}
	Direct() { // 위에 생성자를 만들어서 기본 생성자를 만들어주어야 함
	};
};

class Point {
public:
	int x, y;
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Point() {};
};


using namespace std;
Point SnakeHeading(Point cur, char direct) {
	if (direct == 'D') {
		if (cur.x == 1 && cur.y == 0) {
			return Point(0, 1);
		}
		else if (cur.x == -1 && cur.y == 0) {
			return Point(0, -1);
		}
		else if (cur.x == 0 && cur.y == -1) {
			return Point(1, 0);
		}
		else if (cur.x == 0 && cur.y == 1) {
			return Point(-1, 0);
		}
	}
	else {
		if (cur.x == 1 && cur.y == 0) {
			return Point(0, -1);
		}
		else if (cur.x == -1 && cur.y == 0) {
			return Point(0, 1);
		}
		else if (cur.x == 0 && cur.y == -1) {
			return Point(-1, 0);
		}
		else if (cur.x == 0 && cur.y == 1) {
			return Point(1, 0);
		}
	}
}
int main() {
	using namespace std;
	
	int N, K, time, row, column, i, j, numDirection, countq, directcnt=0, duplicate =0;
	char direction;  // 문자형 방향 돌리기
	set<pair<int, int>> copysnake;
	
	list<Point> snakeList;
	snakeList.push_back(Point(1, 1));

	Point curSnakedirect = Point(1, 0); // 뱀의 방향
	Point curSnakePosition = Point(1, 1); //뱀의 위치
	list<Point>::iterator it;


	scanf("%d", &N);
	scanf("%d", &K);
	int** Board = new int*[N+1];
	for (i = 0; i <= N; i++) {
		Board[i] = new int[N+1];
	}
	for (i = 0; i <= N; i++) {
		for (j = 0; j <= N; j++) {
			Board[i][j] = 0; //보드판
		}
	}

	for ( i = 0; i < K; i++) {
		scanf("%d %d", &row, &column);
		Board[row][column] = 1;
	}
	
	scanf("%d", &numDirection);
	Direct* directionList = new Direct[1004];
	for (i = 0; i < numDirection; i++) {
		scanf("%d %c", &time, &direction);
		directionList[i] = Direct(time, direction);                 
	}
	for (countq = 1; ; countq++) {
		curSnakePosition.x += curSnakedirect.x;
		curSnakePosition.y += curSnakedirect.y; 
		if (curSnakePosition.x > N || curSnakePosition.y > N || curSnakePosition.y <= 0 || curSnakePosition.x <= 0) // 탈출조건
			break;

		snakeList.push_back(Point(curSnakePosition.x, curSnakePosition.y));  //머리추가
	
		for (it = snakeList.begin(); it != snakeList.end(); ++it) {
	
			copysnake.insert({ it->x, it->y });
		}
		if (copysnake.size() != snakeList.size()) {   //중복값있을 경우 탈출
			break;
		}

		copysnake.clear();
		
		
		
		if (Board[curSnakePosition.y][curSnakePosition.x] == 0) 
			snakeList.pop_front();  //꼬리제거
		else{
			Board[curSnakePosition.y][curSnakePosition.x] = 0; 
		}

		if (countq == directionList[directcnt].time) {
			curSnakedirect = SnakeHeading(curSnakedirect, directionList[directcnt].direct); //뱀의 방향 바꾸기

			if(directcnt <numDirection)
			    directcnt++;
		}
	}

	cout <<countq;



}