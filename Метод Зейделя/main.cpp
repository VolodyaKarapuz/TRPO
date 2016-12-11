#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<iostream>
#include<fstream>
#include<iostream>
#define e 0.01

using namespace std;

int  main(int argc, char* argv[])
{
	FILE* out;
	FILE* in;
	
	if(!(in = fopen(argv[2], "r"))) { printf("Open file failed.\n"); return 0; }
	if(!(out = fopen(argv[1], "w"))) { printf("Open file failed.\n"); return 0; }

	int q=2,i,j,k,n;
	float a[50][50],x[50];
	float sum,temp,error,big; 
	
	printf("LOADING... \n");

	while (argv[q] != NULL)
	{
		fclose(in);
		in = fopen(argv[q], "r");
		printf("%8s %8s %6s \n", argv[q],"............", "DONE");
		while (!feof(in))
		{
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
			fprintf(out,"%-2s %4s","Solution from FILE: ",argv[q],"\n\n");
			for(i=1;i<=n;i++)
			{
				fprintf(out,"\nx[%d]=%f",i,x[i]);
			}
			fprintf(out,"\n\n");	
		}
		q++;
	}
	printf("%8s %8s","Output FILE is: ",argv[1]);
	fclose(out);
}

