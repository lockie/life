#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "life.hpp"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionNew_triggered();
	
	void on_actionAbout_Qt_triggered();
	
	void on_actionStep_triggered();
	
	void on_actionRun_triggered();
	
	void on_actionStop_triggered();
	
    void on_actionOpen_triggered();
    
private:
	Ui::MainWindow *ui;
	Life* life;
	QTimer* timer;
};

#endif // MAINWINDOW_H
