#include <iostream>
#include <stdlib.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include<cstring>
#include <stdlib.h>  // rand
#include <time.h>
#include <sstream>
#include <string.h>
#include <ctime>
using namespace std;
int mouseX;
int mouseY;
int previousMouseX;
int previousMouseY;
int windowSize=600;
int characterBodyHalfSize;
bool first=true;
bool eyeLeft=true;
int _moveEye=0;
int16_t eyeMoveCount=0;
int16_t enemySpeed=4;
int16_t increaseEnemySpeedPerSec=8;
int16_t mouthShut=0;
//enemy coordinaes
int enemy1X;
int enemy1Y;
int enemy2X;
int enemy2Y;
int enemy3X;
int enemy3Y;

bool enemy1Left=false;
bool enemy1Up=true;
bool enemy2Left=true;
bool enemy2Up=true;
bool enemy3Left=true;
bool enemy3Up=true;
bool gameOverFlag=true;;
bool enemyMouthOpen=true;

stringstream strs;
char gameOver[] = "KHAISO DHORA";
clock_t start;
int score;

float getX(int x)
{
    return (float)x/300;
}

float getY(int x)
{
    return (float)x/300;
}

void resetEnemy()
{
    enemySpeed=4;
    increaseEnemySpeedPerSec=8;
    characterBodyHalfSize=50;
    mouseX=0;
    mouseY=0;
    previousMouseX=0;
    previousMouseY=0;

    start = std::clock();
    srand(time(NULL));

    enemy1X=rand() % 160+80;
    enemy1Y=rand() % 200+80;
    enemy2X=rand() % 50 -250;
    enemy2Y=rand() % 50 -250;
    enemy3X=rand() % 50 -250;
    enemy3Y=rand() % 250;
    gameOverFlag=false;
}

void mouseMotion(int x, int y)
{
    mouseX = x-300;
    mouseY = 300-y;
}
void printText( float x, float y, char *st)
{
    int l,i;


    l=strlen( st ); // see how many characters are in text string.
    //glDisable(GL_LIGHTING);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);

    }

}


void keyboard(unsigned char key, int x, int y) {
//find key codes: https://www.cambiaresearch.com/articles/15/javascript-char-codes-key-codes
   switch (key) {
      case 82:     // R key
         resetEnemy();
         break;
      case 27:     // Esc key
         resetEnemy();
         //exit(0);
         break;
   }
}


void mouse(int button, int state, int x, int y) {

}

void head(int x,int y)
{
    glBegin(GL_QUADS);
    glVertex3f(getX(x-characterBodyHalfSize),getY(y-characterBodyHalfSize), 0.5f);
    glVertex3f(getX(x+characterBodyHalfSize),getY( y-characterBodyHalfSize), 0.5f);
    glVertex3f(getX(x+characterBodyHalfSize), getY(y+characterBodyHalfSize), 0.5f);
    glVertex3f(getX(x-characterBodyHalfSize),getY( y+characterBodyHalfSize), 0.5f);
    glEnd();

}

void ears(int x,int y)
{
    //ears
    glPointSize(15);
    glBegin(GL_POINTS);
    glVertex3f(getX(x+characterBodyHalfSize),getY(y),0.0f);
    glVertex3f(getX(x-characterBodyHalfSize),getY(y),0.0f);
    glEnd();
}

void playerHair(int x,int y)
{
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    glVertex3f(getX(x-characterBodyHalfSize),getY(y+(characterBodyHalfSize/2)), 0.0f);
    glVertex3f(getX(x),getY(y+(characterBodyHalfSize/4)), 0.0f);
    glVertex3f(getX(x+(characterBodyHalfSize/2)),getY( y+characterBodyHalfSize-20), 0.0f);
    glVertex3f(getX(x+characterBodyHalfSize), getY(y+(characterBodyHalfSize/2)), 0.0f);

    glVertex3f(getX(x+characterBodyHalfSize), getY(y+characterBodyHalfSize), 0.0f);
    glVertex3f(getX(x-characterBodyHalfSize), getY(y+characterBodyHalfSize), 0.0f);
    glEnd();
}


void playerEye(int x,int y)
{
    glColor3f(0.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(getX(_moveEye), getY(y), 0.0f);

    glPointSize(7);
    glBegin(GL_POINTS);
    glVertex3f(getX(x-20),getY(0),0.0f);
    glVertex3f(getY(x+20),getY(0),0.0f);
    glEnd();
    glPopMatrix();
}


void playerMouth(int x,int y)
{

    glLineWidth(3);
    glBegin(GL_LINES);
     glColor3f(1, 0.2, 0.2);
    glVertex3f(getX(x-characterBodyHalfSize/3),getY(y-(characterBodyHalfSize/2)), 0.0f);
    glVertex3f(getX(x+characterBodyHalfSize/3),getY(y-(characterBodyHalfSize/2)), 0.0f);
    glEnd();
}


void player(int x,int y)
{
        //face shape total
        glColor3f(1.0, 0.6,0.2);
        head(x,y);

        //ears
        ears(x,y);
        //hair
        playerHair(x,y);

        //eye
        playerEye(x,y);

        //mouth
        playerMouth(x,y);

        //beared
        glPointSize(15);
        glColor3f(0.250, 0.250, 0.250);
        glBegin(GL_POINTS);
        glVertex3f(getX(x),getY(y-characterBodyHalfSize+10),0.0f);
        glEnd();

}

void enemy(int x,int y)
{
        //head
    glColor3f(0.878, 0.878,0.878);

    head(x,y);

    //eyes
    glPointSize(5);
    glColor3f(0.0, 0.0,0);
    glBegin(GL_POINTS);
    glVertex3f(getX(x-30),getY(y+30),0.0f);
    glVertex3f(getY(x+30),getY(y+30),0.0f);
    glEnd();


    float upX=getX(x-characterBodyHalfSize+10);
    float downX=getX(x+characterBodyHalfSize-10);
    float upY=getY(y+10);
    float downY=getY(y-characterBodyHalfSize+5-mouthShut);

    //mouth
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.2,0.2);

    glVertex3f(upX,downY, 0.0f);
    glVertex3f(downX,downY, 0.0f);

    //upper lip
    glVertex3f(downX, upY, 0.0f);
    glVertex3f(upX,upY, 0.0f);

    glEnd();

    //teeth
    int16_t teathX=0.033;
    int16_t teathY=0.05;

    glColor3f(1.0, 1.0,1.0);
    glPointSize(12);
    glBegin(GL_POINTS);

    glVertex3f(getX(x),upY-.02, 0.0f);

    glEnd();

}
void checkCollision(int &enemyX,int &enemyY)
{
    if(abs(previousMouseX-enemyX)<100 && abs(previousMouseY-enemyY)<100)
    {
        glColor3f(1.0,0.0,0.0);
        printText(-0.2,0.12,gameOver);
        gameOverFlag=true;
    }
}


void printScore()
{
    strs.str(std::string());
    if(!gameOverFlag)
        score=(int) ( std::clock() - start ) / (int) CLOCKS_PER_SEC;
    //increasing speed when score cross extra 6
    if((score+1)%increaseEnemySpeedPerSec==0 && increaseEnemySpeedPerSec!=1)
    {
            enemySpeed+=2;
            increaseEnemySpeedPerSec--;
            characterBodyHalfSize+=2;
    }

    strs <<score;
    string scoreText="Score : ";
    string scoreNum=strs.str();

    scoreText.append(scoreNum);
    char* scoreBoard = (char*) scoreText.c_str();
    glColor3f(0.0,0.0,0.0);
    printText(0.58,0.88,scoreBoard);
}


void drawCheracters()
{
    glPointSize(7);

	//player X Y co ordinates
	int playerX=mouseX;
	int playerY=mouseY;

    //enemy design
    glPushMatrix();
    glTranslatef(getX(enemy1X), getY(enemy1Y), 0.0f);
    enemy(0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(getX(enemy2X), getY(enemy2Y), 0.0f);
    enemy(0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(getX(enemy3X), getY(enemy3Y), 0.0f);
    enemy(0,0);
    glPopMatrix();

    if(first && gameOverFlag)
    {
        if(mouseX<-.17 && mouseY<.17)//&& mouseX<.1 && mouseY>-.1 && mouseY<.1
        {
            first=false;
            resetEnemy();
        }
    }

    //logic for keeping the character with the mouse pointer
    if(getX(playerX+characterBodyHalfSize)<1 && getX(playerX-characterBodyHalfSize)>-1
       && getY(playerY-characterBodyHalfSize)>-1 && getY(playerY+characterBodyHalfSize)<1
       && abs(previousMouseX-mouseX)<200 && abs(previousMouseY-mouseY)<200 && !gameOverFlag)
    {
        playerX=previousMouseX=mouseX;
        playerY=previousMouseY=mouseY;
    }
    else
    {
        playerX=previousMouseX;
        playerY=previousMouseY;
    }
    player(playerX,playerY);

    //check collision
    checkCollision(enemy1X,enemy1Y);
    checkCollision(enemy2X,enemy2Y);
    checkCollision(enemy3X,enemy3Y);


    //Score board
    if(!first)
        printScore();
}




void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); //Reset the drawing perspective
	glMatrixMode(GL_MODELVIEW);

    //drawing and giving logic for the characters
    drawCheracters();

	glutSwapBuffers();
}

void enemyMovement(bool &Left,bool &Up,int &enemyX,int &enemyY)
{
    // x co ordinate
    if(Left)
    {
        enemyX+=enemySpeed;
        if(enemyX>=250)
            Left=false;
    }
    else
    {
        enemyX-=enemySpeed;
        if(enemyX<=-250)
            Left=true;
    }

    //y co ordinate
    if(Up)
    {
        enemyY-=enemySpeed;
        if(enemyY<=-250)
            Up=false;
    }
    else
    {
        enemyY+=enemySpeed;
        if(enemyY>=250)
            Up=true;
    }
}

void update(int value) {

        //eye movement animation
    if(eyeLeft)
    {
        _moveEye+=1;;
        eyeMoveCount++;
        if (eyeMoveCount==15)
        eyeLeft=false;
    }
    else
    {
        _moveEye-=1;;
        eyeMoveCount--;
        if(eyeMoveCount==0)
        eyeLeft=true;
    }

    //enemy mouth animation
    if(enemyMouthOpen)
    {
        mouthShut-=2;
        if(mouthShut==-52)
        {
            enemyMouthOpen=false;
        }
    }
    else
    {
        mouthShut+=2;
        if(mouthShut==0)
        {
            enemyMouthOpen=true;
        }
    }

    if(!gameOverFlag)
    {
    //----------------------------------------------enemy movement----------------------------
    //-----------enemy1--------------
        enemyMovement(enemy1Left,enemy1Up,enemy1X,enemy1Y);

    //-----------enemy2--------------
        enemyMovement(enemy2Left,enemy2Up,enemy2X,enemy2Y);

    //-----------enemy3--------------
        enemyMovement(enemy3Left,enemy3Up,enemy3X,enemy3Y);
    }

    glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowSize, windowSize);
	glutInitWindowPosition(50, 50);

	//Create the window
	glutCreateWindow("Palabi Kothai");
    glEnable(GL_DEPTH_TEST);
	//random position for enemys
    resetEnemy();
    gameOverFlag=true;
	//Set handler functions
	glutDisplayFunc(drawScene);

    glClearColor(1.0, 1.0, 1.0, 0.0);

	glutKeyboardFunc(keyboard);   //Basic keyboard key handler
	glutMouseFunc(mouse);         //Mouse Handler
    glutPassiveMotionFunc(mouseMotion);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}
