#define CSI "\x1b["
#include <string>
#include <tuple>
#include <functional>
#include <thread>
#include <sstream>
#include <iostream>

using namespace std; 



template <class... T>
tuple<T...> getInput(function<bool(tuple<T...> &)> check, string prompt, string eprompt)
{
    tuple<T...> inp;

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

        this_thread::sleep_for(chrono::milliseconds(1));

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

template <class... T>
std::string color(std::string in, T... c)
{
    std::string out = CSI;
    ((out += std::to_string((int)c) + ';'), ...);
    out.pop_back();
    out += 'm' + in + CSI "0m";
    return out;
}