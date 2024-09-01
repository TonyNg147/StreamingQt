#include "animationhelper.h"
#include <QPainter>
#include <QPainterPath>

namespace {
void addSplashEffect(AnimatedPaintedItem *item)
{
	// There is no need to care about the lifycycle of the heap allocation object
	// because we used the Qt child-parent mechanism. So whenever the parent gets destroyed
	// the child will be released as well
	AnimatedPaintedItem *splashEffect = new AnimatedPaintedItem(item);
	splashEffect->setParent(item);
	splashEffect->setPaintedRoutine([splashEffect](QPainter *painter) {
		const size_t x = splashEffect->x();
		const size_t y = splashEffect->y();
		const size_t width = splashEffect->width();
		const size_t height = splashEffect->height();
		QRectF rect(x, y, width, height);
		QPainterPath path;
		path.addRoundedRect(rect, 10, 10);
		painter->fillPath(path, Qt::white);
	});
	splashEffect->setFill(item);
	splashEffect->setMargins(10);
	splashEffect->setDuration(1000);
	splashEffect->setPropertyName("opacity");
	splashEffect->setEndValue(0);
}
}; // namespace

AnimationHelper &AnimationHelper::getInstance()
{
	static AnimationHelper instance;
	return instance;
}

void AnimationHelper::attachAnimation(AnimatedPaintedItem *item, AnimationType type)
{
	if (item) {
		switch (type) {
		case AnimationType::Splash: {
			addSplashEffect(item);
			break;
		}
		default: {
			break;
		}
		}
	}
}
