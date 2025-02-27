#include<stdio.h>
#include<string.h>
#define femalemax 500
#define malemax 500
typedef struct s
{
	char name[10];
	char password[17];
}user;

typedef struct
{
	char name[9];
    char no[12];
    char gender[10];
    char dormnumber[5];
}dorm;

int login()
{
	user users[3];
	FILE *fp;
	fp=fopen("d:\\����ļ�\\C�����ļ�\\�������\\regulatordata.txt","r");
	if(fp==NULL)
	{
		printf("û���ҵ��ļ�");
		return 0;
	}
	int i,count=0;
	char Name[10],Password[17];
	for(i=0;i<3;i++)
	{
		fscanf(fp,"%s",users[i].name);
		fscanf(fp,"%s",users[i].password);
	}
	fclose(fp);
	printf("Login name: ");
	fflush(stdin);
	gets(Name);
	while(count<3)
	{
		printf("Password: ");
		fflush(stdin);
		gets(Password);
		for(i=0;i<3;i++)
		{
		    if(strcmp(users[i].name,Name)==0)
			{
		        break;		
		    } 	
		}	
		if(strcmp(users[i].password,Password)==0)
		{
			break;
		}
		count++;
		printf("Wrong password!\n");
		if(count<3)
		{
			printf("Please input password again:\n");
		}
    }
    if(count==3)
    {
    	printf("Login failed!\n");
    	return 0;
	}
	else
	{
		printf("Login succssful!\n");
		return 1;
	}
}

void load(dorm *dorms,int *count1,int *count2)
{
	int count=0,i=0;
	char sample1[]={"male"};
	char sample2[]={"female"};
	FILE *f;
	f=fopen("d:\\����ļ�\\C�����ļ�\\�������\\dormdata.txt","r");
	if(f==NULL)
	{
		printf("û���ҵ����ļ�\n");
		return ;
	}
	while(fscanf(f,"%s %s %s %s",dorms[i].name,dorms[i].no,dorms[i].gender,dorms[i].dormnumber)!= EOF)
	{
		if(strcmp(dorms[i].gender,sample1)==0)
		{
			(*count1)++;
		}
		else
		    if(strcmp(dorms[i].gender,sample2)==0)
		    {
		    	(*count2)++;
			}
			i++;
	}
	fclose(f);
}

void add(dorm *dorms,dorm *addnumber,int *count1,int *count2,int *count,int *total1)
{
	if((*count1)+(*count2)>=(femalemax+malemax))
	{
		printf("ѧ����������\n");
		return;
	}
	char sample1[]={"male"};
	char sample2[]={"female"};
	printf("��������ӵ�ѧ����Ϣ��\n");
	scanf("%s",dorms[(*count)].name);
	scanf("%s",dorms[(*count)].no);
	scanf("%s",dorms[(*count)].gender);
	scanf("%s",dorms[(*count)].dormnumber);
	addnumber[(*total1)]=dorms[(*count)];
	(*count)++;
	(*total1)++;
	if(strcmp(dorms[(*count)].gender,sample1)==0)
		{
			(*count1)++;
		}
	else
	    if(strcmp(dorms[(*count)].gender,sample2)==0)
	    {
	    	(*count2)++;
		}
	printf("��ӳɹ�!\n");
}

void dele(dorm *dorms,dorm *delenumber,int *count1,int *count2,int *count,int *total2)
{
	char sample1[]={"male"};
	char sample2[]={"female"};
	printf("������ɾ����ѧ��ѧ�ţ�\n");
	char No[12];
	fflush(stdin);
	gets(No);
	int i,j;
	for(i=0;i<(*count);i++)
	{
		if(strcmp(dorms[i].no,No)==0)
		{
			delenumber[(*total2)]=dorms[i];
			(*total2)++;
		    for(j=i;j<(*count)-1;j++)
			{
				dorms[j]=dorms[j+1];
			}	
			(*count)--;
			if (strcmp(dorms[i].gender, sample1) == 0) 
			{
                (*count1)--;
            } else if (strcmp(dorms[i].gender, sample2) == 0) 
			{
                (*count2)--;
            }
            printf("ɾ�����!\n");
            return ;
		}
	}
	printf("δ�ҵ���ѧ��\n");
}

void save(dorm *dorms,int *count)
{
	FILE *fp;
	fp=fopen("d:\\����ļ�\\C�����ļ�\\�������\\dormdata.txt","w");
	if(fp==NULL)
	{
		printf("û���ҵ��ļ�");
		return ;
	}
	int i;
	for(i=0;i<(*count);i++)
	{
		fprintf(fp,"%s %s %s %s\n",dorms[i].name,dorms[i].no,dorms[i].gender,dorms[i].dormnumber);
	}
	fclose(fp);
}

void search(dorm *dorms,dorm *addnumber,dorm *delenumber,int *count1,int *count2,int *count,int *total1,int *total2)
{
	printf("1.���շ��Ų�ѯ��ǰ�մ�λ������λ�����Ϣ\n");
	printf("2.���շ��Ų�ѯ���ѧ����Ϣ\n");
	printf("3.��ѯ��ס���˳���Ϣ\n");
	int choice;
	printf("ָ�"); 
	scanf("%d",&choice);
	int i,j=0;
	if(choice==1)
	{
		printf("������Ҫ��ѯ�ķ���: ");
		char Dormnumber[5];
		fflush(stdin);
		gets(Dormnumber);
		for(i=0;i<(*count);i++)
		{
			if(strcmp(dorms[i].dormnumber,Dormnumber)==0)
			{
				j++;
			}
		}
		if(j==4)
		{
			printf("�޿մ�λ\n");
		}
		else
		    if(j<4)
		    {
		    	printf("��ǰ�մ�λ��Ϊ��%d\n",4-j);
			}
	}
	else
	    if(choice==2)
	    {
	    	printf("�����뷿�ţ�");
	    	char Dormnumber[5];
	    	fflush(stdin);
	    	gets(Dormnumber);
	    	for(i=0;i<(*count);i++)
	    	{
	    		if(strcmp(dorms[i].dormnumber,Dormnumber)==0)
	    		{
	    			printf("%s %s %s\n",dorms[i].name,dorms[i].no,dorms[i].gender);
				}
			}
		}
		else
		    if(choice==3)
		    {
		    	for(i=0;i<(*total1);i++)
		    	{
		    		printf("��סѧ����Ϣ: ");
		    		printf("%s %s %s\n",addnumber[i].name,addnumber[i].no,addnumber[i].gender);
				}
				for(i=0;i<(*total2);i++)
				{
					printf("�˳�ѧ����Ϣ��");
					printf("%s %s %s\n",delenumber[i].name,delenumber[i].no,delenumber[i].gender);
				}
			}
}

void sumerize(int *count1,int *count2)
{
	printf("������ǰռ�ô�λ��Ϊ��%d,�մ�λ��Ϊ��%d\n",(*count1),malemax-(*count1));
	printf("Ů����ǰռ�ô�λ��Ϊ��%d,�մ�λ��Ϊ��%d\n",(*count2),femalemax-(*count2));
}

int main()
{
    if(login()==0)
    {
    	return 0;
	}
	int count,count1=0,count2=0;
	dorm dorms[femalemax+malemax];
    dorm addnumber[femalemax+malemax],delenumber[femalemax+malemax];
    int total1=0,total2=0;
	load(dorms,&count1,&count2);
	count=count1+count2;
	printf("��ѡ���ܣ�\n");
	printf("1. ���ѧ����Ϣ\n");
    printf("2. ɾ��ѧ����Ϣ\n");
    printf("3. ��ѯ��Ϣ\n");
    printf("4. ͳ����Ϣ\n");
    printf("5. ����ѧ����Ϣ���ļ����˳�\n");
    while(1)
    {
    	int c;
    	printf("����ָ�");
    	scanf("%d",&c);
    	switch(c)
    	{
    		case 1:add(dorms,addnumber,&count1,&count2,&count,&total1);break;
    		case 2:dele(dorms,delenumber,&count1,&count2,&count,&total2);break;
    		case 3:search(dorms,addnumber,delenumber,&count1,&count2,&count,&total1,&total2);break;
    		case 4:sumerize(&count1,&count2);break;
    		case 5:save(dorms,&count);return 0;	break;
		}
	}
	return 0;
}



























