#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define iA 843314861
#define iB 453816693
#define iM 1073741824

/*DECLARAÇÃO DE VARIÁVEIS E PARAMETROS*/
#define N 1000
#define MU 0.016
#define B 3.5
#define Y 0.33
#define DT 0.1
#define INFINI 5 /*INDICE DO INDIVIDUO INFECTADO*/
#define TF 300

#define PROPINF 0.1



int controle,R0;

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
  int n,ind;
  ind=(int)TF/DT;
  int S[ind],I[ind],R[ind];

  init_list();

  S[j]=lerQtd(P,0);
  I[j]=lerQtd(P,1);
  R[j]=lerQtd(P,2);
  fprintf(resultado,"%d %d %d\n",S[j],I[j],R[j]);


   /*fprintf(resultado,"S I R\n");*/
  for(t=0;t<=TF;t+=DT)
    {
        j++;
        /*printf("%f \n",sorteio);*/
        for (n=0;n<N;n++)/*Varre os Individuos*/
        {
           if (rand0()<MU*DT) /*MORTE DO INDIVIDUO  */
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
                                            if (rand0()<((B*DT)/(N-1))) /* ((B*DT)/(N-1))*/
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
                            if (rand0()<Y*DT) /*RECUPERAÇÃO DO INDIVIDUO  */
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
    int t,x,propinf,posinf;
    propinf=(int)N*PROPINF; /*quantidade de infectados*/
    for (t=0;t<N;t++)
    {
       P[t]=0;
       Paux[t]=0;
    }
    for (t=0;t<propinf;t++)
    {
        posinf=rand()%N;
        P[posinf]=1;
        Paux[posinf]=1;
    }
}
