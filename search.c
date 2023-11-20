#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int linear_search(int [], int, int); // prototyping

int main()
{

    int A[100], i, n, loc, d;
    printf("\nEnter the size of the list: ");
    scanf("%d", &n); // n -> size of list
    if(n > 100){
        printf("\nSize should be less than or equal to 100");
        exit(0);
    }
    printf("\nEnter elements of the array: \n");
    for(i = 0;i < n; i++)
    {
        printf("Enter A[%d]: ", i);
        scanf("%d", &A[i]); // A -> array
    }
    printf("\nEnter data that need to searched: ");
    scanf("%d", &d); // d -> data
    loc = linear_search(A, n, d); //  location =  Array, size, data
    if(loc == -1)
        printf("\n\nThe data %d is not present in the array\n\n", d);
    else
        printf("\n\nthe data %d is present at position %d of the array\n\n", d, loc);

    getch();
    return 0;
}

int linear_search(int A[], int n, int d){

    int i;

    for(i = 0;i < n;i++)
        if(A[i] == d)
            return i;
    return -1;
}
