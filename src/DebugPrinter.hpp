#ifndef DEBUG_PRINTER_HPP
#define DEBUG_PRINTER_HPP

class DebugPrinter
{
    public:
    DebugPrinter();
    void PrintString(const char* string);
    void PrintCharacter(char c);
    void PrintInt(int number);
    const DebugPrinter& operator<<(const int a);
    const DebugPrinter& operator<<(char a);
    const DebugPrinter& operator<<(const char* a);
};


#endif