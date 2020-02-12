#include<iostream>
#include<queue>
using namespace std;
/*需要按照邻接矩阵进行构造，不能随意构造邻接表

				0
			/	|	\
		1----3	2

			0	1	2	3
		0	0	1	1	1	  
		1	1	0	0	1
		2	1	0	0	0
		3	1	1	0	0
*/

struct Edge//边结点的结构体
{
	friend class Graph_List;
	int VerAdj;//邻接顶点序号，从0开始
	Edge* link;//指向下一个边界点的指针
};

struct Vertex//顶点表中结点的结构体
{
	friend class Graph_List;
	int VerName;//顶点的名称
	Edge* adjacent;//边界点的头指针
};

class Graph_List
{
public:
	Graph_List();
	~Graph_List();
	void DepthFirstSearch(const int v, int* visited);//以序号v为顶点出发，深度优先遍历图的递归算法
	void BFS(const int s);//从顶点s开始广度优先遍历图的迭代算法

private:
	Vertex* Head;//顶点表头指针
	int graphsize;//图中当前顶点的个数
};

Graph_List::Graph_List()
{
	int e, from, to;//边数，新边的始点、终点
	Head = new Vertex[100];//用数组实现顶点表，Head指向数组的第一个元素
	cout << "输入顶点结点数:" << endl;
	cin >> graphsize;//输入顶点个数
	for (int i = 0;i < graphsize;i++)//初始化Head数组
	{
		Head[i].VerName = i;
		Head[i].adjacent = NULL;
	}
	cout << "输入边结点数:" << endl;
	cin >> e;//输入边数
	for (int i = 0;i < e;i++)//依次输入各边
	{
		cout << "输入新边的始点、终点:" << endl;
		cin >> from >> to;//输入新边的始点、终点
		Edge* p = new Edge;//将新边插入图中
		p->VerAdj = to;
		p->link = NULL;
		Edge* q = Head[from].adjacent;
		if (q == NULL)
			Head[from].adjacent = p;
		else
		{
			while (q->link != NULL)
				q = q->link;
			q->link = p;
		}
	}
}

Graph_List::~Graph_List()
{
	for(int i = 0;i<graphsize;i++)
	{
		Edge* p = Head[i].adjacent;
		while (p != NULL)
		{
			Head[i].adjacent = p->link;
			delete p;
			p = Head[i].adjacent;
		}
	}
	delete[] Head;
}



void Graph_List::DepthFirstSearch(const int v, int* visited)//以序号v为顶点出发，深度优先遍历图的递归算法
{
	cout << v << " ";//输出v的名称
	visited[v] = 1;//说明v已经被访问过
	Edge* p = Head[v].adjacent;//取得v的第一个邻接顶点的序号
	while (p != NULL)//若存在顶点p
	{
		if (visited[p->VerAdj] != 1)//若p未被访问过，从p递归访问
			DepthFirstSearch(p->VerAdj, visited);
		p = p->link;//p为c关于p的下一个邻接顶点
	}
}

void Graph_List::BFS(const int s)//从顶点s开始广度优先遍历图的迭代算法，使用了队列
{
	int* visited = new int[graphsize];
	for (int k = 0;k < graphsize;k++)
		visited[k] = 0;
	cout << s << " ";
	visited[s] = 1;
	queue< int> q;
	q.push(s);
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		Edge* p = Head[v].adjacent;
		while (p!=NULL)
		{
			if (visited[p->VerAdj] == 0)
			{
				cout << p->VerAdj << " ";
				visited[p->VerAdj] = 1;
				q.push(p->VerAdj);
			}
			p = p->link;
		}
	}
	delete[] visited;
}

int main()
{
	Graph_List L;
	int visited[100];
	int v;
	cout << "输入遍历顶点：" << endl;
	cin >> v;
	cout << "深度优先：";
	L.DepthFirstSearch(v,visited);
	for (int i = 0;i < 100;i++)
	{
		visited[i] = 0;
	}
	cout << "广度优先:";
	L.BFS(v);
	return 0;
}