#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 21
#define numero 140//numero de cuadritos
//este
int columna= tam-1,fila= tam-1;
int optima  = (tam*tam +1);//mejor ruta
int iter;

void carga_tablero(int arry[][tam])
{
     int j,i;
     for (j=0; j<tam; j++)
     {
         for (i=0; i<tam; i++)
         {arry[j][i] = 0;}
     }
}//carga

void mostrar(int arry[][tam])
{
     int j,i;

     for (i=0; i<tam; i++)
     {
         for (j=0; j<tam; j++)
         {printf(" %2d |",arry[j][i]);}
         printf("\n\n");
     }
}//carga

void diseno(int arry[][tam])
{
     int i,j;
     for (i=0; i<tam*3+2; i++)
     printf("%c",205);
     printf("\n%c",186);
     for (i=0; i<tam; i++)
     {
         for (j=0; j<tam; j++)
         {
             if (arry[j][i] == -1)
             printf("%c%c%c",219,219,219);
             if (arry[j][i] == 0)
             printf("   ");
             if (arry[j][i] != 0 && arry[j][i] != -1)
             printf(" %c ",15);
             ///if(i == columna && j == fila)
             //printf(" %c ",15);

         }
         printf("%c\n%c",186,186);
     }
     for (i=0; i<tam*3+1; i++)
     printf("%c",205);
}

void aleatorio(int arry[][tam])
{
     int i, x, y;
     srand(time(NULL));
     for (i=0; i<numero; i++)
     {
         x = rand()%tam;
         y = rand()%tam;
         if(x != columna || y != fila)
         arry[x][y] = -1;

     }
}//aleatorio

void traspaso(int antes[][tam], int despues[][tam])
{
     int j,i;
     for (i=0; i<tam; i++)
     {
         for (j=0; j<tam; j++)
         {
             despues[j][i] = antes[j][i];
         }
     }
}//traspaso

void recusividad(int tab[][tam], int tab_aux[][tam],int casilla, int x, int y)
{
     int arrx[]={1,0,-1,0};//movimiento
     int arry[]={0,1,0,-1};

     int indice = 0;//vector
     int newx, newy;

     while(indice <= 3)
     {
           newx= x+arrx[indice];
           newy= y+arry[indice];

           //getchar();
           if ((tab[newx][newy] == 0) && (newx < tam && newx >= 0 && newy < tam && newy >= 0)&& (casilla < optima))
           {

               tab[newx][newy] = casilla;
               //system("cls");
               //diseno(tab);
               if (columna == newx && fila == newy)//encontro la solucion
               {
                   system("cls");
                   diseno(tab);


                   if (casilla < optima)//solo la mejor ruta
                   {
                       traspaso(tab,tab_aux);
                       optima = casilla;
                   }
               }

               recusividad(tab,tab_aux,casilla+1,newx,newy);
           }
           indice+=1;
     iter = iter + 1;
     }//while
     tab[x][y]= 0;
}//movimiento


int main()
{
    int tablero[tam][tam];
    int tablero_aux[tam][tam];
    int j,i;
    carga_tablero(tablero);
    carga_tablero(tablero_aux);
    aleatorio(tablero);
    printf("\n                     SOLUCION  LABERINTO\n");
    diseno(tablero);
    printf("\ncolumna y fila\n");
    scanf("%d%d",&j,&i);
    tablero[j][i]=1;
    recusividad(tablero,tablero_aux,2,j,i);
    diseno(tablero_aux);

    return 0;
}
