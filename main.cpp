#include <windows.h>
#include<string>
#include <stdlib.h>

#define ID_TEXTBOX 2
#define ID_BUTTON 1

char Url[] = "start https://www.youtube.com/";
char Url_2[100];
HWND hwndTextBox;
char texto[100];

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
            {
                // Obtener el contexto de dispositivo de la ventana
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                // Definir el texto a mostrar
                LPCSTR szTexto = "¡Buscar Youtuber!";

                // Definir el rectángulo donde se mostrará el texto
                RECT rect;
                rect.left = 30;
                rect.top = 10;
                rect.right = 200;
                rect.bottom = 50;

                // Definir las opciones de formato del texto
                UINT uFormat = DT_SINGLELINE | DT_CENTER | DT_VCENTER;

                // Dibujar el texto en la ventana
                DrawText(hdc, szTexto, -1, &rect, uFormat);
                // Liberar el contexto de dispositivo
                EndPaint(hwnd, &ps);
            }
            break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_CREATE:
		    hwndTextBox = CreateWindow(TEXT("edit"),NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,50, 50, 200, 25, hwnd, (HMENU)ID_TEXTBOX, NULL, NULL);
			break;
		case WM_COMMAND:
        	if (LOWORD(wParam) == ID_BUTTON){
        		GetWindowText(hwndTextBox, texto,100);
        		strcpy(Url_2,Url);
        		strcat(Url_2,texto);
        		system(Url_2);
            }
            break;
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg; 
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; 
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Buscador de Youtuber",WS_VISIBLE|WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT, 400, 170,NULL,NULL,hInstance,NULL);
	HWND hButton = CreateWindowEx(0,"BUTTON","Buscar",WS_VISIBLE | WS_CHILD,255,47,100,30,hwnd,(HMENU)ID_BUTTON,hInstance,NULL);                      

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
