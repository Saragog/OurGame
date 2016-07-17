#include "basicSprite.h"


using namespace DirectX;

basicSprite::basicSprite(DirectxDevice * gDev, std::wstring fileName)
{
	gDevice = gDev;  //TODO sprawdzenia bledy
	HRESULT result;
	ID3D11Resource* res;
	result = CreateWICTextureFromFile(gDevice->dxDevice, fileName.c_str(), &(res), &(pImage), NULL);
	if (FAILED(result))
	{
		throw;
	}
	CD3D11_TEXTURE2D_DESC texDesc;
	((ID3D11Texture2D*)res)->GetDesc(&texDesc);
	height = texDesc.Height;
	width = texDesc.Width;	
}

void basicSprite::draw(int x, int y)
{
	gDevice->sprBatch->Draw(pImage, SimpleMath::Vector2(x, y));
}

void basicSprite::draw(int x, int y, int scale)
{
	gDevice->sprBatch->Draw(pImage,
		SimpleMath::Vector2(x, y),
		NULL,
		Colors::White,
		0.0,							//rotation
		SimpleMath::Vector2(0, 0),		//orgin
		scale,							//scale
		SpriteEffects::SpriteEffects_None,
		0);
}

basicSprite::~basicSprite()
{
}
