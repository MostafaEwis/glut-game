#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <gl/glut.h>

class Obstacle{
public: 
	static float innerRadius;
	static float outerRadius;
	static float thickness;
	static float res;
	static int gap;
	Obstacle(float x_ = 0, float y_ = 0, float z_ = 0): x(x_), y(y_), z(z_){}
	drawObstacle(){
		//(float innerRadius, float outerRadius, float thickness, float res = 0.01, int gap = 50)
		//.		.		.		.		.
		//|		|		|		|		|
		//.		.		.		.		.
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(angle, 0, 0, 1);
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
		glPopMatrix();
	}
	void place(float x_, float y_, float z_){
		x = x_;
		y = y_;
		z = z_;
	}
	void rotate(float angle_){
		angle = angle_;
	}
private:
	float angle = 0;
	float x, y, z;

};

class ObstacleScene{
public:
	ObstacleScene(int len_, float x_ = 0, float y_ = 0, float z_ = 0, float gap_ = 0):len(len_), x(x_), y(y_), z(z_), gap(gap_){
		populateObstacles();
	}
	void populateObstacles(){
		obstacles = new Obstacle[len];
		for(int i = 0; i < len; i++){
			obstacles[i].place(x, y, z + i * gap);
		}
	}
	void drawScene(){
		for(int i = 0; i < len; i++){
			obstacles[i].drawObstacle();
		}
	}
private:
	float x, y, z, gap;
	int len;
	Obstacle* obstacles;
};
