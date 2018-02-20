#pragma once

#include <d3d11.h>

class DX11Graphics
{
public:
	DX11Graphics();
	~DX11Graphics();
	bool InitGraphics(HWND _hwnd,int _screenX,int _screenY,bool _winMode);
	void Exit();
private:
	ID3D11Device*				m_lpDevice;				// DIRECT3DDEVICE11デバイス
	ID3D11DeviceContext*		m_lpImmediateContext;	// DIRECT3DDEVICE11デバイスコンテキスト
	IDXGISwapChain*				m_lpSwapChain;			// スワップチェイン
};

