#pragma once

#include "Animation.h"

class RotationAnimation : public Animation
{
public:
	RotationAnimation(sf::Transformable* object, AnimationType at, float end_rot, int iterations);
	bool iterate();
	bool isFinished();
private:
	float end_rot;
	float ratio;
};

