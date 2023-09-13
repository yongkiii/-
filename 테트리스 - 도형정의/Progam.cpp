#include <Windows.h>
#include "Document.h"

#define BOARD_SX 70
#define BOARD_SY 50
#define MY_WIDTH 15
#define MY_HEIGHT 15


#define MY_RX(x) (BOARD_SX+(x)*MY_WIDTH)
#define MY_RY(y) (BOARD_SY+(y)*MY_HEIGHT)
#define NEXT_SX 300
#define MY_NRX(x) (NEXT_SX+(x)*MY_WIDTH)
#define MY_NRY(y) MY_RY(y)

#define DIAGRAM_WIDTH 4
#define DIAGRAM_HEIGHT 4
#define DW DIAGRAM_WIDTH
#define DH DIAGRAM_HEIGHT
#define BOARD_COL 10
#define BOARD_ROW 18
#define TID_DROP 1032

//먼저 싱글톤으로 폼 문서를 가져오는게 중요 없으면 하나의 폼을 생성
void MoveRightProc(HWND hWnd)
{
	Document* doc = Document::GetSingleton();
	doc->MoveRight();
}
void OnTimer(HWND hWnd, DWORD tid)
{
	Document* doc = Document::GetSingleton();
	if (doc->MoveDown() == false)
	{
		doc->MakeDiagram();
	}
	InvalidateRect(hWnd, 0, true);
}
void MoveLeftProc(HWND hWnd)
{
	Document* doc = Document::GetSingleton();
	doc->MoveLeft();
}
void TurnProc(HWND hWnd)
{
	Document* doc = Document::GetSingleton();
	doc->MoveTurn();
}
void OnKeyDown(HWND hWnd, DWORD key, LPARAM lParam)
{
	switch (key)
	{
	case VK_UP: TurnProc(hWnd); break;
	case VK_LEFT: MoveLeftProc(hWnd); break;
	case VK_RIGHT: MoveRightProc(hWnd); break;
	}
}
void OnCreate(HWND hWnd, CREATESTRUCT* pcs)
{
	Document *doc = Document::GetSingleton();
	doc->MakeDiagram(); //start 하여라
	SetTimer(hWnd, TID_DROP, 200, 0);

}
void DrawGameBoard(HWND hWnd, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(40, 40, 40));
	HPEN oPen = (HPEN)SelectObject(hdc, hPen);
	for (int r = 0; r <= BOARD_ROW; r++)
	{
		MoveToEx(hdc, BOARD_SX, MY_RY(r), 0);
		LineTo(hdc, MY_RX(BOARD_COL), MY_RY(r));
	}
	for (int c = 0; c <= BOARD_COL; c++)
	{
		MoveToEx(hdc, MY_RX(c), MY_RY(0), 0);
		LineTo(hdc, MY_RX(c), MY_RY(BOARD_ROW));
	}
	SelectObject(hdc, oPen);
	DeleteObject(hPen);
}
void DrawDiagram(HWND hWnd, HDC hdc)
{
	Document* doc = Document::GetSingleton();
	Diagram* now = doc->GetNow();
	block bl = now->GetBlock();

	int x = now->GetX();
	int y = now->GetY();

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 128, 128));
	HBRUSH oBrush = (HBRUSH)SelectObject(hdc, hBrush);
	for (int cx = 0; cx < DW; cx++)
	{
		for (int cy = 0; cy < DH; cy++)
		{
			if (bl[cy][cx] == 1)
			{
				Ellipse(hdc, MY_RX(x + cx), MY_RY(y + cy), MY_RX(x + cx+1) - 1, MY_RY(y + cy + 1) - 1);
			}
		}
	}

	SelectObject(hdc, oBrush);
	DeleteObject(hBrush);
}
void DrawNextBoard(HWND hWnd, HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(40, 40, 40));
	HPEN oPen = (HPEN)SelectObject(hdc, hPen);
	for (int r = 0; r <= DH; r++)
	{
		MoveToEx(hdc, NEXT_SX, MY_RY(r), 0);
		LineTo(hdc, MY_NRX(DH), MY_NRY(r));
	}
	for (int c = 0; c <= DW; c++)
	{
		MoveToEx(hdc, MY_NRX(c), MY_NRY(0), 0);
	
		LineTo(hdc, MY_NRX(c), MY_NRY(DW));
	}
	SelectObject(hdc, oPen);
	DeleteObject(hPen);

}
void DrawNextDiagram(HWND hWnd, HDC hdc)
{
	Document* doc = Document::GetSingleton();
	Diagram* next = doc->GetNext();
	block bl = next->GetBlock();
	int x = 0;
	int y = 0;

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 128, 128));
	HBRUSH oBrush = (HBRUSH)SelectObject(hdc, hBrush);
	for (int cx = 0; cx < DW; cx++)
	{
		for (int cy = 0; cy < DH; cy++)
		{
			if (bl[cy][cx] == 1)
			{
				Ellipse(hdc, MY_NRX(x+cx), MY_NRY(y+cy), MY_NRX(x +cx+ 1) - 1, MY_NRY(y +cy+1) - 1);
			}
		}
	}
	
	SelectObject(hdc, oBrush);
	DeleteObject(hBrush);
}
void OnDraw(HWND hWnd, HDC hdc)
{
	DrawGameBoard(hWnd, hdc);
	DrawDiagram(hWnd, hdc);
	DrawNextBoard(hWnd, hdc);
	DrawNextDiagram(hWnd, hdc);
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	OnDraw(hWnd, hdc);
}
void OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}

LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	
	case WM_CREATE: OnCreate(hWnd, (CREATESTRUCT*)lParam); return 0;
	case WM_TIMER: OnTimer(hWnd, (DWORD)wParam); return 0;
	case WM_KEYDOWN: OnKeyDown(hWnd, (DWORD)wParam, lParam); return 0;
	case WM_PAINT: OnPaint(hWnd); return 0;
	case WM_DESTROY: OnDestroy(hWnd, wParam, lParam);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
{
	WNDCLASS wndclass = { 0 };
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.style = CS_DBLCLKS;
	wndclass.lpfnWndProc = MainProc;
	wndclass.lpszClassName = TEXT("테트리스");
	wndclass.hCursor = LoadCursor(0, IDC_ARROW);
	wndclass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wndclass.hInstance = hIns;

	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(TEXT("테트리스"), TEXT("테트리스-도형이동"), WS_OVERLAPPEDWINDOW, 100, 100, 410, 400, 0, 0, hIns, 0);
	ShowWindow(hWnd, nShow);

	MSG Message;
	while (GetMessage(&Message, 0, 0,0))
	{
		DispatchMessage(&Message);
	}
	return 0;
}