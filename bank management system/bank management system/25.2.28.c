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
		printf("没有找到该文件");
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
	printf("------------登录------------");
	printf("\n请输入账号: ");
	scanf("%s", Accountnumber);
	for (i = 0; i < total; i++)
	{
		if (strcmp(users[i].accountnumber, Accountnumber) == 0)
		{
			*site = i;
			while (count > 0)
			{
				printf("请输入密码: ");
				scanf("%s", Password);
				if (strcmp(users[i].password, Password) == 0)
				{
					return 1;
				}
				count--;
				printf("密码错误，还剩%d次机会", count);
			}
			return 0;
		}
	}
	printf("账号不存在!\n");
	return 0;
}

void display()
{
	printf("**********欢迎使用ATM**********\n");
	printf("1.存款\n");
	printf("2.取款\n");
	printf("3.转款\n");
	printf("4.查询余额\n");
	printf("5.退出\n");
	printf("请选择操作: ");
}

void deposit(user* users, int site)
{
	printf("请输入存款金额：");
	double money;
	scanf("%lf", &money);
	users[site].restnumber += money;
	printf("存款成功！\n");
}

void withdrew(user* users, int site)
{
	printf("请输入取款金额: ");
	double money;
	scanf("%lf", &money);
	if (money > users[site].restnumber)
	{
		printf("余额不足！\n");
		return;
	}
	users[site].restnumber -= money;
}

void transfer(user* users, int site,int total)
{
	char Accountnumber[5];
	int i;
	double money;
	printf("请输入要转入的账号：");
	scanf("%s", Accountnumber);
	printf("请输入转入的金额：");
	scanf("%lf", &money);
	for (i = 0; i < total; i++)
	{
		if (strcmp(users[i].accountnumber, Accountnumber) == 0)
		{
			if (money > users[site].restnumber)
			{
				printf("余额不足！\n");
			}
			else
			{
				users[site].restnumber -= money;
				users[i].restnumber += money;
				printf("转账成功！\n");
			}
			return;
		}
	}
		printf("未找到该用户！\n");
		return;
}

void check(user* users, int site)
{
	printf("当前余额为：%.2lf\n", users[site].restnumber);
}

void save(user* users,int total)
{
	FILE* f;
	f = fopen("D:\\college data\\Programing Files\\C files\\vs\\bank management system\\usersdata.txt", "w");
	if (f == NULL)
	{
		printf("未找到该文件\n");
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
		printf("\n登录失败!");
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
			default:printf("无效操作！\n");
		}
	}
	return 0;
}