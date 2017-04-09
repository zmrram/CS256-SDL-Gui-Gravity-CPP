// Tin Huynh & Erik Kuan
//Completed December 8

#ifndef PARTICLE_H
#define PARTICLE_H
#include "Point.h"
class Particle
{
private:
	Point position;
	double acceleration;
	double angle;
	double radius;
	double mass;
	double xVelocity;
	double yVelocity;
public:
	Particle();
	Particle(Point p);
	Particle(Point p, double mass);
	
	~Particle();
	double getRadius() const;
	double getMass() const;
	double getAngle() const;
	double getAcceleration() const;
	double getXVel() const;
	double getYVel() const;
	void setSpeed(double xVel, double yVel);
	void setAngle(double rad);
	void setAccel(double accel);
	Point getPos() const;
	void setPos(double x, double y);
};

#endif