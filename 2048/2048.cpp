#include <iostream>
#include "Square.h"
#include "Number.h"
#include "Blank.h"
#include "Bomb.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void genBlankGrid();
void displayGrid();
void displayGame();
void input(char in);
void start();

void save();
void load();

void displayHall();
void loadHall();
void updateHall(int score);


void newG();
void quit();

void win();
void lose();

void ran();

void left();
void right();
void up();
void down();

void debugF();
bool debug = false;

bool won = false;

string lower(string in);

const Square blank[4][4] = {
    {Blank(), Blank(), Blank(), Blank()},
    {Blank(), Blank(), Blank(), Blank()},
    {Blank(), Blank(), Blank(), Blank()},
    {Blank(), Blank(), Blank(), Blank()}
};
Square grid[4][4] = {
    {Blank(), Blank(), Blank(), Blank()},
    {Blank(), Blank(), Blank(), Blank()},
    {Blank(), Blank(), Blank(), Blank()},
    {Blank(), Blank(), Blank(), Blank()}
};

int score = 0;
string hallName[100];
int hallScore[100];
int hallCount = 0;

int main()
{
    srand((unsigned)time(0));
    loadHall();
    start();
    while (true) {
        displayGame();
        char in;
        cin >> in;
        input(in);
    }
}
void genBlankGrid() {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            grid[x][y] = blank[x][y];
        }
    }
}
void ran() {
        int list[16];
        int count = 0;
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                if (grid[x][y].getType() == BLANK) {
                    list[count] = (4 * x) + y;
                    count++;
                }
            }
        }
        if (count == 0) {
            lose();
        }
        else {
            int result = 1 + (rand() % count);
            int randnum = 1 + (rand() % 100);
            result = list[result - 1];
            int x = result / 4;
            int y = result - (4 * x);
            if (randnum < 40) grid[x][y] = Number(2);
            else if (randnum < 80) grid[x][y] = Number(4);
            else grid[x][y] = Bomb();
            if (debug) {
                cout << "New:" << grid[x][y].getType() << " at: " << x+1 << "," << y+1 << endl;
            }
        }   
}
void start() {
    genBlankGrid();
    ran();
    ran();
    score = 0;
}
void displayGrid() {
    string print;
    for (int x = 0; x < 4; x++) {
        cout << "+----+----+----+----+" << endl;
        cout << "|";
        for (int y = 0; y < 4; y++) {
            if (grid[x][y].getType() == BOMB) {
                print = "   *";
            }
            if (grid[x][y].getType() == BLANK) {
                print = "    ";
            }
            if (grid[x][y].getType() == NUMBER) {
                int i = grid[x][y].getValue();
                if (i < 10) {
                    print = "   " + to_string(i);
                }
                else if (i < 100) {
                    print = "  " + to_string(i);
                }
                else if (i < 1000) {
                    print = " " + to_string(i);
                }
                else {
                    print = to_string(i);
                }
            }
            cout << print << "|";
        }
        cout << endl;
    }
    cout << "+----+----+----+----+" << endl;
}
void displayGame() {
    cout << "============================" << endl;
    cout << "2048 ENHANCED" << endl;
    cout << "----------------------------" << endl;
    cout << "Press A, W, X, D to play" << endl;
    cout << "S to save, L to Load" << endl;
    cout << "H to see the Hall of Fame" << endl;
    cout << "N for a new Game, Q to Quit" << endl;
    cout << "P to enable/disable Debug Mode" << endl;
    cout << "----------------------------" << endl;
    cout << "Score: " << score << endl;
    cout << "----------------------------" << endl;
    displayGrid();
    cout << "============================" << endl;
    if (won) win();
}
void input(char in) {
    switch (in) {
    case 'a':
    case 'A': left(); break;
    case 'w':
    case 'W': up(); break;
    case 'd':
    case 'D': right(); break;
    case 'x':
    case 'X': down(); break;
    case 'q':
    case 'Q': quit(); break;
    case 's':
    case 'S': save(); break;
    case 'h':
    case 'H': displayHall(); break;
    case 'l':
    case 'L': load(); break;
    case 'n':
    case 'N': newG(); break;
    case 'p':
    case 'P': debugF(); break;
    default: cout << "Invalid Selection!" << endl;
    }
}
void load() {
    char inp;
    cout << "Are you sure? Y/N" << endl;
    cin >> inp;
    if (inp == 'y' || inp == 'Y') {
        string name;
        cout << "Enter Save Name:" << endl;
        cin >> name;
        while (lower(name) == "halloffame") {
            cout << "The name 'HallOfFame' cannot be loaded" << endl;
            cout << "Enter Save Name:" << endl;
            cin >> name;
        }
        name = name + ".txt";
        string line;
        ifstream ifs(name);
        if (ifs.fail()) {
            cout << "This file does not exist! Please try again" << endl;
        }
        else {
            genBlankGrid();
            while (getline(ifs, line)) {
                int len = line.length();
                string first = line.substr(0, line.find(":"));
                string second = line.substr(1 + line.find(":"), len);
                if (first == "Score")
                {
                    score = stoi(second);
                }
                else {
                    int fir = stoi(first);
                    int sec = stoi(second);
                    int x = fir / 4;
                    int y = fir - (4 * x);
                    grid[x][y] = Number(sec);
                }
            }
            ifs.close();
        }
    }
    else if(inp == 'n' || inp == 'N'){}
    else {
        cout << "Please choose Y or N" << endl;
    }
}
void save() {
    string name;
    cout << "Enter Save Name:" << endl;
    cin >> name;
    while(lower(name) == "halloffame") {
        cout << "The file 'HallOfFame' cannot be used" << endl;
        cout << "Enter Save Name:" << endl;
        cin >> name;
    }
    name = name + ".txt";
    ofstream ofs(name);
    if (ofs.is_open()) {
        ofs << "Score:" << score << endl;
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                if (grid[x][y].getType() != BLANK) {
                    int position = (4 * x) + y;
                    ofs << position << ":";
                    if (grid[x][y].getType() == NUMBER) {
                        ofs << grid[x][y].getValue() << endl;
                    }
                    else {
                        ofs << "*" << endl;
                    }
                    
                }
            }
        }
        ofs.close();
    }
}
void displayHall() {
    cout << "Hall of Fame:" << endl;
    for (int i = 0; i < hallCount; i++) {
        cout << (i+1) << ": " << hallName[i] << "-" << hallScore[i] << endl;
    }
}
void loadHall() {
    hallCount = 0;
    string line;
    ifstream ifs("HallOfFame.txt");
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            int len = line.length();
            string first = line.substr(0, line.find(":"));
            string second = line.substr(1 + line.find(":"), len);
            hallName[hallCount] = first;
            hallScore[hallCount] = stoi(second);
            hallCount++;
        }
    }
    ifs.close();
}
void updateHall(int score) {
    string name;
    cout << "Congratulations! You won!" << endl;
    cout << "Enter your name: " << endl;
    cin >> name;
    int pos = 0;
    for (int i = hallCount; i > 0; i--) {
        if (score > hallScore[i]) {
            pos = i;
        }
    }
    hallCount++;
    for (int i = hallCount; i > pos; i--) {
        hallName[hallCount] = hallName[hallCount - 1];
        hallScore[hallCount] = hallScore[hallCount - 1];
    }
    hallName[pos] = name;
    hallScore[pos] = score;
    cout << "Congratulations! You are number " << pos << " on the leaderboard" << endl;
    std::ofstream ofs;
    ofs.open("HallOfFame.txt", std::ofstream::out | std::ofstream::trunc);
    for (int i = 0; i < hallCount; i++) {
        ofs << hallName[i] << ":" << hallScore[i] << endl;
    }
    ofs.close();
}
void left() {
    bool moved = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (grid[x][y].getType() == BLANK) {
                for (int m = 3; m > y; m--) {
                    if (grid[x][m].getType() != BLANK) {
                        grid[x][m - 1] = grid[x][m];
                        grid[x][m] = Blank();
                        moved = true;
                    }
                }
            }
            else if (grid[x][y].getType() == NUMBER) {
                for (int m = 1; m < 4 - y; m++) {
                    if (grid[x][y+m].getType() == NUMBER) {
                        if (grid[x][y].getValue() == grid[x][y+m].getValue()) {
                            int newV = 2 * grid[x][y].getValue();
                            grid[x][y + m] = Blank();
                            grid[x][y].setValue(newV);
                            score += newV;
                            if (newV >= 2048) {
                                won = true;
                            }
                            moved = true;
                        }
                        else { break; }
                    }
                    else if (grid[x][y+m].getType() == BOMB) {
                        score -= grid[x][y].getValue();
                        grid[x][y] = Blank();
                        grid[x][y+m] = Blank();
                        moved = true;
                    }
                }
            }
            else if (grid[x][y].getType() == BOMB) {
                for (int m = 1; m < 4 - y; m++) {
                    if (grid[x][y + m].getType() == BOMB) break;
                    else if (grid[x][y + m].getType() == NUMBER) {
                        score -= grid[x][y+m].getValue();
                        grid[x][y] = Blank();
                        grid[x][y + m] = Blank();
                        moved = true;
                    }
                }
            }
        }
    }
    if(moved) ran();
    else { cout << "Invalid move!" << endl; }
}
void right() {
    bool moved = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 3; y > -1; y--) {
            if (grid[x][y].getType() == BLANK) {
                for (int m = 0; m < y; m++) {
                    if (grid[x][m].getType() != BLANK) {
                        grid[x][m + 1] = grid[x][m];
                        grid[x][m] = Blank();
                        moved = true;
                    }
                }
            }
            else if (grid[x][y].getType() == NUMBER) {
                for (int m = 1; m < (y+1); m++) {
                    if (grid[x][y - m].getType() == NUMBER) {
                        if (grid[x][y].getValue() == grid[x][y - m].getValue()) {
                            int newV = 2 * grid[x][y].getValue();
                            grid[x][y - m] = Blank();
                            grid[x][y].setValue(newV);
                            score += newV;
                            if (newV >= 2048) {
                                won = true;
                            }
                            moved = true;
                        }
                        else { break; }
                    }
                    else if (grid[x][y-m].getType() == BOMB) {
                        score -= grid[x][y].getValue();
                        grid[x][y] = Blank();
                        grid[x][y-m] = Blank();
                        moved = true;
                    }
                }
            }
            else if (grid[x][y].getType() == BOMB) {
                for (int m = 1; m < (y+1); m++) {
                    if (grid[x][y - m].getType() == BOMB) break;
                    else if (grid[x][y-m].getType() == NUMBER) {
                        score -= grid[x][y - m].getValue();
                        grid[x][y] = Blank();
                        grid[x][y-m] = Blank();
                        moved = true;
                    }
                }
            }
        }
    }
    if (moved) ran();
    else { cout << "Invalid move!" << endl; }
}
void up() {
    bool moved = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (grid[x][y].getType() == BLANK) {
                for (int m = 3; m > x; m--) {
                    if (grid[m][y].getType() != BLANK) {
                        grid[m - 1][y] = grid[m][y];
                        grid[m][y] = Blank();
                        moved = true;
                    }
                }
            }
            else if (grid[x][y].getType() == NUMBER) {
                for (int m = 1; m < 4 - x; m++) {
                    if (grid[x + m][y].getType() == NUMBER) {
                        if (grid[x][y].getValue() == grid[x + m][y].getValue()) {
                            int newV = 2 * grid[x][y].getValue();
                            grid[x + m][y] = Blank();
                            grid[x][y].setValue(newV);
                            score += newV;
                            if (newV >= 2048) {
                                won = true;
                            }
                            moved = true;
                        }
                        else { break; }
                    }
                    else if (grid[x + m][y].getType() == BOMB) {
                        score -= grid[x][y].getValue();
                        grid[x][y] = Blank();
                        grid[x + m][y] = Blank();
                        moved = true;
                    }
                }
            }
            else if (grid[x][y].getType() == BOMB) {
                for (int m = 1; m < 4 - x; m++) {
                    if (grid[x + m][y].getType() == BOMB) break;
                    else if (grid[x + m][y].getType() == NUMBER) {
                        score -= grid[x + m][y].getValue();
                        grid[x][y] = Blank();
                        grid[x + m][y] = Blank();
                        moved = true;
                    }
                }
            }
        }
    }
    if (moved) ran();
    else { cout << "Invalid move!" << endl; }
}
void down() {
    bool moved = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 3; x > -1; x--) {
            if (grid[x][y].getType() == BLANK) {
                for (int m = 0; m < x; m++) {
                    if (grid[m][y].getType() != BLANK) {
                        grid[m+1][y] = grid[m][y];
                        grid[m][y] = Blank();
                        moved = true;
                    }
                }
            }
            else if (grid[x][y].getType() == NUMBER) {
                for (int m = 1; m < (x+1); m++) {
                    if (grid[x - m][y].getType() == NUMBER) {
                        if (grid[x][y].getValue() == grid[x - m][y].getValue()) {
                            int newV = 2 * grid[x][y].getValue();
                            grid[x - m][y] = Blank();
                            grid[x][y].setValue(newV);
                            score += newV;
                            if (newV >= 2048) {
                                won = true;
                            }
                            moved = true;
                        }
                        else { break; }
                    }
                    else if (grid[x - m][y].getType() == BOMB) {
                        grid[x][y] = Blank();
                        grid[x - m][y] = Blank();
                        score -= grid[x - m][y].getValue();
                        moved = true;
                    }
                }
            }
            else if (grid[x][y].getType() == BOMB) {
                for (int m = 1; m < (x+1); m++) {
                    if (grid[x + m][y].getType() == BOMB) break;
                    else if (grid[x - m][y].getType() == NUMBER) {
                        score -= grid[x-m][y].getValue();
                        grid[x][y] = Blank();
                        grid[x - m][y] = Blank();
                        moved = true;
                    }
                }
            }
        }
    }
    if (moved) ran();
    else { cout << "Invalid move!" << endl; }
}
void lose() {
    cout << "You lose!!" << endl;
    cout << "Your score was: " << score << endl;
    displayHall();
    start();
}
void win() {
    won = false;
    cout << "You win!!" << endl;
    cout << "Your score was: " << score << endl;
    updateHall(score);
    displayHall();
    start();
}
void quit() {
    char inp;
    cout << "Are you sure? Y/N" << endl;
    cin >> inp;
    if (inp == 'y' || inp == 'Y') {
        exit(0);
    }
    else if (inp == 'n' || inp == 'N') {}
    else {
        cout << "Please choose Y or N" << endl;
    }
}
void newG() {
    char inp;
    cout << "Are you sure? Y/N" << endl;
    cin >> inp;
    if (inp == 'y' || inp == 'Y') {
        start();
    }
    else if (inp == 'n' || inp == 'N') {}
    else {
        cout << "Please choose Y or N" << endl;
    }
}
void debugF() {
    if (debug) debug = false;
    else debug = true;
}
string lower(string in) {
    int len = in.length();
    string out = "";
    for (int i = 0; i < len; i++) {
        out += tolower(in[i]);
    }
    return out;
}