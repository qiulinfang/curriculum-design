#include<iostream>
#include<vector>
using namespace std;

typedef struct node
{
	struct node* m_pLeft;
	struct node* m_pRight;
	char m_nValue;
}BinaryTreeNode, * BiTree;

//打印路径
void printPath(vector<int>& path) {
	vector<int>::const_iterator iter = path.begin(); //打印出来
	for (; iter != path.end() - 1; ++iter)
		cout << *iter << "->";
	cout << *iter;
	cout << endl;//换行
}


//寻找某一个特定的子节点
void findPath(BinaryTreeNode* pRoot, vector<int>& path, int nToFind) {
	if (pRoot == NULL)
	{
		return;
	}
	path.push_back(pRoot->m_nValue);
	if (pRoot->m_nValue == nToFind) //达到了子节点
	{
		printPath(path);
		return;      //找到了就返回，不需要再找了
	}
	if (pRoot->m_pLeft != NULL)//左子树
	{
		findPath(pRoot->m_pLeft, path, nToFind);
	}
	if (pRoot->m_pRight != NULL)//右子树
	{
		findPath(pRoot->m_pRight, path, nToFind);
	}
	//path.pop_back();//在返回到父节点之前，在路径上删除当前节点
}




//找到所有路径
void findAllPath(BinaryTreeNode* pRoot, vector<int>& path) {
	if (pRoot == NULL)
	{
		return;
	}
	path.push_back(pRoot->m_nValue);
	if (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL) //达到了叶子节点
	{
		printPath(path);//打印路径
	}
	if (pRoot->m_pLeft != NULL)//左子树
	{
		findAllPath(pRoot->m_pLeft, path);
	}
	if (pRoot->m_pRight != NULL)//右子树
	{
		findAllPath(pRoot->m_pRight, path);
	}
	path.pop_back();//在返回到父节点之前，在路径上删除当前节点
}




//先序创建二叉树  
void CreatBTree(BinaryTreeNode*& root)
{
	int nValue = 0;
	cin >> nValue;
	if (-1 == nValue)//-1代表为空
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

//打印所有路径
void printAllPath(vector<vector<int> >& path) {
	for (int i = 0; i < path.size();i++)
	{
		printPath(path[i]);
	}
}


int main() {
	vector<vector<int> > allPath;
	BinaryTreeNode* T = NULL;
	cout << "先序构建二叉树:" << endl;
	CreatBTree(T);
	cout << endl;
	cout << "找到所有根节点到叶子节点的路径：" << endl;
	vector<int> path;
	findAllPath(T, path);
	cout << "打印得到的所有路径：" << endl;
	printAllPath(allPath);
	path.clear();
	int nNode;
	while (true)
	{
		cout << "输入要找的子节点:" << endl;
		cin >> nNode;
		cout << "根节点到子节点" << nNode << "的路径：" << endl;
		findPath(T, path, nNode);
		cout << endl;
		path.clear();//清零
	}
	return 0;
}