#ifndef VIEWER_H
#define VIEWER_H

#include "../City/City.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* this is a viewer just with glut */
class Viewer
{
	public:
		Viewer(int argc, char* argv[]);
		~Viewer();
		
		void Display(City* city, int width, int height);
		void Loop();
		
	private:
		GLuint GenerateCity();
		void CityRendering();
		void Resize(int width, int height);
		
		void KeyboardManager(unsigned char key, int x, int y);
		void MouseMoveManager(int x, int y);
		void MousePushManager(int button, int state, int x, int y);
		void GlutIdle();
		
		
		struct var
		{
			struct Mouse
			{
				int x;
				int y;
				int key;
			};
			
			GLuint idCity;
			int window;
		};
		var GlutVariables;
		
		City* city;
};

#endif
