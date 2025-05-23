#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <gl/glut.h>
#include <vector>
using namespace std;

class Obstacle{
public: 
	static float innerRadius;
	static float outerRadius;
	static float thickness;
	static float res;
	static int gap;
	Obstacle(float x_ = 0, float y_ = 0, float z_ = 0): x(x_), y(y_), z(z_){
		angle = rand() % 360;
	}
	float getAngle(){
		return angle;
	}
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
		if(angle < 0){
			angle += 360;
		}
		else if(angle > 360){
			angle -= 360;
		}
	}
	void setZ(float z_){
		z = z_;
	}
	float getZ(){
		return z;
	}
private:
	float angle;
	float x, y, z;

};

class ObstacleScene{
public:
	static float forwardRate;
	ObstacleScene(int len_, float x_ = 0, float y_ = 0, float z_ = 0, float gap_ = 0):len(len_), x(x_), y(y_), z(z_), gap(gap_){
		score = 0;
		populateObstacles();
	}
	void populateObstacles(){
		for(int i = 0; i < len; i++){
			obstacles.push_back(new Obstacle());
		}
		for(int i = len - 1; i >= 0; i--){
			obstacles[i] -> place(x, y, z + i * gap);
		}
	}
	void goForward(){
		for(int i = 0; i < obstacles.size(); i++){
			obstacles[i] -> setZ(obstacles[i] -> getZ() + ObstacleScene::forwardRate);
		}
	}
	void checkPops(){
		if(obstacles.back() -> getZ() > 3){
			float ang = obstacles.back() -> getAngle();
			if(ang >= 360 - Obstacle::gap / 2 && ang <= 360){
				score++;
				ObstacleScene::forwardRate += 0.01;
			}else{
				score = 0;
			}
			cout << "score: " << score << endl;
			obstacles.pop_back();
			obstacles.insert(obstacles.begin(), new Obstacle(0, 0, z - gap));
		}
	}
	void rotateFirst(bool clockWise){
		obstacles.back() -> rotate(obstacles.back() -> getAngle() + (clockWise ? 10 : -10));
	}
	void drawScene(){
		for(int i = 0; i < obstacles.size(); i++){
			obstacles[i] -> drawObstacle();
		}
	}
private:
	float x, y, z, gap;
	int score;
	int len;
	vector<Obstacle*> obstacles;
};
