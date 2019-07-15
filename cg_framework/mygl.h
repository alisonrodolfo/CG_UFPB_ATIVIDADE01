#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"


//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

colorRGBA interpolar(colorRGBA cor1, colorRGBA cor2, float size){

    cor.r = (cor1.r*size) + ((1-size)*cor2.r);
    cor.g = (cor1.g*size) + ((1-size)*cor2.g);
    cor.b = (cor1.b*size) + ((1-size)*cor2.b);
    cor.a = (cor1.a*size) + ((1-size)*cor2.a);

    return cor;
}

float size(float x1,float y1,float x2,float y2){ 
    return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
} 

void PutPixel(int x, int y, colorRGBA cor){


	if( x < 0  || y < 0  || x > IMAGE_HEIGHT || y > IMAGE_WIDTH)
	{
		return;
	
      	} else {
		FBptr[X_Y_IMAGE_WIDTH + 0] = cor.r;
		FBptr[X_Y_IMAGE_WIDTH + 1] = cor.g;
		FBptr[X_Y_IMAGE_WIDTH + 2] = cor.b;
		FBptr[X_Y_IMAGE_WIDTH + 3] = cor.a; 
	}

}


void MidPointLine(int x1, int x2, int y1, int y2,colorRGBA cor){
    
    int dx,dy,x,y,xfinal,p,incr_e,incr_ne;
 
    dx = abs(x1 - x2); dy=abs(y1-y2);
    p=2*dy-dx;
    incr_e=2*dy;  incr_ne=2*(dy-dx);
 
    if(x1>x2){
        x=x2; y=y2; xfinal=x1;
 
    }else{
        x=x1;  y=y1; xfinal=x2;
    }
        PutPixel(x,y,cor);
 
    while(x<xfinal){
        x++;
        if(p<0){
            p+=incr_e;
        }else{
            y++;
            p+=incr_ne;
        }
        PutPixel(x,y,cor);
 
    }
}



void DrawLine(int x1, int y1, int x2, int y2,colorRGBA cor1,colorRGBA cor2)
{
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    bool decisao = false;
    float tamanho_atual = 0.0, tamanho_final = size(x1,y1,x2,y2);

    if(dy > dx){
	/* Inverte o ponto */
	int aux = x1; x1 = y1; y1 = aux; 
	aux = x2; x2 = y2; y2 = aux;
        
	dx = x2-x1;
        dy = y2-y1;
        decisao = true;
    }
    if(x1>x2){
	/* Inverte o ponto */
    	int aux = x1; x1 = x2; x2 = aux;
	aux = y1; y1 = y2; y2 = aux;

        dx = x2-x1;
        dy = y2-y1;
    }
    double m = (double)dy/dx ;
    /* Calculo de ponto médio */
    float medX = x1+1;
    float medY = y1+( m>=0 ? 0.5 : -0.5 );
    /**** calculo de decisão somado com o termo independente ****/
    float d = -dx*medY + dy*medX + (-x1*y2 + x1*y2); 

    int x=x1,y=y1,xp, yp;
    for(x; x<=x2; x++) {
	if(decisao) { 
		xp = y; yp = x;
	} else {
		xp = x; yp = y;
	}
	tamanho_atual++;
	cor = interpolar(cor1,cor2, tamanho_atual/tamanho_final);
        PutPixel(xp,yp,cor);
        if(d > 0){
            if(m >= 0) { /* Se m>=0, então NE é escolhido. */
                y++;
                d-=dx;
            }
        } else {
            if( m < 0) { /* Se m<0, então E é escolhido. */
                y--;
                d+=dx;
            }
        }
        d+=dy;
    }
}

void DrawTriangle(int x1,int y1,int x2,int y2,int x3,int y3,colorRGBA cor1,colorRGBA cor2,colorRGBA cor3){
	//DrawLine(x1,y1,x2,y2,cor1,cor2);
	//DrawLine(x2,y2,x3,y3,cor1,cor3);
	DrawLine(x3,y3,x1,y1,cor3,cor2);	

}

//Para um círculo centrado na origem
void CurvePixel (int x,int y,colorRGBA cor)
{
	PutPixel( x, y,cor);
	PutPixel( y, x,cor);
	PutPixel( y,-x,cor);
	PutPixel( x,-y,cor);
	PutPixel(-x,-y,cor);
	PutPixel(-y,-x,cor);
	PutPixel(-y, x,cor);
	PutPixel(-x, y,cor);
}

void drawCurve(int radius) {

	int x = 0;
	int y = radius;
	int d = 1 - radius;
	float tamanho_atual = 0.0, tamanho_final = size(0,400,400,0);

	writeCirclePixel(x, y,cor);
	while (y > x) {
	if(d < 0) {
	// escolher E
		d += 2 * x + 3;
	} else {
		d += 2 * (x-y) + 5;
		--y;
	}
		++x;
		tamanho_atual++;
		cor = interpolar(red,blue, tamanho_atual/tamanho_final);
		CurvePixel(x, y,cor);
	}
}

#endif // _MYGL_H_

