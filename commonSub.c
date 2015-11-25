/***************************************************************
  Name: Paul Lewis
  File Name: commonSub.c

  A program to find a longest common subsequence between strings.
  First by identifying and printing one or more LCSs between two strings.
  Second by finding measures of similarity between a number of strings.
***************************************************************/

#include "commonSub.h"

int main(void) {
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    int n;
    int *p;
    printf("\nPart 1:\n");
    getTwoStrings(str1, str2);
    getLCS(str1,str2);
    printf("\nPart 2:\n");
    p = computeLengths(&n);
    getSimilarity(n,p);

    return 0;
}
/*
 *  Function to parse two strings from file
 *
 *  @param char *str1, reference to first string
 *  @param char *str2, reference to second string
 * 
 *  @local char line[BUFFER_SIZE], the buffer to hold from fgets
 *  @local FILE *fp, the file pointer
 *  @local int m, length of string 1
 *  @local int n, length of string 2
 */
void getTwoStrings(char *str1, char *str2) {
    char line[BUFFER_SIZE];
    FILE *fp;
    int m, n;
    /* open twoStrings.txt */
    fp = fopen("twoStrings.txt", "r");
    if(fp == NULL) {
        perror("Error opening items.txt\n");
        exit(1);
    }
    /* get strings */
    fgets(line,sizeof(line),fp);
    strcpy(str1,line);
    bzero(line,sizeof(line));
    fgets(line,sizeof(line),fp);
    strcpy(str2,line);
    m = strlen(str1);
    n = strlen(str2);
    /* set null terminators */
    str1[m-1] = '\0';
    str2[n-1] = '\0';

}
/*
 *  A function to find the longest commone subsequence between 2 strings
 *
 *  @param const char *s1, the first string to compare
 *  @param const char *s2, the second string to compare
 *
 *  @local int i, j, k, l; counters
 *  @local int max, the length of the longest subsequence
 *  @local fm, row of first LCS
 *  @local char **temp, array to hold all LCS's
 *  @local struct stack *st, the stack to hold characters
 *  @local char **temp, array of strings to hold all LCS
 *  @local int **array, the C array for DP LCS algorithm
 */
void getLCS(const char *s1, const char *s2) {
    int i, j, k, l, m, n;
    int max = 0, fm = 0;
    m = strlen(s1);
    n = strlen(s2);
    /* allocate stack */
    struct stack *st = newStack();
    /* allocate array to contain each LCS string */ 
    char **temp = malloc(sizeof(char *) * m);
    if(temp == NULL) {
        perror("Error allocating temp\n");
        exit(1);
    }
    /* create C array from DP LCS algorithm */
    int **array = LCSLength(s1,s2, &max, &fm);
    k=0;
    /* traverse through C array and find each LCS */
    for(i=fm;i<=m;i++) {
        for(j=1;j<=n;j++) {
            if(s1[i-1] == s2[j-1] && array[i][j] == max) {
                trav(s1,s2,i,j,array,st);
                temp[k] = malloc(sizeof(char) * m);
                if(temp[k] == NULL) {
                    perror("Error allocating temp\n");
                    exit(1);
                }
                l=0;
                while(!isEmptyStack(st)) {      // record an LCS
                    temp[k][l] = popStack(st);
                    l++;
                }
                temp[l] = '\0';
                k++;    
            }
        }
    }
    /* print both strings and all LCS's */
    printPart1(s1,s2,temp,k);
    /* free everything */
    freeEverything(temp,array,m,k);
    freeStack(st);
}
/*
 *  A function to traverse through C array to find an LCS
 *
 *  @param const char *s1, the first string to compare
 *  @param const char *s2, the second string to compare
 *  @param int m, the length of first string
 *  @param int n, the length of second string
 *  @param int **array, the C arrat from DP algorithm
 *  @param struct stack *st, the stack to hold characters in LCS
 */
void trav(const char *s1, const char *s2, int m, int n, int **array, struct stack *st) {
    if(array[m][n] == 0)
        return;
    if(s1[m-1] == s2[n-1]) {
        pushStack(st,s1[m-1]); 
        trav(s1,s2,m-1,n-1,array,st); 
    } else {
        if(array[m-1][n] >= array[m][n-1])
            trav(s1,s2,m-1,n,array,st);
        else
            trav(s1,s2,m,n-1,array,st);
    }
}
/*
 *  A Dynamic Programming algorithm to find all common subsequences between two strings
 *  Does not use "b" array
 *
 *  @param const char *s1, the first string to compare
 *  @param const char *s2, the first string to compare
 *  @param int *max, reference to the length of the current LCS
 *  @param int *fm, reference to the array index which holds the first instance of a LCS (row)
 *
 *  @local int i, j; counters
 *  @local int m, length of first string
 *  @local int n, length of second string
 *  @local int **array, the C array
 *
 *  @return int **, reference to C array
 */
int **LCSLength(const char *s1,const char *s2, int *max, int *fm) {
    int i, j, m, n;
    int **array;
    m = strlen(s1);
    n = strlen(s2);
    array = malloc(sizeof(int *) * (m+1));
    if(array == NULL) {
        perror("Error allocating c array\n");
        exit(1);
    }
    for(i=0;i<=m;i++) { 
        array[i] = malloc(sizeof(int) * (n+1));
        if(array[i] == NULL) {
            perror("Error allocating array[i]\n");
            exit(1);
        }
    }
    for(i=1;i<=m;i++) 
        array[i][0] = 0;
    for(j=0;j<=n;j++) 
        array[0][j] = 0;
    for(i=1;i<=m;i++) {
        for(j=1;j<=n;j++) {
            if(s1[i-1] == s2[j-1]) {
                array[i][j] = array[i-1][j-1] + 1;
                if(array[i][j] > *max)      // record row containing first instance of an LCS
                    *fm = i;
                if(array[i][j] >= *max)     // record the length of largest LCS
                    *max = array[i][j];
            } else {
                if(array[i-1][j] >= array[i][j-1]) 
                    array[i][j] = array[i-1][j];
                else 
                    array[i][j] = array[i][j-1];
            }
        }
    }
    return array;
}
/*
 *  A function to free all data structures for part 1
 *
 *  @param char **temp, array of LCS strings to free
 *  @param int **array, C array to free
 *  @param int m, number of rows in C array
 *  @param int k, number of LCS strings to free
 *
 *  @local int i, counter
 */
void freeEverything(char **temp, int **array, int m, int k) {
    int i;
    for(i=0;i<k;i++) 
        free(temp[i]);
    free(temp);
    for(i=0;i<=m;i++)
        free(array[i]);
    free(array);
}
/*
 *  A function to print relevant information for part 1
 *
 *  @param const char *s1, the first string
 *  @param const char *s2, the second string
 *  @param char **temp, the array containing the LCS strings to print
 *  @param int k, number of LCS strings to print
 *
 *  @local int i, counter
 */
void printPart1(const char *s1, const char *s2, char **temp, int k) {
    int i;
    printf("\nString 1: %s\n", s1);
    printf("String 2: %s\n", s2);
    for(i=0;i<k;i++) 
        printf("LCS %d: %s\n", i+1, temp[i]);    
    printf("\n");
}
/*
 *  Function to find file positions for each string
 *
 *  @param int *n, the number of strings
 *
 *  @local char line[BUFFER_SIZE], temporary buffer for strings
 *  @local int num, the number of strings
 *  @local int i, counter
 *  @local int *positions, the array of positions for strings
 *
 *  @return int *, the array of positons for strings
 */
int *computeLengths(int *n) {

    char line[BUFFER_SIZE];
    int num, i;
    FILE *fp;
    fp = fopen("multipleStrings.txt","r");
    fgets(line,BUFFER_SIZE,fp);     // get number of strings
    num = atoi(line);       
    *n = num;
    int *positions = malloc(sizeof(int) * (num+1));
    if(positions == NULL) {
        perror("Error allocating positions array\n");
        exit(1);
    } 
    positions[0] = strlen(line);
    for(i=1;i<=num;i++) {           // record positions
        fgets(line, BUFFER_SIZE, fp);        
        positions[i] = strlen(line);
    }
    fclose(fp);
    return positions;
}
/*
 *  Function to compute levels of similarity between a number of strings
 *
 *  @param int n, the number of strings
 *  @param int *p, array of positions of strings for direct access
 *
 *  @local char line1[BUFFER_SIZE], temporary buffer for string
 *  @local char line2[BUFFER_SIZE], temporary buffer for string
 *  @local int i, j; counters
 *  @local int num, number of strings
 *  @local int x, length of first string
 *  @local int y, length of second string
 *  @local int z, length of LCS between first and second string
 *  @local int curP, current position for direct access
 *  @local char **array, the array to hold the character values for levels of similarity between strings
 *  @local FILE *fp, file pointer for direct access file
 */
void getSimilarity(int n, int *p) {
    char line1[BUFFER_SIZE];
    char line2[BUFFER_SIZE];      
    FILE *fp;
    int i, j, num, x, y, z, curP = p[0];
    num = n;   
    char **array = malloc(sizeof(char *) * num);    
    if(array == NULL) {
        perror("Error allocating similarity array\n");
        exit(1);
    }
    for(i=0;i<num;i++) {
        array[i] = malloc(sizeof(char) * num);
        if(array[i] == NULL) {
            perror("Error allocating similarity array row\n");
            exit(1);
        } 
        for(j=0;j<num;j++) 
            array[i][j] = '\0';
    }
    fp = fopen("multipleStrings.txt", "r");    
    fseek(fp, curP, SEEK_SET);
    for(i = 0; i < num; i++) {
        fgets(line1, BUFFER_SIZE, fp);
        line1[strlen(line1) - 1] = '\0';    // get main string
        x = strlen(line1);        
        for(j = i+1; j < num; j++) {	    // go through each subsequent string and compare to mains string
            fgets(line2, BUFFER_SIZE, fp);
            line2[strlen(line2) - 1] = '\0';
            y = strlen(line2);
            z = LCSLength2(line1,line2);
            array[i][j] = findSim(x,y,z);           
         }
        curP += p[i];
        fseek(fp, curP, SEEK_SET);
    }   
    /* print and free everything */
    printAndFree(array,num);
    free(p);
}
/* 
 *  Print the output table and free it
 *
 *  @param char **array, the output table
 *  @param int num, number of strings
 *
 *  @local int i, j; counters
 */
void printAndFree(char **array, int num) {
    int i, j;
    printf("\n  ");
    for(i=0;i<num;i++) {
        printf("%d ", i+1);
    }
    printf("\n");
    for(i=0;i<num;i++) {
        printf("%d ", i+1);
        for(j=0;j<num;j++) {
            if(array[i][j] == '\0')
                printf("%c ", '-');
            else
                printf("%c ", array[i][j]); 
        }
        printf("\n");
    }
    for(i=0;i<num;i++) 
        free(array[i]);
    free(array);
}
/*
 *  Function to compute level of similarity between two strings
 *  and return an appropriate symbol
 *
 *  @param int x, length of first string
 *  @param int y, length of second string
 *  @param int z, length of LCS
 *
 *  @local float percLeng, variable to hold percentage of length between short string and long string
 *  @local float percLCS, variabel to hold percentage of length between short string and LCS
 *  @local float s, length of short string as float
 *  @local float l, length of long string as float
 *
 *  @return char, the character representing the level of similarity
 */
char findSim(int x, int y, int z) {
    float percLeng, percLCS, s, l;
    if(x > y) {
        l = (float)x;
        s = (float)y;
    } else {
        l = (float)y;
        s = (float)x;
    }
    percLeng = s/l;
    percLCS = (float)z/s;
    if(percLeng >= 0.9 && percLCS >= 0.8)
        return 'H';
    else if(percLeng >= 0.8 && percLCS >= 0.6)
        return 'M';
    else if(percLeng >= 0.6 && percLCS >= 0.5)
        return 'L';
    else
        return 'D';
}
/*
 *  Function to find length of LCS between two strings using 2*n array
 *
 *  @param const char *s1, the first string
 *  @param const char *s2, the second string
 *
 *  @local int i, j; counters
 *  @local int m, length of first string
 *  @local int n, length of second string
 *  @local int k, the length of LCS
 *  @local int **array, the 2*n array 
 *
 *  @return int, the length of the LCS
 */
int LCSLength2(const char *s1,const char *s2) {
    int i, j, m, n, k;
    int **array;
    m = strlen(s1);
    n = strlen(s2);
    array = malloc(sizeof(int *) * ROWS);
    if(array == NULL) {
        perror("Error allocating c array\n");
        exit(1);
    }
    for(i=0;i<=ROWS;i++) { 
        array[i] = malloc(sizeof(int) * (n+1));
        if(array[i] == NULL) {
            perror("Error allocating array[i]\n");
            exit(1);
        }
    } 
    array[0][1] = 0;
    for(j=0;j<=n;j++) 
        array[0][j] = 0;
    for(i=1;i<=m;i++) {
        for(j=1;j<=n;j++) {
            if(s1[i-1] == s2[j-1]) {
                array[1][j] = array[0][j-1] + 1;
            } else {
                if(array[0][j] >= array[1][j-1]) 
                    array[1][j] = array[0][j];
                else 
                    array[1][j] = array[1][j-1];
            }
        }
        for(j=1;j<=n;j++) {     // move items in row 1 to row 0
            array[0][j] = array[1][j];
        }
    }
    k = array[1][n];
    /* free 2*n array */
    for(i=0;i<ROWS;i++) 
        free(array[i]);
    free(array);
    return k;
}
