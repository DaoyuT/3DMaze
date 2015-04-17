
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
//#include <assert.h>
//#include <stdarg.h>
#include <glut.h>
//#include "glm.h"
//#include "gltb.h"
//#include "dirent32.h"
GLboolean CHEAT = GL_FALSE;
typedef struct{

	GLfloat facenormal[3];
	GLfloat triangle1[3][3];
	GLfloat triangle2[3][3];
	GLfloat diffuse[3];
	GLfloat ambient[3];
	GLfloat specular[3];

}Face;

typedef struct{

	GLfloat orignalcoordinates[3];

	GLfloat vx[3];
	GLfloat vy[3];
	GLfloat vz[3];

	char*name;

	Face groupfaces[1000];
	Face groupfaces2[10];
	GLint enable;
	GLint numoffaces;
	GLint numoffaces2;

}Group;


typedef struct{

	Group Modelgroups[100];

	GLint numofgroups;

}MazeModel;

MazeModel maze;

void scalegroup(Group* gr, GLfloat scalex, GLfloat scaley, GLfloat scalez)
{
	for (int i = 0; i <= (*gr).numoffaces - 1; i++)
	{
		(*gr).groupfaces[i].triangle1[0][0] = (*gr).groupfaces[i].triangle1[0][0] * scalex;
		(*gr).groupfaces[i].triangle1[0][1] = (*gr).groupfaces[i].triangle1[0][1] * scaley;
		(*gr).groupfaces[i].triangle1[0][2] = (*gr).groupfaces[i].triangle1[0][2] * scalez;

		(*gr).groupfaces[i].triangle1[1][0] = (*gr).groupfaces[i].triangle1[1][0] * scalex;
		(*gr).groupfaces[i].triangle1[1][1] = (*gr).groupfaces[i].triangle1[1][1] * scaley;
		(*gr).groupfaces[i].triangle1[1][2] = (*gr).groupfaces[i].triangle1[1][2] * scalez;

		(*gr).groupfaces[i].triangle1[2][0] = (*gr).groupfaces[i].triangle1[2][0] * scalex;
		(*gr).groupfaces[i].triangle1[2][1] = (*gr).groupfaces[i].triangle1[2][1] * scaley;
		(*gr).groupfaces[i].triangle1[2][2] = (*gr).groupfaces[i].triangle1[2][2] * scalez;

		(*gr).groupfaces[i].triangle2[0][0] = (*gr).groupfaces[i].triangle2[0][0] * scalex;
		(*gr).groupfaces[i].triangle2[0][1] = (*gr).groupfaces[i].triangle2[0][1] * scaley;
		(*gr).groupfaces[i].triangle2[0][2] = (*gr).groupfaces[i].triangle2[0][2] * scalez;

		(*gr).groupfaces[i].triangle2[1][0] = (*gr).groupfaces[i].triangle2[1][0] * scalex;
		(*gr).groupfaces[i].triangle2[1][1] = (*gr).groupfaces[i].triangle2[1][1] * scaley;
		(*gr).groupfaces[i].triangle2[1][2] = (*gr).groupfaces[i].triangle2[1][2] * scalez;

		(*gr).groupfaces[i].triangle2[2][0] = (*gr).groupfaces[i].triangle2[2][0] * scalex;
		(*gr).groupfaces[i].triangle2[2][1] = (*gr).groupfaces[i].triangle2[2][1] * scaley;
		(*gr).groupfaces[i].triangle2[2][2] = (*gr).groupfaces[i].triangle2[2][2] * scalez;
	}

	for (int i = 0; i <= (*gr).numoffaces2 - 1; i++)
	{
		(*gr).groupfaces2[i].triangle1[0][0] = (*gr).groupfaces2[i].triangle1[0][0] * scalex;
		(*gr).groupfaces2[i].triangle1[0][1] = (*gr).groupfaces2[i].triangle1[0][1] * scaley;
		(*gr).groupfaces2[i].triangle1[0][2] = (*gr).groupfaces2[i].triangle1[0][2] * scalez;

		(*gr).groupfaces2[i].triangle1[1][0] = (*gr).groupfaces2[i].triangle1[1][0] * scalex;
		(*gr).groupfaces2[i].triangle1[1][1] = (*gr).groupfaces2[i].triangle1[1][1] * scaley;
		(*gr).groupfaces2[i].triangle1[1][2] = (*gr).groupfaces2[i].triangle1[1][2] * scalez;

		(*gr).groupfaces2[i].triangle1[2][0] = (*gr).groupfaces2[i].triangle1[2][0] * scalex;
		(*gr).groupfaces2[i].triangle1[2][1] = (*gr).groupfaces2[i].triangle1[2][1] * scaley;
		(*gr).groupfaces2[i].triangle1[2][2] = (*gr).groupfaces2[i].triangle1[2][2] * scalez;

		(*gr).groupfaces2[i].triangle2[0][0] = (*gr).groupfaces2[i].triangle2[0][0] * scalex;
		(*gr).groupfaces2[i].triangle2[0][1] = (*gr).groupfaces2[i].triangle2[0][1] * scaley;
		(*gr).groupfaces2[i].triangle2[0][2] = (*gr).groupfaces2[i].triangle2[0][2] * scalez;

		(*gr).groupfaces2[i].triangle2[1][0] = (*gr).groupfaces2[i].triangle2[1][0] * scalex;
		(*gr).groupfaces2[i].triangle2[1][1] = (*gr).groupfaces2[i].triangle2[1][1] * scaley;
		(*gr).groupfaces2[i].triangle2[1][2] = (*gr).groupfaces2[i].triangle2[1][2] * scalez;

		(*gr).groupfaces2[i].triangle2[2][0] = (*gr).groupfaces2[i].triangle2[2][0] * scalex;
		(*gr).groupfaces2[i].triangle2[2][1] = (*gr).groupfaces2[i].triangle2[2][1] * scaley;
		(*gr).groupfaces2[i].triangle2[2][2] = (*gr).groupfaces2[i].triangle2[2][2] * scalez;
	}


}
void obj_to_world(Group* gr){

	for (int i = 0; i <= (*gr).numoffaces - 1; i++)
	{
		GLfloat fx = (*gr).groupfaces[i].facenormal[0];
		GLfloat fy = (*gr).groupfaces[i].facenormal[1];
		GLfloat fz = (*gr).groupfaces[i].facenormal[2];

		GLfloat t1x = (*gr).groupfaces[i].triangle1[0][0];
		GLfloat t1y = (*gr).groupfaces[i].triangle1[0][1];
		GLfloat t1z = (*gr).groupfaces[i].triangle1[0][2];

		GLfloat t2x = (*gr).groupfaces[i].triangle1[1][0];
		GLfloat t2y = (*gr).groupfaces[i].triangle1[1][1];
		GLfloat t2z = (*gr).groupfaces[i].triangle1[1][2];

		GLfloat t3x = (*gr).groupfaces[i].triangle1[2][0];
		GLfloat t3y = (*gr).groupfaces[i].triangle1[2][1];
		GLfloat t3z = (*gr).groupfaces[i].triangle1[2][2];

		GLfloat t4x = (*gr).groupfaces[i].triangle2[0][0];
		GLfloat t4y = (*gr).groupfaces[i].triangle2[0][1];
		GLfloat t4z = (*gr).groupfaces[i].triangle2[0][2];

		GLfloat t5x = (*gr).groupfaces[i].triangle2[1][0];
		GLfloat t5y = (*gr).groupfaces[i].triangle2[1][1];
		GLfloat t5z = (*gr).groupfaces[i].triangle2[1][2];

		GLfloat t6x = (*gr).groupfaces[i].triangle2[2][0];
		GLfloat t6y = (*gr).groupfaces[i].triangle2[2][1];
		GLfloat t6z = (*gr).groupfaces[i].triangle2[2][2];

		(*gr).groupfaces[i].facenormal[0] = (*gr).vx[0] * fx + (*gr).vy[0] * fy + (*gr).vz[0] * fz + (*gr).orignalcoordinates[0];
		(*gr).groupfaces[i].facenormal[1] = (*gr).vx[1] * fx + (*gr).vy[1] * fy + (*gr).vz[1] * fz + (*gr).orignalcoordinates[1];
		(*gr).groupfaces[i].facenormal[2] = (*gr).vx[2] * fx + (*gr).vy[2] * fy + (*gr).vz[2] * fz + (*gr).orignalcoordinates[2];

		(*gr).groupfaces[i].triangle1[0][0] = (*gr).vx[0] * t1x + (*gr).vy[0] * t1y + (*gr).vz[0] * t1z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces[i].triangle1[0][1] = (*gr).vx[1] * t1x + (*gr).vy[1] * t1y + (*gr).vz[1] * t1z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces[i].triangle1[0][2] = (*gr).vx[2] * t1x + (*gr).vy[2] * t1y + (*gr).vz[2] * t1z + (*gr).orignalcoordinates[2];

		(*gr).groupfaces[i].triangle1[1][0] = (*gr).vx[0] * t2x + (*gr).vy[0] * t2y + (*gr).vz[0] * t2z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces[i].triangle1[1][1] = (*gr).vx[1] * t2x + (*gr).vy[1] * t2y + (*gr).vz[1] * t2z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces[i].triangle1[1][2] = (*gr).vx[2] * t2x + (*gr).vy[2] * t2y + (*gr).vz[2] * t2z + (*gr).orignalcoordinates[2];

		(*gr).groupfaces[i].triangle1[2][0] = (*gr).vx[0] * t3x + (*gr).vy[0] * t3y + (*gr).vz[0] * t3z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces[i].triangle1[2][1] = (*gr).vx[1] * t3x + (*gr).vy[1] * t3y + (*gr).vz[1] * t3z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces[i].triangle1[2][2] = (*gr).vx[2] * t3x + (*gr).vy[2] * t3y + (*gr).vz[2] * t3z + (*gr).orignalcoordinates[2];


		(*gr).groupfaces[i].triangle2[0][0] = (*gr).vx[0] * t4x + (*gr).vy[0] * t4y + (*gr).vz[0] * t4z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces[i].triangle2[0][1] = (*gr).vx[1] * t4x + (*gr).vy[1] * t4y + (*gr).vz[1] * t4z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces[i].triangle2[0][2] = (*gr).vx[2] * t4x + (*gr).vy[2] * t4y + (*gr).vz[2] * t4z + (*gr).orignalcoordinates[2];

		(*gr).groupfaces[i].triangle2[1][0] = (*gr).vx[0] * t5x + (*gr).vy[0] * t5y + (*gr).vz[0] * t5z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces[i].triangle2[1][1] = (*gr).vx[1] * t5x + (*gr).vy[1] * t5y + (*gr).vz[1] * t5z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces[i].triangle2[1][2] = (*gr).vx[2] * t5x + (*gr).vy[2] * t5y + (*gr).vz[2] * t5z + (*gr).orignalcoordinates[2];

		(*gr).groupfaces[i].triangle2[2][0] = (*gr).vx[0] * t6x + (*gr).vy[0] * t6y + (*gr).vz[0] * t6z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces[i].triangle2[2][1] = (*gr).vx[1] * t6x + (*gr).vy[1] * t6y + (*gr).vz[1] * t6z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces[i].triangle2[2][2] = (*gr).vx[2] * t6x + (*gr).vy[2] * t6y + (*gr).vz[2] * t6z + (*gr).orignalcoordinates[2];


	}

	for (int i = 0; i <= (*gr).numoffaces2 - 1; i++)
	{
		GLfloat fx = (*gr).groupfaces2[i].facenormal[0];
		GLfloat fy = (*gr).groupfaces2[i].facenormal[1];
		GLfloat fz = (*gr).groupfaces2[i].facenormal[2];

		GLfloat t1x = (*gr).groupfaces2[i].triangle1[0][0];
		GLfloat t1y = (*gr).groupfaces2[i].triangle1[0][1];
		GLfloat t1z = (*gr).groupfaces2[i].triangle1[0][2];

		GLfloat t2x = (*gr).groupfaces2[i].triangle1[1][0];
		GLfloat t2y = (*gr).groupfaces2[i].triangle1[1][1];
		GLfloat t2z = (*gr).groupfaces2[i].triangle1[1][2];

		GLfloat t3x = (*gr).groupfaces2[i].triangle1[2][0];
		GLfloat t3y = (*gr).groupfaces2[i].triangle1[2][1];
		GLfloat t3z = (*gr).groupfaces2[i].triangle1[2][2];

		GLfloat t4x = (*gr).groupfaces2[i].triangle2[0][0];
		GLfloat t4y = (*gr).groupfaces2[i].triangle2[0][1];
		GLfloat t4z = (*gr).groupfaces2[i].triangle2[0][2];

		GLfloat t5x = (*gr).groupfaces2[i].triangle2[1][0];
		GLfloat t5y = (*gr).groupfaces2[i].triangle2[1][1];
		GLfloat t5z = (*gr).groupfaces2[i].triangle2[1][2];

		GLfloat t6x = (*gr).groupfaces2[i].triangle2[2][0];
		GLfloat t6y = (*gr).groupfaces2[i].triangle2[2][1];
		GLfloat t6z = (*gr).groupfaces2[i].triangle2[2][2];

		(*gr).groupfaces2[i].facenormal[0] = (*gr).vx[0] * fx + (*gr).vy[0] * fy + (*gr).vz[0] * fz + (*gr).orignalcoordinates[0];
		(*gr).groupfaces2[i].facenormal[1] = (*gr).vx[1] * fx + (*gr).vy[1] * fy + (*gr).vz[1] * fz + (*gr).orignalcoordinates[1];
		(*gr).groupfaces2[i].facenormal[2] = (*gr).vx[2] * fx + (*gr).vy[2] * fy + (*gr).vz[2] * fz + (*gr).orignalcoordinates[2];

		(*gr).groupfaces2[i].triangle1[0][0] = (*gr).vx[0] * t1x + (*gr).vy[0] * t1y + (*gr).vz[0] * t1z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces2[i].triangle1[0][1] = (*gr).vx[1] * t1x + (*gr).vy[1] * t1y + (*gr).vz[1] * t1z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces2[i].triangle1[0][2] = (*gr).vx[2] * t1x + (*gr).vy[2] * t1y + (*gr).vz[2] * t1z + (*gr).orignalcoordinates[2];

		(*gr).groupfaces2[i].triangle1[1][0] = (*gr).vx[0] * t2x + (*gr).vy[0] * t2y + (*gr).vz[0] * t2z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces2[i].triangle1[1][1] = (*gr).vx[1] * t2x + (*gr).vy[1] * t2y + (*gr).vz[1] * t2z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces2[i].triangle1[1][2] = (*gr).vx[2] * t2x + (*gr).vy[2] * t2y + (*gr).vz[2] * t2z + (*gr).orignalcoordinates[2];

		(*gr).groupfaces2[i].triangle1[2][0] = (*gr).vx[0] * t3x + (*gr).vy[0] * t3y + (*gr).vz[0] * t3z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces2[i].triangle1[2][1] = (*gr).vx[1] * t3x + (*gr).vy[1] * t3y + (*gr).vz[1] * t3z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces2[i].triangle1[2][2] = (*gr).vx[2] * t3x + (*gr).vy[2] * t3y + (*gr).vz[2] * t3z + (*gr).orignalcoordinates[2];


		(*gr).groupfaces2[i].triangle2[0][0] = (*gr).vx[0] * t4x + (*gr).vy[0] * t4y + (*gr).vz[0] * t4z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces2[i].triangle2[0][1] = (*gr).vx[1] * t4x + (*gr).vy[1] * t4y + (*gr).vz[1] * t4z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces2[i].triangle2[0][2] = (*gr).vx[2] * t4x + (*gr).vy[2] * t4y + (*gr).vz[2] * t4z + (*gr).orignalcoordinates[2];

		(*gr).groupfaces2[i].triangle2[1][0] = (*gr).vx[0] * t5x + (*gr).vy[0] * t5y + (*gr).vz[0] * t5z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces2[i].triangle2[1][1] = (*gr).vx[1] * t5x + (*gr).vy[1] * t5y + (*gr).vz[1] * t5z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces2[i].triangle2[1][2] = (*gr).vx[2] * t5x + (*gr).vy[2] * t5y + (*gr).vz[2] * t5z + (*gr).orignalcoordinates[2];

		(*gr).groupfaces2[i].triangle2[2][0] = (*gr).vx[0] * t6x + (*gr).vy[0] * t6y + (*gr).vz[0] * t6z + (*gr).orignalcoordinates[0];
		(*gr).groupfaces2[i].triangle2[2][1] = (*gr).vx[1] * t6x + (*gr).vy[1] * t6y + (*gr).vz[1] * t6z + (*gr).orignalcoordinates[1];
		(*gr).groupfaces2[i].triangle2[2][2] = (*gr).vx[2] * t6x + (*gr).vy[2] * t6y + (*gr).vz[2] * t6z + (*gr).orignalcoordinates[2];


	}
}
void creatWall1()
{
	maze.Modelgroups[0].enable = 1;// whether the group is still exist

	//maze.Modelgroups[0].name="Wall1";// the first group name

	maze.Modelgroups[0].orignalcoordinates[0] = 0;//the first group's orign coordinates
	maze.Modelgroups[0].orignalcoordinates[1] = 0;
	maze.Modelgroups[0].orignalcoordinates[2] = 0;

	maze.Modelgroups[0].vx[0] = 1;// the object world x direction
	maze.Modelgroups[0].vx[1] = 0;
	maze.Modelgroups[0].vx[2] = 0;

	maze.Modelgroups[0].vy[0] = 0;// the object world y direction
	maze.Modelgroups[0].vy[1] = 1;
	maze.Modelgroups[0].vy[2] = 0;

	maze.Modelgroups[0].vz[0] = 0;// the object world z direction
	maze.Modelgroups[0].vz[1] = 0;
	maze.Modelgroups[0].vz[2] = 1;

	maze.Modelgroups[0].numoffaces = 192;
	maze.Modelgroups[0].numoffaces2 = 6;
	maze.Modelgroups[0].groupfaces2[0].facenormal[0] = 0;
	maze.Modelgroups[0].groupfaces2[0].facenormal[1] = 1;
	maze.Modelgroups[0].groupfaces2[0].facenormal[2] = 0;

	maze.Modelgroups[0].groupfaces2[0].triangle1[0][0] = -4;
	maze.Modelgroups[0].groupfaces2[0].triangle1[0][1] = 1;
	maze.Modelgroups[0].groupfaces2[0].triangle1[0][2] = -4;
	maze.Modelgroups[0].groupfaces2[0].triangle1[1][0] = 4;
	maze.Modelgroups[0].groupfaces2[0].triangle1[1][1] = 1;
	maze.Modelgroups[0].groupfaces2[0].triangle1[1][2] = -4;
	maze.Modelgroups[0].groupfaces2[0].triangle1[2][0] = -4;
	maze.Modelgroups[0].groupfaces2[0].triangle1[2][1] = 1;
	maze.Modelgroups[0].groupfaces2[0].triangle1[2][2] = 4;

	maze.Modelgroups[0].groupfaces2[0].triangle2[0][0] = 4;
	maze.Modelgroups[0].groupfaces2[0].triangle2[0][1] = 1;
	maze.Modelgroups[0].groupfaces2[0].triangle2[0][2] = 4;
	maze.Modelgroups[0].groupfaces2[0].triangle2[1][0] = -4;
	maze.Modelgroups[0].groupfaces2[0].triangle2[1][1] = 1;
	maze.Modelgroups[0].groupfaces2[0].triangle2[1][2] = 4;
	maze.Modelgroups[0].groupfaces2[0].triangle2[2][0] = 4;
	maze.Modelgroups[0].groupfaces2[0].triangle2[2][1] = 1;
	maze.Modelgroups[0].groupfaces2[0].triangle2[2][2] = -4;

	maze.Modelgroups[0].groupfaces2[1].facenormal[0] = 0;
	maze.Modelgroups[0].groupfaces2[1].facenormal[1] = -1;
	maze.Modelgroups[0].groupfaces2[1].facenormal[2] = 0;

	maze.Modelgroups[0].groupfaces2[1].triangle1[0][0] = 4;
	maze.Modelgroups[0].groupfaces2[1].triangle1[0][1] = -1;
	maze.Modelgroups[0].groupfaces2[1].triangle1[0][2] = -4;
	maze.Modelgroups[0].groupfaces2[1].triangle1[1][0] = -4;
	maze.Modelgroups[0].groupfaces2[1].triangle1[1][1] = -1;
	maze.Modelgroups[0].groupfaces2[1].triangle1[1][2] = -4;
	maze.Modelgroups[0].groupfaces2[1].triangle1[2][0] = 4;
	maze.Modelgroups[0].groupfaces2[1].triangle1[2][1] = -1;
	maze.Modelgroups[0].groupfaces2[1].triangle1[2][2] = 4;

	maze.Modelgroups[0].groupfaces2[1].triangle2[0][0] = -4;
	maze.Modelgroups[0].groupfaces2[1].triangle2[0][1] = -1;
	maze.Modelgroups[0].groupfaces2[1].triangle2[0][2] = 4;
	maze.Modelgroups[0].groupfaces2[1].triangle2[1][0] = 4;
	maze.Modelgroups[0].groupfaces2[1].triangle2[1][1] = -1;
	maze.Modelgroups[0].groupfaces2[1].triangle2[1][2] = 4;
	maze.Modelgroups[0].groupfaces2[1].triangle2[2][0] = -4;
	maze.Modelgroups[0].groupfaces2[1].triangle2[2][1] = -1;
	maze.Modelgroups[0].groupfaces2[1].triangle2[2][2] = -4;

	maze.Modelgroups[0].groupfaces2[2].facenormal[0] = 1;
	maze.Modelgroups[0].groupfaces2[2].facenormal[1] = 0;
	maze.Modelgroups[0].groupfaces2[2].facenormal[2] = 0;

	maze.Modelgroups[0].groupfaces2[2].triangle1[0][0] = 4;
	maze.Modelgroups[0].groupfaces2[2].triangle1[0][1] = 1;
	maze.Modelgroups[0].groupfaces2[2].triangle1[0][2] = -4;
	maze.Modelgroups[0].groupfaces2[2].triangle1[1][0] = 4;
	maze.Modelgroups[0].groupfaces2[2].triangle1[1][1] = -1;
	maze.Modelgroups[0].groupfaces2[2].triangle1[1][2] = -4;
	maze.Modelgroups[0].groupfaces2[2].triangle1[2][0] = 4;
	maze.Modelgroups[0].groupfaces2[2].triangle1[2][1] = 1;
	maze.Modelgroups[0].groupfaces2[2].triangle1[2][2] = 4;

	maze.Modelgroups[0].groupfaces2[2].triangle2[0][0] = 4;
	maze.Modelgroups[0].groupfaces2[2].triangle2[0][1] = -1;
	maze.Modelgroups[0].groupfaces2[2].triangle2[0][2] = 4;
	maze.Modelgroups[0].groupfaces2[2].triangle2[1][0] = 4;
	maze.Modelgroups[0].groupfaces2[2].triangle2[1][1] = 1;
	maze.Modelgroups[0].groupfaces2[2].triangle2[1][2] = 4;
	maze.Modelgroups[0].groupfaces2[2].triangle2[2][0] = 4;
	maze.Modelgroups[0].groupfaces2[2].triangle2[2][1] = -1;
	maze.Modelgroups[0].groupfaces2[2].triangle2[2][2] = -4;

	maze.Modelgroups[0].groupfaces2[3].facenormal[0] = -1;
	maze.Modelgroups[0].groupfaces2[3].facenormal[1] = 0;
	maze.Modelgroups[0].groupfaces2[3].facenormal[2] = 0;

	maze.Modelgroups[0].groupfaces2[3].triangle1[0][0] = -4;
	maze.Modelgroups[0].groupfaces2[3].triangle1[0][1] = -1;
	maze.Modelgroups[0].groupfaces2[3].triangle1[0][2] = -4;
	maze.Modelgroups[0].groupfaces2[3].triangle1[1][0] = -4;
	maze.Modelgroups[0].groupfaces2[3].triangle1[1][1] = 1;
	maze.Modelgroups[0].groupfaces2[3].triangle1[1][2] = -4;
	maze.Modelgroups[0].groupfaces2[3].triangle1[2][0] = -4;
	maze.Modelgroups[0].groupfaces2[3].triangle1[2][1] = -1;
	maze.Modelgroups[0].groupfaces2[3].triangle1[2][2] = 4;

	maze.Modelgroups[0].groupfaces2[3].triangle2[0][0] = -4;
	maze.Modelgroups[0].groupfaces2[3].triangle2[0][1] = 1;
	maze.Modelgroups[0].groupfaces2[3].triangle2[0][2] = 4;
	maze.Modelgroups[0].groupfaces2[3].triangle2[1][0] = -4;
	maze.Modelgroups[0].groupfaces2[3].triangle2[1][1] = -1;
	maze.Modelgroups[0].groupfaces2[3].triangle2[1][2] = 4;
	maze.Modelgroups[0].groupfaces2[3].triangle2[2][0] = -4;
	maze.Modelgroups[0].groupfaces2[3].triangle2[2][1] = 1;
	maze.Modelgroups[0].groupfaces2[3].triangle2[2][2] = -4;

	maze.Modelgroups[0].groupfaces2[4].facenormal[0] = 0;
	maze.Modelgroups[0].groupfaces2[4].facenormal[1] = 0;
	maze.Modelgroups[0].groupfaces2[4].facenormal[2] = 1;

	maze.Modelgroups[0].groupfaces2[4].triangle1[0][0] = -4;
	maze.Modelgroups[0].groupfaces2[4].triangle1[0][1] = 1;
	maze.Modelgroups[0].groupfaces2[4].triangle1[0][2] = 4;
	maze.Modelgroups[0].groupfaces2[4].triangle1[1][0] = 4;
	maze.Modelgroups[0].groupfaces2[4].triangle1[1][1] = 1;
	maze.Modelgroups[0].groupfaces2[4].triangle1[1][2] = 4;
	maze.Modelgroups[0].groupfaces2[4].triangle1[2][0] = -4;
	maze.Modelgroups[0].groupfaces2[4].triangle1[2][1] = -1;
	maze.Modelgroups[0].groupfaces2[4].triangle1[2][2] = 4;

	maze.Modelgroups[0].groupfaces2[4].triangle2[0][0] = 4;
	maze.Modelgroups[0].groupfaces2[4].triangle2[0][1] = -1;
	maze.Modelgroups[0].groupfaces2[4].triangle2[0][2] = 4;
	maze.Modelgroups[0].groupfaces2[4].triangle2[1][0] = -4;
	maze.Modelgroups[0].groupfaces2[4].triangle2[1][1] = -1;
	maze.Modelgroups[0].groupfaces2[4].triangle2[1][2] = 4;
	maze.Modelgroups[0].groupfaces2[4].triangle2[2][0] = 4;
	maze.Modelgroups[0].groupfaces2[4].triangle2[2][1] = 1;
	maze.Modelgroups[0].groupfaces2[4].triangle2[2][2] = 4;

	maze.Modelgroups[0].groupfaces2[5].facenormal[0] = 0;
	maze.Modelgroups[0].groupfaces2[5].facenormal[1] = 0;
	maze.Modelgroups[0].groupfaces2[5].facenormal[2] = -1;

	maze.Modelgroups[0].groupfaces2[5].triangle1[0][0] = -4;
	maze.Modelgroups[0].groupfaces2[5].triangle1[0][1] = -1;
	maze.Modelgroups[0].groupfaces2[5].triangle1[0][2] = -4;
	maze.Modelgroups[0].groupfaces2[5].triangle1[1][0] = 4;
	maze.Modelgroups[0].groupfaces2[5].triangle1[1][1] = -1;
	maze.Modelgroups[0].groupfaces2[5].triangle1[1][2] = -4;
	maze.Modelgroups[0].groupfaces2[5].triangle1[2][0] = -4;
	maze.Modelgroups[0].groupfaces2[5].triangle1[2][1] = 1;
	maze.Modelgroups[0].groupfaces2[5].triangle1[2][2] = -4;

	maze.Modelgroups[0].groupfaces2[5].triangle2[0][0] = 4;
	maze.Modelgroups[0].groupfaces2[5].triangle2[0][1] = 1;
	maze.Modelgroups[0].groupfaces2[5].triangle2[0][2] = -4;
	maze.Modelgroups[0].groupfaces2[5].triangle2[1][0] = -4;
	maze.Modelgroups[0].groupfaces2[5].triangle2[1][1] = 1;
	maze.Modelgroups[0].groupfaces2[5].triangle2[1][2] = -4;
	maze.Modelgroups[0].groupfaces2[5].triangle2[2][0] = 4;
	maze.Modelgroups[0].groupfaces2[5].triangle2[2][1] = -1;
	maze.Modelgroups[0].groupfaces2[5].triangle2[2][2] = -4;

	int count = 0;

	for (int i = -4; i <= 3; i++)//wall 1  64faces
	for (int j = -4; j <= 3; j++)
	{
		maze.Modelgroups[0].groupfaces[count].ambient[0] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[1] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[2] = 0.2;

		maze.Modelgroups[0].groupfaces[count].diffuse[0] = 1;
		maze.Modelgroups[0].groupfaces[count].diffuse[1] = 0;
		maze.Modelgroups[0].groupfaces[count].diffuse[2] = 0;

		maze.Modelgroups[0].groupfaces[count].specular[0] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[1] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[2] = 0;

		maze.Modelgroups[0].groupfaces[count].facenormal[0] = 0;
		maze.Modelgroups[0].groupfaces[count].facenormal[1] = 1;
		maze.Modelgroups[0].groupfaces[count].facenormal[2] = 0;

		maze.Modelgroups[0].groupfaces[count].triangle1[0][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][1] = 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][2] = j;

		maze.Modelgroups[0].groupfaces[count].triangle1[1][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][1] = 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][2] = j;

		maze.Modelgroups[0].groupfaces[count].triangle1[2][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][1] = 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][2] = j + 1;


		maze.Modelgroups[0].groupfaces[count].triangle2[0][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][1] = 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][2] = j + 1;

		maze.Modelgroups[0].groupfaces[count].triangle2[1][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][1] = 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][2] = j + 1;

		maze.Modelgroups[0].groupfaces[count].triangle2[2][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][1] = 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][2] = j;

		count++;
	}

	//  for(int i=-4;i<=3;i++)//wall 2  64 faces
	for (int i = 4; i >= -3; i--)//wall 2  64 faces
	for (int j = -4; j <= 3; j++)
	{
		maze.Modelgroups[0].groupfaces[count].ambient[0] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[1] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[2] = 0.2;

		maze.Modelgroups[0].groupfaces[count].diffuse[0] = 1;
		maze.Modelgroups[0].groupfaces[count].diffuse[1] = 0;
		maze.Modelgroups[0].groupfaces[count].diffuse[2] = 0;

		maze.Modelgroups[0].groupfaces[count].specular[0] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[1] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[2] = 0;


		maze.Modelgroups[0].groupfaces[count].facenormal[0] = 0;
		maze.Modelgroups[0].groupfaces[count].facenormal[1] = -1;
		maze.Modelgroups[0].groupfaces[count].facenormal[2] = 0;

		maze.Modelgroups[0].groupfaces[count].triangle1[0][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][1] = -1;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][2] = j;

		maze.Modelgroups[0].groupfaces[count].triangle1[1][0] = i - 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][1] = -1;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][2] = j;

		maze.Modelgroups[0].groupfaces[count].triangle1[2][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][1] = -1;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][2] = j + 1;


		maze.Modelgroups[0].groupfaces[count].triangle2[0][0] = i - 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][1] = -1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][2] = j + 1;

		maze.Modelgroups[0].groupfaces[count].triangle2[1][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][1] = -1;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][2] = j + 1;

		maze.Modelgroups[0].groupfaces[count].triangle2[2][0] = i - 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][1] = -1;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][2] = j;

		count++;
	}

	for (int i = 1; i >= 0; i--)//wall 3   16faces
		// for(int i=4;i>=-3;i--)//wall 3   16faces
	for (int j = -4; j <= 3; j++)
	{
		maze.Modelgroups[0].groupfaces[count].ambient[0] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[1] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[2] = 0.2;

		maze.Modelgroups[0].groupfaces[count].diffuse[0] = 1;
		maze.Modelgroups[0].groupfaces[count].diffuse[1] = 0;
		maze.Modelgroups[0].groupfaces[count].diffuse[2] = 0;

		maze.Modelgroups[0].groupfaces[count].specular[0] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[1] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[2] = 0;

		maze.Modelgroups[0].groupfaces[count].facenormal[0] = 1;
		maze.Modelgroups[0].groupfaces[count].facenormal[1] = 0;
		maze.Modelgroups[0].groupfaces[count].facenormal[2] = 0;

		maze.Modelgroups[0].groupfaces[count].triangle1[0][0] = 4;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][1] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][2] = j;

		maze.Modelgroups[0].groupfaces[count].triangle1[1][0] = 4;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][1] = i - 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][2] = j;

		maze.Modelgroups[0].groupfaces[count].triangle1[2][0] = 4;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][1] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][2] = j + 1;


		maze.Modelgroups[0].groupfaces[count].triangle2[0][0] = 4;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][1] = i - 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][2] = j + 1;

		maze.Modelgroups[0].groupfaces[count].triangle2[1][0] = 4;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][1] = i;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][2] = j + 1;

		maze.Modelgroups[0].groupfaces[count].triangle2[2][0] = 4;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][1] = i - 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][2] = j;

		count++;
	}

	for (int i = -1; i <= 0; i++)//wall 4  16 faces
		// for(int i=-4;i<=3;i++)//wall 4  16 faces
	for (int j = -4; j <= 3; j++)
	{
		maze.Modelgroups[0].groupfaces[count].ambient[0] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[1] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[2] = 0.2;

		maze.Modelgroups[0].groupfaces[count].diffuse[0] = 1;
		maze.Modelgroups[0].groupfaces[count].diffuse[1] = 0;
		maze.Modelgroups[0].groupfaces[count].diffuse[2] = 0;

		maze.Modelgroups[0].groupfaces[count].specular[0] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[1] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[2] = 0;

		maze.Modelgroups[0].groupfaces[count].facenormal[0] = -1;
		maze.Modelgroups[0].groupfaces[count].facenormal[1] = 0;
		maze.Modelgroups[0].groupfaces[count].facenormal[2] = 0;

		maze.Modelgroups[0].groupfaces[count].triangle1[0][0] = -4;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][1] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][2] = j;

		maze.Modelgroups[0].groupfaces[count].triangle1[1][0] = -4;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][1] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][2] = j;

		maze.Modelgroups[0].groupfaces[count].triangle1[2][0] = -4;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][1] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][2] = j + 1;


		maze.Modelgroups[0].groupfaces[count].triangle2[0][0] = -4;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][1] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][2] = j + 1;

		maze.Modelgroups[0].groupfaces[count].triangle2[1][0] = -4;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][1] = i;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][2] = j + 1;

		maze.Modelgroups[0].groupfaces[count].triangle2[2][0] = -4;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][1] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][2] = j;

		count++;
	}


	for (int i = -4; i <= 3; i++)//wall 5  16 faces
	for (int j = 1; j >= 0; j--)
		// for(int j=4;j>=-3;j--)
	{
		maze.Modelgroups[0].groupfaces[count].ambient[0] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[1] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[2] = 0.2;

		maze.Modelgroups[0].groupfaces[count].diffuse[0] = 1;
		maze.Modelgroups[0].groupfaces[count].diffuse[1] = 0;
		maze.Modelgroups[0].groupfaces[count].diffuse[2] = 0;

		maze.Modelgroups[0].groupfaces[count].specular[0] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[1] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[2] = 0;

		maze.Modelgroups[0].groupfaces[count].facenormal[0] = 0;
		maze.Modelgroups[0].groupfaces[count].facenormal[1] = 0;
		maze.Modelgroups[0].groupfaces[count].facenormal[2] = 1;

		maze.Modelgroups[0].groupfaces[count].triangle1[0][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][1] = j;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][2] = 4;

		maze.Modelgroups[0].groupfaces[count].triangle1[1][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][1] = j;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][2] = 4;

		maze.Modelgroups[0].groupfaces[count].triangle1[2][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][1] = j - 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][2] = 4;


		maze.Modelgroups[0].groupfaces[count].triangle2[0][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][1] = j - 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][2] = 4;

		maze.Modelgroups[0].groupfaces[count].triangle2[1][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][1] = j - 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][2] = 4;

		maze.Modelgroups[0].groupfaces[count].triangle2[2][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][1] = j;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][2] = 4;

		count++;
	}


	for (int i = -4; i <= 3; i++)//wall 6  faces
	for (int j = -1; j <= 0; j++)
		// for(int j=-4;j<=3;j++)
	{

		maze.Modelgroups[0].groupfaces[count].ambient[0] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[1] = 0.2;
		maze.Modelgroups[0].groupfaces[count].ambient[2] = 0.2;

		maze.Modelgroups[0].groupfaces[count].diffuse[0] = 1;
		maze.Modelgroups[0].groupfaces[count].diffuse[1] = 0;
		maze.Modelgroups[0].groupfaces[count].diffuse[2] = 0;

		maze.Modelgroups[0].groupfaces[count].specular[0] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[1] = 0;
		maze.Modelgroups[0].groupfaces[count].specular[2] = 0;

		maze.Modelgroups[0].groupfaces[count].facenormal[0] = 0;
		maze.Modelgroups[0].groupfaces[count].facenormal[1] = 0;
		maze.Modelgroups[0].groupfaces[count].facenormal[2] = -1;

		maze.Modelgroups[0].groupfaces[count].triangle1[0][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][1] = j;
		maze.Modelgroups[0].groupfaces[count].triangle1[0][2] = -4;

		maze.Modelgroups[0].groupfaces[count].triangle1[1][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][1] = j;
		maze.Modelgroups[0].groupfaces[count].triangle1[1][2] = -4;

		maze.Modelgroups[0].groupfaces[count].triangle1[2][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][1] = j + 1;
		maze.Modelgroups[0].groupfaces[count].triangle1[2][2] = -4;


		maze.Modelgroups[0].groupfaces[count].triangle2[0][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][1] = j + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[0][2] = -4;

		maze.Modelgroups[0].groupfaces[count].triangle2[1][0] = i;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][1] = j + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[1][2] = -4;

		maze.Modelgroups[0].groupfaces[count].triangle2[2][0] = i + 1;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][1] = j;
		maze.Modelgroups[0].groupfaces[count].triangle2[2][2] = -4;

		count++;
	}
}
void copyWall(Group* newgr, Group* wall, GLfloat OX, GLfloat OY, GLfloat OZ, GLfloat VX1, GLfloat VX2, GLfloat VX3, GLfloat VY1, GLfloat VY2, GLfloat VY3, GLfloat VZ1, GLfloat VZ2, GLfloat VZ3)
{
	(*newgr).enable = (*wall).enable;

	(*newgr).orignalcoordinates[0] = OX;
	(*newgr).orignalcoordinates[1] = OY;
	(*newgr).orignalcoordinates[2] = OZ;
	(*newgr).vx[0] = VX1;
	(*newgr).vx[1] = VX2;
	(*newgr).vx[2] = VX3;

	(*newgr).vy[0] = VY1;
	(*newgr).vy[1] = VY2;
	(*newgr).vy[2] = VY3;


	(*newgr).vz[0] = VZ1;
	(*newgr).vz[1] = VZ2;
	(*newgr).vz[2] = VZ3;

	(*newgr).numoffaces = 192;
	(*newgr).numoffaces2 = 6;

	for (int i = 0; i <= 191; i++)
	{
		(*newgr).groupfaces[i].ambient[0] = (*wall).groupfaces[i].ambient[0];
		(*newgr).groupfaces[i].ambient[0] = (*wall).groupfaces[i].ambient[1];
		(*newgr).groupfaces[i].ambient[0] = (*wall).groupfaces[i].ambient[2];

		(*newgr).groupfaces[i].diffuse[0] = (*wall).groupfaces[i].diffuse[0];
		(*newgr).groupfaces[i].diffuse[1] = (*wall).groupfaces[i].diffuse[1];
		(*newgr).groupfaces[i].diffuse[2] = (*wall).groupfaces[i].diffuse[2];

		(*newgr).groupfaces[i].specular[0] = (*wall).groupfaces[i].specular[0];
		(*newgr).groupfaces[i].specular[1] = (*wall).groupfaces[i].specular[1];
		(*newgr).groupfaces[i].specular[2] = (*wall).groupfaces[i].specular[2];


		(*newgr).groupfaces[i].facenormal[0] = (*wall).groupfaces[i].facenormal[0];
		(*newgr).groupfaces[i].facenormal[1] = (*wall).groupfaces[i].facenormal[1];
		(*newgr).groupfaces[i].facenormal[2] = (*wall).groupfaces[i].facenormal[2];

		(*newgr).groupfaces[i].triangle1[0][0] = (*wall).groupfaces[i].triangle1[0][0];
		(*newgr).groupfaces[i].triangle1[0][1] = (*wall).groupfaces[i].triangle1[0][1];
		(*newgr).groupfaces[i].triangle1[0][2] = (*wall).groupfaces[i].triangle1[0][2];

		(*newgr).groupfaces[i].triangle1[1][0] = (*wall).groupfaces[i].triangle1[1][0];
		(*newgr).groupfaces[i].triangle1[1][1] = (*wall).groupfaces[i].triangle1[1][1];
		(*newgr).groupfaces[i].triangle1[1][2] = (*wall).groupfaces[i].triangle1[1][2];


		(*newgr).groupfaces[i].triangle1[2][0] = (*wall).groupfaces[i].triangle1[2][0];
		(*newgr).groupfaces[i].triangle1[2][1] = (*wall).groupfaces[i].triangle1[2][1];
		(*newgr).groupfaces[i].triangle1[2][2] = (*wall).groupfaces[i].triangle1[2][2];

		(*newgr).groupfaces[i].triangle2[0][0] = (*wall).groupfaces[i].triangle2[0][0];
		(*newgr).groupfaces[i].triangle2[0][1] = (*wall).groupfaces[i].triangle2[0][1];
		(*newgr).groupfaces[i].triangle2[0][2] = (*wall).groupfaces[i].triangle2[0][2];

		(*newgr).groupfaces[i].triangle2[1][0] = (*wall).groupfaces[i].triangle2[1][0];
		(*newgr).groupfaces[i].triangle2[1][1] = (*wall).groupfaces[i].triangle2[1][1];
		(*newgr).groupfaces[i].triangle2[1][2] = (*wall).groupfaces[i].triangle2[1][2];


		(*newgr).groupfaces[i].triangle2[2][0] = (*wall).groupfaces[i].triangle2[2][0];
		(*newgr).groupfaces[i].triangle2[2][1] = (*wall).groupfaces[i].triangle2[2][1];
		(*newgr).groupfaces[i].triangle2[2][2] = (*wall).groupfaces[i].triangle2[2][2];


	}

	for (int i = 0; i <= 5; i++)
	{
		(*newgr).groupfaces2[i].ambient[0] = (*wall).groupfaces2[i].ambient[0];
		(*newgr).groupfaces2[i].ambient[0] = (*wall).groupfaces2[i].ambient[1];
		(*newgr).groupfaces2[i].ambient[0] = (*wall).groupfaces2[i].ambient[2];

		(*newgr).groupfaces2[i].diffuse[0] = (*wall).groupfaces2[i].diffuse[0];
		(*newgr).groupfaces2[i].diffuse[1] = (*wall).groupfaces2[i].diffuse[1];
		(*newgr).groupfaces2[i].diffuse[2] = (*wall).groupfaces2[i].diffuse[2];

		(*newgr).groupfaces2[i].specular[0] = (*wall).groupfaces2[i].specular[0];
		(*newgr).groupfaces2[i].specular[1] = (*wall).groupfaces2[i].specular[1];
		(*newgr).groupfaces2[i].specular[2] = (*wall).groupfaces2[i].specular[2];


		(*newgr).groupfaces2[i].facenormal[0] = (*wall).groupfaces2[i].facenormal[0];
		(*newgr).groupfaces2[i].facenormal[1] = (*wall).groupfaces2[i].facenormal[1];
		(*newgr).groupfaces2[i].facenormal[2] = (*wall).groupfaces2[i].facenormal[2];

		(*newgr).groupfaces2[i].triangle1[0][0] = (*wall).groupfaces2[i].triangle1[0][0];
		(*newgr).groupfaces2[i].triangle1[0][1] = (*wall).groupfaces2[i].triangle1[0][1];
		(*newgr).groupfaces2[i].triangle1[0][2] = (*wall).groupfaces2[i].triangle1[0][2];

		(*newgr).groupfaces2[i].triangle1[1][0] = (*wall).groupfaces2[i].triangle1[1][0];
		(*newgr).groupfaces2[i].triangle1[1][1] = (*wall).groupfaces2[i].triangle1[1][1];
		(*newgr).groupfaces2[i].triangle1[1][2] = (*wall).groupfaces2[i].triangle1[1][2];


		(*newgr).groupfaces2[i].triangle1[2][0] = (*wall).groupfaces2[i].triangle1[2][0];
		(*newgr).groupfaces2[i].triangle1[2][1] = (*wall).groupfaces2[i].triangle1[2][1];
		(*newgr).groupfaces2[i].triangle1[2][2] = (*wall).groupfaces2[i].triangle1[2][2];

		(*newgr).groupfaces2[i].triangle2[0][0] = (*wall).groupfaces2[i].triangle2[0][0];
		(*newgr).groupfaces2[i].triangle2[0][1] = (*wall).groupfaces2[i].triangle2[0][1];
		(*newgr).groupfaces2[i].triangle2[0][2] = (*wall).groupfaces2[i].triangle2[0][2];

		(*newgr).groupfaces2[i].triangle2[1][0] = (*wall).groupfaces2[i].triangle2[1][0];
		(*newgr).groupfaces2[i].triangle2[1][1] = (*wall).groupfaces2[i].triangle2[1][1];
		(*newgr).groupfaces2[i].triangle2[1][2] = (*wall).groupfaces2[i].triangle2[1][2];


		(*newgr).groupfaces2[i].triangle2[2][0] = (*wall).groupfaces2[i].triangle2[2][0];
		(*newgr).groupfaces2[i].triangle2[2][1] = (*wall).groupfaces2[i].triangle2[2][1];
		(*newgr).groupfaces2[i].triangle2[2][2] = (*wall).groupfaces2[i].triangle2[2][2];


	}

}
void mazeinit(){


	maze.numofgroups = 14;//number of groups

	creatWall1();
	scalegroup(&maze.Modelgroups[0], 10, 10, 10);

	copyWall(&maze.Modelgroups[1], &maze.Modelgroups[0], -260, 160, 0, 0, 1, 0, -1, 0, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[1], 4, 2, 1);

	copyWall(&maze.Modelgroups[2], &maze.Modelgroups[0], -260, -160, 0, 0, 1, 0, -1, 0, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[2], 4, 2, 1);

	copyWall(&maze.Modelgroups[3], &maze.Modelgroups[0], 260, 160, 0, 0, 1, 0, -1, 0, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[3], 4, 2, 1);

	copyWall(&maze.Modelgroups[4], &maze.Modelgroups[0], 260, -160, 0, 0, 1, 0, -1, 0, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[4], 4, 2, 1);

	copyWall(&maze.Modelgroups[5], &maze.Modelgroups[0], -160, 160, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[5], 2, 2, 1);

	copyWall(&maze.Modelgroups[6], &maze.Modelgroups[0], 160, 160, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[6], 2, 2, 1);

	copyWall(&maze.Modelgroups[7], &maze.Modelgroups[0], -160, -160, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[7], 2, 2, 1);

	copyWall(&maze.Modelgroups[8], &maze.Modelgroups[0], 160, -160, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[8], 2, 2, 1);

	copyWall(&maze.Modelgroups[9], &maze.Modelgroups[0], 90, 80, 0, 0, 1, 0, -1, 0, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[9], 1.5, 1, 1);

	copyWall(&maze.Modelgroups[10], &maze.Modelgroups[0], -80, 340, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[10], 5, 2, 1);

	copyWall(&maze.Modelgroups[11], &maze.Modelgroups[0], 80, -340, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[11], 5, 2, 1);

	//door1
	float theta = 0;
	copyWall(&maze.Modelgroups[12], &maze.Modelgroups[0], 0, -160, 0, cos(theta), sin(theta), 0, -sin(theta), cos(theta), 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[12], 2, 1, 1);
	//door2
	float theta1 = 0;
	copyWall(&maze.Modelgroups[13], &maze.Modelgroups[0], 0, 160, 0, cos(theta1), sin(theta1), 0, -sin(theta1), cos(theta1), 0, 0, 0, 1);
	scalegroup(&maze.Modelgroups[13], 2, 1, 1);

	/*copyWall(&maze.Modelgroups[2],&maze.Modelgroups[0],8,1,0,0,1,0,1,0,0,0,0,1);

	copyWall(&maze.Modelgroups[3],&maze.Modelgroups[0],5,4,0,1,0,0,0,1,0,0,0,1);
	scalegroup(&maze.Modelgroups[3],0.5,1,1);
	copyWall(&maze.Modelgroups[4],&maze.Modelgroups[0],-5,4,0,1,0,0,0,1,0,0,0,1);
	scalegroup(&maze.Modelgroups[4],0.5,1,1);

	copyWall(&maze.Modelgroups[5],&maze.Modelgroups[0],0,8,0,1,0,0,0,1,0,0,0,1);
	scalegroup(&maze.Modelgroups[5],1.25,1,1);

	copyWall(&maze.Modelgroups[6],&maze.Modelgroups[0],-8,9,0,0,1,0,1,0,0,0,0,1);

	copyWall(&maze.Modelgroups[7],&maze.Modelgroups[0],8,9,0,0,1,0,1,0,0,0,0,1);

	copyWall(&maze.Modelgroups[8],&maze.Modelgroups[0],0,11,0,0,1,0,1,0,0,0,0,1);
	scalegroup(&maze.Modelgroups[8],0.5,1,1);

	copyWall(&maze.Modelgroups[9],&maze.Modelgroups[0],-2,14,0,1,0,0,0,1,0,0,0,1);
	scalegroup(&maze.Modelgroups[9],1.75,1,1);

	copyWall(&maze.Modelgroups[10],&maze.Modelgroups[0],2,-4,0,1,0,0,0,1,0,0,0,1);
	scalegroup(&maze.Modelgroups[10],1.75,1,1);
	//scalegroup(&maze.Modelgroups[0],2,1,1);*/

	scalegroup(&maze.Modelgroups[0], 2.5, 2, 1);

	for (int i = 0; i <= maze.numofgroups - 1; i++)
	{
		obj_to_world(&maze.Modelgroups[i]);
	}


}
int checkviewpoint(float x, float y)
{
	if (x >= -240 && x <= 240 && y >= -320 && y <= -180)
		return 1;
	if (x >= -80 && x <= 80 && y >= -180 && y <= -140)
		return 1;
	if (x >= -240 && x <= 240 && y >= -140 && y <= -20)
		return 1;
	if (x >= -240 && x <= -100 && y >= -20 && y <= 20)
		return 1;
	if (x >= 100 && x <= 240 && y >= -20 && y <= 20)
		return 1;
	if (x >= -240 && x <= 240 && y >= 20 && y <= 140)
		return 1;
	if (x >= -80 && x <= 80 && y >= 140 && y <= 230)
		return 1;
	if (x >= -230 && x <= 240 && y >= 180 && y <= 320)
		return 1;
	if (x >= 120 && x <= 280 && y >= 320 && y <= 480)
		return 1;
	return 0;
}


typedef struct _GLMmaterial
{
	char* name;                   /* name of material */
	GLfloat diffuse[4];           /* diffuse component */
	GLfloat ambient[4];           /* ambient component */
	GLfloat specular[4];          /* specular component */
	GLfloat emmissive[4];         /* emmissive component */
	GLfloat shininess;            /* specular exponent */
} GLMmaterial;
typedef struct
{
	float r;
	float g;
	float b;
} RGBcolor;

//\B5\E3\BB\F2\CF\F2\C1\BF
typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} MyPoint;

typedef struct
{
	MyPoint v0;
	MyPoint v1;
	MyPoint v2;
}Triangle;

typedef struct{
	MyPoint p;
	MyPoint n;
}ClipFace;

#define INF 9999
#define epsilon	0.0001
#define epsilon2	0.01
#define Nmatrix 4//\BE\D8\D5\F3\B5Ľ\D7\CA\FD
#define Scr_Wid 512
#define Scr_Len 512
#define bPer -4.0
#define tPer 6.0
#define lPer -5.0
#define rPer 5.0
#define nPer -5.0
#define fPer -1000.0
#define PI 3.1415926
#define Horizon 2.5
float door12angle = 0;
float door13angle = 0;

MyPoint		viewDir = { 0, 0, -1 };
MyPoint		viewPos = { -200, 0, 400 };
MyPoint		viewUp = { 0, 1, 0 };
MyPoint		myLight = { -0.5, -0.5, -1 };
RGBcolor	GLPixelData[Scr_Wid][Scr_Len];
GLdouble	zBufferPixel[Scr_Wid][Scr_Len];
int groupbuffer[Scr_Wid][Scr_Len];
GLMmaterial	testMat = { "test", { 0.7, 0.1, 0.1, 0 }, { 0.2, 0.1, 0.0, 0 }, { 0.7, 0.1, 0.1, 0 }, { 0.7, 0.1, 0.1, 0 }, 10 };

GLMmaterial	testMat2 = { "test", { 0.1, 0.7, 0.1, 0 }, { 0.1, 0.2, 0.0, 0 }, { 0.1, 0.7, 0.1, 0 }, { 0.1, 0.7, 0.1, 0 }, 10 };
/*
GLfloat		v0[3] = { -30, 10, -30 };
GLfloat		v1[3] = { 30, 10, -30 };
GLfloat		v2[3] = { 30, 10, -20 };
GLfloat		v3[3] = { -30, 10, -20 };
GLfloat		v4[3] = { -30, 0, -30 };
GLfloat		v5[3] = { 30, 0, -30 };
GLfloat		v6[3] = { 30, 0, -20 };
GLfloat		v7[3] = { -30, 0, -20 };
*/
MyPoint		roAxisX = { 1, 0, 0 };
MyPoint		roAxisY = { 0, 1, 0 };
GLfloat		roThetaX = 0;
GLfloat		roThetaY = 0;

//assign a to b
void assignPoint(MyPoint a, MyPoint b)
{
	b.x = a.x;
	b.y = a.y;
	b.z = a.z;
}

//rotate
MyPoint rotatePoint3D(float theta, float nx, float ny, float nz, MyPoint sp)
{
	float len = sqrtf(nx * nx + ny * ny + nz * nz);		//to unit
	nx /= len;
	ny /= len;
	nz /= len;
	float c = cosf(theta);
	float s = sinf(theta);
	float x = sp.x * (c + nx * nx * (1 - c)) + sp.y * (nx * ny * (1 - c) - nz * s) + sp.z * (nx * nz * (1 - c) + ny * s);		//transform by matrix
	float y = sp.x * (nx * ny * (1 - c) + nz * s) + sp.y * (ny * ny * (1 - c) + c) + sp.z * (ny * nz * (1 - c) - nx * s);
	float z = sp.x * (nx * nz * (1 - c) - ny * s) + sp.y * (ny * nz * (1 - c) + nx * s) + sp.z * (nz * nz * (1 - c) + c);
	MyPoint newsp = { x, y, z };
	return newsp;
}

//matrix multi
void matMulti(float a[][Nmatrix], float b[][Nmatrix], float c[][Nmatrix])
{
	int i, j, k;

	for (i = 0; i<Nmatrix; i++)
	{
		for (j = 0; j<Nmatrix; j++)
		{
			c[i][j] = 0;
		}
	}

	for (k = 0; k < Nmatrix; k++) {
		for (i = 0; i < Nmatrix; i++){
			for (j = 0; j < Nmatrix; j++) {
				c[i][k] += a[i][j] * b[j][k];
			}
		}
	}
}

MyPoint		reverseV(MyPoint a)
{
	MyPoint b = { -a.x, -a.y, -a.z };
	return b;
}
//draw line \BB\AD\CF\DF
void bresenhamLine(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	// Bresenham's line algorithm
	GLboolean steep = (fabs(y2 - y1) > fabs(x2 - x1));
	GLdouble temp = 0;
	if (steep)
	{
		temp = x1;
		x1 = y1;
		y1 = temp;
		temp = x2;
		x2 = y2;
		y2 = temp;
	}

	if (x1 > x2)
	{
		temp = x2;
		x2 = x1;
		x1 = temp;
		temp = y2;
		y2 = y1;
		y1 = temp;
	}

	GLdouble dx = x2 - x1;
	GLdouble dy = fabs(y2 - y1);

	GLdouble error = dx / 2.0f;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	int maxX = (int)x2;

	for (int x = (int)x1; x<maxX; x++)
	{
		if (steep)
		{
			if (x >= 0 && y >= 0 && x <= 511 && y <= 511){
				GLPixelData[x][y].r = 0.0;
				GLPixelData[x][y].g = 0.0;
				GLPixelData[x][y].b = 0.0;

			}
		}
		else
		{
			if (x >= 0 && y >= 0 && x <= 511 && y <= 511){
				GLPixelData[y][x].r = 0.0;
				GLPixelData[y][x].g = 0.0;
				GLPixelData[y][x].b = 0.0;
			}
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

//Tools

MyPoint pointMinus(MyPoint a, MyPoint b)
{
	MyPoint c = { a.x - b.x, a.y - b.y, a.z - b.z };
	return c;
}

GLfloat dotProduct(MyPoint a, MyPoint b)
{
	GLfloat c = (a.x)*(b.x) + (a.y) * (b.y) + (a.z) * (b.z);
	return c;
}

MyPoint toOneV(MyPoint a)
{
	float x = dotProduct(a, a);
	float m = sqrtf(x);
	MyPoint b = { a.x / m, a.y / m, a.z / m };
	return b;
}

MyPoint crossProduct(MyPoint a, MyPoint b)
{
	MyPoint c = { a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y }; //Y1Z2-Y2Z1\A3\ACZ1X2-Z2X1\A3\ACX1Y2-X2Y1
	return c;
}

MyPoint
biSector(MyPoint a, MyPoint b)
{
	MyPoint c = { a.x + toOneV(b).x, a.y + toOneV(b).y, a.z + toOneV(b).z };
	return c;
}

GLfloat getCos(MyPoint a, MyPoint b)
{
	GLfloat cos = dotProduct(a, b) / (sqrtf(a.x*a.x + a.y*a.y + a.z*a.z) * sqrtf(b.x*b.x + b.y*b.y + b.z*b.z));
	return cos;
}

GLfloat getSin(MyPoint a, MyPoint b)
{
	GLfloat cos = getCos(a, b);
	GLfloat sin = sqrtf(1 - cos*cos);
	return sin;
}

MyPoint getNorTri(MyPoint a, MyPoint b, MyPoint c)
{
	MyPoint d = crossProduct(pointMinus(b, a), pointMinus(c, a)); //fanle?
	MyPoint e = toOneV(d);
	return e;
}

//compute rgb color for triangle
RGBcolor getColorTri(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLMmaterial cur_material, MyPoint myLight, MyPoint myView)
{
	MyPoint edge1 = { -(x1 - x2), -(y1 - y2), -(z1 - z2) };
	MyPoint edge2 = { x3 - x2, y3 - y2, z3 - z2 };
	//MyPoint light = { 0.0, 0.0, 1.0 };		//{ (float)(myLight[0]), (float)(myLight[1]), (float)(myLight[2]) };	//\B2\BB\C4ܶ\AF
	//MyPoint view = { 0.0, 0.0, 1.0 };		//{ (float)(myView[0]), (float)(myView[1]), (float)(myView[2]) }; //\B2\BB\C4ܶ\AF
	GLfloat cos1 = dotProduct(toOneV(crossProduct(edge1, edge2)), myLight);
	GLfloat cos2 = dotProduct(toOneV(crossProduct(edge1, edge2)), toOneV(biSector(myLight, myView)));
	if (cos1 < 0)
	{
		cos1 = 0;
	}
	if (cos2 < 0)
	{
		cos2 = 0;
	}
	GLfloat r = cur_material.ambient[0] + cur_material.diffuse[0] * cos1 + cur_material.specular[0] * pow(cos2, cur_material.shininess);
	GLfloat g = cur_material.ambient[1] + cur_material.diffuse[1] * cos1 + cur_material.specular[1] * pow(cos2, cur_material.shininess);
	GLfloat b = cur_material.ambient[2] + cur_material.diffuse[2] * cos1 + cur_material.specular[2] * pow(cos2, cur_material.shininess);
	// to make it darker (higher value goes down more)
	//r *= geDarkFactor(r);
	//g *= geDarkFactor(g);
	//b *= geDarkFactor(b);
	GLfloat max = r > g ? r : g;
	max = max > b ? max : b;
	if (max > 1)
	{
		r = r / max;
		g = g / max;
		b = b / max;
	}
	RGBcolor tricolor = { r, g, b };
	return tricolor;
}

GLdouble
getAreaTri(GLdouble ax, GLdouble ay, GLdouble bx, GLdouble by, GLdouble cx, GLdouble cy)
{
	GLdouble mx = cx - ax, my = cy - ay, nx = bx - ax, ny = by - ay;
	GLdouble Lm = sqrt(mx*mx + my*my), Ln = sqrt(nx*nx + ny*ny), cosA = (mx*nx + my*ny) / Lm / Ln;
	GLdouble sinA = sqrt(1 - cosA*cosA);
	GLdouble S_tri = 0.5*Lm*Ln*sinA;
	if (S_tri >= 0)
		return S_tri;
	else
		return (-1 * S_tri);
}

GLdouble
getZBuffer(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2, GLdouble x3, GLdouble y3, GLdouble z3, GLdouble xcur, GLdouble ycur)
{
	GLdouble S = getAreaTri(x2, y2, x3, y3, x1, y1);
	GLdouble u = getAreaTri(x2, y2, x3, y3, xcur, ycur) / S;
	GLdouble v = getAreaTri(x1, y1, x3, y3, xcur, ycur) / S;
	GLdouble w = 1 - u - v;
	GLdouble z = u*z1 + v*z2 + w*z3;
	return z;
}

// scanline triangle \CC\EE\B3\E4\C8\FD\BD\C7\D0\CE
void
scanLineTriNew(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2, GLdouble x3, GLdouble y3, GLdouble z3, RGBcolor color,int j)
{
	GLuint xmax = (int)((x1 > x2 ? x1 : x2) > x3 ? (x1 > x2 ? x1 : x2) : x3);
	xmax++;
	//xmax = 512 < xmax ? 512 : xmax;
	GLuint xmin = (int)((x1 < x2 ? x1 : x2) < x3 ? (x1 < x2 ? x1 : x2) : x3);
	//xmin = 0 > xmin ? 0 : xmin;
	GLuint ymax = (int)((y1 > y2 ? y1 : y2) > y3 ? (y1 > y2 ? y1 : y2) : y3);
	ymax++;
	//ymax = 512 < ymax ? 512 : ymax;
	GLuint ymin = (int)((y1 < y2 ? y1 : y2) < y3 ? (y1 < y2 ? y1 : y2) : y3);
	//ymin = 0 > ymin ? 0 : ymin;
	GLuint xcur, ycur;
	GLdouble S = getAreaTri(x2, y2, x3, y3, x1, y1);
	GLdouble u, v, w, sum, z;
	for (xcur = xmin; xcur <= xmax; xcur++)
	for (ycur = ymin; ycur <= ymax; ycur++)
	{
		u = getAreaTri(x2, y2, x3, y3, xcur, ycur);
		v = getAreaTri(x1, y1, x3, y3, xcur, ycur);
		w = getAreaTri(x1, y1, x2, y2, xcur, ycur);
		sum = u + v + w;
		if (abs(S - sum) < epsilon)
		{
			z = getZBuffer(x1, y1, z1, x2, y2, z2, x3, y3, z3, xcur, ycur);
			if ((z < zBufferPixel[ycur][xcur]) && (z < 1.0) && (z > -1.0))
			{
				if (xcur >= 0 && ycur >= 0 && xcur <= 511 && ycur <= 511){
					GLPixelData[ycur][xcur].r = color.r;
					GLPixelData[ycur][xcur].g = color.g;
					GLPixelData[ycur][xcur].b = color.b;
					groupbuffer[ycur][xcur]=j;
					zBufferPixel[ycur][xcur] = z;
				}
			}
		}
	}
}

void
viewTrans(float x, float y, float z, float *xt, float *yt, float *zt, MyPoint viewGaz)
{
	if (fabs(z - viewPos.z) < 1)
	{
		*xt = -1;
		*yt = -1;
		*zt = 10;
		return;
	}
	float Mvp[Nmatrix][Nmatrix] = { { Scr_Len / 2, 0, 0, (Scr_Len / 2) }, { 0, Scr_Wid / 2, 0, (Scr_Wid / 2) }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	float Mper[Nmatrix][Nmatrix] = { { (2 * nPer / (rPer - lPer)), 0, ((lPer + rPer) / (lPer - rPer)), 0 }, { 0, (2 * nPer / (tPer - bPer)), ((bPer + tPer) / (bPer - tPer)), 0 }, { 0, 0, ((fPer + nPer) / (nPer - fPer)), (2 * fPer*nPer / (fPer - nPer)) }, { 0, 0, 1, 0 } };
	MyPoint w = reverseV(toOneV(viewGaz));
	MyPoint u = toOneV(crossProduct(viewUp, w));
	MyPoint v = crossProduct(w, u);
	float Mcam1[Nmatrix][Nmatrix] = { { u.x, u.y, u.z, 0 }, { v.x, v.y, v.z, 0 }, { w.x, w.y, w.z, 0 }, { 0, 0, 0, 1 } };
	float Mcam2[Nmatrix][Nmatrix] = { { 1, 0, 0, -viewPos.x }, { 0, 1, 0, -viewPos.y }, { 0, 0, 1, -viewPos.z }, { 0, 0, 0, 1 } };
	float Mvpper[Nmatrix][Nmatrix];
	float Mcam[Nmatrix][Nmatrix];
	float M[Nmatrix][Nmatrix];
	matMulti(Mvp, Mper, Mvpper);
	matMulti(Mcam1, Mcam2, Mcam);
	matMulti(Mvpper, Mcam, M);
	*xt = x*M[0][0] + y*M[0][1] + z*M[0][2] + M[0][3];
	*yt = x*M[1][0] + y*M[1][1] + z*M[1][2] + M[1][3];
	*zt = x*M[2][0] + y*M[2][1] + z*M[2][2] + M[2][3];
	float homoW = x*M[3][0] + y*M[3][1] + z*M[3][2] + M[3][3];
	*xt = *xt / homoW;
	*yt = *yt / homoW;
	*zt = -(*zt / homoW);
	return;
}
// Line Face Intersection
int FaceInter(MyPoint a, MyPoint b, ClipFace f, MyPoint* c)
{
	float q = (a.x - b.x)*f.n.x + (a.y - b.y)*f.n.y + (a.z - b.z)*f.n.z;
	if (fabs(q) < epsilon)
	{
		return 0;
	}
	float p = (f.p.x - b.x)*f.n.x + (f.p.y - b.y)*f.n.y + (f.p.z - b.z)*f.n.z;
	float t = p / q;
	if ( t < 0 || t > 1)
	{
		return 0;
	}
	(*c).x = b.x + t*(a.x - b.x);
	(*c).y = b.y + t*(a.y - b.y);
	(*c).z = b.z + t*(a.z - b.z);
	return 1;
}

//return 1 means null triangle
int checkTri(Triangle T0)
{
	if (T0.v0.x == 0 && T0.v0.y == 0 && T0.v0.z == 0 && T0.v1.x == 0 && T0.v1.y == 0 && T0.v1.z == 0 && T0.v2.x == 0 && T0.v2.y == 0 && T0.v2.z == 0)
	{
		return 1;
	}
	return 0;
}
/*int clippingNew(Triangle T0, Triangle* T1, Triangle *T2, ClipFace f)
{
	float cos0 = dotProduct(f.n, pointMinus(T0.v0, f.p));
	float cos1 = dotProduct(f.n, pointMinus(T0.v1, f.p));
	float cos2 = dotProduct(f.n, pointMinus(T0.v2, f.p));

	MyPoint a; //0-1
	MyPoint b; //1-2 FaceInter(T0.v1, T0.v2, f, &b)
	MyPoint c; //2-0 FaceInter(T0.v2, T0.v0, f, &c)
	if (FaceInter(T0.v0, T0.v1, f, &a))
	{
		if (FaceInter(T0.v1, T0.v2, f, &b)) //v0 v2 on one side
		{
			if (cos1 > 0)
			{
				(*T1).v0 = { a.x, a.y, a.z };
				(*T1).v1 = { T0.v1.x, T0.v1.y, T0.v1.z };
				(*T1).v2 = { b.x, b.y, b.z };
				return 1;
			}
			else
			{
				(*T1).v0 = { T0.v0.x, T0.v0.y, T0.v0.z };
				(*T1).v1 = { a.x, a.y, a.z };
				(*T1).v2 = { b.x, b.y, b.z };
				(*T2).v0 = { T0.v0.x, T0.v0.y, T0.v0.z };
				(*T2).v1 = { b.x, b.y, b.z };
				(*T2).v2 = { T0.v2.x, T0.v2.y, T0.v2.z };
				return 2;
			}
		}
		else	//v2 v1 on one side
		{
			FaceInter(T0.v2, T0.v0, f, &c);
			if (cos0 > 0)
			{
				(*T1).v0 = { T0.v1.x, T0.v1.y, T0.v1.z };
				(*T1).v1 = { a.x, a.y, a.z };
				(*T1).v2 = { c.x, c.y, c.z };
				return 1;
			}
			else
			{
				(*T1).v0 = { a.x, a.y, a.z };
				(*T1).v1 = { T0.v1.x, T0.v1.y, T0.v1.z };
				(*T1).v2 = { T0.v2.x, T0.v2.y, T0.v2.z };
				(*T2).v0 = { a.x, a.y, a.z };
				(*T2).v1 = { T0.v2.x, T0.v2.y, T0.v2.z };
				(*T2).v2 = { c.x, c.y, c.z };
				return 2;
			}
		}
	}
	else	//v0 v1 on one side
	{
		FaceInter(T0.v1, T0.v2, f, &b);
		FaceInter(T0.v2, T0.v0, f, &c);
		if (cos2 > 0)
		{
			(*T1).v0 = { c.x, c.y, c.z };
			(*T1).v1 = { b.x, b.y, b.z };
			(*T1).v2 = { T0.v2.x, T0.v2.y, T0.v2.z };
			return 1;
		}
		else
		{
			(*T1).v0 = { T0.v0.x, T0.v0.y, T0.v0.z };
			(*T1).v1 = { T0.v1.x, T0.v1.y, T0.v1.z };
			(*T1).v2 = { b.x, b.y, b.z };
			(*T2).v0 = { T0.v0.x, T0.v0.y, T0.v0.z };
			(*T2).v1 = { b.x, b.y, b.z };
			(*T2).v2 = { c.x, c.y, c.z };
			return 2;
		}
	}
}*/
//Split one triangle into two(maybe one) using face f
/*int clipping(Triangle T0, Triangle* T1, Triangle *T2, ClipFace f)
{
	
	(*T1).v0 = { 0, 0, 0 };
	(*T1).v1 = { 0, 0, 0 };
	(*T1).v2 = { 0, 0, 0 };
	(*T2).v0 = { 0, 0, 0 };
	(*T2).v1 = { 0, 0, 0 };
	(*T2).v2 = { 0, 0, 0 };
	
	if (checkTri(T0))
	{
		return 0;
	}
	float cos0 = dotProduct(f.n, pointMinus(T0.v0, f.p));
	float cos1 = dotProduct(f.n, pointMinus(T0.v1, f.p));
	float cos2 = dotProduct(f.n, pointMinus(T0.v2, f.p));
	if (((cos0 < 0) && (cos1 < 0) && (cos2 < 0)) || ((cos0 > 0) && (cos1 > 0) && (cos2 > 0)))
	{
		return 0;
	}
	MyPoint a; //0-1
	MyPoint b; //1-2 FaceInter(T0.v1, T0.v2, f, &b)
	MyPoint c; //2-0 FaceInter(T0.v2, T0.v0, f, &c)
	if (FaceInter(T0.v0, T0.v1, f, &a))
	{
		if (FaceInter(T0.v1, T0.v2, f, &b)) //v0 v2 on one side
		{
			if (cos1 > 0)
			{
				(*T1).v0 = { a.x, a.y, a.z };
				(*T1).v1 = { T0.v1.x, T0.v1.y, T0.v1.z };
				(*T1).v2 = { b.x, b.y, b.z };
				return 1;
			}
			else
			{
				(*T1).v0 = { T0.v0.x, T0.v0.y, T0.v0.z };
				(*T1).v1 = { a.x, a.y, a.z };
				(*T1).v2 = { b.x, b.y, b.z };
				(*T2).v0 = { T0.v0.x, T0.v0.y, T0.v0.z };
				(*T2).v1 = { b.x, b.y, b.z };
				(*T2).v2 = { T0.v2.x, T0.v2.y, T0.v2.z };
				return 2;
			}
		}
		else	//v2 v1 on one side
		{
			FaceInter(T0.v2, T0.v0, f, &c);
			if (cos0 > 0)
			{
				(*T1).v0 = { T0.v1.x, T0.v1.y, T0.v1.z };
				(*T1).v1 = { a.x, a.y, a.z };
				(*T1).v2 = { c.x, c.y, c.z };
				return 1;
			}
			else
			{
				(*T1).v0 = { a.x, a.y, a.z }; 
				(*T1).v1 = { T0.v1.x, T0.v1.y, T0.v1.z };
				(*T1).v2 = { T0.v2.x, T0.v2.y, T0.v2.z };
				(*T2).v0 = { a.x, a.y, a.z };
				(*T2).v1 = { T0.v2.x, T0.v2.y, T0.v2.z };
				(*T2).v2 = { c.x, c.y, c.z };
				return 2;
			}
		}
	}
	else	//v0 v1 on one side
	{
		FaceInter(T0.v1, T0.v2, f, &b);
		FaceInter(T0.v2, T0.v0, f, &c);
		if (cos2 > 0)
		{
			(*T1).v0 = { c.x, c.y, c.z };
			(*T1).v1 = { b.x, b.y, b.z };
			(*T1).v2 = { T0.v2.x, T0.v2.y, T0.v2.z };
			return 1;
		}
		else
		{
			(*T1).v0 = { T0.v0.x, T0.v0.y, T0.v0.z };
			(*T1).v1 = { T0.v1.x, T0.v1.y, T0.v1.z };
			(*T1).v2 = { b.x, b.y, b.z };
			(*T2).v0 = { T0.v0.x, T0.v0.y, T0.v0.z };
			(*T2).v1 = { b.x, b.y, b.z };
			(*T2).v2 = { c.x, c.y, c.z };
			return 2;
		}
	}
}*/
//return 0 means no intersection
int clippingTest(Triangle T0, ClipFace f)
{
	float cos0 = dotProduct(f.n, pointMinus(T0.v0, f.p));
	float cos1 = dotProduct(f.n, pointMinus(T0.v1, f.p));
	float cos2 = dotProduct(f.n, pointMinus(T0.v2, f.p));
	if (((cos0 < 0) && (cos1 < 0) && (cos2 < 0)) || ((cos0 > 0) && (cos1 > 0) && (cos2 > 0)))
	{
		return 0;
	}
	return 1;
}
/*
void DoTri(MyPoint vG, GLfloat *v0, GLfloat *v1, GLfloat *v2, RGBcolor cur_color, ClipFace fn, ClipFace ff, ClipFace fl, ClipFace fr, ClipFace ft, ClipFace fb )
{
	GLfloat scrn_v0[3];
	GLfloat scrn_v1[3];
	GLfloat scrn_v2[3];
	Triangle T0; // ???
	T0.v0.x = v0[0];
	T0.v0.y = v0[1];
	T0.v0.z = v0[2];
	T0.v1.x = v1[0];
	T0.v1.y = v1[1];
	T0.v1.z = v1[2];
	T0.v2.x = v2[0];
	T0.v2.y = v2[1];
	T0.v2.z = v2[2];
	int testN = clippingTest(T0, fn);
	int testF = clippingTest(T0, ff);
	int testL = clippingTest(T0, fl);
	int testR = clippingTest(T0, fr);
	int testT = clippingTest(T0, ft);
	int testB = clippingTest(T0, fb);
	if (!(testN || testF || testL || testR || testT || testB))
	{	
		viewTrans(v0[0], v0[1], v0[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], vG);
		viewTrans(v1[0], v1[1], v1[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], vG);
		viewTrans(v2[0], v2[1], v2[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], vG);
		scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
		return;
	}
	//Triangle TS[128];
	Triangle* TS = (Triangle *)malloc(sizeof(Triangle)* 128);
	for (int i1 = 0; i1 <= 127; i1++)
	{
		TS[i1].v0.x = 0;
		TS[i1].v0.y = 0;
		TS[i1].v0.z = 0;

		TS[i1].v1.x = 0;
		TS[i1].v1.y = 0;
		TS[i1].v1.z = 0;

		TS[i1].v2.x = 0;
		TS[i1].v2.y = 0;
		TS[i1].v2.z = 0;
	}
	//\D7\F664\B4\CEclipping
	clipping(T0, &TS[1], &TS[2],fn);
	if (!checkTri(TS[1]))
	{
		clipping(TS[1], &TS[3], &TS[4], ff);
	}
	if (!checkTri(TS[2]))
	{
		clipping(TS[2], &TS[5], &TS[6], ff);
	}
	for (int i = 3; i <= 6; i++)
	{
		if (!checkTri(TS[i]))
		{
			clipping(TS[i], &TS[2 * i + 1], &TS[2 * i + 2], fl);
		}
	}

	for (int i = 7; i <= 14; i++)
	{
		if (!checkTri(TS[i]))
		{
			clipping(TS[i], &TS[2 * i + 1], &TS[2 * i + 2], fr);
		}
	}

	for (int i = 15; i <= 30; i++)
	{
		if (!checkTri(TS[i]))
		{
			clipping(TS[i], &TS[2 * i + 1], &TS[2 * i + 2], ft);
		}
	}

	for (int i = 31; i <= 62; i++)
	{
		if (!checkTri(TS[i]))
		{
			clipping(TS[i], &TS[2 * i + 1], &TS[2 * i + 2], fb);
		}
	}//\CF\D6\D4ڣ\AC64\B8\F6clipping\C8\FD\BD\C7\D0δ\E6\D4\DATS\A1\BE63\A1\BF-TS\A1\BE126\A1\BF\D6С\A3
	
	for (int i = 1; i <= 126; i++)
	{
		if (!checkTri(TS[i]))
		{
			viewTrans(TS[i].v0.x, TS[i].v0.y, TS[i].v0.z, &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], vG);
			viewTrans(TS[i].v1.x, TS[i].v1.y, TS[i].v1.z, &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], vG);
			viewTrans(TS[i].v2.x, TS[i].v2.y, TS[i].v2.z, &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], vG);
			scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
		}
	}
	free(TS);
	return;
}
*/
/*
void
testWall()
{
RGBcolor cur_color;
cur_color = getColorTri(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], testMat, myLight, reverseV(viewDir));
GLfloat scrn_v0[3];
GLfloat scrn_v1[3];
GLfloat scrn_v2[3];
viewTrans(v0[0], v0[1], v0[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2]);
viewTrans(v1[0], v1[1], v1[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2]);
viewTrans(v2[0], v2[1], v2[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2]);
scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
}*/
int insideScrn(float *v0, float *v1, float *v2)
{
	if (v0[0] < Scr_Len && v0[0] > 0 && v0[1] < Scr_Wid && v0[1] > 0 && v0[2] > -1 && v0[2] < 1){
		if (v1[0] < Scr_Len && v1[0] > 0 && v1[1] < Scr_Wid && v1[1] > 0 && v1[2] > -1 && v1[2] < 1){
			if (v2[0] < Scr_Len && v2[0] > 0 && v2[1] < Scr_Wid && v2[1] > 0 && v2[2] > -1 && v2[2] < 1)
				return 1;
		}
	}
	return 0;
}
int outsideScrn(float *v0, float *v1, float *v2)
{
	if (v0[0] < 0 && v1[0] < 0 && v2[0] < 0)
	{
		return 1;
	}
	if (v0[0] > Scr_Len && v1[0] > Scr_Len && v2[0] > Scr_Len)
	{
		return 1;
	}
	if (v0[1] < 0 && v1[1] < 0 && v2[1] < 0)
	{
		return 1;
	}
	if (v0[1] > Scr_Wid && v1[1] > Scr_Wid && v2[1] > Scr_Wid)
	{
		return 1;
	}
	if (v0[2] < -1 && v1[2] < -1 && v2[2] < -1)
	{
		return 1;
	}
	if (v0[2] > 1 && v1[2] > 1 && v2[2] > 1)
	{
		return 1;
	}
	return 0;
}
int LBLineClipTest(float p, float q, float *umax, float *umin)
{
	float r = 0.0;
	if (p < 0.0)
	{
		r = q / p;
		if (r > *umin)		return 0;
		else if (r > *umax)	*umax = r;
	}
	else if (p > 0.0)
	{
		r = q / p;
		if (r < *umax)		return 0;
		else if (r < *umin)  *umin = r;
	}
	else if (q < 0.0)		return 0;
	return 1;
}
int LineClip( float x1, float y1, float z1, float x2, float y2, float z2, float *nx1, float *ny1, float *nz1, float *nx2, float *ny2, float *nz2)
{
	float newpt[2][3] = { { -1, -1, -1 }, { -1, -1, -1 }};
	int k = 0;
	if (x1 > -epsilon && x1 < (Scr_Wid + epsilon) && y1 > -epsilon && y1 < (Scr_Len + epsilon))
	{
		newpt[k][0] = x1;
		newpt[k][1] = y1;
		newpt[k][2] = z1;
		k++;
	}
	if (x2 > -epsilon && x2 < (Scr_Wid + epsilon) && y2 > -epsilon && y2 < (Scr_Len + epsilon))
	{
		newpt[k][0] = x2;
		newpt[k][1] = y2;
		newpt[k][2] = z2;
		k++;
	}
	// x = 0
	if (k < 2)
	{
		if ((x1*x2) < 0)
		{
			float t = (0 - x1) / (x2 - x1);
			float y = y1 + t*(y2 - y1);
			if (y > -epsilon && y < (Scr_Len + epsilon))
			{
				newpt[k][0] = 0;
				newpt[k][1] = y;
				newpt[k][2] = z1 + t*(z2 - z1);
				k++;
			}
		}
	}
	// x = 512
	if (k < 2)
	{
		if (((x1 - 512)*(x2 - 512)) < 0)
		{
			float t = (512 - x1) / (x2 - x1);
			float y = y1 + t*(y2 - y1);
			if (y > -epsilon && y < (Scr_Len + epsilon))
			{
				newpt[k][0] = 512;
				newpt[k][1] = y;
				newpt[k][2] = z1 + t*(z2 - z1);
				k++;
			}
		}
	}
	//y = 0
	if (k < 2)
	{
		if ((y1*y2) < 0)
		{
			float t = (0 - y1) / (y2 - y1);
			float x = x1 + t*(x2 - x1);
			if (x > -epsilon && x < (Scr_Len + epsilon))
			{
				newpt[k][0] = x;
				newpt[k][1] = 0;
				newpt[k][2] = z1 + t*(z2 - z1);
				k++;
			}
		}
	}
	//y = 512
	if (k < 2)
	{
		if (((y1 - 512)*(y2 - 512)) < 0)
		{
			float t = (512 - y1) / (y2 - y1);
			float x = x1 + t*(x2 - x1);
			if (x > -epsilon && x < (Scr_Len + epsilon))
			{
				newpt[k][0] = x;
				newpt[k][1] = 512;
				newpt[k][2] = z1 + t*(z2 - z1);
				k++;
			}
		}
	}
	if (k == 2)
	{
		*nx1 = newpt[0][0];
		*ny1 = newpt[0][1];
		*nz1 = newpt[0][2];
		*nx2 = newpt[1][0];
		*ny2 = newpt[1][1];
		*nz2 = newpt[1][2];
		return 1;
	}
	else
	{
		return 0;
	}

}
int LBLineClip(float xl, float xr, float yb, float yt, float x1, float y1, float z1, float x2, float y2, float z2, float *nx1, float *ny1, float *nz1, float *nx2, float *ny2, float *nz2 )
{
	float umax, umin, deltax, deltay, deltaz;
	deltax = x2 - x1;
	deltay = y2 - y1;
	deltaz = z2 - z1;
	umax = 0.0;
	umin = 1.0;
	if (LBLineClipTest(-deltax, x1 - xl, &umax, &umin)){
		if (LBLineClipTest(deltax, xr - x1, &umax, &umin)){
			if (LBLineClipTest(-deltay, y1 - yb, &umax, &umin)){
				if (LBLineClipTest(deltay, yt - y1, &umax, &umin)){
					*nx1 = x1 + umax*deltax;
					*ny1 = y1 + umax*deltay;
					*nz1 = z1 + umax*deltaz;
					*nx2 = x1 + umin*deltax;
					*ny2 = y1 + umin*deltay;
					*nz2 = z1 + umin*deltaz;

					
				}
				return 1;
			}
		}
	}
	return 0;
}
int onBorder(float x, float y)
{

	if (fabsf(y - 512) < epsilon && fabsf(x) < epsilon)
	{
		return 0;
	}
	if (fabsf(y - 512) < epsilon)
	{
		return 3;
	}
	if (fabsf(x - 512) < epsilon)
	{
		return 2;
	}
	if (fabsf(y) < epsilon)
	{
		return 1;
	}
	if (fabsf(x) < epsilon)
	{
		return 0;
	}
}
void addVertex(float x1, float y1, float z1, float x2, float y2, float z2, int *k, float hexa[][3])
{
	int start = onBorder(x1, y1);
	int end = onBorder(x2, y2);
	int delta = (start - end) % 4;
	if (delta == 0)
	{
		return;
	}
	if (start == 0)
	{
		if (delta == 1)
		{
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
		if (delta == 2)
		{
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 511.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
		if (delta == 3)
		{
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 511.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 511.0;
			hexa[*k][1] = 511.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
	}
	if (start == 1)
	{
		if (delta == 1)
		{
			hexa[*k][0] = 511.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
		if (delta == 2)
		{
			hexa[*k][0] = 511.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 511.0;
			hexa[*k][1] = 511.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
		if (delta == 3)
		{
			hexa[*k][0] = 511.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 512.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
	}
	if (start == 2)
	{
		if (delta == 1)
		{
			hexa[*k][0] = 512.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
		if (delta == 2)
		{
			hexa[*k][0] = 512.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
		if (delta == 3)
		{
			hexa[*k][0] = 512.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
	}
	if (start == 3)
	{
		if (delta == 1)
		{
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
		if (delta == 2)
		{
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
		if (delta == 3)
		{
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 512.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 0.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			hexa[*k][0] = 512.0;
			hexa[*k][1] = 0.0;
			hexa[*k][2] = z1;
			(*k)++;
			return;
		}
	}
}
int insideTri(float *v0, float *v1, float *v2, float x, float y)
{
	GLdouble S = getAreaTri(v0[0], v0[1], v1[0], v1[1], v2[0], v2[1]);
	GLdouble u, v, w, sum;
	u = getAreaTri(v0[0], v0[1], v1[0], v1[1], x, y);
	v = getAreaTri(v1[0], v1[1], v2[0], v2[1], x, y);
	w = getAreaTri(v2[0], v2[1], v0[0], v0[1], x, y);
	sum = u + v + w;
	if (abs(S - sum) < epsilon2)
	{
		return 1;
	}
	return 0;
}
void clipNColorNew(float *v0, float *v1, float *v2, RGBcolor cur_color,int j)
{
	float hexa[10][3] = { { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 } };
	int k = 0;
	float nx1, ny1, nz1, nx2, ny2, nz2;
	//intersection
	if (LBLineClip(0, Scr_Len, 0, Scr_Wid, v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)){		//LBLineClip(0, Scr_Len, 0, Scr_Wid, v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)
		if (CHEAT == GL_TRUE)
		{
			bresenhamLine(nx1, ny1, nx2, ny2);
		}
		hexa[k][0] = nx1;
		hexa[k][1] = ny1;
		hexa[k][2] = nz1;
		k++;
		hexa[k][0] = nx2;
		hexa[k][1] = ny2;
		hexa[k][2] = nz2;
		k++;
	}
	if (LBLineClip(0, Scr_Len, 0, Scr_Wid, v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)){		//LBLineClip(0, Scr_Len, 0, Scr_Wid, v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)
		//bresenhamLine(nx1, ny1, nx2, ny2);
		hexa[k][0] = nx1;
		hexa[k][1] = ny1;
		hexa[k][2] = nz1;
		k++;
		hexa[k][0] = nx2;
		hexa[k][1] = ny2;
		hexa[k][2] = nz2;
		k++;
	}
	if (LBLineClip(0, Scr_Len, 0, Scr_Wid, v2[0], v2[1], v2[2], v0[0], v0[1], v0[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)){		//LBLineClip(0, Scr_Len, 0, Scr_Wid, v2[0], v2[1], v2[2], v0[0], v0[1], v0[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)
		if (CHEAT == GL_TRUE)
		{
			bresenhamLine(nx1, ny1, nx2, ny2);
		}
		hexa[k][0] = nx1;
		hexa[k][1] = ny1;
		hexa[k][2] = nz1;
		k++;
		hexa[k][0] = nx2;
		hexa[k][1] = ny2;
		hexa[k][2] = nz2;
		k++;
	}
	//vertice of window
	
	if (insideTri(v0, v1, v2, 0.0, 0.0))
	{
		hexa[k][0] = 0.0;
		hexa[k][1] = 0.0;
		hexa[k][2] = (v0[2] + v1[2] + v2[2]) / 3;
		k++;
	}
	if (insideTri(v0, v1, v2, 512.0, 0.0))
	{
		hexa[k][0] = 512.0;
		hexa[k][1] = 0.0;
		hexa[k][2] = (v0[2] + v1[2] + v2[2]) / 3;
		k++;
	}
	if (insideTri(v0, v1, v2, 0.0, 512.0))
	{
		hexa[k][0] = 0.0;
		hexa[k][1] = 512.0;
		hexa[k][2] = (v0[2] + v1[2] + v2[2]) / 3;
		k++;
	}
	if (insideTri(v0, v1, v2, 512.0, 512.0))
	{
		hexa[k][0] = 512.0;
		hexa[k][1] = 512.0;
		hexa[k][2] = (v0[2] + v1[2] + v2[2]) / 3;
		k++;
	}
	
	
	if (hexa[0][0] > -0.5 && hexa[1][0] > -0.5)
	for (int i = 1; i <= 7; i++)
	{
		if (hexa[i + 1][0] > -0.5)
		{
			//0 i i+1
			scanLineTriNew(hexa[0][0], hexa[0][1], hexa[0][2], hexa[i][0], hexa[i][1], hexa[i][2], hexa[i + 1][0], hexa[i + 1][1], hexa[i + 1][2], cur_color,j);
		}
		else
		{
			return;
		}
	}
	
	return;
}
void clipNColor(float *v0, float *v1, float *v2, RGBcolor cur_color,int j)
{
	float hexa[8][3] = { { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 }, { -1, -1, -1 } };
	int k = 0;
	float nx1, ny1, nz1, nx2, ny2, nz2;
	int l1 = 0;
	int l2 = 0;
	int l3 = 0;
	if (LBLineClip(0, Scr_Len, 0, Scr_Wid, v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)){		//LBLineClip(0, Scr_Len, 0, Scr_Wid, v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)
		hexa[k][0] = nx1;
		hexa[k][1] = ny1;
		hexa[k][2] = nz1;
		k++;
		hexa[k][0] = nx2;
		hexa[k][1] = ny2;
		hexa[k][2] = nz2;
		k++;
		l1 = 1;
	}
	if (LBLineClip(0, Scr_Len, 0, Scr_Wid, v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)){		//LBLineClip(0, Scr_Len, 0, Scr_Wid, v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)
		hexa[k][0] = nx1;
		hexa[k][1] = ny1;
		hexa[k][2] = nz1;
		k++;
		hexa[k][0] = nx2;
		hexa[k][1] = ny2;
		hexa[k][2] = nz2;
		k++;
		l2 = 1;
	}
	if (LBLineClip(0, Scr_Len, 0, Scr_Wid, v2[0], v2[1], v2[2], v0[0], v0[1], v0[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)){		//LBLineClip(0, Scr_Len, 0, Scr_Wid, v2[0], v2[1], v2[2], v0[0], v0[1], v0[2], &nx1, &ny1, &nz1, &nx2, &ny2, &nz2)
		if (l1 == 1 && l2 == 0)
		{
			addVertex(hexa[k - 1][0], hexa[k - 1][1], hexa[k - 1][2], nx1, ny1, nz1, &k, hexa);
		}
		hexa[k][0] = nx1;
		hexa[k][1] = ny1;
		hexa[k][2] = nz1;
		k++;
		hexa[k][0] = nx2;
		hexa[k][1] = ny2;
		hexa[k][2] = nz2;
		k++;
		l3 = 1;
	}
	if (l1 == 1  && l3 == 1) {

	}
	else if (l1 == 0 && l2 == 0 && l3 == 0){
		if (insideTri(v0, v1, v2, 0.0, 0.0) && insideTri(v0, v1, v2, 0.0, 512.0) && insideTri(v0, v1, v2, 512.0, 512.0) && insideTri(v0, v1, v2, 512.0, 0.0) ) {
			hexa[k][0] = 0.0;
			hexa[k][1] = 0.0;
			hexa[k][2] = v0[3];
			k++;
			hexa[k][0] = 512.0;
			hexa[k][1] = 0.0;
			hexa[k][2] = v0[3];
			k++;
			hexa[k][0] = 512.0;
			hexa[k][1] = 512.0;
			hexa[k][2] = v0[3];
			k++;
			hexa[k][0] = 0.0;
			hexa[k][1] = 512.0;
			hexa[k][2] = v0[3];
			k++;
		}
	}
	else {
		addVertex(hexa[k - 1][0], hexa[k - 1][1], hexa[k - 1][2], hexa[0][0], hexa[0][1], hexa[0][2], &k, hexa);
	}
	//output
	if (hexa[0][0] > -0.5 && hexa[1][0] > -0.5)
	for (int i = 1; i <= 7; i++)
	{
		if (hexa[i + 1][0] > -0.5)
		{
			//0 i i+1
			scanLineTriNew(hexa[0][0], hexa[0][1], hexa[0][2], hexa[i][0], hexa[i][1], hexa[i][2], hexa[i + 1][0], hexa[i + 1][1], hexa[i + 1][2], cur_color,j);
		}
		else
		{
			return;
		}
	}
	return;
	/*
	if (hexa[0][0] > -0.5 && hexa[2][0] > -0.5)
	{
		//012
		scanLineTriNew(hexa[0][0], hexa[0][1], hexa[0][2], hexa[1][0], hexa[1][1], hexa[1][2], hexa[2][0], hexa[2][1], hexa[2][2], cur_color);
		//023
		scanLineTriNew(hexa[0][0], hexa[0][1], hexa[0][2], hexa[2][0], hexa[2][1], hexa[2][2], hexa[3][0], hexa[3][1], hexa[3][2], cur_color);
		if (hexa[4][0] > -0.5)
		{
			//034
			scanLineTriNew(hexa[0][0], hexa[0][1], hexa[0][2], hexa[3][0], hexa[3][1], hexa[3][2], hexa[4][0], hexa[4][1], hexa[4][2], cur_color);
			//045
			scanLineTriNew(hexa[0][0], hexa[0][1], hexa[0][2], hexa[4][0], hexa[4][1], hexa[4][2], hexa[5][0], hexa[5][1], hexa[5][2], cur_color);
		}
	}
	*/
}
void
microMap(float x1, float y1, float x2, float y2,float x3, float y3)
{
	x1 = x1 / 10 + 40;
	x2 = x2 / 10 + 40;
	x3 = x3 / 10 + 40;
	y1 = y1 / 10 + 472;
	y2 = y2 / 10 + 472;
	y3 = y3 / 10 + 472;
	bresenhamLine(x1, y1, x2, y2);
	bresenhamLine(x3, y3, x2, y2);
	bresenhamLine(x1, y3, x1, y1);
	bresenhamLine(x1, y3, x3, y3);
	return;
}
int
critical(float x, float z, MyPoint viewGaz)
{
	float x1 = viewPos.x + nPer*viewGaz.x / 8;
	float z1 = viewPos.z + nPer*viewGaz.z / 8;
	float x2 = x1 + viewGaz.x;
	float z2 = z1 + viewGaz.z;
	float cos = (x - x1)*(x2 - x1) + (z - z1)*(z2 - z1);
	if (cos > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void
display(void)
{
	//printf("%f	%f\n", viewPos.x, viewPos.z);
	float newView[3] = { rotatePoint3D(roThetaY, 0, 1, 0, viewDir).x, rotatePoint3D(roThetaY, 0, 1, 0, viewDir).y, rotatePoint3D(roThetaY, 0, 1, 0, viewDir).z };
	
	//float newView[3] = { rotatePoint3D(roThetaY, roAxisY.x, roAxisY.y, roAxisY.z, viewDir).x, rotatePoint3D(roThetaY, roAxisY.x, roAxisY.y, roAxisY.z, viewDir).y, rotatePoint3D(roThetaY, roAxisY.x, roAxisY.y, roAxisY.z, viewDir).z };
	//viewDir.x = newView[0];
	//viewDir.y = newView[1];
	//viewDir.z = newView[2];
	MyPoint viewGaz = { newView[0], newView[1], newView[2] };
	MyPoint viewLeft = { crossProduct(viewUp, viewGaz).x, crossProduct(viewUp, viewGaz).y, crossProduct(viewUp, viewGaz).z };
	//init cul face

	/*
	MyPoint p1 = { (viewPos.x - nPer * viewGaz.x - lPer * viewLeft.x + tPer * viewUp.x), (viewPos.y - nPer * viewGaz.y - lPer * viewLeft.y + tPer * viewUp.y), (viewPos.z - nPer * viewGaz.z - lPer * viewLeft.z + tPer * viewUp.z) };
	MyPoint p2 = { (viewPos.x - nPer * viewGaz.x - rPer * viewLeft.x + tPer * viewUp.x), (viewPos.y - nPer * viewGaz.y - rPer * viewLeft.y + tPer * viewUp.y), (viewPos.z - nPer * viewGaz.z - rPer * viewLeft.z + tPer * viewUp.z) };
	MyPoint p3 = { (viewPos.x - nPer * viewGaz.x - rPer * viewLeft.x + bPer * viewUp.x), (viewPos.y - nPer * viewGaz.y - rPer * viewLeft.y + bPer * viewUp.y), (viewPos.z - nPer * viewGaz.z - rPer * viewLeft.z + bPer * viewUp.z) };
	MyPoint p4 = { (viewPos.x - nPer * viewGaz.x - lPer * viewLeft.x + bPer * viewUp.x), (viewPos.y - nPer * viewGaz.y - lPer * viewLeft.y + bPer * viewUp.y), (viewPos.z - nPer * viewGaz.z - lPer * viewLeft.z + bPer * viewUp.z) };
	MyPoint p5 = { (viewPos.x - fPer * viewGaz.x - lPer * viewLeft.x + tPer * viewUp.x), (viewPos.y - fPer * viewGaz.y - lPer * viewLeft.y + tPer * viewUp.y), (viewPos.z - fPer * viewGaz.z - lPer * viewLeft.z + tPer * viewUp.z) };
	MyPoint p6 = { (viewPos.x - fPer * viewGaz.x - rPer * viewLeft.x + bPer * viewUp.x), (viewPos.y - fPer * viewGaz.y - rPer * viewLeft.y + bPer * viewUp.y), (viewPos.z - fPer * viewGaz.z - rPer * viewLeft.z + bPer * viewUp.z) };
	
	ClipFace fn;
	ClipFace ff;
	ClipFace fl;
	ClipFace fr;
	ClipFace ft;
	ClipFace fb;
	fn.n = { viewGaz.x, viewGaz.y, viewGaz.z }; 
	fn.p = { p1.x, p1.y, p1.z };
	ff.n = { -viewGaz.x, -viewGaz.y, -viewGaz.z };
	ff.p = { p6.x, p6.y, p6.z };
	fl.n = getNorTri(p1, p4, p5);
	fl.p = { p1.x, p1.y, p1.z };
	fr.n = getNorTri(p2, p6, p3);
	fr.p = { p6.x, p6.y, p6.z };
	ft.n = getNorTri(p1, p5, p2);
	ft.p = { p1.x, p1.y, p1.z };
	fb.n = getNorTri(p3, p6, p4);
	fb.p = { p6.x, p6.y, p6.z };
	*/


	RGBcolor cur_color;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int j = 0; j < (Scr_Wid / Horizon); j++)
	for (int k = 0; k < Scr_Len; k++)
	{
		GLPixelData[j][k].r = 0.1;
		GLPixelData[j][k].g = 0.1;
		GLPixelData[j][k].b = 0.1;
		zBufferPixel[j][k] = INF;
	}

	for (int j = (Scr_Wid / Horizon); j < Scr_Wid; j++)
	for (int k = 0; k < Scr_Len; k++)
	{
		GLPixelData[j][k].r = 0.3;
		GLPixelData[j][k].g = 0.3;
		GLPixelData[j][k].b = 0.3;
		zBufferPixel[j][k] = INF;
	}
	GLfloat v0[3];
	GLfloat v1[3];
	GLfloat v2[3];
	GLfloat scrn_v0[3];
	GLfloat scrn_v1[3];
	GLfloat scrn_v2[3];


	for (int j = 0; j <= maze.numofgroups; j++)
	if (maze.Modelgroups[j].enable == 1)
	for (int i = 0; i <= maze.Modelgroups[j].numoffaces; i++)
	{
		v0[0] = maze.Modelgroups[j].groupfaces[i].triangle1[0][0];
		v0[1] = maze.Modelgroups[j].groupfaces[i].triangle1[0][2];
		v0[2] = -maze.Modelgroups[j].groupfaces[i].triangle1[0][1];
		v1[0] = maze.Modelgroups[j].groupfaces[i].triangle1[1][0];
		v1[1] = maze.Modelgroups[j].groupfaces[i].triangle1[1][2];
		v1[2] = -maze.Modelgroups[j].groupfaces[i].triangle1[1][1];
		v2[0] = maze.Modelgroups[j].groupfaces[i].triangle1[2][0];
		v2[1] = maze.Modelgroups[j].groupfaces[i].triangle1[2][2];
		v2[2] = -maze.Modelgroups[j].groupfaces[i].triangle1[2][1];
		if (critical(v0[0], v0[2], viewGaz) && critical(v1[0], v1[2], viewGaz) && critical(v2[0], v2[2], viewGaz))
		{
			if (j == 12 || j == 13){
				cur_color = getColorTri(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], testMat2, myLight, reverseV(viewGaz));
			}
			else{
				cur_color = getColorTri(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], testMat, myLight, reverseV(viewGaz));
			}
			//DoTri(viewGaz, v0, v1, v2, cur_color, fn, ff, fl, fr, ft, fb );

			viewTrans(v0[0], v0[1], v0[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
			viewTrans(v1[0], v1[1], v1[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
			viewTrans(v2[0], v2[1], v2[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
			// if all inside z included
			if (insideScrn(scrn_v0, scrn_v1, scrn_v2)){
				scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color,j);
				if (CHEAT == GL_TRUE)
				{
					bresenhamLine(scrn_v0[0], scrn_v0[1], scrn_v1[0], scrn_v1[1]);
					//bresenhamLine(scrn_v1[0], scrn_v1[1], scrn_v2[0], scrn_v2[1]);
					bresenhamLine(scrn_v2[0], scrn_v2[1], scrn_v0[0], scrn_v0[1]);
				}
			}
			// if all outside do nothing z included

			else if (outsideScrn(scrn_v0, scrn_v1, scrn_v2)){

			}
			else
			{
				clipNColorNew(scrn_v0, scrn_v1, scrn_v2, cur_color,j);
			}
		}
		/*
		else if (critical(v0[0], v0[2], viewGaz) || critical(v1[0], v1[2], viewGaz) || critical(v2[0], v2[2], viewGaz))
		{
			cur_color = getColorTri(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], testMat, myLight, reverseV(viewGaz));
			ClipFace f ;
			f.n.x = viewGaz.x;
			f.n.y = viewGaz.y;
			f.n.z = viewGaz.z;
			f.p.x = viewPos.x + nPer*viewGaz.x / 8;
			f.p.y = 0;
			f.p.z = viewPos.z + nPer*viewGaz.z / 8;
			Triangle T0 ;
			T0.v0.x = v0[0];
			T0.v0.y = v0[1];
			T0.v0.z = v0[2];
			T0.v1.x = v1[0];
			T0.v1.y = v1[1];
			T0.v1.z = v1[2];
			T0.v2.x = v2[0];
			T0.v2.y = v2[1];
			T0.v2.z = v2[2];
			Triangle T1, T2;
			int k = clippingNew(T0, &T1, &T2, f);
			viewTrans(T1.v0.x, T1.v0.y, T1.v0.z, &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
			viewTrans(T1.v1.x, T1.v1.y, T1.v1.z, &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
			viewTrans(T1.v2.x, T1.v2.y, T1.v2.z, &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
			
			if (insideScrn(scrn_v0, scrn_v1, scrn_v2)){
				scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
				if (CHEAT == GL_TRUE)
				{
					bresenhamLine(scrn_v0[0], scrn_v0[1], scrn_v1[0], scrn_v1[1]);
					//bresenhamLine(scrn_v1[0], scrn_v1[1], scrn_v2[0], scrn_v2[1]);
					bresenhamLine(scrn_v2[0], scrn_v2[1], scrn_v0[0], scrn_v0[1]);
				}
			}
			// if all outside do nothing z included

			else if (outsideScrn(scrn_v0, scrn_v1, scrn_v2)){

			}
			else
			{
				clipNColorNew(scrn_v0, scrn_v1, scrn_v2, cur_color);
			}
			if (k == 2)
			{
				viewTrans(T1.v0.x, T1.v0.y, T1.v0.z, &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
				viewTrans(T1.v1.x, T1.v1.y, T1.v1.z, &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
				viewTrans(T1.v2.x, T1.v2.y, T1.v2.z, &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
			
				if (insideScrn(scrn_v0, scrn_v1, scrn_v2)){
					scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
					if (CHEAT == GL_TRUE)
					{
						bresenhamLine(scrn_v0[0], scrn_v0[1], scrn_v1[0], scrn_v1[1]);
						//bresenhamLine(scrn_v1[0], scrn_v1[1], scrn_v2[0], scrn_v2[1]);
						bresenhamLine(scrn_v2[0], scrn_v2[1], scrn_v0[0], scrn_v0[1]);
					}
				}
				// if all outside do nothing z included

				else if (outsideScrn(scrn_v0, scrn_v1, scrn_v2)){

				}
				else
				{
					clipNColorNew(scrn_v0, scrn_v1, scrn_v2, cur_color);
				}
			}
		}*/
		
		// else clip to get hexa then 123 134 145 156
		// return 2 pt for every edge if no intersection(every vertex is on one side of edge) return vertex that is included in tri
		v0[0] = maze.Modelgroups[j].groupfaces[i].triangle2[0][0];
		v0[1] = maze.Modelgroups[j].groupfaces[i].triangle2[0][2];
		v0[2] = -maze.Modelgroups[j].groupfaces[i].triangle2[0][1];
		v1[0] = maze.Modelgroups[j].groupfaces[i].triangle2[1][0];
		v1[1] = maze.Modelgroups[j].groupfaces[i].triangle2[1][2];
		v1[2] = -maze.Modelgroups[j].groupfaces[i].triangle2[1][1];
		v2[0] = maze.Modelgroups[j].groupfaces[i].triangle2[2][0];
		v2[1] = maze.Modelgroups[j].groupfaces[i].triangle2[2][2];
		v2[2] = -maze.Modelgroups[j].groupfaces[i].triangle2[2][1];
		if (critical(v0[0], v0[2], viewGaz) && critical(v1[0], v1[2], viewGaz) && critical(v2[0], v2[2], viewGaz))
		{
			if (j == 12 || j == 13){
				cur_color = getColorTri(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], testMat2, myLight, reverseV(viewGaz));
			}
			else{
				cur_color = getColorTri(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], testMat, myLight, reverseV(viewGaz));
			}			//DoTri(viewGaz, v0, v1, v2, cur_color, fn, ff, fl, fr, ft, fb);

			viewTrans(v0[0], v0[1], v0[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
			viewTrans(v1[0], v1[1], v1[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
			viewTrans(v2[0], v2[1], v2[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
			// if all inside z included
			if (insideScrn(scrn_v0, scrn_v1, scrn_v2)){
				scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color,j);
				if (CHEAT == GL_TRUE)
				{
					bresenhamLine(scrn_v0[0], scrn_v0[1], scrn_v1[0], scrn_v1[1]);
					//bresenhamLine(scrn_v1[0], scrn_v1[1], scrn_v2[0], scrn_v2[1]);
					bresenhamLine(scrn_v2[0], scrn_v2[1], scrn_v0[0], scrn_v0[1]);
				}
			}

			else if (outsideScrn(scrn_v0, scrn_v1, scrn_v2)){

			}
			else
			{
				clipNColorNew(scrn_v0, scrn_v1, scrn_v2, cur_color,j);
			}
		}
	}

	/* testing wall
	cur_color = getColorTri(v2[0], v2[1], v2[2], v3[0], v3[1], v3[2], v7[0], v7[1], v7[2], testMat, myLight, reverseV(viewGaz));

	viewTrans(v2[0], v2[1], v2[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
	viewTrans(v3[0], v3[1], v3[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
	viewTrans(v7[0], v7[1], v7[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
	scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
	
	cur_color = getColorTri(v2[0], v2[1], v2[2], v7[0], v7[1], v7[2], v6[0], v6[1], v6[2], testMat, myLight, reverseV(viewGaz));

	viewTrans(v2[0], v2[1], v2[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
	viewTrans(v7[0], v7[1], v7[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
	viewTrans(v6[0], v6[1], v6[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
	scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
	
	cur_color = getColorTri(v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], v6[0], v6[1], v6[2], testMat, myLight, reverseV(viewGaz));

	viewTrans(v1[0], v1[1], v1[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
	viewTrans(v2[0], v2[1], v2[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
	viewTrans(v6[0], v6[1], v6[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
	scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
	
	cur_color = getColorTri(v1[0], v1[1], v1[2], v6[0], v6[1], v6[2], v5[0], v5[1], v5[2], testMat, myLight, reverseV(viewGaz));

	viewTrans(v1[0], v1[1], v1[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
	viewTrans(v6[0], v6[1], v6[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
	viewTrans(v5[0], v5[1], v5[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
	scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);

	cur_color = getColorTri(v3[0], v3[1], v3[2], v0[0], v0[1], v0[2], v7[0], v7[1], v7[2], testMat, myLight, reverseV(viewGaz));

	viewTrans(v3[0], v3[1], v3[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
	viewTrans(v0[0], v0[1], v0[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
	viewTrans(v7[0], v7[1], v7[2],  &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
	scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);

	cur_color = getColorTri(v0[0], v0[1], v0[2], v4[0], v4[1], v4[2], v7[0], v7[1], v7[2], testMat, myLight, reverseV(viewGaz));

	viewTrans(v0[0], v0[1], v0[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
	viewTrans(v4[0], v4[1], v4[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
	viewTrans(v7[0], v7[1], v7[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
	scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);

	cur_color = getColorTri(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], v4[0], v4[1], v4[2], testMat, myLight, reverseV(viewGaz));

	viewTrans(v0[0], v0[1], v0[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
	viewTrans(v1[0], v1[1], v1[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
	viewTrans(v4[0], v4[1], v4[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
	scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);


	cur_color = getColorTri(v1[0], v1[1], v1[2], v5[0], v5[1], v5[2], v4[0], v4[1], v4[2], testMat, myLight, reverseV(viewGaz));

	viewTrans(v1[0], v1[1], v1[2], &scrn_v0[0], &scrn_v0[1], &scrn_v0[2], viewGaz);
	viewTrans(v5[0], v5[1], v5[2], &scrn_v1[0], &scrn_v1[1], &scrn_v1[2], viewGaz);
	viewTrans(v4[0], v4[1], v4[2], &scrn_v2[0], &scrn_v2[1], &scrn_v2[2], viewGaz);
	scanLineTriNew(scrn_v0[0], scrn_v0[1], scrn_v0[2], scrn_v1[0], scrn_v1[1], scrn_v1[2], scrn_v2[0], scrn_v2[1], scrn_v2[2], cur_color);
	*/
	if (CHEAT == GL_TRUE)
	{

		float viewLefta[3] = { crossProduct(viewUp, viewGaz).x, crossProduct(viewUp, viewGaz).y, crossProduct(viewUp, viewGaz).z };
		float xme = viewPos.x;
		float yme = -viewPos.z;
		float xfront = viewPos.x + 50 * viewGaz.x;
		float yfront = -viewPos.z - 50 * viewGaz.z;
		xme = xme / 10 + 40;
		xfront = xfront / 10 + 40;
		yme = yme / 10 + 472;
		yfront = yfront / 10 + 472;

		microMap(-280+160, -320, 120+160, -320, 120+160, -360);
		microMap(-280, 320, -240, 320, -240, -320);
		microMap(-280, 360, 120, 360, 120, 320);
		microMap(-240, 180, -80, 180, -80, 140);
		microMap(-240, -140, -80, -140, -80, -180);
		microMap(-100, 20, 100, 20, 100, -20);
		microMap(80, 180, 240, 180, 240, 140);
		microMap(80, -140, 240, -140, 240, -180);
		microMap(240, 320, 280, 320, 280, -320);
		microMap(80, 140, 100, 140, 100, 20);
		float xright = xme - (2 * viewLeft.x);
		float yright = yme + (2 * viewLeft.z);
		float xleft = xme + (2 * viewLeft.x);
		float yleft = yme - (2 * viewLeft.z);
		bresenhamLine(xright, yright, xleft, yleft);
		bresenhamLine(xfront, yfront, xright, yright);
		bresenhamLine(xfront, yfront, xleft, yleft);
	}
	glDrawPixels(Scr_Wid, Scr_Len, GL_RGB, GL_FLOAT, GLPixelData);
	glutSwapBuffers();
}

void
keyboard(unsigned char key, int x, int y)
{
	float viewGaze[3] = { rotatePoint3D(roThetaY, 0, 1, 0, viewDir).x, rotatePoint3D(roThetaY, 0, 1, 0, viewDir).y, rotatePoint3D(roThetaY, 0, 1, 0, viewDir).z };
	MyPoint viewGaz = { viewGaze[0], viewGaze[1], viewGaze[2] };
	float viewLeft[3] = { crossProduct(viewUp, viewGaz).x, crossProduct(viewUp, viewGaz).y, crossProduct(viewUp, viewGaz).z };
	switch (key) {
	case 'c':
		if (CHEAT == GL_TRUE)
		{
			CHEAT = GL_FALSE;
		}
		else
		{
			CHEAT = GL_TRUE;
		}
		glutPostRedisplay();
		break;
	case 'w':
		if (checkviewpoint(-(viewPos.x + viewGaze[0] * 45), viewPos.z + viewGaze[2] * 45))
		{
			viewPos.x += viewGaze[0] * 5;
			viewPos.y += viewGaze[1] * 5;
			viewPos.z += viewGaze[2] * 5;
		}
		glutPostRedisplay();
		break;
	case 's':
		if (checkviewpoint(-(viewPos.x - viewGaze[0] * 25), viewPos.z - viewGaze[2] * 25))
		{
			viewPos.x -= viewGaze[0] * 5;
			viewPos.y -= viewGaze[1] * 5;
			viewPos.z -= viewGaze[2] * 5;
		}
		glutPostRedisplay();
		break;
	case 'a':
		if (checkviewpoint(-(viewPos.x + viewLeft[0] * 25), viewPos.z + viewLeft[2] * 25))
		{
			viewPos.x += viewLeft[0] * 5;
			viewPos.y += viewLeft[1] * 5;
			viewPos.z += viewLeft[2] * 5;
		}
		glutPostRedisplay();
		break;
	case 'd':
		if (checkviewpoint(-(viewPos.x - viewLeft[0] * 25), viewPos.z - viewLeft[2] * 25))
		{
			viewPos.x -= viewLeft[0] * 5;
			viewPos.y -= viewLeft[1] * 5;
			viewPos.z -= viewLeft[2] * 5;
		}
		glutPostRedisplay();
		break;
	case 'z':
		viewPos.y += 5;
		glutPostRedisplay();
		break;
	case 'x':
		viewPos.y -= 5;
		glutPostRedisplay();
		break;
	case 'j':
		roThetaY += 0.05;
		glutPostRedisplay();
		break;
	case 'l':
		roThetaY -= 0.05;
		glutPostRedisplay();
		break;
	}
}
void 
Mouse(int button, int state, int x, int y)
{
	/*
	FILE *fp = fopen("mouseposition.txt", "w");
	if (button == 0)
	{
		//fprintf(fp,"%d %d",x,y);
		fprintf(fp, "%d %d", x, y);
	}
	fclose(fp);
	*/
	if (state== 0)
	{
		/*if (groupbuffer[512 - y][x] == 13 || groupbuffer[512 - y][x] ==12){
			maze.Modelgroups[groupbuffer[512 - y][x]].enable = 0;
			glutPostRedisplay();
		}*/
		if (groupbuffer[512 - y][x] == 12)
		{
			door12angle += 0.2;
			copyWall(&maze.Modelgroups[12], &maze.Modelgroups[0], 0, -160, 0, cos(door12angle), sin(door12angle), 0, -sin(door12angle), cos(door12angle), 0, 0, 0, 1);
			scalegroup(&maze.Modelgroups[12], 0.8, 0.5, 1);
				obj_to_world(&maze.Modelgroups[12]);
		}
		if (groupbuffer[512 - y][x] == 13)
		{
			door13angle += 0.2;
			copyWall(&maze.Modelgroups[13], &maze.Modelgroups[0], 0, 160, 0, cos(door13angle), sin(door13angle), 0, -sin(door13angle), cos(door13angle), 0, 0, 0, 1);
			scalegroup(&maze.Modelgroups[13], 0.8, 0.5, 1);
			obj_to_world(&maze.Modelgroups[13]);
		}
	}
	glutPostRedisplay();
	return;
}
int
main(int argc, char** argv)
{
	mazeinit();
	//Up to Dir
	int buffering = GLUT_DOUBLE;

	glutInitWindowSize(512, 512);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | buffering);
	glutCreateWindow("Maze");
	//keyborad
	glutDisplayFunc(display);
	glutMouseFunc(&Mouse);
	glutKeyboardFunc(keyboard);
	//menu
	glutMainLoop();
	return 0;
}
