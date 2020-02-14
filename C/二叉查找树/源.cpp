#include<iostream>
using namespace std;
//书本p286如此构造
class BSTNode
{
public:
	BSTNode* llink;
	BSTNode* rlink;
	int key;
	BSTNode(const int& item, BSTNode* lptr = NULL, BSTNode* rptr = NULL):key(item),llink(lptr),rlink(rptr){}
};


class BSTree
{
public:
	BSTree(BSTNode* t = NULL):root(t){}
	bool Search_Insert(int k,int &count);
	BSTNode*& ReturnRoot() { return root; }
private:
	BSTNode*  root;
};


bool BSTree::Search_Insert(int k, int &count)//二叉查找树的查找和插入
{
	if (root == NULL)
	{
		root = new BSTNode(k, NULL, NULL);//如果树为空，直接插入结点k
		return false;
	}
	BSTNode* p = root;//初始化
	while (p != NULL)
	{
		if (k == p->key) return true;
		if (k < p->key)
		{
			if (p->llink == NULL) break;
			else
			{
				p = p->llink;
				count++;
			}
		}
		else
		{
			if (p->rlink == NULL) break;
			else
			{
				p = p->rlink;
				count++;
			}
		}
	}
	//至此，查找不成功，将包含关键词k的新结点插入树中
	BSTNode* q = new BSTNode(k, NULL, NULL);
	if (k < p->key) p->llink = q;
	else p->rlink = q;
	return false;
}



void InOrder(BSTNode* &t)//中序遍历
{
	if (t != NULL)
	{
		InOrder(t->llink);
		cout << t->key << " ";
		InOrder(t->rlink);
	}
}

int main()
{
	BSTNode * p;
	int item;//查找的变元
	int count = 0;//记录变元所在的层数
	BSTree t;//创建二叉查找树对象
	BSTNode* &q = t.ReturnRoot();
	cout << "输入查找的变元" << endl;
	cin >> item;
	while (item != 0)
	{
		if (!t.Search_Insert(item, count))//创建二叉查找树
		{
			InOrder(q);//中序遍历
			count = 0;
		}
		else
		{
			cout <<"层数："<< count << endl;//输出变元所在的层数
			count = 0;
			InOrder(q);//中序遍历
		}
		cout << endl;
		cout << "输入查找的变元" << endl;
		cin >> item;
	}
	
}