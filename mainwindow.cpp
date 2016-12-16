
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>

#include "lifeview.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	LifeView* view = new LifeView(this);
	ui->gridLayout->addWidget(view);

	life = new Life(this);
	life->setView(view);
	connect(view, SIGNAL(clicked(int,int)), life, SLOT(toggleCell(int,int)));

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), life, SLOT(step()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionNew_triggered()
{
	on_actionStop_triggered();
	life->clear();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
	qApp->aboutQt();
}

void MainWindow::on_actionStep_triggered()
{
	life->step();
}

void MainWindow::on_actionRun_triggered()
{
	ui->actionStop->setEnabled(true);
	ui->actionRun->setEnabled(false);
	ui->actionStep->setEnabled(false);
	timer->start(100);
}

void MainWindow::on_actionStop_triggered()
{
	timer->stop();
	ui->actionStep->setEnabled(true);
	ui->actionRun->setEnabled(true);
	ui->actionStop->setEnabled(false);
}

void MainWindow::on_actionOpen_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this);
	if(filename.isEmpty())
		return;
	
	QFile file(filename);
	if(!file.open(QFile::ReadOnly))
	{
		QMessageBox::critical(this, tr("Error"), file.errorString());
		return;
	}

	QByteArray data = file.readAll();
	QJsonDocument document(QJsonDocument::fromJson(data));
	life->read(document.object());
}

void MainWindow::on_actionSave_triggered()
{
	QString filename = QFileDialog::getSaveFileName(this);
	if(filename.isEmpty())
		return;

	QFile file(filename);
	if(!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(this, tr("Error"), file.errorString());
		return;
	}

	QJsonObject lifeObject;
	life->write(lifeObject);
	QJsonDocument document(lifeObject);
	file.write(document.toJson());
}
