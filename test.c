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

// printing State data members, all items on one line
bool test_totalEVs() {
    State aStates[10];
    int res;
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;
    // call totalEVs() with the array of states to calculate the total number of electoral votes in the array
    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 13, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return 0;
    }

    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 15;
    aStates[6].electoralVotes = 12;
    aStates[7].electoralVotes = 8;
    aStates[8].electoralVotes = 14;
    aStates[9].electoralVotes = 13;
    
    printf(" Checking totalEVs() for 10 States:\n");
    res = totalEVs(aStates,10);
    // check the total number of electoral votes in the array
    if (res != 100) {
        printf("  expected total EVs = 100, actual total EVs = %d\n",res);
        return false;
    }

    return true;
}
// a test case for totalPVs() by creating an array of states and calling totalPVs()
bool test_totalPVs() {
    State aStates[10];
    int res;
    aStates[0].popularVotes = 5;
    aStates[1].popularVotes = 8;
    aStates[2].popularVotes = 12;
    aStates[3].popularVotes = 6;
    aStates[4].popularVotes = 7;
    aStates[5].popularVotes = 10;
    // call totalPVs() with the array of states to calculate the total number of popular votes in the array
    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,5);
    if (res != 38) {
        printf("  individual state PVs are 5, 8, 13, 6, 7\n");
        printf("  expected total PVs = 38, actual total PVs = %d\n",res);
        return 0;
    }

    aStates[0].popularVotes = 53;
    aStates[1].popularVotes = 832;
    aStates[2].popularVotes = 1462;
    aStates[3].popularVotes = 7586;
    aStates[4].popularVotes = 247;
    aStates[5].popularVotes = 16245;
    aStates[6].popularVotes = 1242;
    aStates[7].popularVotes = 428;
    aStates[8].popularVotes = 134;
    aStates[9].popularVotes = 16;

    printf(" Checking totalPVs() for 10 States:\n");
    res = totalPVs(aStates,10);
    // check the total number of popular votes in the array
    if (res != 28245) {
        printf("  expected total PVs = 28245, actual total PVs = %d\n",res);
        return false;
    }
    return true;
}
// a test case for setSettings() by calling setSettings() and checking the values in the year, fastMode, and quietMode variables
bool test_setSettings() {
    int year = 0;
    bool fastMode = false;
    bool quietMode = false;
    printf(" Checking setSettings() for 5 different types of arguments:\n");
    char* argv[10];
    argv[0] = "./app.exe";
    argv[1] = "-y";
    argv[2] = "2016";
    argv[3] = "-f";
    argv[4] = "-q";
    // call setSettings() with the 5 arguments above to set the values
    if (setSettings(5, argv, &year, &fastMode, &quietMode) == false) {
        printf("  expected setSettings() to return true, actual return value is false\n");
        return false;
    }
    if (year != 2016) {
        printf("  expected year = 2016, actual year = %d\n", year);
        return false;
    }
    argv[4] = "-v";
    // check for invalid arguement
    if (setSettings(5, argv, &year, &fastMode, &quietMode) == true) {
        printf("  expected setSettings() to return false, actual return value is true\n");
        return false;
    }
    argv[4] = "-q";
    argv[3] = "-v";
    if (setSettings(5, argv, &year, &fastMode, &quietMode) == true) {
        printf("  expected setSettings() to return false, actual return value is true\n");
        return false;
    }
    argv[3] = "-f";
    argv[2] = "2017";
    if (setSettings(5, argv, &year, &fastMode, &quietMode) == false) {
        printf("  expected setSettings() to return true, actual return value is false\n");
        return false;
    }
    return true;
}
// a test case for inFilename() by calling inFilename() and checking the value in the filename string
bool test_inFilename() {
    printf(" Checking inFilename() for 2 different years:\n");
    char filename[100];
    inFilename(filename, 2016);
    // check the value in the filename string
    if (strcmp(filename, "data/2016.csv") != 0) {
        printf("  expected filename = data/2016.csv, actual filename = %s\n", filename);
        return false;
    }
    // call inFilename() with the year 2017 to generate the filename string
    inFilename(filename, 2017);
    if (strcmp(filename, "data/2017.csv") != 0) {
        printf("  expected filename = data/2017.csv, actual filename = %s\n", filename);
        return false;
    }
    return true;
}
// a test case for outFilename() by calling outFilename() and checking the value in the filename string
bool test_outFilename() {
    printf(" Checking outFilename() for 2 different years:\n");
    char filename[100];
    outFilename(filename, 2016);
    // check the value in the filename string
    if (strcmp(filename, "toWin/2016_win.csv") != 0) {
        printf("  expected filename = toWin/2016_win.csv, actual filename = %s\n", filename);
        return false;
    }
    // call outFilename() with the year 2017 to generate the filename string
    outFilename(filename, 2017);
    if (strcmp(filename, "toWin/2017_win.csv") != 0) {
        printf("  expected filename = toWin/2017_win.csv, actual filename = %s\n", filename);
        return false;
    }

    return true; 
}
// a test case for parseLine() by calling parseLine() and checking the values in the myState struct
bool test_parseLine() {
    printf(" Checking parseLine() for 4 different lines:\n");
    State myState;
    char line[100] = "Alabama,AL,9,1318255 ";
    // call parseLine() with the line above to parse the line and store the values in the myState struct
    if (parseLine(line, &myState) == false) {
        printf("  expected parseLine() to return true, actual return value is false\n");
        return false;
    }
    // check the values in the myState struct
    if (strcmp(myState.name, "Alabama") != 0) {
        printf("  expected myState.name = Alabama, actual myState.name = %s\n", myState.name);
        return false;
    }
    if (strcmp(myState.postalCode, "AL") != 0) {
        printf("  expected myState.postalCode = AL, actual myState.postalCode = %s\n", myState.postalCode);
        return false;
    }
    // check the electoral votes and popular votes for the state
    if (myState.electoralVotes != 9) {
        printf("  expected myState.electoralVotes = 9, actual myState.electoralVotes = %d\n", myState.electoralVotes);
        return false;
    }
    // check the electoral votes and popular votes for the state
    if (myState.popularVotes != 1318255) {
        printf("  expected myState.popularVotes = 1318255, actual myState.popularVotes = %d\n", myState.popularVotes);
        return false;
    }
    strcpy(line, "Alabama,AL,9,1318255,extra");
    if (parseLine(line, &myState) == true) {
        printf("  expected parseLine() to return false, actual return value is true\n");
        return false;
    }
    strcpy(line, "Alabama,AL,9");
    if (parseLine(line, &myState) == true) {
        printf("  expected parseLine() to return false, actual return value is true\n");
        return false;
    }
    strcpy(line, "Alabama,AL,9,1318255,extra");
    if (parseLine(line, &myState) == true) {
        printf("  expected parseLine() to return false, actual return value is true\n");
        return false;
    }
    strcpy(line, "Hello,HI,3,25000");
    parseLine(line, &myState);

    return true;
}
// a test case for readElectionData() by calling readElectionData() and checking the values in the array of states
bool test_readElectionData() {
    printf(" Checking readElectionData() for 2016.csv:\n");
    State allStates[100];
    int nStates = 0;
    // call readElectionData() with the 2016.csv file to create an array of states
    if (readElectionData("data/2016.csv", allStates, &nStates) == false) {
        printf("  expected readElectionData() to return true, actual return value is false\n");
        return false;
    }
    // check the number of states in the array
    if (nStates != 51) {
        printf("  expected nStates = 51, actual nStates = %d\n", nStates);
        return false;
    }
    // check the values in the array of states
    if (strcmp(allStates[0].name, "Alabama") != 0) {
        printf("  expected allStates[0].name = Alabama, actual allStates[0].name = %s\n", allStates[0].name);
        return false;
    }
    if (strcmp(allStates[0].postalCode, "AL") != 0) {
        printf("  expected allStates[0].postalCode = AL, actual allStates[0].postalCode = %s\n", allStates[0].postalCode);
        return false;
    }
    // check the electoral votes and popular votes for the first state in the array
    if (allStates[0].electoralVotes != 9) {
        printf("  expected allStates[0].electoralVotes = 9, actual allStates[0].electoralVotes = %d\n", allStates[0].electoralVotes);
        return false;
    }
    if (allStates[0].popularVotes != 2123372) {
        printf("  expected allStates[0].popularVotes = 2123372, actual allStates[0].popularVotes = %d\n", allStates[0].popularVotes);
        return false;
    }
    if (strcmp(allStates[50].name, "Wyoming") != 0) {
        printf("  expected allStates[50].name = Wyoming, actual allStates[50].name = %s\n", allStates[50].name);
        return false;
    }
    if (strcmp(allStates[50].postalCode, "WY") != 0) {
        printf("  expected allStates[50].postalCode = WY, actual allStates[50].postalCode = %s\n", allStates[50].postalCode);
        return false;
    }
    if (allStates[50].electoralVotes != 3) {
        printf("  expected allStates[50].electoralVotes = 3, actual allStates[50].electoralVotes = %d\n", allStates[50].electoralVotes);
        return false;
    }
    if (allStates[50].popularVotes != 255849) {
        printf("  expected allStates[50].popularVotes = 255849, actual allStates[50].popularVotes = %d\n", allStates[50].popularVotes);
        return false;
    }
    return true;
}
// a test case for minPopVoteAtLeast() by creating an array of states and calling minPopVoteAtLeast()
bool test_minPVsSlow() {
    // a test case for minPopVoteAtLeast() by creating an array of 4 states and calling minPopVoteAtLeast()
    printf(" Checking minPopVoteAtLeast() for 4 states:\n");
    // create an array of 4 states, with each state having a different number of electoral votes and popular votes
    State states[4];
    states[0].electoralVotes = 5;
    states[0].popularVotes = 20;
    states[1].electoralVotes = 8;
    states[1].popularVotes = 30;
    states[2].electoralVotes = 12;
    states[2].popularVotes = 40;
    states[3].electoralVotes = 6;
    states[3].popularVotes = 50;
    // calculate the total number of electoral votes in the array of states and the number of electoral votes required to win the election
    int totEVs = totalEVs(states, 4);
    int reqEVs = totEVs/2 + 1;
    // call minPopVoteAtLeast() with the array of states to find the minimum popular vote total for a subset of states that has enough electoral votes to win the election
    MinInfo rez = minPopVoteAtLeast(states, 4, 0, reqEVs);
    // check every set in rez
    if (rez.szSomeStates != 2) {
        printf("  expected rez.szSomeStates = 2, actual rez.szSomeStates = %d\n", rez.szSomeStates);
        return false;
    }
    // check the total popular vote for the subset of states returned by the function
    if (rez.subsetPVs != 32) {
        printf("  expected rez.subsetPVs = 70, actual rez.subsetPVs = %d\n", rez.subsetPVs);
        return false;
    }
    // check the sufficientEVs field in the MinInfo struct to ensure that it is set to true
    if (rez.sufficientEVs != true) {
        printf("  expected rez.sufficientEVs = true, actual rez.sufficientEVs = %d\n", rez.sufficientEVs);
        return false;
    }
    // check the electoral votes and popular votes for the first state in the someStates array returned by the function
    if (rez.someStates[0].electoralVotes != 12) {
        printf("  expected rez.someStates[0].electoralVotes = 12, actual rez.someStates[0].electoralVotes = %d\n", rez.someStates[0].electoralVotes);
        return false;
    }
    if (rez.someStates[0].popularVotes != 40) {
        printf("  expected rez.someStates[0].popularVotes = 40, actual rez.someStates[0].popularVotes = %d\n", rez.someStates[0].popularVotes);
        return false;
    }
    // if all checks pass, return true to indicate that the test case succeeded
    return true;
}
// a test case for minPopVoteAtLeastFast() by creating an array of states and calling minPopVoteAtLeastFast()
bool test_minPVsFast() {
    printf(" Checking minPopVoteAtLeastFast() for 50 states:\n");
    // create an array of 50 states, with each state having 5 electoral votes and 20 popular votes
    State states[50];
    for (int i = 0; i < 50; ++i) {
        states[i].electoralVotes = 5;
        states[i].popularVotes = 20;
    }
    // call minPopVoteToWinFast() with the array of states to find the minimum popular vote total for a subset of states that has enough electoral votes to win the election
    MinInfo rez = minPopVoteToWinFast(states, 50);
    // check every set in rez
    if (rez.szSomeStates != 26) {
        printf("  expected rez.szSomeStates = 26, actual rez.szSomeStates = %d\n", rez.szSomeStates);
        return false;
    }
    // check the total popular vote for the subset of states returned by the function
    if (rez.subsetPVs != 286) {
        printf("  expected rez.subsetPVs = 130, actual rez.subsetPVs = %d\n", rez.subsetPVs);
        return false;
    }
    // check the sufficientEVs field in the MinInfo struct to ensure that it is set to true
    if (rez.sufficientEVs != true) {
        printf("  expected rez.sufficientEVs = true, actual rez.sufficientEVs = %d\n", rez.sufficientEVs);
        return false;
    }
    // check the electoral votes and popular votes for the first state in the someStates array returned by the function
    if (rez.someStates[0].electoralVotes != 5) {
        printf("  expected rez.someStates[0].electoralVotes = 5, actual rez.someStates[0].electoralVotes = %d\n", rez.someStates[0].electoralVotes);
        return false;
    }
    if (rez.someStates[0].popularVotes != 20) {
        printf("  expected rez.someStates[0].popularVotes = 20, actual rez.someStates[0].popularVotes = %d\n", rez.someStates[0].popularVotes);
        return false;
    }
    // if all checks pass, return true to indicate that the test case succeeded
    return true;
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
