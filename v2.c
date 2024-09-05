#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

#define WIDTH 22
#define HEIGHT 22

typedef struct SnakeSegment {
    int x, y;
    struct SnakeSegment *next;
} SnakeSegment;

typedef struct Coordinates{
    int x;
    int y;
} Coordinates;

void Print();
void load();
void createBoard(char board[WIDTH][HEIGHT]);
void printBoard(char board[WIDTH][HEIGHT]);
void drawSnake(char board[WIDTH][HEIGHT], SnakeSegment *head, SnakeSegment *tail);
void eraseSnake(char board[WIDTH][HEIGHT], SnakeSegment *head, SnakeSegment *tail);
void clearConsole();
void moveSnake(SnakeSegment *tail, SnakeSegment *head,int dx, int dy);
SnakeSegment * addSegment(SnakeSegment **tail);
int getKeyPressed();
Coordinates appleDropper(char board[WIDTH][HEIGHT], SnakeSegment *tail, SnakeSegment *head);
bool rip(SnakeSegment *tail, SnakeSegment *RealHead, SnakeSegment *head);

int main(){
    Print();
    clearConsole();
    char board[WIDTH][HEIGHT];
    createBoard(board);
    SnakeSegment *head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    head->x = 10;
    head->y = 11;
    head->next = head;

    SnakeSegment *tail = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    tail->x = 10;
    tail->y = 10;
    tail->next = head;

    SnakeSegment *RealHead= addSegment(&tail);
    addSegment(&tail);
    addSegment(&tail);

    Coordinates applePos = appleDropper(board, tail, head);
    load();
    clearConsole();
    drawSnake(board, head, tail);
    printBoard(board);


    //MainGameLoop
    int key;
    int x_direction=0;
    int y_direction=1;
    int direction= 3;


        while(!rip(tail, RealHead, head)){
        key=getKeyPressed();
        if(key){
            switch(key){
                case 72:  // Up arrow
                case 'w':
                case 'W':
                    if(direction!=2){
                    x_direction=-1; y_direction=0;
                    direction= 1;
                    }
                    break;
                case 80:  // Down arrow
                case 's':
                case 'S':
                    if(direction!=1){
                     x_direction=1; y_direction=0;
                     direction= 2;
                     }
                     break;
                case 75:  // Left arrow
                case 'a':
                case 'A':
                    if(direction!=3){
                     x_direction=0; y_direction=-1;
                     direction= 4;
                     }
                     break;
                case 77:  // Right arrow
                case 'd':
                case 'D':
                    if(direction!=4){
                    x_direction=0; y_direction=1;
                    direction= 3;
                    }
                    break;
             }}
            eraseSnake(board, head, tail);
            moveSnake(tail, head, x_direction, y_direction);
            drawSnake(board, head, tail);
            clearConsole();
            printBoard(board);

            if (RealHead->x == applePos.x && RealHead->y == applePos.y) {
                eraseSnake(board, head, tail);
                addSegment(&tail);
                drawSnake(board, head, tail);
                clearConsole();
                printBoard(board);

                applePos = appleDropper(board, tail, head);
                clearConsole();
                printBoard(board);
            }

            Sleep(100);
    }
    return 0;
}

//Functions:
//Function to print instructions:
void Print(){
    printf("Welcome to the mini Snake game.(press any key to continue)\n");
    getch(); //It's like a pause to the program.
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element.\n");
    printf("\n\nPress any key to start the game...");
    if(getch()==27) exit(0);
}
//Function for the loading screen
void load()
{
    int r,q;
    printf("loading...\n");
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=150000000; q++);
        printf("%c",177);
    }
    getchar();
}
// Function to create the board
void createBoard(char board[WIDTH][HEIGHT]) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if(i==0 || j==0 || i==WIDTH-1 || j==HEIGHT-1) board[i][j]='#';
            else board[i][j] = ' ';
        }
    }
}
//Function to clear the console
void clearConsole() {
    system("cls");
}
//Function to print the board
void printBoard(char board[WIDTH][HEIGHT]){
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
                printf("%c",board[i][j]);
        }
        printf("\n");
    }
}
// Function for erasing old snake
void eraseSnake(char board[WIDTH][HEIGHT], SnakeSegment *head, SnakeSegment *tail) {
    SnakeSegment *current = tail->next;
    while (current != head) {
        board[current->x][current->y] = ' ';
        current = current->next;
    }
}
// Function to draw the snake on the board
void drawSnake(char board[WIDTH][HEIGHT], SnakeSegment *head, SnakeSegment *tail) {
    SnakeSegment *current = tail->next;
    while (current != head) {
        board[current->x][current->y] = '*';
        current = current->next;
    }
}
//Function to remove eaten food
void remEatenF(char board[WIDTH][HEIGHT], int x, int y){
    board[x][y]= ' ';
}
//Function to add a new segment to the snake which is triggered when it eats
SnakeSegment * addSegment(SnakeSegment **tail) {
    SnakeSegment *newSegment = (SnakeSegment *)malloc(sizeof(SnakeSegment));
    newSegment->x= (*tail)->x;
    newSegment->y= (*tail)->y;
    newSegment->next= (*tail)->next;
    (*tail)->next= newSegment;
    if(newSegment->x== newSegment->next->x){
        (*tail)->y= newSegment->y > newSegment->next->y ? (newSegment->y)+1 : (newSegment->y)-1;
    }
    else if(newSegment->y== newSegment->next->y){
        (*tail)->x= newSegment->x > newSegment->next->x ? (newSegment->x)+1 : (newSegment->x)-1;
    }
    return newSegment;
}
//Function to move the snake
void moveSnake(SnakeSegment *tail, SnakeSegment *head,int dx, int dy){
    SnakeSegment *current = tail;
    while(current != head){
        current->x= current->next->x;
        current->y= current->next->y;
        current= current->next;
    }
    //once the loop stops, current is head now
    (current->x)+=dx;
    (current->y)+=dy;
}
//Function to check the pressed key for helping the movement fn work correctly
int getKeyPressed() {
    if (kbhit()) {
        int ch = getch();

        if (ch == 0 || ch == 224) {
            ch = getch();
        }
        return ch;
    }
    return -1;
}
// Function to handle food
Coordinates appleDropper(char board[WIDTH][HEIGHT], SnakeSegment *tail, SnakeSegment *head){
    Coordinates applePos;
    bool validPosition;

    do {
        applePos.x = rand() % (WIDTH - 2) + 1;  // Ensure x is between 1 and WIDTH-2
        applePos.y = rand() % (HEIGHT - 2) + 1; // Ensure y is between 1 and HEIGHT-2
        validPosition = true;
        SnakeSegment *current = tail->next;
        // Ensure the apple does not spawn on any part of the snake's body
        while (current != head) {
            if (current->x == applePos.x && current->y == applePos.y) {
                validPosition = false;
                break;
            }
            current = current->next;
        }
    } while (!validPosition);

    board[applePos.x][applePos.y] = 'F';

    return applePos;
}
// Snake's Death
bool rip(SnakeSegment *tail, SnakeSegment *RealHead, SnakeSegment *head){
    SnakeSegment *current= tail->next;
    if(RealHead->x==0||RealHead->x==WIDTH-1||RealHead->y==0||RealHead->y==HEIGHT-1){return true;}
    while(current!= RealHead){
        if(RealHead->x==current->x&&RealHead->y==current->y){return true;}
        current= current->next;
    }
    return false;
}
