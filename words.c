
//  words.c
//  Project 5
//  David Cordes CS100-001
//  Created by Reagan Soltis on 10/31/17.
//  Copyright © 2017 Reagan Soltis. All rights reserved.

// This projects takes in a data file and integar size as its command-line arguments and allows the user to pick a word to find. The program then prints the puzzle and says exactly where the word was found in the matrix and prints the puzzle again with "." for every non-valid character.

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//Variables
int count = 0;
int RLcount = 0;
int TBcount = 0;
int BTcount = 0;


void reverseWord(char word[]);

int LR(int size, char **search, char word[], char **emptyArray);
int RL(int size, char **search, char word [], char **emptyArray);
int TB(int size, char **search, char word [], char **emptyArray);
int BT(int size, char **search, char word [], char **emptyArray);

//Functions used to clear array/print matrixes
void clearArray(char **search, int size) {
    for (int i = 0; i < size; i++) {
        for (int j=0; j <size; j++) {
            search[i][j] = '.';
        }
    }
}

void printArray (char **search, int size) {
    for (int i = 0; i < size; i++) {
        printf("\t");
        for (int j = 0; j < size; j++) {
            printf("%c", search[i][j]);
        }
        printf("\n");
    }
}

int main (int argc, char *argv[])
{
    //Open the data file and print error messages
    FILE *inFile = fopen(argv[2], "r");
    if (inFile == NULL) {
        printf("file \"%s\" does not exist\n", argv[2]);
        return -1;
    }
    int size = atoi(argv[1]);
    char **search = malloc(sizeof(char*) * (size + 1));
    if (search == NULL) {
        printf("Not enough memory\n");
        return -1;
    }
    
    for (int i=0; i<size; i++) {
        search[i] = malloc(sizeof(char) * size);
        if (search[i] == NULL) {
            printf("Not enough memory\n");
            return -1;
        }
    }
    
    char **emptyArray = malloc(sizeof(char*) * (size + 1));
    if (emptyArray == NULL) {
        printf("Not enough memory\n");
        return -1;
    }
    for (int i = 0; i < size; i++) {
        emptyArray[i] = malloc(sizeof(char) * size);
        if (emptyArray[i] == NULL) {
            printf("Not enough memory\n");
            return -1;
        }
    }
    
    clearArray(emptyArray, size);
    
    
    // Checking arguments
    if (argc != 3) {
        printf("Incorrect number of arguments\n");
        return -1;
    }
    //Scan puzzle
    printf("The word puzzle is: \n");
    for (int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
            fscanf(inFile, " %c", &search[r][c]);
        }
    }
    
    //Print puzzle
    for (int r=0; r<size; r++) {
        printf("\t");
        for (int c=0; c<size; c++) {
            printf("%c", search[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    
    //Getting user inputted word
    char word[size+1];
    printf("Enter a word to find in the puzzle: ");
    scanf("%s", word);
    printf("\n");
    
    while (strcmp(word, "zzz") != 0) {
        
        int LRcount = LR(size, search, word, emptyArray);
        int RLcount = RL(size, search, word, emptyArray);
        int TBcount = TB(size, search, word, emptyArray);
        int BTcount = BT(size, search, word, emptyArray);
        count = LRcount + TBcount + BTcount + RLcount;
        
        //Print statements
        
        printf("The word %s was found %d times as shown below\n", word, count);
        printf("\t%d times left-to-right\n", LRcount);
        printf("\t%d times top-to-bottom\n", TBcount);
        printf("\t%d times bottom-to-top\n", BTcount);
        printf("\t%d times right-to-left\n", RLcount);
        printf("\n");
        printArray(emptyArray, size);
        clearArray(emptyArray, size);
        printf("\n");
        printf("Enter another word to find (or 'zzz' to exit): ");
        scanf("%s", word);
        
    }
    printf("\n");
    
    
    return 0;
}

//Search functions

int LR(int size, char **search, char word[], char **emptyArray) {
    
    bool wordIsReal = false;
    int num = 0;
    
    int len = strlen(word);
    for (int r=0; r<size; r++) {
        for (int c=0; c<size-len+1; c++) {
            wordIsReal = true;
            for (int w=0; w<len; w++) {
                if (word[w] != search[r][c+w]) {
                    wordIsReal = false;
                    break;
                }
            }
            if (wordIsReal == true) {
                for (int i = 0; i < strlen(word); i++) {
                    emptyArray[r][c+i] = word[i];
                    
                }
                num++;
            }
        }
    }
    return num;
}

int RL(int size, char **search, char word[], char **emptyArray) {
    
    char reverse[strlen(word) + 1];
    strcpy (reverse, word);
    
    reverseWord(reverse);
    
    bool wordIsReal = false;
    int num = 0;
    
    int len = strlen(word);
    for (int r=0; r<size; r++) {
        for (int c=0; c<size-len+1; c++) {
            wordIsReal = true;
            for (int w=0; w<len; w++) {
                if (reverse[w] != search[r][c+w]) {
                    wordIsReal = false;
                    break;
                }
            }
            if (wordIsReal == true) {
                for (int i = 0; i < strlen(reverse); i++) {
                    emptyArray[r][c+i] = reverse[i];
                    
                }
                num++;
            }
        }
    }
    return num;
}
int TB(int size, char **search, char word[], char **emptyArray) {
    
    bool wordIsReal = false;
    int num = 0;
    
    int len = strlen(word);
    for (int r=0; r<size-len+1; r++) {
        for (int c=0; c<size; c++) {
            wordIsReal = true;
            for (int w=0; w<len; w++) {
                if (word[w] != search[r+w][c]) {
                    wordIsReal = false;
                    break;
                }
            }
            if (wordIsReal == true) {
                for (int i = 0; i < strlen(word); i++) {
                    emptyArray[r+i][c] = word[i];
                    
                }
                num++;
            }
        }
    }
    return num;
}


int BT(int size, char **search, char word[], char **emptyArray) {
    
    char reverse[strlen(word) + 1];
    strcpy (reverse, word);
    
    reverseWord(reverse);
    
    bool wordIsReal = false;
    int num = 0;
    
    int len = strlen(word);
    for (int r=0; r<size-len+1; r++) {
        for (int c=0; c<size; c++) {
            wordIsReal = true;
            for (int w=0; w<len; w++) {
                if (reverse[w] != search[r+w][c]) {
                    wordIsReal = false;
                    break;
                }
            }
            if (wordIsReal == true) {
                for (int i = 0; i < strlen(reverse); i++) {
                    emptyArray[r+i][c] = reverse[i];
                    
                }
                num++;
            }
        }
    }
    return num;
}



void reverseWord(char word[])
{
    int max = strlen(word) - 1;
    int min = 0;
    char temp;
    
    while (min < max) {
        temp = word[min];
        word[min] = word[max];
        word[max] = temp;
        min++;
        max--;
    }
}



