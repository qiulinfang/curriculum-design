#include<iostream>
using namespace std;
//�鱾p286��˹���
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


bool BSTree::Search_Insert(int k, int &count)//����������Ĳ��ҺͲ���
{
	if (root == NULL)
	{
		root = new BSTNode(k, NULL, NULL);//�����Ϊ�գ�ֱ�Ӳ�����k
		return false;
	}
	BSTNode* p = root;//��ʼ��
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
	//���ˣ����Ҳ��ɹ����������ؼ���k���½���������
	BSTNode* q = new BSTNode(k, NULL, NULL);
	if (k < p->key) p->llink = q;
	else p->rlink = q;
	return false;
}



void InOrder(BSTNode* &t)//�������
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
	int item;//���ҵı�Ԫ
	int count = 0;//��¼��Ԫ���ڵĲ���
	BSTree t;//�����������������
	BSTNode* &q = t.ReturnRoot();
	cout << "������ҵı�Ԫ" << endl;
	cin >> item;
	while (item != 0)
	{
		if (!t.Search_Insert(item, count))//�������������
		{
			InOrder(q);//�������
			count = 0;
		}
		else
		{
			cout <<"������"<< count << endl;//�����Ԫ���ڵĲ���
			count = 0;
			InOrder(q);//�������
		}
		cout << endl;
		cout << "������ҵı�Ԫ" << endl;
		cin >> item;
	}
	
}