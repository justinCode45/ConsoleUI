#include "UIObject.hpp"
#include <tuple>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <functional>

// using namespace std; 

template <class... T>
tuple<T...> InputBox::getInput(function<bool(tuple<T...> &)> check)
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