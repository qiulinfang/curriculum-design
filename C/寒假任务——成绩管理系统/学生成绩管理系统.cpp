//1.程序预处理  头文件  结构体  常量变量
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"//标准输入输出函数库
#include "stdlib.h"//标准函数库
#include "string.h"//字符串函数库
#include "conio.h"//屏幕操作函数库
#define HEADER1 "-----------------------------------------STUDENT--------------------------------------------------  \n"
#define HEADER2 "|   number   |   name     |   Comp     |   Math     |   Eng     |   sum   |   ave   |   mici   |  \n "
#define HEADER3 "--------------------------------------------------------------------------------------------------------  \n "
#define FORMAT "|  %-7s   |  %-7s  |    %-7d |  %-11d |  %-7d |  %-7d |  %-.2f |  %-1d   |   \n "
#define DATA p->data.num,p->data.name,p->data.egrade,p->data.mgrade,p->data.cgrade,p->data.total,p->data.ave,p->data.mingci
#define END "-----------------------------------------------------------------------------------------------------------------    \n"

int saveflag = 0;//是否需要存盘的标志变量
//定义与学生有关的数据结构
typedef  struct student
{
	char num[10];//学号
	char name[15];//姓名
	int cgrade;//C语言成绩
	int mgrade;//数学成绩
	int egrade;//英语成绩
	int total;//总分
	float ave;//平均分
	int mingci;//名次
};

typedef struct node
{
	struct student data;//数据域
	struct node* next;//指针域
}Node,*Link;//Node为node型的结构变量，*link为node型的指针变量

void printheader();//打印输出表头信息
void printdata(Node *pp);//打印输出学生信息
void stringinput(char* t, int lens, char* notice);//输入字符串
int numberinput(char* notice);//输入数值型数据
void Disp(Link l);//显示单链表l中存储的学生记录
Node* Locate(Link l, char findmess[], char nameornum);//定位链表中符合要求的节点
void Add(Link l);//增加学生记录
void Qur(Link l);//查询学生记录
void Del(Link l);//删除学生记录
void Modify(Link l);//修改学生记录
void Insert(Link l);//插入学生记录
void Tongji(Link l);//统计最高分和不及格率
void Sort(Link l);//用插入排序实现单链表的按总分字段的降序排序
void Save(Link l);//将单链表l中数据写入磁盘
void Wrong();
void Nofind();
void  menu();
//2.主函数
int main()
{
	Link l;//定义链表
	FILE* fp;//文件指针
	int select;//保存选择结构变量
	char ch;//保存（Y，y，N，n）
	int count = 0;//保存文件中的记录条数（或节点数目）
	Node* p, * r;//定义记录指针变量
	l = (Node*)malloc(sizeof(Node));//创建头结点
	if (!l)
	{
		printf("\n  allocate memory failure");
		return 0;
	}
	l->next = NULL;
	r = l;
	fp = fopen("F:\\student", "ab+");//以追加方式打开一个二进制文件，可读可写，若此文件不存在，会创建此文件
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
		if (fread(p, sizeof(Node), 1, fp) == 1)//一次从文件中读取一条学生成绩记录
		{
			p->next = NULL;
			r->next = p;
			r = p;//r指针向后移动一个位置
			count++;
		}
	}
	fclose(fp);//关闭文件
	printf("\n========>open file sucess, the total records number is : %d.\n", count);//现实提示星系
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
			if (saveflag == 1)//若对链表的数据有修改且未进行存盘操作，则此标志为1
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

//3.主菜单界面
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

//4.表格形式显示记录
void printheader()//格式化输出表头
{
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);	
}
void printdata(Node* pp)//格式化输出表中数据
{
	Node* p;
	p = pp;
	printf(FORMAT, DATA);
}
void Disp(Link l)
{
	Node* p;
	p = l->next;// l 存储的士单链表中头节点的指针，该头节点没有存储学生信息，指针域指向的后继节点才有学生信息
	if (!p)
	{
		printf("\n============>Not student record!\n");
		system("pause");
		return;
	}
	printf("\n\n");
	printheader();//输出表格头部
	while (p)//逐条输出链表中存储的学生信息
	{
		printdata(p);
		p = p->next;//移动指向下一节点
		printf(HEADER3);
	}
	system("pause");
}
void Wrong()//输出按键错误信息
{
	printf("\n\n\n\n***************Error:input has wrong! press any key to continue******************\n");
	system("pause");
}
void Nofind()//输出未查找此学生的信息
{
	printf("\n=========>Not find this student!\n");
}

//5.记录查找定位
Node* Locate(Link l, char findmess[], const char nameornum[])// l 是链表，findmess【】保存要查找的内容，nameornum【】保存按什么字段在单链表 l 中进行查找
{
	Node* r;
	if (strcmp(nameornum, "num") == 0)//按学号查询
	{
		r = l->next;
		while (r)
		{
			if (strcmp(r->data.num, findmess) == 0)//若找到findmess值的学号
				return r;
			r = r->next;
		}
	}
	else if (strcmp(nameornum,"name") == 0)//按姓名查询
	{
		r = l->next;
		while (r)
		{
			if (strcmp(r->data.name, findmess) == 0)//若找到findmess值的学生姓名
				return r;
			r = r->next;
		}
	}
	return 0;//若未找到，返回空指针
}

//6.格式化输入数据
void stringinput(char t[], int lens,const char notice[])
{
	char n[255];
	do
	{
		printf(notice);//显示提示信息
		scanf("%s", n);//输入字符串
		if (int(strlen(n)) > lens) printf("\n exceed the required length! \n");//对长度进行校验，超过lens值重新输入
	} while (strlen(n) > lens);
	strcpy(t, n);//将输入的字符串复制到字符串t
}

int numberinput(const char notice[])
{
	int t = 0;
	do
	{
		printf(notice);//显示提示信息
		scanf("%d", &t);//输入分数
		if (t > 100 || t < 0)printf("\n scorre must int [0,100]! \n");//进行分数校验
	} while (t > 100 || t < 0);
	return t;
}

//7.增加学生记录
void Add(Link l)
{
	Node* p, * r, * s;//实现操作的临时的结构体指针变量 r位于链表末尾，添加记录；s用于遍历l，看学号是否存在；p用于申请内存空间
	char ch, flag, num[10];//ch 接收 y/Y，flag提示是否重新输入学号，num【10】接受输入的字符串
	r = l;
	system("cls");
	Disp(l);//先打印出已有的学生信息
	while (r->next != NULL)//将指针移至链表末尾，准备添加记录
		r = r->next;
	while (l)//一次可输入多条记录，直至输入学号为0的记录节点添加操作
	{
		while (l)//输入学号，保证该学号没有被使用，若输入为0，则退出添加记录操作
		{
			stringinput(num, 10, "input number (press '0' return menu):");//格式化输入学号并检验
			flag = 0;
			if (strcmp(num, "0") == 0)//输入为0，则退出添加操作，返回主界面
				return;
			s = l->next;
			while (s)//查询该学号是否已经存在，若存在则要求重新输入一个未被占用的学号
			{
				if (strcmp(s->data.num, num) == 0)
				{
					flag = 1;//学号已存在
					break;
				}
				s = s->next;
			}
			if (flag == 1)//提示用户是否重新输入
			{
				printf("=======>The number %s is existing,try again?(y/n):", num);
				scanf(" %c", &ch);//前导空格它告诉scanf函数忽略所有空白字符
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					return; //结束添加节点
			}
			else//学号未存在
				break;
		}
		p = (Node*)malloc(sizeof(Node));//申请内存空间
		if (!p)
		{
			printf(" \n allocate memory failure");//如果没申请到，打印提示信息
			return;//返回主界面
		}
		strcpy(p->data.num, num);//将字符串num复制到p->data.num中
		stringinput(p->data.name, 15, "Name:");
		p->data.cgrade = numberinput("C language Score[0-100]:");//输入并检验分数
		p->data.mgrade = numberinput("Math Score[0-100]:");//输入并检验分数
		p->data.egrade = numberinput("English Score[0-100]:");//输入并检验分数
		p->data.total = p->data.cgrade + p->data.mgrade + p->data.egrade;
		p->data.ave = (float)(p->data.total / 3);
		p->data.mingci = 0;
		p->next = NULL;//表明这是链表的尾结点
		r->next = p;//将新建的节点加入链表的尾部中
		r = p;
		saveflag = 1;
	}
}

//8.查询学生记录
void Qur(Link l)
{
	int select;// 1 按学号查 2 按姓名查找
	char searchinput[20];//保存用户输入的查询内容
	Node* p;
	if (! l->next)//若链表为空
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
	if (select == 1)//按学号查找
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
	else if (select == 2)//按姓名查找
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


//9.删除学生记录
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
		return;//返回主页面
	}
	Disp(l);
	printf("\n ========>1 Delete by number =========>2 Delete by name\n");
	printf("please choice[1,2]:");
	scanf("%d", &sel);
	if (sel == 1)//按学号查找
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
			saveflag = 1;//未保存
		}
		else {
			Nofind();
			system("pause");
		}
	}
	else if (sel == 2)//按姓名查找
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
			saveflag = 1;//未保存
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

//10.修改学生记录
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
	stringinput(findmess, 10, "input the existing student number:");//输入并检验该学号
	p = Locate(l, findmess, "num");//查询到该节点
	if (p)//若p！=NULL，表明已经找到该节点
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

//11.插入学生记录
void Insert(Link l)
{
	Link p, v, newinfo;//Link是node类型的指针变量，p用来遍历，v用来遍历，newinfo用来申请新的节点
	char ch, num[10], s[10];//ch保存y/Y，s保存插入点位置之前的学号，num保存输入的新记录的学号
	int flag = 0;//判断学号非否存在
	system("cls");
	Disp(l);
	while (l)
	{
		stringinput(s, 10, "please input insert location after the Number:");
		flag = 0;
		v = l->next;
		while (v)//查询该学号是否存在，flag=1表示该学号存在
		{
			if (strcmp(v->data.num, s) == 0) { flag = 1;break; }
			v = v->next;
		}
		if (flag == 1)
			break;//若学号存在，则进行插入之前的新纪录的输入操作
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

	//以下新记录的输入操作与Add()相同
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
			printf("\n allocate menory failure");//没有申请到空间
			return;//返回主界面
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
		//在main（）有对该全局变量的判断，若为1，则进行存盘操作
		//将指针赋值给p，因为l中的头节点的下一个节点才实际保存着学生的记录
		p = l->next;
		while (l)
		{
			if (strcmp(p->data.num,s)==0)//在链表中插入一个节点
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

//12.统计学生记录
void Tongji(Link l)
{
	Node* pm, * pe, * pc, * pt;//用于指向最高分的节点
	Node* r = l->next;
	int countc = 0, countm = 0, counte = 0;//保存三门成绩中不及格的人数
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

//13.排序学生信息
void Sort(Link l)
{
	Link ll;
	Node* p, * rr, * s;//p遍历l，rr遍历ll，s申请节点
	int i = 0;
	if (l->next == NULL)
	{
		system("cls");
		printf("\n==========>Not student record!\n");
		system("pause");
		return;
	}
	ll = (Node*)malloc(sizeof(Node));
	if (!ll)//用于创建新的节点
	{
		printf("\n allocate memory failure");
		return;//返回主界面
	}
	ll->next = NULL;
	system("cls");
	Disp(l);//显示排序前的所有学生记录
	p = l->next;
	while (p)
	{
		s = (Node*)malloc(sizeof(Node));//新建节点用于保存从原链表中取出的节点信息
		if (!s)
		{
			printf("\n allocate memory failure");//如果没有申请到，打印提示信息
			return;//返回主界面
		}
		s->data = p->data;//填数据域
		s->next = NULL;//指针域为空
		rr = ll;
		//插入排序
		while (rr->next != NULL && rr->next->data.total >= p->data.total)//rr链表于存储插入单个节点后保持排序的链表
			//ll是这个链表的头指针，每次从头开始查找插入位置
		{
			rr = rr->next;//指针移至总分比p所指的节点的总分小的节点位置
		}
		if (rr->next == NULL)//若新链表ll中的所有节点的总分值都比p->data.total大时，就将p所指节点加入链表尾部
			rr->next = s;
		else//否则将该节点插入至第一个总分字段比它小的节点的前面
		{
			s->next = rr->next;
			rr->next = s;
		}
		p = p->next;//原链表中的指针下移一个节点
	}
	l->next = ll->next;//ll中存储的是已排序的链表的头指针
	p = l->next;//已排好序的头指针赋给p，准备填写名次
	while (p!=NULL)
	{
		i++;//节点序号
		p->data.mingci = i;//将名次赋值
		p = p->next;//指针后移
	}
	Disp(l);
	saveflag = 1;
	printf("\n========>sort complete!\n");
}


//14.存储学生记录
void Save(Link l)
{
	FILE* fp;
	Node* p;
	int count = 0;
	fp = fopen("F:\\student", "wb");//以只写方式打开二进制文件
	if (fp == NULL)//打开文件失败
	{
		printf("\n=======>open file error!\n");
		system("pause");
		return;
	}
	p = l->next;
	while (p)
	{
		if (fwrite(p, sizeof(Node), 1, fp) == 1)//每次写一条记录或一个节点信息至文件
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
		fclose(fp);//关闭此文件
	}
}