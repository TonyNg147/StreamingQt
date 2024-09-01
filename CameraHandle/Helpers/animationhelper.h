#ifndef ANIMATIONHELPER_H
#define ANIMATIONHELPER_H

#include <AnimatedPaintedItem.h>

enum class AnimationType
{
	Splash,
	Undefined,
};

class AnimationHelper
{
private:
	AnimationHelper() = default;

public:
	static AnimationHelper &getInstance();

	void attachAnimation(AnimatedPaintedItem *item, AnimationType type);
};

#endif // ANIMATIONHELPER_H
