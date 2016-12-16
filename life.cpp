
#include <QJsonArray>

#include "life.hpp"


static const int _cell_size = 10;

Life::Life(QObject *parent) :
	QObject(parent)
{
	scene = new QGraphicsScene(this);
	clear();
}

void Life::setView(QGraphicsView* view)
{
	view->setScene(scene);
}

void Life::clear()
{
	memset(lattice, 0, _width * _height * sizeof(bool));
	render();
}

void Life::read(const QJsonObject& json)
{
	Q_ASSERT(json["width"] == _width);
	if(json["width"] != _width)
		return;
	Q_ASSERT(json["height"] == _height);
	if(json["height"] != _height)
		return;

	QJsonArray l = json["lattice"].toArray();
	int counter = 0;
	for(int i = 0; i < _height; i++)
		for(int j = 0; j < _width; j++)
			lattice[i][j] = l[counter++].toBool();

	render();
}

void Life::write(QJsonObject& json) const
{
	json["width"]  = _width;
	json["height"] = _height;
	QJsonArray l;
	for(int i = 0; i < _height; i++)
		for(int j = 0; j < _width; j++)
			l.append(lattice[i][j]);
	json["lattice"] = l;
}

void Life::toggleCell(int x, int y)
{
	x /= _cell_size;
	y /= _cell_size;

	if(x >= _width)
		x = x % _width;
	if(x < 0)
		x = (x % _width) + _width;
	if(y >= _height)
		y = y % _height;
	if(y < 0)
		y = (y % _height) + _height;

	lattice[y][x] = !lattice[y][x];
	render();
}

void Life::step()
{
	bool newlattice[_height][_width];
	memcpy(newlattice, lattice, _width * _height * sizeof(bool));

	for(int i = 0; i < _height; i++)
	{
		for(int j = 0; j < _width; j++)
		{
			// count neighbours
			int nei = 0;
			for(int k = -1; k <= 1; k++)
			{
				for(int l = -1; l <= 1; l++)
				{
					if(k == 0 && l == 0)
						continue;

					int x_idx = j + l;
					int y_idx = i + k;
					
					if(x_idx < 0)
						x_idx += _width;
					if(x_idx >= _width)
						x_idx -= _width;
					if(y_idx < 0)
						y_idx += _height;
					if(y_idx >= _height)
						y_idx -= _height;

					if(lattice[y_idx][x_idx])
						nei++;
				}
			}

			// set new state
			if(lattice[i][j] && nei != 2 && nei != 3)
				newlattice[i][j] = false;
			if(!lattice[i][j] && nei == 3)
				newlattice[i][j] = true;
		}
	}
	memcpy(lattice, newlattice, sizeof(lattice));
	render();
}

void Life::render()
{
	scene->clear();
	scene->addRect(0, 0, _width * _cell_size, _height * _cell_size);
	for(int i = 0; i < _height; i++)
		for(int j = 0; j < _width; j++)
			if(lattice[i][j])
				scene->addRect(j*_cell_size, i*_cell_size,
					_cell_size, _cell_size,
					QPen(), QBrush(Qt::black));
}

