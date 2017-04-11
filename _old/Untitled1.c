#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define iA 843314861
#define iB 453816693
#define iM 1073741824



/*DECLARAÇÃO DE VARIÁVEIS E PARAMETROS*/
#define N 2000
#define MU 0.1167
#define B 0.35
#define Y 0.2333
#define DT 0.1
#define INFINI 5 /*INDICE DO INDIVIDUO INFECTADO*/
#define TF 3000

int indice;
/*indice=(int)TF/DT;*/
int controle,R0;
int S[63535],I[63535],R[63535];

int Paux[N],P[N];

int isem=123456789;

float rand0();
int lerQtd(int Pop[], int state);
void init_list(void);


void main()
{
  FILE *resultado;
  resultado=fopen("resultados.txt","w");
    if (!resultado) printf("Erro na abertura do arquivo.");

  float t, sorteio;;
  int i=0,j=0;
  int n;

  init_list();
  P[INFINI]=1;

  fprintf(resultado,"S I R\n");
  for(t=0;t<=TF;t+=DT)
    {
        j++;
        sorteio=rand0();
        /*printf("%f \n",sorteio);*/
        for (n=0;n<N;n++)/*Varre os Individuos*/
        {
           if (sorteio<MU) /*MORTE DO INDIVIDUO  */
                {
                    Paux[n]=0;
                    /*Paux[n].R0=0;*/
                    if (n==INFINI)
                    {
                        controle=1;
                    }
                }
           else
             {
                    if (P[n]==1)/*SE O INDIVIDUO n ESTIVER INFECTADO*/
                        {
                            for (i=0;i<N;i++)/*PERCORRENDO A VIZINHANÇA DE N, REDE REGULAR*/
                                {
                                    if (i!=n)
                                        {
                                            if (sorteio<B) /* ((B*DT)/(N-1))*/
                                                {
                                                    if (P[i]==0)
                                                        {
                                                            Paux[i]=1;/*ESTÁ INFECTANDO O VIZINHO*/
                                                            /*Paux[n].R0++;*/
                                                            if ((n==INFINI) && (controle==0))
                                                                {
                                                                    R0++;
                                                                }
                                                        }
                                                }
                                        }
                                }
                            if (sorteio<Y) /*RECUPERAÇÃO DO INDIVIDUO  */
                                {
                                    Paux[n]=2;
                                    if (n==INFINI)
                                    {
                                        controle=1;
                                    }
                                }
                        }

            }
            /*  printf("Estado:%d Indice:%d Iteracao no tempo: %d\n",Paux[n],n,j);*/
        } /*FIM VARREDURA DOS INDIVIDUOS */
        for (n=0;n<N;n++)
        {
            P[n]=Paux[n];
            /*P[n].R0=Paux[n].R0;*/
        }

        S[j]=lerQtd(P,0);
        I[j]=lerQtd(P,1);
        R[j]=lerQtd(P,2);
        fprintf(resultado,"%d %d %d \n",S[j],I[j],R[j]);
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

int lerQtd(int Pop[], int state)
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
       P[t]=1;
       Paux[t]=1;
    }
}
