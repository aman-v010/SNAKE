#include<iostream>
#include<time.h>
#include<windows.h>
#include<cstdio>
#include<stdio.h>
#include<conio.h>
using namespace std;

int sx[1000];
int sy[1000];
int length = 0;
int fx;
int fy;
int direction=1;
int foodOnSnake(){
    int flag =0;
    for (int i =0; i<=(length-1); i++) {
        if ((sx[i] == fx) && (sy[i] == fy)) {
            flag =1;
            break;
        }
    }
    if (flag ==1) {
        return 0;
    }
    else {
        return 1; 
    }
}

void generateFood (){
    srand(time(0));
    while (1) {
        int x = (rand() % 23) +2;
        int y = (rand() % 23) + 2;
        fx = x;
        fy = y;
        int answer = foodOnSnake();
        if (answer ==1) {
            break;
        }
    }

}
void printBoundary () {
    for (int i = 0; i <= 25; i++) {
        for (int j = 0; j <= 25; j++) {
            if (i>=1 && i<=24 && j>=1 && j<=24) {
                cout << " ";
            }
            else {
                cout << "*";
            }
        }
        cout << endl;
    }
}
void changeCursor( int columnPos, int rowPos ){
    HANDLE handle;
    COORD coord;

    coord.X = columnPos;
    coord.Y = rowPos;


    handle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition( handle,coord );
}
void printSnake () {
    for (int i =0; i<=(length-1); i++) {
        changeCursor(sx[i], sy[i]);
        cout << "#";
    }
}

void printFood() {
    changeCursor(fx, fy);
    cout << "@";
}

void delay() {
    for (long long int i =0; i <=200000000; i++) {

    }
}

void changeThePositionOfSnake () {
    if (direction ==1) {
        for (int i = 0; i<=(length-1); i++) {
            sy[i]--; 
        }
    }
    else if (direction ==2) {
        for (int i = 0; i<=(length-1); i++) {
            sy[i]++; 
        }
    }
    else if (direction ==3) {
        for (int i = 0; i<=(length-1); i++) {
            sx[i]--; 
        }
    }
    else if (direction ==4) {
        for (int i = 0; i<=(length-1); i++) {
            sx[i]++; 
        }
    }
}

bool gameOver () {
    int fsx = sx[0]; 
    int fsy = sy[0];
    for (int i = 0; i<= (length-1); i++) {
        if (sx[i] == 0 || sx[i] == 25 || sy[i] == 0 || sy[i] == 25) {
            return 0;
        }
    }
    int flag =0;
    for (int i =1; i<=(length-1); i++) {
        if (fsx == sx[i] && fsy == sy[i]) {
            flag =1;
            break;
        }
    }
    if (flag ==1) {
        return 0;
    }
    else {
        return 1; 
    }
}

bool foodEatenBySnake() {
    int fsx = sx[0];
    int fsy = sy[0];
    if (fsx == fx && fsy == fy) {
        return 1; 
    }
    else {
        return 0;
    }
}
int main() {
    printBoundary();
    sx[length] = 13; 
    sy[length] = 13; 
    length++; 
    printSnake();
    generateFood();
    printFood();
    changeCursor(0,27);
    cout << "Score : " << ((length-1)*10);
    while(1) {
        delay();
        changeCursor(0,26);
        char ch;
        if (_kbhit()) { 
            cin>> ch;
            if (ch == 'w' && direction != 2) { 
                direction =1;
            }
            else if (ch == 's' && direction != 1) {
                direction = 2;
            }
            else if (ch == 'a' && direction != 4) {
                direction = 3;
            }
            else if (ch == 'd' && direction != 3) {
                direction = 4;
            }
        }
        system("cls");
        printBoundary();
        int tsx = sx[length-1];
        int tsy = sy[length-1];
        changeThePositionOfSnake();

        int food = foodEatenBySnake();
        if (food == 1) {
            generateFood();
            sx[length] = tsx;
            sy[length] = tsy;
            length++;
        }

        changeCursor(0,27);
        cout << "Score : " << ((length-1)*10);

        int val = gameOver();
        if (val ==0) {
            changeCursor(0,28);
            cout << "GAME OVER....";
            break;
        }
        printSnake();
        printFood();
    }
    getchar();
}
