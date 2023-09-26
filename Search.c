#include<stdio.h>

int maze[5][5] = {
	{0,0,0,0,0},
	{0,1,0,1,0},
	{0,1,1,0,0},
	{0,1,1,0,1},
	{1,0,0,0,0}
};

int _index[16][16] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,0,1,1,1,1,0,1,1,1,1,1},
	{1,0,0,1,0,1,1,0,0,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1},
	{1,0,0,1,1,1,1,1,0,1,1,1,1,0,1,1},
	{1,0,1,1,1,1,1,1,0,0,0,1,1,0,1,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1},
	{1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1},
	{1,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,1},
	{1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,1},
	{1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1},
	{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct Dot
{
	int r; 	 //横坐标
	int c;	 //纵坐标
	int di;  //搜索方向
}Dot;

typedef struct Stack
{
	Dot dot[100];
	int top;
}Stack;

typedef struct Queue
{
	Dot dot[200];
	int front;
	int rear; 
}Queue;

//深度优先搜索
int DFS(int sr, int sc, int er, int ec)
{
	Stack S;
	int count = 0, R, C, D, find;
	S.top = -1;
	S.top++;
	S.dot[S.top].r = sr;		//处理起始点
	S.dot[S.top].c = sc;
	S.dot[S.top].di = -1;
	while (S.top > -1) {			//栈不为空则继续循环，栈为空时说明无解
		R = S.dot[S.top].r;
		C = S.dot[S.top].c;
		D = S.dot[S.top].di;
		if(D == -1) D++;
		if (R == er && C == ec) { 	//找到出口则打印路径
			for (int i = 0; i <= S.top; i++) {
				printf("(%d,%d)", S.dot[i].r, S.dot[i].c);
			}
			printf("\n");
			count++;
			S.top--; 	//将目标点出栈并进行回溯
			R = S.dot[S.top].r;
			C = S.dot[S.top].c;
			D = S.dot[S.top].di;
		}
		find = 0;
		while (D < 4 && S.top > -1 && find != 1) {
			if (D == 0 && _index[R + 1][C] == 0 && find == 0) { //向右搜索
				_index[R][C] = -1; 		//将当前点标记为已搜索
				S.dot[S.top].di = D;
				S.dot[S.top].di++; 		//以便下一次回溯回来时直接搜索下一个方向
				S.top++;				//入栈并更新此点信息
				S.dot[S.top].r = R + 1;
				S.dot[S.top].c = C;
				S.dot[S.top].di = -1;
				find = 1;
			}
			if (_index[R + 1][C] != 0 && find == 0 && D == 0) D++;
			if (D == 1 && _index[R][C + 1] == 0 && find == 0) { //向下搜索
				_index[R][C] = -1;
				S.dot[S.top].di = D;
				S.dot[S.top].di++;
				S.top++;
				S.dot[S.top].r = R;
				S.dot[S.top].c = C + 1;
				S.dot[S.top].di = -1;
				find = 1;
			}
			if (_index[R][C + 1] != 0 && find == 0 && D == 1) D++;
			if (D == 2 && _index[R - 1][C] == 0 && find == 0) { //向左搜索
				_index[R][C] = -1;
				S.dot[S.top].di = D;
				S.dot[S.top].di++;
				S.top++;
				S.dot[S.top].r = R - 1;
				S.dot[S.top].c = C;
				S.dot[S.top].di = -1;
				find = 1;
			}
			if (_index[R - 1][C] != 0 && find == 0 && D == 2) D++;
			if (D == 3 && _index[R][C - 1] == 0 && find == 0) { //向上搜索
				_index[R][C] = -1;
				S.dot[S.top].di = D;
				S.dot[S.top].di++;
				S.top++;
				S.dot[S.top].r = R;
				S.dot[S.top].c = C - 1;
				S.dot[S.top].di = -1;
				find = 1;
			}
			if (_index[R][C - 1] != 0 && find == 0 && D == 3) D++;
		}
		if (find == 0 && S.top > -1 ) { 		//无法继续向下搜索，出栈，将上一个标记为-1
			S.top--;
			_index[S.dot[S.top].r][S.dot[S.top].c] = -1;
		}
	}
	return count; 	//返回路径数
}

//广度优先搜索
int BFS(int sr, int sc, int er, int ec)
{
	int count = 0, R, C;
	Queue Q;
	Q.front = 0;
	Q.rear = 1; 	//初始化队首队尾指针
	Q.dot[Q.front].r = sr;  //处理起始点
	Q.dot[Q.front].c = sc;
	while(Q.front != Q.rear){ 	//队列不为空则继续循环
		R = Q.dot[Q.front].r;
		C = Q.dot[Q.front].c;
		if(_index[R + 1][C] != 1 && _index[R + 1][C] != -1){ 	//下一个点可以走而且未被标记过，入队
			if(R + 1 == er && C == ec){ 	//若找到终点则计数加一，并且不能标记终点
				count++;
			}else{
				Q.dot[Q.rear].r = R + 1; 	//处理入队元素
				Q.dot[Q.rear].c = C;
				_index[R + 1][C] = -1;
				Q.rear++;
			}
		}
		if(_index[R][C + 1] != 1 && _index[R][C + 1] != -1){
			if(R == er && C + 1== ec){
				count++;
			}else{
				Q.dot[Q.rear].r = R;
				Q.dot[Q.rear].c = C + 1;
				_index[R][C + 1] = -1;
				Q.rear++;
			}
		}
		if(_index[R - 1][C] != 1 && _index[R - 1][C] != -1){
			if(R - 1 == er && C == ec){
				count++;
			}else{
				Q.dot[Q.rear].r = R - 1;
				Q.dot[Q.rear].c = C;
				_index[R - 1][C] = -1;
				Q.rear++;
			}
		}
		if(_index[R][C - 1] != 1 && _index[R][C - 1] != -1){
			if(R == er && C - 1== ec){
				count++;
			}else{
				Q.dot[Q.rear].r = R;
				Q.dot[Q.rear].c = C - 1;
				_index[R][C - 1] = -1;
				Q.rear++;
			}
		}
		Q.front++;
	}
	return count; 	//返回路径数
}

int main()
{
	printf("%d", DFS(1, 1, 14, 14));
	printf("%d", BFS(1, 1, 14, 14));
	return 0;
}
