// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT1L
// Names: TAN HUI JEEN | TEH YVONNE
// IDs: 1211101196 | 1211100571
// Emails: 1211101196@student.mmu.edu.my | 1211100571@student.mmu.edu.my
// Phones: 60163592283 | 60193317457
// *********************************************************

#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <unordered_set>

using namespace std;

void Customisation(int &boardRows, int &boardColumns, int &zombieCount, string &commands);
void displayBoard(int &boardRows, int &boardColumns, int &zombieCount, string &commands);
void Usercommands(string &commands, int &boardRows, int &boardColumns, int &zombieCount);

class Alien
{
public:
    int initial_life;
    int initial_attack;

    Alien()
    {
        initial_life = 100;
        initial_attack = 0;
    }
};

class Zombie
{
public:
    vector<int> life;
    vector<int> attack;
    vector<int> range;

    Zombie()
    {
        // initialize random seed
        life = {35, 50, 70, 80, 95, 100, 120, 150, 250};
        attack = {10, 20, 30, 40, 50, 60};
        range = {1, 2, 3};
    }
};

// Deafult Game Settings
void gameSettings(int boardRows, int boardColumns, int zombieCount, string &commands)
{
    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    :" << boardRows << endl;
    cout << "Board Columns :" << boardColumns << endl;
    cout << "Zombie Count  :" << zombieCount << endl;
    cout << endl;

    // User input y or n to change settings:
    char changeSettings;
    cout << "Do you wish to change the game settings (y/n) ? => ";
    cin >> changeSettings;

    if (changeSettings == 'y' || changeSettings == 'Y')
    {
        system("pause");

        system("cls");
        Customisation(boardRows, boardColumns, zombieCount, commands);
    }
    else if (changeSettings == 'n' || changeSettings == 'N')
    {
        system("pause");

        system("cls");
        displayBoard(boardRows, boardColumns, zombieCount, commands);
    }
    else
    {
        cout << endl << "Please enter (y/n). " << endl;
        system("pause");
        system("cls");
        gameSettings(boardRows, boardColumns, zombieCount, commands);
    }

    cout << endl;
    return;
}

// Game Settings Customisation:
void Customisation(int &boardRows, int &boardColumns, int &zombieCount, string &commands)
{
    cout << "Please fill in your desire settings!" << endl;
    cout << "-------------------------------------" << endl;

    // Customise Board Rows:
    bool bR = false;
    while (bR == false)
    {
        cout << "Enter rows    (odd number > 2) => ";
        cin >> boardRows;
        cout << endl;

        if (boardRows < 3 || boardRows % 2 == 0)
        {
            cout << "Please enter an odd number larger than 2." << endl;
            cout << endl;
        }
        else
        {
            bR = true;
        }
    }

    // Customise Board Columns:
    bool bC = false;
    while (bC == false)
    {
        cout << "Enter columns (odd number > 8) => ";
        cin >> boardColumns;
        cout << endl;

        if (boardColumns < 9 || boardColumns % 2 == 0)
        {
            cout << "Please enter an odd number larger than 8." << endl;
            cout << endl;
        }
        else
        {
            bC = true;
        }
    }

    // Customise Zombie Count:
    bool zC = false;
    while (zC == false)
    {
        cout << "Enter Zombie Counts (max 9)    => ";
        cin >> zombieCount;
        cout << endl;

        if (zombieCount > 9 || zombieCount == 0)
        {
            cout << "Please enter number betwen 1 to 9." << endl;
            cout << endl;
        }
        else
        {
            zC = true;
        }
    }

    cout << endl;
    cout << "-.-.-.-.-.-.-.-.-.-.-" << endl;
    cout << "- Settings updated. -" << endl;
    cout << "-.-.-.-.-.-.-.-.-.-.-" << endl;
    cout << endl;
    cout << "Board Rows   : " << boardRows << endl
         << "Board Columns: " << boardColumns << endl
         << "Zombie Count : " << zombieCount << endl;

    cout << endl;
    system("pause");

    system("cls");
    displayBoard(boardRows, boardColumns, zombieCount, commands);
}

// Alien and Zombie life, attack and range:
void alienZombie(int &boardRows, int &boardColumns, int &zombieCount)
{
    // Alien's life and attack
    Alien alien;
    cout << "Alien => " << "life: " << alien.initial_life << " , ";
    cout << "attack: " << alien.initial_attack << endl;
    cout << endl;

    // Zombies' life, attack and range
    Zombie zombies;

    // generate random index for life and attack
    int zombieLife[zombieCount];
    int zombieAttack[zombieCount];
    int zombieRange[zombieCount];

    for (int h = 0; h < zombieCount; h++)
    {
        int randomIndex = rand() % zombies.life.size();
        zombieLife[h] = zombies.life[randomIndex];
        randomIndex = rand() % zombies.attack.size();
        zombieAttack[h] = zombies.attack[randomIndex];
        randomIndex = rand() % zombies.range.size();
        zombieRange[h] = zombies.range[randomIndex];

        // print out the random life and attack values
        cout << "Zombie " << h + 1 << " => "
             << "life: " << zombieLife[h] << " , ";
        cout << "attack: " << zombieAttack[h] << " , ";
        cout << "range: " << zombieRange[h] << endl;
        cout << endl;
    }
}

void displayBoard(int &boardRows, int &boardColumns, int &zombieCount, string &commands)
{

    cout << " ";
    int c = boardColumns + 1;
    while (c > 10)
    {
        cout << " ";
        --c;
    }

    cout << ".: Alien vs Zombie :." << endl;

    char arr[boardRows][boardColumns];
    char objects[] = {' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r'};
    int num_objects = 9;

    // Initialize array to all
    for (int x = 0; x < boardRows; x++)
    {
        int middleRow;
        int middleColumn;

        //  Display columns:
        for (int j = 0; j < boardColumns; j++)
        {
            // Display 'A' in the middle:
            if (boardRows % 2 == 0 && boardColumns % 2 == 0)
            {
                middleRow = boardRows / 2;
                middleColumn = boardColumns / 2;
            }
            else if (boardRows % 2 == 0)
            {
                middleRow = boardRows / 2;
                middleColumn = (boardColumns - 1) / 2;
            }
            else if (boardColumns % 2 == 0)
            {
                middleRow = (boardRows - 1) / 2;
                middleColumn = boardColumns / 2;
            }
            else
            {
                middleRow = (boardRows - 1) / 2;
                middleColumn = (boardColumns - 1) / 2;
            }
            arr[middleRow][middleColumn] = 'A';

            // Empty out the middle space for 'A':
            if (x == middleRow && j == middleColumn)
            {
                continue;
            }

            int index = rand() % num_objects;
            arr[x][j] = objects[index];
        }
    }

    // Place zombies randomly in the array:
    srand(time(0));
    int g = zombieCount;
    int x = 0;
    unordered_set<string> usedCoordinates;

    while (x < g)
    {
        int a = rand() % boardRows;
        int y = rand() % boardColumns;
        string coordinate = to_string(a) + "," + to_string(y);

        // print A before printing zombies and m
        if (arr[a][y] == 'A' || arr[a][y] != 'Z' && usedCoordinates.count(coordinate) == 0)
        {
            arr[a][y] = x + '0' + 1;
            usedCoordinates.insert(coordinate);
            x++;
        }
    }
    
    //  Print the array
    for (int x = 0; x < boardRows; x++)
    {
        cout << "  ";
        for (int z = 0; z < boardColumns; z++)
        {
            cout << "+-";
        }
        cout << "+";
        cout << endl;

        cout << setw(2) << (x + 1);

        for (int j = 0; j < boardColumns; j++)
        {
            cout << "|" << arr[x][j];
        }
        cout << "|";
        cout << endl;
    }

    // Display last horizontal line:
    cout << "  ";
    for (int z = 0; z < boardColumns; z++)
    {
        cout << "+-";
    }
    cout << "+";
    cout << endl;

    // Display column numbers:
    cout << "  ";
    for (int x = 0; x < boardColumns; ++x)
    {
        int digit = (x + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int x = 0; x < boardColumns; ++x)
    {
        cout << " " << (x + 1) % 10;
    }
    cout << endl;
    cout << endl;

    alienZombie(boardRows, boardColumns, zombieCount);
    Usercommands(commands, boardRows, boardColumns, zombieCount);
    return;
}

// Display Help Command:
void help(string &commands, int &boardRows, int &boardColumns, int &zombieCount)
{
    cout << "1. up    - Move up." << endl;
    cout << "2. down  - Move down." << endl;
    cout << "3. left  - Move left." << endl;
    cout << "4. right - Move right." << endl;
    cout << "5. arrow - Switch the direction of arrow." << endl;
    cout << "6. save  - Save the current game." << endl;
    cout << "7. load  - Load a saved game." << endl;
    cout << "8. Quit  - Quit the game." << endl;

    cout << endl;
    system("pause");
    system("cls");

    displayBoard(boardRows, boardColumns, zombieCount, commands);
    return;
}

void moves(string controls)
{
    if (controls == "^" || controls == "v" || controls == "<" || controls == ">")
    {
        cout << "Alien finds an arrow." << endl;
        cout << "Alien's attack is incresed by 20. " << endl;
    }
    if (controls == "p")
    {
        cout << "Alien finds a pod." << endl;
        cout << "Zombie"
             << "receives a damage of 10. " << endl;
    }
    if (controls == "h")
    {
        cout << "Alien finds a health pack." << endl;
        cout << "Alien's life is increased by 20" << endl;
    }
}

void Usercommands(string &commands, int &boardRows, int &boardColumns, int &zombieCount)
{
    bool Uc = true;

    while (Uc != false)
    {

        cout << "Command => ";
        cin >> commands;
        cout << endl;

        if (commands == "help")
        {
            help(commands, boardRows, boardColumns, zombieCount);
            cout << endl;
        }

        if (commands == "up")
        {
            break;
        }
        if (commands == "down")
        {
            break;
        }

        if (commands == "left")
        {
            break;
        }

        if (commands == "right")
        {
            break;
        }

        if (commands == "arrow")
        {
            break;
        }

        if (commands == "save")
        {
            break;
        }

        if (commands == "load")
        {
            break;
        }

        if (commands == "quit")
        {
            string exit;
            cout << "Are you sure you want to quit the current game? (y/n) => ";
            cin >> exit;

            if (exit == "y" || exit == "Y")
            {
                cout << endl
                     << "Goodbye, See you again!" << endl;
                cout << endl;
                system("pause");
                break;
            }
            else if (exit == "n" || exit == "N")
            {
                return Usercommands(commands, boardRows, boardColumns, zombieCount);
            }
            break;
        }
    }
}

int main()
{
    // Default Settings :
    int boardRows = 5;
    int boardColumns = 9;
    int zombieCount = 1;
    string commands;

    gameSettings(boardRows, boardColumns, zombieCount, commands);
    
}



