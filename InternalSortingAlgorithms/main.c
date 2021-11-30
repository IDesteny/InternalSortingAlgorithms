#include <windows.h>
#include <tchar.h>
#include "InternalSortingAlgorithms.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define TEXT_OUT(hdc, x, y, msg) \
	TextOut(hdc, x, y, msg, lstrlen(msg))

#define DRAW_LINE(hdc, x1, y1, x2, y2) \
	MoveToEx(hdc, x1, y1, NULL);	\
	LineTo(hdc, x2, y2)

#define BTN_0 1000
#define BTN_1 1001
#define BTN_2 1002
#define BTN_3 1003
#define BTN_4 1004
#define BTN_5 1005

VOID(*Sorts[])(
	PINT,
	INT,
	PINT,
	PINT,
	PULONGLONG,
	OUTPUT_DATA_CALLBACK) = {
		BubbleSort,
		SelectionSort,
		InclusionSort,
		ShellSort,
		LinearSort
};

INT tmpArr[20];
TCHAR buffer[256];
HWND outputEdit;

VOID
Bypass(
	PINT arr,
	INT size)
{
	if (!memcmp(arr, tmpArr, size * sizeof(INT)))
		return;

	for (INT i = 0; i < size; ++i)
	{
		_stprintf_s(buffer + lstrlen(buffer), ARRAYSIZE(buffer) - lstrlen(buffer), _T("%i "), arr[i]);
	}
	_stprintf_s(buffer + lstrlen(buffer), ARRAYSIZE(buffer) - lstrlen(buffer), _T("\r\n"));

	memcpy(tmpArr, arr, size * sizeof(INT));
}

#pragma warning(disable: 6386)

VOID
ShowSort(
	INT index, INT arraySize)
{
	PINT arr = malloc(arraySize * sizeof(INT));
	if (!arr)
		return;

	for (INT i = 0; i < arraySize; ++i)
		arr[i] = rand() % 10;

	ZeroMemory(buffer, sizeof(buffer));
	Sorts[index](arr, arraySize, NULL, NULL, NULL, Bypass);

	SetWindowText(outputEdit, buffer);
	free(arr);
}

LRESULT
WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	static PAINTSTRUCT ps;
	static HDC hdc;
	static HPEN hPen;
	static HWND edits[16];

	switch (message)
	{
		case WM_CREATE:
		{
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
			edits[0] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 82, 32, 102, 27, hWnd, NULL, NULL, NULL);
			edits[1] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 82, 62, 102, 27, hWnd, NULL, NULL, NULL);
			edits[2] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 82, 92, 102, 27, hWnd, NULL, NULL, NULL);
			edits[3] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 82, 122, 102, 27, hWnd, NULL, NULL, NULL);
			edits[4] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 82, 152, 102, 27, hWnd, NULL, NULL, NULL);
			edits[5] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 187, 32, 102, 27, hWnd, NULL, NULL, NULL);
			edits[6] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 187, 62, 102, 27, hWnd, NULL, NULL, NULL);
			edits[7] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 187, 92, 102, 27, hWnd, NULL, NULL, NULL);
			edits[8] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 187, 122, 102, 27, hWnd, NULL, NULL, NULL);
			edits[9] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 187, 152, 102, 27, hWnd, NULL, NULL, NULL);
			edits[10] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 291, 32, 48, 27, hWnd, NULL, NULL, NULL);
			edits[11] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 291, 62, 48, 27, hWnd, NULL, NULL, NULL);
			edits[12] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 291, 92, 48, 27, hWnd, NULL, NULL, NULL);
			edits[13] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 291, 122, 48, 27, hWnd, NULL, NULL, NULL);
			edits[14] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY, 291, 152, 48, 27, hWnd, NULL, NULL, NULL);
			edits[15] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_NUMBER, 0, 187, 80, 30, hWnd, NULL, NULL, NULL);
			outputEdit = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER | ES_READONLY | ES_MULTILINE, 80, 232, 261, 148, hWnd, NULL, NULL, NULL);
			CreateWindow(_T("button"), _T("Run"), WS_CHILD | WS_VISIBLE, 80, 187, 262, 30, hWnd, (HMENU)BTN_0, NULL, NULL);
			CreateWindow(_T("button"), _T("Bubble"), WS_CHILD | WS_VISIBLE, 0, 231, 80, 30, hWnd, (HMENU)BTN_1, NULL, NULL);
			CreateWindow(_T("button"), _T("Selection"), WS_CHILD | WS_VISIBLE, 0, 261, 80, 30, hWnd, (HMENU)BTN_2, NULL, NULL);
			CreateWindow(_T("button"), _T("Inclusion"), WS_CHILD | WS_VISIBLE, 0, 291, 80, 30, hWnd, (HMENU)BTN_3, NULL, NULL);
			CreateWindow(_T("button"), _T("Shell"), WS_CHILD | WS_VISIBLE, 0, 321, 80, 30, hWnd, (HMENU)BTN_4, NULL, NULL);
			CreateWindow(_T("button"), _T("Linear"), WS_CHILD | WS_VISIBLE, 0, 351, 80, 30, hWnd, (HMENU)BTN_5, NULL, NULL);

			break;
		}

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			SelectObject(hdc, hPen);
			TEXT_OUT(hdc, 10, 40, _T("Bubble"));
			TEXT_OUT(hdc, 10, 70, _T("Selection"));
			TEXT_OUT(hdc, 10, 100, _T("Inclusion"));
			TEXT_OUT(hdc, 10, 130, _T("Shell"));
			TEXT_OUT(hdc, 10, 160, _T("Linear"));
			TEXT_OUT(hdc, 90, 10, _T("Comparisons"));
			TEXT_OUT(hdc, 195, 10, _T("Permutations"));
			TEXT_OUT(hdc, 300, 10, _T("Time"));
			DRAW_LINE(hdc, 0, 0, 0, 180);
			DRAW_LINE(hdc, 80, 0, 80, 180);
			DRAW_LINE(hdc, 185, 0, 185, 180);
			DRAW_LINE(hdc, 290, 0, 290, 180);
			DRAW_LINE(hdc, 340, 0, 340, 180);
			DRAW_LINE(hdc, 0, 0, 80, 30);
			DRAW_LINE(hdc, 0, 0, 340, 0);
			DRAW_LINE(hdc, 0, 30, 340, 30);
			DRAW_LINE(hdc, 0, 60, 340, 60);
			DRAW_LINE(hdc, 0, 90, 340, 90);
			DRAW_LINE(hdc, 0, 120, 340, 120);
			DRAW_LINE(hdc, 0, 150, 340, 150);
			DRAW_LINE(hdc, 0, 180, 340, 180);
			DRAW_LINE(hdc, 0, 224, 340, 224);
			EndPaint(hWnd, &ps);
			break;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case BTN_0:
				{
					TCHAR InputBuffer[16];

					if (!GetWindowText(edits[15], InputBuffer, 16))
					{
						MessageBox(NULL, _T("Empty line"), NULL, MB_ICONERROR);
						break;
					}

					INT size = _tstoi(InputBuffer);
					PINT arr = malloc(size * sizeof(INT));
					if (!arr) break;
					TCHAR OutBuffer[16];
					ULONGLONG time[5] = { 0 };
					INT comp[5] = { 0 };
					INT perm[5] = { 0 };

					for (INT i = 0; i < 5; ++i)
					{
						for (INT i = 0; i < size; ++i)
							arr[i] = rand();

						Sorts[i](arr, size, &comp[i], &perm[i], &time[i], NULL);

						_itot_s(comp[i], OutBuffer, 16, 10);
						SetWindowText(edits[i], OutBuffer);

						_itot_s(perm[i], OutBuffer, 16, 10);
						SetWindowText(edits[i + 5], OutBuffer);

						_ui64tot_s(time[i], OutBuffer, 16, 10);
						SetWindowText(edits[i + 10], OutBuffer);
					}

					free(arr);
					break;
				}

				case BTN_1:
				{
					ShowSort(0, 10);
					break;
				}

				case BTN_2:
				{
					ShowSort(1, 10);
					break;
				}

				case BTN_3:
				{
					ShowSort(2, 10);
					break;
				}

				case BTN_4:
				{
					ShowSort(3, 20);
					break;
				}

				case BTN_5:
				{
					ShowSort(4, 10);
					break;
				}
			}

			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
			break;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return EXIT_SUCCESS;
}

#pragma warning(default: 6386)

INT
_tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ INT nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = _T("MainWindow");

	if (!RegisterClass(&wc))
		return EXIT_FAILURE;

	HWND hWnd = CreateWindow(
		wc.lpszClassName,
		NULL, WS_OVERLAPPEDWINDOW,
		700, 300, 357, 420,
		NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return EXIT_FAILURE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (INT)msg.wParam;
}
