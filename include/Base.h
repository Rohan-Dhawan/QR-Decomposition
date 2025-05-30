#ifndef BASE_H
#define BASE_H


class Base
{
    public:
        Base(int id = 0);
        virtual ~Base();

        // Attributes
        int nID;                    // number of an object

        static char logFile[256];   // Log file name
        static char msg[256];       // Message for logging

        // Methods
        static void appendLog(char* str);           // append msg to log
        static void appendLog(const char* str);     // append msg to log
        static void resetLog();                     // Delete log file


    protected:

    private:
        static int nCounter;         // Counter of number of objects
};

#endif // BASE_H
