#include<iostream>
using namespace std;
# define pi 3.1415926
float Pw[8000];
int main()
{
	float miu = 1.7; //�߶Ȳ���
	float sigma = 0.9; //��״����
	int num = 8000; //�����������ݵ���
	int	fr = 1000;
	int i;
	float f[8000];
	int Num[8000];
	for (i = 0; i < num; ++i)
		Num[i] = i;
	int fs = 1000; //����Ƶ��
	int sigmaf = 50; //������ƵƵ�׹��ʣ�����
	float amp = 1 / (sqrt(2 * pi)*sigmaf);
	for (i = -num / 2; i < num / 2; ++i)
	{
		 f[i+num/2] = fs / num * i; //�ԳƵĹ�����
	}
	for(i=0;i<num;++i)
		Pw[i] = amp*exp(f[i]*f[i] / (2 * sigmaf ^ 2)); //��˹������
}