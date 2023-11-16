#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP
#include "ConsoleUI.hpp"
#include <tuple>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
using std::cin;
using std::string;
using std::tuple;
using std::vector;
using std::stringstream; 


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

            cout << CSI + to_string((int)FSGR::brightYellow) + "m" << flush;

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

#endif