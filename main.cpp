#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <gl/glut.h>
#include "./obstacle.cpp"

using namespace std;
//TODO: 
//create a class for obstacles [x]
//create obstacle generation [x]
//*** obstacles animatoin []
//	obstacle front goes back []
//	obstacle move forward []
//	obstacles rotate by the keyboard[]
//	front obstacle should be selected and controlled []
//draw a ball where the player should be (will be fixed) [x]
//collision detection []
//texture []
float Obstacle::innerRadius = 1;
float Obstacle::outerRadius = 1.5;
float Obstacle::thickness = 0.5;
float Obstacle::res = 0.01;
int Obstacle::gap = 50;
ObstacleScene scene(6, 0, 0, -3, 2);
void myInit(){
	GLfloat width = 700;
	GLfloat height = 700;
	glClearColor( 1.0, 0.75, 0.8, 1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
	glEnable(GL_DEPTH_TEST);
	GLfloat light_pos[] = {3, 1, 2, 0};
	GLfloat ambient[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat	diffuse[] = {0.7, 0.7, 0.7, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	GLfloat amb[]={0.0215f,0.1745f,0.0215f,1.0f};
	GLfloat diff[]={0.07568f,0.61424f,0.07568f,1.0f};
	GLfloat spec[]={0.633f,0.727811f,0.633f,1.0f};
	GLfloat shine=76.8f;
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
}
void reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float) w / (float) h, 1.0f, 100.0f);

}
void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLineWidth(1);
	gluLookAt(0, 5, 5,
		0.f, 0.f, 0.f,
		0.f, 1.f, 0.f);
	//purple
	glColor3f(156.f / 256, 0, 255.f/256);
	scene.drawScene();
	glTranslatef(0, -4, 0);
	//player
	glColor3f(0, 1, 0);
	glutSolidSphere(0.6, 50, 50);
	glutSwapBuffers();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(GetSystemMetrics(SM_CXSCREEN) / 2.0f - 700 / 2, GetSystemMetrics(SM_CYSCREEN) / 2.0f - 700 / 2);
	glutCreateWindow("Abdo Nawar");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	myInit();
	glutMainLoop();

	return 0;
}
