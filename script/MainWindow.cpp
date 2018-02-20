#include "MainWindow.h"
#include <process.h>
#include <crtdbg.h>

MainWindow::MainWindow()
{
	// �E�C���h�E�̕�
	m_screen_width = 800;
	m_screen_height = 600;

	m_hwnd = NULL;
	m_hInstance = NULL;

	m_isFullScreenFlag = false;

	strcat_s(m_name,sizeof(m_name),"Win32");
	strcat_s(m_title, sizeof(m_title), "Direct11_���");
}

MainWindow::~MainWindow()
{
}

bool MainWindow::InitWindow(HINSTANCE _hInstance, int _winMode) {
	
	m_hInstance			= _hInstance;
	m_isFullScreenFlag  = _winMode;

	// �������[���[�N���m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �E�C���h�E�N���X���̃Z�b�g
	WNDCLASSEX	wcex;

	// �E�C���h�E�N���X���̃Z�b�g
	wcex.hInstance = _hInstance;			// �C���X�^���X�l�̃Z�b�g
	wcex.lpszClassName = m_name;					// �N���X��
	wcex.lpfnWndProc = (WNDPROC)WndProc;		// �E�C���h�E���b�Z�[�W�֐�
	wcex.style = 0;					// �E�C���h�E�X�^�C��
	wcex.cbSize = sizeof(WNDCLASSEX);	// �\���̂̃T�C�Y
	wcex.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);	// ���[�W�A�C�R��
	wcex.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);		// �X���[���A�C�R��
	wcex.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);		// �J�[�\���X�^�C��
	wcex.lpszMenuName = 0; 					// ���j���[�Ȃ�
	wcex.cbClsExtra = 0;					// �G�L�X�g���Ȃ�
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// �w�i�F��

	if (!RegisterClassEx(&wcex)) return false;	// �E�C���h�E�N���X�̓o�^

	// �E�C���h�E����
	if (m_isFullScreenFlag) {
		// �t���X�N���[�����[�h
		m_hwnd = CreateWindow(
			m_name,								// �E�B���h�E�N���X�̖��O
			m_title,							// �^�C�g��
			WS_VISIBLE | WS_POPUP,				// �E�B���h�E�X�^�C��
			0, 0,								// �E�B���h�E�ʒu �c, ��
			m_screen_width, m_screen_height,	// �E�B���h�E�T�C�Y
			NULL,								// �e�E�B���h�E�Ȃ�
			(HMENU)NULL,						// ���j���[�Ȃ�
			_hInstance,							// �C���X�^���X�n���h��
			(LPVOID)NULL);						// �ǉ������Ȃ�
	}
	else {
		// �E�C���h�E���[�h
		RECT	rWindow, rClient;

		m_hwnd = CreateWindow(
			m_name,								// �E�B���h�E�N���X�̖��O
			m_title,							// �^�C�g��
			WS_CAPTION | WS_SYSMENU,			// �E�B���h�E�X�^�C��
			0, 0,								// �E�B���h�E�ʒu �c, ��(���ƂŒ����Ɉړ������܂�)
			m_screen_width, m_screen_height,	// �E�B���h�E�T�C�Y
			HWND_DESKTOP,						// �e�E�B���h�E�Ȃ�
			(HMENU)NULL,						// ���j���[�Ȃ�
			_hInstance,							// �C���X�^���X�n���h��
			(LPVOID)NULL);						// �ǉ������Ȃ�

											// �E�C���h�E�T�C�Y���Čv�Z�iMetrics�����ł́A�t���[���f�U�C���ŃN���C�A���g�̈�T�C�Y���ς���Ă��܂��̂Łj
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

	// �E�C���h�E�\������
	ShowWindow(m_hwnd, _winMode);
	UpdateWindow(m_hwnd);

	// �^�C�}�̕���\�͂��P�����ɂ���
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
	// �^�C�}�̕���\�͂��Ƃɖ߂�
	timeEndPeriod(1);
}