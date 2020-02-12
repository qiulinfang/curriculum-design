//1.����Ԥ����  ͷ�ļ�  �ṹ��  ��������
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"//��׼�������������
#include "stdlib.h"//��׼������
#include "string.h"//�ַ���������
#include "conio.h"//��Ļ����������
#define HEADER1 "-----------------------------------------STUDENT--------------------------------------------------  \n"
#define HEADER2 "|   number   |   name     |   Comp     |   Math     |   Eng     |   sum   |   ave   |   mici   |  \n "
#define HEADER3 "--------------------------------------------------------------------------------------------------------  \n "
#define FORMAT "|  %-7s   |  %-7s  |    %-7d |  %-11d |  %-7d |  %-7d |  %-.2f |  %-1d   |   \n "
#define DATA p->data.num,p->data.name,p->data.egrade,p->data.mgrade,p->data.cgrade,p->data.total,p->data.ave,p->data.mingci
#define END "-----------------------------------------------------------------------------------------------------------------    \n"

int saveflag = 0;//�Ƿ���Ҫ���̵ı�־����
//������ѧ���йص����ݽṹ
typedef  struct student
{
	char num[10];//ѧ��
	char name[15];//����
	int cgrade;//C���Գɼ�
	int mgrade;//��ѧ�ɼ�
	int egrade;//Ӣ��ɼ�
	int total;//�ܷ�
	float ave;//ƽ����
	int mingci;//����
};

typedef struct node
{
	struct student data;//������
	struct node* next;//ָ����
}Node,*Link;//NodeΪnode�͵Ľṹ������*linkΪnode�͵�ָ�����

void printheader();//��ӡ�����ͷ��Ϣ
void printdata(Node *pp);//��ӡ���ѧ����Ϣ
void stringinput(char* t, int lens, char* notice);//�����ַ���
int numberinput(char* notice);//������ֵ������
void Disp(Link l);//��ʾ������l�д洢��ѧ����¼
Node* Locate(Link l, char findmess[], char nameornum);//��λ�����з���Ҫ��Ľڵ�
void Add(Link l);//����ѧ����¼
void Qur(Link l);//��ѯѧ����¼
void Del(Link l);//ɾ��ѧ����¼
void Modify(Link l);//�޸�ѧ����¼
void Insert(Link l);//����ѧ����¼
void Tongji(Link l);//ͳ����߷ֺͲ�������
void Sort(Link l);//�ò�������ʵ�ֵ�����İ��ܷ��ֶεĽ�������
void Save(Link l);//��������l������д�����
void Wrong();
void Nofind();
void  menu();
//2.������
int main()
{
	Link l;//��������
	FILE* fp;//�ļ�ָ��
	int select;//����ѡ��ṹ����
	char ch;//���棨Y��y��N��n��
	int count = 0;//�����ļ��еļ�¼��������ڵ���Ŀ��
	Node* p, * r;//�����¼ָ�����
	l = (Node*)malloc(sizeof(Node));//����ͷ���
	if (!l)
	{
		printf("\n  allocate memory failure");
		return 0;
	}
	l->next = NULL;
	r = l;
	fp = fopen("F:\\student", "ab+");//��׷�ӷ�ʽ��һ���������ļ����ɶ���д�������ļ������ڣ��ᴴ�����ļ�
	if (fp == NULL)
	{
		printf("\n=======>can not open file!\n");
		exit(0);
	}
	while (!feof(fp))
	{
		p = (Node*)malloc(sizeof(Node));
		if (!p)
		{
			printf("\n  allocate memory failure");
			return 0;
		}
		if (fread(p, sizeof(Node), 1, fp) == 1)//һ�δ��ļ��ж�ȡһ��ѧ���ɼ���¼
		{
			p->next = NULL;
			r->next = p;
			r = p;//rָ������ƶ�һ��λ��
			count++;
		}
	}
	fclose(fp);//�ر��ļ�
	printf("\n========>open file sucess, the total records number is : %d.\n", count);//��ʵ��ʾ��ϵ
	menu();
	while (1)
	{
		system("cls");
		menu();
		p = r;
		printf("\n  Please enter your choice(0~9):");
		scanf("%d", &select);
		if (select == 0)
		{
			if (saveflag == 1)//����������������޸���δ���д��̲�������˱�־Ϊ1
			{
				printf("\n =====>Whether save the modified record to file?(y/n):");
				scanf("%c", &ch);
				if (ch == 'Y' || ch == 'y')
				{
					Save(l);
				}
			}
			printf("======>thank you for useness!");
			system("pause");
			break;
		}
		switch (select)
		{
		case 1: Add(l);break;
		case 2: Del(l);break;
		case 3: Qur(l);break;
		case 4: Modify(l);break;
		case 5: Insert(l);break;
		case 6: Tongji(l);break;
		case 7: Sort(l);break;
		case 8: Save(l);break;
		case 9: system("cls");Disp(l);break;
		default: Wrong();system("pause");break;
		}
	}
}

//3.���˵�����
void  menu()
{
	system("cls");
	printf("                       The Students' Grade Management System                \n ");
	printf("********************************menu*************************************\n");
	printf("           * 1 input record                                          2 delete record*\n");
	printf("           * 3 search record                                       4 modify record*\n");
	printf("           * 5 insearch record                                    6 count record*\n");
	printf("           * 7 sort record                                            8 save record*\n");
	printf("           * 9 display record                                       0 quit record*\n");
	printf("********************************menu*************************************\n");
}

//4.�����ʽ��ʾ��¼
void printheader()//��ʽ�������ͷ
{
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);	
}
void printdata(Node* pp)//��ʽ�������������
{
	Node* p;
	p = pp;
	printf(FORMAT, DATA);
}
void Disp(Link l)
{
	Node* p;
	p = l->next;// l �洢��ʿ��������ͷ�ڵ��ָ�룬��ͷ�ڵ�û�д洢ѧ����Ϣ��ָ����ָ��ĺ�̽ڵ����ѧ����Ϣ
	if (!p)
	{
		printf("\n============>Not student record!\n");
		system("pause");
		return;
	}
	printf("\n\n");
	printheader();//������ͷ��
	while (p)//������������д洢��ѧ����Ϣ
	{
		printdata(p);
		p = p->next;//�ƶ�ָ����һ�ڵ�
		printf(HEADER3);
	}
	system("pause");
}
void Wrong()//�������������Ϣ
{
	printf("\n\n\n\n***************Error:input has wrong! press any key to continue******************\n");
	system("pause");
}
void Nofind()//���δ���Ҵ�ѧ������Ϣ
{
	printf("\n=========>Not find this student!\n");
}

//5.��¼���Ҷ�λ
Node* Locate(Link l, char findmess[], const char nameornum[])// l ������findmess��������Ҫ���ҵ����ݣ�nameornum�������水ʲô�ֶ��ڵ����� l �н��в���
{
	Node* r;
	if (strcmp(nameornum, "num") == 0)//��ѧ�Ų�ѯ
	{
		r = l->next;
		while (r)
		{
			if (strcmp(r->data.num, findmess) == 0)//���ҵ�findmessֵ��ѧ��
				return r;
			r = r->next;
		}
	}
	else if (strcmp(nameornum,"name") == 0)//��������ѯ
	{
		r = l->next;
		while (r)
		{
			if (strcmp(r->data.name, findmess) == 0)//���ҵ�findmessֵ��ѧ������
				return r;
			r = r->next;
		}
	}
	return 0;//��δ�ҵ������ؿ�ָ��
}

//6.��ʽ����������
void stringinput(char t[], int lens,const char notice[])
{
	char n[255];
	do
	{
		printf(notice);//��ʾ��ʾ��Ϣ
		scanf("%s", n);//�����ַ���
		if (int(strlen(n)) > lens) printf("\n exceed the required length! \n");//�Գ��Ƚ���У�飬����lensֵ��������
	} while (strlen(n) > lens);
	strcpy(t, n);//��������ַ������Ƶ��ַ���t
}

int numberinput(const char notice[])
{
	int t = 0;
	do
	{
		printf(notice);//��ʾ��ʾ��Ϣ
		scanf("%d", &t);//�������
		if (t > 100 || t < 0)printf("\n scorre must int [0,100]! \n");//���з���У��
	} while (t > 100 || t < 0);
	return t;
}

//7.����ѧ����¼
void Add(Link l)
{
	Node* p, * r, * s;//ʵ�ֲ�������ʱ�Ľṹ��ָ����� rλ������ĩβ����Ӽ�¼��s���ڱ���l����ѧ���Ƿ���ڣ�p���������ڴ�ռ�
	char ch, flag, num[10];//ch ���� y/Y��flag��ʾ�Ƿ���������ѧ�ţ�num��10������������ַ���
	r = l;
	system("cls");
	Disp(l);//�ȴ�ӡ�����е�ѧ����Ϣ
	while (r->next != NULL)//��ָ����������ĩβ��׼����Ӽ�¼
		r = r->next;
	while (l)//һ�ο����������¼��ֱ������ѧ��Ϊ0�ļ�¼�ڵ���Ӳ���
	{
		while (l)//����ѧ�ţ���֤��ѧ��û�б�ʹ�ã�������Ϊ0�����˳���Ӽ�¼����
		{
			stringinput(num, 10, "input number (press '0' return menu):");//��ʽ������ѧ�Ų�����
			flag = 0;
			if (strcmp(num, "0") == 0)//����Ϊ0�����˳���Ӳ���������������
				return;
			s = l->next;
			while (s)//��ѯ��ѧ���Ƿ��Ѿ����ڣ���������Ҫ����������һ��δ��ռ�õ�ѧ��
			{
				if (strcmp(s->data.num, num) == 0)
				{
					flag = 1;//ѧ���Ѵ���
					break;
				}
				s = s->next;
			}
			if (flag == 1)//��ʾ�û��Ƿ���������
			{
				printf("=======>The number %s is existing,try again?(y/n):", num);
				scanf(" %c", &ch);//ǰ���ո�������scanf�����������пհ��ַ�
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					return; //������ӽڵ�
			}
			else//ѧ��δ����
				break;
		}
		p = (Node*)malloc(sizeof(Node));//�����ڴ�ռ�
		if (!p)
		{
			printf(" \n allocate memory failure");//���û���뵽����ӡ��ʾ��Ϣ
			return;//����������
		}
		strcpy(p->data.num, num);//���ַ���num���Ƶ�p->data.num��
		stringinput(p->data.name, 15, "Name:");
		p->data.cgrade = numberinput("C language Score[0-100]:");//���벢�������
		p->data.mgrade = numberinput("Math Score[0-100]:");//���벢�������
		p->data.egrade = numberinput("English Score[0-100]:");//���벢�������
		p->data.total = p->data.cgrade + p->data.mgrade + p->data.egrade;
		p->data.ave = (float)(p->data.total / 3);
		p->data.mingci = 0;
		p->next = NULL;//�������������β���
		r->next = p;//���½��Ľڵ���������β����
		r = p;
		saveflag = 1;
	}
}

//8.��ѯѧ����¼
void Qur(Link l)
{
	int select;// 1 ��ѧ�Ų� 2 ����������
	char searchinput[20];//�����û�����Ĳ�ѯ����
	Node* p;
	if (! l->next)//������Ϊ��
	{
		system("cls");
		printf(" \n =====> No student record!\n");
		system("pause");
		return;
	}
	system("cls");
	printf("\n ========>1 Search by number =========>2 Search by name\n");
	printf("please choice[1,2]:");
	scanf("%d", &select);
	if (select == 1)//��ѧ�Ų���
	{
		stringinput(searchinput, 10, "input the existing student number:");
		p = Locate(l, searchinput, "num");
		if (p)
		{
			printheader();
			printdata(p);
			printf(END);
			printf("press any key to return");
			system("pause");
		}
		else {
			Nofind();
			system("pause");
		}
	}
	else if (select == 2)//����������
	{
		stringinput(searchinput, 15, "input the existing student name:");
		p = Locate(l, searchinput, "num");
		if (p)
		{
			printheader();
			printdata(p);
			printf(END);
			printf("press any key to return");
			system("pause");
		}
		else {
			Nofind();
			system("pause");
		}
	}
	else {
		Wrong();
		system("pause");
	}
}


//9.ɾ��ѧ����¼
void Del(Link l)
{
	int sel;
	Node* p, * r;
	char findmess[20];
	if (! l->next)
	{
		system("cls");
		printf("\n=======>No student record!\n");
		system("pause");
		return;//������ҳ��
	}
	Disp(l);
	printf("\n ========>1 Delete by number =========>2 Delete by name\n");
	printf("please choice[1,2]:");
	scanf("%d", &sel);
	if (sel == 1)//��ѧ�Ų���
	{
		stringinput(findmess, 10, "input the existing student number:");
		p = Locate(l, findmess, "num");
		if (p)
		{
			r = l;
			while (r->next != p)
				r = r->next;
			r->next = p->next;
			free(p);
			printf("\n=========>Delete success!\n");
			system("pause");
			saveflag = 1;//δ����
		}
		else {
			Nofind();
			system("pause");
		}
	}
	else if (sel == 2)//����������
	{
		stringinput(findmess, 15, "input the existing student name:");
		p = Locate(l, findmess, "num");
		if (p)
		{
			r = l;
			while (r->next != p)
				r = r->next;
			r->next = p->next;
			free(p);
			printf("\n=========>Delete success!\n");
			system("pause");
			saveflag = 1;//δ����
		}
		else {
			Nofind();
			system("pause");
		}
	}
	else {
		Wrong();
		system("pause");
	}
}

//10.�޸�ѧ����¼
void Modify(Link l)
{
	Node* p;
	char findmess[20];
	if (!l->next)
	{
		system("cls");
		printf("\n======>No student record \n");
		system("pause");
		return;
	}
	system("cls");
	printf("modify student record");
	Disp(l);
	stringinput(findmess, 10, "input the existing student number:");//���벢�����ѧ��
	p = Locate(l, findmess, "num");//��ѯ���ýڵ�
	if (p)//��p��=NULL�������Ѿ��ҵ��ýڵ�
	{
		printf("Number:%s,\n", p->data.num);
		printf("Name:%s,\n", p->data.name);
		stringinput(p->data.name, 15, "input new name:");
		printf("C language score:%d", p->data.cgrade);
		p->data.cgrade = numberinput("C language Score[0-100]:");
		printf("Math score:%d", p->data.mgrade);
		p->data.mgrade = numberinput("Math score[0-100]:");
		printf("English score:%d", p->data.egrade);
		p->data.egrade = numberinput("English score[0-100]:");
		p->data.total = p->data.egrade + p->data.cgrade + p->data.mgrade;
		p->data.ave = (float)(p->data.total / 3);
		p->data.mingci = 0;
		printf("\n========>modify success!\n");
		Disp(l);
		saveflag = 1;
	}
	else {
		Nofind();
		system("pause");
	}
}

//11.����ѧ����¼
void Insert(Link l)
{
	Link p, v, newinfo;//Link��node���͵�ָ�������p����������v����������newinfo���������µĽڵ�
	char ch, num[10], s[10];//ch����y/Y��s��������λ��֮ǰ��ѧ�ţ�num����������¼�¼��ѧ��
	int flag = 0;//�ж�ѧ�ŷǷ����
	system("cls");
	Disp(l);
	while (l)
	{
		stringinput(s, 10, "please input insert location after the Number:");
		flag = 0;
		v = l->next;
		while (v)//��ѯ��ѧ���Ƿ���ڣ�flag=1��ʾ��ѧ�Ŵ���
		{
			if (strcmp(v->data.num, s) == 0) { flag = 1;break; }
			v = v->next;
		}
		if (flag == 1)
			break;//��ѧ�Ŵ��ڣ�����в���֮ǰ���¼�¼���������
		else
		{
			system("pause");
			printf("\n====>The number %s is not existing,try again?(y/n):", s);
			scanf("%c", &ch);
			if (ch == 'Y' || ch == 'y')
				continue;
			else
				return;
		}
	}

	//�����¼�¼�����������Add()��ͬ
		stringinput(num, 10, "input new student Numer:");
		v = l->next;
		while (v)
		{
			if (strcmp(v->data.num,num) == 0)
			{
				printf("==========>Sorry,the new number:'%s' is existing!\n", num);
				printheader();
				printdata(v);
				printf("\n");
				system("pause");
				return;
			}
			v = v->next;
		}
		newinfo = (Node*)malloc(sizeof(Node));
		if (!newinfo)
		{
			printf("\n allocate menory failure");//û�����뵽�ռ�
			return;//����������
		}
		strcpy(newinfo->data.num, num);
		stringinput(newinfo->data.name, 15, "Name:");
		newinfo->data.cgrade = numberinput("C language Score[0-100]:");
		newinfo->data.mgrade = numberinput("Math Score[0-100]:");
		newinfo->data.egrade = numberinput("English Score[0-100]:");
		newinfo->data.total = newinfo->data.egrade + newinfo->data.cgrade + newinfo->data.mgrade;
		newinfo->data.ave = (float)(newinfo->data.total / 3);
		newinfo->data.mingci = 0;
		newinfo->next = NULL;
		saveflag = 1;
		//��main�����жԸ�ȫ�ֱ������жϣ���Ϊ1������д��̲���
		//��ָ�븳ֵ��p����Ϊl�е�ͷ�ڵ����һ���ڵ��ʵ�ʱ�����ѧ���ļ�¼
		p = l->next;
		while (l)
		{
			if (strcmp(p->data.num,s)==0)//�������в���һ���ڵ�
			{
				newinfo->next = p->next;
				p->next = newinfo;
				break;
			}
			p = p->next;
		}

		Disp(l);
		printf("\n");
		system("pause");
}

//12.ͳ��ѧ����¼
void Tongji(Link l)
{
	Node* pm, * pe, * pc, * pt;//����ָ����߷ֵĽڵ�
	Node* r = l->next;
	int countc = 0, countm = 0, counte = 0;//�������ųɼ��в����������
	if (!r)
	{
		system("cls");
		printf("\n======>Not sutdent record!\n");
		system("pause");
		return;
	}
	system("cls");
	Disp(l);
	pm = pe = pc = pt = r;
	while (r)
	{
		if (r->data.cgrade < 60) countc++;
		if (r->data.mgrade < 60) countm++;
		if (r->data.egrade < 60) counte++;
		if (r->data.cgrade >= pc->data.cgrade) pc = r;
		if (r->data.mgrade >= pc->data.mgrade) pm = r;
		if (r->data.egrade >= pc->data.egrade) pe = r;
		r = r->next;
	}
	printf("\n-----------------------------------the Tongji result---------------------------------------\n");
	printf("C language < 60: %d(ren)\n", countc);
	printf("Math            < 60: %d(ren)\n", countm);
	printf("English        < 60: %d(ren)\n", counte);
	printf("\n------------------------------------------------------------------------------------------------\n");
	printf("The highest student by total score name:%s total score:%d\n", pt->data.name, pt->data.total);
	printf("The highest student by English score name:%s total score:%d\n", pt->data.name, pt->data.egrade);
	printf("The highest student by Math score name:%s total score:%d\n", pt->data.name, pt->data.mgrade);
	printf("The highest student by C score name:%s total score:%d\n", pt->data.name, pt->data.cgrade);
	printf("\n\npress any key to return");
	system("pause");
}

//13.����ѧ����Ϣ
void Sort(Link l)
{
	Link ll;
	Node* p, * rr, * s;//p����l��rr����ll��s����ڵ�
	int i = 0;
	if (l->next == NULL)
	{
		system("cls");
		printf("\n==========>Not student record!\n");
		system("pause");
		return;
	}
	ll = (Node*)malloc(sizeof(Node));
	if (!ll)//���ڴ����µĽڵ�
	{
		printf("\n allocate memory failure");
		return;//����������
	}
	ll->next = NULL;
	system("cls");
	Disp(l);//��ʾ����ǰ������ѧ����¼
	p = l->next;
	while (p)
	{
		s = (Node*)malloc(sizeof(Node));//�½��ڵ����ڱ����ԭ������ȡ���Ľڵ���Ϣ
		if (!s)
		{
			printf("\n allocate memory failure");//���û�����뵽����ӡ��ʾ��Ϣ
			return;//����������
		}
		s->data = p->data;//��������
		s->next = NULL;//ָ����Ϊ��
		rr = ll;
		//��������
		while (rr->next != NULL && rr->next->data.total >= p->data.total)//rr�����ڴ洢���뵥���ڵ�󱣳����������
			//ll����������ͷָ�룬ÿ�δ�ͷ��ʼ���Ҳ���λ��
		{
			rr = rr->next;//ָ�������ֱܷ�p��ָ�Ľڵ���ܷ�С�Ľڵ�λ��
		}
		if (rr->next == NULL)//��������ll�е����нڵ���ܷ�ֵ����p->data.total��ʱ���ͽ�p��ָ�ڵ��������β��
			rr->next = s;
		else//���򽫸ýڵ��������һ���ܷ��ֶα���С�Ľڵ��ǰ��
		{
			s->next = rr->next;
			rr->next = s;
		}
		p = p->next;//ԭ�����е�ָ������һ���ڵ�
	}
	l->next = ll->next;//ll�д洢����������������ͷָ��
	p = l->next;//���ź����ͷָ�븳��p��׼����д����
	while (p!=NULL)
	{
		i++;//�ڵ����
		p->data.mingci = i;//�����θ�ֵ
		p = p->next;//ָ�����
	}
	Disp(l);
	saveflag = 1;
	printf("\n========>sort complete!\n");
}


//14.�洢ѧ����¼
void Save(Link l)
{
	FILE* fp;
	Node* p;
	int count = 0;
	fp = fopen("F:\\student", "wb");//��ֻд��ʽ�򿪶������ļ�
	if (fp == NULL)//���ļ�ʧ��
	{
		printf("\n=======>open file error!\n");
		system("pause");
		return;
	}
	p = l->next;
	while (p)
	{
		if (fwrite(p, sizeof(Node), 1, fp) == 1)//ÿ��дһ����¼��һ���ڵ���Ϣ���ļ�
		{
			p = p->next;
			count++;
		}
		else
		{
			break;
		}
	}
	if (count > 0)
	{
		printf("\n\n\n\n\n=========>save file complete,total saved's record number is :%d\n", count);
		system("pause");
		saveflag = 0;
	}
	else
	{
		system("cls");
		printf("the current link is empty,no student record is saved!\n");
		system("pause");
		fclose(fp);//�رմ��ļ�
	}
}