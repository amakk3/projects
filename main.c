/*-------------------------------------------
Program 5: Smallest Word Ladder
Course: CS 211, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

int countWordsOfLength(char* filename, int wordSize) { 
    // count the number of words in a file that are exactly "wordSize" letters long
    FILE* file = fopen(filename,"r");
    if (file == NULL) { // if file not found, return -1
        return -1;
    }
    int count = 0;
    char word[100];
    while (!feof(file)) { // go through each word in the file
        fscanf(file,"%s",word);
        if (strlen(word) == wordSize) { // if word is correct length, increment count
            count++; 
        }
    }
    fclose(file);
    return count;
}

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    // build an array of words from a file that are exactly "wordSize" letters long
    FILE* file = fopen(filename,"r");
    if (file == NULL) { // if file not found, return false
        return false;
    }
    int count = 0;
    char word[100];
    while (!feof(file)) { // go through each word in the file
        fscanf(file,"%s",word);
        if (strlen(word) == wordSize) { // if word is correct length, copy it to the array
            strcpy(words[count],word);
            count++; 
        }
    }
    fclose(file);
    return (count == numWords);
}

int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    // find the index of a word in an array of words using binary search
    if (loInd > hiInd) { // if word not found, return -1
        return -1;
    }
    int midInd = (loInd + hiInd) / 2;
    int cmp = strcmp(aWord, words[midInd]); // compare the word to the middle word
    if (cmp == 0) { // if word found, return its index
        return midInd;
    } else if (cmp < 0) { // if word is before the middle word, search the first half
        return findWord(words,aWord,loInd,midInd-1);
    } else { // if word is after the middle word, search the second half
        return findWord(words,aWord,midInd+1,hiInd);
    }
}

void freeWords(char** words, int numWords) {
    // free the heap-allocated memory for the words array
    for (int i = 0; i < numWords; ++i) {
        free(words[i]);
    }
    free(words);
}

void insertWordAtFront(WordNode** ladder, char* newWord) {
    // insert a new word at the front of a word ladder
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode)); // allocate space for the new word
    newNode->myWord = newWord; // set the new word
    newNode->next = *ladder; // set the next word to the old front of the ladder
    *ladder = newNode;
}

int getLadderHeight(WordNode* ladder) {
    // get the height of a word ladder
    int count = 0;
    WordNode* currNode = ladder;
    while (currNode != NULL) { // go through each word in the ladder
        count++; // increment count
        currNode = currNode->next;
    }
    return count;
}

WordNode* copyLadder(WordNode* ladder) {
    // copy a word ladder
    WordNode* new_ladder;
    WordNode* newCurrNode;
    WordNode* currNode = ladder;
    for (int i = getLadderHeight(ladder)-1; i >= 0; --i) { // go through each word in the ladder
        WordNode* newNode = (WordNode*)malloc(sizeof(WordNode)); // allocate space for the new word
        newNode->myWord = currNode->myWord; // set the new word
        newNode->next = NULL;
        if (i == getLadderHeight(ladder)-1) { // if this is the first word in the ladder set head node
            new_ladder = newNode;
            newCurrNode = new_ladder;
        } else { // otherwise set the next word to the new word
            newCurrNode->next = newNode;
            newCurrNode = newCurrNode->next;
        }
        currNode = currNode->next;
    }
    return new_ladder;
}

void freeLadder(WordNode* ladder) {
    // free the heap-allocated memory for a word ladder
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        WordNode* nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
}

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    // insert a new word ladder at the back of a list of word ladders
    LadderNode* newNode = (LadderNode*)malloc(sizeof(LadderNode)); // allocate space for the new ladder
    newNode->topWord = newLadder;
    newNode->next = NULL;
    if (*list == NULL) { // if the list is empty set the head node
        *list = newNode;
    } else {
        LadderNode* currNode = *list;
        while (currNode->next != NULL) { // go to the end of the list
            currNode = currNode->next; // set the next node to the new ladder
        }
        currNode->next = newNode;
    }
}

WordNode* popLadderFromFront(LadderNode** list) {
    // pop a word ladder from the front of a list of word ladders
    if (*list == NULL) { // if the list is empty return NULL
        return NULL;
    }
    LadderNode* poppedNode = *list; // set the popped node to the head node
    *list = (*list)->next; // set the head node to the next node
    poppedNode->next = NULL;
    WordNode* poppedLadder = poppedNode->topWord; // set the popped ladder to the top word of the popped node
    free(poppedNode);
    return poppedLadder;
}

void freeLadderList(LadderNode* myList) {
    // free the heap-allocated memory for a list of word ladders
    LadderNode* currNode = myList;
    while (currNode != NULL) {
        LadderNode* nextNode = currNode->next;
        freeLadder(currNode->topWord);
        free(currNode);
        currNode = nextNode;
    }
}

WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {
    // find the shortest word ladder between two words
    LadderNode* myList = NULL;
    // create myLadder, an empty list of WordNode structs
    WordNode* myLadder = NULL;
    insertWordAtFront(&myLadder,startWord);
    insertLadderAtBack(&myList,myLadder);
    while (myList != NULL) { // while myList is not empty:
        myLadder = popLadderFromFront(&myList); 
        int wordInd = findWord(words, myLadder->myWord, 0, numWords-1); // find the index of the current word
        for (int i = 0; i < numWords; ++i) { // go through each word in the word array
            if (i != wordInd && !usedWord[i]) { // if the word is not the current word and has not been used
                int changes = 0;
                for (int j = 0; j < wordSize; ++j) { // go through each letter in the word
                    if (words[i][j] != myLadder->myWord[j]) { // if the letter is different increment changes
                        changes++;
                    }
                }
                if (changes == 1) { // if there is only one letter different
                    if (strcmp(words[i], finalWord) == 0) { // if the word is the final word return the ladder
                        insertWordAtFront(&myLadder, words[i]);// insert the word at the front of the ladder
                        freeLadderList(myList); // free the list of ladders
                        return myLadder;
                    } else { // otherwise add the word to the ladder and add the ladder to the list
                        WordNode* anotherLadder = copyLadder(myLadder); // copy the ladder
                        insertWordAtFront(&anotherLadder, words[i]); // insert the word at the front of the ladder
                        insertLadderAtBack(&myList, anotherLadder); // insert the ladder at the back of the list
                        usedWord[i] = true;
                    }
                }
            }
        }
        freeLadder(myLadder);
    }    
    freeLadderList(myList);
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main()
//-----------------------------------------------------
int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
