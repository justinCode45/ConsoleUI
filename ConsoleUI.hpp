#include <iostream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <math.h>
#include <variant>
#include <tuple>
#include <string>
#include <fstream>
#include <functional>
using std::apply;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::fstream;
using std::function;
using std::get;
using std::string;
using std::stringstream;
using std::to_string;
using std::tuple;
using std::variant;
using std::vector;

#define ESC '\x1b'
#define CSI "\x1b["
#define color(in, c) CSI + to_string((int)c) + 'm' + in + CSI "0m"
typedef tuple<double, double, int> Tddi;

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

class Rect
{
public:
    int top, left, bottom, right;
    Rect(int top_, int left_, int bottom_, int right_) : top(top_), left(left_), bottom(bottom_), right(right_) {}
    Rect() : top(0), left(0), bottom(0), right(0) {}
};

class UnitChar
{
public:
    string c;
    variant<SGR, int> colorF;
    variant<SGR, int> colorB;
    UnitChar()
    {
        c = ' ';
        colorF = SGR::white;
        colorB = 232;
    };
    void setColorF(int c256)
    {
        colorF = c256;
    }
    void setColorF(SGR x)
    {
        colorF = x;
    }
    void setColorF(variant<SGR, int> x)
    {
        colorF = x;
    }
    void setColorB(int c256)
    {
        colorB = c256;
    }
    void setColorB(SGR x)
    {
        colorB = x;
    }
    void setColorB(variant<SGR, int> x)
    {
        colorB = x;
    }
    string toString()
    {
        std::stringstream ss;

        if (colorF.index() == 1)
        {
            int c256 = std::get<1>(colorF);
            ss << CSI << "38;5;" << c256 << 'm';
        }
        else
        {
            ss << CSI << static_cast<int>(std::get<0>(colorF)) << 'm';
        }

        if (colorB.index() == 1)
        {
            int c256 = std::get<1>(colorB);
            ss << CSI << "48;5;" << c256 << 'm';
        }
        else
        {
            ss << CSI << static_cast<int>(std::get<0>(colorB)) << 'm';
        }
        ss << c;
        ss << CSI << "0m";
        return ss.str();
    }
    void claer()
    {
        c = ' ';
        colorF = SGR::white;
        colorB = 232;
    }
    void setChar(char c_)
    {
        c = c_;
    }
};

vector<vector<UnitChar>> convetStringtoUnitChar(string s);
void decodeColor(string temp, variant<SGR, int> &resultF, variant<SGR, int> &resultB);

class UIObject
{
public:
    Rect rect;
    int prow;
    int pcol;
    UIObject() {}
    UIObject(Rect r) : rect(r) {}
    UIObject(int _prow, int _pcol) : prow(_prow), pcol(_pcol) {}
    void setRect(Rect r);
    virtual void draw(UnitChar **, int, int) = 0;
};

class ConsoleUI
{
public:
    int height;
    int width;
    vector<UIObject *> uioj;

    UnitChar **formatDisplay;

    CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
    HANDLE hout;

    ConsoleUI(int height, int widht);
    ~ConsoleUI();
    void SetWindow(int Width, int Height);
    void ClearScreen();
    void draw();
    void display();
};

class TextBox : public UIObject
{
public:
    string text;
    TextBox(int _prow, int _pcol) : UIObject(_prow, _pcol) {}
    void draw(UnitChar **, int, int) override;
};

class Image : public UIObject
{
public:
    Image(int _prow, int _pcol) : UIObject(_prow, _pcol) {}
    vector<vector<UnitChar>> image;
    void draw(UnitChar **, int, int) override;
    void setImage(string path);
};

class InputBox : public UIObject
{
public:
    string prompt;
    string eprompt;
    InputBox(int height, int width);
    void draw(UnitChar **, int, int) override;
    template <class... T>
    tuple<T...> getInput(function<bool(tuple<T...> &)> check)
    {
        tuple<T...> inp;
        cout << CSI << this->prow + 1 << ";0H";
        cout << prompt << flush;
        while (1)
        {
            stringstream ssin;
            string rawInput;

            cout << CSI + to_string((int)SGR::brightYellow) + "m" << flush;

            getline(cin, rawInput);
            ssin << rawInput;
            cout << CSI "0m" << flush;

            apply([&ssin](auto &...x)
                  { (ssin >> ... >> x); },
                  inp);

            // this_thread::sleep_for(chrono::milliseconds(1));

            if (ssin.rdbuf()->in_avail() != 0 || ssin.fail() || !check(inp))
            {
                ssin.clear();
                cout << CSI "1F" CSI "0J" << eprompt << flush;
                continue;
            }
            break;
        }
        return inp;
    }
};
