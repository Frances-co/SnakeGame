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


void createBoard(char board[WIDTH][HEIGHT]);
void printBoard(char board[WIDTH][HEIGHT]);
void updateBoard(char board[WIDTH][HEIGHT], SnakeSegment *head);
void drawSnake(char board[WIDTH][HEIGHT], SnakeSegment *head);
void eraseSnake(char board[WIDTH][HEIGHT], SnakeSegment *head);
void clearConsole();
void addSegment(SnakeSegment **head, int direction);
void moveSnake(SnakeSegment *head, int dx, int dy);
int getKeyPressed();
Coordinates appleDropper(char board[WIDTH][HEIGHT], SnakeSegment *head);
bool rip(SnakeSegment *head);

int main() {
    char board[WIDTH][HEIGHT];
    createBoard(board);
/*
    SnakeSegment *segment3 = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    segment3->x = 10;
    segment3->y = 12;
    segment3->next = NULL;

    SnakeSegment *segment2 = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    segment2->x = 10;
    segment2->y = 11;
    segment2->next = segment3;

    SnakeSegment *head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    head->x = 10;
    head->y = 10;
    head->next = segment2;
*/
    SnakeSegment *head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    head->x = 10;
    head->y = 10;
    head->next = NULL;

    addSegment(&head, 3);
    addSegment(&head, 3);



    int direction = 3;
    Coordinates applePos = appleDropper(board, head);
    updateBoard(board, head);

    //MainGameLoop
    int key;
    int x_direction=0;
    int y_direction=1;


        while(!rip(head)){
        key=getKeyPressed();
        if(key){
            switch(key){
                case 72:  // Up arrow
                case 'w':
                case 'W':
                    x_direction=-1; y_direction=0;
                    direction=1;
                    break;
                case 80:  // Down arrow
                case 's':
                case 'S':
                     x_direction=1; y_direction=0;
                     direction=2;
                     break;
                case 75:  // Left arrow
                case 'a':
                case 'A':
                     x_direction=0; y_direction=-1;
                     direction=4;
                     break;
                case 77:  // Right arrow
                case 'd':
                case 'D':
                    x_direction=0; y_direction=1;
                    direction=3;
                    break;
             }}
            eraseSnake(board, head);
            moveSnake(head, x_direction, y_direction);

            if (head->x == applePos.x && head->y == applePos.y) {
            addSegment(&head, direction);
            applePos = appleDropper(board, head);  // Drop a new apple
            }
            updateBoard(board, head);
            Sleep(150);
    }
    return 0;
}

//Functions:
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
void eraseSnake(char board[WIDTH][HEIGHT], SnakeSegment *head) {
    SnakeSegment *current = head;
    while (current != NULL) {
        board[current->x][current->y] = ' ';
        current = current->next;
    }
}
// Function to draw the snake on the board
void drawSnake(char board[WIDTH][HEIGHT], SnakeSegment *head) {
    SnakeSegment *current = head;
    while (current != NULL) {
        board[current->x][current->y] = '*';
        current = current->next;
    }
}
//Function to update board
void updateBoard(char board[HEIGHT][WIDTH], SnakeSegment *head) {
    clearConsole();
    drawSnake(board, head);
    printBoard(board);
}
//Function to add a new segment to the snake which is triggered when it eats
void addSegment(SnakeSegment **head, int direction) {
    SnakeSegment *newSegment = (SnakeSegment *)malloc(sizeof(SnakeSegment));
    switch(direction){
        case 1:
            newSegment->x = (*head)->x-1;
            newSegment->y = (*head)->y;
            break;
        case 2:
            newSegment->x = (*head)->x+1;
            newSegment->y = (*head)->y;
            break;
        case 3:
            newSegment->x = (*head)->x;
            newSegment->y = (*head)->y+1;
            break;
        case 4:
            newSegment->x = (*head)->x;
            newSegment->y = (*head)->y-1;
            break;
    }
    newSegment->next = *head;
    *head = newSegment;
}
//Function to move the snake
void moveSnake(SnakeSegment *head, int dx, int dy) {
    SnakeSegment *current = head;
    int prevX = head->x;
    int prevY = head->y;
    head->x += dx;
    head->y += dy;


    while (current->next != NULL) {
        current = current->next;
        int tempX = current->x;
        int tempY = current->y;
        current->x = prevX;
        current->y = prevY;
        prevX = tempX;
        prevY = tempY;
    }
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
Coordinates appleDropper(char board[WIDTH][HEIGHT], SnakeSegment *head) {
    Coordinates applePos;
    bool validPosition;

    do {
        applePos.x = rand() % (WIDTH - 2) + 1;  // Ensure x is between 1 and WIDTH-2
        applePos.y = rand() % (HEIGHT - 2) + 1; // Ensure y is between 1 and HEIGHT-2
        validPosition = true;
        SnakeSegment *current = head;
        // Ensure the apple does not spawn on any part of the snake's body
        while (current != NULL) {
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
bool rip(SnakeSegment *head){
    SnakeSegment *current= head->next;
    if(head->x==0||head->x==WIDTH-1||head->y==0||head->y==HEIGHT-1)return true;
    while(current!= NULL){
        if(head->x==current->x&&head->y==current->y){return true;}
        current= current->next;
    }
    return false;
}
