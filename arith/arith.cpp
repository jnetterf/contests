#include "arith.h"
#include "ui_arith.h"
#include <cstdlib>
#include <QTimer>
Arith::Arith(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Arith), s_ans(0), s_pts(0), s_accel(1)
{
    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)),this,SLOT(checkAnswer()));
    QTimer* x=new QTimer;
    connect(x,SIGNAL(timeout()),this,SLOT(losePoints()));
    x->start(2000);

    generateQuestion();
}

void Arith::generateQuestion() {
    int type = qrand()%4;

    int b = qrand()%(s_pts+1);
    int a = qrand()%(s_pts+1);
    b=!b?1:b;
    if(type==3) {   //no div...
        b=a;
        type=2;
    }
    a=type==3?a*b:a;
    ui->eqLabel->setText(QString::number(a)+QString(!type?"+":(type==1?"-":(type==2?"x":"/")))+QString::number(b));
    switch(type) {
    case 0:
        s_ans=a+b;
        break;
    case 1:
        s_ans=a-b;
        break;
    case 2:
        s_ans=a*b;
        break;
    case 3:
        s_ans=a/b;
    }
}

void Arith::checkAnswer() {
    if (ui->lineEdit->text().toInt()==s_ans) {
        ui->ptLabel->setText(QString::number(s_pts+= ++s_accel)+" points");
        generateQuestion();
        ui->lineEdit->clear();
    }
}

void Arith::losePoints() {
    if(s_pts>1) {
        if(s_accel<=0) {
            s_accel=2;
            s_pts/=2;
        }
        ui->ptLabel->setText(QString::number(s_pts-= --s_accel)+" points");
    }
}

Arith::~Arith()
{
    delete ui;
}
