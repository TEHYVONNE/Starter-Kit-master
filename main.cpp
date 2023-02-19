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
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <random>

using namespace std;

class Alien // Alien life and attack
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

struct Alien2 // 'A' movement in the board
{
public:
    int middleRow;
    int middleColumn;
    int boardRows;
    int boardColumns;

    Alien2(int boardRows, int boardColumns)
    {
        this->boardRows = boardRows;
        this->boardColumns = boardColumns;
        middleRow = (boardRows - 1) / 2;
        middleColumn = (boardColumns - 1) / 2;
    }
};

class Zombie // Zombie's life, attack and range
{
public:
    vector<int> life;
    vector<int> attack;
    vector<int> range;
    vector<int> zombieLife;
    vector<int> zombieAttack;
    vector<int> zombieRange;

    Zombie(int zombieCount)
    {
        // initialize random seed
        srand(time(NULL));

        life = {35, 50, 70, 80, 95, 100, 120, 150, 250};
        attack = {10, 20, 30, 40, 50, 60};
        range = {1, 2, 3};

        for (int h = 0; h < zombieCount; h++)
        {
            // generate random index for life and attack
            int randomIndex = rand() % life.size();
            zombieLife.push_back(life[randomIndex]);
            randomIndex = rand() % attack.size();
            zombieAttack.push_back(attack[randomIndex]);
            randomIndex = rand() % range.size();
            zombieRange.push_back(range[randomIndex]);
        }
    }
};

char arr[100][100]; // initialize array to hold board.

void displayCommands(int &boardRows, int &boardColumns, int &zombieCount, string &commands, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir);
void Customisation(int &boardRows, int &boardColumns, int &zombieCount, string &commands, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName);
void displayBoard(int &boardRows, int &boardColumns, int &zombieCount, string &commands, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName);
void Usercommands(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName);
void moves(Alien &alien, Alien2 alien2, int zombieCount, Zombie &zombie, int &boardRows, int &boardColumns);

// Deafult Game Settings
void gameSettings(int boardRows, int boardColumns, int zombieCount, string &commands, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
{

    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    :" << boardRows << endl;
    cout << "Board Columns :" << boardColumns << endl;
    cout << "Zombie Count  :" << zombieCount << endl;
    cout << endl;

    // User input y or n to change settings:
    string changeSettings;
    cout << "Do you wish to change the game settings (y/n) ? => ";
    cin >> changeSettings;

    if (changeSettings == "y" || changeSettings == "Y")
    {
        system("pause");

        system("cls");
        Customisation(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
        // system("pause");
    }
    else if (changeSettings == "n" || changeSettings == "N")
    {
        system("pause");

        system("cls");
        // Title(boardRows, boardColumns, zombieCount, commands);
        displayBoard(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
        //  system("pause");
    }
    else
    {
        cout << endl
             << "Please enter (y/n). " << endl;
        system("pause");
        system("cls");
        gameSettings(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
    }

    cout << endl;
    return;
}

// Game Settings Customisation:
void Customisation(int &boardRows, int &boardColumns, int &zombieCount, string &commands, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
{
    cout << "--------------------------------------" << endl;
    cout << " Please fill in your desire settings! " << endl;
    cout << "--------------------------------------" << endl;

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

    alien2 = Alien2(boardRows, boardColumns);
    cout << endl;
    system("pause");

    system("cls");
    displayBoard(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
}

// Display Alien and Zombie life, attack and range:
void alienZombie(int &boardRows, int &boardColumns, int &zombieCount, Alien &alien, Zombie &zombie, Alien2 &alien2)
{
    if (arr[alien2.middleRow][alien2.middleColumn])
    {

        cout << "-> ";

        // Alien's life and attack
        cout << "Alien => "
             << "life: " << alien.initial_life << " , ";
        cout << "attack: " << alien.initial_attack << endl;
        cout << endl;
    }

    // Zombies' life, attack and range
    bool randomDone = false; // check if randomization of zombie's life, attack and range done or not.
    if (!randomDone)
    {

        for (int h = 0; h < zombieCount; h++)
        {
            int randomIndex = rand() % zombie.life.size();
            zombie.zombieLife.push_back(zombie.life[randomIndex]);
            randomIndex = rand() % zombie.attack.size();
            zombie.zombieAttack.push_back(zombie.attack[randomIndex]);
            randomIndex = rand() % zombie.range.size();
            zombie.zombieRange.push_back(zombie.range[randomIndex]);

            // print zombie life, attack and range:
            cout << "Zombie " << h + 1 << " => "
                 << "life: " << zombie.zombieLife[h] << " , ";
            cout << "attack: " << zombie.zombieAttack[h] << " , ";
            cout << "range: " << zombie.zombieRange[h] << endl;
            cout << endl;
        }
        randomDone = true;
    }
}

bool isGenerated = false; // flag to check if random objects and zombies have already been generated.
// Randomize objects and zombies.
void randomizeZombiesObj(int &zombieCount, int &boardRows, int &boardColumns)
{
    if (!isGenerated)
    {
        srand(time(NULL));
        char objects[] = {' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r'};
        int num_objects = 9;

        // Initialize array to all random objects
        for (int x = 0; x < boardRows; x++)
        {
            for (int j = 0; j < boardColumns; j++)
            {
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
        isGenerated = true;
    }
}

bool centeredA = false; // flag to check if 'A' has been placed in the board or not.
void centerA(int &boardRows, int &boardColumns, Alien2 &alien2)
{
    arr[alien2.middleRow][alien2.middleColumn] = 'A';
    centeredA = true;
}

// Random Objects on Trails, '.' :
void randomTrails(int &boardRows, int &boardColumns, Alien2 &alien2)
{
    srand(time(NULL));
    if (alien2.middleRow == 0 || alien2.boardRows >= boardRows || alien2.middleColumn == 0 || alien2.middleColumn >= boardColumns ||
        arr[alien2.middleRow - 1][alien2.middleColumn] == 'r' || arr[alien2.middleRow + 1][alien2.middleColumn] == 'r' || arr[alien2.middleRow][alien2.middleColumn - 1] == 'r' || arr[alien2.middleRow][alien2.middleColumn + 1] == 'r')
    {
        for (int x = 0; x < boardRows; x++)
        {
            for (int j = 0; j < boardColumns; j++)
            {

                if (arr[x][j] == '.')
                {

                    int randomIndex = rand() % 8;
                    char randomChar = " ^v<>hpr"[randomIndex];
                    arr[x][j] = randomChar;
                }
            }
        }
    }
}

void displayBoard(int &boardRows, int &boardColumns, int &zombieCount, string &commands, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
{
    randomizeZombiesObj(zombieCount, boardRows, boardColumns);
    randomTrails(boardRows, boardColumns, alien2);

    if (!centeredA)
    {
        centerA(boardRows, boardColumns, alien2);
    }

    // Display the title:
    cout << " ";
    int c = boardColumns + 1;
    while (c > 10)
    {
        cout << " ";
        --c;
    }

    cout << ".: Alien vs Zombie :." << endl;

    //  Print the array:
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

    alienZombie(boardRows, boardColumns, zombieCount, alien, zombie, alien2);

    Usercommands(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);

    return;
}

void zombieMove(int &boardRows, int &boardColumns, int &zombieCount, Alien2 &alien2, string &commands, char &controls, Alien &alien, int &row, int &column, char &dir, Zombie &zombie, string &direction, string &fileName)
{
    vector<pair<int, int>> zombieLocations; // Check the location of all zombies
    for (int i = 0; i < boardRows; i++)
    {
        for (int j = 0; j < boardColumns; j++)
        {
            if (arr[i][j] >= '1' && arr[i][j] <= '0' + zombieCount)
            {
                zombieLocations.push_back(make_pair(i, j));
            }
        }
    }

    sort(zombieLocations.begin(), zombieLocations.end(),
         [](pair<int, int> a, pair<int, int> b)
         {
             return arr[a.first][a.second] < arr[b.first][b.second];
         });

    bool zDone = false;
    do
    {
        for (int zombieIndex = 0; zombieIndex < zombieCount; zombieIndex++)
        {

            vector<pair<int, int>> CurrzombieLocations; // Store the location of the current zombie
            for (auto loc : zombieLocations)
            {
                if (arr[loc.first][loc.second] == '1' + zombieIndex)
                {
                    CurrzombieLocations.push_back(loc);
                }
            }

            if (CurrzombieLocations.size() == 0)
            {
                continue;
            }

            srand(time(NULL));
            int zombieDir = rand() % 4;
            pair<int, int> zombieLocation = CurrzombieLocations[rand() % CurrzombieLocations.size()];

            int zombieRow = zombieLocation.first;
            int zombieCol = zombieLocation.second;

            int newRow = zombieRow, newCol = zombieCol;
            string zombieDir1;

            if (zombieDir == 0)
            {
                newRow--;
                zombieDir1 = "up";
                zDone = true;
            }
            else if (zombieDir == 1)
            {
                newCol++;
                zombieDir1 = "right";
                zDone = true;
            }
            else if (zombieDir == 2)
            {
                newRow++;
                zombieDir1 = "down";
                zDone = true;
            }
            else if (zombieDir == 3)
            {
                newCol--;
                zombieDir1 = "left";
                zDone = true;
            }

            bool canMove = true;
            for (auto loc : zombieLocations) // checks if its occupied by other zombies or the alien
            {
                if (loc != zombieLocation && loc.first == newRow && loc.second == newCol || (newRow == alien2.middleRow && newCol == alien2.middleColumn))
                {
                    canMove = false;
                    break;
                }
            }

            if (newRow >= 0 && newRow < boardRows && newCol >= 0 && newCol < boardColumns && arr[newRow][newCol] != arr[alien2.middleRow][alien2.middleColumn] && canMove)
            {
                randomTrails(boardRows, boardColumns, alien2); // Sets trails to random objects.

                arr[zombieRow][zombieCol] = '.'; // Insert '.' to the old position (trail)
                char current = arr[newRow][newCol];
                arr[newRow][newCol] = '1' + zombieIndex; // Move the zombie to the new position
                system("cls");
                displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);

                cout << "Zombie " << zombieIndex + 1 << " moved " << zombieDir1 << "." << endl;

                cout << endl;
                system("pause");
                system("cls");
                displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);

                int dx = newCol - alien2.middleColumn;
                int dy = newRow - alien2.middleRow;
                int distance = sqrt(dx * dx + dy * dy);
                bool inRange = false;
                for (int range : zombie.zombieRange)
                {
                    if (distance <= range)
                    {
                        inRange = true;
                        break;
                    }
                }

                if (inRange)
                {
                    system("cls");
                    displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);

                    cout << "Zombie " << zombieIndex + 1 << " attacks Alien." << endl;
                    cout << "Alien's life is decreased by " << zombie.zombieAttack[zombieIndex] << endl
                         << endl;
                    system("pause");

                    if (alien.initial_life > 0)
                    {
                        alien.initial_life -= zombie.zombieAttack[zombieIndex];

                        if (alien.initial_life == 0)
                        {
                            system("cls");
                            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);

                            alien.initial_life = 0;
                            cout << "Alien lost! Better luck next time!" << endl;
                            string start;
                            cout << "Do you want to play again? (y/n) => ";
                            cin >> start;
                            if (start == "y" || start == "Y")
                            {
                                system("cls");
                                gameSettings(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                            }
                            else if (start == "n" || start == "N")
                            {
                                cout << "Thanks for playing!" << endl
                                     << endl;
                                system("pause");
                                break;
                                zDone = true;
                            }
                            system("pause");
                        }
                    }
                    zDone = true;
                }

                else
                {
                    system("cls");
                    displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
                    cout << "Zombie " << zombieIndex + 1 << " cannot attack Alien because it is out of range." << endl
                         << endl;
                    system("pause");
                    zDone = true;
                }

                system("cls");
                displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
                cout << "Zombie " << zombieIndex + 1 << "'s turn ends." << endl;
                cout << "The trails will be reset." << endl
                     << endl;
                system("pause");
                zDone = true;
            }

            else if (arr[newRow][newCol] == arr[alien2.middleRow][alien2.middleColumn] && !canMove)
            {
                system("cls");
                displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
                cout << "The space where zombie " << zombieIndex + 1 << " wants to go is occupied." << endl;
                cout << "Zombie " << zombieIndex + 1 << "'s turn ends." << endl;
                cout << "The trails will be reset." << endl
                     << endl;
                system("pause");
                zDone = true;
            }

            else if (newRow < 0 || newRow > boardRows || newCol < 0 || newCol > boardColumns)
            {
                system("cls");
                displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
                cout << "The direction where zombie " << zombieIndex + 1 << " wants to go is beyond border." << endl;
                cout << "Zombie " << zombieIndex + 1 << "'s turn ends." << endl;
                cout << "The trails will be reset." << endl
                     << endl;
                system("pause");
                zDone = true;
            }
            zDone = true;
        }

    } while (zDone = false);
}

// Display Help Command:
void help(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
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

    displayBoard(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
    return;
}

void displayCommands(int &boardRows, int &boardColumns, int &zombieCount, string &commands, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir)
{
    randomizeZombiesObj(zombieCount, boardRows, boardColumns);
    // randomTrails(boardRows, boardColumns, alien2);

    if (!centeredA)
    {
        centerA(boardRows, boardColumns, alien2);
    }

    // Display the title:
    cout << " ";
    int c = boardColumns + 1;
    while (c > 10)
    {
        cout << " ";
        --c;
    }

    cout << ".: Alien vs Zombie :." << endl;

    //  Print the array:
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

    alienZombie(boardRows, boardColumns, zombieCount, alien, zombie, alien2);
    return;
}

// Save Current Game:
void saveGame(int &boardRows, int &boardColumns, int &zombieCount, Alien &alien, Alien2 &alien2, Zombie &zombie)
{
    string fileName;
    cout << "Name the game you would like to save (eg: 123.txt) => ";
    cin >> fileName;

    while (fileName.length() < 5 || fileName.substr(fileName.length() - 4) != ".txt")
    {
        cout << endl;
        cout << "Invalid file name. Please enter a file name ending with .txt => ";
        cin >> fileName;
    }

    ofstream saveFile(fileName);
    saveFile << boardRows << " " << boardColumns << endl; // Save the board dimensions

    saveFile << alien.initial_life << " " << alien.initial_attack << endl; // Save the alien's current life and attack

    saveFile << zombieCount << endl; // Save the number of zombies

    for (int h = 0; h < zombieCount; h++) // Save zombie(s)'s life, attack and range value
    {
        saveFile << zombie.zombieLife[h] << " " << zombie.zombieAttack[h] << " " << zombie.zombieRange[h] << endl;
    }

    for (int x = 0; x < boardRows; x++) // Save the board
    {
        for (int j = 0; j < boardColumns; j++)
        {
            saveFile << arr[x][j]; // prob
        }
        saveFile << endl;
    }

    saveFile.close(); // Close the file

    cout << "Game Saved!" << endl
         << endl;
    system("pause");
}

// Load saved game:
void loadGame(int &boardRows, int &boardColumns, int &zombieCount, string &fileName, Alien &alien, Alien2 &alien2, Zombie &zombie)
{
    cout << "Enter the file name (including.txt) => ";
    cin >> fileName;

    while (fileName.length() < 5 || fileName.substr(fileName.length() - 4) != ".txt")
    {
        cout << endl;
        cout << "Invalid file name. Please enter a file name ending with .txt => ";
        cin >> fileName;
    }

    ifstream loadFile(fileName);
    loadFile >> boardRows >> boardColumns; // Read the board dimensions from the file

    loadFile >> alien.initial_life >> alien.initial_attack; // Read the alien's life and attack from the file

    loadFile >> zombieCount; // Read the number of zombies from the file

    for (int h = 0; h < zombieCount; h++) // Save zombie(s)'s life, attack and range value
    {
        loadFile >> zombie.zombieLife[h] >> zombie.zombieAttack[h] >> zombie.zombieRange[h];
    }

    string Row; // Board
    getline(loadFile, Row);
    for (int x = 0; x < boardRows; x++)
    {
        getline(loadFile, Row);
        for (int j = 0; j < boardColumns; j++)
        {
            arr[x][j] = Row[j];
        }
    }

    loadFile.close(); // Close the file

    cout << "Game loaded successfully." << endl
         << endl;
    system("pause");
}

void moves(Alien &alien, Alien2 alien2, int zombieCount, Zombie &zombie, int &boardRows, int &boardColumns)
{
    vector<pair<int, int>> zombieLocations; // Check the location of zombies
    for (int i = 0; i < boardRows; i++)
    {
        for (int j = 0; j < boardColumns; j++)
        {
            if (arr[i][j] >= '1' && arr[i][j] <= '0' + zombieCount)
            {
                zombieLocations.push_back(make_pair(i, j));
            }
        }
    }

    if (arr[alien2.middleRow][alien2.middleColumn] == '^' || arr[alien2.middleRow][alien2.middleColumn] == 'v' || arr[alien2.middleRow][alien2.middleColumn] == '<' || arr[alien2.middleRow][alien2.middleColumn] == '>')
    {
        cout << "Alien finds an arrow." << endl;
        cout << "Alien's attack is incresed by 20. " << endl;
        cout << endl;
        alien.initial_attack += 20; // Add 20 to alien's attack value.
    }

    if (arr[alien2.middleRow][alien2.middleColumn] == 'p')
    {
        cout << "Alien finds a pod." << endl;

        sort(zombieLocations.begin(), zombieLocations.end(),
             [](pair<int, int> a, pair<int, int> b)
             {
                 return arr[a.first][a.second] < arr[b.first][b.second];
             });

        // Find the zombie nearest to the alien
        int minDistance = INT_MAX;
        int nearestZombieIndex = -1;
        for (int zombieIndex = 0; zombieIndex < zombieCount; zombieIndex++)
        {
            bool isZombie[boardRows][boardColumns]; // Store zombie's location
            fill(&isZombie[0][0], &isZombie[0][0] + boardRows * boardColumns, false);
            for (int i = 0; i < zombieLocations.size(); i++)
            {
                int r = zombieLocations[i].first + 1;
                int c = zombieLocations[i].second + 1;
                isZombie[r][c] = true; // Set the value of the current location to true.
                int distance = abs(alien2.middleRow - r) + abs(alien2.middleColumn - c);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    nearestZombieIndex = i;
                }
            }
        }

        if (nearestZombieIndex != -1)
        {
            // Attack the nearest zombie
            cout << "Zombie " << nearestZombieIndex + 1 << " receives a damage of 10." << endl
                 << endl;
            zombie.zombieLife[nearestZombieIndex] -= 10;
            if (zombie.zombieLife[nearestZombieIndex] == 0)
            {
                cout << "Zombie " << nearestZombieIndex + 1 << " lost." << endl
                     << endl;
            }
        }
    }

    if (arr[alien2.middleRow][alien2.middleColumn] == 'h')
    {
        cout << "Alien finds a health pack." << endl;
        cout << "Alien's life is increased by 20" << endl;
        cout << endl;
        if (alien.initial_life < 100)
        {
            alien.initial_life += 20; // Add 20 to alien's life value.

            if (alien.initial_life == 100)
            {
                alien.initial_life = 100; // Alien's life value stay as 100.
            }
        }
    }

    if (arr[alien2.middleRow][alien2.middleColumn] == ' ')
    {
        cout << "Alien finds an empty space. " << endl;
        cout << endl;
    }

    if (arr[alien2.middleRow][alien2.middleColumn] == '.')
    {
        cout << "Alien finds an empty space. " << endl;
        cout << endl;
    }

    if (arr[alien2.middleRow][alien2.middleColumn] == '@') // Additional
    {
        cout << "Alien finds a x2 attack. " << endl;
        cout << "Alien's attack is increased 2 times." << endl;
        cout << endl;
        alien.initial_attack *= 2; // Multiple 2 to alien's attack value.
    }

    system("pause");
    cout << endl;
}

void updateArrow(int &row, int &column, string &direction)
{
    while (true)
    {
        cout << "Please enter row, column and direction (eg : 3 5 left) => ";
        cin >> row >> column >> direction;

        if (arr[row - 1][column - 1] == '^' || arr[row - 1][column - 1] == 'v' || arr[row - 1][column - 1] == '<' || arr[row - 1][column - 1] == '>')
        {
            if (direction == "up")
            {
                arr[row - 1][column - 1] = '^';
            }

            else if (direction == "down")
            {
                arr[row - 1][column - 1] = 'v';
            }

            else if (direction == "left")
            {
                arr[row - 1][column - 1] = '<';
            }

            else if (direction == "right")
            {
                arr[row - 1][column - 1] = '>';
            }
            else
            {
                cout << endl;
                cout << "Please enter a valid direction." << endl;
                cout << endl;
                return updateArrow(row, column, direction);
            }
            break;
        }

        else
        {
            cout << endl;
            cout << "Invalid row, column or direction. Please enter again." << endl;
            cout << endl;
            system("pause");
            cout << endl;
            return updateArrow(row, column, direction);
        }
    }
    cout << endl;
    system("pause");
}

// calling functions:
void arrowDown(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName);
void arrowUp(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName);
void arrowRight(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName);

void arrowLeft(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
{
    vector<pair<int, int>> zombieLocations; // Check the location of zombies
    for (int i = 0; i < boardRows; i++)
    {
        for (int j = 0; j < boardColumns; j++)
        {
            if (arr[i][j] >= '1' && arr[i][j] <= '0' + zombieCount)
            {
                zombieLocations.push_back(make_pair(i, j));
            }
        }
    }

    bool isZombie[boardRows][boardColumns]; // Store zombie's location
    fill(&isZombie[0][0], &isZombie[0][0] + boardRows * boardColumns, false);
    for (int i = 0; i < zombieLocations.size(); i++)
    {
        int r = zombieLocations[i].first;
        int c = zombieLocations[i].second;
        isZombie[r][c] = true; // Set the value of the current location to true.
    }

    bool done = false;
    do
    {
        while (alien2.middleColumn > 0 && !isZombie[alien2.middleRow][alien2.middleColumn - 1] && arr[alien2.middleRow][alien2.middleColumn - 1] != 'r')
        {
            arr[alien2.middleRow][alien2.middleColumn] = '.';
            alien2.middleColumn -= 1; // Move 'A' left by decreasing the column index.
            moves(alien, alien2, zombieCount, zombie, boardRows, boardColumns);
            char current = arr[alien2.middleRow][alien2.middleColumn];
            arr[alien2.middleRow][alien2.middleColumn] = 'A';
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);

            if (current == '^')
            {
                arrowUp(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }

            else if (current == '>')
            {
                arrowRight(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }

            else if (current == 'v')
            {
                arrowDown(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }
            done = true;
        }

        if (alien2.middleColumn == 0)
        {
            cout << "Cannot move 'A' left, it is already at the last column." << endl
                 << endl;
            system("pause");
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
            cout << "Alien's turn ends. The trails will be reset." << endl
                 << endl;
            system("pause");
            alien.initial_attack = 0;

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }

        else if (isZombie[alien2.middleRow][alien2.middleColumn - 1])
        {
            sort(zombieLocations.begin(), zombieLocations.end(),
                 [](pair<int, int> a, pair<int, int> b)
                 {
                     return arr[a.first][a.second] < arr[b.first][b.second];
                 });

            int zombieIndex = -1;
            for (int i = 0; i < zombieCount; i++)
            {
                if (zombieLocations[i].first == alien2.middleRow && zombieLocations[i].second == alien2.middleColumn - 1)
                {
                    zombieIndex = i;
                    break;
                }
            }

            if (zombieIndex != -1)
            {
                // Attack the zombie
                cout << "Alien attacks Zombie " << zombieIndex + 1 << "." << endl;
                cout << "Zombie " << zombieIndex + 1 << " receives a damage of " << alien.initial_attack << "." << endl
                     << endl;

                zombie.zombieLife[zombieIndex] -= alien.initial_attack;

                if (zombie.zombieLife[zombieIndex] > 0)
                {
                    cout << "Zombie " << zombieIndex + 1 << " still alive." << endl;
                    system("pause");
                    break;
                    done = true;
                }
                if (zombie.zombieLife[zombieIndex] <= 0)
                {
                    zombie.zombieLife[zombieIndex] = 0;
                    cout << "Zombie " << zombieIndex + 1 << " lost." << endl
                         << endl;
                    system("pause");
                    break;
                    done = true;
                }
                done = true;
                alien.initial_attack = 0;
            }
            system("pause");

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }

        else if (arr[alien2.middleRow][alien2.middleColumn - 1] == 'r')
        {
            cout << "Alien hit a rock." << endl
                 << endl;

            srand(time(NULL));
            int randomIndex = rand() % 8;
            char randomChar = " ^v<>hp@"[randomIndex];
            arr[alien2.middleRow][alien2.middleColumn - 1] = randomChar;
            cout << "You have found '" << randomChar << "' under the rock!" << endl
                 << endl;

            system("pause");
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
            cout << "Alien's turn ends. The trails will be reset." << endl
                 << endl;
            alien.initial_attack = 0;

            system("pause");
            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }
    } while (done = false);
}

void arrowRight(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
{
    vector<pair<int, int>> zombieLocations; // Check the location of zombies
    for (int i = 0; i < boardRows; i++)
    {
        for (int j = 0; j < boardColumns; j++)
        {
            if (arr[i][j] >= '1' && arr[i][j] <= '0' + zombieCount)
            {
                zombieLocations.push_back(make_pair(i, j));
            }
        }
    }

    bool isZombie[boardRows][boardColumns]; // Store zombie's location
    fill(&isZombie[0][0], &isZombie[0][0] + boardRows * boardColumns, false);
    for (int i = 0; i < zombieLocations.size(); i++)
    {
        int r = zombieLocations[i].first;
        int c = zombieLocations[i].second;
        isZombie[r][c] = true; // Set the value of the current location to true.
    }

    bool done = false;
    do
    {
        while (alien2.middleColumn < (boardColumns - 1) && !isZombie[alien2.middleRow][alien2.middleColumn + 1] && arr[alien2.middleRow][alien2.middleColumn + 1] != 'r')
        {
            arr[alien2.middleRow][alien2.middleColumn] = '.';
            alien2.middleColumn += 1; // Move 'A' right by increasing the column index.
            moves(alien, alien2, zombieCount, zombie, boardRows, boardColumns);
            char current = arr[alien2.middleRow][alien2.middleColumn];
            arr[alien2.middleRow][alien2.middleColumn] = 'A';
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);

            if (current == '<')
            {
                arrowLeft(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }

            else if (current == '^')
            {
                arrowUp(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }

            else if (current == 'v')
            {
                arrowDown(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }
            done = true;
        }

        if (alien2.middleColumn + 1 == boardColumns)
        {
            cout << "Cannot move 'A' right, it is already at the last column." << endl
                 << endl;
            system("pause");
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
            cout << "Alien's turn ends. The trails will be reset." << endl
                 << endl;
            system("pause");
            alien.initial_attack = 0;

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }

        else if (isZombie[alien2.middleRow][alien2.middleColumn + 1])
        {
            sort(zombieLocations.begin(), zombieLocations.end(),
                 [](pair<int, int> a, pair<int, int> b)
                 {
                     return arr[a.first][a.second] < arr[b.first][b.second];
                 });

            int zombieIndex = -1;
            for (int i = 0; i < zombieCount; i++)
            {
                if (zombieLocations[i].first == alien2.middleRow && zombieLocations[i].second == alien2.middleColumn + 1)
                {
                    zombieIndex = i;
                    break;
                }
            }

            if (zombieIndex != -1)
            {
                // Attack the zombie
                cout << "Alien attacks Zombie " << zombieIndex + 1 << "." << endl;
                cout << "Zombie " << zombieIndex + 1 << " receives a damage of " << alien.initial_attack << "." << endl
                     << endl;
                zombie.zombieLife[zombieIndex] -= alien.initial_attack;
                if (zombie.zombieLife[zombieIndex] > 0)
                {
                    cout << "Zombie " << zombieIndex + 1 << " still alive." << endl;
                    system("pause");
                    break;
                    done = true;
                }
                if (zombie.zombieLife[zombieIndex] <= 0)
                {
                    zombie.zombieLife[zombieIndex] = 0;
                    cout << "Zombie " << zombieIndex + 1 << " lost." << endl
                         << endl;
                    system("pause");
                    break;
                    done = true;
                }
                alien.initial_attack = 0;
                done = true;
            }
            system("pause");

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }

        else if (arr[alien2.middleRow][alien2.middleColumn + 1] == 'r')
        {
            cout << "Alien hit a rock." << endl
                 << endl;

            srand(time(NULL));
            int randomIndex = rand() % 8;
            char randomChar = " ^v<>hp@"[randomIndex];
            arr[alien2.middleRow][alien2.middleColumn + 1] = randomChar;
            cout << "You have found '" << randomChar << "' under the rock!" << endl
                 << endl;

            system("pause");
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
            cout << "Alien's turn ends. The trails will be reset." << endl
                 << endl;
            alien.initial_attack = 0;
            system("pause");

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }
    } while (done = false);
}

void arrowUp(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
{
    vector<pair<int, int>> zombieLocations; // Check the location of zombies
    for (int i = 0; i < boardRows; i++)
    {
        for (int j = 0; j < boardColumns; j++)
        {
            if (arr[i][j] >= '1' && arr[i][j] <= '0' + zombieCount)
            {
                zombieLocations.push_back(make_pair(i, j));
            }
        }
    }

    bool isZombie[boardRows][boardColumns]; // Store zombie's location
    fill(&isZombie[0][0], &isZombie[0][0] + boardRows * boardColumns, false);
    for (int i = 0; i < zombieLocations.size(); i++)
    {
        int r = zombieLocations[i].first;
        int c = zombieLocations[i].second;
        isZombie[r][c] = true; // Set the value of the current location to true.
    }

    bool done = false;
    do
    {
        while (alien2.middleRow > 0 && !isZombie[alien2.middleRow - 1][alien2.middleColumn] && arr[alien2.middleRow - 1][alien2.middleColumn] != 'r') //'A' moves until it hits the border or a rock or a zombie.
        {
            arr[alien2.middleRow][alien2.middleColumn] = '.'; // Replace the character at the current position of 'A' with a dot.
            alien2.middleRow -= 1;                            // Move 'A' up by decreasing the row index.
            moves(alien, alien2, zombieCount, zombie, boardRows, boardColumns);
            char current = arr[alien2.middleRow][alien2.middleColumn];
            arr[alien2.middleRow][alien2.middleColumn] = 'A'; // Update the new position of 'A'.
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);

            if (current == '<')
            {
                arrowLeft(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }

            else if (current == '>')
            {
                arrowRight(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }

            else if (current == 'v')
            {
                arrowDown(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }
            done = true;
        }

        if (alien2.middleRow == 0)
        {
            cout << "Cannot move 'A' up, it is already at the top row." << endl
                 << endl;
            system("pause");
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
            cout << "Alien's turn ends. The trails will be reset." << endl
                 << endl;
            system("pause");
            alien.initial_attack = 0;

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }

        else if (isZombie[alien2.middleRow - 1][alien2.middleColumn])
        {
            sort(zombieLocations.begin(), zombieLocations.end(),
                 [](pair<int, int> a, pair<int, int> b)
                 {
                     return arr[a.first][a.second] < arr[b.first][b.second];
                 });

            int zombieIndex = -1;
            for (int i = 0; i < zombieCount; i++)
            {
                if (zombieLocations[i].first == alien2.middleRow - 1 && zombieLocations[i].second == alien2.middleColumn)
                {
                    zombieIndex = i;
                    break;
                }
            }

            if (zombieIndex != -1)
            {
                // Attack the zombie
                cout << "Alien attacks Zombie " << zombieIndex + 1 << "." << endl;
                cout << "Zombie " << zombieIndex + 1 << " receives a damage of " << alien.initial_attack << "."
                     << endl
                     << endl;
                zombie.zombieLife[zombieIndex] -= alien.initial_attack;
                if (zombie.zombieLife[zombieIndex] > 0)
                {
                    cout << "Zombie " << zombieIndex + 1 << " still alive." << endl;
                    system("pause");
                    break;
                    done = true;
                }
                if (zombie.zombieLife[zombieIndex] <= 0)
                {
                    zombie.zombieLife[zombieIndex] = 0;
                    cout << "Zombie " << zombieIndex + 1 << " lost." << endl
                         << endl;
                    system("pause");
                    break;
                    done = true;
                }
                alien.initial_attack = 0;
                done = true;
            }
            system("pause");

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }

        else if (arr[alien2.middleRow - 1][alien2.middleColumn] == 'r')
        {
            cout << "Alien hit a rock." << endl
                 << endl;

            srand(time(NULL));
            int randomIndex = rand() % 8;
            char randomChar = " ^v<>hp@"[randomIndex]; // Random object underneath the rock.
            arr[alien2.middleRow - 1][alien2.middleColumn] = randomChar;
            cout << "You have found '" << randomChar << "' under the rock!" << endl
                 << endl;

            system("pause");
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
            cout << "Alien's turn ends. The trails will be reset." << endl
                 << endl;
            alien.initial_attack = 0;
            system("pause");

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }
    } while (done = false);
}

void arrowDown(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
{
    vector<pair<int, int>> zombieLocations; // Check the location of zombies
    for (int i = 0; i < boardRows; i++)
    {
        for (int j = 0; j < boardColumns; j++)
        {
            if (arr[i][j] >= '1' && arr[i][j] <= '0' + zombieCount)
            {
                zombieLocations.push_back(make_pair(i, j));
            }
        }
    }

    bool isZombie[boardRows][boardColumns]; // Store zombie's location
    fill(&isZombie[0][0], &isZombie[0][0] + boardRows * boardColumns, false);
    for (int i = 0; i < zombieLocations.size(); i++)
    {
        int r = zombieLocations[i].first;
        int c = zombieLocations[i].second;
        isZombie[r][c] = true; // Set the value of the current location to true.
    }

    bool done = false;
    do
    {
        while (alien2.middleRow < (boardRows - 1) && !isZombie[alien2.middleRow + 1][alien2.middleColumn] && arr[alien2.middleRow + 1][alien2.middleColumn] != 'r')
        {
            arr[alien2.middleRow][alien2.middleColumn] = '.';
            alien2.middleRow += 1; // Move 'A' down by increasing the row index.
            moves(alien, alien2, zombieCount, zombie, boardRows, boardColumns);
            char current = arr[alien2.middleRow][alien2.middleColumn];
            arr[alien2.middleRow][alien2.middleColumn] = 'A';
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);

            if (current == '<')
            {
                arrowLeft(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }

            else if (current == '>')
            {
                arrowRight(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }

            else if (current == '^')
            {
                arrowUp(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
                break;
            }
            done = true;
        }

        if (alien2.middleRow + 1 == boardRows)
        {
            cout << "Cannot move 'A' down, it is already at the bottom row." << endl
                 << endl;
            system("pause");
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
            cout << "Alien's turn ends. The trails will be reset." << endl
                 << endl;
            system("pause");
            alien.initial_attack = 0;

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }

        else if (isZombie[alien2.middleRow + 1][alien2.middleColumn])
        {
            sort(zombieLocations.begin(), zombieLocations.end(),
                 [](pair<int, int> a, pair<int, int> b)
                 {
                     return arr[a.first][a.second] < arr[b.first][b.second];
                 });

            int zombieIndex = -1;
            for (int i = 0; i < zombieCount; i++)
            {
                if (zombieLocations[i].first == alien2.middleRow + 1 && zombieLocations[i].second == alien2.middleColumn)
                {
                    zombieIndex = i;
                    break;
                }
            }

            if (zombieIndex != -1)
            {
                // Attack the zombie
                cout << "Alien attacks Zombie " << zombieIndex + 1 << "." << endl;
                cout << "Zombie " << zombieIndex + 1 << " receives a damage of " << alien.initial_attack << "."
                     << endl
                     << endl;
                zombie.zombieLife[zombieIndex] -= alien.initial_attack;
                if (zombie.zombieLife[zombieIndex] > 0)
                {
                    cout << "Zombie " << zombieIndex + 1 << " still alive." << endl;
                    system("pause");
                    break;
                    done = true;
                }
                if (zombie.zombieLife[zombieIndex] <= 0)
                {
                    zombie.zombieLife[zombieIndex] = 0;
                    cout << "Zombie " << zombieIndex + 1 << " lost." << endl
                         << endl;
                    system("pause");
                    break;
                    done = true;
                }
                alien.initial_attack = 0;
                done = true;
            }
            system("pause");

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }

        else if (arr[alien2.middleRow + 1][alien2.middleColumn] == 'r')
        {
            cout << "Alien hit a rock." << endl
                 << endl;

            srand(time(NULL));
            int randomIndex = rand() % 8;
            char randomChar = " ^v<>hp@"[randomIndex];
            arr[alien2.middleRow + 1][alien2.middleColumn] = randomChar;
            cout << "You have found '" << randomChar << "' under the rock!" << endl
                 << endl;

            system("pause");
            system("cls");
            displayCommands(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir);
            cout << "Alien's turn ends. The trails will be reset." << endl
                 << endl;
            alien.initial_attack = 0;
            system("pause");

            zombieMove(boardRows, boardColumns, zombieCount, alien2, commands, controls, alien, row, column, dir, zombie, direction, fileName);
            done = true;
        }
    } while (done = false);
}

void Usercommands(string &commands, int &boardRows, int &boardColumns, int &zombieCount, char &controls, Alien &alien, int &row, int &column, string &direction, Alien2 &alien2, Zombie &zombie, char &dir, string &fileName)
{
    vector<pair<int, int>> zombieLocations; // Check the location of zombies
    for (int i = 0; i < boardRows; i++)
    {
        for (int j = 0; j < boardColumns; j++)
        {
            if (arr[i][j] >= '1' && arr[i][j] <= '0' + zombieCount)
            {
                zombieLocations.push_back(make_pair(i, j));
            }
        }
    }

    bool isZombie[boardRows][boardColumns]; // Store zombie's location
    fill(&isZombie[0][0], &isZombie[0][0] + boardRows * boardColumns, false);
    for (int i = 0; i < zombieLocations.size(); i++)
    {
        int r = zombieLocations[i].first;
        int c = zombieLocations[i].second;
        isZombie[r][c] = true; // Set the value of the current location to true.
    }

    bool Uc = true;
    while (Uc != false)
    {
        cout << "Command [Enter 'help'] => ";
        cin >> commands;
        cout << endl;

        if (commands == "help")
        {

            help(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
            cout << endl;
        }

        if (commands == "up")
        {
            arrowUp(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
            Uc = false;
            system("cls");
        }

        if (commands == "down")
        {
            arrowDown(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
            Uc = false;
            system("cls");
        }

        if (commands == "left")
        {
            arrowLeft(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
            Uc = false;
            system("cls");
        }

        if (commands == "right")
        {
            arrowRight(commands, boardRows, boardColumns, zombieCount, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
            Uc = false;
            system("cls");
        }

        if (commands == "arrow")
        {
            updateArrow(row, column, direction);
            Uc = false;
            system("cls");
        }
        if (commands == "save")
        {
            saveGame(boardRows, boardColumns, zombieCount, alien, alien2, zombie);
            Uc = false;
            system("cls");
        }
        if (commands == "load")
        {
            loadGame(boardRows, boardColumns, zombieCount, fileName, alien, alien2, zombie);
            Uc = false;
            system("cls");
        }

        if (commands == "quit")
        {
            string exit;
            bool quit = false;

            while (!quit)
            {
                cout << "Are you sure you want to quit the current game? (y/n) => ";
                cin >> exit;
                cout << endl;
                
                if (exit == "y" || exit == "Y" || exit == "n" || exit == "N")
                {
                    quit = true;
                }
                else
                {
                    cout << "Invalid input. Please enter y or n." << endl;
                    cout << endl;
                }
            }

            if (exit == "y" || exit == "Y")
            {
                cout << endl
                     << "Goodbye, See you again!" << endl;
                cout << endl;
                system("pause");
                break;
                Uc = false;
            }
            else if (exit == "n" || exit == "N")
            {
                cout << endl;
                system("pause");
                system("cls");
                displayBoard(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
            }

            system("pause");
            break;
        }

        else if (Uc == true)
        {
            cout << "Please enter a valid command. " << endl;
            cout << endl;
            system("pause");
            system("cls");
            Uc = true;
        }

        displayBoard(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
    }
}

int main()
{
    // Default Settings :
    int boardRows = 5;
    int boardColumns = 9;
    int zombieCount = 1;
    string commands;
    char controls;
    char dir;
    int row, column;
    string direction;
    Alien alien;
    Zombie zombie(zombieCount);
    Alien2 alien2(boardRows, boardColumns);
    string fileName;

    gameSettings(boardRows, boardColumns, zombieCount, commands, controls, alien, row, column, direction, alien2, zombie, dir, fileName);
}