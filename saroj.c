#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <process.h>


/*some macros */
#define TEXTX 500
#define TEXTY 200
#define FONT_SIZE 4
#define LEFT -100
#define RIGHT 100
#define WIDTH 1600
#define HEIGHT 700


/*border*/
typedef struct{
    char Name[90];
    long score;


}data;

typedef struct{
    int inih,inik;//ini means initial
    int r,h,k;
    int vx,vy;

}ball;
typedef struct{
    int len;
    int thick;
    int inipos;
    int curpos;//current postion
}launcher;

float TIME;
int RX1=150,RY1=50,RX2=1200,RY2=650;
int current=0;

/*prototype */
void mainscreen(void);
int changeKicker(int,int,int,int);
void drawKicker(int,int ,int);
void moveBall(int,int ,int ,int ,int);
void drawBall(int ,int ,int );
void deleteKicker(int,int,int);
void deleteBall(int,int,int);
void gameMenu(void);
void levelScreen(void);
void instructions(void);
void playerDetail(void);
void gameScreen(void);








int main(){
    char ch;
    data player;

//launcher properties
    launcher l;
    l.len=100;
    l.thick=20;
    l.inipos=(RX2-RX1)/2-l.len/2;



    /*BALL properties*/
    ball b;
    b.r=10;
    b.inih =(RX2-RX1)/2;
    b.inik = RY2-l.thick-b.r;
    b.vx = 5;
    b.vy = 5;

    initwindow(WIDTH,HEIGHT,"Brick  breaker");
    mainscreen();
    outtextxy(TEXTX,TEXTY,(char *)"Enter your name");//casted to get rid of error:deprecated conversion
    getch();

   // gets(player.Name);
    gameMenu();
    cleardevice();
    mainscreen();




    /*game starts */


    gameScreen();

    drawBall(b.inih,b.inik,b.r);
    drawKicker(l.inipos,l.thick,l.len);
    l.curpos=l.inipos;
    b.h=b.inih;
    b.k=b.inik;
    setcolor(RED);
   // rectangle(300,100,1000,200);
    getch();
    while(1){

        /*ball at bound */
        if(b.h>=RX2-b.r || b.h<=RX1+5+b.r){  //5 is added for boundary effect
            b.vx=b.vx*(-1);
        }
        if (b.h>=l.curpos-10 && b.h<=l.curpos+l.len+10){
        if(b.k>=(RY2-b.r-l.thick)){
            b.vy=b.vy*(-1);
        }
        }
        if(b.k<=RY1+5+b.r)//5 is added for boundary effect
            b.vy=b.vy*(-1);

        b.h+=b.vx;
        b.k+=b.vy;

        delay(TIME);

        moveBall(b.inih,b.inik,b.h,b.k,b.r);
        b.inih=b.h;
        b.inik=b.k;




        /* kicker */

        fflush(stdin);
        if(kbhit()){
            ch=getch();
            switch(ch)
            {
            case 'a' : case 'A':
                l.curpos=changeKicker(l.curpos,LEFT,l.len,l.thick);
                break;
            case 'd': case 'D':
                l.curpos=changeKicker(l.curpos,RIGHT,l.len,l.thick);
                break;
            default:
                break;

            }
        }



}
    return 0;
}
void mainscreen(){

    setfillstyle(SOLID_FILL,BROWN);
    floodfill(10,50,10);


}
void gameScreen(){
    setcolor(YELLOW);
    rectangle(RX1,RY1,RX2,RY2+5);
}

int  changeKicker(int cur,int dis,int len,int thick){

    if(cur >=RX1 || cur+len <=RX2)
    {
          deleteKicker(cur,thick,len);
          drawKicker(cur+dis,thick,len);
           current=cur;
          return (cur+dis);

     }
     return cur;

}
void drawKicker(int pos,int thick ,int len){
    setcolor(BLACK);
    rectangle(pos,RY2-thick,pos+len,RY2);
    return ;


}
void deleteKicker(int pos,int thick,int len){
    setcolor(BROWN);
    rectangle(pos,RY2-thick,pos+len,RY2);

}
void drawBall(int h,int k,int r){
    setcolor(BLACK);
    circle(h,k,r);

}
void moveBall(int inih,int inik,int h,int k,int r){
    deleteBall(inih,inik,r);
    setcolor(BLACK);
    drawBall(h,k,r);

}
void deleteBall(int h,int k,int r){
    setcolor(BROWN);
    circle(h,k,r);
}
void gameMenu(){
    cleardevice();
    mainscreen();
    char choice;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(TEXTX,TEXTY,    (char *)"1.Start game");
    outtextxy(TEXTX,TEXTY+100,(char *)"2.Select Level");
    outtextxy(TEXTX,TEXTY+2*100,(char *)"3.Instructions");
    outtextxy(TEXTX,TEXTY+3*100,(char *)"4.View score");
    outtextxy(TEXTX,TEXTY+4*100, (char *)"5.Quit");
    choice=getch();
    switch(choice){
    case '1':
        return ;
    case '2':
        levelScreen();
        gameMenu();
        break;

    case '3':
        instructions();
        gameMenu();
        break;


    case '4':
        playerDetail();
        gameMenu();
        break;
    case '5':
        outtextxy(500,500,(char *)"QUITTING");
        delay(25);
        exit(0);
    default:
        gameMenu();
        break;
    }

  return ;




}
void levelScreen(){
    cleardevice();
    mainscreen();

    char choice;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(TEXTX,TEXTY,(char *)"1.Easy");
    outtextxy(TEXTX,TEXTY+1*100,(char *)"2.Medium");
    outtextxy(TEXTX,TEXTY+2*100,(char *)"3.Hard");
    choice=getch();
    switch(choice){
    case '1':
        TIME=0.1;
        return ;
    case '2':
        TIME=0.001;
        return ;
    case '3':
        TIME=0.00001;
        break;
    default:
        levelScreen();
        return ;

    }
    return ;

}
void  instructions(){
    cleardevice();
    mainscreen();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(200,200,(char *)"Hit 'A' to move left or 'D' to move right ");
    getch();
    return;


}

void playerDetail(){
    FILE *fp;
    char d;
   char buffer[1];
    int y=TEXTY;
    cleardevice();
    mainscreen();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    fp=fopen("data.txt","r+");
    if(!fp){
            outtext((char *)"Error");
        return ;
    }
    while(1)
    {
        d=getc(fp);
        if(d==EOF)
           break;
        putc(d,fp);

    }
    fclose(fp);
    getch();
    return;

}

