#include<iostream>
#include<cmath>
#include<time.h>
#include <fstream>
using namespace std;

void Restore(int R[], int f, int e) //重建树根为Rf的二叉树，使之满足堆的特性，任意结点之编号不大于e
{
	int m;//j记录较大子结点的编号
	int j = f;//j指向树根
	while (j <= floor(e/2))//确保有儿子
	{
		if (2*j<e && R[2*j]<R[2*j+1])//找具有较大关键词的子结点
		{
			 m = 2 * j + 1;
		}
		else
		{
			 m = 2 * j;
		}
		if (R[m]>R[j])
		{
			R[0] = R[m];
			R[m] = R[j];
			R[j] = R[0];
			j = m;//继续重建堆
		}
		else
		{
			j = e;//终止循环
		}
	}
}

void HeapSort(int R[], const int n)//堆排序算法
{
	int i;
	for (i = floor(n / 2);i >= 1;i--)//建立堆,注意 i 的变化，i是根节点，这说明了堆排序是从低到顶进行的
		Restore(R, i, n);
	for (int i = n;i > 1;i--)//排序
	{
		R[0] = R[i];
		R[i] = R[1];
		R[1] = R[0];
		Restore(R, 1, i - 1);//重建堆
	}
}

int main()
{
	ofstream examplefile("example.txt");
	if (examplefile.is_open())
	{
		cout << "文件打开成功" << endl;
	}
	int R[100];
	srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子 
	for (int i = 1;i <= 10;i++)
	{
		R[i] = rand() % 100;//MAX为最大值，其随机域为0~MAX-1
		cout << R[i]<<" ";
		examplefile << R[i] << " ";
	}
	cout << endl;
	examplefile << "\n";
	HeapSort(R, 10);
	for (int i = 1;i <= 10;i++)
	{
		cout << R[i] << " ";
		examplefile << R[i] << " ";
	}
	examplefile.close();
}