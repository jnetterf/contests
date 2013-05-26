#include "imainwindow.h"
#include "ui_imainwindow.h"

IMainWindow::IMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IMainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    ui->ribbon->init(ui->document);
}

IMainWindow::~IMainWindow()
{
    delete ui;
}
