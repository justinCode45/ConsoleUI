#include "../head/ConsoleUI.hpp"

ConsoleUI::ConsoleUI(int _height, int _weight)
{
    std::ios_base::sync_with_stdio(false);
    cout << CSI "?1049h";

    hout = GetStdHandle(STD_OUTPUT_HANDLE);

    height = _height;
    width = _weight;
    SetWindow(width, height);

    formatDisplay = new UnitChar *[height];
    for (int i = 0; i < height; i++)
    {
        formatDisplay[i] = new UnitChar[width];
    }
}

ConsoleUI::~ConsoleUI()
{
    delete[] formatDisplay;
    for (auto i : uioj)
    {
        delete i;
    }
    cout << CSI "?1049l";
}

void ConsoleUI::display()
{
    cout << CSI << "H";
    this->draw();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << formatDisplay[i][j].toString();
        }
        if (i != height - 1)
            std::cout << '\n';
    }
    std::cout << std::flush;
}

void ConsoleUI::SetWindow(int Width, int Height)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    SetConsoleScreenBufferSize(hout, coord); // Set Buffer Size
    SetConsoleWindowInfo(hout, TRUE, &Rect); // Set Window Size
}

void ConsoleUI::ClearScreen()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hout, &csbi))
        return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
            hout,
            (TCHAR)' ',
            cellCount,
            homeCoords,
            &count))
        return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
            hout,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count))
        return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hout, homeCoords);
}

void ConsoleUI::draw()
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            formatDisplay[i][j].claer();
        }
    }
    for (int i=0;i< uioj.size();i++)
    {
        uioj[i]->draw(formatDisplay, height, width);
    }
}


void UIObject::setRect(Rect r)
{
    rect = r;
    prow = rect.top;
    pcol = rect.left;
}



vector<vector<UnitChar>> convetStringtoUnitChar(string s)
{
    std::stringstream ss(s);
    variant<FSGR, int> nowColorF = FSGR::white;
    variant<BSGR, int> nowColorB = 232;
    vector<vector<UnitChar>> result;
    string line;
    while (getline(ss, line))
    {
        // deal each line
        // cout << "dd1" << endl;
        bool check = 0;
        string temp = "";
        result.push_back(vector<UnitChar>());
        // cout << "dd2" << endl;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == 'm' && check)
            {
                decodeColor(temp, nowColorF, nowColorB);
                check = 0;
                temp.clear();
                continue;
            }
            if (check)
            {
                temp += line[i];
            }
            if (line[i] == '\x1b')
                check = 1;
            if (!check)
            {
                result.back().push_back(UnitChar());
                result.back().back().setChar(line[i]);
                result.back().back().setColorF(nowColorF);
                result.back().back().setColorB(nowColorB);
            }
            // cout << "dd4" << endl;
        }
    }
    return result;
}

void decodeColor(string temp, variant<FSGR, int> &resultF, variant<BSGR, int> &resultB)
{
    stringstream ss(temp);
    int nowi;
    char trash;
    while (!ss.eof())
    {
        ss >> trash;
        ss >> nowi;
        switch (nowi)
        {
        case 38: // F
            ss >> trash >> trash >> trash >> nowi;
            //   ;       5      ;     231
            resultF = nowi;
            // cout<<nowi<<endl;
            break;
        case 48: // B
            ss >> trash >> trash >> trash >> nowi;
            //   ;       5      ;     231
            resultB = nowi;
            break;
        case 0:
            resultF = FSGR::white;
            resultB = 232;
            break;
        default: // xx
            resultF = (FSGR)nowi;
            break;
        }
    }
    // resultF=SGR::white;
    // resultB=SGR::black;
}



