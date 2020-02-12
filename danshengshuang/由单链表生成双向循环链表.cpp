#include<iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>


struct LNode{
	int data;
	LNode *next;
}; 


LNode *Creat_LinkList2(){
	LNode *L;
	LNode *s,*r = NULL;
	int x;
	L = new LNode;
	L->next = NULL;
	cout << "������ֵ��Ϊ0����" << endl;
	cin>>x;
	while(x != 0){
		s = new LNode;
		s->data = x;
		if(L->next == NULL){
			L->next = s;
		}else{
			r->next = s;
		}
		r = s;
		cout << "������ֵ��Ϊ0����" << endl;
		cin>>x;
	}
	if(r != NULL){
		r->next = NULL;
	}
	return L;
}

int Length_LinkList(LNode *L){
	LNode *p;
	int i;
	p = L->next;
	i = 0;
	while(p){
		i++;
		p = p->next;
	}
	return i;
}

LNode *Get_LinkList(LNode *L, int i){
	LNode *p;
	int j;
	p = L->next;
	j = 1;
	while(p != NULL && j < i){
		p = p->next;
		j++;
	}
	return p;
} 

LNode *Locate_LinkList(LNode *L, int x){
	LNode *p;
	p = L->next;
	while(p != NULL && p->data != x){
		p = p->next;
	}
	return p;
} 

int Insert_LinkList(LNode *L, int i, int x){
	LNode *p, *s;
	int j;
	p = L->next;
	j = 1;
	while(p != NULL && j < i){
		p = p->next;
		j++;
	}
	if(p == NULL){
		return 0;
	}else{
		s = new LNode;
		s->data = x;
		s->next = p->next;
		p->next = s;
		return 1;
	}
}

int Del_LinkList(LNode *L, int i){
	LNode *p, *s;
	int j;
	p = L->next;
	j = 1;
	while(p != NULL && j < i){
		p = p->next;
		j++;
	}
	if(p == NULL){
		return -1;
	}else if(p->next == NULL){
			return 0;
			}else{
				s = p->next;
				p->next = s->next;
				delete s;
				return 1;
		}
}

int Print_LinkList(LNode *L){
	LNode *p;
	p = L->next;
	if(p == NULL){
		return -1;
	}else{
		while(p){
			cout<<p->data<<"->";
			p = p->next;
		}
		return 1;
	}
}

int Max_LinkList(LNode *L){
	LNode *p;
	p = L->next;
	int Max = p->data;
	while(p->next){
		p = p->next;
		int temp;
		temp = p->data;
		if(temp > Max){
			Max = temp;
		}
	}
	return Max;
}

int Min_LinkList(LNode *L){
	LNode *p;
	p = L->next;
	int Min = p->data;
	while(p->next){
		p = p->next;
		int temp;
		temp = p->data;
		if(temp < Min){
			Min = temp;
		}
	}
	return Min;
}

void BubbleSort(LNode *head)
{
	LNode *f, *p, *x, *y;
	f = NULL;
	//�ж��Ƿ�ֻ��һ��Ԫ�ػ���û��Ԫ��
	if(head -> next == NULL || head -> next -> next == NULL)
	{
		return;
	}
	while(f != head->next->next)
	{
		//�����N - 1��ѭ��,����
		for(p = head; p -> next -> next != f; p = p -> next)
		{
			if(p -> next -> data > p -> next -> next ->data)
			{
				x = p -> next;
				y = p -> next -> next;
				p -> next = y;
				x -> next = y -> next;
				y -> next = x;
			}
		}
		f = p -> next;
	}
}



typedef struct Node
{
	int data;
	struct Node *pNext;
	struct Node *pPre;
}NODE, *pNODE;

pNODE CreateDbCcLinkList(void)
{
	int i, length = 0, data = 0;
	pNODE p_new = NULL, pTail = NULL;
	pNODE pHead = (pNODE)malloc(sizeof(NODE));
 
	if (NULL == pHead)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(EXIT_FAILURE);
	}
	pHead->data = 0;
	pHead->pNext = pHead;
	pHead->pPre = pHead;
	pTail = pHead;
 
	printf("��������Ҫ��������ĳ��ȣ�");
	scanf_s("%d", &length);
 
	for (i=1; i<length+1; i++)
	{
		p_new = (pNODE)malloc(sizeof(NODE));
 
		if (NULL == p_new)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			exit(EXIT_FAILURE);
		}
 
		printf("�������%d���ڵ�Ԫ��ֵ��", i);
		scanf_s("%d", &data);
 
		p_new->data = data;
		p_new->pPre = pTail;
		p_new->pNext = pHead;
		pTail->pNext = p_new;
		pHead->pPre = p_new;
		pTail = p_new;
	}
	return pHead;
}

void TraverseDbCcLinkList(pNODE pHead)
{
	pNODE pt = pHead->pNext;
	while (pt != pHead)
	{
		printf("%d ", pt->data);
		pt = pt->pNext;
	}
	putchar('\n');
}

int main(){
	LNode *L;
	cout << "������������" << endl;
	L = Creat_LinkList2();
	Print_LinkList(L);
	printf("\n");
	cout << "ð������" << endl;
	BubbleSort(L);
	printf("\n");
	Print_LinkList(L);
	printf("\n");
	cout << "�����ȡ���С��㡢�����" << Length_LinkList(L) <<"\n"<< Max_LinkList(L) << "\n" << Min_LinkList(L);
	pNODE D;
	printf("\n");
	cout << "����˫������" << endl;
	D = CreateDbCcLinkList(); 
	TraverseDbCcLinkList(D);
}
