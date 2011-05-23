#ifndef VIEWER_H
#define VIEWER_H

#include "../City/City.h"
#include "../ExportObj/ExportObj.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct GlutVariables
{
	int mouseX;
	int mouseY;
	int mouseKey;
	
	int light;
	int rotate;
	double rotationSpeed;
	float alpha;
	
	float t;
	
	GLuint idCity;
	int window;
};

/* this is a viewer just with glut */
class Viewer
{
	public:
		Viewer(std::string filename, int argc, char* argv[]);
		~Viewer();
		
		void Display(City* city, int width, int height);
		void Loop();
		
	private:
		GLuint GenerateCity(City* city);
		static void CityRendering();
		static void Resize(int width, int height);
		
		static void KeyboardManager(unsigned char key, int x, int y);
		static void MouseMoveManager(int x, int y);
		static void MousePushManager(int button, int state, int x, int y);
		static void GlutIdle();
		
		
		static GlutVariables var;
		City* city;
		ExportObj* exporter;
};

#endif
