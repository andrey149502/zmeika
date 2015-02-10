#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const short n = 20, m = 30;

enum side{ Left, Top, Right, Bottom };
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

//void SetColor(ConsoleColor text, ConsoleColor background);
void SetColorText(ConsoleColor text);
void SetColorBg(ConsoleColor background);
void randomEda(short *coordI, short *coordJ, short kolZ, short &edaI, short &edaJ);
void DrawPole(short *coordI, short *coordJ, short edaI, short edaJ);
short Move(short side, short *coordI, short *coordJ, short &kolZ, short &edaI, short &edaJ);
void SetPosition(short x, short y);
void PrintCol(ConsoleColor background);
