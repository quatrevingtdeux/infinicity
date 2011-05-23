
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Viewer.h"
#include "../Geom/GL/GLColor.h"

Viewer::Viewer(int argc, char* argv[])
{
	glutInit(&argc, argv);
}

Viewer::~Viewer()
{}

void Viewer::Display(City* city, int width, int height)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

	// Création de la fenêtre initiale
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(0, 0);
	GlutVariables.window = glutCreateWindow("Infinicity");
	
	
	
	/* *********************************************************************
	 * Fonctions de gestion de GLUT
	 * ********************************************************************/
	/*glutDisplayFunc(GlutRendering);
	//glutFullScreen();
	glutIdleFunc(&GlutIdle);	// Rafraichissement
	glutReshapeFunc(Resize);	// Changement de taille
	glutKeyboardFunc(Keyboard);	// Clavier
	//glutSpecialFunc(&SpecialKeyboard);
	
	// Souris
	glutMouseFunc(MousePush);
	glutMotionFunc(MouseMove);
	*/
	
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

	GlutVariables.idCity = GenerateCity();
}


void Viewer::Loop()
{
	glutMainLoop();
}

GLuint Viewer::GenerateCity()
{
	GLuint list = glGenLists(1);

	glNewList(list,GL_COMPILE);
	{
		GlutShade(0.9f, 0.9f, 0.9f);

		City city;
		city.Generate();
	}
	glEndList();

	return list;
}

