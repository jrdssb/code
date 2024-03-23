#include <iostream>
#include<iomanip>
#include<time.h>

using namespace std;

int main()
{
    for(int in=200;in<=3200;in*=2)
    {
        clock_t start, finish;  // clock_t为时钟计时单元数
        start = clock();        // clock()返回此时CPU时钟计时单元数
        int n=in;
        for(int epoch=0;epoch<10000;epoch++)
        {
            //matrix initial
            int**matrix=new int*[n];
            for(int r=0;r<n;r++)
            {
                matrix[r]=new int[n];
            }
            for(int r=0;r<n;r++)
            {
                for(int c=0;c<n;c++)
                {
                    matrix[r][c]=r+c+1;
                }
            }

            //tensor and sum initial
            int*tensor=new int[n];
            int*sum=new int[n];
            for(int i=0;i<n;i++)
            {
                tensor[i]=i+1;
                sum[i]=0;
            }

            for(int j = 0; j < n; j++)
            {
                for(int i = 0; i < n; i++)
                {
                    sum[i] += matrix[j][i]*tensor[j];
                }
            }
            //print sum
        }
        finish = clock();
        cout << "在输入规模大小为"<< in << "时，代码花费时间为：" << fixed << setprecision(8)<< double(finish - start) / CLOCKS_PER_SEC << "ms"<< endl;
    }
}
