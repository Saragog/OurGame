#include "programControl.h"
#include "basicSprite.h"
#include "TextClass.h"

#define numberOfImages 3

#define matimage 0 // Mozemy tak z tego korzystac jak chcesz ale nie musimy mozna to wywalic
				   // nazywanie tych obrazkow by potem nie szukac numerka tylko jakas nazwe nadac porzadna
				   // proponuje nazywac jakos te obrazki porzadnie
#define whateverimage 1
#define andimage 2

DirectxDevice *gDevice;
basicSprite* sprites[numberOfImages];

using namespace std;
using namespace DirectX;

void init(HWND hwnd)
{
	gDevice = new DirectxDevice();
	gDevice->Initialize(hwnd, true);

	gDevice->sprBatch = new SpriteBatch(gDevice->dxContext);


	sprites[0] = new basicSprite(gDevice, L"sprite.png");
	sprites[1] = new basicSprite(gDevice, L"blue.png");
	sprites[2] = new basicSprite(gDevice, L"huehue.jpg");
	


	gDevice->text = L"twoja starafdsafdsafdsafdsa fdsa fdsafdsafdsafdsaffd";
		
		
	

}
void update()
{
	
	gDevice->dxContext->ClearRenderTargetView(gDevice->renderView, Colors::DarkGray);

	
	gDevice->spriteBegin(0,0,500,160);	

	sprites[0]->draw(200, 150);

	gDevice->spriteEnd();
	
	
	
	gDevice->textBegin();
	gDevice->d2dRenderTarget->DrawText(gDevice->text.c_str(), gDevice->text.length(), gDevice->wrFormat, D2D1::RectF(400, 400, 602, 852), gDevice->d2dSolidBrush);
	gDevice->textEnd();

	gDevice->spriteBegin();
	sprites[0]->draw(200, 170,3);
	sprites[0]->draw(300, 150);
	sprites[0]->draw(400, 150);
	sprites[0]->draw(500, 150);
	sprites[0]->draw(600, 150);
	sprites[2]->draw(700, 250);
	gDevice->spriteEnd();
	

	

	


	gDevice->present();

}

void close()
{
	delete gDevice;
}
