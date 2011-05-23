
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Viewer.h"
#include "../ExportObj/ExportObj.h"
#include "../Geom/GL/GLColor.h"

GlutVariables Viewer::var = {	0, 0, 0, // mouse
				0, 0, 0.f, 
				0.f, // t
				0.f, (GLuint)0, 0};

Viewer::Viewer(std::string filename, int argc, char* argv[])
{
	exporter = new ExportObj(filename);
	glutInit(&argc, argv);
}

Viewer::~Viewer()
{
	delete exporter;	
}

void Viewer::Display(City* city, int width, int height)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

	// Création de la fenêtre initiale
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(0, 0);
	var.window = glutCreateWindow("Infinicity");
	
	
	
	/* *********************************************************************
	 * Fonctions de gestion de GLUT
	 * ********************************************************************/
	glutDisplayFunc(CityRendering);
	//glutFullScreen();
	glutIdleFunc(&GlutIdle);	// Rafraichissement
	glutReshapeFunc(Resize);	// Changement de taille
	glutKeyboardFunc(KeyboardManager);	// Clavier
	//glutSpecialFunc(&SpecialKeyboard);
	
	// Souris
	glutMouseFunc(&MousePushManager);
	glutMotionFunc(&MouseMoveManager);
	
	
	/* *********************************************************************
	 * Couleur du fond
	 * ********************************************************************/
	glClearColor (0.5f, 0.6f, 0.7f, 1.0);

	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);

	/* *********************************************************************
	 * Mode de projection en perspective
	 * ********************************************************************/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, 2.0f, 500.0f);

	/* *********************************************************************
	 * Placement des lumieres dans l'espace du modele
	 * ********************************************************************/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat light_ambient1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light_diffuse1[] = { 0.7f, 0.7f, 0.6f, 1.0f };
	GLfloat light_position1[] = { -50.0f, -50.0f, 200.0f, 0.0f };

	GLfloat light_ambient2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light_diffuse2[] = { 0.6f, 0.6f, 0.7f, 1.0f };
	GLfloat light_position2[] = { 50.0f, 50.0f, 200.0f, 0.0f };

	// lumière 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glEnable(GL_LIGHT1);

	// lumière 2
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glEnable(GL_LIGHT2);

	glEnable(GL_LIGHTING);
	
	/* *********************************************************************
	 *  Optimisation Elimination des facettes arriere
	 * ********************************************************************/
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	var.idCity = GenerateCity(city);
}


void Viewer::Loop()
{
	glutMainLoop();
}

GLuint Viewer::GenerateCity(City* city)
{
	GLuint list = glGenLists(1);

	glNewList(list,GL_COMPILE);
	{
		GlutShade(0.9f, 0.9f, 0.9f);
		
		city->Generate();
	}
	glEndList();

	return list;
}

void Viewer::CityRendering()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-40.f, 0.f, 20.f,  0, 0, 0,  0, 0, 1);

	if (var.rotate)
		var.alpha += var.rotationSpeed;
	glRotatef(var.alpha, 0.0f, 0.0f, 1.0f);
	
	glCallList(var.idCity);

	glutSwapBuffers();
}

void Viewer::Resize(int width, int height)
{
	height = (height == 0) ? 1: height;
	
	// Set window
	glViewport(0, 0, width, height);

	// Define the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 2.0f, 500.0f);

	// Back to model space
	glMatrixMode(GL_MODELVIEW);
	
}

void Viewer::KeyboardManager(unsigned char key, int x, int y)
{
	(void)x;
	(void)y;
	
	switch (key)
	{
		case 27:
			glutDestroyWindow(var.window);
			exit(EXIT_SUCCESS);
			break;
		case 'l':
		case 'L':
			var.light = 1 - var.light;
			if (!var.light)
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);
			break;
		case 'r':
		case 'R':
			var.rotate = 1 - var.rotate;
			break;
		case 'p':
		case 'P':
			break;
	}

	glutPostRedisplay();
}

void Viewer::MouseMoveManager(int x, int y)
{
	var.mouseX = x;
	var.mouseY = y;
}

void Viewer::MousePushManager(int button, int state, int x, int y)
{
	(void)state;
	MouseMoveManager(x, y);
	var.mouseKey = button;
}

void Viewer::GlutIdle()
{
	var.t += 1.0f;
	CityRendering();
}

