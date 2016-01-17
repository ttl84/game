#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle{

	public:
		Rectangle(float t, float b, float l, float r);
		float getTop();
		float getBottom();
		float getLeft();
		float getRight();

	private:
		float top;
		float bottom;
		float left;
		float right;

};

bool Intersect(Rectangle rect1, Rectangle rect2);
bool Contains(Rectangle rect, float x, float y);
#endif
