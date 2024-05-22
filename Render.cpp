#include "Render.h"
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>


void Render(double delta_time) {
	glBegin(GL_LINES);
	
	glColor3d(1, 0, 0);
	glVertex3d(1, 0, 0);
	glVertex3d(0, 1, 0);
	glVertex3d(0, 0, 1);
	glEnd();
}