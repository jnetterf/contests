#include <QtGui/QApplication>
#include <QLabel>
#include <Qt>
#include <QPixmapCache>
#include <QFile>
#include <QDir>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QLabel* l = new QLabel;
    l->show();
//    QPixmapCache::setCacheLimit(0);
    QStringList al=QDir("/home/joshua/.local/share/data/hathorMP/").entryList();
    while(1) {
        for(int i=0;i<al.size();i++) {
            QPixmap p("/home/joshua/.local/share/data/hathorMP/"+al[i]);
            if(p.isNull()) continue;
            l->setMinimumWidth(1700);
            l->setMinimumHeight(1700);
            int max=1400;
            int oldmax=max;
            while(1) {
                max=qrand()%(max)+300;
                if(max>oldmax-300) break;
            }
            p=p.scaledToWidth(1400+300);
            //        p.fill(QColor(qrand()%255,qrand()%255,qrand()%255));
            l->setPixmap(p);
            a.processEvents();
        }
    }
    w.show();
    
}
