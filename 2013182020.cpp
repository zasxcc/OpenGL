#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>

#include <math.h>  
#include <iostream>
#include <time.h>


#define MAX 1000

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);

void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);

void MakeStage();
void MakeTriangle();
void MakeRect();
void MakeSC();
enum STATE {
	_RECT = 99, //정사각형
	_RECT2, //마름모
	_TRI,
	_DIV,
	_DIV2,
	_DIV3,
	_DIV4,
	_DIA,
	_CATCH,
	_CATCH2,
	_CATCH3,
	_CATCH4,
	_IDLE,
	_STAR,
	_NULL,
};

class POINT3D
{
public:
	float posX;
	float posY;
	float posZ;
	float size;
	float size2;
	float randomShape;
	int state;
	int state2;
	int state3;
	float R, G, B, A;
	int randomFlag;
	float angle;
	float x;
	float y;
	int posFlag;
	int posFlag2;
	int sizeFlag;
	float x2;
	float y2;
	float divPosX;
	float divPosY;
	float divPosZ;
	float divPosX2;
	float divPosY2;
	float divPosZ2;
	float tempX;
	float tempX2;
	float tempY;
	float tempY2;
	float stageTriX;
	float stageTriY;
	float stageTriX2;
	float stageTriY2;
	float vel;
	float vel2;
	int Rflag;
	int Lflag;
	POINT3D()
	{
		posX = 0;
		posY = 0;
		posZ = 0;
		divPosX = 0;
		divPosY = 0;
		divPosZ = 0;
		divPosX2 = 0;
		divPosY2 = 0;
		divPosZ2 = 0;
		size = 0;
		state2 = 0;
		state = STATE::_IDLE;
		state3 = 0;
		randomShape = 0;
		R = 1.0f;
		G = 1.0f;
		B = 1.0f;
		A = 1.0f;
		vel = 12;
		vel2 = 12;
		randomFlag = 0;
		angle = 0;
		x = 0;
		y = 0;
		posFlag = 0;
		posFlag2 = 0;
		sizeFlag = 2;
		size2 = size;
		x2 = 0;
		y2 = 0;
		tempX = 0;
		tempX2 = 0;
		tempY = 0;
		tempY2 = 0;
		stageTriX = 0;
		stageTriY = 0;
		stageTriX2 = 0;
		stageTriY2 = 0;
		Rflag = 0;
		Lflag = 0;
	}

	~POINT3D()
	{
	}
};

POINT3D tri[MAX];
POINT3D rect[MAX];
POINT3D sc;

int count = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;

void main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("sad");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(10, TimerFunction, 1);
	glutReshapeFunc(reshape);
	//Init
	for (int i = 0; i < MAX; ++i)
	{
		tri[i].posX = -150000+(i * 150);        //위에 삼각형
		tri[i].posY = 550;
		tri[i].size = (rand() % 20) + 20;
		tri[i].size2 = tri[i].size;
		tri[i].randomShape = (rand() % 30) + 10;
		tri[i].x = rand() % 1000;
		rect[i].posX = 500;
		rect[i].posY = (-199700*2) +(i*400);
		rect[i].size = 50;

		rect[i].state = rand() % 2;  
		if (rect[i].state == 0)
			rect[i].state = STATE::_RECT2;
		if (rect[i].state == 1)
			rect[i].state = STATE::_RECT;
	}
	glutMainLoop();
}



GLvoid drawScene()
{
	glClearColor(0.f, 0.0f, .0f, .0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(5.0);
	glLineWidth(2.0);
	if (sc.posFlag == 1)
		MakeSC();
	else
	{

	}
	MakeStage();
	
	MakeTriangle();
	
	MakeRect();
	
	
	glutSwapBuffers();

}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1000, 0, 600, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool left_button;

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	

	case 'q':

		break;
	}
	reshape(1000, 600);
	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{

	}
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		for (int i = 0; i < MAX; ++i)
		{
			if (x < tri[i].posX + 25 &&
				x > tri[i].posX - 25 &&
				600 - y< tri[i].posY + 25 &&
				600 - y> tri[i].posY - 25)
			{
				for (int j = 0; j < MAX; ++j)
				{
					if (tri[i].posX < rect[j].divPosX + 45 && tri[i].posX > rect[j].divPosX - 45 && 
						tri[i].posY < rect[j].divPosY + 45 && tri[i].posY > rect[j].divPosY - 45) {
						tri[i].state = STATE::_STAR;
						rect[j].Lflag = 1;
						count--;
					}

					if (tri[i].posX < rect[j].divPosX2 + 45 && tri[i].posX > rect[j].divPosX2 - 45 &&
						tri[i].posY < rect[j].divPosY2 + 45 && tri[i].posY > rect[j].divPosY2 - 45) {
						tri[i].state = STATE::_STAR;
						rect[j].Rflag = 1;
						
						count3--;
					}
				}
			}

			if (rect[i].state2 == STATE::_CATCH || rect[i].state2 == STATE::_CATCH2)
			{
				rect[i].state2 = STATE::_NULL;
			}

		}
		//사각형 컷팅
		for (int i = 0; i < MAX; ++i)
		{
			if (sc.y < rect[i].posY + rect[i].size + 30 && //사각형 자르기 ( 좌상향 우하향 )
				sc.y > rect[i].posY + rect[i].size - 30 &&
				sc.x < rect[i].posX - rect[i].size + 30 &&
				sc.x > rect[i].posX - rect[i].size - 30 &&
				sc.y2 < rect[i].posY - rect[i].size + 30 &&
				sc.y2 > rect[i].posY - rect[i].size - 30 &&
				sc.x2 < rect[i].posX + rect[i].size + 30 &&
				sc.x2 > rect[i].posX + rect[i].size - 30 &&
				rect[i].state == STATE::_RECT)
			{
				rect[i].divPosX = rect[i].posX;
				rect[i].divPosY = rect[i].posY;
				rect[i].divPosX2 = rect[i].posX;
				rect[i].divPosY2 = rect[i].posY;
				rect[i].state = STATE::_DIV;
				rect[i].stageTriX = 40 * count;
				rect[i].stageTriX2 = (1000)-(40 * count3);
				rect[i].stageTriY = 40 * count2;
				rect[i].stageTriY2 = 40 * count4;
				count++;
				if (count == 10) {
					count = 0;
					count2++;
				}
				count3++;
				if (count3 == 10) {
					count3 = 0;
					count4++;
				}
				
			}

			else if (sc.y2 < rect[i].posY + rect[i].size + 30 && //사각형 자르기 ( 우하향 좌상향 )
				sc.y2 > rect[i].posY + rect[i].size - 30 &&
				sc.x2 < rect[i].posX - rect[i].size + 30 &&
				sc.x2 > rect[i].posX - rect[i].size - 30 &&
				sc.y < rect[i].posY - rect[i].size + 30 &&
				sc.y > rect[i].posY - rect[i].size - 30 &&
				sc.x < rect[i].posX + rect[i].size + 30 &&
				sc.x > rect[i].posX + rect[i].size - 30&&
				rect[i].state == STATE::_RECT)
			{
				rect[i].divPosX = rect[i].posX;
				rect[i].divPosY = rect[i].posY;
				rect[i].divPosX2 = rect[i].posX;
				rect[i].divPosY2 = rect[i].posY;
				rect[i].state = STATE::_DIV;
				rect[i].stageTriX = 40 * count;
				rect[i].stageTriX2 = (1000) - (40 * count3);
				rect[i].stageTriY = 40 * count2;
				rect[i].stageTriY2 = 40 * count4;
				count++;
				if (count == 10) {
					count = 0;
					count2++;
				}
				count3++;
				if (count3 == 10) {
					count3 = 0;
					count4++;
				}

			}

			else if (sc.y < rect[i].posY + rect[i].size + 30 && //사각형 자르기 ( 우상향 좌하향 )
				sc.y > rect[i].posY + rect[i].size - 30 &&
				sc.x < rect[i].posX + rect[i].size + 30 &&
				sc.x > rect[i].posX + rect[i].size - 30 &&
				sc.y2 < rect[i].posY - rect[i].size + 30 &&
				sc.y2 > rect[i].posY - rect[i].size - 30 &&
				sc.x2 < rect[i].posX - rect[i].size + 30 &&
				sc.x2 > rect[i].posX - rect[i].size - 30&&
				rect[i].state == STATE::_RECT)
			{
				rect[i].divPosX = rect[i].posX;
				rect[i].divPosY = rect[i].posY;
				rect[i].divPosX2 = rect[i].posX;
				rect[i].divPosY2 = rect[i].posY;
				rect[i].state = STATE::_DIV2;
				rect[i].stageTriX = 40 * count;
				rect[i].stageTriX2 = (1000) - (40 * count3);
				rect[i].stageTriY = 40 * count2;
				rect[i].stageTriY2 = 40 * count4;
				count++;
				if (count == 10) {
					count = 0;
					count2++;
				}
				count3++;
				if (count3 == 10) {
					count3 = 0;
					count4++;
				}
			}

			else if (sc.y2 < rect[i].posY + rect[i].size + 30 && //사각형 자르기 ( 좌하향 우상향 )
				sc.y2 > rect[i].posY + rect[i].size - 30 &&
				sc.x2 < rect[i].posX + rect[i].size + 30 &&
				sc.x2 > rect[i].posX + rect[i].size - 30 &&
				sc.y < rect[i].posY - rect[i].size + 30 &&
				sc.y > rect[i].posY - rect[i].size - 30 &&
				sc.x < rect[i].posX - rect[i].size + 30 &&
				sc.x > rect[i].posX - rect[i].size - 30 &&
				rect[i].state == STATE::_RECT)
			{
				rect[i].divPosX = rect[i].posX;
				rect[i].divPosY = rect[i].posY;
				rect[i].divPosX2 = rect[i].posX;
				rect[i].divPosY2 = rect[i].posY;
				rect[i].state = STATE::_DIV2;
				rect[i].stageTriX = 40 * count;
				rect[i].stageTriX2 = (1000) - (40 * count3);
				rect[i].stageTriY = 40 * count2;
				rect[i].stageTriY2 = 40 * count4;
				count++;
				if (count == 10) {
					count = 0;
					count2++;
				}
				count3++;
				if (count3 == 10) {
					count3 = 0;
					count4++;
				}

			}
			else if (sc.y > rect[i].posY + rect[i].size - 100 && //마름모 자르기 (위에서 아래)
				sc.y < rect[i].posY + rect[i].size + 100 &&
				sc.x > rect[i].posX - 15 &&
				sc.x < rect[i].posX + 15 &&
				sc.y2 > rect[i].posY - rect[i].size - 100 &&
				sc.y2 < rect[i].posY - rect[i].size + 100 &&
				sc.x2 > rect[i].posX - 15 &&
				sc.x2 < rect[i].posX + 15 &&
				rect[i].state == STATE::_RECT2)
			{
				rect[i].divPosX = rect[i].posX;
				rect[i].divPosY = rect[i].posY;
				rect[i].divPosX2 = rect[i].posX;
				rect[i].divPosY2 = rect[i].posY;
				rect[i].state = STATE::_DIV3;
				rect[i].stageTriX = 40 * count;
				rect[i].stageTriX2 = (1000) - (40 * count3);
				rect[i].stageTriY = 40 * count2;
				rect[i].stageTriY2 = 40 * count4;
				count++;
				if (count == 10) {
					count = 0;
					count2++;
				}
				count3++;
				if (count3 == 10) {
					count3 = 0;
					count4++;
				}
			}

			else if (sc.y2 > rect[i].posY + rect[i].size - 100 && //마름모 자르기 (아래에서 위)
				sc.y2 < rect[i].posY + rect[i].size + 100 &&
				sc.x2 > rect[i].posX - 15 &&
				sc.x2 < rect[i].posX + 15 &&
				sc.y > rect[i].posY - rect[i].size - 100 &&
				sc.y < rect[i].posY - rect[i].size + 100 &&
				sc.x > rect[i].posX - 15 &&
				sc.x < rect[i].posX + 15 &&
				rect[i].state == STATE::_RECT2)
			{
				rect[i].divPosX = rect[i].posX;
				rect[i].divPosY = rect[i].posY;
				rect[i].divPosX2 = rect[i].posX;
				rect[i].divPosY2 = rect[i].posY;
				rect[i].state = STATE::_DIV3;
				rect[i].stageTriX = 40 * count;
				rect[i].stageTriX2 = (1000) - (40 * count3);
				rect[i].stageTriY = 40 * count2;
				rect[i].stageTriY2 = 40 * count4;
				count++;
				if (count == 10) {
					count = 0;
					count2++;
				}
				count3++;
				if (count3 == 10) {
					count3 = 0;
					count4++;
				}
			}
			else if (sc, y > rect[i].posY - 15 &&      //마름모 자르기 가로 (좌에서 우)
				sc.y < rect[i].posY + 10 &&
				sc.x > rect[i].posX - rect[i].size - 100 &&
				sc.x < rect[i].posX - rect[i].size + 100 &&
				sc.y2 > rect[i].posY - 15 &&
				sc.y2 < rect[i].posY + 15 &&
				sc.x2 > rect[i].posX + rect[i].size - 100 &&
				sc.x2 < rect[i].posX + rect[i].size + 100 &&
				rect[i].state == STATE::_RECT2)
			{
				rect[i].divPosX = rect[i].posX;
				rect[i].divPosY = rect[i].posY;
				rect[i].divPosX2 = rect[i].posX;
				rect[i].divPosY2 = rect[i].posY;
				rect[i].state = STATE::_DIV4;
				rect[i].stageTriX = 40 * count;
				rect[i].stageTriX2 = (1000) - (40 * count3);
				rect[i].stageTriY = 40 * count2;
				rect[i].stageTriY2 = 40 * count4;
				count++;
				if (count == 10) {
					count = 0;
					count2++;
				}
				count3++;
				if (count3 == 10) {
					count3 = 0;
					count4++;
				}
			}
			else if (sc.y2 > rect[i].posY - 15 &&     //마름모 자르기 가로 (우에서 좌)
				sc.y2 < rect[i].posY + 10 &&
				sc.x2 > rect[i].posX - rect[i].size - 100 &&
				sc.x2 < rect[i].posX - rect[i].size + 100 &&
				sc.y > rect[i].posY - 15 &&
				sc.y < rect[i].posY + 15 &&
				sc.x > rect[i].posX + rect[i].size - 100 &&
				sc.x < rect[i].posX + rect[i].size + 100 &&
				rect[i].state == STATE::_RECT2)
			{
				rect[i].divPosX = rect[i].posX;
				rect[i].divPosY = rect[i].posY;
				rect[i].divPosX2 = rect[i].posX;
				rect[i].divPosY2 = rect[i].posY;
				rect[i].state = STATE::_DIV4;
				rect[i].stageTriX = 40 * count;
				rect[i].stageTriX2 = (1000) - (40 * count3);
				rect[i].stageTriY = 40 * count2;
				rect[i].stageTriY2 = 40 * count4;
				count++;
				if (count == 10) {
					count = 0;
					count2++;
				}
				count3++;
				if (count3 == 10) {
					count3 = 0;
					count4++;
				}
			}

			
		}
	
		sc.posFlag = 0;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		sc.x = x;
		sc.y = 600- y;

		for (int i = 0; i < MAX; ++i) {

			if (rect[i].state == STATE::_DIV || rect[i].state == STATE::_DIV2 || rect[i].state == STATE::_DIV3 || rect[i].state == STATE::_DIV4)
			{
				if (rect[i].divPosX + rect[i].size > sc.x && rect[i].divPosX - rect[i].size < sc.x&&
					rect[i].divPosY - rect[i].size < sc.y && rect[i].divPosY + rect[i].size > sc.y)
				{
					rect[i].state2 = STATE::_CATCH;
					rect[i].vel = 5.4;
				}

				if (rect[i].divPosX2 + rect[i].size > sc.x && rect[i].divPosX2 - rect[i].size < sc.x&&
					rect[i].divPosY2 - rect[i].size < sc.y && rect[i].divPosY2 + rect[i].size > sc.y)
				{
					rect[i].state2 = STATE::_CATCH2;
					rect[i].vel2 = 5.4;
				}
			}
		}
	}
	left_button = true;
}

void Motion(int x, int y)
{
	if (left_button == true)
	{
		sc.posFlag = 1;
		sc.x2 = x ;
		sc.y2 = (600 - y);
	}
}

void TimerFunction(int value)
{
	
	for (int i = 0; i < MAX; ++i)
	{
		if (tri[i].state == STATE::_IDLE)
			tri[i].posX += 4;


		tri[i].angle += 3 + rand() % 10;

		if (rect[i].state == STATE::_RECT || rect[i].state == STATE::_RECT2)
			rect[i].posY += 1.6;

		if (rect[i].posY > 500 && rect[i].state == STATE::_RECT) {
			rect[i].R -= 0.015;
			rect[i].G -= 0.015;
			rect[i].B -= 0.015;
		}

		if (rect[i].posY > 500 && rect[i].state == STATE::_RECT2) {
			rect[i].R -= 0.015;
			rect[i].G -= 0.015;
			rect[i].B -= 0.015;
		}

		

		if (rect[i].state == STATE::_DIV || rect[i].state == STATE::_DIV2 || rect[i].state ==STATE::_DIV3 || rect[i].state == STATE::_DIV4) 
		{
			rect[i].tempX = rect[i].stageTriX+20;
			rect[i].tempX2 = rect[i].stageTriX2 - 20;
			rect[i].tempY = rect[i].stageTriY+20;
			rect[i].tempY2 = rect[i].stageTriY2 + 20;
			if (rect[i].divPosX > rect[i].tempX)
				rect[i].divPosX -= 2.5;
			else if (rect[i].divPosX < rect[i].tempX)
				rect[i].divPosX += 2.5;
			if (rect[i].divPosX  < rect[i].tempX + 3 && rect[i].divPosX > rect[i].tempX - 3)
				rect[i].divPosX = rect[i].tempX;

			if (rect[i].divPosX2 < rect[i].tempX2)
				rect[i].divPosX2 += 2.5;
			else if (rect[i].divPosX2 > rect[i].tempX2)
				rect[i].divPosX2 -= 2.5;
			if (rect[i].divPosX2  < rect[i].tempX2 + 3 && rect[i].divPosX2 > rect[i].tempX2 - 3)
				rect[i].divPosX2 = rect[i].tempX2;


			if (rect[i].state == STATE::_DIV || rect[i].state == STATE::_DIV2 || rect[i].state == STATE::_DIV3 || rect[i].state == STATE::_DIV4) //중력적용 떨어지기
			{
				if (rect[i].divPosY + rect[i].vel > rect[i].tempY)
				{
					rect[i].vel -= 0.15;
				}
				else if (rect[i].divPosY + rect[i].vel < rect[i].tempY)
				{
					rect[i].vel = 0;
					rect[i].divPosY = rect[i].tempY;
				}
				rect[i].divPosY += rect[i].vel;

				if (rect[i].divPosY2 + rect[i].vel2 > rect[i].tempY2)
				{
					rect[i].vel2 -= 0.15;
				}
				else if (rect[i].divPosY2 + rect[i].vel2 < rect[i].tempY2)
				{
					rect[i].vel2 = 0;
					rect[i].divPosY2 = rect[i].tempY2;
				}
				rect[i].divPosY2 += rect[i].vel2;
			}


			if (rect[i].state != STATE::_DIV3 &&rect[i].state != STATE::_DIV4)
			{
				if (rect[i].angle < 1080)
					rect[i].angle += 4;
			}
			

			if (rect[i].state != STATE::_DIV && rect[i].state != STATE::_DIV2)
			{
				if (rect[i].angle < 1035)
					rect[i].angle += 3;

			}
			


			if (rect[i].size > 20 && rect[i].state != STATE::_DIV3 &&rect[i].state != STATE::_DIV4)
				rect[i].size -= 0.1;

			else if (rect[i].size > 30)
				rect[i].size -= 0.1;
		}

	}

	for (int i = 0; i < MAX; ++i)
	{
		if (tri[i].state == STATE::_STAR)
		{
			if (tri[i].y < tri[i].posY)
				tri[i].posY -= 5;

			if (tri[i].x < tri[i].posX && tri[i].posFlag == 0)
			{
				tri[i].posFlag = 1;
			}
			else if (tri[i].x > tri[i].posX && tri[i].posFlag == 0)
			{
				tri[i].posFlag = 2;
			}
			

			if (tri[i].posFlag == 1 && tri[i].x < tri[i].posX)
			{
				tri[i].posX -= 5;
			}
			else if (tri[i].posFlag == 2 && tri[i].x > tri[i].posX)
			{
				tri[i].posX += 5;
			}
			
			tri[i].R = rand() % 10;
			tri[i].G = rand() % 10;
			tri[i].B = rand() % 10;
			tri[i].R = tri[i].R /10;
			tri[i].G = tri[i].G / 10;
			tri[i].B = tri[i].B/ 10;
			
			if (tri[i].size < tri[i].size2 - 10)
				tri[i].sizeFlag = 1;
			else if (tri[i].size > tri[i].size2 + 20)
				tri[i].sizeFlag = 2;

			if (tri[i].sizeFlag == 1)
			{
				tri[i].size += 2;
			}
			else if (tri[i].sizeFlag == 2)
			{
				tri[i].size -= 2;
			}
		}

	}

	glutPostRedisplay(); //화면 재출력
	glutTimerFunc(20, TimerFunction, 1);
}


void MakeStage()
{
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 500, 0);
	glVertex3f(1000, 500, 0);
	glEnd();


	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			glPushMatrix();
			glTranslated(j * 40, i * 40, 0);
			glutWireCube(80);
			glPopMatrix();
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			glPushMatrix();
			glTranslated(640 + j * 40,i * 40, 0);
			glutWireCube(80);
			glPopMatrix();
		}
	}
}

void MakeTriangle()
{
	for (int i = 0; i < MAX; ++i)
	{
		if (tri[i].state == STATE::_IDLE)
		{
			glColor3f(1,1, 1);
			glPushMatrix();
			glTranslated(tri[i].posX, tri[i].posY, tri[i].posZ);
			glRotated(tri[i].angle, 0, 1, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(0 - tri[i].size + tri[i].randomShape, 0 + tri[i].size, 0);
			glVertex3f(0 - tri[i].size, 0 - tri[i].size + tri[i].randomShape, 0);
			glVertex3f(0 + tri[i].size, 0- tri[i].size, 0);
			glEnd();
			glPopMatrix();
		}
		else if (tri[i].state == STATE::_STAR)
		{
			if (tri[i].randomFlag == 0) 
			{
				tri[i].x = rand() % 1000;
				tri[i].y = 500 - rand() % 300;
				tri[i].randomFlag = 1;
			}
			glColor3f(tri[i].R, tri[i].G, tri[i].B);
			glPushMatrix();
			glTranslated(tri[i].posX, tri[i].posY, tri[i].posZ);
			glRotated(tri[i].angle, 0, 1, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(0, 0+tri[i].size, 0);
			glVertex3f(0 + tri[i].size / 3, 0 + tri[i].size / 2, 0);
			glVertex3f(0 + tri[i].size, 0 + tri[i].size / 2, 0);
			glVertex3f(0 + tri[i].size/2, 0, 0);
			glVertex3f(0 + tri[i].size, 0 - tri[i].size / 2, 0);
			glVertex3f(0 + tri[i].size / 3, 0 - tri[i].size / 2, 0);

			glVertex3f(0, 0 - tri[i].size, 0);
			glVertex3f(0 - tri[i].size / 3, 0 - tri[i].size / 2, 0);
			glVertex3f(0 - tri[i].size, 0 - tri[i].size / 2, 0);
			glVertex3f(0 - tri[i].size / 2, 0, 0);
			glVertex3f(0 - tri[i].size, 0 + tri[i].size / 2, 0);
			glVertex3f(0 - tri[i].size / 3, 0 + tri[i].size / 2, 0);

			
			glEnd();
			glutSolidSphere(tri[i].size*2/5, 8, 8);

			glPopMatrix();
		}
	}
}

void MakeRect()
{
	for (int i = 0; i < MAX; ++i) {

		if (rect[i].state == STATE::_RECT) //사각형
		{
			glColor3f(rect[i].R, rect[i].G, rect[i].B);
			glPushMatrix();
			glTranslatef(rect[i].posX, rect[i].posY, rect[i].posZ);
			glBegin(GL_LINE_LOOP);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size , rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size , rect[i].y - rect[i].size, 0);
			glVertex3f(rect[i].x - rect[i].size , rect[i].y - rect[i].size, 0);
			glEnd();
			glPopMatrix();
		}

		else if (rect[i].state == STATE::_RECT2) //마름모
		{
			glColor3f(rect[i].R, rect[i].G, rect[i].B);
			glPushMatrix();
			glTranslatef(rect[i].posX, rect[i].posY, rect[i].posZ);
			glBegin(GL_LINE_LOOP);
			glVertex3f(rect[i].x , rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size , rect[i].y, 0);
			glVertex3f(rect[i].x, rect[i].y - rect[i].size, 0);
			glVertex3f(rect[i].x - rect[i].size , rect[i].y, 0);
			glEnd();
			glPopMatrix();
		}

		else if (rect[i].state == STATE::_DIV) //사각형 좌에서 우
		{
			glColor3f(0, 1, 0.3);
			if (rect[i].state2 != STATE::_CATCH && rect[i].Lflag == 0) {
				
				glPushMatrix();
				glTranslated(rect[i].divPosX, rect[i].divPosY, rect[i].divPosZ);
				glRotatef(rect[i].angle, 0, 0, 1);
				glBegin(GL_POLYGON);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y - rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y - rect[i].size, 0);
				glEnd();
				glPopMatrix();
			}
			if (rect[i].state2 != STATE::_CATCH2 && rect[i].Rflag == 0) {
				glPushMatrix();
				glTranslated(rect[i].divPosX2, rect[i].divPosY2, rect[i].divPosZ2);
				glRotatef(rect[i].angle, 0, 0, 1);
				glBegin(GL_POLYGON);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y - rect[i].size, 0);
				glEnd();
				glPopMatrix();
			}
		}

		else if (rect[i].state == STATE::_DIV2) //사각형 우에서 좌
		{
			glColor3f(0, 1, 0.3);
			if (rect[i].state2 != STATE::_CATCH && rect[i].Lflag ==0) {
				
				glPushMatrix();
				glTranslated(rect[i].divPosX, rect[i].divPosY, rect[i].divPosZ);
				glRotatef(rect[i].angle, 0, 0, 1);
				glBegin(GL_POLYGON);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y - rect[i].size, 0);
				glEnd();
				glPopMatrix();
			}
			if (rect[i].state2 != STATE::_CATCH2 && rect[i].Rflag ==0) {
				glPushMatrix();
				glTranslated(rect[i].divPosX2, rect[i].divPosY2, rect[i].divPosZ2);
				glRotatef(rect[i].angle, 0, 0, 1);
				glBegin(GL_POLYGON);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y - rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y - rect[i].size, 0);
				glEnd();
				glPopMatrix();
			}
		}

		else if (rect[i].state == STATE::_DIV3) //마름모 세로
		{
			glColor3f(0, 1, 0.3);
			if (rect[i].state2 != STATE::_CATCH && rect[i].Lflag == 0) {
				
				glPushMatrix();
				glTranslated(rect[i].divPosX, rect[i].divPosY, rect[i].divPosZ);
				glRotatef(rect[i].angle, 0, 0, 1);
				glBegin(GL_POLYGON);
				glVertex3f(rect[i].x, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y, 0);
				glVertex3f(rect[i].x, rect[i].y - rect[i].size, 0);
				glEnd();
				glPopMatrix();
			}
			if (rect[i].state2 != STATE::_CATCH2 && rect[i].Rflag == 0) {
				glPushMatrix();
				glTranslated(rect[i].divPosX2, rect[i].divPosY2, rect[i].divPosZ2);
				glRotatef(rect[i].angle, 0, 0, 1);
				glBegin(GL_POLYGON);
				glVertex3f(rect[i].x, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y, 0);
				glVertex3f(rect[i].x, rect[i].y - rect[i].size, 0);
				glEnd();
				glPopMatrix();
			}
		}

		else if (rect[i].state == STATE::_DIV4) //마름모 가로
		{
			glColor3f(0, 1, 0.3);
			if (rect[i].state2 != STATE::_CATCH && rect[i].Lflag == 0) {
				
				glPushMatrix();
				glTranslated(rect[i].divPosX, rect[i].divPosY, rect[i].divPosZ);
				glRotatef(rect[i].angle, 0, 0, 1);
				glBegin(GL_POLYGON);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y, 0);
				glVertex3f(rect[i].x, rect[i].y + rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y, 0);
				glEnd();
				glPopMatrix();
			}
			if (rect[i].state2 != STATE::_CATCH2 && rect[i].Rflag == 0) {
				glPushMatrix();
				glTranslated(rect[i].divPosX2, rect[i].divPosY2, rect[i].divPosZ2);
				glRotatef(rect[i].angle, 0, 0, 1);
				glBegin(GL_POLYGON);
				glVertex3f(rect[i].x - rect[i].size, rect[i].y, 0);
				glVertex3f(rect[i].x, rect[i].y - rect[i].size, 0);
				glVertex3f(rect[i].x + rect[i].size, rect[i].y, 0);
				glEnd();
				glPopMatrix();
			}
		}

		if (rect[i].state2 == STATE::_CATCH && rect[i].state == STATE::_DIV)  //잘린거 잡앗을때
		{
			if (sc.posFlag == 1) {
				rect[i].divPosX = sc.x2;
				rect[i].divPosY = sc.y2;
			}
			else {
				rect[i].divPosX = sc.x;
				rect[i].divPosY = sc.y;
			}
			glPushMatrix();
			glTranslated(rect[i].divPosX, rect[i].divPosY, rect[i].divPosZ);
			glRotatef(rect[i].angle, 0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y - rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size, rect[i].y - rect[i].size, 0);
			glEnd();
			glPopMatrix();
		}
		if (rect[i].state2 == STATE::_CATCH2 && rect[i].state == STATE::_DIV)
		{
			if (sc.posFlag == 1) {
				rect[i].divPosX2 = sc.x2;
				rect[i].divPosY2 = sc.y2;
			}
			else {
				rect[i].divPosX2 = sc.x;
				rect[i].divPosY2 = sc.y;
			}
			glPushMatrix();
			glTranslated(rect[i].divPosX2, rect[i].divPosY2, rect[i].divPosZ);
			glRotatef(rect[i].angle, 0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y - rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size, rect[i].y - rect[i].size, 0);
			glEnd();
			glPopMatrix();
		}

		if (rect[i].state2 == STATE::_CATCH && rect[i].state == STATE::_DIV2)
		{
			if (sc.posFlag == 1) {
				rect[i].divPosX = sc.x2;
				rect[i].divPosY = sc.y2;
			}
			else {
				rect[i].divPosX = sc.x;
				rect[i].divPosY = sc.y;
			}
			glPushMatrix();
			glTranslated(rect[i].divPosX, rect[i].divPosY, rect[i].divPosZ);
			glRotatef(rect[i].angle, 0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y - rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size, rect[i].y - rect[i].size, 0);
			glEnd();
			glPopMatrix();
		}
		if (rect[i].state2 == STATE::_CATCH2 && rect[i].state == STATE::_DIV2)
		{
			if (sc.posFlag == 1) {
				rect[i].divPosX2 = sc.x2;
				rect[i].divPosY2 = sc.y2;
			}
			else {
				rect[i].divPosX2 = sc.x;
				rect[i].divPosY2 = sc.y;
			}
			glPushMatrix();
			glTranslated(rect[i].divPosX2, rect[i].divPosY2, rect[i].divPosZ);
			glRotatef(rect[i].angle, 0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y - rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size, rect[i].y - rect[i].size, 0);
			glEnd();
			glPopMatrix();
		}

		if (rect[i].state2 == STATE::_CATCH && rect[i].state == STATE::_DIV3)
		{
			if (sc.posFlag == 1) {
				rect[i].divPosX = sc.x2;
				rect[i].divPosY = sc.y2;
			}
			else {
				rect[i].divPosX = sc.x;
				rect[i].divPosY = sc.y;
			}
			glPushMatrix();
			glTranslated(rect[i].divPosX, rect[i].divPosY, rect[i].divPosZ);
			glRotatef(rect[i].angle, 0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex3f(rect[i].x, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y, 0);
			glVertex3f(rect[i].x, rect[i].y - rect[i].size, 0);
			glEnd();
			glPopMatrix();
		}
		if (rect[i].state2 == STATE::_CATCH2 && rect[i].state == STATE::_DIV3)
		{
			if (sc.posFlag == 1) {
				rect[i].divPosX2 = sc.x2;
				rect[i].divPosY2 = sc.y2;
			}
			else {
				rect[i].divPosX2 = sc.x;
				rect[i].divPosY2 = sc.y;
			}
			glPushMatrix();
			glTranslated(rect[i].divPosX2, rect[i].divPosY2, rect[i].divPosZ);
			glRotatef(rect[i].angle, 0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y - rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size, rect[i].y - rect[i].size, 0);
			glEnd();
			glPopMatrix();
		}

		if (rect[i].state2 == STATE::_CATCH && rect[i].state == STATE::_DIV4)
		{
			if (sc.posFlag == 1) {
				rect[i].divPosX = sc.x2;
				rect[i].divPosY = sc.y2;
			}
			else {
				rect[i].divPosX = sc.x;
				rect[i].divPosY = sc.y;
			}
			glPushMatrix();
			glTranslated(rect[i].divPosX, rect[i].divPosY, rect[i].divPosZ);
			glRotatef(rect[i].angle, 0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y, 0);
			glVertex3f(rect[i].x, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size, rect[i].y, 0);
			glEnd();
			glPopMatrix();
		}
		if (rect[i].state2 == STATE::_CATCH2 && rect[i].state == STATE::_DIV4)
		{
			if (sc.posFlag == 1) {
				rect[i].divPosX2 = sc.x2;
				rect[i].divPosY2 = sc.y2;
			}
			else {
				rect[i].divPosX2 = sc.x;
				rect[i].divPosY2 = sc.y;
			}
			glPushMatrix();
			glTranslated(rect[i].divPosX2, rect[i].divPosY2, rect[i].divPosZ);
			glRotatef(rect[i].angle, 0, 0, 1);
			glBegin(GL_POLYGON);
			glVertex3f(rect[i].x - rect[i].size, rect[i].y, 0);
			glVertex3f(rect[i].x, rect[i].y + rect[i].size, 0);
			glVertex3f(rect[i].x + rect[i].size, rect[i].y, 0);
			glEnd();
			glPopMatrix();
		}
	}
}

void MakeSC()
{
	glColor3f(1, 1, 1);
	//glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(sc.x, sc.y, 0);
	glVertex3f(sc.x2, sc.y2, 0);
	glEnd();
	//glPopMatrix();
}