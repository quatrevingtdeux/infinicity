#ifndef FACE_H
#define FACE_H

class Face
{
	public:
		Face();
		Face(Vertex* tL, Vertex* bR) : topLeft(tL), bottomRight(bR) {}
		~Face();

	private:
		Vertex* topLeft;
		Vertex* bottomRight;
};

#endif