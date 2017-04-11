#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define iA 843314861
#define iB 453816693
#define iM 1073741824



/*DECLARAÇÃO DE VARIÁVEIS E PARAMETROS*/
#define N 400
#define MU 0.016
#define B 0.25
#define Y 0.4
#define DT 0.1
#define INFINI 5 /*INDICE DO INDIVIDUO INFECTADO*/
#define TF 60000

int indice;
/*indice=(int)TF/DT;*/
int controle,R0;
int S[600000],I[600000],R[600000];
int isem=123456789;
int Paux[N],P[N];

float rand0();
int lerQtd(const int Pop[], int state);
void init_list(void);


void main()
{
  FILE *resultado;
  resultado=fopen("resultados.txt","w");
    if (!resultado) printf("Erro na abertura do arquivo.");

  float t;
  int i,j=0;
  int n;

  init_list();
  P[INFINI]=1;

  /*fprintf(resultado,"S I R\n");*/
  for(t=0;t<=TF;t+=DT)
    {
        j++;
        /*printf("%f \n",sorteio);*/
        for (n=0;n<N;n++)/*Varre os Individuos*/
        {
           if (rand()<MU*DT) /*MORTE DO INDIVIDUO  */
           {
              P[n]=0;
           }
           else if (P[n]==0)/*SE O INDIVIDUO n ESTIVER INFECTADO*/
                 {
                    if (rand()<((B*DT))) /* ((B*DT)/(N-1))*/
                    {
                      P[n]=1;
                    }
                 }
           else if (P[n]==1) 
                {
                  if (rand()<Y*DT) /*RECUPERAÇÃO DO INDIVIDUO  */
                      {
                        P[n]=2;
                      }
                }
        }
        S[j]=lerQtd(P,0);
        I[j]=lerQtd(P,1);
        R[j]=lerQtd(P,2);
        fprintf(resultado,"%d %d %d\n",S[j],I[j],R[j]);
        /*printf("%d %d %d %d\n",S[j],I[j],R[j],j);*/
   } /*FIM DO FOR DE TEMPO*/
  fclose(resultado);
} /*FIM DO MAIN*/

float rand0()
{
  float aux, x;
  aux = 0.5 / iM;
  isem = isem*iA + iB;
  if (isem < 0)
    isem = (isem + iM) + iM;
  x = isem*aux;
  return x;
}

int lerQtd(const int Pop[], int state)
{
   int k,contador=0;
   for (k=0;k<N;k++)
    {
      if (Pop[k]==state)
         contador++;
    }
   return contador;
}

void init_list(void)
{
    int t;
    for (t=0;t<N;t++)
    {
       P[t]=0;
       Paux[t]=0;
    }
}
