#ifndef GENGRAL_HPP
#define GENGRAL_HPP

#define CSI "\x1b["
#include <string>
#include <tuple>
#include <functional>
#include <thread>

using namespace std;

enum class FSGR
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

enum class BSGR
{
    black = 40,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white,
    brightBlack = 100,
    brightRed,
    brightGreen,
    brightYellow,
    brightBlue,
    brightMagenta,
    brightCyan,
    brightWhite
};



template <class... T>
tuple<T...> getInput(function<bool(tuple<T...> &)> check, string prompt, string eprompt);

template <class... T>
std::string color(std::string in, T... c);

#include "Gengral.tpp"

#endif