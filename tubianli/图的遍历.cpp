#include<iostream>
#include<queue>
using namespace std;
/*��Ҫ�����ڽӾ�����й��죬�������⹹���ڽӱ�

				0
			/	|	\
		1----3	2

			0	1	2	3
		0	0	1	1	1	  
		1	1	0	0	1
		2	1	0	0	0
		3	1	1	0	0
*/

struct Edge//�߽��Ľṹ��
{
	friend class Graph_List;
	int VerAdj;//�ڽӶ�����ţ���0��ʼ
	Edge* link;//ָ����һ���߽���ָ��
};

struct Vertex//������н��Ľṹ��
{
	friend class Graph_List;
	int VerName;//���������
	Edge* adjacent;//�߽���ͷָ��
};

class Graph_List
{
public:
	Graph_List();
	~Graph_List();
	void DepthFirstSearch(const int v, int* visited);//�����vΪ���������������ȱ���ͼ�ĵݹ��㷨
	void BFS(const int s);//�Ӷ���s��ʼ������ȱ���ͼ�ĵ����㷨

private:
	Vertex* Head;//�����ͷָ��
	int graphsize;//ͼ�е�ǰ����ĸ���
};

Graph_List::Graph_List()
{
	int e, from, to;//�������±ߵ�ʼ�㡢�յ�
	Head = new Vertex[100];//������ʵ�ֶ����Headָ������ĵ�һ��Ԫ��
	cout << "���붥������:" << endl;
	cin >> graphsize;//���붥�����
	for (int i = 0;i < graphsize;i++)//��ʼ��Head����
	{
		Head[i].VerName = i;
		Head[i].adjacent = NULL;
	}
	cout << "����߽����:" << endl;
	cin >> e;//�������
	for (int i = 0;i < e;i++)//�����������
	{
		cout << "�����±ߵ�ʼ�㡢�յ�:" << endl;
		cin >> from >> to;//�����±ߵ�ʼ�㡢�յ�
		Edge* p = new Edge;//���±߲���ͼ��
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



void Graph_List::DepthFirstSearch(const int v, int* visited)//�����vΪ���������������ȱ���ͼ�ĵݹ��㷨
{
	cout << v << " ";//���v������
	visited[v] = 1;//˵��v�Ѿ������ʹ�
	Edge* p = Head[v].adjacent;//ȡ��v�ĵ�һ���ڽӶ�������
	while (p != NULL)//�����ڶ���p
	{
		if (visited[p->VerAdj] != 1)//��pδ�����ʹ�����p�ݹ����
			DepthFirstSearch(p->VerAdj, visited);
		p = p->link;//pΪc����p����һ���ڽӶ���
	}
}

void Graph_List::BFS(const int s)//�Ӷ���s��ʼ������ȱ���ͼ�ĵ����㷨��ʹ���˶���
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
	cout << "����������㣺" << endl;
	cin >> v;
	cout << "������ȣ�";
	L.DepthFirstSearch(v,visited);
	for (int i = 0;i < 100;i++)
	{
		visited[i] = 0;
	}
	cout << "�������:";
	L.BFS(v);
	return 0;
}