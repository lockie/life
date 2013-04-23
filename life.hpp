#ifndef LIFE_HPP
#define LIFE_HPP

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>


const int _width = 50;
const int _height = 50;

class Life : public QObject
{
Q_OBJECT

public:
	explicit Life(QObject *parent = 0);

	void setView(QGraphicsView* view);
	void clear();

public slots:
	void toggleCell(int x, int y);
	void step();

private:
	bool lattice[_height][_width];
	QGraphicsScene* scene;
	
	void render();
};

#endif // LIFE_HPP
