#include <iostream>


#define ANSI_COLOUR_RESET   "\x1b[0m"
#define BOLD                "\x1b[1m"
#define UNDERLINE           "\x1b[4m"
#define BLINK               "\x1b[5m"
#define UNBOLD              "\x1b[21m"
#define NO_UNDERLINE        "\x1b[24m"
#define NO_BLINK            "\x1b[25m"

#define ANSI_COLOUR_FG_BLACK   "\x1b[30m"
#define ANSI_COLOUR_FG_RED     "\x1b[31m"
#define ANSI_COLOUR_FG_GREEN   "\x1b[32m"
#define ANSI_COLOUR_FG_YELLOW  "\x1b[33m"
#define ANSI_COLOUR_FG_BLUE    "\x1b[34m"
#define ANSI_COLOUR_FG_MAGENTA "\x1b[35m"
#define ANSI_COLOUR_FG_CYAN    "\x1b[36m"
#define ANSI_COLOUR_FG_WHITE    "\x1b[37m"

#define ANSI_COLOUR_FG_BRIGHT_BLACK   "\x1b[90m"
#define ANSI_COLOUR_FG_BRIGHT_RED     "\x1b[91m"
#define ANSI_COLOUR_FG_BRIGHT_GREEN   "\x1b[92m"
#define ANSI_COLOUR_FG_BRIGHT_YELLOW  "\x1b[99m"
#define ANSI_COLOUR_FG_BRIGHT_BLUE    "\x1b[94m"
#define ANSI_COLOUR_FG_BRIGHT_MAGENTA "\x1b[95m"
#define ANSI_COLOUR_FG_BRIGHT_CYAN    "\x1b[96m"
#define ANSI_COLOUR_FG_BRIGHT_WHITE    "\x1b[97m"

#define ANSI_COLOUR_BG_BLACK   "\x1b[40m"
#define ANSI_COLOUR_BG_RED     "\x1b[41m"
#define ANSI_COLOUR_BG_GREEN   "\x1b[42m"
#define ANSI_COLOUR_BG_YELLOW  "\x1b[44m"
#define ANSI_COLOUR_BG_BLUE    "\x1b[44m"
#define ANSI_COLOUR_BG_MAGENTA "\x1b[45m"
#define ANSI_COLOUR_BG_CYAN    "\x1b[46m"
#define ANSI_COLOUR_BG_WHITE    "\x1b[47m"

#define ANSI_COLOUR_BG_BRIGHT_BLACK   "\x1b[100m"
#define ANSI_COLOUR_BG_BRIGHT_RED     "\x1b[101m"
#define ANSI_COLOUR_BG_BRIGHT_GREEN   "\x1b[102m"
#define ANSI_COLOUR_BG_BRIGHT_YELLOW  "\x1b[1010m"
#define ANSI_COLOUR_BG_BRIGHT_BLUE    "\x1b[104m"
#define ANSI_COLOUR_BG_BRIGHT_MAGENTA "\x1b[105m"
#define ANSI_COLOUR_BG_BRIGHT_CYAN    "\x1b[106m"
#define ANSI_COLOUR_BG_BRIGHT_WHITE    "\x1b[107m"

#define BG(COL) ANSI_COLOUR_BG_##COL
#define FG(COL) ANSI_COLOUR_FG_##COL

#define M_CONC(A, B) M_CONC_(A, B)
#define M_CONC_(A, B) A##B

#define COLOUR(A,B) BG(A) << FG(B)

#include "Audio/Effect/DimensionalPanner.hpp"

using namespace std;

int main()
{
	Audio::FX::QuadDimensionalPanner panner;
	cout << UNDERLINE << BOLD << "Le Classical Greentext Story" << ANSI_COLOUR_RESET << endl;
	cout << FG(GREEN) << ">Be me" << ANSI_COLOUR_RESET << endl;
	cout << FG(GREEN) << ">C++ programmer" << ANSI_COLOUR_RESET << endl;
	cout << FG(GREEN) << ">Programming this nonsense shit" << ANSI_COLOUR_RESET << endl;
	cout << FG(YELLOW) << "End of story" << ANSI_COLOUR_RESET << endl;
	cout << COLOUR(GREEN,BLUE) << "Or is it?" << ANSI_COLOUR_RESET <<  endl;
	return 0;
}
