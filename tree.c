/*********************************
Insitituto Tecnologico de Costa Rica
Compiladores e Interpretes
Alexis Boza 
Silvia Delgado
2013
**********************************/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
/****************************
Arbol de parsing formado por
un arbol n-ario
-siguiente: Nodo en el mismo nivel
-hijos : Nodos hijos
*****************************/
struct Tnodo { 
   char *nombre; 
   struct Tnodo *siguiente; 
   struct Tnodo *hijos; 
} *root = NULL;

struct Tnodo *auxi;//Nodo auxiliar
int i;

char* ultimo_tag;//almacena el ultimo tag al que se le inserto un nodo

/**************************************
liberar_arbol:
Destruye el arbol de paring y libera
la memoria que fue reservada para
su uso.
***************************************/
void liberar_arbol (struct Tnodo *nodo) 
{ 
   while (nodo != NULL) { 
      struct Tnodo *n = nodo; 
      liberar_arbol (n->hijos); 
      nodo = nodo->siguiente; 
      free (n->nombre); 
      free (n); 
   } 
} 
/**************************************
DameBuffer:
Reserva memoria para la estructura
que estamos formando (malloc).
***************************************/
void *DameBuffer (size_t n) 
{ 
   char *p = (char *)malloc (n); 
   if (p == NULL) { 
      liberar_arbol (root); 
      fprintf (stderr, "\nMEMORIA INSUFICIENTE\n"); 
      exit (EXIT_FAILURE); 
   } 
   return (void *)p; 
} 
/**************************************
crear_nodo:
Toma un string (*char) y crea un nodo
de arbol.
***************************************/
struct Tnodo *crear_nodo (char *nombre) 
{ 
   struct Tnodo *nodo = (struct Tnodo *)DameBuffer (sizeof (struct Tnodo)); 
   nodo->nombre = (char *)DameBuffer (strlen(nombre) + 1); 
   strcpy (nodo->nombre, nombre); 
   nodo->hijos = nodo->siguiente = NULL; 
   return nodo; 
} 
/**************************************
Agrega_nodo:
Ingresa un nodo al arbol de parsing
tomando como referencia un nodo padre.
***************************************/
void Agrega_nodo (struct Tnodo **raiz, char *nombre) 
{ 
   struct Tnodo *nodo = crear_nodo (nombre); 
   if (raiz == &root) { 
      if (root == NULL) 
         root = nodo; 
      else { 
         struct Tnodo *ap;
         if (root->hijos == NULL){
                 root->hijos=nodo;
         }
         else{
         for (ap = root; ap->siguiente != NULL; ap = ap->siguiente) 
            ; 
         ap->siguiente = nodo; 
      } }
   } else {
     if(strcmp((*raiz)->nombre,nodo->nombre)==0){
           if ((*raiz)->siguiente == NULL) { 
          (*raiz)->siguiente = nodo; 
      } 
      else { 
      struct Tnodo *ap; 
      for (ap = (*raiz)->siguiente; ap->siguiente != NULL; ap = ap->siguiente) 
         ; 
      ap->siguiente = nodo; 
   }
      }
      else{
       if ((*raiz)->hijos == NULL) { 
          (*raiz)->hijos = nodo; 
      } 
      else { 
      struct Tnodo *ap; 
      for (ap = (*raiz)->hijos; ap->siguiente != NULL; ap = ap->siguiente) 
         ; 
      ap->siguiente = nodo; 
   }} }
    
} 
/**************************************
imprimir_arbol:
Imprime en consola la estructura completa
de un arbol.
***************************************/
void imprimir_arbol(struct Tnodo *nodo) 
{ 
   static int deep = 0; 
   static int nspaces = 1; 
   int i, j; 
   while (nodo != NULL) { 
      for (i = 0; i < deep; i++) 
         for (j = 0; j < nspaces; j++) 
            printf ("-"); 
      printf ("%s\n", nodo->nombre); 
      deep++; 
      imprimir_arbol (nodo->hijos); 
      deep--; 
      nodo = nodo->siguiente; 
   } 
} 
/**************************************
busca:
Busca en el arbol un nodo en
especifico y devuelve su referencia.
***************************************/
void busca(struct Tnodo *raiz, char* nombre){
    struct Tnodo* aux2;
    aux2=raiz;
    char* aux_c;
    int i;
    
    while (aux2!= NULL) { 
        if(strcmp(aux2->nombre,nombre)==0){
             auxi=aux2;
             busca(aux2->hijos,nombre); 
             aux2 = aux2->siguiente;
        }
        else{ 
            busca(aux2->hijos,nombre); 
            aux2 = aux2->siguiente; 
        }
       }
    
}
/**************************************
insertar_nodo:
Inserta un nodo en el arbol de parsing.
***************************************/
void insertar_nodo(char* padre , char* nombre){
    struct Tnodo *aux; 
    auxi=NULL; 
    
    //aux=busca(root,padre,NULL);
    busca(root,padre);
    aux=auxi;
    if(aux!=NULL){
     Agrega_nodo(&aux,nombre);
    }
    else {printf("No se pudo insertar %s \n ",nombre);
     }
}
