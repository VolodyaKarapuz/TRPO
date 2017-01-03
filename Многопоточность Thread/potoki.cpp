#include<stdio.h>
#include<conio.h>
#include<math.h>


#define e 0.01
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>

#include <mutex>
#include <thread>

using namespace std;

void foo (int& num, mutex& mtx, FILE* in, FILE* out)
{

	mtx.lock();
		int q=2,i,j,k,n;
	float a[50][50],x[50];
	float sum,temp,error,big; 
	
	printf("LOADING1... \n");


	{
		while (!feof(in))
		{	
			printf("POTOK 1 \n");
			fscanf(in,"%d",&n) ;
			for(i=1;i<=n;i++)
			{
				for(j=1;j<=n+1;j++)
				{
					fscanf(in,"%f",&a[i][j]);
				}
			}
			for(i=1;i<=n;i++)
			{
				x[i]=0;
			}
			do
			{
				big=0;
				for(i=1;i<=n;i++)
				{
					sum=0;
					for(j=1;j<=n;j++)
					{
						if(j!=i)
						{
							sum=sum+a[i][j]*x[j];
						}
					}
					temp=(a[i][n+1]-sum)/a[i][i];
					error=fabs(x[i]-temp);
					if(error>big)
					{
						big=error;
					}
					x[i]=temp;
				}
			}
			while(big>=e);
			fprintf(out,"%-2s %4s","Solution from FILE: 1","\n\n");
			for(i=1;i<=n;i++)
			{
				fprintf(out,"\nx[%d]=%f",i,x[i]);
			}
			fprintf(out,"\n\n ");	
		}
		q++;	
	
	}
	
	mtx.unlock();
	usleep(50000);
	
		
	
}

void bar (int& num, mutex& mtx, FILE* in2, FILE* out)
{
	mtx.lock();		
		int q=2,i,j,k,n;
	float a[50][50],x[50];
	float sum,temp,error,big; 
	
	printf("LOADING2... \n");

	
	{
		while (!feof(in2))
		{	
			printf("POTOK 2 \n");
			fscanf(in2,"%d",&n) ;
			for(i=1;i<=n;i++)
			{
				for(j=1;j<=n+1;j++)
				{
					fscanf(in2,"%f",&a[i][j]);
				}
			}
			for(i=1;i<=n;i++)
			{
				x[i]=0;
			}
			do
			{
				big=0;
				for(i=1;i<=n;i++)
				{
					sum=0;
					for(j=1;j<=n;j++)
					{
						if(j!=i)
						{
							sum=sum+a[i][j]*x[j];
						}
					}
					temp=(a[i][n+1]-sum)/a[i][i];
					error=fabs(x[i]-temp);
					if(error>big)
					{
						big=error;
					}
					x[i]=temp;
				}
			}
			while(big>=e);
			fprintf(out,"%-2s %4s","Solution from FILE: 2","\n\n");
			for(i=1;i<=n;i++)
			{
				fprintf(out,"\nx[%d]=%f",i,x[i]);
			}
			fprintf(out,"\n\n");	
		}
		q++;	
	}
	mtx.unlock();
	usleep(50000); 
}

int main (int argc, char* argv[])
{
	int num = 10;
	mutex mtx;
	
	FILE* out;
	FILE* in;
	FILE* in2;

	int q=2;
	in = fopen(argv[2], "r");
	in2 = fopen(argv[3], "r");
	out = fopen(argv[1], "w");

	thread t1 (foo, ref(num), ref(mtx), ref(in), ref(out));
	thread t2 (bar, ref(num), ref(mtx), ref(in2), ref(out));

	t1.join();
	t2.join();
}
