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
	int R, C, D;
	Stack S;
	S.top = 0;
	S.dot[S.top].r = sr; 	//处理起始点
	S.dot[S.top].c = sc;
	S.dot[S.top].di = -1;
	_index[sr][sc] = -1; 	//已搜索过置为-1
	while(S.top > -1){
		R = S.dot[S.top].r;
		C = S.dot[S.top].c;
		D = S.dot[S.top].di;
		if(R == er && C == ec){ 	//当搜索到出口，打印栈内元素，也就是搜索的路径
			for(int i = 0; i <= S.top; i++){
				printf("(%d,%d)",S.dot[i].r,S.dot[i].c);
			}
			printf("\n");
			return 1;
		}
		int find = 0;
		while(D < 4 && find == 0){
			switch(D++){
			case 0:		//向右遍历
				R = S.dot[S.top].r + 1;
				C = S.dot[S.top].c;
				break;
			case 1:		//向下遍历
				R = S.dot[S.top].r;
				C = S.dot[S.top].c + 1;
				break;
			case 2:		//向左遍历
				R = S.dot[S.top].r - 1;
				C = S.dot[S.top].c;
				break;
			case 3:		//向上遍历
				R = S.dot[S.top].r;
				C = S.dot[S.top].c - 1;
			}
			if(_index[R][C] == 0){ 	//可以继续搜索下一个点
				find = 1;
			}
		}
		if(find == 1){ 		//若可以搜索下一个点则将下一个点入栈
			S.dot[S.top++].di = D;
			S.dot[S.top].r = R;
			S.dot[S.top].c = C;
			S.dot[S.top].di = -1;
			_index[R][C] = -1; 	//已搜索过置为-1
		}else{ 			//否则回溯
			S.top--;
			_index[S.dot[S.top].r][S.dot[S.top].c] = 0;
		}
	}
	return 0;
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
	//DFS(1, 1, 14, 14);
	printf("%d",BFS(1, 1, 14, 14));
	return 0;
}
