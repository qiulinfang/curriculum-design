#include<iostream>
#include<cmath>
#include<time.h>
#include <fstream>
using namespace std;

void Restore(int R[], int f, int e) //�ؽ�����ΪRf�Ķ�������ʹ֮����ѵ����ԣ�������֮��Ų�����e
{
	int m;//j��¼�ϴ��ӽ��ı��
	int j = f;//jָ������
	while (j <= floor(e/2))//ȷ���ж���
	{
		if (2*j<e && R[2*j]<R[2*j+1])//�Ҿ��нϴ�ؼ��ʵ��ӽ��
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
			j = m;//�����ؽ���
		}
		else
		{
			j = e;//��ֹѭ��
		}
	}
}

void HeapSort(int R[], const int n)//�������㷨
{
	int i;
	for (i = floor(n / 2);i >= 1;i--)//������,ע�� i �ı仯��i�Ǹ��ڵ㣬��˵���˶������Ǵӵ͵������е�
		Restore(R, i, n);
	for (int i = n;i > 1;i--)//����
	{
		R[0] = R[i];
		R[i] = R[1];
		R[1] = R[0];
		Restore(R, 1, i - 1);//�ؽ���
	}
}

int main()
{
	ofstream examplefile("example.txt");
	if (examplefile.is_open())
	{
		cout << "�ļ��򿪳ɹ�" << endl;
	}
	int R[100];
	srand((unsigned)time(NULL));//srand()��������һ���Ե�ǰʱ�俪ʼ��������� 
	for (int i = 1;i <= 10;i++)
	{
		R[i] = rand() % 100;//MAXΪ���ֵ���������Ϊ0~MAX-1
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