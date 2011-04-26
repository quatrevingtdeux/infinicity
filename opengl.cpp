// Affichage OpenGL
// Changelog 06.02.2002

#include "vector.h"

#include "city.h"
#include "shape.h"

// Identifiant d'une cité
GLuint cut;

double ro_speed = 0.012;

// Parametre global de temps
float t=0.0f;

// Angle
float alpha=0.0f;

int Mousekey=0,Mousex,Mousey;

int light=1;
int rotate=0;


// Identifiant de fenetre
int window;

GLuint GenerateCity()
{
    GLuint list = glGenLists(1);

    // Optimize list
    glNewList(list,GL_COMPILE);

    GlutShade(0.9,0.9,0.9);

    City city;
    city.Generate();

    // Fin de la liste
    glEndList();

    return list;
}


// Gestion du clavier.
void Keyboard(unsigned char key, int x, int y)
{
    // Si ESC
    if (key==27)
    {
        glutDestroyWindow(window);
        exit(0);
    }
    // Gestion des lumieres
    if ((key=='l') || (key=='L'))
    {
        light = 1-light;
        if (!light)
        {
            glDisable(GL_LIGHTING);
        }
        else
        {
            glEnable(GL_LIGHTING);
        }
    }
    if ((key=='r') || (key=='R'))
    {
        rotate = 1-rotate;
    }

    glutPostRedisplay();
}

void Resize(int width, int height)
{
    if (height==0)
    {
        height=1;
    }
    // Set window
    glViewport (0, 0, width, height);

    // Define the projection matrix
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,2.0f,500.0f);

    // Back to model space
    glMatrixMode(GL_MODELVIEW);
}


// Affichage
void GlutRendering()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt(-40.0, 0.0, 20.0,
              0, 0, 0,
              0, 0, 1);

    if (rotate)
    {
        alpha+=ro_speed;
    }
    glRotatef(alpha,0.0f,0.0f,1.0f);
    glCallList(cut);

    glutSwapBuffers();
}

void MouseMove(int x, int y)
{
    Mousex = x;
    Mousey = y;
}

void MousePush(int button, int state, int x, int y)
{

    Mousex = x;
    Mousey = y;
    Mousekey=button;
}

// Rafraichissement
void GlutIdle(void)
{
    // Augmentation du parametre de temps
    t+=1.0;
    GlutRendering();
}

//!Initialise OpenGL
void InitGlut(int width,int height)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

	// Fenetre initiale
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(0, 0);
	window=glutCreateWindow("City Generator");

	glutDisplayFunc(GlutRendering);
	//glutFullScreen();

	// Rafraichissement
	glutIdleFunc(&GlutIdle);

	// Changement de taille
	glutReshapeFunc(Resize);

	// Clavier
	glutKeyboardFunc(Keyboard);
	//glutSpecialFunc(&SpecialKeyboard);

	// Souris
	glutMouseFunc(MousePush);
	glutMotionFunc(MouseMove);

	// Initialise les parametres de rendu
	glClearColor (0.5f, 0.6f, 0.7f, 1.0);

	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,2.0f,500.0f);

	// Placement des lumieres dans l'espace du modele
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();				// Reset The Projection Matrix

	GLfloat light_ambient1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light_diffuse1[] = { 0.7f, 0.7f, 0.6f, 1.0f };
	GLfloat light_position1[] = { -50.0,-50.0, 200.0,0.0 };

	GLfloat light_ambient2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light_diffuse2[] = { 0.6f, 0.6f, 0.7f, 1.0f };
	GLfloat light_position2[] = { 50.0,50.0, 200.0,0.0 };

	glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv (GL_LIGHT1, GL_POSITION, light_position1);
	glEnable(GL_LIGHT1);

	glLightfv (GL_LIGHT2, GL_AMBIENT, light_ambient2);
	glLightfv (GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv (GL_LIGHT2, GL_POSITION, light_position2);
	glEnable(GL_LIGHT2);

	glEnable(GL_LIGHTING);

	// Elimination des facettes arriere
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	cut=GenerateCity();
}

int main(int argc,char **argv)
{
	glutInit(&argc, argv);

	InitGlut(512,512);
	glutMainLoop();
	return 0;
}
