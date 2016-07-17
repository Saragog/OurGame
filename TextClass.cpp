#include "TextClass.h"

using namespace std;

TextClass::TextClass(string cont, int len, IDWriteTextFormat* form)
{
	content = cont;
	length = len;
	format = form;
}

TextClass::~TextClass()
{
}

string TextClass::getContent()
{
	return content;
}

int TextClass::getLength()
{
	return length;
}

IDWriteTextFormat* TextClass::getFormat()
{
	return format;
}