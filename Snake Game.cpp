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
        return 0; // Food is lying on the co ordinates of the snake
    }
    else {
        return 1; // food is not lying on the snake
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
            sy[i]--; // direction agar 1 huaa yanee NORTH to y axis ghatega Snake Upar move karega
        }
    }
    else if (direction ==2) {
        for (int i = 0; i<=(length-1); i++) {
            sy[i]++; // direction agar 2 huaa yanee South top y axis increase hoga Snake neeche move karega
        }
    }
    else if (direction ==3) {
        for (int i = 0; i<=(length-1); i++) {
            sx[i]--; // direction agar 3 hai to snake left kee taraf move karega or x axix decrease karega
        }
    }
    else if (direction ==4) {
        for (int i = 0; i<=(length-1); i++) {
            sx[i]++; // direction agar 4 raha to snake right kee taraf move karega or x axix increase karega
        }
    }
}

bool gameOver () {
    int fsx = sx[0]; // face of snake ka x co ordinate
    int fsy = sy[0];
    //if (fsx == 0 || fsx == 25 || fsy == 0 || fsy == 25){
    //    return 0; // GAME OVER touched the boundary
    //}
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
        return 0; // GAMEW OVER Touched on body
    }
    else {
        return 1; // na body me touch kiya hai or na hee boundary me touch kiya hai
    }
}

bool foodEatenBySnake() {
    int fsx = sx[0];
    int fsy = sy[0];
    if (fsx == fx && fsy == fy) {
        return 1; // snake ne food ko kha liya hai
    }
    else {
        return 0;
    }
}
int main() {
    printBoundary();
    sx[length] = 13; // first co ordinate of snake X axis
    sy[length] = 13; // first co ordinate of snake Y axis
    length++; // length will increase
    printSnake();
    generateFood();
    printFood();
    changeCursor(0,27);
    cout << "Score : " << ((length-1)*10);
    while(1) {
        delay();
        changeCursor(0,26);
        char ch;
        if (_kbhit()) { // agar kisi ne press kiya tabhee ye If statement khulega
            cin>> ch;
            if (ch == 'w' && direction != 2) { // agar direction upar kee taraf hai to check hoga kee wo neeche kee taraf na ho pehle
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

    // fx and fy wo food ke co ordinates hain
    getchar();
}



// 2 se 25 tak values generate karna hai
// 24 se modulo leke usme 2 add kar denge --> 2 3 4 .. ...... 25


// 2 se 9 ke beech ke random number generate karne hain --> 2 3 4 5 6 7 8 9
// 8 se modulo lene pe --> 0 1 2 3 4 5 6 7
// 9 modulo jo aaya hai usme agar 2 add kartenge to --> 2 3 4 5 6 7 8 9


// position --> W -> 1 , S -> 2, A -> 3, D -> 4
