#include<windows.h>	// 底层实现窗口 的头文件


/* 回调函数声明[第6步骤] */
LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

/* 程序入口函数 */
// #define WINAPI	__stdcall  [代表参数传递顺序]从右向左
int WINAPI WinMain(
	HINSTANCE hInstance,	// 应用程序实例句柄
	HINSTANCE hPrevInstance,	// 上一个应用程序句柄，[Win32下]NULL
	LPSTR lpcmdLine,	// char* argv[]
	int nCmdShow	// [显示命令]最大/小化 正常
){
#pragma region 设计窗口类
	WNDCLASS wc;
	wc.cbClsExtra = 0;	// 类附加内存
	wc.cbWndExtra = 0;	// 窗口附加内存
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 指定窗口类的背景画刷句柄
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// 指定光标句柄	NULL:调用系统提供的
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 指定图标句柄
	wc.hInstance = hInstance;	// 应用程序实例句柄
	wc.lpfnWndProc = WinProc;	// 回调函数
	wc.lpszClassName = TEXT("Win");	// 指定窗口类的名称
	wc.lpszMenuName = NULL;	// 菜单名称
	wc.style = 0;	// 显示风格 0：默认
#pragma endregion
#pragma region 注册窗口类
	RegisterClass(&wc);
#pragma endregion
#pragma region 创建窗口
	HWND hwnd = CreateWindow(wc.lpszClassName,	// 类名
		TEXT("Windows"),			// 标题名
		WS_OVERLAPPEDWINDOW,        // 风格
		CW_USEDEFAULT,              // 显示坐标 x		CW_USEDEFAULT：默认值
		CW_USEDEFAULT,              // y
		CW_USEDEFAULT,              // 宽
		CW_USEDEFAULT,              // 高
		NULL,                       // 父窗口 NULL
		NULL,                       // 实例句柄
		hInstance,                  // 附加值 NULL
		NULL
	);
#pragma endregion
#pragma region 显示和更新
	ShowWindow(hwnd, SW_SHOWNORMAL);	// 窗口显示状态
	UpdateWindow(hwnd);
#pragma endregion
#pragma region 通过循环取消息
	/*typedef struct tagMSG {
		HWND	hwnd;		主窗口句柄
		UINT	message;	具体消息名称
		WPARAM	wParam;		附加消息 键盘消息
		LPARAM	lParam;		附加消息 鼠标消息
		DWORD	time;		消息产生时间
		POINT	pt;			附加消息 鼠标消息 x y
	} MSG*/
	MSG msg;	// 消息结构体
	/*GetMessageA(
			_Out_ LPMSG	lpMsg,			消息
			_In_opt_	HWND hWnd,		指定捕获哪一个窗口的消息 NULL：捕获所有窗口
			_In_ UINT	wMsgFilterMin,	指定要获取的消息最小值，通常设为0
			_In_ UINT	wMsgFilterMax				  最大值
		);*/
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	// 翻译消息
		DispatchMessage(&msg);	// 分发消息
	}
#pragma endregion

	return 0;
}
#pragma region 消息处理（窗口过程）
// #define WINAPI	__stdcall  [代表参数传递顺序]从右向左
LRESULT CALLBACK WinProc(
	HWND hwnd,		// 消息所属窗口句柄
	UINT uMsg,		// 消息具体名称	WM_XXX 窗口消息消息名
	WPARAM wParam,	// 键盘 附加消息
	LPARAM lParam	// 鼠标 附加消息
) {
	switch (uMsg)
	{
	case WM_CLOSE:
		/* 一个机制
			所有xxxxWindows的方法，都不回进入到消息队列，而是直接执行
		*/
		DestroyWindow(hwnd);	// DestroyWindow 发送另一个消息 WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:	// 鼠标左键按下
	{
		int xpos = LOWORD(lParam);
		int ypos = HIWORD(lParam);

		char buf[64];
		wsprintf(buf, TEXT("x = %d, y = %d"), xpos, ypos);
		// 输出打印【弹出窗口】
		MessageBox(hwnd, buf, TEXT("鼠标左键按下的坐标是："), MB_OK);
		break;
	}
	case WM_KEYDOWN:	// 键盘
		MessageBox(hwnd, TEXT("键盘按下了！！！"), TEXT("键盘按下："), MB_OK);
		break;
	case WM_PAINT:	// 绘画
	{
		PAINTSTRUCT ps;	// 绘画结构体
		HDC hdc = BeginPaint(hwnd, &ps);

		TextOut(hdc, 100, 200, TEXT("i love you"), strlen("i love you"));

		EndPaint(hwnd, &ps);
		break;
	}
	}
	// 返回值 用默认处理方式
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
#pragma endregion