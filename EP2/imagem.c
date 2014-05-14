/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: Lucas Romao Silva
  NUSP: 8536214

  imagem.c

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:

  - função mallocSafe copiada de: 

       http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


/*
   Funcoes que manipulam uma imagem:
*/
#include <stdio.h>  /* fprintf, printf */
#include <stdlib.h> /* malloc, free,  */
#include "imagem.h" /* Byte, ImagemRGB, CelPixel, CelRegiao ... */

/*-------------------------------------------------------------
  contantes 
*/
#define EXIT_FAILURE_MALLOC -1

/*-------------------------------------------------------------
  Funcoes auxiliares 
*/
static void *mallocSafe (size_t nbytes);

static Boolean coresIguaisByte(Byte cor1[], Byte cor2[]);

static Boolean coresIguaisPixel(PixelRGB pix1, PixelRGB pix2);

/*-------------------------------------------------------------
  mallocImagemRGB
  
  Recebe inteiros width e height e retorna a estrutura que representa
  uma imagem RGB com height linhas e width colunas (height x width pixels). 
  Cada pixel da imagem e do tipo PixelRGB.
   
  Esta funcao utiliza a funcao mallocSafe.
 */
ImagemRGB *
mallocImagemRGB(int width, int height)
{
	int i;
   PixelRGB **p;
	ImagemRGB *Imagem;
	Imagem = mallocSafe(sizeof(ImagemRGB));
	

	p = mallocSafe(height*sizeof(PixelRGB*));
	for(i = 0; i < height; i++)
		p[i] = mallocSafe(width*sizeof(PixelRGB));
  /* O objetivo do return a seguir e evitar que 
     ocorra erro de sintaxe durante a fase de desenvolvimento 
     do EP. Esse return devera ser removido depois que
     a funcao estiver pronta.
  */
	Imagem->pixel = p;
	
  return Imagem;

}

/*-------------------------------------------------------------
  freeImagemRGB
  
  Recebe um ponteiro img para um estrutura que representa uma 
  imagem RGB e libera a memoria utilizada.
  
  Esta funcao utiliza a funcao free.
 */

void
freeImagemRGB(ImagemRGB *img)
{

	int i;
	printf("Entrei na funcao freeImagemRGB\n");
	for(i = 0; i< img->height; i++)
		free(img->pixel[i]);

	free(img->pixel);
	free(img);
	printf("Sai da funcao freeImagemRGB\n");
}


/*-------------------------------------------------------------
  freeImagemRGB
  
  Recebe um ponteiro listaRegioes para um lista de regioes
  e libera a memoria aloca para cada celula dessa lista.
  Tambem libera a memoria alocada para cada celula da lista 
  de pixels da regiao.

 */

void 
freeRegioes(CelRegiao *listaRegioes)
{

	CelRegiao *p, *morta;
	CelPixel *aux, *pmorta;
	printf("Entrei na funcao freeRegioes\n");
	p = listaRegioes;
	/*vou varrendo a lista de regioes, aqui estou sempre eliminando o primeiro elemento da lista, a mesma coisa vale para a lista de pixels*/	
	while(p != NULL){
				
		morta = p;
		/*aux e para varrer a lista de pixels*/
		aux = morta->ini;
		/*o procedimento aqui e igual ao do looping maior, guardo a parte atual numa variavel e dou free nela*/
		while(aux != NULL){

			pmorta = aux;
			aux = aux->prox;
			free(pmorta);
		}
		
		morta->ini = NULL;
		free(morta);

		p = p->prox;	
	}
	p = NULL;
	printf("Sai da funcao freeRegioes\n");
}

/*-------------------------------------------------------------
  getPixel

  Recebe um ponteiro img para uma estrutura que representa 
  uma imagem RGB e a posicao (x,y) de um pixel e retorna
  o valor do pixel (valor = representacao da cor do pixel).

 */

PixelRGB
getPixelRGB(ImagemRGB *img, int w, int h)
{
  
	PixelRGB pixelxy;
	pixelxy.red = img->pixel[h][w].red;
	pixelxy.green = img->pixel[h][w].green;
	pixelxy.blue = img->pixel[h][w].blue;
	pixelxy.visitado = img->pixel[h][w].visitado;
   
  
	return pixelxy;    
}

/*-------------------------------------------------------------
  setPixel

  Recebe uma imagem img, uma posicao (h,w) de um pixel e uma cor.
  A funcao pinta o pixel da posicao (h,w) com a cor dada.

*/

void
setPixelRGB(ImagemRGB *img, int w, int h, Byte cor[])
{
	img->pixel[h][w].red = cor[RED];
	img->pixel[h][w].green = cor[GREEN];
	img->pixel[h][w].blue = cor[BLUE];

}

/*-------------------------------------------------------------
  pinteImagem

  Recebe uma imagem img e uma cor e pinta todos os pixels
  da imagem com a cor dada.

  Esta funcao deve utilizar a funcao setPixelRGB.
 */ 

void 
pinteImagemRGB(ImagemRGB *img, Byte cor[])
{

	int i, j;
	for(i=0; i < img->height; i++)
		for(j =0; j < img->width; j++)
			setPixelRGB(img, j, i, cor);
						

		

}


/*-------------------------------------------------------------
  pinteImagem

  Recebe uma imagem, um ponteiro para uma lista de pixels 
  (de uma regiao) e uma cor. A funcao pinta todos os pixels da 
  imagem com a cor dada.

  Esta funcao deve utilizar a funcao setPixelRGB.
 */ 

void 
pinteRegiaoRGB(ImagemRGB *img, CelPixel *pixel, Byte cor[])
{

	CelPixel *p = pixel;
	while(p!= NULL){
	
		setPixelRGB(img, p->w, p->h, cor);
		p = p->prox;

	}

}



/*-------------------------------------------------------------*/ 
/* copieImagemRGB 

   Copia a imagem *origem para a imagem *destino. 
   
   Suponha que a imagem *destino já foi criada, ou seja, a
   memória utilizada pela matriz já foi alocada.

*/

void 
copieImagemRGB (ImagemRGB *destino, ImagemRGB *origem)
{
	int h,w;

	destino->width = origem->width;
	destino->height = origem->height;
	for(h = 0; h < origem->height; h++)
		for(w = 0; w < origem->width; w++){
			destino->pixel[h][w].red = origem->pixel[h][w].red;
			destino->pixel[h][w].green = origem->pixel[h][w].green;
			destino->pixel[h][w].blue = origem->pixel[h][w].blue;
			destino->pixel[h][w].visitado = origem->pixel[h][w].visitado;

		}

}

/*-------------------------------------------------------------*/ 
/*
  regioesImagem

  Recebe uma imagem img e cria e retorna um ponteiro para 
  o inicio de uma lista de regioes conexas da imagem.

  Cada uma dessas regioes conexas deve ser formada por pixels
  de uma mesma cor. 

  Cada celula da lista de regioes e do tipo CelRegiao e 
  contem um campo ini sera o ponteiro para o inicio da 
  lista de pixels que formam a regiao.
 
  Cada celula dessa lista de pixels e do tipo CelPixel.

  Esta funcao utiliza a funcao mallocSafe.
  Esta funcao deve utilizar a funcao pixelsRegiao que 
  cria e devolve a lista de pixels de cada regiao.

 */

CelRegiao *
regioesImagem(ImagemRGB *img)
{

	int h, w;
	CelRegiao *ini, *p;
	CelPixel *pixel;
	pixel = NULL;
	ini = NULL;
	/*aloca um espaco para a lista de regioes*/
	

	/*pega o numero de pixels da regiao e ja monta a lista de pixels*/

	/*p->nPixels = pixelsRegiao(img, 0, 0, img->pixel[0][0], &pixel);
	p->ini = pixel;
	p->cor[RED] = img->pixel[0][0].red;
	p->cor[GREEN] = img->pixel[0][0].green;
	p->cor[BLUE] = img->pixel[0][0].blue;
	p->prox = ini;

	ini = p;	
	*/

	for(h = 0; h < img->height; h++)
		for(w = 0; w < img->width; w++){

			if(img->pixel[h][w].visitado == FALSE){
				pixel = NULL;
				p = mallocSafe(sizeof(CelRegiao));
				p->nPixels = pixelsRegiao(img, w, h, img->pixel[h][w], &pixel);
				p->ini = pixel;
				p->cor[RED] = img->pixel[h][w].red;
				p->cor[GREEN] = img->pixel[h][w].green;
				p->cor[BLUE] = img->pixel[h][w].blue;
				p->prox = ini;
				
				ini = p;
				
			}
	

		}


  /* O objetivo do return a seguir e evitar que 
     ocorra erro de sintaxe durante a fase de desenvolvimento 
     do EP. Esse return devera ser removido depois que
     a funcao estiver pronta.
  */
  return ini; 
}

/*-------------------------------------------------------------*/ 
/* pixelsRegiao

   Atencao: Esta funcao deve ser recursiva.

   Recebe 
    
       * uma imagem img, 
       * uma posicao (h,w) de um pixel, 
       * um  pixel semente e
       * um  ponteiro *pIni para de uma lista de pixels. 

   A funcao cria uma lista de pixels e devolve essa lista 
   atraves do parametros *pIni.

   Essa lista devolvida deve ser criada recursivamente 
   visitando-se 

        - os vizinhos do pixel da posicao (h,w) 
          que tem a mesma cor que o pixel semente 
          e ainda nao foram visitados 
	- os vizinhos dos vizinhos .... que tem 
          a mesma cor que a semente e ainda nao 
          foram visitados 
	- os vizinhos, dos vizinhos, dos vizinhos ...
        - ...

    Um pixel tem de 3 (os quatro pixels do canto) a 8 
    vizinhos (pixels do meio da imagem).

    A funcao ainda retorna o numero de pixels na lista 
    devolvida.

    Cada celula da lista de pixels e do tipo CelPixel.
 */
int
pixelsRegiao(ImagemRGB *img, int w, int h, 
	     PixelRGB semente, CelPixel **pIni)
{
	int cont , aux;
	CelPixel *p;
	cont = aux = 0;
	/*minha base e se o pixel ja foi visitado ou se a cor e diferente da semente*/
	if(((w<0 || h<0) || (w > img->width - 1 || h > img->height - 1)) || img->pixel[h][w].visitado || !coresIguaisPixel(img->pixel[h][w], semente)){
		return 0;
		
	}
	else{	
			img->pixel[h][w].visitado = TRUE;

			/*aqui tento pegar o numero de pixels dos oito vizinhos dele*/
			
			if(w != (img->width - 1)){
				aux += pixelsRegiao(img, w+1, h, semente, pIni);
				
				if(h != 0)
					aux += pixelsRegiao(img, w+1, h-1, semente, pIni);
			
				if(h != (img->height - 1))
					aux += pixelsRegiao(img, w+1, h+1, semente, pIni);
					
			}
			
			if(w != 0){
				aux += pixelsRegiao(img, w-1, h, semente, pIni);
				
				if(h != 0)
					aux += pixelsRegiao(img, w-1, h-1, semente, pIni);
				
				if(h != (img->height - 1))
					aux += pixelsRegiao(img, w-1, h+1, semente, pIni);
								
			}
		   if(h != 0){
						
				aux += pixelsRegiao(img, w, h-1, semente, pIni);
		
			}

			if(h != (img->height - 1))
				aux += pixelsRegiao(img, w, h+1, semente, pIni);

			p = mallocSafe(sizeof(CelPixel));
			p->w = w;
			p->h = h;
			p->prox = *pIni;
			*pIni = p;

			cont = cont + aux;
			cont++;
			return cont;
	}
  /* O objetivo do return a seguir e evitar que 
     ocorra erro de sintaxe durante a fase de desenvolvimento 
     do EP. Esse return devera ser removido depois que
     a funcao estiver pronta.
  */
 
}
 
 
/*-------------------------------------------------------------*/ 
/* trocaCor

   Recebe uma imagem, a lista de regioes conexas e de mesma cor,
   uma cor antiga e uma cor nova. 

   A funcao pinta todos os pixels da imagem que tem a cor antiga 
   com a cor nova. 

   Para isto a funcao percorre a lista de regioes e para cada 
   regiao de pixels com a cor antiga percorre a lista de 
   pixels pintando-os com a cor nova.

   Esta funcao deve itilizar a funcao coresIguaisByte.
   Esta funcao deve utilizar a funcao pintaRegiaoRGB.
*/

void
trocaCorRGB (ImagemRGB *img, CelRegiao *listaRegioes, Byte cor[3], Byte corNova[3])
{

		CelRegiao *p;
		
		for(p = listaRegioes; p != NULL; p = p->prox)
			if(coresIguaisByte(p->cor, cor))
				pinteRegiaoRGB(img, p->ini,corNova);


}


/* 
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    IMPLEMENTACAO DAS FUNCOES DADAS

////////////////////////////////////////////////////////////////////// 
*/

/*-------------------------------------------------------------*/ 
/* coresIguaisPixel

   Recebe dois pixels e retorna TRUE se eles tem a mesma cor 
   e FALSE em caso contrario.
*/
 
static Boolean
coresIguaisPixel(PixelRGB pix1, PixelRGB pix2)
{
  return pix1.red   == pix2.red
     &&  pix1.green == pix2.green
     &&  pix1.blue  == pix2.blue;   
} 


/*-------------------------------------------------------------*/ 
/* coresIguaisByte

   Recebe duas cores no formato de vetor de bytes retorna TRUE se 
   sao iguais e FALSE em caso contrario.
*/
 
static Boolean
coresIguaisByte(Byte cor1[], Byte cor2[])
{
  return cor1[RED]   == cor2[RED]
     &&  cor1[GREEN] == cor2[GREEN]
     &&  cor1[BLUE]  == cor2[BLUE];   
} 

/*-------------------------------------------------------------*/ 
/*  mallocSafe 

   O parâmetro de mallocSafe é do tipo size_t.  
   Em muitos computadores, size_t é equivalente a unsigned int.  
   A função mallocSafe não está em nenhuma biblioteca e é desconhecida 
   fora destas notas de aula. 
   Ela é apenas uma abreviatura conveniente.

   Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
 */

static void 
*mallocSafe (size_t nbytes)
{
   void *ptr;

   ptr = malloc (nbytes);
   if (ptr == NULL) {
     fprintf (stderr, "Socorro! malloc devolveu NULL!\n");
     exit (EXIT_FAILURE_MALLOC);
   }

   return ptr;
}
