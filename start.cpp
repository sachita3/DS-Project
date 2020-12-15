#include<graphics.h>
#include<iostream>
#include<conio.h>

int main(){
    initwindow(800, 800);
    setcolor(YELLOW);
    settextstyle(10,0, 8);
    outtextxy(270, 120, "SUDOKU");
    rectangle(250, 220, 600, 280);
    settextstyle(1,0,-0.5);
    outtextxy(280, 230, "1. EASY");
    rectangle(250, 320, 600, 380);
    outtextxy(280, 330, "2. MEDIUM");
    rectangle(250, 420, 600, 480);
    outtextxy(280, 430, "3.DIFFICULT");
    rectangle(250, 520, 600, 580);
    outtextxy(280, 530, "4. EXIT");
    outtextxy(220, 620, "ENTER CHOICE: ");
    int opt;
    opt = getch();
    getch();
}
