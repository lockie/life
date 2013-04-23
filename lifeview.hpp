#ifndef LIFEVIEW_HPP
#define LIFEVIEW_HPP

#include <QGraphicsView>

class LifeView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit LifeView(QWidget *parent = 0);
	
signals:
	void clicked(int x, int y);
	
public slots:
	
private:
	void mousePressEvent(QMouseEvent * e);
};

#endif // LIFEVIEW_HPP
