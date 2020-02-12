#include<iostream>
#include<vector>
using namespace std;

typedef struct node
{
	struct node* m_pLeft;
	struct node* m_pRight;
	char m_nValue;
}BinaryTreeNode, * BiTree;

//��ӡ·��
void printPath(vector<int>& path) {
	vector<int>::const_iterator iter = path.begin(); //��ӡ����
	for (; iter != path.end() - 1; ++iter)
		cout << *iter << "->";
	cout << *iter;
	cout << endl;//����
}


//Ѱ��ĳһ���ض����ӽڵ�
void findPath(BinaryTreeNode* pRoot, vector<int>& path, int nToFind) {
	if (pRoot == NULL)
	{
		return;
	}
	path.push_back(pRoot->m_nValue);
	if (pRoot->m_nValue == nToFind) //�ﵽ���ӽڵ�
	{
		printPath(path);
		return;      //�ҵ��˾ͷ��أ�����Ҫ������
	}
	if (pRoot->m_pLeft != NULL)//������
	{
		findPath(pRoot->m_pLeft, path, nToFind);
	}
	if (pRoot->m_pRight != NULL)//������
	{
		findPath(pRoot->m_pRight, path, nToFind);
	}
	//path.pop_back();//�ڷ��ص����ڵ�֮ǰ����·����ɾ����ǰ�ڵ�
}




//�ҵ�����·��
void findAllPath(BinaryTreeNode* pRoot, vector<int>& path) {
	if (pRoot == NULL)
	{
		return;
	}
	path.push_back(pRoot->m_nValue);
	if (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL) //�ﵽ��Ҷ�ӽڵ�
	{
		printPath(path);//��ӡ·��
	}
	if (pRoot->m_pLeft != NULL)//������
	{
		findAllPath(pRoot->m_pLeft, path);
	}
	if (pRoot->m_pRight != NULL)//������
	{
		findAllPath(pRoot->m_pRight, path);
	}
	path.pop_back();//�ڷ��ص����ڵ�֮ǰ����·����ɾ����ǰ�ڵ�
}




//���򴴽�������  
void CreatBTree(BinaryTreeNode*& root)
{
	int nValue = 0;
	cin >> nValue;
	if (-1 == nValue)//-1����Ϊ��
	{
		return;
	}
	else
	{
		root = new BinaryTreeNode();
		root->m_nValue = nValue;
		CreatBTree(root->m_pLeft);
		CreatBTree(root->m_pRight);
	}
}

//��ӡ����·��
void printAllPath(vector<vector<int> >& path) {
	for (int i = 0; i < path.size();i++)
	{
		printPath(path[i]);
	}
}


int main() {
	vector<vector<int> > allPath;
	BinaryTreeNode* T = NULL;
	cout << "���򹹽�������:" << endl;
	CreatBTree(T);
	cout << endl;
	cout << "�ҵ����и��ڵ㵽Ҷ�ӽڵ��·����" << endl;
	vector<int> path;
	findAllPath(T, path);
	cout << "��ӡ�õ�������·����" << endl;
	printAllPath(allPath);
	path.clear();
	int nNode;
	while (true)
	{
		cout << "����Ҫ�ҵ��ӽڵ�:" << endl;
		cin >> nNode;
		cout << "���ڵ㵽�ӽڵ�" << nNode << "��·����" << endl;
		findPath(T, path, nNode);
		cout << endl;
		path.clear();//����
	}
	return 0;
}