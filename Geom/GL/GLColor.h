#ifndef GLCOLOR_H
#define GLCOLOR_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Définit une matière a partir d'une couleur
inline void GlutShade(GLfloat r, GLfloat v, GLfloat b)
{
	// Couleur sans lumieres
	glColor3f(0.2, 0.7, 0.6);

	// Couleur avec lumieres
	GLfloat color[4];

	// La couleur diffuse sera egale a 87,5% de la couleur
	float percentage = 0.875f;
	color[0] = percentage * r;
	color[1] = percentage * v;
	color[2] = percentage * b;
	color[3] = 1.0;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	// La couleur ambiante sera egale a 12,5% de la couleur
	percentage = 0.125f;
	color[0] = percentage * r;
	color[1] = percentage * v;
	color[2] = percentage * b;
	color[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, color); // GL_AMBIENT_AND_DIFFUSE

	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;

	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color);
}

#endif
