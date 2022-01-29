#include "RotationAnimation.h"

RotationAnimation::RotationAnimation(sf::Transformable* object, AnimationType at, float end_rot, int iterations)
{
	animationType = at;
	this->object = object;
	iteration = 0;
	this->iterations = iterations;
	this->end_rot = end_rot;

	ratio = (end_rot - object->getRotation()) / iterations;
}

bool RotationAnimation::iterate()
{
	if (!isFinished()) {
		if (animationType == AnimationType::LINEAR) {
			object->setRotation(object->getRotation() + ratio);
			iteration++;
			return false;
		}
		if (animationType == AnimationType::EXPONENTIAL) {
			object->setRotation(object->getRotation() * (object->getRotation() + ratio));
			iteration++;
			return false;
		}
	}
	//object->setRotation(end_rot);
	return true;
}

bool RotationAnimation::isFinished()
{
	return !(iteration < iterations);
}
