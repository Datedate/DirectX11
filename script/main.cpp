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
		MessageBox(NULL, "ERROR!", "MainWindow �������@���s" , 0);
		return -1;
	}

	if (graphicsObj.InitGraphics()) {
		MessageBox(NULL, "ERROR!", "DX11Graphics �������@���s", 0);
		return -1;
	}

	MSG	msg;

	// ���b�Z�[�W����[�v
	while (true) {	

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else {
				TranslateMessage(&msg); 			// �������b�Z�[�W�ւ̃R���o�[�g�j
				DispatchMessage(&msg); 				// ���b�Z�[�W��WndProc�֑���
			}
		}
		else {
			GameMain();
		}
	}

	mainWindow.ExitWindow();

	return 0;
}