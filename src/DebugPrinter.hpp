#ifndef DEBUG_PRINTER_HPP
#define DEBUG_PRINTER_HPP

class DebugPrinter
{
    public:
    DebugPrinter();
    void PrintString(const char* string) const;
    void PrintCharacter(char c) const;
    void PrintInt(int number) const;
    const DebugPrinter& operator<<(const int a) const;
    const DebugPrinter& operator<<(char a) const;
    const DebugPrinter& operator<<(const char* a) const;
};


#endif