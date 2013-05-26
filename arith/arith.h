#ifndef ARITH_H
#define ARITH_H

#include <QMainWindow>

namespace Ui {
    class Arith;
}

class Arith : public QMainWindow
{
    Q_OBJECT

public:
    explicit Arith(QWidget *parent = 0);
    ~Arith();

public slots:
    void generateQuestion();
    void checkAnswer();
    void losePoints();

private:
    Ui::Arith *ui;
    int s_ans;
    int s_pts;
    int s_accel;
};

#endif // ARITH_H
