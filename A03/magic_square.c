//---------------------------------------------------------------------
// magic_square.c 
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name:
//
#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int *array = malloc(sizeof(int)*m*n);
    if (!array) {
        printf("Malloc failed.\n");
        exit(1);
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d ", &array[i*n+j]);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", array[i*n+j]);
        printf("\n");
    }

    int num = 0;
    int magic = 1;
    for (int k = 0; k < m; k++) {
        num += array[k];
    }

    // row
    int test = 0;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++)
            test += array[i*n+j];
        if (test != num) {
            magic = -1;
            break;
        }
        test = 0;
    }

    // column
    test = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            test += array[j*n+i];
        if (test != num) {
            magic = -1;
            break;
        }
        test = 0;
    }

    //diaganol
    test = 0;
    for (int i = 0; i < m; i++) {
        test += array[i*n+i];
    }
    if (test != num) 
        magic = -1;
    test = 0;
    for (int i = 0; i < m; i++) {
        test += array[(m-1-i)*n+i];
    }
    if (test != num) 
        magic = -1;
    test = 0;

    if (magic == -1) {
        printf("M is NOT a magic square!\n");
    } else 
        printf("M is a magic square (magic constant = %d)\n", num);

    free(array);
    array = NULL;
    return 0;
}

