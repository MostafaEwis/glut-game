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
//*** obstacles animatoin [x]
//	obstacle front goes back [x]
//	obstacle move forward [x]
//	obstacles rotate by the keyboard[x]
//	front obstacle should be selected and controlled [x]
//draw a ball where the player should be (will be fixed) [x]
//collision detection [x]
//texture [] 
float cx = 0;
float cy = 5;
float cz = 10;
float fps = 1000.f / 60.f;
float Obstacle::innerRadius = 1;
float Obstacle::outerRadius = 1.5;
float Obstacle::thickness = 0.5;
float Obstacle::res = 0.01;
float ObstacleScene::forwardRate = 0.01;
int Obstacle::gap = 130;
float lx = 0;
float ly = 5;
float lz = 12;
ObstacleScene scene(6, 0, 0, -10, 3);
void applyLighting(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = {lx, ly, lz, 0};
	GLfloat ambient[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat	diffuse[] = {0.7, 0.7, 0.7, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
}
void myInit(){
	GLfloat width = 700;
	GLfloat height = 700;
	glClearColor( 1.0, 0.75, 0.8, 1);
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
	glEnable(GL_DEPTH_TEST);
	applyLighting();
}
void reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float) w / (float) h, 1.0f, 100.0f);

}
void playerMaterial(){
	GLfloat amb[]={0.02f,0.0f,0.0f,1.0f};
	GLfloat diff[]={0.07568f,0.61424f,0.07568f,1.0f};
	GLfloat spec[]={0.633f,0.727811f,0.21f,1.0f};
	GLfloat shine=28.f;
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);

}
void obstacleMaterial(){
	GLfloat amb[]={0.02f,0.0f,0.0f,1.0f};
	GLfloat diff[]={0.07568f,0.61424f,0.07568f,1.0f};
	GLfloat spec[]={0.633f,0.727811f,0.21f,1.0f};
	GLfloat shine=28.f;
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
}
void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLineWidth(1);
	gluLookAt(cx, cy, cz,
		0.f, 0.f, 0.f,
		0.f, 1.f, 0.f);
	//purple
	glColor3f(156.f / 256, 0, 255.f/256);
	obstacleMaterial();
	scene.drawScene();
	scene.checkPops();
	applyLighting();
	glTranslatef(0, -1 * Obstacle::outerRadius, 3);
	//player
	glColor3f(0, 1, 0);
	playerMaterial();
	glutSolidSphere(0.6, 50, 50);
	glFlush();
	glutSwapBuffers();
}
void rotateObstacle(unsigned char key, int x, int y){
	float change = 0.1;
	if(key == 'k'){
		scene.rotateFirst(false);	
	}else if(key == 'j'){
		scene.rotateFirst(true);	
	}else if(key == '8'){
		cy += change;
		
	}else if(key == '2'){
		cy -= change;
		
	}else if(key == '6'){
		cx += change;
	}else if(key == '4'){
		cx -= change;
	}else if(key == '5'){
		cz += change;
	}else if(key == '-'){
		cz -= change;
	}else if(key == 'w'){
		ly += change;
	}else if(key == 's'){
		ly -= change;
	}else if(key == 'd'){
		lx += change;
	}else if(key == 'a'){
		lx -= change;
	}
	glutPostRedisplay();

}
void timerFunc(int t){
	scene.goForward();
	glutPostRedisplay();
	glutTimerFunc(fps, timerFunc, 0);
}
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(GetSystemMetrics(SM_CXSCREEN) / 2.0f - 700 / 2, GetSystemMetrics(SM_CYSCREEN) / 2.0f - 700 / 2);
	glutCreateWindow("Abdo Nawar");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(rotateObstacle);
	glutTimerFunc(fps, timerFunc, 0);
	myInit();
	glutMainLoop();

	return 0;
}
