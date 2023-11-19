#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP

#include "ConsoleUI.hpp"
#include <tuple>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class TextBox : public UIObject
{
public:
    TextBox(int _prow, int _pcol) : UIObject(_prow, _pcol) {}
    void draw(UnitChar **, int, int) override;
    TextBox& operator<<(string s);
    void clear();
    string text;
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
    tuple<T...> getInput(function<bool(tuple<T...> &)> check);
};
#include "UIObject.tpp"

#endif