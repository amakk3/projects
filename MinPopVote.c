/*-------------------------------------------
Program 4: Popular Vote Minimizer
Course: CS 251, Fall 2023, UIC
System: VS Code
Author: Abrar Makki
------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

// Function to get arguements from the command line and set the settings
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    *year = 0;
    *quietMode = false;
    *fastMode = false;
    for (int i = 1; i < argc; i++) { // loop through arguements
        if (strchr(argv[i], '-')) { // check the type of arguement by checking for '-' 
            if (strchr(argv[i], 'f')) { //once letters are checked, get next arguement for the number
                *fastMode = true;
            } else if (strchr(argv[i], 'y')) {
                if ((atoi(argv[i+1])% 4 != 0) || (atoi(argv[i+1]) < 1828) || (atoi(argv[i+1]) > 2020)) {
                    *year = 0;
                } else {
                    *year =atoi(argv[i+1]);
                }
            } else if (strchr((argv[i]), 'q')) {
                *quietMode = true;
            } else {
                return false; //if nothing was checked above, then arguement must be invalid type
            }
        }
    } 
    return true; 
}
// Function to create the input file
void inFilename(char* filename, int year) {
    char str1[100] = "data/"; // create base file path
    sprintf(filename, "%d", year); // convert num from year into string
    strcat(str1, filename); //concatinate the rest of the strings
    strcat(str1, ".csv");
    strcpy(filename, str1);
    return;
}
// Function to create the output file
void outFilename(char* filename, int year) {
    char str1[100] = "toWin/"; //create base file
    sprintf(filename, "%d", year); //convert year num into string
    strcat(str1, filename); // concatinate rest
    strcat(str1, "_win.csv");
    strcpy(filename, str1);
    return;
}
// Function to separate the line into tokens to fill in the state's subitems
bool parseLine(char* line, State* myState) {
    int comma_count = 0;
    for (int i = 0; i < strlen(line); i++) { //count the number of commas
        if (line[i] == ',') {
            comma_count++;
        }
    }
    if (comma_count != 3) { //if invalid comma format, return false
        return false;
    }
    char* token = strtok(line, ",");
    strcpy(myState->name , token); // split line into tokens to put into myState subitems
    token = strtok(NULL, ",");
    strcpy(myState->postalCode, token);
    token = strtok(NULL, ",");
    myState->electoralVotes = atoi(token);
    token = strtok(NULL, ",");
    char votes[30];
    strncpy(votes, token, strlen(token));
    votes[strlen(token)] = '\0';
    myState->popularVotes = atoi(votes);

    return true;
}
// Function to read the election data
bool readElectionData(char* filename, State* allStates, int* nStates) {
    //given string filename, read file and fill in allStates array, and increment nStates for each state filled in
    FILE* electionData = NULL;
    electionData = fopen(filename, "r"); //open file
    if (electionData == NULL) { // if file does not exist, then return false
        return false;
    }
    char line[200];
    *nStates = 0;
    while (fgets(line, 200, electionData)) { // loop through file date line by line and call parse line to fill in state's subitems
        parseLine(line, &allStates[*nStates]);
        (*nStates)++;
    }
    fclose(electionData);
    return true;
}
// Function to count the total number of electoral votes
int totalEVs(State* states, int szStates) {
    //iterate over all states and add up electoral votes
    int total = 0;
    for (int i = 0; i < szStates; i++) {
        total += states[i].electoralVotes;
    }
    return total;
}
// Function to count the total number of popular votes
int totalPVs(State* states, int szStates) {
    //iterate over all states and add up popular votes
    int total = 0;
    for (int i = 0; i < szStates; i++) {
        total += states[i].popularVotes;
    }
    return total;
}
// Function to calculate the minimum subset of states that will win the election
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    MinInfo result;
    // base case if the required number of electoral votes is less than or equal to 0
    if (EVs <= 0) {
        result.szSomeStates = 0; 
        result.subsetPVs = 0; 
        result.sufficientEVs = true; 
        return result;
    }
    // base case If all states have been considered and we still haven't found a sufficient number of EVs
    if (szStates == start) {
        result.szSomeStates = 0; 
        result.subsetPVs = 0;
        result.sufficientEVs = false; 
        return result;
    }
    // recursive call to minPopVoteAtLeast function with the current state included
    result = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);
    result.someStates[result.szSomeStates] = states[start]; // add current state to the result
    result.szSomeStates += 1; // increment the size of the result array
    result.subsetPVs += states[start].popularVotes / 2 + 1; // add the minimum popular vote required for the current state to the result
    // recursive call to minPopVoteAtLeast function with the current state excluded
    MinInfo excludeCurrent;
    excludeCurrent = minPopVoteAtLeast(states, szStates, start + 1, EVs);
    // compare the results of the two recursive calls and return the one with the lower minimum popular vote required
    if ((result.subsetPVs > excludeCurrent.subsetPVs) && (excludeCurrent.sufficientEVs)) {
        return excludeCurrent;
    } else if (!((result.subsetPVs > excludeCurrent.subsetPVs) && (excludeCurrent.sufficientEVs))){
        return result;
    }
}
// helper function for minPopVoteToWinFast
MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}
// Function to find the minimum popular vote
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    MinInfo result;
    // base case if the required number of electoral votes is less than or equal to 0
    if (EVs <= 0) {
        result.szSomeStates = 0; 
        result.subsetPVs = 0; 
        result.sufficientEVs = true; 
        return result;
    }
    // base case If all states have been considered and still haven't found a sufficient number of EVs
    if (szStates == start) {
        result.szSomeStates = 0; 
        result.subsetPVs = 0;
        result.sufficientEVs = false; 
        return result;
    }
    // check if the current state of the problem has been memoized
    if ((-1 < EVs) && memo[start][EVs].subsetPVs > -1) {
        return memo[start][EVs]; 
    }
    // include the current state in the subset and decrease the required EVs by its electoral votes
    result = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);
    result.someStates[result.szSomeStates] = states[start]; 
    result.szSomeStates += 1;
    result.subsetPVs += states[start].popularVotes / 2 + 1; 
    MinInfo excludeCurrent;

    excludeCurrent = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);
    // compare the two solutions and choose the one with fewer popular votes and sufficient EVs
    if ((result.subsetPVs > excludeCurrent.subsetPVs) && (excludeCurrent.sufficientEVs)) {
        memo[start][EVs] = excludeCurrent; 
        return excludeCurrent;
    } else if (!((result.subsetPVs > excludeCurrent.subsetPVs) && (excludeCurrent.sufficientEVs))){
        memo[start][EVs] = result;
        return result;
    }
}
// Function to find the minimum popular vote
MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    // allocate memory for memo
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
    // free all memory that was malloced
    for (int i = 0; i < szStates+1; ++i) {
        free(memo[i]);
    }
    free(memo);
    return res;
}
// Function to print the state's subitems
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    //given name of file filenameW, write [TotalEVs],[TotalPVs],[EVsWon],[PVsWon] as the first line
    // after the first line write each state in the subset in the order they were added to the subset
    FILE* subsetData = NULL;
    subsetData = fopen(filenameW, "w");
    if (subsetData == NULL) {
        return false;
    }
    fprintf(subsetData, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);
    // reverse the order of the states in the subset to print in the correct order
    for (int i = 0; i < toWin.szSomeStates; i++) {
        fprintf(subsetData, "%s,%s,%d,%d\n", toWin.someStates[toWin.szSomeStates-i-1].name, toWin.someStates[toWin.szSomeStates-i-1].postalCode, toWin.someStates[toWin.szSomeStates-i-1].electoralVotes, toWin.someStates[toWin.szSomeStates-i-1].popularVotes/2+1);
    }
    fclose(subsetData);
    return true;
}
