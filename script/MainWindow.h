#pragma once

#include <Windows.h>

class MainWindow
{
public:
	MainWindow();
	~MainWindow();
	bool InitWindow(HINSTANCE _hInstance,int _winMode);
	void ExitWindow();

	HWND		GetHwnd() const;
	HINSTANCE	GetHinstance() const;
	int			GetScreenX() const;
	int			GetScreenY() const;
	bool		GetScreenMode() const;
private:
	HWND		m_hwnd;
	HINSTANCE	m_hInstance;
	int			m_screen_width;
	int			m_screen_height;
	char		m_name[64];
	char		m_title[128];
	bool		m_isFullScreenFlag;
};

