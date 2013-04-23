
#include <QMouseEvent>

#include "lifeview.hpp"


LifeView::LifeView(QWidget *parent) :
	QGraphicsView(parent)
{
}


void LifeView::mousePressEvent(QMouseEvent * e)
{
	QPointF pos = mapToScene(e->pos());
	emit clicked(pos.x(), pos.y());
}
