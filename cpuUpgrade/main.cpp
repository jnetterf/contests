#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QTextEdit>
#include <QScrollBar>
#include <QTimer>
#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(x)
#endif

class Client : public QTextEdit {
    Q_OBJECT
    int timesLeft;
    QString log1bk,log2bk;
    QFile log1,log2;
public:
    Client() : log1("log.ipc"),log2("log2.ipc") {
        log1bk=log2bk="###";
//        setReadOnly(1);
//        setWindowTitle("QMake++");
        setText("[98%] Caching libraries...");  //lol
//        show();
        timesLeft=-1;
        startTimer(200);
        log1.open(QIODevice::WriteOnly|QIODevice::Text);    //Expensive
        log1.close();
    }
protected:
    void timerEvent(QTimerEvent *e) {
        if(timesLeft>-1) {
            if(!--timesLeft) {
                qApp->quit();
            }
        }
        log1.open(QIODevice::ReadOnly|QIODevice::Text);
        log2.open(QIODevice::ReadOnly|QIODevice::Text);
        QString log1x=log1.readAll(),log2x=log2.readAll();
        if(log1bk!="###"&&log2bk!="###"&&(log1bk!=log1x||log2bk!=log2x)) {
//            setText("COMMAND OUTPUT:\n"+log1x+"\n\nLOG OUTPUT:\n"+log2x);
            qDebug()<<"COMMAND OUTPUT:\n"+log1x+"\n\nLOG OUTPUT:\n"+log2x;
            verticalScrollBar()->setValue(verticalScrollBar()->maximum()+10);
        }
        if(log1bk!="###"&&log1bk!=log1x&&log1x.endsWith("COMMAND COMPLETED!\n\n")) {
            qApp->quit();
            timesLeft=10;
        }
        log1.close();
        log2.close();
        log1bk=log1x;
        log2bk=log2x;
    }
};

int main(int argc, char *argv[])
{
    QString command;
    for(int i=1;i<argc;i++) {
        if(i!=1) command+=" ";
        command+=QString(argv[i]);
    }
    QFile file("cpuUpgrade.ipc");
    if(command!="server") {
        QApplication x(argc,argv);
        Client showoff;

        qDebug()<<"[5%] Caching libraries...";
        while(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//            qDebug()<<"Couldn't open file for writting. I'll retry. Hang on...";
            sleep(5);
        }
        QTextStream out(&file);
        out<<QTime::currentTime().toString("HHmmss")<<"\n"<<command;
        file.close();
        return qApp->exec();
    } else {
        qDebug()<<"Started server!";
        QString prevtime="###";
        while(1) {
            while(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug()<<"Couldn't open file. I'll retry. Don't worry.";
                sleep(1);
            }
            QString newtime=file.readLine();
            newtime.chop(1);
            QString command=file.readLine();
            if(prevtime!="###"&&newtime!=prevtime) {
                QFile echo("log.ipc");
                while(!echo.open(QIODevice::Append | QIODevice::Text )) {
                    qDebug()<<"Couldn't open append file. I'll retry. Don't worry...";
                    sleep(1);
                }
                {
                    QTextStream log(&echo);
                    qDebug()<<"LOG:"<<"Recieved command "<< command<<" sent at time "<<newtime<<"\n"<<"Executing.";
                    log<<"Recieved command "<< command<<" sent at time "<<newtime<<"\n"<<"Executing.\n";
                    echo.close();
                }
                system(QString(command+" > /home/joshua/Dropbox/Coding/hathor/release/log2.ipc 2>&1").toAscii());
                {
                    echo.open(QIODevice::Append|QIODevice::Text);
                    qDebug()<<"LOG:"<<"COMMAND COMPLETED";
                    QTextStream log(&echo);
                    log<<"COMMAND COMPLETED!\n\n";
                    echo.close();
                }
            }
            prevtime=newtime;
            file.close();
            sleep(1);
        }
    }
}

#include "main.moc"
