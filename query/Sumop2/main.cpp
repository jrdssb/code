#include <iostream>
#include<iomanip>
#include<time.h>

using namespace std;

int main()
{
    for(int i=100000;i<=200000;i+=10000)
    {
        long test ;
        clock_t start, finish;  // clock_tΪʱ�Ӽ�ʱ��Ԫ��
        start = clock();        // clock()���ش�ʱCPUʱ�Ӽ�ʱ��Ԫ��
        int n=i;
        int sum=0;
        for(int epoch=0;epoch<100;epoch++)
        {
            int*vec=new int[n];
            for(int i=0;i<n;i++)
            {
                vec[i]=i+1;
            }
            int sum1=0;int sum2=0;
            for(int m=n;m>1;m/=2)
            {
                for(int i=0;i<m/2;i++)
                {
                    vec[i]=vec[i*2]+vec[i*2+1];
                }
            }
            sum=sum1+sum2;
        }
        finish = clock();
        cout << "�������ģ��СΪ"<< n << "ʱ����������ʱ��Ϊ��" << fixed << setprecision(8)<< double(finish - start) / CLOCKS_PER_SEC << "ms"<< endl;
    }
}
