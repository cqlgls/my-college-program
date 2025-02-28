#define _CRT_SECURE_NO_WARNINGS  1
#include<stdio.h>
#include<string.h>
#define max 1000
typedef struct s
{
	char  accountnumber[5];
	char password[7];
	char name[50];
	double restnumber;
}user;

int  load(user *users,int total)
{
	FILE *f;
	f = fopen("D:\\college data\\Programing Files\\C files\\vs\\bank management system\\usersdata.txt","r");
	if (f == NULL)
	{
		printf("û���ҵ����ļ�");
		return total;
	}
	int i=0;
	while (fscanf(f, "%s %s %s %lf", users[i].accountnumber, users[i].password, users[i].name, &users[i].restnumber) != EOF)
	{
		total++;
		i++;
	}
	fclose(f);
	return total;
}

int login(user* users,int total,int *site)
{
	char Accountnumber[5];
	char Password[7];
	int count=3,i;
	printf("------------��¼------------");
	printf("\n�������˺�: ");
	scanf("%s", Accountnumber);
	for (i = 0; i < total; i++)
	{
		if (strcmp(users[i].accountnumber, Accountnumber) == 0)
		{
			*site = i;
			while (count > 0)
			{
				printf("����������: ");
				scanf("%s", Password);
				if (strcmp(users[i].password, Password) == 0)
				{
					return 1;
				}
				count--;
				printf("������󣬻�ʣ%d�λ���", count);
			}
			return 0;
		}
	}
	printf("�˺Ų�����!\n");
	return 0;
}

void display()
{
	printf("**********��ӭʹ��ATM**********\n");
	printf("1.���\n");
	printf("2.ȡ��\n");
	printf("3.ת��\n");
	printf("4.��ѯ���\n");
	printf("5.�˳�\n");
	printf("��ѡ�����: ");
}

void deposit(user* users, int site)
{
	printf("���������");
	double money;
	scanf("%lf", &money);
	users[site].restnumber += money;
	printf("���ɹ���\n");
}

void withdrew(user* users, int site)
{
	printf("������ȡ����: ");
	double money;
	scanf("%lf", &money);
	if (money > users[site].restnumber)
	{
		printf("���㣡\n");
		return;
	}
	users[site].restnumber -= money;
}

void transfer(user* users, int site,int total)
{
	char Accountnumber[5];
	int i;
	double money;
	printf("������Ҫת����˺ţ�");
	scanf("%s", Accountnumber);
	printf("������ת��Ľ�");
	scanf("%lf", &money);
	for (i = 0; i < total; i++)
	{
		if (strcmp(users[i].accountnumber, Accountnumber) == 0)
		{
			if (money > users[site].restnumber)
			{
				printf("���㣡\n");
			}
			else
			{
				users[site].restnumber -= money;
				users[i].restnumber += money;
				printf("ת�˳ɹ���\n");
			}
			return;
		}
	}
		printf("δ�ҵ����û���\n");
		return;
}

void check(user* users, int site)
{
	printf("��ǰ���Ϊ��%.2lf\n", users[site].restnumber);
}

void save(user* users,int total)
{
	FILE* f;
	f = fopen("D:\\college data\\Programing Files\\C files\\vs\\bank management system\\usersdata.txt", "w");
	if (f == NULL)
	{
		printf("δ�ҵ����ļ�\n");
		return;
	}
	for (int i = 0; i < total; i++)
	{
		fprintf(f, "%s %s %s %.2lf\n", users[i].accountnumber, users[i].password, users[i].name, users[i].restnumber);
	}
	fclose(f);
}

int main()
{
	user users[max];
	int choice,total,site;
	total=load(users,0);
	if (login(users, total, &site) == 0)
	{
		printf("\n��¼ʧ��!");
		return 0;
	}
	while (1)
	{
		display();
		scanf("%d", &choice);
		switch (choice)
		{
		    case 1:deposit(users, site); break;
			case 2:withdrew(users, site); break;
			case 3:transfer(users, site, total); break;
			case 4:check(users, site); break;
			case 5:save(users,total); return 0;
			default:printf("��Ч������\n");
		}
	}
	return 0;
}