#include<iostream>
#include<graphics.h>
#include<ctime>
#include "sudokugenerator.h"

int check_row(int *p);
int check_colm(int *p);
void brdr();
void display_sud();
void show_box();
void show_level();
void show_timer();

int box_x=0,box_y=0;
int lv_l;
float tm;
short cc[9][9];
int mat_sud[9][9];
char str[20];

int main(){

    void load_cc();
    void initialize();
    void level();
    int gd=0,gm;
    int c[9],r[9],*p,i,j,c_temp=0,r_temp=0;
    int key,value;
    bool done=false;
    initgraph(&gd,&gm,"");
    initwindow(950,670,"Sudoku",100,10);

    setbkcolor(COLOR(151, 169, 178)); //background color
    cleardevice();

   // initialize();
    p=(int *)mat_sud;

    settextstyle(8,0,3);
    outtextxy(90,100,"Select level");
    level();

    load_cc();
    brdr();

    display_sud();
    show_box();

    int t=clock();

    while(done!=true){

        r_temp=0;
        c_temp=0;
        key=getch();

        if(key>='1'&&key<='9'){
           if(cc[box_x][box_y]==0){

                mat_sud[box_x][box_y]=key-48;
                sprintf(str,"%d",key-48);
                setviewport(0,0,1000,600,0);
                outtextxy(223+60*box_x, 85+60*box_y, str);
           }
       }
       else{
        if(key == 'w' && box_y > 0){
            box_y=box_y-1;
            show_box();
        }
        if(key == 's' && box_y < 8){
            box_y=box_y+1;
            show_box();
        }
        if(key == 'd' && box_x < 8){
            box_x=box_x+1;
            show_box();
        }
        if(key == 'a' && box_x > 0){
            box_x=box_x-1;
            show_box();
        }
        if(key == 'x'){
            cleardevice();
            setviewport(0,0,700,600,0);
            outtextxy(300,300,"Thank you");
            delay(1000);
            exit(1);
        }
       }
        for(int i = 0; i <= 8; i++){
            r[i] = check_row(p + 9*i);
            if(r[i] == 1)
                r_temp++;
        }
        for(i = 0; i <= 8; i++){
            c[i] = check_colm(p+i);
            if(c[i] == 1)
                c_temp++;
        }
        if(r_temp == 9 && c_temp == 9)
            done=true;
    }

    t = clock() - t;
    tm = tm + t/CLOCKS_PER_SEC;

    cleardevice();
    outtextxy(350,300,"Done!");
    show_timer();

    getch();
    closegraph();
    return 0;
}


int check_row(int *p){

    int v = 1, s = 0, cnt[9] = {0};
    for(int i = 0; i <= 8; i++){
        s = *(p + i);
        switch(s){
            case 1:
                cnt[0] = cnt[0] + 1; break;
            case 2:
                cnt[1] = cnt[1] + 1; break;
            case 3:
                cnt[2] = cnt[2] + 1; break;
            case 4:
                cnt[3] = cnt[3] + 1; break;
            case 5:
                cnt[4] = cnt[4] + 1; break;
            case 6:
                cnt[5] = cnt[5] + 1; break;
            case 7:
                cnt[6] = cnt[6] + 1; break;
            case 8:
                cnt[7] = cnt[7] + 1; break;
            case 9:
                cnt[8] = cnt[8] + 1;
        }
    }
    for(int i = 0; i <= 8; i++){
        if(cnt[i] != 1)
            v = 0;
    }
    return v;
}

int check_colm(int *p){

    int v = 1, cnt[9] = {0};
    for(int i = 0; i <= 8; i++){
        switch(*(p + i*9)){
            case 1:
                cnt[0] = cnt[0] + 1; break;
            case 2:
                cnt[1] = cnt[1] + 1; break;
            case 3:
                cnt[2] = cnt[2] + 1; break;
            case 4:
                cnt[3] = cnt[3] + 1; break;
            case 5:
                cnt[4] = cnt[4] + 1; break;
            case 6:
                cnt[5] = cnt[5] + 1; break;
            case 7:
                cnt[6] = cnt[6] + 1; break;
            case 8:
                cnt[7] = cnt[7] + 1; break;
            case 9:
                cnt[8] = cnt[8] + 1;
        }
    }
    for(int i = 0; i <= 8; i++){
        if(cnt[i] != 1)
            v=0;
    }
    return v;
}

void brdr(){
    // div=60
    setviewport(0,0,1000,800,0);
    setcolor(/*COLOR(15, 27, 33)*/15);
    rectangle(200,70,740,610);
    rectangle(199,69,741,611);

    setcolor(BLUE);
    for(int t = 1; t <=8; t++)
        line(200+60*t, 70, 200+60*t, 610);
    for(int t = 1; t <= 8; t++)
        line(200, 60*t+70, 740, 60*t+70);
    for(int t = 1; t <= 2; t++){
        line(180*t+199, 70, 180*t+199, 610);
        line(180*t+201, 70, 180*t+201, 610);
    }

    for(int t = 1; t <= 2; t++){
        line(200, 69+180*t, 740, 69+180*t);
        line(200, 71+180*t, 740, 71+180*t);
    }
    settextstyle(8,0,2);
    outtextxy(720,650,"Press ESC to exit");
}

void display_sud(){

    int t1,t2;
    int i,j;
    settextstyle(8,0,4);
    setcolor(/*COLOR(244, 244, 12)*/0);
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            t1 = i*60 + 200;
            t2 = j*60 + 70;
            setviewport(t1,t2,t1+50,t2+50,1);
            if(mat_sud[i][j] == 0)
                outtextxy(22,15," ");
            else{
                int tt = getcolor();
                if(cc[i][j] == 0)
                    setcolor(COLOR(244, 244, 12));
                sprintf(str,"%d",mat_sud[i][j]);
                outtextxy(20,18,str);
                setcolor(tt);
            }
        }
        show_level();
    }
}

void show_box(){

    cleardevice();

    int t1 = box_x*60, t2 = box_y*60;
    setviewport(202+t1, 72+t2, 255+t1, 125+t2, 1);
    setcolor(RED);
    rectangle(10,10,50,52);
    setcolor(15);
    brdr();
    display_sud();
}

void show_timer(){
    float s;
    // setviewport(20,20,200,70,1);
    if(tm > 60){
        s = tm/60.0;
        tm = (int)tm%60;
        sprintf(str,"Time: %.0f.%.0f min",s,tm);
        outtextxy(300,350,str);
    }
    else{
        sprintf(str,"Time: %.1f sec",tm);
        outtextxy(300,350,str);
   }
}

void load_cc(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(mat_sud[i][j] != 0)
                cc[i][j] = 1;
        }
    }
}

void level(){

    void  initializer(int );
    int ch;
    static int y_crd = 0;
    setcolor(BLUE);
    setviewport(300,150,600,400,1);
    outtextxy(5,5,"Easy  ");
    outtextxy(5,45,"Medium");
    outtextxy(5,85,"Hard ");
    rectangle(0, y_crd, 150, y_crd+35);
    ch=getch();
    if(ch == 13){
        if(y_crd == 0){
            initializer(0);
            lv_l = 1;
        }
        else if(y_crd == 40){
            initializer(1);
            lv_l = 2;
        }
        else if(y_crd == 80){
            initializer(2);
            lv_l = 3;
        }
        return;
    }
    else{
        if(ch == 's' || ch == 'd'){
            y_crd = y_crd + 40;
            if(y_crd > 80)
                y_crd = 0;
        }
        else if(ch == 'w' || ch == 'a'){
            y_crd = y_crd - 40;
            if(y_crd < 0)
                y_crd = 80;
        }
        clearviewport();
        level();
     }
}

void initializer(int c){
    
    short mat_m[9][9] = get_puzzle();
    
    for(int m = 0; m < 9; m++)
        for(int n = 0; n < 9; n++)
            mat_sud[m][n] = mat_m[m][n];
}

void show_level(){

    setviewport(0,0,250,40,1);
    settextstyle(8,0,3);
    if(lv_l == 1)
        sprintf(str,"Level : Easy " );
    else if(lv_l == 2){
        clearviewport();
        sprintf(str,"Level : Medium ");
    }
    else
        sprintf(str,"Level : Hard ");
    outtextxy(20,10,str);
    settextstyle(8,0,4);
}
