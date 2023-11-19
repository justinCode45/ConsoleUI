#include "../head/UIObject.hpp"
#include "../head/ConsoleUI.hpp"


void TextBox::draw(UnitChar **formatdisplay, int height, int width)
{
    auto formatText = convetStringtoUnitChar(text);
    for (int i = 0; i < formatText.size(); i++)
    {
        for (int j = 0; j < formatText[i].size(); j++)
        {
            if (this->prow + i < height && this->pcol + j < width)
                formatdisplay[this->prow + i][this->pcol + j] = formatText[i][j];
        }
    }
}

TextBox &TextBox::operator<<(string s)
{
    this->text += s;
    return *this;
}

void TextBox::clear()
{
    this->text.clear();
}

void Image::draw(UnitChar **formatdisplay, int height, int width)
{

    for (int i = 0; i < this->image.size(); i++)
    {
        for (int j = 0; j < this->image[i].size(); j++)
        {
            if (this->prow + i < height && this->pcol + j < width)
                formatdisplay[this->prow + i][this->pcol + j] = this->image[i][j];
        }
    }
}

void Image::setImage(string path)
{
    fstream fin(path);
    if (fin.fail())
    {
        cout << "File not found" << endl;
        exit(1);
    }
    string s;
    while (fin)
    {
        string tmp;
        getline(fin, tmp);
        s += tmp + '\n';
    }
    this->image = convetStringtoUnitChar(s);
    this->setRect(Rect(this->prow, this->pcol, this->image.size(), this->image[0].size()));
}

InputBox::InputBox(int height, int width)
{
    this->setRect(Rect(height - 2, 0, height - 1, width));
}

void InputBox::draw(UnitChar **formatdisplay, int height, int width)
{
    for (int i = this->prow; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            formatdisplay[i][j].claer();
        }
    }
}