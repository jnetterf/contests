#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class IMainWindow;
}

class IMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IMainWindow(QWidget *parent = 0);
    ~IMainWindow();

private:
    Ui::IMainWindow *ui;
};

#endif // IMAINWINDOW_H
