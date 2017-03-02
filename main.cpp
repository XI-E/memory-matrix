#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "rlutil.h"

using namespace std;

class coord{
public:
    coord(int a, int b){
        x = a;
        y = b;
    }
    coord(void){
        x = 0;
        y = 0;
    }
    friend void check(coord);

    operator =(coord & b){
        this->x = b.x;
        this->y = b.y;
    }

    int x;
    int y;
};

vector<vector<bool> > revealed(10, vector<bool>(10, false));

int x = 0, y = 0, param;
bool already_open = false;
coord opened;
char matrix_data[10][10];
char matrix_display[10][10] = { {'*','*'} };

void print_board(void);
void check(coord);
void matrix_fill(int);

int main()
{
    start:

    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);

    cout << "Welcome to Memory Matrix!\n"
            << "How many rows/columns would you like(even, less than 10)? ";
    param = getch(); rlutil::setColor(rlutil::YELLOW); cout << (char) param;
    param -= 48;

    if(param > 9 || param < 2 || param%2 != 0){
        rlutil::setColor(rlutil::LIGHTRED);
        cout << "\n\nInvalid Input! Please try again!";
        getch();
        goto start;
    }
    else{
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                matrix_display[i][j] = 219;
                matrix_data[i][j] = 0;
            }
        }
        matrix_fill(param);
    }

    rlutil::setColor(rlutil::GREEN);
    cout << "\n\nInput success, press any key to start!";
    getch();

    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();

    while(true){
        cout << " Make pairs of like symbols to win!\n Use arrow keys to control position\n Press enter to flip tile\n\n\n";
        print_board();
        while(!kbhit()){
            ;
        }

        int a = rlutil::getkey();

        if(a == rlutil::KEY_UP && y != 0){
                y--;
        }
        else if(a == rlutil::KEY_DOWN && y != (param - 1)){
                y++;
        }
        else if(a == rlutil::KEY_LEFT && x != 0){
                x--;
        }
        else if(a == rlutil::KEY_RIGHT && x != (param - 1)){
                x++;
        }
        else if(a == rlutil::KEY_ENTER){
            check(coord (x, y));
        }

        rlutil::cls();
        }

    return 0;
}

void print_board(void){
    for(int i = 0; i < param; i++){
        for(int j=0; j < param; j++){
            if(y == i && x == j){
                rlutil::setColor(rlutil::GREEN);
            }
            else if(opened.x == j && opened.y == j){
                rlutil::setColor(rlutil::LIGHTRED);
            }
            if(opened.x == j && opened.y == i){
             cout << "  " << matrix_data[i][j];
            }
            else{
             cout << "  " << matrix_display[i][j];
            }
            rlutil::setColor(rlutil::WHITE);
        }
        cout << endl << endl;
    }
}

void check(coord a){
    if(revealed[a.x][a.y]){
        return;
    }
    if(already_open == true){
        if(matrix_data[a.x][a.y] == matrix_data[opened.x][opened.y]){
            revealed[a.x][a.y] = true;
            revealed[opened.x][opened.y] = true;
            already_open = false;
            coord b (11, 11);
            opened = b;
        }
    }
    else{
        already_open = true;
        opened = a;
    }
}

void matrix_fill(int a){
    int r1, r2, r3, r4;
    char p[10] = {127, 131, 140, 167, 182, 208, 198, 164, 165};

    for(int i=0; i < (a*a/2); i++){
        do{
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            default_random_engine generator (seed);
            uniform_int_distribution<int> distribution(0,param);

            r1 = distribution(generator);
            r2 = distribution(generator);
            r3 = distribution(generator);
            r4 = distribution(generator);

        }while(matrix_data[r1][r2] != 0 && matrix_data[r3][r4] != 0);

        matrix_data[r1][r2] = p[i];
        matrix_data[r3][r4] = p[i];
    }
    return;
}
