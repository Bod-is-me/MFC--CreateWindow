#include<windows.h>	// �ײ�ʵ�ִ��� ��ͷ�ļ�


/* �ص���������[��6����] */
LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

/* ������ں��� */
// #define WINAPI	__stdcall  [�����������˳��]��������
int WINAPI WinMain(
	HINSTANCE hInstance,	// Ӧ�ó���ʵ�����
	HINSTANCE hPrevInstance,	// ��һ��Ӧ�ó�������[Win32��]NULL
	LPSTR lpcmdLine,	// char* argv[]
	int nCmdShow	// [��ʾ����]���/С�� ����
){
#pragma region ��ƴ�����
	WNDCLASS wc;
	wc.cbClsExtra = 0;	// �฽���ڴ�
	wc.cbWndExtra = 0;	// ���ڸ����ڴ�
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ָ��������ı�����ˢ���
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// ָ�������	NULL:����ϵͳ�ṩ��
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// ָ��ͼ����
	wc.hInstance = hInstance;	// Ӧ�ó���ʵ�����
	wc.lpfnWndProc = WinProc;	// �ص�����
	wc.lpszClassName = TEXT("Win");	// ָ�������������
	wc.lpszMenuName = NULL;	// �˵�����
	wc.style = 0;	// ��ʾ��� 0��Ĭ��
#pragma endregion
#pragma region ע�ᴰ����
	RegisterClass(&wc);
#pragma endregion
#pragma region ��������
	HWND hwnd = CreateWindow(wc.lpszClassName,	// ����
		TEXT("Windows"),			// ������
		WS_OVERLAPPEDWINDOW,        // ���
		CW_USEDEFAULT,              // ��ʾ���� x		CW_USEDEFAULT��Ĭ��ֵ
		CW_USEDEFAULT,              // y
		CW_USEDEFAULT,              // ��
		CW_USEDEFAULT,              // ��
		NULL,                       // ������ NULL
		NULL,                       // ʵ�����
		hInstance,                  // ����ֵ NULL
		NULL
	);
#pragma endregion
#pragma region ��ʾ�͸���
	ShowWindow(hwnd, SW_SHOWNORMAL);	// ������ʾ״̬
	UpdateWindow(hwnd);
#pragma endregion
#pragma region ͨ��ѭ��ȡ��Ϣ
	/*typedef struct tagMSG {
		HWND	hwnd;		�����ھ��
		UINT	message;	������Ϣ����
		WPARAM	wParam;		������Ϣ ������Ϣ
		LPARAM	lParam;		������Ϣ �����Ϣ
		DWORD	time;		��Ϣ����ʱ��
		POINT	pt;			������Ϣ �����Ϣ x y
	} MSG*/
	MSG msg;	// ��Ϣ�ṹ��
	/*GetMessageA(
			_Out_ LPMSG	lpMsg,			��Ϣ
			_In_opt_	HWND hWnd,		ָ��������һ�����ڵ���Ϣ NULL���������д���
			_In_ UINT	wMsgFilterMin,	ָ��Ҫ��ȡ����Ϣ��Сֵ��ͨ����Ϊ0
			_In_ UINT	wMsgFilterMax				  ���ֵ
		);*/
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	// ������Ϣ
		DispatchMessage(&msg);	// �ַ���Ϣ
	}
#pragma endregion

	return 0;
}
#pragma region ��Ϣ�������ڹ��̣�
// #define WINAPI	__stdcall  [�����������˳��]��������
LRESULT CALLBACK WinProc(
	HWND hwnd,		// ��Ϣ�������ھ��
	UINT uMsg,		// ��Ϣ��������	WM_XXX ������Ϣ��Ϣ��
	WPARAM wParam,	// ���� ������Ϣ
	LPARAM lParam	// ��� ������Ϣ
) {
	switch (uMsg)
	{
	case WM_CLOSE:
		/* һ������
			����xxxxWindows�ķ����������ؽ��뵽��Ϣ���У�����ֱ��ִ��
		*/
		DestroyWindow(hwnd);	// DestroyWindow ������һ����Ϣ WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:	// ����������
	{
		int xpos = LOWORD(lParam);
		int ypos = HIWORD(lParam);

		char buf[64];
		wsprintf(buf, TEXT("x = %d, y = %d"), xpos, ypos);
		// �����ӡ���������ڡ�
		MessageBox(hwnd, buf, TEXT("���������µ������ǣ�"), MB_OK);
		break;
	}
	case WM_KEYDOWN:	// ����
		MessageBox(hwnd, TEXT("���̰����ˣ�����"), TEXT("���̰��£�"), MB_OK);
		break;
	case WM_PAINT:	// �滭
	{
		PAINTSTRUCT ps;	// �滭�ṹ��
		HDC hdc = BeginPaint(hwnd, &ps);

		TextOut(hdc, 100, 200, TEXT("i love you"), strlen("i love you"));

		EndPaint(hwnd, &ps);
		break;
	}
	}
	// ����ֵ ��Ĭ�ϴ���ʽ
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
#pragma endregion