// Tin Huynh & Erik Kuan
//Completed December 8

#include "Point.h"


Point::Point() : x(0), y(0)
{
}

Point::Point(double xx, double yy) : x(xx), y(yy)
{
}

double Point::getX() const
{
	return x;
}

double Point::getY() const
{
	return y;
}

void Point::setX(double xx){
	x = xx;
}

void Point::setY(double yy){
	y = yy;
}

Point::~Point()
{
	x = 0;
	y = 0;
}
