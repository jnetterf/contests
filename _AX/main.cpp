#include <QtGui/QApplication>
#include "CCompleter.h"

#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QList<CompletionCase> data;
  data.push_back(CompletionCase(""));
  for(int i=0;i<2;i++) {
    data.back().push_back(Category("Category "+QString::number(i)));
    for(int j=i;j<500;j+=2){
      srandom(i*100+j);
      QString x;
      int n=(random()*100)/(j+1);
      do {
        x.push_back((char)(qAbs(n%26)+'a'));
      } while(n/=26);
      data.back()[i].push_back(x);
    }
  }

  data.push_back(CompletionCase("["));
  data.back().push_back(Category("Vectors"));
  data.back().back().push_back("f]");
  data.back().back().push_back("V1]");
  data.back().back().push_back("V2]");
  data.back().back().push_back("V3]");
  data.back().push_back(Category("Scalers"));
  data.back().back().push_back("g]");
  data.back().back().push_back("S1]");
  data.back().back().push_back("S2]");
  data.back().back().push_back("S3]");

  CCLineEdit* lineEdit = new CCLineEdit(&data);
  lineEdit->setWindowTitle("Categorical Completer");
//  CategoricalCompleter* cc=new CategoricalCompleter(lineEdit,&data);
  lineEdit->show();

  int ret = a.exec();
//  delete cc;
  delete lineEdit;
  return ret;
}
