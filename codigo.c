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
#define ListaSize 10

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



int findLinealSearch(int element){

}

int findBinarySearch(int element){

}


int main() {

	srand(time(NULL));
	
	// ----------- PROBLEM 1 ----------------------
	int lista[ListaSize];
	for(int i = 0; i<ListaSize; i++){
		lista[i] = rand()%1000; // max number wont be > than 1000
	}

	RadixSort(lista);
	// --------------------------------------------


    return 0;
}