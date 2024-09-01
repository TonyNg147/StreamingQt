#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H
#include <AnimatedPaintedItem.h>

class ScreenCapture : public AnimatedPaintedItem
{
	Q_OBJECT

public:
	ScreenCapture(QQuickItem *parent);
};

#endif // SCREENCAPTURE_H
