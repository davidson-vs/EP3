// Davidson Vieira de Souza Nº USP:12611668
// Gabriel Jasen Marques Nº USP:12542741

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// constante que define o valor maximo que um pixel pode assumir.

#define VALOR_MAXIMO 255

// constantes que definem as strings que podem ser especificadas na entrada, cada uma associada uma operacao.

#define RETA "RETA"
#define RETANGULO_CONTORNO "RETANGULO_CONTORNO"
#define RETANGULO_PREENCHIDO "RETANGULO_PREENCHIDO"
#define CLONA "CLONA"
#define CLONA_INV "CLONA_INV"
#define CLONA_HOR "CLONA_HOR"
#define CLONA_VER "CLONA_VER"
#define FIM "FIM"

// estrutura que representa uma imagem.

typedef struct
{

   int altura;   // altura da imagem (numero de linhas)
   int largura;  // largura da imagem (numero de colunas na imagem)
   int **matriz; // ponteiro para a matriz que armazena o conteudo da imagem

} Imagem;

// estrutura que representa um Ponto no plano 2D.

typedef struct
{

   int x; // coordenada horizontal
   int y; // coordenada vertical

} Ponto2D;

// funcao que cria uma imagem vazia e a devolve. Precisar ser completada para funcionar corretamente.

Imagem *cria_imagem(int largura, int altura)
{

   Imagem *imagem = (Imagem *)malloc(sizeof(Imagem));

   imagem->altura = altura;   // isto está correto?
   imagem->largura = largura; // e isto?

   imagem->matriz = (int **)malloc(imagem->altura * sizeof(int *));

   int i, j;
   int k = 0;

   for (k = 0; k < imagem->altura; k++)
   {
      imagem->matriz[k] = (int *)malloc(imagem->largura * sizeof(int *));
   }

   for (i = 0; i < imagem->altura; i++)
   {
      for (j = 0; j < imagem->largura; j++)
      {
         imagem->matriz[i][j] = 0;
      }
   }
   return imagem;
   /* 
	  Você deve completar esta função para que ela inicialize corretamente a estrutura ja alocada,
	  incluindo a alocacao dinâmica do campo 'matriz' de acordo com a largura e altura fornecidas. 
   */
}

// funcao (ja completa) que libera os recursos de memoria associados a uma imagem.

void libera_imagem(Imagem *imagem)
{

   int lin;

   for (lin = 0; lin < imagem->altura; lin++)
      free(imagem->matriz[lin]); // liberacao de cada linha da matriz (cada linha é um vetor de int)

   free(imagem->matriz); // liberacao da matriz (que é na realidade um vetor de linhas, ou um vetor de "vetor de int")
   free(imagem);         // liberacao da estrutura em si
}

// funcao (ja completa) que salva uma imagem em um arquivo, no formato PGM. Programas/utilitarios que trabalham
// com imagens bitmap (como o Gimp e visualizadores de imagens normalmente instalados em ambiente Linux) em geral
// reconhecem formato. Se tiver dificuldades para visualizar os arquivos de imagem salvos por esta funcao, um visualizador
// online pode ser encontrado neste link: http://paulcuth.me.uk/netpbm-viewer/.

void salva(Imagem *imagem, char *nomeArquivo)
{

   int lin, col;
   FILE *saida = fopen(nomeArquivo, "w"); // abertura do arquivo para escrita ("w" - write)

   if (saida)
   {

      // o 'fprintf' funciona de forma igual ao 'printf', com a diferença que
      // o conteudo eh escrito em um arquivo (associado a variavel 'saida')

      fprintf(saida, "P2\n%d %d\n%d\n", imagem->largura, imagem->altura, VALOR_MAXIMO);

      for (lin = 0; lin < imagem->altura; lin++)
      {

         for (col = 0; col < imagem->largura; col++)
         {

            fprintf(saida, (col == 0 ? "%d" : " %d"), imagem->matriz[lin][col]);
         }

         fprintf(saida, "\n");
      }
   }

   fclose(saida); // fechamento do arquivo
}

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//  Funcoes que implementam as operacoes de desenho. Todas precisam ser completadas.  //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

// desenha uma reta que tem origem no ponto 'p1' e termina no ponto 'p2', na tonalidade de cinza definida em 'cor'.

void reta(Imagem *imagem, Ponto2D p1, Ponto2D p2, int cor)
{
   int deltaX = p2.x - p1.x;
   int deltaY = p2.y - p1.y;
   int i, k;
   float inclinacao = ceil(deltaX / deltaY);

   for (i = 0; i < imagem->altura; i++)
   {
      k = i * inclinacao;
      imagem->matriz[k][i] = cor;
      if (i * inclinacao > imagem->largura)
      {
         break;
      }
   }
   /* completar */
}

// desenha o contorno de um retangulo com cantos opostos em 'p1' e 'p2', na tonalidade de cinza definida em 'cor'.
// Você não pode assumir nada em relacao a posicao dos cantos 'p1' e 'p2', apenas que tratam-se de cantos opostos.

void retangulo_contorno(Imagem *imagem, Ponto2D p1, Ponto2D p2, int cor)
{
   int i, j;
   if (p1.y < p2.y && p1.x < p2.x)
   {
      for (j = p1.x; j <= p2.x; j++)
      {

         imagem->matriz[p1.y][j] = cor;
         imagem->matriz[p2.y][j] = cor;
      }
      for (i = p1.y; i <= p2.y; i++)
      {
         imagem->matriz[i][p1.x] = cor;
         imagem->matriz[i][p2.x] = cor;
      }
   }

   if (p1.y > p2.y && p1.x < p2.x)
   {
      for (j = p1.x; j <= p2.x; j++)
      {
         imagem->matriz[p2.y][j] = cor;
         imagem->matriz[p1.y][j] = cor;
      }
      for (i = p2.y; i <= p1.y; i++)
      {
         imagem->matriz[i][p1.x] = cor;
         imagem->matriz[i][p2.x] = cor;
      }
   }

   if (p1.y < p2.y && p1.x > p2.x)
   {
      for (j = p1.x; j <= p2.x; j++)
      {
         imagem->matriz[p1.y][j] = cor;
         imagem->matriz[p2.y][j] = cor;
      }
      for (i = p2.y; i <= p1.y; i++)
      {
         imagem->matriz[i][p2.x] = cor;
         imagem->matriz[i][p1.x] = cor;
      }
   }

   if (p1.y > p2.y && p1.x > p2.x)
   {
      for (j = p1.x; j <= p2.x; j++)
      {
         imagem->matriz[p2.y][j] = cor;
         imagem->matriz[p1.y][j] = cor;
      }
      for (i = p2.y; i <= p1.y; i++)
      {
         imagem->matriz[i][p2.x] = cor;
         imagem->matriz[i][p1.x] = cor;
      }
   }
   /* completar */
}

// desenha um retangulo preenchido com cantos opostos em 'p1' e 'p2', na tonalidade de cinza definida em 'cor'.
// Você não pode assumir nada em relacao a posicao dos cantos 'p1' e 'p2', apenas que tratam-se de cantos opostos.

void retangulo_preenchido(Imagem *imagem, Ponto2D p1, Ponto2D p2, int cor)
{

   int i, j;
   if (p1.y < p2.y && p1.x < p2.x)
   {
      for (i = p1.y; i <= p2.y; i++)
      {
         for (j = p1.x; j <= p2.x; j++)
         {

            imagem->matriz[i][j] = cor;
         }
      }
   }

   if (p1.y > p2.y && p1.x < p2.x)
   {
      for (i = p2.y; i <= p1.y; i++)
      {
         for (j = p1.x; j <= p2.x; j++)
         {
            imagem->matriz[i][j] = cor;
         }
      }
   }

   if (p1.y < p2.y && p1.x > p2.x)
   {
      for (i = p1.y; i <= p2.y; i++)
      {
         for (j = p2.x; j <= p1.x; j++)
         {
            imagem->matriz[i][j] = cor;
         }
      }
   }

   if (p1.y > p2.y && p1.x > p2.x)
   {
      for (i = p2.y; i <= p1.y; i++)
      {
         for (j = p2.x; j <= p1.x; j++)
         {
            imagem->matriz[i][j] = cor;
         }
      }
   }
   /* completar */
}

// copia o conteudo da area compreendida no retangulo delimitado pelos cantos opostos 'p1' e 'p2' para uma região destino
// na imagem. Para esta funcao, voce pode assumir que 'p1' representa o canto superior esquerdo da area a ser copiada,
// 'p2' o canto inferior direito desta mesma area, e 'p3' o canto superior esquerdo da regiao que receberá a copia.

void clona(Imagem *imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
   int i, j;
   if (p1.y < p2.y && p1.x < p2.x)
   {
      for (i = p1.y; i <= p2.y; i++)
      {
         for (j = p1.x; j <= p2.x; j++)
         {
            imagem->matriz[p3.y + i - p1.y][p3.x + j - p1.x] = imagem->matriz[i][j];
         }
      }
   }

   if (p1.y > p2.y && p1.x < p2.x)
   {
      for (i = p2.y; i <= p1.y; i++)
      {
         for (j = p1.x; j <= p2.x; j++)
         {
            imagem->matriz[p3.y + i - p2.y][p3.x + j - p1.x] = imagem->matriz[i][j];
         }
      }
   }

   if (p1.y < p2.y && p1.x > p2.x)
   {
      for (i = p1.y; i <= p2.y; i++)
      {
         for (j = p2.x; j <= p1.x; j++)
         {
            imagem->matriz[p3.y + i - p1.y][p3.x + j - p2.x] = imagem->matriz[i][j];
         }
      }
   }

   if (p1.y > p2.y && p1.x > p2.x)
   {
      for (i = p2.y; i <= p1.y; i++)
      {
         for (j = p2.x; j <= p1.x; j++)
         {
            imagem->matriz[p3.y + i - p2.y][p3.x + j - p2.x] = imagem->matriz[i][j];
         }
      }
   }
   /* completar */
}

// similar a funcao acima, mas invertendo o valor dos pixels copiados para a região destino. Isto é, pixels brancos devem
// se tornar pretos, pixels pretos se tornar brancos, e pixels em tons de cinza devem assumir o valor complementar (aquele
// que somado ao valor original resulta no valor definido na constante VALOR_MAXIMO).

void clona_inverte_cor(Imagem *imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
   int i, j;
   if (p1.y < p2.y && p1.x < p2.x)
   {
      for (i = p1.y; i <= p2.y; i++)
      {
         for (j = p1.x; j <= p2.x; j++)
         {
            imagem->matriz[p3.y + i - p1.y][p3.x + j - p1.x] = 255 - imagem->matriz[i][j];
         }
      }
   }

   if (p1.y > p2.y && p1.x < p2.x)
   {
      for (i = p2.y; i <= p1.y; i++)
      {
         for (j = p1.x; j <= p2.x; j++)
         {
            imagem->matriz[p3.y + i - p2.y][p3.x + j - p1.x] = 255 - imagem->matriz[i][j];
         }
      }
   }

   if (p1.y < p2.y && p1.x > p2.x)
   {
      for (i = p1.y; i <= p2.y; i++)
      {
         for (j = p2.x; j <= p1.x; j++)
         {
            imagem->matriz[p3.y + i - p1.y][p3.x + j - p2.x] = 255 - imagem->matriz[i][j];
         }
      }
   }

   if (p1.y > p2.y && p1.x > p2.x)
   {
      for (i = p2.y; i <= p1.y; i++)
      {
         for (j = p2.x; j <= p1.x; j++)
         {
            imagem->matriz[p3.y + i - p2.y][p3.x + j - p2.x] = 255 - imagem->matriz[i][j];
         }
      }
   }
   /* completar */
}

// similar a funcao 'clona', mas espelhando horizontalmente a região copiada.

void clona_espelha_horizontal(Imagem *imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
   int i, j;
   if (p1.y < p2.y && p1.x < p2.x)
   {
      for (i = p1.y; i <= p2.y; i++)
      {
         for (j = p1.x; j <= p2.x; j++)
         {
            imagem->matriz[p3.y + i - p1.y][p3.x + p2.x - j] = imagem->matriz[i][j];
         }
      }
   }

   if (p1.y > p2.y && p1.x < p2.x)
   {
      for (i = p2.y; i <= p1.y; i++)
      {
         for (j = p1.x; j <= p2.x; j++)
         {
            imagem->matriz[p3.y + i - p2.y][p3.x + p2.x - j] = imagem->matriz[i][j];
         }
      }
   }

   if (p1.y < p2.y && p1.x > p2.x)
   {
      for (i = p1.y; i <= p2.y; i++)
      {
         for (j = p2.x; j <= p1.x; j++)
         {
            imagem->matriz[p3.y + i - p1.y][p3.x + p1.x - j] = imagem->matriz[i][j];
         }
      }
   }

   if (p1.y > p2.y && p1.x > p2.x)
   {
      for (i = p2.y; i <= p1.y; i++)
      {
         for (j = p2.x; j <= p1.x; j++)
         {
            imagem->matriz[p3.y + i - p2.y][p3.x + p1.x - j] = imagem->matriz[i][j];
         }
      }
   }
   /* completar */
}

// similar a funcao 'clona', mas espelhando verticalmente a região copiada.

void clona_espelha_vertical(Imagem *imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
   /* completar */
}

/////////////////////////////////////////////////////////
//                                                     //
//  Program principal. Também precisa ser completado.  //
//                                                     //
/////////////////////////////////////////////////////////

int main()
{

   int largura, altura;
   char operacao[32], nome_arquivo[256];
   Imagem *img;
   Ponto2D p1, p2, p3;
   int cor;

   scanf("%s %d %d", nome_arquivo, &largura, &altura);
   img = cria_imagem(largura, altura);

   while (scanf("%s", operacao) == 1 && strcmp(operacao, FIM) != 0)
   {
      if ((strcmp(operacao, "RETANGULO_CONTORNO") == 0))
      {
         scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
         retangulo_contorno(img, p1, p2, cor);
      }
      if (strcmp(operacao, "RETANGULO_PREENCHIDO") == 0)
      {
         scanf("%d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &cor);
         retangulo_preenchido(img, p1, p2, cor);
      }
      if ((strcmp(operacao, "CLONA") == 0))
      {
         scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
         clona(img, p1, p2, p3);
      }
      if ((strcmp(operacao, "CLONA_INV") == 0))
      {
         scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
         clona_inverte_cor(img, p1, p2, p3);
      }
      if ((strcmp(operacao, "CLONA_HOR") == 0))
      {
         scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
         clona_espelha_horizontal(img, p1, p2, p3);
      }
      if ((strcmp(operacao, "CLONA_VER") == 0))
      {
         scanf("%d %d %d %d %d %d", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
         clona_espelha_vertical(img, p1, p2, p3);
      }
      /* completar */

      // voce deve verificar o conteudo da string 'operacao' para definir qual a operacao
      // de desenho a ser realizada, e chamar a funcao adequada para tal. Nao se esqueca
      // de ler os parametros adicionais esperados para a operacao a ser realizada. Caso
      // o conteudo da string nao corresponda a nenhuma das operacoes reconhecidas (como
      // as definidas nas constantes) voce pode simplesmente ignorar o comando na iteracao
      // atual.
   }

   salva(img, nome_arquivo);
   libera_imagem(img);
   printf("terminou\n");
   return 0;
}