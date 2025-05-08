#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <gl/glut.h>

using namespace std;
//TODO: 
//create a class for obstacles []
//create obstacle generation []
//draw a ball where the player should be (will be fixed) [x]
//collision detection []
//texture []
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
void obstacle(float innerRadius, float outerRadius, float thickness, float res = 0.01, int gap = 50){
	//.		.		.		.
	//|		|		|		|
	//.		.		.		.		.
	glBegin(GL_QUADS);
	//front
	for(float degree = 0; degree < 2 * M_PI - gap * res; degree += res){
		glVertex3f(innerRadius * cos(degree), innerRadius* sin(degree), 0);
		glVertex3f(outerRadius * cos(degree), outerRadius * sin(degree), 0);
		glVertex3f(outerRadius * cos(degree + res), outerRadius * sin(degree + res), 0);
		glVertex3f(innerRadius * cos(degree + res), innerRadius * sin(degree + res), 0);
	}
	//back
	for(float degree = 0; degree < 2 * M_PI - gap * res; degree += res){
		glVertex3f(innerRadius * cos(degree), innerRadius* sin(degree), -thickness);
		glVertex3f(outerRadius * cos(degree), outerRadius * sin(degree), -thickness);
		glVertex3f(outerRadius * cos(degree + res), outerRadius * sin(degree + res), -thickness);
		glVertex3f(innerRadius * cos(degree + res), innerRadius * sin(degree + res), -thickness);
	}
	//gap in between inner
	for(float degree = 0; degree < 2 * M_PI - gap * res; degree += res){
		glVertex3f(innerRadius * cos(degree), innerRadius* sin(degree), -thickness);
		glVertex3f(innerRadius * cos(degree), innerRadius * sin(degree), 0);
		glVertex3f(innerRadius * cos(degree + res), innerRadius * sin(degree + res), 0);
		glVertex3f(innerRadius * cos(degree + res), innerRadius * sin(degree + res), -thickness);
	}
	//gap in between outer
	for(float degree = 0; degree < 2 * M_PI - gap * res; degree += res){
		glVertex3f(outerRadius * cos(degree), outerRadius * sin(degree), -thickness);
		glVertex3f(outerRadius * cos(degree), outerRadius * sin(degree), 0);
		glVertex3f(outerRadius * cos(degree + res), outerRadius * sin(degree + res), 0);
		glVertex3f(outerRadius * cos(degree + res), outerRadius * sin(degree + res), -thickness);
	}
	glEnd();
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
	obstacle(1, 1.5, 0.5);
	//player
	glTranslatef(0, -4, 0);
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
