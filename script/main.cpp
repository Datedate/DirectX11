#include "MainWindow.h"
#include "DX11Graphics.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CLOSE:
		PostMessage(hWnd, WM_DESTROY, 0, 0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	MainWindow	 mainWindow;
	DX11Graphics graphicsObj;

	if (mainWindow.InitWindow(hInstance, nCmdShow)) {
		MessageBox(NULL, "ERROR!", "MainWindow 初期化　失敗" , 0);
		return -1;
	}

	if (graphicsObj.InitGraphics()) {
		MessageBox(NULL, "ERROR!", "DX11Graphics 初期化　失敗", 0);
		return -1;
	}

	MSG	msg;

	// メッセージ･ループ
	while (true) {	

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else {
				TranslateMessage(&msg); 			// 文字メッセージへのコンバート）
				DispatchMessage(&msg); 				// メッセージをWndProcへ送る
			}
		}
		else {
			GameMain();
		}
	}

	mainWindow.ExitWindow();

	return 0;
}