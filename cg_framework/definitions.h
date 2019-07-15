#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define IMAGE_WIDTH  512 // número de colunas da imagem.
#define IMAGE_HEIGHT 512 // número de linhas da imagem.

#define X_Y_IMAGE_WIDTH (x + y * IMAGE_WIDTH) * 4
//#define X_Y_IMAGE_WIDTH 4*x + 4*y*IMAGE_WIDTH
unsigned char * FBptr;

struct pixel2D {
      int x;
      int y;
   }; 
struct colorRGBA {
      int r;
      int g;
      int b;
      int a;
   };

struct pixel2D pixel;
struct colorRGBA cor;

colorRGBA red = { 255, 0, 0, 255 };
colorRGBA gree = { 0, 255, 0, 255 };
colorRGBA blue = { 0, 0, 255, 255 };
colorRGBA yellow = { 255, 255, 0, 255 };
colorRGBA pastel = { 245, 245, 245, 255 };
colorRGBA magenta = { 255, 0, 255, 255 };


#endif // _DEFINITIONS_H_


