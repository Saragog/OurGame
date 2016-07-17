#ifndef DIRECTXDEVICE_H
#define DIRECTXDEVICE_H

#include <DirectXColors.h>
#include <d3d11.h>
#include <d2d1.h>
#include <dxgi.h>
#include <dwrite.h>
#include "SpriteBatch.h"
#include "CommonStates.h"
#include "WICTextureLoader.h"
#include "SimpleMath.h"

#include <string.h>






class DirectxDevice
{
public:
	DirectxDevice();
	~DirectxDevice();
	
	void Initialize(HWND hwnd, bool windowed);

	void spriteBegin();
	void spriteBegin(int l, int t, int r, int b);
	void spriteEnd();
	void textBegin();
	void textBegin(int l, int t, int r, int b);
	void textEnd();
	void present();
	
	ID3D11Device* dxDevice;
	ID3D11DeviceContext* dxContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderView; //3d
	RECT rectange; //rozmiar wnetrza okna

	ID2D1Factory* d2dFactory;
	IDWriteFactory* wrFactory;
	ID2D1RenderTarget*  d2dRenderTarget;  //text w 2d
	ID2D1SolidColorBrush*  d2dSolidBrush;
	IDWriteTextLayout*  wrLayout;
	IDWriteTextFormat* wrFormat;

	
	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;
	D3D11_VIEWPORT viewPort;
	ID3D11RasterizerState* g_pRasterState;
	D3D11_RASTERIZER_DESC rasterizerState;

	DirectX::CommonStates* m_states;
	DirectX::SpriteBatch* sprBatch;
	

	
	
	std::wstring text;


private:
	
	
};

#endif /* DIRECTXDEVICE_H */