#pragma once

#include "Animation.h"

class PositionAnimation : public Animation
{
public:
	PositionAnimation(sf::Transformable* object, AnimationType at, sf::Vector2f end_pos, int iterations);
	bool iterate();
	bool isFinished();
private:
	sf::Vector2f end_pos;
	sf::Vector2f ratio;
};

