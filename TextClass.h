/*
	This class describes texts
	Enables us to set texts over our game.
	16.07.2016
*/

#include "basicSprite.h"

using namespace DirectX;

class TextClass
{
protected:
	std::string content;
	int length;
	IDWriteTextFormat* format;

public:
	TextClass(std::string cont, int length, IDWriteTextFormat* format);
	~TextClass();
	std::string getContent();
	int getLength();
	IDWriteTextFormat* getFormat();
};

