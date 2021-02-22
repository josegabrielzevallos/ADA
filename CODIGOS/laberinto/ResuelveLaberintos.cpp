#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
// #include<iostream>

void leerArchivo();
int infoC(int);
int metaCerca();
void MuestraLaberinto();
int evitaParedesDer(int);
int evitaParedesIzq(int);
void borraRastro(int,int,int);
void mueveJugador(int);
void dimensionaMatriz();
void menu();
bool backtracking(char, int, int);

int **m; // Matriz dinamica que guarda los datos del archivo.            
int f,c; // filas y columnas del laberinto            
int fp,cp; // coordenadas del jugador
int fs,cs; // coordenadas de la salida o meta
int ifp,icp; // coordenadas iniciales del jugador
const int ARRIBA=0, DERECHA=1, IZQUIERDA=2, ABAJO=3;
int direccion=ARRIBA; // El jugador inicia viendo hacia arriba
int movs; // Cuenta los movimientos que hace un jugador para llegar a la meta
int espacios; // Cuenta los espacios que hay en un laberinto
bool pasoApaso=false; // true si queremos ver el recorrido paso a paso 
bool vision=true; // true para que el jugador "vea la meta a lo lejos"
int metodo=1;
int pasosReales; // Solo para metodo backtracking
char ruta[20]="laberinto.txt"; // Nombre del archivo que tiene los datos del laberinto
bool ya;

bool backtracking(int i, int j){
//función backtracking (vuelta atras), cada vez que encuentra un callejon sin salida, se devuelve al principio del mismo.
// Este metodo prueba todos y cada uno de los posibles caminos, regresando al principio de ellos hasta encontrar la solucion
// Es el que mas consume recursos del sistema, pero al final nos muestra el camino mas corto.
       
   //comprueba si es solución
   if(m[i][j]==3){
       MuestraLaberinto();
       fp=i; cp=j;
       
       /* Descomenta este bloque para ver cuantos ciclos o pasos reales dio el programa
      printf("Movimientos %d, pasos reales %d. ",movs, pasosReales); //debug
      system("pause"); // debug
      */
      
      return true;
   }

   //marcar el camino
   m[i][j]=4; // Pone un punto por donde ya pasamos
   
   if (pasoApaso) {
      fp=i; cp=j;
      MuestraLaberinto();
      printf("Movimientos %d, pasos reales %d. ",movs, pasosReales);
      system("pause");
   }
   //else animCalculando(); Quise poner una animacion aqui mientras calculaba, pero se tarda mas
   movs++;
   pasosReales++; // Aumentamos un paso cada vez que llamamos a esta funcion 

   //Alternativas
   if(i-1>=0 && i-1<f && (m[i-1][j]==0 || m[i-1][j]==3))  if(backtracking(i-1, j)) return true; //arriba   
      
    if(j+1>=0 && j+1<c && (m[i][j+1]==0 || m[i][j+1]==3))  if(backtracking(i, j+1)) return true; //derecha     
      
    if(i+1>=0 && i+1<f && (m[i+1][j]==0 ||  m[i+1][j]==3)) if(backtracking(i+1, j)) return true; //abajo     
    
    if(j-1>=0 && j-1<c && (m[i][j-1]==0 ||  m[i][j-1]==3)) if(backtracking(i, j-1)) return true;//izquierda     
      
    //desmarcar el camino porque devolverá un paso
    m[i][j]=0;
    movs--;
    if (pasoApaso) {
      fp=i; cp=j;
      MuestraLaberinto();
      printf("Movimientos %d, pasos reales %d. ",movs, pasosReales);
      pasosReales++;
      system("pause");
   }
    return false;
}


void menu() {
     int opcion;
     
     while (opcion!=1) {
         system("cls");
         printf("------------------------  M E N U ------------------------\n\n");
         printf("Barra de estado|");
         if (pasoApaso) printf ("Paso a paso|");
         else           printf ("...........|");
         if (vision) printf ("Ver meta|");
         else        printf ("........|");
         if (metodo==0) printf ("Mano izquierda|");
         else if  (metodo==1) printf ("Mano derecha|");
         else printf ("Backtracking|");
         printf("Archivo:%s|",ruta);
         printf("\n\n\n");  
         
         printf("1) Resolver.\n\n");
         printf("2) Metodo de la mano derecha.\n\n");
         printf("3) Metodo de la mano izquierda.\n\n");
         printf("4) Mostrar paso a paso.\n\n");  
         printf("5) Ver meta.\n\n");
         printf("6) Cambiar nombre de archivo.\n\n");
         printf("7) Metodo de Backtracking.\n\n");
         printf("8) Salir.\n\n");
         //while (opcion<0 && opcion>6)
         //opcion = getch(); 
         printf("Opcion:");
         scanf ("%d",&opcion);        
         switch (opcion) {
                case 2: metodo=1; break;
                case 3: metodo=0; break;
                case 4:
                     if (pasoApaso) pasoApaso=false;
                     else pasoApaso=true; break;
                case 5: if (vision) vision=false;
                     else vision=true; break;
                case 6: 
                     printf ("Ingresa nuevo nombre de archivo:");
                     scanf ("%s",&ruta); ; break;
                case 7: metodo=2; break;
                case 8: exit(EXIT_SUCCESS); break;
         }
     }                      
}

void dimensionaMatriz() {
     bool flag=true; // Sirve para que aumente el numero de columnas solo hasta que encuentre el primer salto de linea
                     // suponiendo que el archivo tiene todas las lineas de igual numero de caracteres
    FILE *archivo;
    char caracter;
    int codigo; // codigo ascii del caracter leido de archivo
    
    archivo=fopen(ruta,"rt"); // abrimos el archivo en modo lectura de texto("rt")
    if (archivo==NULL) { // En caso de que el archivo no exista o que este mal el nombre
       printf("Error en lectura de archivo\n");
       system("pause");
       exit (EXIT_FAILURE); // Terminacion del programa por falla
    }
    f=1;c=1;
    while(!feof(archivo)) { // Dimensionamos nuestra matriz
            caracter=fgetc(archivo);
            codigo = caracter; // obtenemos el codigo Ascii de el caracter
            
            if (codigo==10) { // codigo del salto de linea
               f++; // Si encontramos un enter añadimos una fila mas a nuestra matriz
               if (flag) flag=false; // solo lo hacemos una vez
            } 
            else if (flag) c++;// añadimos una columna mas a nuestra matriz               
    }
    fclose(archivo); 
    
    // Dimensionamos m[][] dinamicamente 
    m = (int **)malloc (f*sizeof(int *));        
    for (int j=0;j<f;j++) m[j] = (int *) malloc (c*sizeof(int));      
}

void leerArchivo() {
    int ff,cc,codigo;
    FILE *archivo;
    char caracter;      
    
    archivo=fopen(ruta,"rt"); // abrimos el archivo "laberinto.txt" en modo lectura de texto("rt"
    if (archivo==NULL) { // En caso de que el archivo no exista o que este mal el nombre
       printf("Error en lectura de archivo\n");
       system("pause");
       exit (EXIT_FAILURE); // Terminacion del programa por falla
    }
    
    for (int i=0;i<f-1;i++){
       for (int ii=0;ii<c;ii++) {
           caracter=fgetc(archivo);
           codigo = caracter; // obtenemos el codigo Ascii de el caracter               
           if (codigo!=10) {
               m[i][ii]=codigo-48; // usamos el codigo ascii del caracter del archivo para hacerlo entero
               if (m[i][ii]==2){ifp=i;icp=ii;}
               if (m[i][ii]==3){fs=i;cs=ii;}
               if (m[i][ii]==0) espacios++; // contamos los espacios 
           }
               
       }
    }        
    fclose(archivo);      
}

int infoC(int dir) { // Devuelve informacion de la casilla inmediata al jugador
    switch (dir) {
       case ARRIBA: return m[fp-1][cp];break;
       case ABAJO: return m[fp+1][cp]; break;
       case IZQUIERDA: return m[fp][cp-1]; break;
       case DERECHA: return m[fp][cp+1];break;
    }
	return 0;}

int infoC(int dir,int dist) { // Devuelve informacion de la casilla a cierta distancia del jugador
    switch (dir) {
       case ARRIBA: return m[fp-dist][cp];break;
       case ABAJO: return m[fp+dist][cp]; break;
       case IZQUIERDA: return m[fp][cp-dist]; break;
       case DERECHA: return m[fp][cp+dist];break;
    }
	return 0;
}

int metaCerca() { // checa si la meta esta a una posicion
    // checamos si la meta esta a una casilla del jugador y nos movemos ahi
       int lejos=1,aux=0,dir=-1;
       
       while (aux!=1 && aux!=3) {
           aux=infoC(ABAJO,lejos);
           if (aux==3) dir=ABAJO;
           lejos++;
       } lejos=1;aux=0;
       if (dir==-1) {
           while (aux!=1 && aux!=3) {
               aux=infoC(DERECHA,lejos);
               if (aux==3) dir=DERECHA;
               lejos++;
           } lejos=1;aux=0;
       }
       if (dir==-1) {
       while (aux!=1 && aux!=3) {
           aux=infoC(ARRIBA,lejos);
           if (aux==3) dir=ARRIBA;
           lejos++;
       } lejos=1;aux=0;
       }
       if (dir==-1) {
          while (aux!=1 && aux!=3) {
               aux=infoC(IZQUIERDA,lejos);
               if (aux==3) {dir=IZQUIERDA;}
               lejos++;
           } lejos=1;
       }
      return dir;  
}

void MuestraLaberinto() {
     // En esta funcion las paredes se muestran como bloques (caracter ascii 219), el jugador como "J" y la meta como "M"
    system("cls");
    for (int i=0;i<f;i++) {
        for (int ii=0;ii<c;ii++) {
           if (m[i][ii]==1) printf ("%c",char(219)); // Bloque
           else if (i==fs && ii==cs) printf ("M");
           else if (i==fp && ii==cp) printf ("J");
           else if (m[i][ii]==4) printf ("."); // Es por donde ya paso el jugador
           else printf (" ");
        }
    printf ("\n");
    }
}
int evitaParedesDer(int dir) {//  Cambia la direccion en la que avanza el jugador, metodo mano derecha
    switch (dir) {
    case ARRIBA: 
        if (infoC(DERECHA)==1 && infoC(ARRIBA)!=1) {}// Antes de avanzar checamos si hay pared a la derecha 
        else if (infoC(DERECHA)!=1) dir=DERECHA;// si no hay pared a la derecha giramos viendo a la derecha         
        else if (infoC(IZQUIERDA)!=1) dir=IZQUIERDA;// si no, si no hay pared en la izq. giramos viendo hacia alla   
        else dir=ABAJO;// ultima opcion, abajo giramos viendo hacia abajo           
    break;    
    case DERECHA:
        if (infoC(ABAJO)==1 && infoC(DERECHA)!=1) {}// Antes de avanzar hacia la derecha checamos si hay pared abajo      
        else if (infoC(ABAJO)!=1) dir=ABAJO;// si no hay pared abajo giramos a la derecha, mirando abajo
        else if (infoC(ARRIBA)!=1) dir=ARRIBA;// si no hay pared arriba giramos
        else dir=IZQUIERDA;// ultima opcion la izquierda     
    break;                
    case ABAJO:
        if (infoC(IZQUIERDA)==1 && infoC(ABAJO)!=1) {}// si no hay pared abajo y a la izq. si, avanzamos      
        else if (infoC(IZQUIERDA)!=1) dir=IZQUIERDA;// si no hay pared a la izquierda giramos
        else if (infoC(DERECHA)!=1) dir=DERECHA;// si no hay pared a la derecha giramos 
        else dir=ARRIBA; // ultima opcion arriba
    break;
     case IZQUIERDA:
        if (infoC(ARRIBA)==1 && infoC(IZQUIERDA)!=1) {}// si hay pared arriba y a la izq. no, avanzamos             
        else if (infoC(ARRIBA)!=1) dir=ARRIBA;// si no hay pared arriba giramos a la derecha,
        else if (infoC(ABAJO)!=1) dir=ABAJO;// si no hay pared abajo giramos 
        else dir=DERECHA;// ultima opcion volver atras, giramos 
    break;
    }
    return dir;           
}

int evitaParedesIzq(int dir) {//  Cambia la direccion en la que avanza el jugador, metodo mano izquierda
    switch (dir) {
    case ARRIBA: 
         if (infoC(IZQUIERDA)==1 && infoC(ARRIBA)!=1) {}
        else if (infoC(IZQUIERDA)!=1) dir=IZQUIERDA;
        else if (infoC(DERECHA)!=1) dir=DERECHA;
        else dir=ABAJO;           
    break;    
    case DERECHA:
         if (infoC(ARRIBA)==1 && infoC(DERECHA)!=1) {} 
        else if (infoC(ARRIBA)!=1) dir=ARRIBA;
        else if (infoC(ABAJO)!=1) dir=ABAJO;
        else dir=IZQUIERDA;
    break;                
    case ABAJO:
          if (infoC(DERECHA)==1 && infoC(ABAJO)!=1) {}
        else if (infoC(DERECHA)!=1) dir=DERECHA;
        else if (infoC(IZQUIERDA)!=1) dir=IZQUIERDA;
        else dir=ARRIBA;
    break;
     case IZQUIERDA:
            if (infoC(ABAJO)==1 && infoC(IZQUIERDA)!=1) {}// si hay pared arriba y a la izq. no, avanzamos             
        else if (infoC(ABAJO)!=1) dir=ABAJO;
        else if (infoC(ARRIBA)!=1) dir=ARRIBA;
        else dir=DERECHA;
    break;
    }
    return dir;           
}

void Rastro(int dir,int f,int c) {
     switch(dir){ // Si ya pasamos por ahi lo recordamos para el sigueinte ciclo
        case ARRIBA: if (infoC(ARRIBA)==4) ya=true;
        case DERECHA: if (infoC(DERECHA)==4) ya=true;           
        case IZQUIERDA: if (infoC(IZQUIERDA)==4) ya=true;
        case ABAJO: if (infoC(ABAJO)==4) ya=true;            
     }
     m[f][c]=4; // Marcamos para poner un punto (.) donde estaba el jugador para marcar el camino      
}
void mueveJugador(int dir) {
     switch(dir){ // Movemos al jugador
        case ARRIBA: m[fp-1][cp]=2; // actualizamos matriz            
            fp--; // Actualizamos coordenadas del jugador         
        break;            
        case DERECHA: m[fp][cp+1]=2; // actualizamos matriz            
             cp++; // Actualizamos coordenadas del jugador           
        break;            
        case IZQUIERDA: m[fp][cp-1]=2; // actualizamos matriz            
            cp--; // Actualizamos coordenadas del jugador           
        break; 
        case ABAJO: m[fp+1][cp]=2; // actualizamos matriz           
            fp++; // Actualizamos coordenadas del jugador           
        break;            
     }     
}    

int main() { 
    int old_fp,old_cp;  // Las usaremos para poner un espacio en donde estaba el jugador 
    int meta=-1; // poner 1 o 0 para izquierda o derecha
    int codAscii;
    char tcl;
               
    dimensionaMatriz();       
    
    while (tcl!=27) {
        pasosReales=0;
        leerArchivo(); // Leemos archivo de texto con la informacion del laberinto 
        metodo=2;
        movs=0; fp=ifp;cp=icp;// ifp e icp son los valores iniciales de las coordenadas del jugador no  cambian
                   // fp Y cp, si van cambiando en el transcurso del programa    
    
        while (fp!=fs || cp!=cs) {// Cuando encontramos la meta, salimos del ciclo
            old_fp=fp; old_cp=cp; // Guardamos las coordenadas del jugador, para colocar un espacio cuando se mueva
            
            if (pasoApaso && metodo!=2) {
             MuestraLaberinto();
             //printf("movimientos %d\n",movs); //debug 
             //printf("espacios %d\n",espacios*2-movs);  // debug
             printf("Movimientos %d. ",movs);
             system("pause"); // esperamos que el usuario presione una tecla                    
            }
            
            if (vision) meta=metaCerca();  // Simula que el jugador ve la meta a lo lejos. 
            if (meta!=-1) direccion=meta; // si la meta esta cerca  nos moveremos ahi  
            else  if (metodo==0) direccion=evitaParedesIzq(direccion);// Giramos si topamos con pared 
                else if (metodo==1)direccion=evitaParedesDer(direccion);
                else  {
                      printf("Calculando...");
                      backtracking(fp, cp);
                }
            
            if (metodo!=2) {
                mueveJugador(direccion);
                Rastro(direccion,old_fp, old_cp);
                movs++;
                if (espacios*2-movs<0) break;
            }
        }
        MuestraLaberinto();
        if (fp==fs && cp==cs) {
            if (metodo==0) printf ("%d movimientos con el metodo de la mano izquierda.\n", movs); // para debug
            else if (metodo==1)printf ("%d movimientos con el metodo de la mano derecha.\n", movs);
            else printf ("%d movimientos con el metodo de Backtracking.\n", movs);
        }
        else if (metodo!=2) printf ("El laberinto no tiene solucion."); // Se muesstra cuando cierta cantidad de movimientos 
                                                               //transcurren, no es el metodo optimo.
        printf("Quieres probar otro metodo? <esc> para no, cualquier tecla para si.");
        tcl = getch();
    }
    return 0;
}
