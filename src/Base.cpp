#include <iostream>
#include "Base.h"
#include "QR_Decompo.h"

int  Base::nCounter = 0;                            // total number of objects
char Base::msg[256] = {0};                          // message for logging

char Base::logFile[256] = "QR_HHT.log";                // Log file name

Base::Base(int nID)
{
    nCounter++;                                     // increment the number of object

    if (nID) this->nID = nID;                       // Use pointer to assign value to an attribute
    else     this->nID = nCounter;                  // Otherwise assign nCounter to attribute

    sprintf(msg,"> Object %d created.",this->nID);  // print object created to msg
    appendLog(msg);                                 // write the string to log file

}

Base::~Base()
{
    sprintf(msg,"> Object %d deleted.",nID);        // Object deleted
    appendLog(msg);                                 // Append msg
    nCounter--;                                     // Reduce the total counter
}

void Base::appendLog(char* str)                     // function with dynamic format
{
    appendLog((const char*)str);                    // convert dynamic format to string
}

void Base::appendLog(const char* str)               // Constant string without dynamic format
{
    // Print to the screen
    printf("%s\n",str);                             // print string onto screen

    // Print on log file
    //    | file handle
    //                 | file name
    //                         | modes of opening
    FILE* pHnd = fopen(logFile,"a");
    // Modes:
    // "w": write (delete file)
    // "r": read
    // "wr": write and read
    // "a" : append file

    // error check
    if (!pHnd) return;                              // error in opening file

    // print in file
    fprintf(pHnd,"%s\n",str);                       // append the file
    fclose(pHnd);                                   // close the log file
}

void Base::resetLog()                               // Delete the log file
{
    remove(logFile);                                // delete log file
}
