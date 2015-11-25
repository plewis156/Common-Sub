/***************************************************************
  Student Name: Paul Lewis
  File Name: commonSub.h

  Contains #includes, #defines, and function prototypes for prog5.c
***************************************************************/

#ifndef _COMMONSUB_H
#define _COMMONSUB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stack.h"

#define BUFFER_SIZE 50002
#define SIZE 100
#define ROWS 2

/*
 *  Function to parse two strings from file
 *
 *  @param char *str1, reference to first string
 *  @param char *str2, reference to second string
 */
void getTwoStrings(char *str1, char *str2);
/*
 *  A Dynamic Programming algorithm to find all common subsequences between two strings
 *  Does not use "b" array
 *
 *  @param const char *s1, the first string to compare
 *  @param const char *s2, the first string to compare
 *  @param int *max, reference to the length of the current LCS
 *  @param int *fm, reference to the array index which holds the first instance of a LCS
 *
 *  @return int **, reference to C array
 */
int **LCSLength(const char *s1, const char *s2, int *max, int *fm);
/*
 *  A function to find the longest commone subsequence between 2 strings
 *
 *  @param const char *s1, the first string to compare
 *  @param const char *s2, the second string to compare
 */
void getLCS(const char *s1, const char *s2);
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
void trav(const char *s1, const char *s2, int m, int n, int **array, struct stack *st);
/*
 *  A function to free all data structures for part 1
 *
 *  @param char **temp, array of LCS strings to free
 *  @param int **array, C array to free
 *  @param int m, number of rows in C array
 *  @param int k, number of LCS strings to free
 */
void freeEverything(char **temp, int **array, int m, int k);
/*
 *  A function to print relevant information for part 1
 *
 *  @param const char *s1, the first string
 *  @param const char *s2, the second string
 *  @param char **temp, the array containing the LCS strings to print
 *  @param int k, number of LCS strings to print
 */
void printPart1(const char *s1, const char *s2, char **temp, int k);
/*
 *  Function to find file positions for each string
 *
 *  @param int *n, the number of strings
 *
 *  @return int *, the array of positons for strings
 */
int *computeLengths(int *n);
/*
 *  Function to compute levels of similarity between a number of strings
 *
 *  @param int n, the number of strings
 *  @param int *p, array of positions of strings for direct access
 */
void getSimilarity(int n, int *p);
/*
 *  Function to find length of LCS between two strings using 2*n array
 *
 *  @param const char *s1, the first string
 *  @param const char *s2, the second string
 *
 *  @return int, the length of the LCS
 */

int LCSLength2(const char *s1,const char *s2);
/*
 *  Function to compute level of similarity between two strings
 *  and return an appropriate symbol
 *
 *  @param int x, length of first string
 *  @param int y, length of second string
 *  @param int z, length of LCS
 *
 *  @return char, the character representing the level of similarity
 */
char findSim(int x, int y, int z);
/* 
 *  Function to Print the output table and free it
 *
 *  @param char **array, the output table
 *  @param int num, number of strings
 */
void printAndFree(char **array, int num);

#endif
