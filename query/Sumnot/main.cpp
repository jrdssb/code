#include <iostream>
#include<iomanip>
#include<time.h>

using namespace std;

int main()
{
    for(int i=10000;i<=160000;i*=2)
    {
        long test ;
        clock_t start, finish;  // clock_tΪʱ�Ӽ�ʱ��Ԫ��
        start = clock();        // clock()���ش�ʱCPUʱ�Ӽ�ʱ��Ԫ��
        int n=i;
        int z=0;
        for(int epoch=0;epoch<10000;epoch++)
        {
            int*vec=new int[n];
            for(int i=0;i<n;i++)
            {
                vec[i]=i+1;
            }
            for(int i=0;i<n;i++)
            {
                #pragma unroll 8
                z+=vec[i];
            }
        }
        finish = clock();
        cout << "�������ģn��СΪ"<< n << "ʱ����������ʱ��Ϊ��" << fixed << setprecision(8)<< double(finish - start) / CLOCKS_PER_SEC << "ms"<< endl;
    }
}
