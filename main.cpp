#include <iostream>
#include <thread>
#include <random>
#include <windows.h>
#include "./head/ConsoleUI.hpp"
#include "./head/UnitChar.hpp"
#include "./head/UIobject.hpp"
#include "./head/Gengral.hpp"
#define SHEIGHT 50
#define SWIDTH 150
#define imgsetZ 3

using namespace std;
typedef tuple<double, double, int> Tddi;

const double CM_PRE_INCH = 2.54;
const double KG_PRE_POUND = 0.454;

struct person
{
    int age;
    double height;
    double weight;
    person(double _height, double _weight, int _age)
    {
        age = _age;
        height = _height / CM_PRE_INCH;
        weight = _weight / KG_PRE_POUND;
    }
};

double hatSize(const unique_ptr<person> &p);
double jacketSize(const unique_ptr<person> &p);
double waistSize(const unique_ptr<person> &p);

int main()
{
    int maxRepetitions = 0;
    ConsoleUI prepareUI(SHEIGHT, SWIDTH);
    Image preImage(0, 0);
    InputBox preInput(SHEIGHT, SWIDTH);
    TextBox preText(20, 5);
    preText << "The purpose of this program is to suggest hats,               \n"
            << "jackets, and waist sizes based on the input height and weight.";
    
    preImage.setImage("./img/bochi.ans");
    preInput.prompt = "Enter the maximum of repetitons (an int): ";
    preInput.eprompt = "Enter the maximum of repetitons (" + color("an int", FSGR::brightRed) + "): ";

    prepareUI.uioj.push_back(&preImage);
    prepareUI.uioj.push_back(&preInput);
    prepareUI.uioj.push_back(&preText);

    prepareUI.display();
    maxRepetitions = get<0>(preInput.getInput(
        (function<bool(tuple<int> &)>)[](tuple<int> x)->bool { return get<0>(x) > 0; }));

    ConsoleUI mainUI(SHEIGHT, SWIDTH);
    InputBox dataIn(SHEIGHT, SWIDTH);
    TextBox result1(5, 2);
    TextBox result2(10, 2);

    dataIn.prompt = "Enter " + color("height", FSGR::brightWhite) + " (in cm) and " + color("weight", FSGR::brightWhite) + " (in Kg) and " + color("age", FSGR::brightWhite) + " (3 postive ints) :";
    dataIn.eprompt = "Enter " + color("height", FSGR::brightWhite) + " (in cm) and " + color("weight", FSGR::brightWhite) + " (in Kg) and " + color("age", FSGR::brightWhite) + " (" + color("3 postive ints", FSGR::brightRed) + ") :";
    result1.clear();
    result2.clear();
    string imgPath[imgsetZ] = {
        "karyl1",
        "karyl2",
        "karyl3"};
    Image *imgSet[imgsetZ];

    for (int i = 0; i < imgsetZ; i++)
    {
        imgSet[i] = new Image(5, 60);
        imgSet[i]->setImage("./img/" + imgPath[i] + ".ans");
    }

    mainUI.uioj.push_back(imgSet[0]);
    mainUI.uioj.push_back(&result1);
    mainUI.uioj.push_back(&result2);
    mainUI.uioj.push_back(&dataIn);
   
    for (int k = 0; k < maxRepetitions; k++)
    {
        mainUI.display();
    
        auto [height, weight, age] = dataIn.getInput<double, double, int>(
            (function<bool(Tddi &)>)[](Tddi & in)->bool {
                return get<0>(in) > 0 && get<1>(in) > 0 && get<2>(in) > 0;
            });

        auto p = make_unique<person>(height, weight, age);
        double hat = hatSize(p);
        double jacket = jacketSize(p);
        double waist = waistSize(p);
        result1.clear();
        result2.clear();
        result1 << "You input:                      \n"
                << "Height: " + to_string(height) + " cm\n"
                << "Weight: " + to_string(weight) + " Kg\n"
                << "Age   : " + to_string(age) + " years old\n";

        result2 << "Hat size    : " + color(to_string(hat), FSGR::brightCyan) + "\n"
                << "Jacket size : " + color(to_string(jacket), FSGR::brightCyan) + "\n"
                << "Waist size  : " + color(to_string(waist), FSGR::brightCyan) + "\n";

        mainUI.uioj[0] = imgSet[rand() % imgsetZ];
    }

    return 0;
}

double hatSize(const unique_ptr<person> &p)
{
    return (p->weight / p->height) * 2.9;
}

double jacketSize(const unique_ptr<person> &p)
{
    if (p->age < 30)
        return (p->height * p->weight) / 288.f;
    else
        return (p->height * p->weight) / 288.f + (p->age - 30) / 10 * 0.125;
}

double waistSize(const unique_ptr<person> &p)
{
    if (p->age < 28)
        return p->weight / 5.7;
    else
        return p->weight / 5.7 + (p->age - 28) / 2 * 0.1;
}
