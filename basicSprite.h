#pragma once

#include "directxDevice.h"

class basicSprite
{
public:
	basicSprite(DirectxDevice *gDev, std::wstring fileName);
	void draw(int x, int y);
	void draw(int x, int y,int scale);
	~basicSprite();
private:
	int height;
	int width;
	DirectxDevice *gDevice;
	ID3D11ShaderResourceView* pImage;
};

