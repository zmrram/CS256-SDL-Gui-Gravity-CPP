// Tin Huynh & Erik Kuan
//Completed December 8

#include "Particle.h"

Particle::Particle() : position(0, 0), mass(0), radius(0), angle(0), xVelocity(0), yVelocity(0), acceleration(0)
{
}

Particle::Particle(Point p) : position(p), mass(1), radius(1), angle(0), xVelocity(0), yVelocity(0), acceleration(0)
{
}

Particle::Particle(Point p, double x) : position(p), mass(x)
{
	radius = ((double) mass / 3e26) + 3;
	xVelocity = 0;
	yVelocity = 0;
	acceleration = 0;
	angle = 0;
}

Particle::~Particle()
{
	radius = 0;
	mass = 0;
	xVelocity = 0;
	yVelocity = 0;
	acceleration = 0;
	angle = 0;
}

double Particle::getRadius() const
{
	return radius;
}

void Particle::setPos(double x, double y){
	position.setX(x);
	position.setY(y);
}

double Particle::getMass() const{
	return mass;
}

double Particle::getAcceleration() const {
	return acceleration;
}

double Particle::getAngle() const {
	return angle;
}

double Particle::getXVel() const {
	return xVelocity;
}

double Particle::getYVel() const {
	return yVelocity;
}

void Particle::setAccel(double accel) {
	acceleration = accel;
}

void Particle::setAngle(double rad){
	angle = rad;
}

void Particle::setSpeed(double xVel, double yVel){
	xVelocity = xVel;
	yVelocity = yVel;
}
Point Particle::getPos() const
{
	return position;
}

