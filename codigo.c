/**
 * Made by Emilly Sancho Murillo and Daniel Bogarin * 
 * for TI4202 Algoritmos y estructuras de datos.
 * Teacher: Maria Jose Artavia.
 * IS 2020 - Homework 3 - 06/06/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <math.h> 


#define ListaSize 50


//---------------	 PROBLEM 1

/**
 * @brief      Prints a list.
 *
 * @param      int lista[]
 */
void printList(int lista[]){
	printf("Lista: ");
	for(int i = 0; i<ListaSize; i++){
		printf("%i ", lista[i] );
	}
	printf("\n");
}

/**
 * @brief      Finds maximum digits.
 *
 * @param      int lista[]
 *
 * @return     returns the digits amount of the higher number in the array
 */
int findMaxDigits(int lista[]){
	int max = lista[0];

	for(int i = 0; i<ListaSize; i++){
		if(lista[i]>max){
			max = lista[i];

		}
	}
	return (int)log10(max)+1 ;

}


/**
 * @brief      Finds a minimum.
 *
 * @param      int lista[] 
 * @param      int min 
 * @param      int pos     
 * @param  	   int pot     
 * @param      int digits
 * It looks for the minimun value on the list depending on the 
 * power it's working with
 */
void findMin(int lista[], int *min, int *pos,int pot,int digits){
	int m, mm, p = 0;
	
	m = lista[0]%(int)(pow(10,pot+1));
	mm = lista[0];

	
	for(int i = 0; i<ListaSize; i++){
		if(lista[i] != pow(10,digits)-1 && m == 9){
			mm = lista[i];
			m = lista[i]%(int)(pow(10,pot+1));
			p = i;
		}
		if((lista[i]%(int)(pow(10,pot+1))) < m ){
			mm = lista[i];
			m = (lista[i]%(int)(pow(10,pot+1)));
			p = i;
			
		}
	}

	*min = mm;
	*pos = p;
}

/**
 * @brief      RadixSort
 *
 * @param      int lista[]
 * It takes a list of integers and sort it on ascendent way
 */
void RadixSort(int lista[]){
	printf("ORIGINAL  ");
	printList(lista);
	int digits = findMaxDigits(lista);
	int temp[ListaSize];
	int min = 0, minPos = 0;
	
	for(int j=0; j<digits; j++ ){		
		
		for(int i=0; i<ListaSize; i++){
			findMin(lista, &min, &minPos,j, digits);
			
			temp[i] = min;
			lista[minPos] = pow(10,digits)-1;
		}
		printf("Iteracion: %i, ", j+1);
		printList(temp);

		for(int k = 0; k<ListaSize; k++){
			lista[k] = temp[k];
		}
	}	
	printf("\nFINAL  ");
	printList(temp);


}

//---------------	 PROBLEM 2 

typedef struct Lista Lista;
typedef struct Nodo Nodo;

struct Nodo
{
	int dato;
	Nodo *siguiente;
};

struct Lista
{
	Nodo *inicio;
};

Lista *listaNueva(void)
{
	Lista *L;
	L = (Lista *) malloc(sizeof(Lista));
	L->inicio = NULL;
	return L;
}
void insertarDato(Lista *L, int dato)
{
	Nodo *n, *aux;
	
	if(L->inicio == NULL) //Valida si la lista está vacía
	{
		//Inserta al inicio de la lista
		L->inicio = (Nodo *) malloc(sizeof(Nodo));
		L->inicio->dato = dato;
		L->inicio->siguiente = NULL;
		return;
	}
	n = L->inicio;
	
	while(n!= NULL)
	{
		aux = n;
		n = n->siguiente;		
	}
	aux->siguiente = (Nodo *) malloc(sizeof(Nodo));
	aux->siguiente->siguiente = NULL;
	aux->siguiente->dato = dato;

	
}

void eliminarDato(Lista *L, int dato)
{
	Nodo *aux = L->inicio, *anterior = NULL;
	
	//Valida si la lista esta vacia
	if(L->inicio == NULL)
	{
		printf("La lista está vacía...\n");		
	}
	else
	{
		//Si el nodo a eliminar esta al inicio de la lista
		if(L->inicio->dato == dato)
		{
			aux = L->inicio;
			L->inicio = L->inicio->siguiente;				
		}
		else
		{
			while(aux!= NULL)
			{
				if(aux->dato == dato) //Nodo a eliminar es el último nodo de la lista
				{
					anterior->siguiente = aux->siguiente;
					break;					
				}
				else
				{
					anterior = aux;
					aux = aux->siguiente;				
				}
			}
		}
		if(aux != NULL)
		{
			//printf("El dato eliminado es %d \n", aux->dato);
			free(aux);
		}
	}
}


void mostrarLista(const Lista *L)
{
	Nodo *i;
	printf("La lista es: \n");
	for(i = L->inicio; i!= NULL; i = i->siguiente)
		printf("%d ", i->dato);
	printf("\n");
}

void liberarLista(Lista *L)
{
	Nodo *n, *aux;
	if(L->inicio == NULL)
		return;
	if(L->inicio->siguiente == NULL)
		return;		
	n = L->inicio;
	
	while(n != NULL)
	{
		aux = n;
		n = n->siguiente;
		free(aux);
	}
	
}

Lista* sortList(Lista *L){
	
	Lista *M;
	M = listaNueva();
	Nodo *aux = L->inicio;
	int min;


	for(int i=0; i<ListaSize; i++){
		aux = L->inicio;
		min = aux->dato;
		while(aux!=NULL){
			if(min>aux->dato){
				min = aux->dato;
			}
			aux = aux->siguiente;
		}

		eliminarDato(L, min);
		insertarDato(M, min);
	}

	mostrarLista(M);
	liberarLista(L);

}



int findLinealSearch(Lista *L, int element){
	Nodo *nAux = L->inicio;
	
	while(nAux != NULL)
	{
		if(nAux->dato == element)
			return 0;
		nAux = nAux->siguiente;		
	}
	return -1;

}

int findBinarySearch(int element){

}

void timeTest(){
	unsigned t0, t1;

	Lista *L;
	L = listaNueva();
	int result;

	for(int i = 0; i<ListaSize; i++){
		insertarDato(L, rand()%500);
	}
	int random = rand()%500;

	t0 = clock();
	result = findLinealSearch(L,random);
	t1 = clock();
	double time = ((double)(t1-t0)/CLOCKS_PER_SEC);
	
	printf("Number to find: %i, result: %i.\n", random, result );
	printf("Time: %f.\n",time );
}

int main() {

	srand(time(NULL));
	
	// ----------- PROBLEM 1 ----------------------
	int lista[ListaSize];
	for(int i = 0; i<ListaSize; i++){
		lista[i] = rand()%1000; // max number wont be > than 1000
	}

	//RadixSort(lista);
	


	// ----------- PROBLEM 2 ----------------------
	// Lista *L;
	// L = listaNueva();

	// for(int i = 0; i<ListaSize; i++){
	// 	insertarDato(L, rand()%500);
	// }

	// mostrarLista(L);

	// int random = rand()%500;
	// printf("Number to find: %i, result: %i.\n", random, findLinealSearch(L,random) );
	
	timeTest();
	// ----------- PROBLEM 3 ----------------------

    return 0;
}