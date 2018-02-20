#include "MainWindow.h"
#include <process.h>
#include <crtdbg.h>

MainWindow::MainWindow()
{
	// ウインドウの幅
	m_screen_width = 800;
	m_screen_height = 600;

	m_hwnd = NULL;
	m_hInstance = NULL;

	m_isFullScreenFlag = false;

	strcat_s(m_name,sizeof(m_name),"Win32");
	strcat_s(m_title, sizeof(m_title), "Direct11_基盤");
}

MainWindow::~MainWindow()
{
}

bool MainWindow::InitWindow(HINSTANCE _hInstance, int _winMode) {
	
	m_hInstance			= _hInstance;
	m_isFullScreenFlag  = _winMode;

	// メモリーリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ウインドウクラス情報のセット
	WNDCLASSEX	wcex;

	// ウインドウクラス情報のセット
	wcex.hInstance = _hInstance;			// インスタンス値のセット
	wcex.lpszClassName = m_name;					// クラス名
	wcex.lpfnWndProc = (WNDPROC)WndProc;		// ウインドウメッセージ関数
	wcex.style = 0;					// ウインドウスタイル
	wcex.cbSize = sizeof(WNDCLASSEX);	// 構造体のサイズ
	wcex.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);	// ラージアイコン
	wcex.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);		// スモールアイコン
	wcex.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);		// カーソルスタイル
	wcex.lpszMenuName = 0; 					// メニューなし
	wcex.cbClsExtra = 0;					// エキストラなし
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// 背景色白

	if (!RegisterClassEx(&wcex)) return false;	// ウインドウクラスの登録

	// ウインドウ生成
	if (m_isFullScreenFlag) {
		// フルスクリーンモード
		m_hwnd = CreateWindow(
			m_name,								// ウィンドウクラスの名前
			m_title,							// タイトル
			WS_VISIBLE | WS_POPUP,				// ウィンドウスタイル
			0, 0,								// ウィンドウ位置 縦, 横
			m_screen_width, m_screen_height,	// ウィンドウサイズ
			NULL,								// 親ウィンドウなし
			(HMENU)NULL,						// メニューなし
			_hInstance,							// インスタンスハンドル
			(LPVOID)NULL);						// 追加引数なし
	}
	else {
		// ウインドウモード
		RECT	rWindow, rClient;

		m_hwnd = CreateWindow(
			m_name,								// ウィンドウクラスの名前
			m_title,							// タイトル
			WS_CAPTION | WS_SYSMENU,			// ウィンドウスタイル
			0, 0,								// ウィンドウ位置 縦, 横(あとで中央に移動させます)
			m_screen_width, m_screen_height,	// ウィンドウサイズ
			HWND_DESKTOP,						// 親ウィンドウなし
			(HMENU)NULL,						// メニューなし
			_hInstance,							// インスタンスハンドル
			(LPVOID)NULL);						// 追加引数なし

											// ウインドウサイズを再計算（Metricsだけでは、フレームデザインでクライアント領域サイズが変わってしまうので）
		GetWindowRect(m_hwnd, &rWindow);
		GetClientRect(m_hwnd, &rClient);
		m_screen_width = (rWindow.right - rWindow.left) - (rClient.right - rClient.left) + m_screen_width;
		m_screen_height = (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top) + m_screen_height;
		SetWindowPos(
			m_hwnd,
			NULL,
			GetSystemMetrics(SM_CXSCREEN) / 2 - m_screen_width / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - m_screen_height / 2,
			m_screen_width  - 1,
			m_screen_height - 1,
			SWP_NOZORDER);
	}

	if (!m_hwnd) return false;

	// ウインドウ表示する
	ShowWindow(m_hwnd, _winMode);
	UpdateWindow(m_hwnd);

	// タイマの分解能力を１ｍｓにする
	timeBeginPeriod(1);

	return true;
}

HWND	  MainWindow::GetHwnd() const{
	return m_hwnd;
}

HINSTANCE MainWindow::GetHinstance() const {
	return m_hInstance;
}
int		  MainWindow::GetScreenX() const {
	return m_screen_width;
}
int		  MainWindow::GetScreenY() const {
	return m_screen_height;
}
bool	  MainWindow::GetScreenMode() const {
	return m_isFullScreenFlag;
}

void MainWindow::ExitWindow() {
	// タイマの分解能力もとに戻す
	timeEndPeriod(1);
}