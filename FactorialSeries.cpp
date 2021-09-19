#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMORDER1 15
#define NUMORDER2 400000
#define NUMORDER3 10
int count=0;
int count2=0;
int ***g_a;
int stac=1;
int stac2=1;
int g_n=0;
void seed(int x)
{
	int i,j;
	for(i=0;i<(x+g_n)*stac;i++)
	{
		for(j=0;j<x+1;j++)
		{
			if(j==0)
			{
				g_a[x-1+g_n][i][0]=0;
			}
			else
			{
				g_a[x-1+g_n][i][j]=g_a[x-2+g_n][i][j-1]+1;
				
			}
		}
	}
	stac*=x;
}
void blender(int x)
{

	int i,j,k,l,m,n;
	
	count2=0;
	n=0;
	for(i=0;i<x*stac2;i++)
	{
		count=0;
		for(k=0,m=k;k<x+1;k++,m=k)
		{
			count2++;
			
			for(j=0,l=j;j<x+1;j++,l++)
			{
				if(l+m>x)
				{
					m=0;
					l=0;
				}
				g_a[x+g_n][n][count]=g_a[x-1+g_n][i][m+l];
				printf("%d",g_a[x+g_n][n][count]);
				count++;
				if(count>x)
				{
					count=0;
					n++;
				}
			}
			printf(" ");
		}
	}
	stac2*=x;
}
void main()
{
	int i,j,k,l;
	g_a=(int***)calloc(NUMORDER1,sizeof(int**));
	if(!g_a)
	{
		printf("g_aのメモリが取れませんでした\n");
		return ;
	}
	for(i=0;i<NUMORDER1;i++)
	{
		g_a[i]=(int**)calloc(NUMORDER2,sizeof(int*));
		if(!g_a[i])
		{
			printf("g_a[%d]のメモリが取れませんでした\n",i);
			for(j=0;j<i;j++)
			{
				free(g_a[j]);
			}
			free(g_a);
			return ;
		}
		for(j=0;j<NUMORDER2;j++)
		{
			g_a[i][j]=(int *)calloc(NUMORDER3,sizeof(int));
			if(!g_a[i][j])
			{
				printf("g_a[%d][%d]のメモリが取れませんでした\n",i,j);
				for(k=0;k<i;k++)
				{
					for(l=0;l<j;l++)
					{
						free(g_a[k][l]);
					}
					free(g_a[k]);
				}
				free(g_a);
				return ;
			}
		}
	}
	g_a[0][0][0]=0;
	g_a[0][0][1]=1;
	g_a[0][1][0]=1;
	g_a[0][1][1]=0;
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%d",g_a[0][i][j]);
		}
		printf(" ");
	}
	printf(" 2!\n");
	for(i=2;i<6;i++)
	{
		seed(i);
		blender(i);
		g_n++;
		printf("  %d!\n",count2);
	}
	for(i=0;i<NUMORDER1;i++)
	{
		for(j=0;j<NUMORDER2;j++)
		{
			free(g_a[i][j]);
		}
		free(g_a[i]);
	}
	free(g_a);
}
