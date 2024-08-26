#include "camerascreencapture.h"
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPainter>

CameraScreenCapture::CameraScreenCapture(const QImage &screen, QQuickItem *parentView)
	:m_screen{screen}
{
	setParentItem(parentView);
}

void CameraScreenCapture::paint(QPainter *painter)
{
	if (painter)
	{
		QRectF rect2{x(),y(),width(),height()};
		painter->drawImage(rect2, m_screen);
	}
}

CameraScreenCapture &CameraScreenCapture::setDuration(const size_t & duration)
{
	m_duration = duration;
	return *this;
}

CameraScreenCapture &CameraScreenCapture::setOriginalPos(const QPoint & originalPos)
{
	m_originalPos = originalPos;
	return *this;
}

CameraScreenCapture* CameraScreenCapture::setFinalPos(const QPoint & finalPos)
{
	m_FinalPos = finalPos;
	return this;
}

CameraScreenCapture* CameraScreenCapture::setScale(const float &scale)
{
	m_scale = scale;
	return this;
}

void CameraScreenCapture::startAnimation()
{

	if (!m_originalPos && !m_FinalPos && !m_scale) {
		return;
	}

	QAnimationGroup* groupAnimation = nullptr;
	if ((m_originalPos || m_FinalPos) && m_scale) {
		groupAnimation = new QSequentialAnimationGroup(this);
	}

	if (groupAnimation) {
		if (m_scale) {
			QPropertyAnimation* scaleAni = new QPropertyAnimation(this, "scale", this);
			scaleAni->setDuration(1000);
			this->setTransformOrigin(QQuickItem::BottomRight);
			scaleAni->setStartValue(scale());
			scaleAni->setEndValue(*m_scale);
			groupAnimation->addAnimation(scaleAni);
		}
		// if (m_originalPos || m_FinalPos) {
		// 	QPropertyAnimation* posX = new QPropertyAnimation(this, "width", this);
		// 	QPropertyAnimation* posY = new QPropertyAnimation(this, "height", this);
		// 	posX->setDuration(2000);
		// 	posY->setDuration(2000);
		// 	posX->setEndValue(width()/3);
		// 	posY->setEndValue(height()/3);

		// 	if (m_originalPos){
		// 		posX->setStartValue(m_originalPos->x());
		// 		posY->setStartValue(m_originalPos->y());
		// 	} else {
		// 		posX->setStartValue(width());
		// 		posY->setStartValue(height());
		// 	}

		// 	QParallelAnimationGroup* parallelPos = new QParallelAnimationGroup(this);
		// 	parallelPos->addAnimation(posX);
		// 	parallelPos->addAnimation(posY);

		// 	groupAnimation->addAnimation(parallelPos);
		// }
		groupAnimation->start();
	}

}
