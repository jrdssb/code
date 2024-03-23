#include <iostream>
#include<iomanip>
#include<time.h>

using namespace std;

int main()
{
    for(int i=10000;i<=160000;i*=2)
    {
        long test ;
        clock_t start, finish;  // clock_t为时钟计时单元数
        start = clock();        // clock()返回此时CPU时钟计时单元数
        int n=i;
        int sum=0;
        for(int epoch=0;epoch<10000;epoch++)
        {
            int*vec=new int[n];
            for(int i=0;i<n;i++)
            {
                vec[i]=i+1;
            }
            int sum1=0;int sum2=0;
            for(int i=0;i<n;i+=4)
            {
                sum1+=vec[i]+vec[i+1];
                sum2+=vec[i+2]+vec[i+3];
            }
            sum=sum1+sum2;
        }
        finish = clock();
        cout << "在输入规模大小为"<< n << "时，代码运行时间为：" << fixed << setprecision(8)<< double(finish - start) / CLOCKS_PER_SEC << "ms"<< endl;
    }
}
