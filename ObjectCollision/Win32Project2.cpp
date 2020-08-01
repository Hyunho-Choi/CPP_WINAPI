// Win32Project2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project2.h"
#include "func.h"
#include "shapeClass.h"



#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(255,255, 255));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(NULL, IDI_QUESTION);
	

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, _T("what"), WS_OVERLAPPEDWINDOW,
      200, 300, 1000, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
	const int size = 20;
	static TCHAR str[size];
	static int count , yPos;
	static SIZE sizec;
	static int arrow = 5;
	static POINT circleCenterPos;
	*/
	static RECT rcSize;
	static int mx, my;
	static std::vector<cShape*> object;
	static int mode = 1;
	static const int minimum = 15;

    switch (message)
    {
	case WM_CREATE: //윈도우 최초 생성시 발생
		{	
			/*
			count = 0;
			yPos = 0;
			circleCenterPos.x = 10;
			circleCenterPos.y = 10;
			CreateCaret(hWnd, NULL, 5, 15);
			ShowCaret(hWnd);
			*/
			SetTimer(hWnd, 1, 10, NULL);
			SetTimer(hWnd, 2, 40, NULL);
			srand((unsigned)time(NULL));
		}
		break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_CHAR :
		{
			/*
			if (wParam == VK_BACK && count > 0) count--;
			else if (wParam == VK_RETURN)
			{
				count = 0;
				yPos += 20;
			}
			else if(count < size-1) str[count++] = wParam;
			
			str[count] = NULL;
			InvalidateRgn(hWnd, NULL, TRUE);
			*/


			// 모드변경 넣기
		if (wParam == '1') mode = 1;
		else if (wParam == '2') mode = 2;
		else if (wParam == '3') mode = 3;

		}
		break;

	case WM_SIZE:
		{
		int breakpoint = 0;
		GetClientRect(hWnd, &rcSize);
		}
		break;

	case WM_TIMER:
		{
			switch (wParam)
			{
			case 1: 
					switch (mode)
					{
					case 1:
						for (int i = 0; i < object.size(); i++)
						{
							if (object[i]->OutOfWindow(rcSize))
							{
								cShape* temp = object[i];
								object.erase(object.begin() + i);
								//std::vector<cShape*>(object).swap(object);
								object.shrink_to_fit();
								delete temp;
								break;
							}
							object[i]->CollisonToWall(rcSize);
							object[i]->CollisonMode1(object);
							object[i]->Update();
						}
						break;
					case 2:
						for (int i = 0; i < object.size(); i++)
						{
							if (object[i]->OutOfWindow(rcSize))
							{
								cShape* temp = object[i];
								object.erase(object.begin() + i);
								//std::vector<cShape*>(object).swap(object);
								object.shrink_to_fit();
								delete temp;
								break;
							}
							if (object[i]->getR() > 200)
							{
								cShape* temp = object[i];
								object.erase(object.begin() + i);
								//std::vector<cShape*>(object).swap(object);
								object.shrink_to_fit();
								delete temp;
								break;
							}


							object[i]->CollisonToWall(rcSize);
							int colIndex = (object[i]->CollisonMode2(object));
							object[i]->Update();

							if (colIndex > -1)
							{
								cShape* temp = object[colIndex];
								object.erase(object.begin() + colIndex);
								//std::vector<cShape*>(object).swap(object);
								object.shrink_to_fit();
								delete temp;
							}
							else if (colIndex == -2)
							{
								cShape* temp = object[i];
								object.erase(object.begin() + i);
								//std::vector<cShape*>(object).swap(object);
								object.shrink_to_fit();
								delete temp;
							}
						}
						break;
					case 3:
						for (int i = 0; i < object.size(); i++)
						{
							if (object[i]->OutOfWindow(rcSize))
							{
								cShape* temp = object[i];
								object.erase(object.begin() + i);
								//std::vector<cShape*>(object).swap(object);
								object.shrink_to_fit();
								delete temp;
								break;
							}
							if (object[i]->getR() < minimum)
							{
								cShape* temp = object[i];
								object.erase(object.begin() + i);
								//std::vector<cShape*>(object).swap(object);
								object.shrink_to_fit();
								delete temp;
								break;
							}
							

							object[i]->CollisonToWall(rcSize);
							int colIndex = (object[i]->CollisonMode3(object));
							object[i]->Update();

							if (colIndex > -1) // 상대 분열
							{
								//object[colIndex]->getR();
								
								if (object[colIndex]->getR() >= minimum)
								{
									cShape* temp;
									switch (object[colIndex]->GetType())
									{
									case 0:
										temp = new cCircle(object[colIndex]->GetCenter(), object[colIndex]->GetAngle(), object[colIndex]->getR());
										break;
									case 1:
										temp = new cSquare(object[colIndex]->GetCenter(), object[colIndex]->GetAngle(), object[colIndex]->getR());
										break;
									case 2:
										temp = new cStar(object[colIndex]->GetCenter(), object[colIndex]->GetAngle(), object[colIndex]->getR());
										break;
									}
									object.push_back(temp);
								}
								
								break;
							}
							else if (colIndex == -2) // 자신 분열
							{
								//object[colIndex]->getR();
								cShape* temp;

								switch (object[i]->GetType())
								{
								case 0:
									temp = new cCircle(object[i]->GetCenter(), object[i]->GetAngle(), object[i]->getR());
									break;
								case 1:
									temp = new cSquare(object[i]->GetCenter(), object[i]->GetAngle(), object[i]->getR());
									break;
								case 2:
									temp = new cStar(object[i]->GetCenter(), object[i]->GetAngle(), object[i]->getR());
									break;
								}

								object.push_back(temp);
								break;
							}
						}
						break;
					}

				break;
			case 2:
				InvalidateRgn(hWnd, NULL, TRUE);
				break;
			}
		}
		break;


	case WM_LBUTTONDOWN :
		{
			
			//중복되면 안생기게
			
			POINT pptt = { LOWORD(lParam), HIWORD(lParam) };
			bool plag = false;
			for (int i = 0; i < object.size(); i++)
			{
				if (object[i]->CollisonToMause(pptt))
				{
					plag = true;
					break;
				}
			}

			if (!plag) 
			{
				cShape* temp;
				switch (rand() % 3)
				{
				case 0:
					temp = new cCircle(lParam);
					break;
				case 1:
					temp = new cSquare(lParam);
					break;
				case 2:
					temp = new cStar(lParam);
					break;
				}

				object.push_back(temp);
				//InvalidateRgn(hWnd, NULL, TRUE);
			}
			
		}
		break;
	case WM_LBUTTONUP:
		{}
		break;
	case WM_RBUTTONDOWN:
		{}
		break;
	case WM_RBUTTONUP:
		{}
		break;
	case WM_MOUSEMOVE:
		{}
		break;




	case WM_KEYDOWN:
		{
			/*
			switch (wParam)
			{
			case VK_LEFT:arrow = 1;
				break;
			case VK_UP:arrow = 2;
				break;
			case VK_RIGHT:arrow = 3;
				break;
			case VK_DOWN:arrow = 4;
				break;
			}
			*/

			/*
		if (circleCenterPos.y > rcSize.bottom || circleCenterPos.y < rcSize.top ||
			circleCenterPos.x < rcSize.left|| circleCenterPos.x > rcSize.right)
			{
				
			}
		else
		{
			MoveObjectByKeyboard(wParam, circleCenterPos, 20);
			InvalidateRgn(hWnd, NULL, TRUE);
		}

			*/




		}
		break;

	case WM_KEYUP:
		{
			/*
			switch (wParam)
			{
			case VK_LEFT:
			case VK_UP:
			case VK_RIGHT:
			case VK_DOWN:
				arrow = 5;
				break;
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			*/
		}
		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			for (int i = 0; i < object.size(); i++)
			{
				object[i]->Draw(hdc);
			}




			/*
			RECT rt = { 100, 100, 500, 500 };
			Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
			DrawText(hdc, str2, _tcslen(str2), &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdc, str2, _tcslen(str2), &rt, DT_SINGLELINE);
			DrawText(hdc, str2, _tcslen(str2), &rt, DT_SINGLELINE | DT_BOTTOM);
			DrawText(hdc, str2, _tcslen(str2), &rt, DT_SINGLELINE | DT_RIGHT);
			DrawText(hdc, str2, _tcslen(str2), &rt, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
			*/

			/*
			HPEN hPen, oldPen;
			hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			*/

			HBRUSH hBrush, oldBrush;
			
			//oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
			//POINT point[10] = { {10,150},{250,30},{500,150},{350,300},{150,300} };
			//DrawStar(hdc, 200, 300, 100);

			/*
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			*/

			/*
			RECT rt = { 200, 200, 300, 300 };
			int len = 100;
			RECT rtSide[5] = { 
				{ rt.left - len, rt.top, rt.right - len, rt.bottom }, 
				{ rt.left, rt.top - len, rt.right, rt.bottom - len },
				{ rt.left + len, rt.top, rt.right + len, rt.bottom },
				{ rt.left, rt.top + len, rt.right, rt.bottom + len },
				{ rt.left, rt.top, rt.right, rt.bottom }
			};
			
			//Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
			Rectangle(hdc, rtSide[0].left, rtSide[0].top, rtSide[0].right, rtSide[0].bottom);
			Rectangle(hdc, rtSide[1].left, rtSide[1].top, rtSide[1].right, rtSide[1].bottom);
			Rectangle(hdc, rtSide[2].left, rtSide[2].top, rtSide[2].right, rtSide[2].bottom);
			Rectangle(hdc, rtSide[3].left, rtSide[3].top, rtSide[3].right, rtSide[3].bottom);
			Rectangle(hdc, rtSide[4].left, rtSide[4].top, rtSide[4].right, rtSide[4].bottom);
			
			DrawText(hdc, _T("왼쪽"), _tcslen(_T("왼쪽")), &rtSide[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdc, _T("위"), _tcslen(_T("위")), &rtSide[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdc, _T("오른쪽"), _tcslen(_T("오른쪽")), &rtSide[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdc, _T("아래"), _tcslen(_T("아래")), &rtSide[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Rectangle(hdc, rtSide[arrow - 1].left, rtSide[arrow - 1].top, rtSide[arrow - 1].right, rtSide[arrow - 1].bottom);

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			*/
			//DrawStar(hdc, 300, 300, 100);

			// 글자 출력 + 캐롯출력	
			/*
			DrawText(hdc, str, _tcslen(str), &rt, DT_SINGLELINE);
			GetTextExtentPoint(hdc, str, _tcslen(str), &sizec);
			SetCaretPos(sizec.cx, yPos);
			*/

			// 글자 출력
			// TextOut(hdc, 100, 100, str2, _tcslen(str2)); 

			// 선 출력
			// MoveToEx(hdc, 100, 100, NULL);
			// LineTo(hdc, 200, 200);

			// 기타 등등 출력
			//Drawline(hdc, 100, 100, 0, 50);
			//DrawGrid(hdc, 100, 100, 500, 500, 50);
			//DrawSnail(hdc, 100, 100, 300, 10);

			//타원 출력
			//Ellipse(hdc, 0, 0, 100, 100);
			//DrawSunflower(hdc, 200, 200, 100, 6);
			//DrawSunflowerFractal(hdc, 200, 200, 100, 12);
			

            // TODO: Add any drawing code that uses hdc here...

			/*
			WCHAR str[15] = L"가나다라abc";
			
			TCHAR cen[15] = _T("cen");
			TCHAR vcen[20] = _T("vcen");
			TCHAR right[20] = _T("right");
			
			TextOut(hdc, 100, 110, str2, _tcslen(str2));
			RECT rc;
			rc.left = 200;
			rc.top = 200;
			rc.right = 300;
			rc.bottom = 300;
			SetTextColor(hdc, RGB(255, 0, 0));
			DrawText(hdc, cen, _tcslen(cen), &rc, DT_SINGLELINE | DT_CENTER);
			DrawText(hdc, vcen, _tcslen(vcen), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdc, right, _tcslen(right), &rc, DT_SINGLELINE | DT_RIGHT);
			*/

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
        PostQuitMessage(0);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
