#include "dialog.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
       // QTextCodec::setCodecForTr(codec);
      //  QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForLocale(codec);


    return a.exec();
}
