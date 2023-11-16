#include <iostream>
#include <fstream>
#include "./head/ConsoleUI.hpp"
#include <cassert>
#include <vector>
#include <thread>
using namespace std;
#define height 50
#define width 150
typedef tuple<double, double, int> Tddi;
int main()
{
    // Image img1(0, 0);
    // Image img2(0, 0);
    // InputBox inp(height, width);
    // TextBox tb(10,5);
    // tb.text = "Hello World";
    // inp.prompt = "Enter " color("height", SGR::brightWhite) " (in cm) and " color("weight", SGR::brightWhite) " (in Kg) and " color("age", SGR::brightWhite) " (3 postive ints) :";
    // inp.eprompt = "Enter " color("height", SGR::brightWhite) " (in cm) and " color("weight", SGR::brightWhite) " (in Kg) and " color("age", SGR::brightWhite) " (" color("3 postive ints", SGR::brightRed) ") :";

    // // img1.setImage("./img/karyl1.ans");
    // img2.setImage("./img/bochi.ans");
    // ConsoleUI cui(height, width);
    // cui.uioj.push_back(&img2);
    // cui.uioj.push_back(&inp);
    // cui.uioj.push_back(&tb);
    // while (1)
    // {
    //     cui.display();
    //     Tddi x = inp.getInput(
    //         (function<bool(Tddi &)>)[](Tddi & in)->bool {
    //             return get<0>(in) > 0 && get<1>(in) > 0 && get<2>(in) > 0;
    //         });
    //     tb.text = "Hello World " + to_string(get<0>(x)) + " " + to_string(get<1>(x)) + " " + to_string(get<2>(x));
        
    //     this_thread::sleep_for(chrono::milliseconds(1000));
    // }
}
