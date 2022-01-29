#pragma once

#include "Animation.h"

class ScaleAnimation : public Animation
{
public:
	ScaleAnimation(sf::Transformable* object, AnimationType at, sf::Vector2f end_scale, int iterations);
	bool iterate();
	bool isFinished();
private:
	sf::Vector2f end_scale;
	sf::Vector2f ratio;
};

