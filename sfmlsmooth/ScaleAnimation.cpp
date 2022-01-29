#include "ScaleAnimation.h"

ScaleAnimation::ScaleAnimation(sf::Transformable* object, AnimationType at, sf::Vector2f end_scale, int iterations)
{
	animationType = at;
	this->object = object;
	iteration = 0;
	this->iterations = iterations;
	this->end_scale = end_scale;

	ratio = {
		(end_scale.x - object->getScale().x) / iterations,
		(end_scale.y - object->getScale().y) / iterations
	};
}

bool ScaleAnimation::iterate()
{
	if (!isFinished()) {
		if (animationType == AnimationType::LINEAR) {
			object->setScale(object->getScale().x + ratio.x, object->getScale().y + ratio.y);
			iteration++;
			return false;
		}
		if (animationType == AnimationType::LINEAR) {
			object->setScale(object->getScale().x + ratio.x, object->getScale().y + ratio.y);
			iteration++;
			return false;
		}
		object->setScale(end_scale);
	}
	return true;
}

bool ScaleAnimation::isFinished()
{
	return !(iteration < iterations);
}
