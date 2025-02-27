#include<stdio.h>
#include<stdlib.h>
#define max 10
typedef struct s
{
	int posx,posy;
}direction;

int isexit(int x,int y,int n)
{
	if(x==n-1&&y==n-1)
	{
		return 1;
	}
	return 0;
}

void prnmaze(int maze[max][max],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%2d ",maze[i][j]);
		}
		printf("\n");
	}
}

void MAZE(int maze[max][max],int n,int currentx,int currenty,int step,int path[max*max][2],int *pathcount)
{
	int i,nextx,nexty;
	direction dirc[8]={{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
	path[step][0]=currentx;
	path[step][1]=currenty;
	if(isexit(currentx,currenty,n))
	{
		(*pathcount)++;
		printf("·��%d:\n",*pathcount);
		for(i=1;i<=step;i++)
		{
			printf("(%d,%d)",path[i][0],path[i][1]);
		}
		printf("\n");
		return ;//���ص���һ������ 
	}
	for(i=0;i<8;i++)
	{
		nextx=currentx+dirc[i].posx;
		nexty=currenty+dirc[i].posy;
		if (nextx<0||nextx>=n||nexty<0||nexty>=n) 
		{
            continue;//����ǲ��ǵ��˱߽� 
        }
		if(maze[nextx][nexty]==0)
		{
			maze[nextx][nexty]=step+1;
			MAZE(maze,n,nextx,nexty,step+1,path,pathcount);//�ݹ� 
			maze[nextx][nexty]=0;//���� 
		}
	}
}

int main()
{
	FILE *fp;
	fp=fopen("d:\\����ļ�\\C�����ļ�\\�������\\�Թ�data.txt","r");
	if(fp==NULL)
	{
		printf("δ�ҵ��ļ�");
		return 0;
	}
	int n;
	printf("�������Թ���Сn��");
	scanf("%d",&n);
	int maze[max][max]={0};
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%d",&maze[i][j]);
		}
	}
	fclose(fp);
    
	printf("�Թ�Ϊ��\n");
	prnmaze(maze,n);
	int step;
	int currentx,currenty;
	printf("������������꣺");
	scanf("%d %d",&currentx,&currenty);
	maze[currentx][currenty]=1;
	int path[max*max][2]={0};
	int pathcount=0;
	MAZE(maze,n,currentx,currenty,1,path,&pathcount);
	printf("����%d��·��",pathcount);
	return 0;
}
























