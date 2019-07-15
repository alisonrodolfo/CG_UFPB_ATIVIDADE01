#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************

	//PutPixel(rand()%512,rand()%512,cor1);
 	
	//Bresenham(0,0,400,400);
	//DrawLine(512,0,0,512,red,blue);
	//DrawLine(256,0,256,512,blue,red);
	//DrawLine(0,0,512,512,gree,pastel);
	//DrawLine(0,256,512,256,pastel,gree);
	//DrawTriangle(128,128,384,384,128,384,red,blue,gree);
	//DrawTriangle(160,128,384,352,384,128,red,blue,gree);
	//DrawTriangle(200,100,300,100,250,50,red,blue,gree);
	//PutPixel(256,256,red);
	drawCurve(400);
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

