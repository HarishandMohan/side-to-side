#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<fstream.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<graphics.h>
#include<bios.h>

int key; // For storing the key pressed while playing
long fire_cl=1; //For changing color of the fire
int level=1,score=0;//For storing the Level & Score of a single gameplay
int c=1,sborder=0,accident=0;
int midx,midy,midxx,c1,c2,c3,c4,p1=288,ptr=199;
int x[900],y[900],xcopy[900],ycopy[900],count=0;// Variables for star positions


// Prototypes for the program

void move_up();
void move_down();
void fire();
void HUD();
void generate(int);
void draw_bg(int,int);
void draw_fire(int);
void writeinator();
void movement();
void cord1();
void cord2();
void cord3();
void draw_border();
void draw_line();
void obstacle(int,int,int,int,int);
void draw_config();
void vanish_obsta(int,int,int,int);
void nameinator();
void masterreset();
void read_config();
void helpinator();
void resetinator();
void initiator();
void pauseinator();
void sound1();
void sound2();
void move_left();
void draw_char(int);
void exitinator();
void finishing();
void loadinator();
void move_right();
void accidentinator();
void gameinator();
void menuinator();
void highinator();
void optinator();
int sureinator(int pause_exit);

//Defining a class for player records

class player
{
 char name[20];
 int scre;
 public:
 void player1()
 {
 strcpy(name,"  ");
 score=0;
 }
 player()
 {
 strcpy(name," ");
 score=0;
 }

 int ret_score()
 {
  return scre;
 }
 void ins(int x,char c[20])
 {
  scre=x;
  strcpy(name,c);
 }
 void dis(int i)
 {
  cout<<name;
  gotoxy(62,14+i);
  cout<<scre;
 }
}p,pl,hs;

fstream f;
char nme[20];

//Defining a class for config records

class config
{
 public:
 int soundset;
 int controlset;
 int money;

 void  config1()
 {
  soundset=1;
  controlset=1;
  money=0;
 }
 config()
 {
  soundset=1;
  controlset=1;
  money=0;
 }
}config;

//Function to initiate graphics in required functions

void initiator()
{
 int errorcode,gdriver= DETECT,gmode;
 initgraph(&gdriver, &gmode, "C:\\TC\\bgi");
 errorcode = graphresult();
 if (errorcode != grOk)
   {
    cout<<"Graphics error: %s\n"<<grapherrormsg(errorcode);
    cout<<"Press any key to halt:";
    getch();
    exit(1);
   }
}

// To copy the cordinates of stars the star from the virtual screen

void copy()
{
 int j=0;
 for(int i=0;i<900;i++)
 {
  if(y[i]<0)
  {
   xcopy[j]=x[i];
   ycopy[j]=y[i];
   j++;
   count++;
  }
 }
}

// To generate Random cordinates for stars

void generate(int gen=0)
{
 if(gen==1)
 {
  for(int i=0;i<900;i++)
  {
   x[i]=random(700);
   y[i]=random(1000)-500;
  }
  copy();
 }
 else
 {
  for(int i=0;i<count;i++)
  {
   x[i]=xcopy[i];
   y[i]=ycopy[i]+(480+level);
  }
  for(i=count;i<900;i++)
  {
   x[i]=random(700);
   y[i]=random(478)-479 ;
  }
  count=0;
  copy();
 }
}

// To draw the stars

void draw_bg()
{
 setcolor(0);
 for(int i=0;i<900;i++)
  line(x[i],y[i]-level,x[i],y[i]-level);
 setcolor(WHITE);
 for(i=0;i<900;i++)
  line(x[i],y[i],x[i],y[i]);
}

// To erase the stars after a wave

void erase_bg()
{
 setcolor(0);
 for(int i=0;i<900;i++)
 {
  line(x[i],y[i]-level,x[i],y[i]-level);
  line(x[i],y[i]-level-(level-1),x[i],y[i]-level-(level-1));
 }
}


// Sounds for the program

void sound1()
{
 int count=5;
 if(config.soundset==1)
 {
  while(count--)
  {
   sound(1000);
   delay(10);
   nosound();
  }
 }
}

void sound2()
{
 int count=5;
 if(config.soundset==1)
 {
  while(count--)
  {
   sound(100);
   delay(10);
   nosound();
  }
 }
}

void sound3()
{
 int count=5;
 if(config.soundset==1)
 {
  while(count--)
  {
   sound(10*random(1000));
   delay(10);
   nosound();
  }
 }
}

//Function for reading previous configs

void read_config()
{
 fstream F;
 F.open("config.dat",ios::in);
 if(!F)
 goto END;
 while(!F.eof())
 F.read((char*)&config,sizeof(config));
 F.close();
 END:
}

// Splashscreen for the GAME

void splashinator()
{
 initiator();
 generate(1);
 draw_bg();
 setcolor(14);
 settextstyle(4,0,9);
 outtextxy(getmaxx()-500,40," SIDE ");
 outtextxy(getmaxx()-500,130,"  TO ");
 outtextxy(getmaxx()-500,getmaxy()-260," SIDE ");
 setcolor(GREEN);
 settextstyle(11,0,3);
 outtextxy(getmaxx()-250,getmaxy()-40," PRESS ANY KEY TO CONTINUE...");
 getch();
 read_config();
 closegraph();
 menuinator();
}

// Menu for the Program

void menuinator()
{
 initiator();
 draw_bg();
 int bios,clr=2;
 //gotoxy(65,8);
 //cout<<"Money - "<<config.money;
 rectangle(0,0,getmaxx(),getmaxy()-3);
 rectangle(3,3,getmaxx()-3,getmaxy()-6);
 setcolor(GREEN);
 settextstyle(4,0,9);
 outtextxy(30,3,"Menu");
 setcolor(WHITE);
 line(0,130,getmaxx(),130);
 line(0,133,getmaxx(),133);
 setcolor(14);
 settextstyle(3,0,2);
 outtextxy(getmaxx()/2+100,getmaxy()/2-40,"Start Game");
 outtextxy(getmaxx()/2+100,getmaxy()/2,"High Scores");
 outtextxy(getmaxx()/2+100,getmaxy()/2+40,"Options");
 outtextxy(getmaxx()/2+100,getmaxy()/2+80,"Help");
 outtextxy(getmaxx()/2+100,getmaxy()/2+120,"Exit");
 setcolor(clr);
 outtextxy(getmaxx()/2+80,ptr,">");
 int j=0,loop=0;
 while(loop==0)
 {
   while(!kbhit());
   if(kbhit())
   {
   bios=bioskey(0);
   if(bios==20480)
   {
    if(ptr==getmaxy()/2+120)
    {
     ptr-=160;
     setcolor(BLACK);
     outtextxy(getmaxx()/2+80,getmaxy()/2+120,">");
     setcolor(GREEN);
     outtextxy(getmaxx()/2+80,ptr,">");
     sound1();
    }
    else if(ptr<getmaxy()/2+120)
    {
      setcolor(BLACK);
      outtextxy(getmaxx()/2+80,ptr,">");
      ptr+=40;
      if(ptr==getmaxy()/2+120)
       setcolor(RED);
      else
       setcolor(BLUE);
      outtextxy(getmaxx()/2+80,ptr,">");
      sound1();
    }
   }
   if(bios==18432)
   {
    if(ptr==getmaxy()/2-40)
    {
     ptr+=160;
     setcolor(BLACK);
     outtextxy(getmaxx()/2+80,getmaxy()/2-40,">");
     setcolor(RED);
     outtextxy(getmaxx()/2+80,ptr,">");
     sound1();
     j=1;
    }
    if(ptr>getmaxy()/2-40 && j==0)
    {
      setcolor(BLACK);
      outtextxy(getmaxx()/2+80,ptr,">");
      ptr-=40;
      if(ptr==getmaxy()/2-40)
       setcolor(GREEN);
      else
       setcolor(BLUE);
      outtextxy(getmaxx()/2+80,ptr,">");
      sound1();
    }
    j=0;
   }
   if(bios==7181 && ptr==getmaxy()/2-40)
   {
    sound2();
    cleardevice();
    closegraph();
    clr=2;
    nameinator();
   }
   if(bios==7181 && ptr==getmaxy()/2)
   {
    sound2();
    cleardevice();
    closegraph();
    clr=1;
    highinator();
   }
   if(bios==7181 && ptr==getmaxy()/2+40)
   {
    sound2();
    cleardevice();
    closegraph();
    clr=1;
    optinator();
   }
   if(bios==7181 && ptr==getmaxy()/2+80)
   {
    sound2();
    cleardevice();
    closegraph();
    clr=1;
    helpinator();
   }
   if(bios==7181 && ptr==getmaxy()/2+120)
   {
    sound2();
    clr=4;
    closegraph();
    exitinator();
   }

   while(kbhit())
   getch();
 }
}
 closegraph();
}

//Function to get the name of the player

void nameinator()
{

 // Graphic Section

 initiator();
 draw_bg();
 setcolor(WHITE);
 rectangle(0,0,getmaxx(),getmaxy()-3);
 rectangle(3,3,getmaxx()-3,getmaxy()-6);
 setcolor(GREEN);
 settextstyle(1,0,3);
 outtextxy(getmaxx()/2-200,getmaxy()/2-43,"Enter Your Name :");

 // Working Section

 char letter;
 int location=0,letterbios;
 while(letter!=13)
 {
   NAME:
   letter=getch();
   letterbios=bioskey(letter);

   //In case of a space

   if(letterbios==8192)
   {
    gotoxy(45+(location+1),14);
    nme[location]=' ';
    location++;
   }

   // In case of a letter

   if(letter>=97&&letter<=122)
   {
    gotoxy(45+location,14);
    if(location==0 || nme[location-1]==' ')
    {
     letter=toupper(letter);
    }
    nme[location]=letter;
    location++;
    cout<<letter;
    setcolor(0);
    settextstyle(11,0,3);
    outtextxy(350,400,"Enter Your Name To Proceed...");
   }

   // In case of a backspace

   if(letter==8 && location>0)
   {
    location--;
    nme[location]='\0';
    cout<<"\b \b";
   }
  }

 //In case no name is entered

 nme[location+1]='\0';
 if(strlen(nme)==0)
 {
  setcolor(YELLOW);
  settextstyle(11,0,3);
  outtextxy(350,400,"Enter Your Name To Proceed...");
  goto NAME;
 }

 cleardevice();
 closegraph();
 loadinator();
}

//Function to display the loading screen

void loadinator()
{
 for(int i=0;i<11;i++)
 {
  textcolor(i);
  clrscr();
  gotoxy(2,21);
  puts("LOADING...");
  gotoxy(2,23);
  for(int j=0;j<=i;j++)
  {
   if(j==2)
   {
    gotoxy(54,2);
    cout<<">> Initializing Graphics";
    gotoxy(14,23);
   }
   if(j==4)
   {
    gotoxy(54,3);
    cout<<">> Initializing Character";
    gotoxy(28,23);
   }
   if(j==6)
   {
    gotoxy(54,4);
    cout<<">> Initializing Obstacles";
    gotoxy(42,23);
   }
   if(j==8)
   {
    if(config.soundset==1)
    {
     gotoxy(54,5);
     cout<<">> Initializing Sound";
     gotoxy(56,23);
    }
    else
    {
     gotoxy(54,5);
     cout<<">> Disabling Sound";
     gotoxy(56,23);
    }
   }
   if(j==9)
   {
    gotoxy(54,6);
    cout<<">> Good to GO";
    gotoxy(56,23);
   }
   cout<<"�������";
   if(j==10)
    cout<<"�������";
  }
  delay(500);
 }
 delay(4000);
 resetinator();
 gameinator();
}

//Function for the gameplay

void gameinator()
{

 initiator();
 setcolor(GREEN);
 midy=getmaxy()/2+150;
 midx=288;
 midxx=319;
 int obst_color;

 while(accident!=1)
 {
  int x1=103*random(3),y1=0,x2=103*random(3),y2=0;
  obstacle(x1,y1,x2,y2,obst_color);
  obst_color=random(10)+1;
  sound3();
  if(accident!=1)
  {
   score++;
   level=score/5+1;
   config.money++;
  }
 }
 closegraph();
 finishing();
}

//Function to draw the obstacle and move it

void obstacle(int x,int y,int X, int Y,int obst_color)
{
 char chh;
 while(y<getmaxy())
 {
  HUD();
  fire_cl++;
  draw_fire(fire_cl);
  accidentinator();
  if(kbhit())
  {
   movement();
   while(kbhit())getch();
   accidentinator();
  }
  else
 // speed=0;
  setcolor(YELLOW);
  switch(x)
  {
   case 103:
    x=x+10;
    break;
   case 206:
    x=x+20;
  }
  switch(X)
  {
   case 103:
    X=X+10;
    break;
   case 206:
    X=X+20;
  }
  draw_bg();
  setcolor(obst_color+1);
  setfillstyle(9,obst_color+1);
  fillellipse(207+x,y,50,50);
  setfillstyle(9,obst_color+1);
  fillellipse(207+X,Y,50,50);
  vanish_obsta(x,y,X,Y);
  y=y+level;//+speed;
  Y=Y+level;//+speed;
  for(int i=0;i<900;i++)
   ::y[i]=::y[i]+level;
  if(sborder>=getmaxy())
  {
   sborder=0;c=random(10)+1;
   erase_bg();
   generate();
  }
  sborder+=level;
  c1=155+x;
  c2=155+X;
  c3=y+100;
  c4=Y+100;
  if(accident==1)break;
 }
}

//Function to compare the key input by the user during gameplay

void movement()
{
 key=bioskey(0);
 if(key==283)
 {
  sound2();
  pauseinator();
 }
 if(key==14626)
  fire();
 if(midxx==319)
  cord2();
 else if(midxx==206)
  cord1();
 else if(midxx==432)
  cord3();
}


// HUD for the gameplay

void HUD()
{
 draw_char(1);
 setcolor(YELLOW);
 settextstyle(4,1,6);
 outtextxy(30,20," SIDE TO SIDE ");
 rectangle(getmaxx()-110,20,getmaxx()-2,90);
 line(getmaxx()-110,55,getmaxx()-2,55);
 gotoxy(3,2);
 cout<<" ESC - Pause";
 draw_config();
  gotoxy(69,3);
  textcolor(RED);
  cout<<"SCORE - "<<score;
  gotoxy(69,5);
  cout<<"LEVEL - "<<level;
}

//Function to draw the character of thr game

void draw_char(int i)
{

 int body[30],tri[6],fire1[6],fire2[6];

 //1
 body[0]=midxx;
 body[1]=midy-70;
 //2
 body[2]=midxx+10;
 body[3]=midy;
 //3
 body[4]=midxx+30;
 body[5]=midy-31;
 //4
 body[6]=midxx+40;
 body[7]=midy+31;
  //5
 body[8]=midxx+25;
 body[9]=midy+20;
//6
 body[10]=midxx+20;
 body[11]=midy+10;
 //7
 body[12]=midxx+10;
 body[13]=midy+10;
 //8
 body[14]=midxx+5;
 body[15]=midy+20;
 //9
 body[16]=midxx-5;
 body[17]=midy+20;
 //10
 body[18]=midxx-10;
 body[19]=midy+10;
 //11
 body[20]=midxx-20;
 body[21]=midy+10;
 //12
 body[22]=midxx-25;
 body[23]=midy+20;
 //13
 body[24]=midxx-40;
 body[25]=midy+31;
 //14
 body[26]=midxx-30;
 body[27]=midy-31;
 //15
 body[28]=midxx-10;
 body[29]=midy;

 if(i!=0)
 {
  setcolor(BLACK);
  setfillstyle(1,WHITE);
 }

 else
 {
  setcolor(BLACK);
  setfillstyle(1,BLACK);
 }

 fillpoly(15,body);

 if(i!=0)
 setcolor(BLUE);
 else
 setcolor(BLACK);
 line(midxx+10,midy+10,midxx+20,midy+10);
 line(midxx+10,midy+11,midxx+20,midy+11);

 line(midxx-10,midy+10,midxx-20,midy+10);
 line(midxx-10,midy+11,midxx-20,midy+11);

 setcolor(BLACK);
 line(midxx-40,midy+6,midxx-20,midy+14);
 line(midxx-40,midy+8,midxx-20,midy+16);
 line(midxx-40,midy+10,midxx-20,midy+18);

 line(midxx+40,midy+6,midxx+20,midy+14);
 line(midxx+40,midy+8,midxx+20,midy+16);
 line(midxx+40,midy+10,midxx+20,midy+18);

 setfillstyle(1,BLACK);

 tri[0]=midxx;
 tri[1]=midy-60;

 tri[2]=midxx+5;
 tri[3]=midy-25;

 tri[4]=midxx-5;
 tri[5]=midy-25;

 fillpoly(3,tri);

}

void draw_fire(int i)
{
 int fire1[6],fire2[6];
 setcolor(BLACK);

 if(i==0)
  setfillstyle(1,BLACK);
 else if(i%2==0 || i%3==0)
  setfillstyle(1,4);
 else
  setfillstyle(1,14);

 fire1[0]=midxx+20;
 fire1[1]=midy+12;

 fire1[2]=midxx+10;
 fire1[3]=midy+12;

 fire1[4]=midxx+15;
 fire1[5]=midy+35;

 fillpoly(3,fire1);

 if(i==0)
  setfillstyle(1,BLACK);
 else if(i%2==0 || i%3==0)
  setfillstyle(1,4);
 else
  setfillstyle(1,14);


 fire2[0]=midxx-20;
 fire2[1]=midy+12;

 fire2[2]=midxx-10;
 fire2[3]=midy+12;

 fire2[4]=midxx-15;
 fire2[5]=midy+35;

 fillpoly(3,fire2);
}

//Function to draw config status of the gameplay

void draw_config()
{
 int sound[12],maxx=getmaxx(),maxy=getmaxy();
 if(config.soundset==1)
 {
  setcolor(GREEN);
  setfillstyle(1,GREEN);
  arc(maxx-20,maxy-50,320,45,10);
  arc(maxx-20,maxy-50,320,45,15);
  arc(maxx-20,maxy-50,320,45,20);
 }
 else
 {
  setcolor(RED);
  settextstyle(1,0,1);
  setfillstyle(1,RED);
  outtextxy(maxx-10,maxy-63,"x");
 }
 //1
 sound[0]=maxx-30;
 sound[1]=maxy-60;
 //2
 sound[2]=maxx-25;
 sound[3]=maxy-60;
 //3
 sound[4]=maxx-20;
 sound[5]=maxy-70;
 //4
 sound[6]=maxx-20;
 sound[7]=maxy-32;
 //5
 sound[8]=maxx-25;
 sound[9]=maxy-40;
 //6
 sound[10]=maxx-30;
 sound[11]=maxy-40;

 fillpoly(6,sound);

 if(config.controlset==1)
 {
  settextstyle(1,0,1);
  setcolor(YELLOW);
  rectangle(maxx-110,maxy-62,maxx-50,maxy-40);
  line(maxx-80,maxy-62,maxx-80,maxy-40);
  setcolor(WHITE);
  outtextxy(maxx-107,maxy-63,"<- ->");
 }
 else
 {
  settextstyle(1,0,1);
  setcolor(YELLOW);
  rectangle(maxx-110,maxy-62,maxx-50,maxy-40);
  line(maxx-80,maxy-62,maxx-80,maxy-40);
  setcolor(WHITE);
  outtextxy(maxx-100,maxy-63,"A  D");
 }
}

//Function to erase the trail left by the obstacle

void vanish_obsta(int x,int y,int X, int Y)
{
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 fillellipse(207+x,y,50,50);
 setfillstyle(9,BLACK);
 fillellipse(207+X,Y,50,50);
}

//Function to pause and display the pause menu

void pauseinator()
{
 START:
 int pause=1,bios=7181,ptr=190,pause_exit=0;
 setfillstyle(SOLID_FILL,BLACK);
 bar3d(getmaxx()/2-74,130,getmaxx()/2+74,280,0,0);
 settextstyle(1,0,2);
 setcolor(14);
 rectangle(getmaxx()/2-75,130,getmaxx()/2+75,280);
 outtextxy(getmaxx()/2-35,150,"PAUSED");
 settextstyle(3,0,1);
 outtextxy(getmaxx()/2-30,190,"Resume");
 outtextxy(getmaxx()/2-30,210,"Menu");
 outtextxy(getmaxx()/2-30,230,"Exit");
 setcolor(2);
 outtextxy(getmaxx()/2-45,ptr,">");
 while(pause!=0)
 {
  while(!kbhit());
  if(kbhit())
  {
   bios=bioskey(0);
   if(bios==20480 && ptr<230)
   {
    setcolor(0);
    outtextxy(getmaxx()/2-45,ptr,">");
    ptr+=20;
    if(ptr==230)
    setcolor(4);
    else
    setcolor(2);
    outtextxy(getmaxx()/2-45,ptr,">");
    sound1();
   }
   if(bios==18432 && ptr>190)
   {
    setcolor(0);
    outtextxy(getmaxx()/2-45,ptr,">");
    ptr-=20;
    setcolor(2);
    outtextxy(getmaxx()/2-45,ptr,">");
    sound1();
   }
   if(bios==7181 && ptr==190)
   {
    sound2();
    pause=0;
   }
   if(bios==7181 && ptr==210)
   {
    sound2();
    sureinator(pause_exit);
    goto START;
   }
   if(bios==7181 && ptr==230)
   {
    sound2();
    pause_exit=1;
    sureinator(pause_exit);
    goto START;
   }
  }
 }
 setcolor(0);
 rectangle(getmaxx()/2-75,130,getmaxx()/2+75,280);
 setfillstyle(SOLID_FILL,BLACK);
 bar3d(getmaxx()/2-74,130,getmaxx()/2+74,280,0,0);
 settextstyle(1,0,2);
 outtextxy(getmaxx()/2-35,150,"PAUSED");
 settextstyle(3,0,1);
 outtextxy(getmaxx()/2-30,190,"Resume");
 outtextxy(getmaxx()/2-30,210,"Menu");
 outtextxy(getmaxx()/2-30,230,"Exit");
 outtextxy(getmaxx()/2-45,ptr,">");
 setcolor(3);
 //draw_line();
}

//Function to display the "Are you sure" menu

int sureinator(int pause_exit)
{
 int sure=200,bios;
 setcolor(14);
 rectangle(getmaxx()/2-75,130,getmaxx()/2+75,280);
 setfillstyle(SOLID_FILL,BLACK);
 bar3d(getmaxx()/2-74,130,getmaxx()/2+74,280,0,0);
 settextstyle(1,0,1);
 outtextxy(getmaxx()/2-65,150,"ARE YOU SURE");
 settextstyle(3,0,1);
 outtextxy(getmaxx()/2-17,200,"YES");
 outtextxy(getmaxx()/2-15,230,"NO");
 setcolor(4);
 outtextxy(getmaxx()/2-30,200,">");
 int i=1;
 while(i==1)
 {
  while(!kbhit());
   if(kbhit())
   {
    bios=bioskey(0);
    if(bios==20480 && sure==200)
    {
     sure+=30;
     setcolor(0);
     outtextxy(getmaxx()/2-30,200,">");
     setcolor(2);
     outtextxy(getmaxx()/2-30,230,">");
     sound1();
    }
    if(bios==18432 && sure==230)
    {
     sure-=30;
     setcolor(0);
     outtextxy(getmaxx()/2-30,230,">");
     setcolor(4);
     outtextxy(getmaxx()/2-30,200,">");
     sound1();
    }
    if(bios==7181 && sure==200)
    {
     if(pause_exit==0)
     {
      sound2();
      closegraph();
      menuinator();
     }
     if(pause_exit==1)
     {
      sound2();
      closegraph();
      exitinator();
     }
    }
    if(bios==7181 && sure==230)
    {
     sound2();
     break;
    }
   }
  }
return 0;
}

// Functions for the movement of the character

void cord1()
{
 if(config.controlset==1)
 {
  switch(key)
  {
   case 19712:
   move_right();
   break;
   case 18432:
   move_up();
   break;
   case 20480:
   move_down();
   break;
  }
 }
 else if(config.controlset==0)
 {
  switch(key)
  {
   case 8292:
   move_right();
   break;
   case 4471:
   move_up();
   break;
   case 8051:
   move_down();
   break;
  }
 }
}

void cord2()
{
 if(config.controlset==1)
 {
  switch(key)
  {
   case 19712:
   move_right();
   break;
   case 19200:
   move_left();
  break;
  case 18432:
  move_up();
  break;
  case 20480:
  move_down();
  break;
  }
 }
 else if(config.controlset==0)
 {
  switch(key)
  {
   case 8292:
   move_right();
   break;
   case 7777:
   move_left();
     break;
   case 4471:
  move_up();
  break;
  case 8051:
  move_down();
  break;
   }
 }
}

void cord3()
{

 if(config.controlset==1)
 {
  switch(key)
  {
   case 19200:
   move_left();
   break;
   case 18432:
   move_up();
   break;
   case 20480:
   move_down();
   break;
  }
 }

 else if(config.controlset==0)
 {
  switch(key)
  {
   case 7777:
   move_left();
   break;
   case 4471:
   move_up();
   break;
   case 8051:
   move_down();
   break;
  }
 }
}

//Function to move the character right

void move_right()
{
 sound2();
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 draw_char(0);
 draw_fire(0);
 midxx=midxx+113;
 setfillstyle(1,getmaxcolor());
 draw_char(fire_cl);
 p1=midxx-31;
}

//Function to move the character left

void move_left()
{
 sound2();
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 draw_char(0);
 draw_fire(0);
 midxx=midxx-113;
 setfillstyle(1,getmaxcolor());
 draw_char(fire_cl);
 p1=midxx-31;
}

//Function to say if the character colloides with the obstacles

void accidentinator()
{
 if(  ((p1-c1)==20) && (((midy-70-c3)<=-45)&&((midy-70-c3)>=-250)) || ((p1-c2)==20 && (((midy-70-c4)<=-45)&&((midy-70-c4)>=-250))))
 accident=1;
}

//Function to display the results of the gameplay

void finishing()
{
 initiator();
 generate(1);
 draw_bg();
 int count=30;
 setcolor(RED);
 settextstyle(4,1,6);
 outtextxy(getmaxx()-500,40," GAME OVER ");
 setcolor(BLUE);
 settextstyle(1,0,1);
 outtextxy(350,185," LEVEL = ");
 outtextxy(350,220," SCORE = ");
 gotoxy(56,13);
 cout<<level;
 gotoxy(56,15);
 cout<<score;
 fstream f;
 f.open("score.dat",ios::in);
 f.read((char*)&hs,sizeof(hs));
 if(hs.ret_score()<=score)
 {
 setcolor(GREEN);
 settextstyle(4,0,6);
 outtextxy(300,300,"High Score");
 }
 if(config.soundset==1)
 {
  while(count--)
  {
   sound(10*random(100));
   delay(75);
   nosound();
  }
 }
 writeinator();
 setcolor(14);
 settextstyle(3,0,3);
 outtextxy(500,380,"Restart");
 outtextxy(500,400,"Menu");
 outtextxy(500,420,"Exit");
 setcolor(GREEN);
 outtextxy(480,380,">");
 int i=1,bios,ptr=380;
 while(i==1)
 {
  while(!kbhit());
  if(kbhit())
  {
   bios=bioskey(0);
   if(bios==20480 && ptr<420)
   {
     setcolor(0);
     outtextxy(480,ptr,">");
     ptr+=20;
     if(ptr==420)
     setcolor(RED);
     else
     setcolor(GREEN);
     outtextxy(480,ptr,">");
     sound1();
   }
   if(bios==18432 && ptr>380)
   {
     setcolor(0);
     outtextxy(480,ptr,">");
     ptr-=20;
     setcolor(GREEN);
     outtextxy(480,ptr,">");
     sound1();
    }
   if(bios==7181 && ptr==380)
   {
    sound2();
    closegraph();
    generate(1);
    loadinator();
   }
   if(bios==7181 && ptr==400)
   {
    sound2();
    closegraph();
    menuinator();
   }
   if(bios==7181 && ptr==420)
   {
    sound2();
    exitinator();
   }
  }
 }
}

//Function to write the records of highscores

void writeinator()
{
 fstream f1;
 f1.open("temp.dat",ios::out);
 char ch='a';
 f.open("score.dat",ios::out|ios::in|ios::ate);
 p.ins(score,nme);
 f.seekp(0,ios::end);
 if(f.tellp()==0)
 {
  f.seekp(0);
  f1.write((char*)&p,sizeof(p));
  cout<<endl;
 }
 else
 {
  f1.seekp(0,ios::beg);
  f.seekg(0,ios::beg);
  while(!f.eof())
  {
   f.read((char*)&pl,sizeof(pl));
   if(p.ret_score()>=pl.ret_score())
   {
    f1.write((char*)&p,sizeof(p));
    ch='b';
    f1.write((char*)&pl,sizeof(pl));
    break;
   }
   else if(!f.eof())
   {
    f1.write((char*)&pl,sizeof(pl));
   }
  }
  if(ch=='a')
  {
   f1.write((char*)&p,sizeof(p));
  }
  else
  {
   while(!f.eof())
   {
    f.read((char*)&pl,sizeof(pl));
    if(!f.eof())
    {
     f1.write((char*)&pl,sizeof(pl));
    }
   }
  }
 }
 f.close();
 f1.close();
 remove("score.dat");
 rename("temp.dat","score.dat");
 resetinator();
}

//Function to display the credits of the game

void exitinator()
{
 fstream f;
 initiator();
 setcolor(GREEN);
 settextstyle(3,0,2);
 outtextxy(500,350," DONE BY:");
 setcolor(8);
 outtextxy(500,370," Mohan Raj R ");
 outtextxy(500,390," Harish R ");
 f.open("config.dat",ios::out);
 f.write((char*)&config,sizeof(config));
 f.close();
 getch();
 closegraph();
 exit(0);
}

//Function to display highscores

void highinator()
{
 initiator();
 draw_bg();
 rectangle(0,0,getmaxx(),getmaxy()-3);
 rectangle(3,3,getmaxx()-3,getmaxy()-6);
 setcolor(GREEN);
 settextstyle(4,0,9);
 outtextxy(120,3,"HighScores");
 setcolor(WHITE);
 line(0,130,getmaxx(),130);
 line(0,133,getmaxx(),133);
 settextstyle(1,0,1);
 circle(25,25,17);
 outtextxy(10,12," <  Bksp");
 setcolor(14);
 settextstyle(3,0,2);
 int i=1;
 gotoxy(20,12);
 cout<<"  Position ";
 cout<<"           ";
 cout<<" Name ";
 cout<<"           ";
 cout<<" Score ";
 fstream f;
 f.open("score.dat",ios::nocreate|ios::binary|ios::in);
 f.seekg(0);
 while(!f.eof())
 {
  if(i>10)
  break;
  f.read((char*)&pl,sizeof(pl));
  gotoxy(25,14+i);
  if(f.eof()!=0)
  break;
  cout<<i;
  gotoxy(42,14+i);
  pl.dis(i);
  i++;
 }
 f.close();
 int k=1,bios;
 while(k==1)
 {
  while(!kbhit());
  if(kbhit())
  {
   bios=bioskey(0);
   if(bios==3592)
   {
    while(kbhit())getch();
    sound2();
    closegraph();
    menuinator();
   }
  }
 }
 closegraph();
}

// Function for the options menu

void optinator()
{
 initiator();
 draw_bg();
 int ptr,bios,ptrx;
 rectangle(0,0,getmaxx(),getmaxy()-3);
 rectangle(3,3,getmaxx()-3,getmaxy()-6);
 setcolor(GREEN);
 settextstyle(4,0,8);
 outtextxy(200,20,"Options");
 setcolor(WHITE);
 line(0,130,getmaxx(),130);
 line(0,133,getmaxx(),133);
 line(getmaxx()/2,133,getmaxx()/2,getmaxy()-6);
 setcolor(WHITE);
 settextstyle(1,0,1);
 circle(25,25,17);
 outtextxy(10,12," <  Bksp");
 setcolor(14);
 settextstyle(4,0,3);
 outtextxy(550,440,"R-Reset");
 setcolor(WHITE);
 outtextxy(getmaxx()/2-200,getmaxy()/2,"SOUND");
 setcolor(14);
 settextstyle(3,0,2);
 outtextxy(getmaxx()/2-175,getmaxy()/2+40,"Yes");
 if(config.soundset==1)
 {
  setcolor(GREEN);
  outtextxy(getmaxx()/2-120,getmaxy()/2+40,"��");
 }
 else if(config.soundset==0)
 {
  setcolor(RED);
  outtextxy(getmaxx()/2-120,getmaxy()/2+80,"��");
 }
 setcolor(14);
 outtextxy(getmaxx()/2-175,getmaxy()/2+80,"No");
 settextstyle(4,0,3);
 setcolor(WHITE);
 outtextxy(getmaxx()/2+100,getmaxy()/2,"Controls");
 setcolor(14);
 settextstyle(3,0,2);
 outtextxy(getmaxx()/2+100,getmaxy()/2+40," Arrows ");
 if(config.controlset==1)
 {
  setcolor(GREEN);
  outtextxy(getmaxx()/2+200,getmaxy()/2+40,"��");
 }
 else if(config.controlset==0)
 {
  setcolor(GREEN);
  outtextxy(getmaxx()/2+200,getmaxy()/2+80,"��");
 }
 setcolor(14);
 outtextxy(getmaxx()/2+100,getmaxy()/2+80," WASD ");
 setcolor(GREEN);
 outtextxy(getmaxx()/2-195,getmaxy()/2+40,">");
 ptr=getmaxy()/2+40;
 ptrx=getmaxx()/2-195;
 int i=1;
 while(i==1)
 {
  while(!kbhit());
  if(kbhit())
  {
   bios=bioskey(0);
   if(bios==20480)
   {
    if(ptr==getmaxy()/2+40 && ptrx==getmaxx()/2-195)
    {
     setcolor(BLACK);
     outtextxy(ptrx,ptr,">");
     ptr+=40;
     setcolor(RED);
     outtextxy(ptrx,ptr,">");
     sound1();
    }
    if(ptr==getmaxy()/2+40 && ptrx==getmaxx()/2+90)
    {
     setcolor(BLACK);
     outtextxy(ptrx,ptr,">");
     ptr+=40;
     setcolor(GREEN);
     outtextxy(ptrx,ptr,">");
     sound1();
    }
   }
   if(bios==18432)
   {
    if(ptr==getmaxy()/2+80 &&  ptrx==getmaxx()/2-195)
    {
     setcolor(BLACK);
     outtextxy(ptrx,ptr,">");
     ptr-=40;
     setcolor(GREEN);
     outtextxy(ptrx,ptr,">");
     sound1();
    }
    if(ptr==getmaxy()/2+80 &&  ptrx==getmaxx()/2+90)
    {
     setcolor(BLACK);
     outtextxy(ptrx,ptr,">");
     ptr-=40;
     setcolor(GREEN);
     outtextxy(ptrx,ptr,">");
     sound1();
    }
   }
   if(bios==19712)
   {
    if(ptrx==getmaxx()/2-195)
    {
     setcolor(BLACK);
     outtextxy(getmaxx()/2-195,ptr,">");
     setcolor(GREEN);
     ptrx=getmaxx()/2+90;
     outtextxy(getmaxx()/2+90,ptr,">");
     sound1();
    }
   }
   if(bios==19200)
   {
    if(ptrx==getmaxx()/2+90)
    {
     setcolor(BLACK);
     outtextxy(getmaxx()/2+90,ptr,">");
     if(ptr==getmaxy()/2+40)
     setcolor(GREEN);
     if(ptr==getmaxy()/2+80)
     setcolor(RED);
     ptrx=getmaxx()/2-195;
     outtextxy(getmaxx()/2-195,ptr,">");
     sound1();
    }
   }
   if(bios==3592)
   {
    sound2();
    closegraph();
    menuinator();
   }
   if(bios==4978)
   {
    sound2();
    closegraph();
    masterreset();
   }
   while(kbhit())getch();
  }
  if(bios==7181)
  {
   if(ptrx==getmaxx()/2-195 && ptr==getmaxy()/2+40)
   {
    config.soundset=1;
    setcolor(BLACK);
    outtextxy(getmaxx()/2-120,getmaxy()/2+80,"��");
    setcolor(GREEN);
    outtextxy(getmaxx()/2-120,getmaxy()/2+40,"��");
    sound2();
   }
   if(ptrx==getmaxx()/2-195 && ptr==getmaxy()/2+80)
   {
    config.soundset=0;
    setcolor(BLACK);
    outtextxy(getmaxx()/2-120,getmaxy()/2+40,"��");
    setcolor(RED);
    outtextxy(getmaxx()/2-120,getmaxy()/2+80,"��");
   }
   if(ptrx==getmaxx()/2+90 && ptr==getmaxy()/2+40)
   {
    setcolor(BLACK);
    outtextxy(getmaxx()/2+200,getmaxy()/2+80,"��");
    setcolor(GREEN);
    outtextxy(getmaxx()/2+200,getmaxy()/2+40,"��");
    sound2();
    config.controlset=1;
   }
   if(ptrx==getmaxx()/2+90 && ptr==getmaxy()/2+80)
   {
    setcolor(BLACK);
    outtextxy(getmaxx()/2+200,getmaxy()/2+40,"��");
    setcolor(GREEN);
    outtextxy(getmaxx()/2+200,getmaxy()/2+80,"��");
    config.controlset=0;
    sound2();
   }
  }
 }
}

//Function to reset the config and highscore data of the game

void masterreset()
{
 char password[20];

 initiator();
 draw_bg();
 setcolor(WHITE);
 rectangle(0,0,getmaxx(),getmaxy()-3);
 rectangle(3,3,getmaxx()-3,getmaxy()-6);
 setcolor(GREEN);
 settextstyle(1,0,3);
 outtextxy(getmaxx()/2-120,getmaxy()/2-43,"Enter Password : ");
 gotoxy(51,14);
 int i=1;
 while(i!=0)
 {

  char pa;int o=0;
  while(pa!=13)
  {
   pa=getch();
   if(pa>=97&&pa<=122)
   {
    gotoxy(51+o,14);
    password[o]=pa;
    o++;
    cout<<"*";
   }
   if(pa==8&&o>0)
   {
    o--;
    password[o]='\0';
    cout<<"\b \b";
   }
  }
  while(o<=20)
  {
   password[o]='\0';
   o++;
  }
  if(strcmp("secret",password)==0)
  {
   fstream f1,f2;
   f1.open("temp1.dat",ios::in);
   f2.open("temp2.dat",ios::in);
   remove("score.dat");
   remove("config.dat");
   rename("temp1.dat","score.dat");
   rename("temp2.dat","config.dat");
   f1.close();
   f2.close();
   setcolor(2);
   settextstyle(2,0,6);
   outtextxy(400,400,"Reset Successful ");
   config.config1();
   pl.player1();
   delay(1000);
   break;
  }
  else
  {
   setcolor(RED);
   settextstyle(2,0,6);
   outtextxy(400,400," Password Incorrect");
   delay(1000);
   i=0;
  }
 }
 closegraph();
 optinator();
}


//Function for the help screen

void helpinator()
{
 initiator();
 draw_bg();
 int bios;
 rectangle(0,0,getmaxx(),getmaxy()-3);
 rectangle(3,3,getmaxx()-3,getmaxy()-6);
 setcolor(GREEN);
 settextstyle(4,0,8);
 outtextxy(250,10,"Help");
 setcolor(WHITE);
 line(0,130,getmaxx(),130);
 line(0,133,getmaxx(),133);
 setcolor(WHITE);
 settextstyle(1,0,1);
 circle(25,25,17);
 outtextxy(10,12," <  Bksp");
 gotoxy(2,10);
 cout<<" The Aim of the game is to avoid crashing the spacecraft with the oncoming";
 gotoxy(2,11);
 cout<<" asteroids and record a high score.";
 gotoxy(2,13);
 cout<<" The Spacecraft can either be controlled by the 'Arrow keys' or ' WASD keys'.";
 gotoxy(2,14);
 cout<<" The choice is up to the player. It can changed in the options menu.";
 gotoxy(2,16);
 cout<<" If the sounds in the game seems to be disturbing for the player, It can be ";
 gotoxy(2,17);
 cout<<" disabled in the options menu.";
 gotoxy(2,19);
 cout<<" You can keep track of your records in the Highscores section of the game.";
 gotoxy(2,21);
 cout<<" During Gameplay, The game can be paused using 'Esc'.";
 gotoxy(2,23);
 cout<<" Use arrow to control the movement of the character by default";
 gotoxy(2,25);
 cout<<" You can reset the game in the options menu";
 int i=1;
 while(i==1)
 {
  while(!kbhit());
  if(kbhit())
  {
   bios=bioskey(0);
   if(bios==3592)
   {
    sound2();
    menuinator();
   }
  }
 }

}

//Function to reset the values

void resetinator()
{
 midx=288;
 midxx=319;
 level=1;
 p1=288;
 c=1;
 score=0;
 sborder=0;
 accident=0;
 c3=0;
 c4=0;
}

void main()
{
 clrscr();
 randomize();
 splashinator();
}
