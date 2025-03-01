#include<stdio.h>//ͼ�ο�
#include<easyx.h>
#include<time.h>
#include<math.h>

struct Point
{
	double x, y;
	COLORREF color;
};

COLORREF colors[7] = { RGB(255 ,0 ,0),RGB(255 ,0 ,0),RGB(255 ,0 ,0),RGB(255 ,0 ,0),RGB(255 ,0 ,0),RGB(255 ,0 ,0),RGB(255 ,0 ,0) };

const int xScreen = 1200;
const int yScreen = 800;

const double PI = 3.1415926;
const double e = 2.71828;
const double averag_distance = 0.162;
const int quantity = 506;
const int circles = 210;
const int frames = 20;
Point origin_points[quantity];
Point points[circles * quantity];
IMAGE images[frames];

double screen_x(double x)
{
	x += xScreen / 2;
	return x;
}

double screen_y(double y)
{
	y = -y+yScreen / 2;
	return y;
}

int createRandom(int x1,int  x2)
{
	if (x2 > x1)
	{
		return rand() % (x2 - x1 + 1) + x1;
	}
}

void creat_data()
{
	int index = 0;
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	for (double radin = 0.1; radin <= 2 * PI; radin += 0.005)
	{
		x2 = 16 * pow(sin(radin), 3);
		y2 = 13 * cos(radin) - 5 * cos(2 * radin) - 2 * cos(3 * radin) - cos(4 * radin);
		double distance = sqrt(pow(x2 - x1,2) + pow(y2 - y1, 2));
		if (distance > averag_distance)
		{
			x1 = x2;
			y1 = y2;
			origin_points[index].x = x2;
			origin_points[index++].y = y2;
		}
	}
	index = 0;
	for (double size = 0.1, light = 1.5; size <= 20; size += 0.1)
	{
		double p = 1 / (1 + pow(e, 8 - size / 2));
		for (int i = 0; i < quantity; ++i)
		{
			if (p > createRandom(0, 100) / 100.0)
			{
				points[index].color = colors[createRandom(0, 6)];
				points[index].x = size * origin_points[i].x + createRandom(-4, 4);
				points[index++].y = size * origin_points[i].y + createRandom(-4, 4);
			}
		}
	}

	int points_size = index;
	for (int f = 0; f < frames; ++f)
	{
		images[f] = IMAGE(xScreen, yScreen);
		SetWorkingImage(&images[f]);
		//����
		for (index = 0; index < points_size; ++index)
		{
			double x = points[index].x, y = points[index].y;
			double dis = sqrt(pow(x, 2) + pow(y, 2));
			double dis_in = -0.0009 * dis * dis + 0.35174 * dis + 5;

			double x_dis = dis_in * x / dis / frames;
			double y_dis = dis_in * y / dis / frames;

			points[index].x += x_dis;
			points[index].y += y_dis;

			setfillcolor(points[index].color);
			solidcircle(screen_x(points[index].x), screen_y(points[index].y), 1);

		}
	}
}

int main()
{
	srand(time(NULL));
	//��������
	initgraph(xScreen, yScreen);

	//����˫���壬��ֹ��˸
	BeginBatchDraw();

	//�������Ӵ���
	creat_data();


	SetWorkingImage();

	int f = 0;
	bool extend = true, shrink = false;
	//��ѭ��
	while (1)
	{
		//��Ⱦ��������
		putimage(0, 0, &images[f]);
		//ˢ�´���
		FlushBatchDraw();

		//����
		cleardevice;

		if (extend)
			f == 19 ? (shrink = true, extend = false) : ++f;
		else
			f == 0 ? (shrink = false, extend = true) : --f;
		Sleep(20);
	}
	//�ر�˫�����ͼ
	EndBatchDraw();
	//�رմ���
	closegraph();
	return 0;
}
