/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/*
   Neste exercicio programa usaremos apenas o Portable pixmap binary.

   http://netpbm.sourceforge.net/doc/ppm.html

   Funcoes para manipulacao de arquivos no formato Netpbm:
    
   Magic Number       Type                  Encoding
   P1              Portable bitmap          ASCII
   P2              Portable graymap         ASCII
   P3              Portable pixmap          ASCII
   P4              Portable bitmap          Binary
   P5              Portable graymap         Binary
   P6              Portable pixmap          Binary
 
   fonte: http://en.wikipedia.org/wiki/Netpbm_format

   ou ainda 
 
   meu_prompt> > man Netpbm
  
   netpbm(1)      General Commands Manual          netpbm(1)
  
   NAME
     netpbm - package of graphics manipulation programs and libraries
   [...]

 */

#undef DEBUG_CARREGA
#undef DEBUG_COR

#include <stdio.h>  /* fprintf, sprintf */
#include <stdlib.h> /* fopen, fclose, exit, EXIT_SUCCESS, EXIT_FAILURE */ 
#include <string.h> /* strncpy, strcat,... */

#include "io.h"     /* prototipos das funcoes de leitura e gravacao de imagens */

/* tamanho maximo de uma linha no arquivo */
#define MAX_NOME 128

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/*
 * Interface para uso do modulo io.c 
 *
 */

#ifndef _IMAGEM_H
# define _IMAGEM_H

# include "imagem.h" /* tipos e prototipos de funcoes que manipulam imagens */
#endif /* _IMAGEM_H */

/*-------------------------------------------------------------*/
/* indices de uma cor */
#define RED   0
#define GREEN 1
#define BLUE  2

#define TRUE  1
#define FALSE 0

/* Byte assume valores entre 0 e 255 (8 bits) */
typedef unsigned char Byte;

typedef Byte Boolean;

/* Cor indica o nivel/intensidade da cor */
typedef Byte Cor;

/*-------------------------------------------------------------*/
/* pixel True Color */
/* http://en.wikipedia.org/wiki/True_Color#True_color_.2824-bit.29 */
typedef struct pixelRGB PixelRGB;
struct pixelRGB {
  Byte    red;         /* valor entre 0 e 255 */
  Byte    green;       /* valor entre 0 e 255 */
  Byte    blue;        /* valor entre 0 e 255*/
  Boolean visitado;    /* TRUE ou FALSE */ 
}; 

/*------------------------------------------------------------*/
/* representacao para uma imagem colorida */
typedef struct imagemRGB ImagemRGB;
struct imagemRGB {
  int  width;        /* numero de colunas (width/largura) da imagem em pixels */
  int height;        /* numero de linhas  (height/altura) da imagem em pixels */
  PixelRGB **pixel;  /* matriz height x width de pixels com os níveis RGB     */
}; 

ImagemRGB *
mallocImagemRGB(int width, int height);

ImagemRGB *
carregueImagemPPM(char *nomeArquivo);



int main(){




}

ImagemRGB *
carregueImagemPPM(char *nomeArquivo)
{
  FILE *fEntrada;
  char magicNumber[3];
  int height;
  int width;
  int maxValue;  
  ImagemRGB *img;
  int w, h;


  fEntrada = fopen(nomeArquivo, "rb");
  if (fEntrada == NULL) 
    {
      fprintf(stderr, "ERRO! Nao consegui abrir o arquivo '%s'\n", nomeArquivo);
      exit(EXIT_FAILURE);
    }

  fprintf(stdout, "Arquivo '%s' com a imagem foi aberto.\n", nomeArquivo);

  /* confira o magicNumber */
  fgets(magicNumber, 3, fEntrada);
  if (strncmp("P6", magicNumber, 2))
    {
      fprintf(stderr, 
	      "ERRO! '%s' nao contem uma imagem no formato Portable pixmap binary\n"
	      "      MagicNumber '%s'\n", nomeArquivo, magicNumber);
      exit(EXIT_FAILURE);
    }

  if (fscanf(fEntrada, "%d ", &width) != 1) 
    {
      fprintf(stderr, "ERRO! problema na leitura (width)\n");
      exit(EXIT_FAILURE);
    }

  if (fscanf(fEntrada, "%d\n", &height) != 1) 
    {
      fprintf(stderr, "ERRO! problema na leitura (height)\n");
      exit(EXIT_FAILURE);
    }

  if (fscanf(fEntrada, "%d\n", &maxValue) != 1) 
    {
      fprintf(stderr, "ERRO! problema na leitura (maxValue)\n");
      exit(EXIT_FAILURE);
    }
  
  /* cria estrutura para armazenar a imagem */
  img = mallocImagemRGB(width, height);
  img->width  = width;
  img->height = height;

#ifdef DEBUG_CARREGA
  fprintf(stderr, "Criei a imagem, width=%d, height=%d maxValue=%d\n", 
	  width, height, maxValue);
#endif

  /* A raster of Height rows, in order from top to bottom. */
  for (h = 0; h < img->height; h++)
    {
      for (w = 0; w < img->width; w++)
	{ 
	  Byte red, green, blue;

	  if (fscanf(fEntrada, "%c%c%c", &red, &green, &blue) != 3)
	    {
	      fprintf(stderr, "ERRO! problema na leitura (pixel (%d, %d))\n", h, w);
	      exit(EXIT_FAILURE);
	      freeImagemRGB(img);
	    }

	  img->pixel[h][w].red   =  red   ; /* intensidade vermelho */
	  img->pixel[h][w].green =  green ; /* intensidade verde */
	  img->pixel[h][w].blue  =  blue  ; /* intensidade azul */
	  img->pixel[h][w].visitado  = FALSE; 

#ifdef DEBUG_COR
	  if (190 < h && h < 200 && 290 < w && w < 300 )
	    fprintf(stderr, "Pixel w=%d h=%d cor = (%d,%d,%d)\n", 
		    w, h, red, green, blue);
#endif

#ifdef DEBUG_CARREGA
	  fprintf(stderr, "Pixel w=%d h=%d cor = (%f,%f,%f)\n", 
		  w, h, img->pixel[h][w].red, img->pixel[h][w].green, img->pixel[h][w].blue);
#endif

	}
    }

  fclose(fEntrada);

  fprintf(stdout, "A imagem foi carregada e o "
	          "arquivo '%s' foi fechado.\n", nomeArquivo);

  return img;
}
