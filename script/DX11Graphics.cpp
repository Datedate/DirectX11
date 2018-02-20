#include "DX11Graphics.h"

#define SAFE_RELEASE(x) if(x != nullptr){ x->Release(); }

DX11Graphics::DX11Graphics()
{
	m_lpSwapChain = nullptr;
	m_lpImmediateContext = nullptr;
	m_lpDevice = nullptr;
}

bool DX11Graphics::InitGraphics(HWND _hwnd ,int _screenX,int _screenY,bool _winMode) {
	HRESULT hr;
	
	// �t�@�N�g������
	IDXGIFactory1* factory = nullptr;
	hr = ::CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&factory));
	if (FAILED(hr)) {
		MessageBox(NULL, "ERROR!", "�t�@�N�g���������s", 0);
		SAFE_RELEASE(factory);
		return false;
	}

	// �A�_�v�^�̎擾�i�f�t�H���g�j
	IDXGIAdapter1* adapter = nullptr;
	hr = factory->EnumAdapters1(0, &adapter);
	if (FAILED(hr)) {
		MessageBox(NULL, "ERROR!", "�A�_�v�^�擾���s", 0);
		SAFE_RELEASE(adapter);
		return false;
	}

	// �@�\���x��
	D3D_FEATURE_LEVEL	featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	UINT			featureLevelsNum = sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL);
	D3D_FEATURE_LEVEL	validFeatureLevel;

	// �X���b�v�`�F�C���̐ݒ�
	DXGI_SWAP_CHAIN_DESC	scDesc;
	ZeroMemory(&scDesc, sizeof(scDesc));
	scDesc.BufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	scDesc.BufferDesc.Width = _screenX;							// �o�b�N�o�b�t�@�̕�
	scDesc.BufferDesc.Height = _screenY;						// �o�b�N�o�b�t�@�̍���
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// �o�b�N�o�b�t�@�t�H�[�}�b�g(0.0 �` 1.0)
	scDesc.BufferDesc.RefreshRate.Numerator = 60;				// ���t���b�V�����[�g�i����j
	scDesc.BufferDesc.RefreshRate.Denominator = 1;				// ���t���b�V�����[�g�i���q�j
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// �o�b�N�o�b�t�@�̎g�p���@
	scDesc.OutputWindow = _hwnd;
	scDesc.SampleDesc.Count = 1;								
	scDesc.SampleDesc.Quality = 0;
	scDesc.Windowed = _winMode;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// �f�o�C�X�ƃX���b�v�`�F�C�����쐬����
	hr = D3D11CreateDeviceAndSwapChain(
		adapter,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		featureLevels,
		featureLevelsNum,
		D3D11_SDK_VERSION,
		&scDesc,
		&m_lpSwapChain,
		&m_lpDevice,
		&validFeatureLevel,
		&m_lpImmediateContext);

	if (FAILED(hr)) { 
		MessageBox(NULL, "ERROR!", "�A�_�v�^�擾���s", 0);
		SAFE_RELEASE(factory);
		SAFE_RELEASE(adapter);
		Exit();
		return false; 
	}


	return true;

	
	return true;
}

void DX11Graphics::Exit() {

	SAFE_RELEASE(m_lpSwapChain);
	SAFE_RELEASE(m_lpImmediateContext);
	SAFE_RELEASE(m_lpDevice);

}

DX11Graphics::~DX11Graphics()
{
}