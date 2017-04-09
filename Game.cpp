// Tin Huynh & Erik Kuan
//Completed December 8

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Game.h"

Game::Game() : start(0), last(0), current(0), good(true), running(false), 
        width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT), 
        particles(std::vector<Particle>())
{
    // Seed the random number generator
    srand(time(0));
    
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        good = false;
        return;
    }
    
    // initialize SDL window
    window = SDL_CreateWindow("Gravity", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        good = false;
        return;
    }
    
    // initialize SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        good = false;
        return;
    }
    
    // initialize particle texture
    SDL_Surface* bmp = SDL_LoadBMP("particle.bmp");
    if (bmp == NULL)
    {
        good = false;
        return;
    }
    particleTexture = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
    if (particleTexture == NULL)
    {
        good = false;
        return;
    }
    
    // initialize our particles
    for (int i = 0; i < PARTICLE_COUNT; ++i)
    {
        particles.push_back(randomParticle());
    }
}

Game::~Game()
{
    if (!good)
    {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    }
    if (particleTexture != NULL)
    {
        SDL_DestroyTexture(particleTexture);
    }
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

int Game::operator()()
{
    if (!good)
    {
        return -1;
    }
    running = true;
    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    start = SDL_GetTicks();
    last = start;
    while (running) // every iteration is 1 frame
    {
        current = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            handleEvent(event);
        }
        update((current - last) / 1000.0);
        render();
        last = current;
    }
    return 0;
}

inline double distance (Particle& a, Particle& b){
	return sqrt(pow(a.getPos().getX() - b.getPos().getX(),2) + pow(a.getPos().getY() - b.getPos().getY(),2));
}

inline double angle (Particle& p, Particle& i){
	return atan2(p.getPos().getY() - i.getPos().getY(), p.getPos().getX() - i.getPos().getX());
}

void Game::update(double dt)
{
    std::cout << dt << " sec since last frame.\n";

    // Replace with your game logic!
	for(Particle& p : particles){
		for (Particle& i : particles)
		{
			if (p.getPos().getX() != i.getPos().getX() && p.getPos().getY() != i.getPos().getY())
			{
				if (distance(p,i) > p.getRadius() + i.getRadius())
				{
					double accel = G * (i.getMass()/pow(distance(p,i),2));
					p.setAccel(accel);
					p.setAngle(angle(p,i));
					double xAcceleration = p.getAcceleration() * sin(p.getAngle());
					double yAcceleration = p.getAcceleration() * cos(p.getAngle());
					double xVelocity = p.getXVel() + xAcceleration * dt;
					double yVelocity = p.getYVel() + yAcceleration * dt;
					p.setSpeed(xVelocity,yVelocity);
				}
				else {
					double p1speed = sqrt((pow(p.getXVel(),2) + pow(p.getYVel(),2)));
					double p2speed = sqrt((pow(i.getXVel(),2) + pow(i.getYVel(),2)));
					double collisonAngle = angle(p,i);
					double xVelocity = (((p1speed * cos(p.getAngle() - collisonAngle)*(p.getMass() - i.getMass()) + 
					2*i.getMass()*p2speed*cos(i.getAngle()-collisonAngle)) / p.getMass() + i.getMass()) * cos(collisonAngle) 
					+ p1speed * sin(p.getAngle() - collisonAngle) * cos(collisonAngle + (M_PI/2))) / 2e13;
					double yVelocity = (((p1speed * cos(p.getAngle() - collisonAngle)*(p.getMass() - i.getMass()) + 
					2*i.getMass()*p2speed*cos(i.getAngle()-collisonAngle)) / p.getMass() + i.getMass()) * sin(collisonAngle) 
					+ p1speed * sin(p.getAngle() - collisonAngle) * sin(collisonAngle + (M_PI/2))) / 2e13;
					p.setSpeed(xVelocity,yVelocity);
				}
			}
		}
	}
	
	for(Particle& p : particles){
		if (p.getPos().getX() - p.getRadius() < 0 || p.getPos().getX() + p.getRadius() > DEFAULT_WIDTH){
			if (p.getPos().getX() - p.getRadius() < 0){
				p.setPos(p.getRadius(),p.getPos().getY());
			}
			else{
				p.setPos(DEFAULT_WIDTH - p.getRadius(),p.getPos().getY());
			}
			p.setSpeed((-1) * p.getXVel(),p.getYVel());
		}
		if (p.getPos().getY() - p.getRadius() < 0 || p.getPos().getY() + p.getRadius() > DEFAULT_HEIGHT){
			if (p.getPos().getY() - p.getRadius() < 0){
				p.setPos(p.getPos().getX(), p.getRadius());
			}
			else{
				p.setPos(p.getPos().getX(), DEFAULT_HEIGHT - p.getRadius());
			}
			p.setSpeed(p.getXVel(),(-1) * p.getYVel());
		}
	}

	for(Particle& p : particles){
		double x = p.getPos().getX();
		double y = p.getPos().getY();
		x += p.getXVel()/2e13;
		y += p.getYVel()/2e13;
		p.setPos(x,y);
		
	}
}

void Game::render()
{
    SDL_RenderClear(renderer);
    
    // rendering here would place objects beneath the particles
    for (const Particle& p : particles)
    {
        drawParticle(p);
    }
    
    // rendering here would place objects on top of the particles
    
    SDL_RenderPresent(renderer);
}

void Game::handleEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    // Add your own event handling here if desired
    case SDL_QUIT:
        running = false;
        break;
    default:
        break;
    }
}

void Game::drawParticle(const Particle& p)
{
    SDL_Rect dst;
    double shift = p.getRadius();
    dst.x = (int) (p.getPos().getX() - shift);
    dst.y = (int) (p.getPos().getY() - shift);
    dst.w = shift * 2;
    dst.h = shift * 2;
    SDL_RenderCopy(renderer, particleTexture, NULL, &dst);
}

Particle Game::randomParticle() const
{
    Point pos(rand() % width, rand() % height);
    
    // using some percentage of the mass of Jupiter
    double mass = ((double) rand() / RAND_MAX) * 1.9e27 + 1.0;
    return Particle(pos, mass);
}