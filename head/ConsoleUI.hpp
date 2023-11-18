#ifndef CONSOLEUI_HPP
#define CONSOLEUI_HPP

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
#include "Gengral.hpp"
#include "UnitChar.hpp"


using namespace std;

#define ESC '\x1b'

typedef tuple<double, double, int> Tddi;


vector<vector<UnitChar>> convetStringtoUnitChar(string s);

void decodeColor(string temp, variant<FSGR, int> &resultF, variant<BSGR, int> &resultB);
class Rect
{
public:
    int top, left, bottom, right;
    Rect(int top_, int left_, int bottom_, int right_) : top(top_), left(left_), bottom(bottom_), right(right_) {}
    Rect() : top(0), left(0), bottom(0), right(0) {}
};

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



#endif