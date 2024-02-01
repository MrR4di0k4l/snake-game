#include <iostream>
#include<conio.h>
#include <stdlib.h>
#include<time.h>
#include <windows.h>

using namespace std;

int  score;
int  y;
int  y2;
int  x;
int  x2;
int const width=20,height=20;
bool gameOver;
struct point {
    int x,y ;
};

point player,fruit;
point tail[400];
int n_tail;

enum direction {STOP=0,LEFT,RIGHT,UP,DOWN};
direction dir;

void setup(){
    player.x=width/2;
    player.y=height/2;

    fruit.x=rand()%(width-2)+1;
    fruit.y=rand()%(height-2)+1;
    gameOver=false;
    score=0;
    y=0;
    y2=0;
    x=0;
    x2=0;
    dir=STOP;
    n_tail=0;

}
void draw(){
    system("cls");
    int i,j;
    for(i=0 ; i<width ; i++)
    cout<<"*";
    cout<<endl;

    for(i=0 ; i<height ; i++){
    for(j=0 ; j<width;j++){
        if(j==0||j==width-1)
            cout<<"*";
        else if( j==player.x && i==player.y)
            cout<<"O";
        else if( j==fruit.x && i==fruit.y)
            cout<<"X";
        else{
            bool flag =false;
            for(int k=0;k<n_tail;k++)
            if (j==tail[k].x&&i==tail[k].y){
                cout<<"o";
                flag=true;
            }
            if (!flag)
                cout<<" ";

        }

    }
    cout <<endl;
    }

    for(i=0;i<width;i++)
        cout<<"*";
    cout <<"\n score:"<<score;

}
void input(){
    if (kbhit()){
    switch(getche()){
        case'w' :
        case 'W':
            dir=UP;
        break;

        case's' :
        case 'S':
            dir=DOWN;
        break;

        case'a' :
        case 'A':
            dir=LEFT;
        break;

        case'd' :
        case 'D':
            dir=RIGHT;
        break;
            default:
            break;
        }
    }
}
void lagic(){
    for(int i=n_tail-1;i>=1;i--){
        tail[i].x=tail[i-1].x;
                tail[i].y=tail[i-1].y;
        }
    tail[0].x=player.x;
    tail[0].y=player.y;


    switch (dir){
        case LEFT:
            y = 0;
            y2 = 0;
            x2 = 1;
            if(x < x2)
                player.x=(player.x-1+width)%width;
            else
                player.x=(player.x+1+height)%height;
            break;

        case RIGHT:
            y = 0;
            y2 = 0;
            x = 1;
            if(x > x2)
                player.x=(player.x+1)%width;
            else
                player.x=(player.x-1)%width;
            break;

        case UP:
            y2 = 1;
            x = 0;
            x2 = 0;
            if(y < y2)
                player.y=(player.y-1+height)%height;
            else
                player.y=(player.y+1+height)%height;
            break;

        case DOWN:
            y = 1;
            x = 0;
            x2 = 0;
            if(y > y2)
                player.y=(player.y+1)%height;
            else
                player.y=(player.y-1+height)%height;
            break;

        default:
            break;

    }
     if (player.x==fruit.x&&player.y==fruit.y)
    {
        score+=10;
        Beep(500,50);

        fruit.x=rand()%(width-2)+1;
        fruit.y=rand()%(height-2)+1;
        n_tail++;
    }
    for(int i=n_tail-1;i>=1;i--)
    {
        if (player.x==tail[i].x&&player.y==tail[i].y)
            gameOver = TRUE;
    }

}

int main(){

    srand(time(NULL));
    setup();
    while(!gameOver)
    {
        draw();
        input();
        lagic();
        Sleep(50);

    }
    cout << "\nGame Over :(" <<endl;
    getch();
return 0;
}
