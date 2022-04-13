#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void printArray(int *a, int n, char *lbl) {
    int i;
    printf("%s => ", lbl);
    for (i = 0; i < n; i++)
        printf("%d, ", a[i]);
    printf("\n");
}

void f1() {
	int i, j, n = 8, c = 5;
	int *a = (int*)calloc(n, sizeof(int));

	a[0] = c;
	
	for (i = 1; i <= log2(n); i++) {
		#pragma omp for
		for (j = (int)pow(2,i)-1; j <= (int)pow(2,i+1)-1; j++) {
			a[j] = a[j/2];
		}
	}

	printArray(a, n, "a");
}

void f2() {
	int i, n = 8, m = 0;
	int *a = (int*)calloc(n, sizeof(int));

	i = (int)rand() % n;
	
	a[i] = rand() % 2;
	printf("Valor sorteado: {%d}, no i {%d}\n", a[i], i);
	
	#pragma omp for
	for (i = 0; i < n; i++) {
		m |= a[i];
	}

	printf("M = {%d}\n", m);
}

void f3() {
	int i, j, n = 1000000, p = 4, m = 0, chunkSize;
	int *a = (int*)calloc(n, sizeof(int));

	i = (int)rand() % n;
	
	a[i] = rand() % 2;
	printf("Valor sorteado: {%d}, no i {%d}\n", a[i], i);

	chunkSize = n/p;
	
	#pragma omp for
	for(i = 1; i < p - 1; i++) {
		for(j = chunkSize; j < (i-1) * chunkSize + 1; j++){
			m |= a[j];	
		}
	}

	printf("M = {%d}\n", m);
}

// AULA 6
				
// Num vetor a, achar n onde n eh o numero de elementos menor que c em CREW
// igor
void f4() {
	int i, j, n = 8, c = 5;
	int a[] = {5,4,3,7,8,2,9,6};
	int *f = calloc(8, sizeof(int));

	#pragma omp for
	for (i = 0; i < n; i++)
		f[i] = a[i] < c;

	for (i = log2(n); i > 0; i--) {
		#pragma omp for
		for (j = 0; j < (int) pow(2, i-1); j++){
			printf("i {%d}, j {%d}, j1 {%d}, j2{%d}\n", i, j, 2*j, 2*j + ((int) log2(n)) + 1 - i);
			f[j] = f[2*j] + f[2*j + (int) log2(n) + 1 - i];
		}
	}
	printArray(f, n, "F");
}

//takuno
void f5() {
	int i, j, n = 8, c = 5;
	int a[] = {5,4,3,7,8,2,9,6};
	int *f = calloc(8, sizeof(int));

	#pragma omp for
	for (i = 0; i < n; i++)
		f[i] = a[i] < c;

	for (i = 1; i <= (int)log2(n); i++) {
		#pragma omp for
		for (j = 1; j <= n/(int)(pow(2, i)); j++) {
			int x, y;
			x = (int)pow(2,i) + (j-1)*(int)pow(2,i);
			y = (int)pow(2,i) + (j-1)*(int)pow(2,i) - (int)pow(2,i-1);
			f[x] = f[x] + f[y]; 
		}
	}
	printArray(f, n, "F");
}

// EREW
void f6(){
	int i, j, n = 8, c = 5;
	int a[] = {5,4,3,7,8,2,9,6};
	int *f = calloc(8, sizeof(int));
	int *cl = calloc(8, sizeof(int));
	
	cl[0] = c;
	
	for (i = 0; i <= log2(n); i++)
		#pragma omp for
		for (j = 0; j <= i; j++) {
			cl[j + i] = cl[j];	
		}

	printArray(cl, 8, "cl");
}

int main(void) {
	srand((unsigned) time(NULL));
	f6();
	
    return 0;
}