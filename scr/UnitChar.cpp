#include "../head/UnitChar.hpp"

UnitChar::UnitChar()
{
    c = ' ';
    colorF = FSGR::white;
    colorB = 232;
}

void UnitChar::setColorF(int c256)
{
    colorF = c256;
}

void UnitChar::setColorF(FSGR x)
{
    colorF = x;
}

void UnitChar::setColorF(variant<FSGR, int> x)
{
    colorF = x;
}

void UnitChar::setColorB(int c256)
{
    colorB = c256;
}

void UnitChar::setColorB(BSGR x)
{
    colorB = x;
}

void UnitChar::setColorB(variant<BSGR, int> x)
{
    colorB = x;
}

string UnitChar::toString()
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

void UnitChar::claer()
{
    c = ' ';
    colorF = FSGR::white;
    colorB = 232;
}

void UnitChar::setChar(char c_)
{
    c = c_;
}