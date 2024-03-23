#include <iostream>
#include<iomanip>
#include<time.h>

using namespace std;

void recrusion(int n,int*arr)
{
    if(n==1)
    {
        return ;
    }
    else
    {
        for(int i=0;i<n/2;i++)
        {
            arr[i]+=arr[n-i-1];
        }
        n=n/2;
        recrusion(n,arr);
    }
}

int main()
{
    for(int i=10000;i<=160000;i*=2)
    {
        long test ;
        clock_t start, finish;
        start = clock();
        int n=i;
        int sum=0;
        for(int epoch=0;epoch<10000;epoch++)
        {
            int*vec=new int[n];
            for(int i=0;i<n;i++)
            {
                vec[i]=i+1;
            }
            recrusion(n,vec);
        }
        finish = clock();
        cout << "在输入规模大小为"<< n << "时，代码运行时间为：" << fixed << setprecision(3)<< double(finish - start) / CLOCKS_PER_SEC << "s"<< endl;
    }
}
