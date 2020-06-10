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
	int i = 0;
	for( i<ListaSize; i++;){
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
	int i = 0;

	for( i<ListaSize; i++;){
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
	int i = 0; 
	
	for(i<ListaSize; i++;){
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
	int j=0;
	for( j<digits; j++; ){		
		int i=0;
		for( i<ListaSize; i++;){
			findMin(lista, &min, &minPos,j, digits);
			
			temp[i] = min;
			lista[minPos] = pow(10,digits)-1;
		}
		printf("Iteracion: %i, ", j+1);
		printList(temp);
		int k = 0;
		for( k<ListaSize; k++;){
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
	int i=0;

	for( i<ListaSize; i++;){
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

//ejercicio 4

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
//ejercicio 5
Nodo *middle(Nodo *inicio, Nodo *final) 
{ 
	if (inicio == NULL) 
		return NULL; 

	Nodo *Aux1 = inicio; 
	Nodo *Aux2 = inicio->siguiente; 

	while (Aux2 != final) 
	{ 
		Aux2 = Aux2->siguiente; 
		if (Aux2 != final) 
		{ 
			Aux1 = Aux1->siguiente; 
			Aux2 = Aux2->siguiente; 
		} 
	} 

	return Aux1; 
} 

// Funcion q implementa La busqueda binaria 

int findbinarySearch(Lista *L, int value) 
{ 
	Nodo *inicio= L->inicio;
	Nodo *final = NULL;

	do
	{ 
		// encuenta el medio
		Nodo *mid = middle(inicio,final); 

		//  sie el medio es NUlL 
		if (mid == NULL) 
			return -1; 

		//  si el  valor esta en el medio 
		if (mid->dato == value) 
			return mid->dato; 

		// si el valor es mayor q la mitad
		else if (mid->dato < value) 
			inicio = mid->siguiente; 

		// si el valor es menor q la mitad
		else
			final = mid; 

	} while (final == NULL || 
			final != inicio); 

	// value  se noi se encuntra 
	return -1; 
} 

void timeTest(){
	unsigned t0, t1;

	Lista *L;
	L = listaNueva();
	int result;
	int i = 0;
	for( i<ListaSize; i++;){
		insertarDato(L, rand()%500);
	}
	int random = rand()%500;
	t0 = clock();
	result = findLinealSearch(L,random);
	t1 = clock();
	double time = ((double)(t1-t0)/CLOCKS_PER_SEC);
	
	printf("Number to find: %d, result: %d.\n", random, result );
	printf("Time: %f.\n",time );
}
void timeTest2(){
	unsigned t0, t1;

	Lista *L;
	L = listaNueva();
	int result;
	int i = 0;
	for( i<ListaSize; i++;){
		insertarDato(L, rand()%500);
	}
	int random = rand()%500;
	Lista *M=listaNueva();
	M=sortList(L);
	t0 = clock();
	printf("Number to find: %i, result: %d.\n", random,findbinarySearch(M,random));
	t1 = clock();
	double time = ((double)(t1-t0)/CLOCKS_PER_SEC);
	printf("Time: %f.\n",time );
}

int main() {
	 timeTest();
	 timeTest2();
	 


	srand(time(NULL));
	
	// ----------- PROBLEM 1 ----------------------
	int lista[ListaSize];
	int i = 0;
	for( i<ListaSize; i++;){
		//lista[i] = rand()%1000; // max number wont be > than 1000
	}

	RadixSort(lista);
	


	// ----------- PROBLEM 2 ----------------------
	 //Lista *L;
	//L = listaNueva();
	//int p= 0;
	//for(p<ListaSize; p++;){
	//	insertarDato(L, rand()%500);
	//}

	//mostrarLista(L);

	 //int random = rand()%500;
	// printf("Number to find: %i, result: %i.\n", random, findLinealSearch(L,random) );
	

	// ----------- PROBLEM 3 ----------------------();
	
	
	
}
