#include <iostream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <math.h>

using std::cerr;
using std::endl;
using std::to_string;
using std::vector;
using std::cout;

#define ESC '\x1b'
#define CSI "\x1b["

enum class SGR : short
{
    black = 30,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white,
    brightBlack = 90,
    brightRed,
    brightGreen,
    brightYellow,
    brightBlue,
    brightMagenta,
    brightCyan,
    brightWhite
};

class UIObject
{
public:
    int prow, pcol;
    UIObject(int x_, int y_) : prow(x_), pcol(y_) {}
    virtual void draw(char **&displayChar, SGR **&displayColor) = 0;
};

class ConsoleUI
{
public:
    int height;
    int width;
    vector<UIObject *> uioj;
    // UIObject* uioj;
    char **displayChar;
    SGR **displayColor;

    CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
    HANDLE hout;

    ConsoleUI()
    {
        std::ios_base::sync_with_stdio(false);
        cout<<CSI<<"?25l";
        // get consloe height and width
        // hout = GetStdHandle(STD_OUTPUT_HANDLE);
        // GetConsoleScreenBufferInfo(hout, &ScreenBufferInfo);
        // width = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
        // height = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;
        //
        cout<<CSI<<"6n";
        scanf("\033[%d;%dR", &, y);
        cerr << height << " " << width << endl;

        displayChar = new char *[height];
        for (int i = 0; i < height; i++)
        {
            displayChar[i] = new char[width];
        }
        displayColor = new SGR *[height];
        for (int i = 0; i < height; i++)
        {
            displayColor[i] = new SGR[width];
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                displayChar[i][j] = ' ';
                displayColor[i][j] = SGR::brightWhite;
            }
        }
    }
    ~ConsoleUI()
    {
        delete[] displayChar;
        delete[] displayColor;
        for (auto i : uioj)
        {
            delete i;
        }
        // delete uioj;
    }

    void ClearScreen();
    void draw();
    void display();
};

void ConsoleUI::display()
{
    // SetConsoleCursorPosition(hout, {0, 0});
    cout<<CSI<<"H";
    this->draw();
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            std::cout << ESC << "[" << (int)displayColor[i][j] << "m" << displayChar[i][j] << ESC << "[0m";
        }
        if (i != height - 1)
            std::cout << '\n';
    }
    std::cout << std::flush;
}

void ConsoleUI::ClearScreen()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hout, &csbi))
        return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
            hout,
            (TCHAR)' ',
            cellCount,
            homeCoords,
            &count))
        return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
            hout,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count))
        return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hout, homeCoords);
}

void ConsoleUI::draw()
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            displayChar[i][j] = ' ';
            displayColor[i][j] = SGR::brightWhite;
        }
    }

    for (auto i : uioj)
    {
        // cerr << displayChar << " " << displayColor << endl;
        // cerr << i << endl;
        i->draw(displayChar, displayColor);
    }

    // uioj->draw(displayChar,displayColor);
}

class TextBox : public UIObject
{

public:
    TextBox(int x_, int y_) : UIObject(x_, y_) {}
    void draw(char **&displayChar, SGR **&displayColor) override;
};
void TextBox::draw(char **&displayChar, SGR **&displayColor)
{
    // 5*10

    // cerr << this->prow << " " << this->pcol << endl;

    for (int i = 0; i < 5; i++)
    {
        displayChar[this->prow + i][this->pcol] = '|';
    }
    // cerr << "ds1" << endl;
    for (int i = 0; i < 5; i++)
    {
        displayChar[this->prow + i][this->pcol + 9] = '|';
    }
    // cerr << "ds2" << endl;
    for (int i = 0; i < 10; i++)
    {
        displayChar[this->prow][this->pcol + i] = '-';
    }
    // cerr << "ds3" << endl;
    for (int i = 0; i < 10; i++)
    {
        displayChar[this->prow + 4][this->pcol + i] = '-';
    }
    // cerr << "ds4" << endl;
}
