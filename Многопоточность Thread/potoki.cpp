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

void foo(FILE* in, FILE* out)
{ 
	for (int i = 0; i < 5; i++)
	{
		
	}
}

void bar(FILE* in2, FILE* out)
{
	int q=2,i,j,k,n;
	float a[50][50],x[50];
	float sum,temp,error,big; 
	
	printf("LOADING... \n");

	
	{
		while (!feof(in2))
		{
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
			fprintf(out,"%-2s %4s","Solution from FILE: ","\n\n");
			for(i=1;i<=n;i++)
			{
				fprintf(out,"\nx[%d]=%f",i,x[i]);
			}
			fprintf(out,"\n\n");	
		}
		q++;
	}
	fclose(out);
}


int main ()
{
	FILE* out;
	FILE* in;
	FILE* in2;

	int q=2;
	in = fopen("G:\in.txt", "r");
	in2 = fopen("G:\in2.txt", "r");
	out = fopen("G:\out.txt", "w");
	

	//Establishment of an independent thread
	thread t1 (foo, in, out);
	thread t2 (bar, in2, out);
	t1.join();
	t2.join();

	//The main thread will not wait for the completion of this flow. It allows him to work independently


	system("pause");
};
