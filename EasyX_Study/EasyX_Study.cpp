/*
* 名称: EasyX图形库学习记录
* 
* 开发环境: VS2019
* 
*/

#include <graphics.h>
#include <conio.h>

void test_fun1(void);		//创建窗口
void test_fun2(void);		//基本的几何图形
void test_fun3(void);		//文字
void test_fun4(void);		//缓冲区
void test_fun5(void);		//外部素材
void test_fun6(void);		//获取输入
void test_fun7(void);		//键鼠消息

int main()
{
	
	//	test_fun1();
	//	test_fun2();
	//	test_fun3();
	//	test_fun4();
	//	test_fun5();
	//	test_fun6();
	//	test_fun7();

	return 0;
}

void test_fun1(void)
{
	initgraph(400, 400);		//初始化
	
	_getch();

	closegraph();				//关闭
}

//基本图形的绘制
void test_fun2(void)
{
	initgraph(400, 400);		//初始化

	setbkcolor(BLUE);
//	cleardevice();				//清空来填充背景色

	setlinecolor(RED);			//新的颜色用来绘图
	
	rectangle(50, 100, 200, 200);	//矩形
	arc(50, 50, 100, 100, 5, 0);	//圆弧
	circle(60, 60, 20);

	clearcircle(20, 20, 10);

	POINT pts[] = { {70,70}, {140,140}, {140,70} };
	clearpolygon(pts, 3);


	_getch();

	closegraph();				//关闭
}

//文字的绘制
void test_fun3(void)
{
	initgraph(400, 400);		//初始化

	//获取样式
	COLORREF test_color = gettextcolor();
	LOGFONT text_style;
	gettextstyle(&text_style);

	RECT r = { 100,100, 164,120 };
	drawtext(_T("测试文字"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	int height = textheight(_T("测试文字"));
	int width = textwidth(_T("测试"));
	
	//修改字体
	text_style.lfHeight = 40;
	text_style.lfWidth = 20;
	_tcscpy_s(text_style.lfFaceName, _T("宋体"));
	text_style.lfQuality = ANTIALIASED_QUALITY;		//抗锯齿

	settextstyle(&text_style);

	r = { 200,100, 360,140 };
	drawtext(_T("测试文字"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);




	_getch();

	closegraph();				//关闭
}

//缓冲区
void test_fun4(void)
{
	initgraph(400, 400);		//初始化

	//缓冲区
	DWORD* pMem = GetImageBuffer();

	//手动填充缓冲区
	for (int i = 0; i < 400*400; i++)
	{
		//内存中是以BGR格式存储颜色的!
		pMem[i] = BGR(RGB(0, 0, i * 256 / (400 * 400)));
	}

	//强制刷新缓冲区到屏幕
	FlushBatchDraw();

	_getch();

	closegraph();				//关闭
}

//载入外部素材
void test_fun5(void)
{
	initgraph(1000, 1000);		//初始化

	IMAGE test_image, test_image2;
	loadimage(&test_image, _T("psb.jpg"), 200, 200);
	test_image2 = test_image;
	//显示图像
	putimage(100, 100, &test_image);
	//PI/2 = 90°
	rotateimage(&test_image2, &test_image, 3.1415926 / 2);
	putimage(300, 300, &test_image2);

	saveimage(_T("C:\\Users\\likes\\Desktop\\test.bmp"));

	//设置工作区局限在这个对象上
	SetWorkingImage(&test_image2);
	//恢复默认的工作区
	SetWorkingImage(NULL);


	_getch();

	closegraph();				//关闭
}

//获取输入
void test_fun6(void)
{
	initgraph(400, 400);		//初始化

	wchar_t s[10];

	
	InputBox(s, 10, L"请输入内容");

	//宽字符就不需要_T()了
	RECT r = { 100,100, 164,120 };
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	_getch();

	closegraph();				//关闭
}
 
//键鼠消息
void test_fun7(void)
{
	initgraph(400, 400);		//初始化

	ExMessage msg;
	//清空所有消息
	flushmessage();

//	msg = getmessage(EX_MOUSE | EX_KEY);

	//获取消息,直到有消息
	while (true)
	{
		peekmessage(&msg, EX_MOUSE | EX_KEY);

			switch (msg.message)
			{
			case WM_LBUTTONDOWN:	//鼠标按下了左键
				if (msg.ctrl)		//键盘按下了CTRL
				{

				}
				else
				{
					RECT r = { 100,100, 180,120 };
					drawtext(_T("鼠标已按下"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				break;
			case WM_KEYDOWN:
				if (msg.vkcode == VK_ESCAPE)	//如果按下的是ESC
				{
					RECT r = { 100,100, 164,120 };
					drawtext(_T("ESC!         "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				break;
			}
	}

	_getch();

	closegraph();				//关闭
}