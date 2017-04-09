// Tin Huynh & Erik Kuan
//Completed December 8

#ifndef POINT_H
#define POINT_H

class Point
{
private:
	double x;
	double y;
public:
	Point();
	Point(double xx, double yy);
	~Point();
	double getX() const;
	double getY() const;
	void setX(double xx);
	void setY(double yy);
};

#endif