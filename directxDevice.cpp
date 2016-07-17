
#include "directxDevice.h"
using namespace DirectX;
DirectxDevice::DirectxDevice()
{
	//Constructor
}

void DirectxDevice::Initialize(HWND hwnd, bool windowed)
{	
	D3D_FEATURE_LEVEL fLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};
	UINT numFLevels = ARRAYSIZE(fLevels);
	
	GetClientRect(hwnd,&rectange);
	DXGI_SWAP_CHAIN_DESC swapDesc;

	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = rectange.right;
	swapDesc.BufferDesc.Height = rectange.bottom;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//swapDesc.BufferDesc.RefreshRate
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hwnd;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = windowed;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT result;
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, fLevels, numFLevels, D3D11_SDK_VERSION,
		&swapDesc, &swapChain, &dxDevice, &featureLevel, &dxContext);

	if(FAILED(result))
	{
		return;
	}

	// 2d ----
	auto options = D2D1_FACTORY_OPTIONS();
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
	result = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, options, &d2dFactory);
	if (FAILED(result)) {		
		return;
	}

	result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown * *>(&wrFactory));
	if (FAILED(result)) {
		return;
	}
	//-----




	//viewport z bufora
	ID3D11Texture2D* backBufferTex = 0;  
	swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBufferTex));
	dxDevice->CreateRenderTargetView(backBufferTex, nullptr, &renderView);

	dxContext->OMSetRenderTargets(1, &renderView, nullptr);

	viewPort.Width = rectange.right;
	viewPort.Height = rectange.bottom;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	dxContext->RSSetViewports(1, &viewPort);

	//rasterizer
		
	rasterizerState.FillMode = D3D11_FILL_SOLID;
	rasterizerState.CullMode = D3D11_CULL_BACK;
	rasterizerState.FrontCounterClockwise = false;
	rasterizerState.DepthBias = 0;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = true;
	rasterizerState.MultisampleEnable = true;
	rasterizerState.AntialiasedLineEnable = false;

	result = dxDevice->CreateRasterizerState(&rasterizerState, &g_pRasterState); //ustawienie stanu scissor enable
	if (FAILED(result)) {
		return;
	}
	//dxContext->RSSetState(g_pRasterState);
	//nieuzyteczne

	//2d -----
	IDXGISurface* dxgiSurf = 0;
	result = swapChain->GetBuffer(NULL, __uuidof(IDXGISurface), reinterpret_cast<void**>(&dxgiSurf));
	if (FAILED(result)) {
		return;
	}

	float dpiX;
	float dpiY;
	d2dFactory->GetDesktopDpi(&dpiX, &dpiY);

	auto d2dRTProps = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	result = d2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurf, &d2dRTProps, &d2dRenderTarget);
	if (FAILED(result)) {
		return;
	}

	//formaty i kolory textu
	result = d2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &d2dSolidBrush);
	if (FAILED(result)) {
		return;
	}

	result = wrFactory->CreateTextFormat(L"Consolas", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f, L"", &wrFormat);
	if (FAILED(result)) {
		return;
	}

	sprBatch = new DirectX::SpriteBatch(dxContext);
	m_states = new DirectX::CommonStates(dxDevice);
	
}

void DirectxDevice::spriteBegin()
{
	spriteBegin(0, 0, rectange.right, rectange.bottom);
}

void DirectxDevice::spriteBegin(int l, int t, int r, int b)
{
	
	sprBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied(),
		nullptr, nullptr, g_pRasterState,
		[=]()
	{
		CD3D11_RECT r(l, t, r, b);
		dxContext->RSSetScissorRects(1, &r);
	});
	
}

void DirectxDevice::spriteEnd()
{
	sprBatch->End();
}
void DirectxDevice::textBegin()
{
	textBegin(0, 0, rectange.right, rectange.bottom);
}
void DirectxDevice::textBegin(int l, int t, int r, int b)
{
	d2dRenderTarget->BeginDraw();
	d2dRenderTarget->PushAxisAlignedClip(
		D2D1::RectF(l, t, r, b),
		D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
		);
}

void DirectxDevice::textEnd()
{
	d2dRenderTarget->PopAxisAlignedClip();
	d2dRenderTarget->EndDraw();
}

void DirectxDevice::present()
{
	swapChain->Present(0, 0);
}

DirectxDevice::~DirectxDevice()
{
	if(dxContext)dxContext->ClearState();
	renderView->Release();
	swapChain->Release();
	dxContext->Release();
	dxDevice->Release();
	d2dFactory->Release();
	d2dSolidBrush->Release();
	d2dRenderTarget->Release();
}