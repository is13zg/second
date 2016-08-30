#include "dialog.h"
#include "ui_dialog.h"
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))




Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint|Qt::WindowSystemMenuHint|Qt::WindowCloseButtonHint|Qt::WindowCancelButtonHint);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    OBYA_text="";
     std::srand(std::time(NULL));

    config_file_name=QCoreApplication::applicationDirPath()+"/dh.config";


    QString errors="";

    if ( config_file_name != "") {
        QFile file( config_file_name);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open  config file"));
            return;
        } else {
        QTextStream in(&file);
        QString temp;
         temp=in.readAll();

      QStringList tempqsl, file_names=temp.split("\r\n");

      for (uint i = 0; i < (uint)file_names.size(); ++i){
      if (file_names.at(i).contains("Plus")) { tempqsl=file_names.at(i).split("==") ; ui->plus_word_file_string->setText(tempqsl[1]); };
      if (file_names.at(i).contains("Minus")) { tempqsl=file_names.at(i).split("==") ; ui->minus_word_file_string->setText(tempqsl[1]); };
      if (file_names.at(i).contains("Zamena")) { tempqsl=file_names.at(i).split("==") ; zamena_file_name=tempqsl[1]; };
      if (file_names.at(i).contains("file1")) { tempqsl=file_names.at(i).split("==") ; name_file1=tempqsl[1]; };
      if (file_names.at(i).contains("file2")) { tempqsl=file_names.at(i).split("==") ; name_file2=tempqsl[1]; };
      if (file_names.at(i).contains("Mystem")) { tempqsl=file_names.at(i).split("==") ; MYSTEM=tempqsl[1]; };
      if (file_names.at(i).contains("Temp")) { tempqsl=file_names.at(i).split("==") ; Tempfile=tempqsl[1]; };
      }
      if(MYSTEM.size()<3) MYSTEM=QCoreApplication::applicationDirPath()+"/mystem.exe";
      if(Tempfile.size()<3) Tempfile=QCoreApplication::applicationDirPath()+"/tempfile.txt";


        file.close(); }
    }


   // ui->minus_word_file_string->setText(QCoreApplication::applicationDirPath()+"/Minus13.txt");
    //ui->plus_word_file_string->setText(QCoreApplication::applicationDirPath()+"/Plus13.txt");

    if (ui->minus_word_file_string->text() == "") {ui->minus_word_file_string->setText(QCoreApplication::applicationDirPath()+"/Minus.txt");}
    QString fileName =ui->minus_word_file_string->text();

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                  errors+="Minus file not open!\r\n";

            } else {
            QTextStream in(&file);
            QString temp;
             temp=in.readAll();
            ui->file1_brows->setText("Минус слова константы \n"+temp);
            ui->minusBrowser->append(temp);
            minus_words=temp.split("\n",QString::SkipEmptyParts);


            file.close(); }
        } else errors+="Minus file not name!\r\n";

    if (ui->plus_word_file_string->text() == "") {ui->plus_word_file_string->setText(QCoreApplication::applicationDirPath()+"/Plus.txt");}
    fileName = ui->plus_word_file_string->text();


        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                errors+="Plus file not open!\r\n";

            } else {
            QTextStream in(&file);
            QString temp;
             temp=in.readAll();
            ui->file2_brows->setText("Плюс слова константы \n"+temp);
             ui->plusBrowser->append(temp);
            plus_words=temp.split("\n",QString::SkipEmptyParts);


            file.close(); }
        }  else errors+="Plus file not name!\r\n";


        if(name_file2=="") { name_file2=QCoreApplication::applicationDirPath()+"/f2.txt";}
        fileName=name_file2;

            if (fileName != "") {
                QFile file(fileName);
                if (!file.open(QIODevice::ReadOnly)) {
                    //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                    errors+="File2 not open!\r\n";
                } else {
                QTextStream in(&file);
                ui->file2_brows->setText(string_file2=in.readAll());
                //textEdit->setText(in.readAll());
                file.close();}
            } else errors+="File2 file not name!\r\n";

            if(name_file1=="") { name_file1=QCoreApplication::applicationDirPath()+"/f1.txt";}
            fileName=name_file1;

                if (fileName != "") {
                    QFile file(fileName);
                    if (!file.open(QIODevice::ReadOnly)) {
                        //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                        errors+="File1 not open!\r\n";
                    } else {
                    QTextStream in(&file);
                    ui->file1_brows->setText(string_file1=in.readAll());
                    //textEdit->setText(in.readAll());
                    file.close();}
                } else errors+="File1 file not name!\r\n";

                if(zamena_file_name=="") { zamena_file_name=QCoreApplication::applicationDirPath()+"/Zamena.txt";}
                fileName=zamena_file_name;

                    if (fileName != "") {
                        QFile file(fileName);
                        if (!file.open(QIODevice::ReadOnly)) {
                            //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                            errors+="Zamena file not open!\r\n";
                        } else {
                        QTextStream in(&file);
                        QString ttemp;
                        ttemp=in.readAll();
                        QStringList tt, tempqsl;
                        tempqsl=ttemp.split("\r\n");
                         for (uint i = 0; i < (uint)tempqsl.size(); i++){
                             tt=tempqsl.at(i).split("==");
                             if(tt.size()==2){
                             zam_src.push_back(tt.at(0));
                             ui->zamsrc->append(tt.at(0));
                             zam_res.push_back(tt.at(1));
                             ui->zamres->append(tt.at(1));
                             }

                         }
                        file.close();

                        }
                    } else errors+="Zamena file not name!\r\n";


                if(errors!="") QMessageBox::critical(this, tr("Error"), errors);



}
Dialog::~Dialog()
{
    delete ui;


    QString fileName=zamena_file_name;

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Zamena file not open!"));

            } else {
                QTextStream stream(&file);
                QString outstring="",tempstr;

                for (uint i = 0; i < (uint)zam_src.size(); ++i) {
                    tempstr=zam_src.at(i)+"=="+zam_res.at(i)+"\r\n";
                    outstring+=tempstr;


                }
          stream.setCodec("UTF-8");
          stream<<outstring;

          stream.flush();
          file.close();

            }
        } else QMessageBox::critical(this, tr("Error"), tr("destr: Zamena file not name!"));



}

void Dialog::on_select_file2_clicked()
{
    //QString qs=QCoreApplication::applicationDirPath()  +"C:/Users\v\Desktop\f2.txt";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/Users/Василий/Desktop/f2.txt",
                                                    tr("Text Files (*.txt);;ALL Files (*.*)"));
    name_file2=fileName;

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QTextStream in(&file);
            ui->file2_brows->setText(string_file2=in.readAll());
            //textEdit->setText(in.readAll());
            file.close();
        }
}

void Dialog::on_do_task_clicked()
{
   ui->state_brows->append("Starting task: "+QString::number(ui->select_task->currentIndex()));

   switch ( ui->select_task->currentIndex() ) {
   case 0:
      {
      ui->file1_brows->clear();
      ui->state_brows->append(ui->select_task->currentText());
      QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
      qsl.sort();

      QFile file(name_file1+"out");
              if (!file.open(QIODevice::WriteOnly)) {

              } else {
                  QTextStream stream(&file);
                  stream.setCodec("UTF-8");
                  string_file1="";
                        for (uint i = 0; i < (uint)qsl.size(); ++i)
                        string_file1+=qsl.at(i)+"\n";

                  stream<<string_file1;
                  ui->file1_brows->append(string_file1);
                  stream.flush();
                  file.close();}
   }
       break;
   case 1:
      {
      ui->file1_brows->clear();
      ui->state_brows->append(ui->select_task->currentText());
      QStringList qsl=string_file1.split(" ",QString::SkipEmptyParts);

      QFile file(name_file1+"out");
              if (!file.open(QIODevice::WriteOnly)) {

              } else {
                  QTextStream stream(&file);
                  stream.setCodec("UTF-8");
                  string_file1="";
                        for (uint i = 0; i < (uint)qsl.size(); ++i){
                        if (qsl.at(i)!="\n") string_file1+=qsl.at(i)+"\n";
                        }

                  stream<<string_file1;
                  ui->file1_brows->append(string_file1);
                  stream.flush();
                  file.close();}
   }
     break;
   case 2:
   {
   ui->file1_brows->clear();
   ui->state_brows->append(ui->select_task->currentText());

  QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
    bool ok;
   QFile file(name_file1+"out");
           if (!file.open(QIODevice::WriteOnly)) {

           } else {
               QTextStream stream(&file);
               stream.setCodec("UTF-8");
               string_file1="";
                     for (uint i = 0; i < (uint)qsl.size(); ++i)
                     { qsl.at(i).toLongLong(&ok,10);
                     if(!ok)string_file1+=qsl.at(i)+"\n";
                     }

               stream<<string_file1;
               ui->file1_brows->append(string_file1);
               stream.flush();
               file.close();}
}


     break;

   case 3:
   {
   ui->file1_brows->clear();
   ui->state_brows->append(ui->select_task->currentText()+" = "+ui->string_x->text());
   int Main_num;
   Main_num=ui->string_x->text().toInt();
   QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);

   QFile file(name_file1+"out");
           if (!file.open(QIODevice::WriteOnly)) {

           } else {
               QTextStream stream(&file);
               stream.setCodec("UTF-8");
               string_file1="";
                     for (uint i = 0; i < (uint)qsl.size(); ++i)
                     if(qsl.at(i).length()>Main_num)string_file1+=qsl.at(i)+"\n";

               stream<<string_file1;
               ui->file1_brows->append(string_file1);
               stream.flush();
               file.close();}
}

     break;


   case 4:
   {
   ui->file1_brows->clear();
   ui->file2_brows->clear();
   ui->state_brows->append(ui->select_task->currentText()+" = "+ui->string_x->text());
   int Main_num;
   Main_num=ui->string_x->text().toInt();
   QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);

   QFile file(name_file1+"out");
           if (!file.open(QIODevice::WriteOnly)) {

           } else {
               QTextStream stream(&file);
               stream.setCodec("UTF-8");
               string_file1="";
                     for (uint i = 0; i < (uint)qsl.size(); ++i) {
                     if(qsl.at(i).length()>Main_num) ui->file2_brows->append("Строка № "+QString::number(i)+" "+qsl.at(i));


                    string_file1+=qsl.at(i)+"\n";                }

               stream<<string_file1;
               ui->file1_brows->append(string_file1);
               stream.flush();
               file.close();}
}

     break;

   case 5:
   {
       ui->file1_brows->clear();
       ui->file2_brows->clear();
       ui->state_brows->append(ui->select_task->currentText());
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
       qsl.sort();
       QString duplicates="";

       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                   string_file1+=qsl.at(0)+"\n";
                         for (uint i = 1; i < (uint)qsl.size(); ++i)
                         if(qsl.at(i-1)!=qsl.at(i)) string_file1+=qsl.at(i)+"\n";
                         else { duplicates+=qsl.at(i)+"\n";}

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                    ui->file2_brows->append(duplicates);
                   stream.flush();
                   file.close();}
               QFile file2(name_file1+"dup");
                       if (!file2.open(QIODevice::WriteOnly)) {

                       } else {
                           QTextStream stream(&file2);
                           stream.setCodec("UTF-8");
                           stream<<duplicates;
                           stream.flush();
                           file2.close();}
}

     break;


   case 6:
   {
       // добавляем строку в  конец
       ui->file1_brows->clear();

       ui->state_brows->append(ui->select_task->currentText()+" = "+ui->string_x->text());
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
        QString temp;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)qsl.size(); ++i) {
                             temp=qsl.at(i);

                                //temp.remove(temp.length()-1,1);

                         if(temp.at(temp.length()-1)=='\r') temp.remove(temp.length()-1,1);
                         if(temp.at(temp.length()-1)=='\n') temp.remove(temp.length()-1,1);
                         if(temp.at(temp.length()-1)=='\r') temp.remove(temp.length()-1,1);
                         if(!temp.isEmpty()) string_file1+=temp+ui->string_x->text()+"\n";
                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   stream.flush();
                   file.close();}
}

     break;

   case 7:
   {
       ui->file1_brows->clear();
       ui->state_brows->append(ui->select_task->currentText());
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
       QStringList qsl2=string_file2.split("\n",QString::SkipEmptyParts);
        bool flag;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)qsl.size(); ++i) {
                             flag=true;
                              for (uint j = 0; j < (uint)qsl2.size(); ++j)
                              if (qsl.at(i)==qsl2.at(j)) {flag=false; break; }

                           if (flag) string_file1+=qsl.at(i)+"\n";

                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   stream.flush();
                   file.close();}
}

     break;

   case 8:
   {
       ui->file1_brows->clear();
        ui->state_brows->append(ui->select_task->currentText()+" = "+ui->string_x->text());
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts), qsl2=ui->string_x->text().split(" ",QString::SkipEmptyParts);
       bool flag;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)qsl.size(); ++i) {
                             flag=true;
                              for (uint j = 0; j < (uint)qsl2.size(); ++j)
                              if (qsl.at(i).contains(qsl2.at(j),Qt::CaseInsensitive)==true) {flag=false; break; }

                           if (flag) string_file1+=qsl.at(i)+"\n";

                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   stream.flush();
                   file.close();}
}

     break;

   case 9:
   {
       ui->file1_brows->clear();
        ui->state_brows->append(ui->select_task->currentText());
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
         QString temp;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)qsl.size(); ++i) {
                             temp=qsl.at(i);
                             temp[0]=qsl.at(i).at(0).toUpper();

                                string_file1+=temp+"\n";

                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   stream.flush();
                   file.close();}
}

     break;


   case 10:
   {
       ui->file1_brows->clear();
        ui->state_brows->append(ui->select_task->currentText());
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
         QString temp;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)qsl.size(); ++i) {
                             temp=qsl.at(i);
                             int j=0;
                             while(j<temp.length())
                             {
                                 if(temp[j].isDigit()) temp.remove(j,1);
                                 else j++;
                             }

                                string_file1+=temp+"\n";

                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   stream.flush();
                   file.close();}
}

     break;

   case 11:
   {
       ui->file1_brows->clear();
        ui->state_brows->append(ui->select_task->currentText());
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
         QString temp;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)qsl.size(); ++i) {
                             temp=qsl.at(i);

                             while(temp.contains(ui->string_x->text(),Qt::CaseInsensitive))
                             temp.remove(temp.indexOf(ui->string_x->text(),Qt::CaseInsensitive),ui->string_x->text().length());

                                string_file1+=temp+"\n";

                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   stream.flush();
                   file.close();}
}

     break;

   case 12:
   {
       ui->file1_brows->clear();
       ui->file2_brows->clear();
       ui->state_brows->append(ui->select_task->currentText());
       normal_string_file1=get_normal(string_file1);
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts), nqsl=normal_string_file1.split("\n",QString::SkipEmptyParts) ;


        for (uint i = 0; i < (uint)nqsl.size(); ++i){
         QStringList tqsl=nqsl.at(i).split(" ",QString::SkipEmptyParts);
         tqsl.sort();
         QString tqs=tqsl.at(0);

                for (uint j = 1; j < (uint)tqsl.size(); ++j){
                   if(tqsl.at(j).length()>2) tqs+=" "+tqsl.at(j);
                }
         nqsl[i]=tqs;
        }

       bool flag;
       QString duplicates="",temp;

       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";

                         for (uint i = 0; i < (uint)nqsl.size(); ++i){
                             flag=true;
                             temp=nqsl.at(i); temp.remove(temp.length()-1,1);
                             for(uint j=i+1; j<(uint)nqsl.size()-1; j++) {
                               if(nqsl.at(j).length()>Max(ui->string_x->text().toInt(),3))
                               {

                                 if(nqsl.at(j)==temp) {flag=false;  break;}

                               }

                             }
                             if (flag)   string_file1+=qsl.at(i)+"\n";
                         else { duplicates+=qsl.at(i)+"\n";}
                        }
                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                    ui->file2_brows->append(duplicates);
                   stream.flush();
                   file.close();}
               QFile file2(name_file1+"dup");
                       if (!file2.open(QIODevice::WriteOnly)) {

                       } else {
                           QTextStream stream(&file2);
                           stream.setCodec("UTF-8");
                           stream<<duplicates;
                           stream.flush();
                           file2.close();}
}

     break;


   case 13:
   {
       ui->file1_brows->clear();
       ui->file2_brows->clear();
       ui->state_brows->append(ui->select_task->currentText());

       QString temps, temp2;
       temps=string_file1;
       string_file1=string_file2;

       //1 слово в строке
       ui->select_task->setCurrentIndex(1);
       on_do_task_clicked();

       //Удалить вхождение непонятного символа
       ui->string_x->setText("	");
       ui->select_task->setCurrentIndex(11);
       on_do_task_clicked();

       //Удалить вхождение непонятного символа
       ui->string_x->setText("+");
       ui->select_task->setCurrentIndex(11);
       on_do_task_clicked();



       //добавить плюс слова
       temp2="";
       for(uint i=0; i<(uint)plus_words.size(); i++)
           temp2+=plus_words.at(i)+"\n";
       string_file1+=temp2;

       // сортировка
       ui->select_task->setCurrentIndex(0);
       on_do_task_clicked();

       // строгое дублирование
       ui->select_task->setCurrentIndex(5);
       on_do_task_clicked();


       string_file1=get_normal(string_file1);

       // сортировка
       ui->select_task->setCurrentIndex(0);
       on_do_task_clicked();

       // строгое дублирование
       ui->select_task->setCurrentIndex(5);
       on_do_task_clicked();



       //пермена строка
       ui->state_brows->append("Перемена строк");
       string_file2=string_file1;
       string_file1=temps;


       //1 слово в строке
       ui->select_task->setCurrentIndex(1);
       on_do_task_clicked();

       //Удалить вхождение непонятного символа
       ui->string_x->setText("	");
       ui->select_task->setCurrentIndex(11);
       on_do_task_clicked();

       //Удалить вхождение непонятного символа
       ui->string_x->setText("+");
       ui->select_task->setCurrentIndex(11);
       on_do_task_clicked();




       //добавить минус слова
       temp2="";
       for(uint i=0; i<(uint)minus_words.size(); i++)
           temp2+=minus_words.at(i)+"\n";
       string_file1+=temp2;

       // сортировка
       ui->select_task->setCurrentIndex(0);
       on_do_task_clicked();

       // строгое дублирование
       ui->select_task->setCurrentIndex(5);
       on_do_task_clicked();


       string_file1=get_normal(string_file1);

       // сортировка
       ui->select_task->setCurrentIndex(0);
       on_do_task_clicked();

       // строгое дублирование
       ui->select_task->setCurrentIndex(5);
       on_do_task_clicked();

       // Ф1-ф2
       ui->select_task->setCurrentIndex(14);
       on_do_task_clicked();

       // нестрогое дублирование длинна 3 осталась
       ui->select_task->setCurrentIndex(12);
       on_do_task_clicked();



}

     break;

   case 14:
   {
       ui->file1_brows->clear();
       ui->file2_brows->clear();
       ui->state_brows->append(ui->select_task->currentText());
       normal_string_file1=get_normal(string_file1);
       normal_string_file2=get_normal(string_file2);
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
       QStringList qsl2=string_file2.split("\n",QString::SkipEmptyParts);

       QStringList nqsl=normal_string_file1.split("\n",QString::SkipEmptyParts);
       QStringList nqsl2=normal_string_file2.split("\n",QString::SkipEmptyParts);

       // сортировка по алфавиту внутри каждого словосочетания и выбор всех слов длинной больше чем 2
       for (uint i = 0; i < (uint)nqsl.size(); ++i){
        QStringList tqsl=nqsl.at(i).split(" ",QString::SkipEmptyParts);
        tqsl.sort();
        QString tqs=tqsl.at(0);

               for (uint j = 1; j < (uint)tqsl.size(); ++j){
                  if(tqsl.at(j).length()>2) tqs+=" "+tqsl.at(j);
               }
        nqsl[i]=tqs;
       }
         // сортировка по алфавиту внутри каждого словосочетания и выбор всех слов длинной больше чем 2
       for (uint i = 0; i < (uint)nqsl2.size(); ++i){
        QStringList tqsl=nqsl2.at(i).split(" ",QString::SkipEmptyParts);
        tqsl.sort();
        QString tqs=tqsl.at(0);

               for (uint j = 1; j < (uint)tqsl.size(); ++j){
                  if(tqsl.at(j).length()>2) tqs+=" "+tqsl.at(j);
               }
        nqsl2[i]=tqs;
       }

       nqsl.sort(); nqsl2.sort();

       nqsl.removeDuplicates(); nqsl2.removeDuplicates();

        bool flag;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)nqsl.size(); ++i) {
                             flag=true;
                              for (uint j = 0; j < (uint)nqsl2.size(); ++j)
                              if (nqsl.at(i)==nqsl2.at(j)) {flag=false; break; }

                           if (flag) string_file1+=nqsl.at(i)+"\n";

                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   ui->file2_brows->append(string_file2);
                   stream.flush();
                   file.close();}
}

     break;

    //Заголовок по ключас
   case 15:
   {
       ui->file1_brows->clear();
       ui->file2_brows->clear();
       ui->state_brows->append(ui->select_task->currentText());

       QString temps, temp2;
       temps=string_file1;






       //Удалить вхождение непонятного символа
       ui->string_x->setText("	");
       ui->select_task->setCurrentIndex(11);
       on_do_task_clicked();

       //Удалить плюсы
       ui->string_x->setText("+");
       ui->select_task->setCurrentIndex(11);
       on_do_task_clicked();

       // сделать заглавной
       ui->select_task->setCurrentIndex(9);
       on_do_task_clicked();


       //добавить слово если есть место и его нет
       temp2=ui->geoline->text();


       QStringList geolist=temp2.split(" ",QString::SkipEmptyParts), ngeolist=get_normal(temp2).split(" ",QString::SkipEmptyParts);
       ui->state_brows->append(ui->select_task->currentText()+" = "+ui->string_x->text());
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);

        ui->file1_brows->clear();
       qSort(geolist.begin(), geolist.end(), MyLessThan);
        QString temp;
        bool ok,add;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)qsl.size(); ++i) {
                             temp=qsl.at(i);
                             add=false;
                           /*  nott=false;

                             QString tttemp=get_normal(temp);
                             for (uint j = 0; j < (uint)ngeolist.size(); ++j) {
                                if(tttemp.contains(ngeolist.at(j))) {nott=true; break;}
                             }*/

                             if(temp.at(temp.length()-1)=='\r') temp.remove(temp.length()-1,1);
                             if(temp.at(temp.length()-1)=='\n') temp.remove(temp.length()-1,1);
                             if(temp.at(temp.length()-1)=='\r') temp.remove(temp.length()-1,1);

                            // if(nott) {  if(temp.length()+1<=ui->zag_len->text().toInt(&ok)) qsl[i]=temp+"!"; string_file1+=qsl.at(i)+"\n"; break;}
                             for (uint j = 0; j < (uint)geolist.size(); ++j) {

                             if(temp.length()+geolist.at(j).length()+2<=ui->zag_len->text().toInt(&ok)) {qsl[i]=temp+" "+geolist.at(j)+"!"; add=true; break; }
                             if(temp.length()+geolist.at(j).length()+1<=ui->zag_len->text().toInt(&ok)) {qsl[i]=temp+" "+geolist.at(j); add=true; break; }
                             }
                            if(add) {add=false; string_file1+=qsl.at(i)+"\n"; continue;} else { if(temp.length()+1<=ui->zag_len->text().toInt(&ok)) qsl[i]=temp+"!"; string_file1+=qsl.at(i)+"\n"; }


                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   stream.flush();
                   file.close();}








}

     break;



   case 16:
   {
       ui->file1_brows->clear();

       ui->state_brows->append(ui->select_task->currentText());
       QString temp;



                temp=ui->actionline->text();
               QStringList actionlist=temp.split(" ",QString::SkipEmptyParts);
                int  length_action_list=(uint)actionlist.size();
                for (uint i = 0; i < (uint)length_action_list; ++i) {
                    temp=actionlist.at(i);
                    actionlist.append(temp.remove(temp.length()-1,1));
                }


               ui->state_brows->append(ui->select_task->currentText()+" = "+ui->string_x->text());
               QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);

                ui->file1_brows->clear();
               qSort(actionlist.begin(), actionlist.end(), MyMoreThan);

                bool ok;
               QFile file(name_file1+"out");
                       if (!file.open(QIODevice::WriteOnly)) {

                       } else {
                           QTextStream stream(&file);
                           stream.setCodec("UTF-8");
                           string_file1="";
                                 for (uint i = 0; i < (uint)qsl.size(); ++i) {
                                     temp=qsl.at(i);

                                 // проверка на содержание слова континю


                                     if(temp.at(temp.length()-1)=='\r') temp.remove(temp.length()-1,1);
                                     if(temp.at(temp.length()-1)=='\n') temp.remove(temp.length()-1,1);
                                     if(temp.at(temp.length()-1)=='\r') temp.remove(temp.length()-1,1);

                                     for (uint j = 0; j < (uint)actionlist.size(); ++j) {
                                     if(temp.length()+actionlist.at(j).length()+1<=ui->zag_len->text().toInt(&ok)) {qsl[i]=temp+" "+actionlist.at(j);  }
                                     }
                                     string_file1+=qsl.at(i)+"\n";

                                 }

                           stream<<string_file1;
                           ui->file1_brows->append(string_file1);
                           stream.flush();
                           file.close();}






}

     break;


   case 17:
   {
       ui->file1_brows->clear();

       ui->state_brows->append(ui->select_task->currentText());
       QString temp;

       temp=string_file1;

       //Удалить +
       ui->string_x->setText("+");
       ui->select_task->setCurrentIndex(11);
       on_do_task_clicked();


             //записать в файл стринг1
       zapisat_v_fail(name_file1+"out",string_file1);

                // подать на вход
        QString line=" -cdl ";
        QProcess process;
         process.start(MYSTEM+line+ name_file1+"out" + " " +Tempfile );
         process.waitForFinished(-1);


                //забрать стринг1 из файла
         normal_string_file1=chitat_fail(Tempfile);

         string_file1=normal_string_file1;

         //Удалить ?
                  ui->string_x->setText("?");
                  ui->select_task->setCurrentIndex(11);
                  on_do_task_clicked();


       //Удалить {
         ui->string_x->setText("{");
         ui->select_task->setCurrentIndex(11);
         on_do_task_clicked();






         //Удалить }
         ui->string_x->setText("}");
         ui->select_task->setCurrentIndex(11);
         on_do_task_clicked();

                // отобрзаить
         zapisat_v_fail(name_file1+"out",string_file1);
          normal_string_file1=string_file1;
          string_file1=temp;




}
       break;


   case 18:
   {
       ui->file1_brows->clear();
       ui->file2_brows->clear();
       ui->state_brows->append(ui->select_task->currentText());
       normal_string_file1=get_normal(string_file1);
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts), nqsl=normal_string_file1.split("\n",QString::SkipEmptyParts) ;


        for (uint i = 0; i < (uint)nqsl.size(); ++i){
         QStringList tqsl=nqsl.at(i).split(" ",QString::SkipEmptyParts);
         tqsl.sort();
         QString tqs=tqsl.at(0);

                for (uint j = 1; j < (uint)tqsl.size(); ++j){
                   if(tqsl.at(j).length()>2) tqs+=" "+tqsl.at(j);
                }
         nqsl[i]=tqs;
        }

       bool flag;
       QString duplicates="",temp;

       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";

                         for (uint i = 0; i < (uint)nqsl.size(); ++i){
                             flag=true;
                             temp=nqsl.at(i); temp.remove(temp.length()-1,1);
                             for(uint j=i+1; j<(uint)nqsl.size()-1; j++) {
                               if(nqsl.at(j).length()>Max(ui->string_x->text().toInt(),3))
                               {

                                 if(nqsl.at(j).contains(temp)) {flag=false;  break;}

                               }

                             }
                             if (flag)   string_file1+=qsl.at(i)+"\n";
                         else { duplicates+=qsl.at(i)+"\n";}
                        }
                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                    ui->file2_brows->append(duplicates);
                   stream.flush();
                   file.close();}
               QFile file2(name_file1+"dup");
                       if (!file2.open(QIODevice::WriteOnly)) {

                       } else {
                           QTextStream stream(&file2);
                           stream.setCodec("UTF-8");
                           stream<<duplicates;
                           stream.flush();
                           file2.close();}
}

     break;

   case 19:
   {
       ui->file1_brows->clear();
       ui->file2_brows->clear();
       ui->state_brows->append(ui->select_task->currentText());
       normal_string_file1=get_normal2(string_file1);
       normal_string_file2=get_normal2(string_file2);
       QStringList qsl=string_file1.split("\n",QString::SkipEmptyParts);
       QStringList qsl2=string_file2.split("\n",QString::SkipEmptyParts);

       QStringList nqsl=normal_string_file1.split("\n",QString::SkipEmptyParts);
       QStringList nqsl2=normal_string_file2.split("\n",QString::SkipEmptyParts);

       QString qs;

       // сортировка по алфавиту внутри каждого словосочетания
       for (uint i = 0; i < (uint)nqsl.size(); ++i){
           qs=nqsl.at(i);

           if(qs.at(qs.length()-1)=='\r') qs.remove(qs.length()-1,1);
           if(qs.at(qs.length()-1)=='\n') qs.remove(qs.length()-1,1);
           if(qs.at(qs.length()-1)=='\r') qs.remove(qs.length()-1,1);

          nqsl[i]=qs;

        QStringList tqsl=nqsl.at(i).split(" ",QString::SkipEmptyParts);
        tqsl.sort();


        QString tqs=tqsl.at(0);
        for (uint j = 1; j < (uint)tqsl.size(); ++j){
            tqs+=" "+tqsl.at(j);
        }


        nqsl[i]=tqs;
       }
         // сортировка по алфавиту внутри каждого словосочетания
       for (uint i = 0; i < (uint)nqsl2.size(); ++i){

           qs=nqsl2.at(i);

           if(qs.at(qs.length()-1)=='\r') qs.remove(qs.length()-1,1);
           if(qs.at(qs.length()-1)=='\n') qs.remove(qs.length()-1,1);
           if(qs.at(qs.length()-1)=='\r') qs.remove(qs.length()-1,1);

          nqsl2[i]=qs;

        QStringList tqsl=nqsl2.at(i).split(" ",QString::SkipEmptyParts);
        tqsl.sort();
        QString tqs=tqsl.at(0);

        for (uint j = 1; j < (uint)tqsl.size(); ++j){
            tqs+=" "+tqsl.at(j);
        }


        nqsl2[i]=tqs;
       }



        bool flag;
       QFile file(name_file1+"out");
               if (!file.open(QIODevice::WriteOnly)) {

               } else {
                   QTextStream stream(&file);
                   stream.setCodec("UTF-8");
                   string_file1="";
                         for (uint i = 0; i < (uint)nqsl.size(); ++i) {
                             flag=true;
                              for (uint j = 0; j < (uint)nqsl2.size(); ++j)
                              if (nqsl.at(i)==nqsl2.at(j)) {flag=false; break; }

                           if (flag) string_file1+=qsl.at(i)+"\n";

                         }

                   stream<<string_file1;
                   ui->file1_brows->append(string_file1);
                   ui->file2_brows->append(string_file2);
                   stream.flush();
                   file.close();}
}

     break;


   default:
 ui->state_brows->append("DEFAULT! task is: "+QString::number(ui->select_task->currentIndex()));
     break;
   }
   ui->state_brows->append("End task: "+QString::number(ui->select_task->currentIndex()));
}

void Dialog::on_select_file1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/Users/Василий/Desktop/f1.txt",
                                                    tr("Text Files (*.txt);;ALL Files (*.*)"));
    name_file1=fileName;

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QTextStream in(&file);
            ui->file1_brows->setText(string_file1=in.readAll().toUtf8());
            //textEdit->setText(in.readAll());
            file.close();
        }
}

void Dialog::on_clear_fb1_clicked()
{
   ui->file1_brows->clear();
}

void Dialog::on_clear_fb2_clicked()
{
   ui->file2_brows->clear();
}


void Dialog::on_minus_word_select_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QCoreApplication::applicationDirPath()+"/Minus13.txt",
                                                    tr("Text Files (*.txt);;ALL Files (*.*)"));
    ui->minus_word_file_string->setText(fileName);

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QTextStream in(&file);
            QString temp;
            temp=in.readAll();
            ui->file1_brows->setText("Минус слова константы \n"+temp);
            minus_words=temp.split("\n");

            file.close();
        }
}

void Dialog::on_plus_word_select_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QCoreApplication::applicationDirPath()+"/Plus13.txt",
                                                    tr("Text Files (*.txt);;ALL Files (*.*)"));
    ui->plus_word_file_string->setText(fileName);

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QTextStream in(&file);
            QString temp;
             temp=in.readAll();
            ui->file2_brows->setText("Плюс слова константы \n"+temp);
            plus_words=temp.split("\n");
            ui->file2_brows->append("plusword length "+QString::number(plus_words.size()));
            file.close();
        }
}



int Dialog::perezapisati1v2(QString filename1, QString filename2)
{

    QString temp;
        if (filename1 != "") {
            QFile file(filename1);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open read file while rewriting"));
                return -1;
            } else {
            QTextStream in(&file);

             temp=in.readAll();



            file.close(); }
        } else  {QMessageBox::critical(this, tr("Error"), tr("Could not open read file while rewriting, no file name"));
            return -3;}





        if (filename2 != "") {
            QFile file(filename2);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open write file while rewriting"));
                return -2;
            } else {
            QTextStream out(&file);
            out<<temp;
            out.flush();
            file.close(); }
        } else  {QMessageBox::critical(this, tr("Error"), tr("Could not open write file while rewriting, no file name"));
            return -3;}
        return 1;
}

int Dialog::zapisat_v_fail(QString filename, QString src_string)
{





        if (filename != "") {
            QFile file(filename);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open write file while writing"));
                return -2;
            } else {
            QTextStream out(&file);
            out<<src_string;
            out.flush();
            file.close(); }
        } else  {QMessageBox::critical(this, tr("Error"), tr("Could not open write file while writing, no file name"));
            return -3;}
        return 1;

}

QString Dialog::chitat_fail(QString filename)
{
    QString temp;
        if (filename != "") {
            QFile file(filename);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open read file while reading"));
                return "";
            } else {
            QTextStream in(&file);

             temp=in.readAll();



            file.close();
            return temp;}
        } else  {QMessageBox::critical(this, tr("Error"), tr("Could not open read file while reading, no file name"));
            return "";}
}

QString Dialog::get_normal(QString qs)
{



          //записать в файл стринг1
    zapisat_v_fail(name_file1+"temp",qs);

             // подать на вход
     QString line=" -cdl ";
     QProcess process;
      process.start(MYSTEM+line+ name_file1+"temp" + " " +Tempfile );
      process.waitForFinished(-1);


             //забрать стринг1 из файла
      qs=chitat_fail(Tempfile);



      qs.replace("+"," ");
      qs.replace("-"," ");
      qs.replace("!"," ");
      qs.replace("?"," ");
      qs.replace("."," ");
      qs.replace("_"," ");
      qs.replace("{"," ");
      qs.replace("}"," ");
      qs.replace("  "," ");

      if(qs.at(qs.length()-1)=='\r') qs.remove(qs.length()-1,1);
      if(qs.at(qs.length()-1)=='\n') qs.remove(qs.length()-1,1);
      if(qs.at(qs.length()-1)=='\r') qs.remove(qs.length()-1,1);
      return qs;


}

QString Dialog::get_normal2(QString qs)
{
    //записать в файл стринг1
zapisat_v_fail(name_file1+"temp",qs);

       // подать на вход
QString line=" -cdl ";
QProcess process;
process.start(MYSTEM+line+ name_file1+"temp" + " " +Tempfile );
process.waitForFinished(-1);


       //забрать стринг1 из файла
qs=chitat_fail(Tempfile);




qs.replace("-"," ");
qs.replace("!"," ");
qs.replace("?"," ");
qs.replace("."," ");
qs.replace("_"," ");
qs.replace("{"," ");
qs.replace("}"," ");
qs.replace("  "," ");

if(qs.at(qs.length()-1)=='\r') qs.remove(qs.length()-1,1);
if(qs.at(qs.length()-1)=='\n') qs.remove(qs.length()-1,1);
if(qs.at(qs.length()-1)=='\r') qs.remove(qs.length()-1,1);
return qs;

}




int Dialog::podshet_sootvetstvia(QString str1, QString str2, int min_dlinna_slova=2)
{
    QStringList qsl1=str1.split(" ",QString::SkipEmptyParts);
    QStringList qsl2=str2.split(" ",QString::SkipEmptyParts);

    for (uint i = 0; i < (uint)qsl1.size(); ++i)
    if (qsl1.at(i).length()<min_dlinna_slova) qsl1.removeAt(i);


    for (uint i = 0; i < (uint)qsl2.size(); ++i)
    if (qsl2.at(i).length()<min_dlinna_slova) qsl2.removeAt(i);

    int sootvetstvie=0;

     for (uint i = 0; i < (uint)qsl1.size(); ++i)
           for (uint j = 0; j < (uint)qsl2.size(); ++j){
        if (qsl1.at(i).contains(qsl2.at(j)) or  qsl2.at(j).contains(qsl1.at(i))) {sootvetstvie++;}
     }

     return sootvetstvie;
}


void Dialog::on_do_tab2_clicked()
{

 if(OBYA_text=="") {ui->obyaBrowser->append("NO OBYAVLENii"); return;}

/*
    QString line=" -cdl ";
    QProcess process;
      process.start(MYSTEM+line+ name_file1 + " " +Tempfile );
      process.waitForFinished(-1);
      return;
*/

   normal_string_file1=get_normal(string_file1);
   QString normal_obya, temp, result="";
   int max=0;



   normal_obya=get_normal(OBYA_text);
   QStringList qsl,qslobya,qslobyastart, qslsel;


   qsl=normal_string_file1.split("\n",QString::SkipEmptyParts);
   qslobya=normal_obya.split("\n",QString::SkipEmptyParts);
   qslobyastart=OBYA_text.split("\n",QString::SkipEmptyParts);

   for (uint i = 0; i < (uint)qsl.size(); ++i)
   { max=0;
       qslsel.clear();
       qslsel.append(qslobyastart.at(0));

         for (uint j = 0; j < (uint)qslobya.size(); ++j){
             int tempint=podshet_sootvetstvia(qsl.at(i),qslobya.at(j));
             if( max<tempint) { max=tempint; qslsel.clear(); qslsel.append(qslobyastart.at(j)); }
             else if(max==tempint) {qslsel.append(qslobyastart.at(j)); }
         }

         //temp+='\n';
     result+=qslsel.at(std::rand()%qslsel.size())+'\n';
   }
    ui->file2_brows->clear();
    ui->file2_brows->append(result);
    zapisat_v_fail(name_file1+"out",result);
}

void Dialog::on_add_zam_clicked()
{
    QStringList tt;

if(!ui->zamtext->text().contains("==")) {QMessageBox::critical(this, tr("Error"), tr("USE ==")); return;}
         tt=ui->zamtext->text().split("==");
         if(tt.size()==2){
         zam_src.push_back(tt.at(0));
         ui->zamsrc->append(tt.at(0));
         zam_res.push_back(tt.at(1));
         ui->zamres->append(tt.at(1));
         }
ui->zamtext->clear();

}

void Dialog::on_do_zamena_clicked()
{
    ui->file1_brows->clear();
     ui->state_brows->append("СуперЗамена");
        int mcount=0;

    QFile file(name_file1+"out");
            if (!file.open(QIODevice::WriteOnly)) {

            } else {
                QTextStream stream(&file);


                      for (uint i = 0; i < (uint)zam_src.size(); ++i) {


                        while(string_file1.contains(zam_src.at(i))) {
                            string_file1.replace(zam_src.at(i),zam_res.at(i));
                        mcount++;}


                      }
                stream.setCodec("UTF-8");
                stream<<string_file1;
                ui->file1_brows->append(string_file1);
                stream.flush();
                file.close();}
            ui->state_brows->append("СуперЗамена закончилась! Всего использовано: "+QString::number(mcount));
}



void Dialog::on_clear_obya_clicked()
{
    ui->obyaBrowser->clear();
    OBYA_text="";
}

void Dialog::on_pushButton_clicked()
{
    if(ui->obyaline->text()=="") return;
    if(ui->obyaline->text().length()>ui->obya_length->value()) {ui->obya_label->setText("Too Long"); return;}
    OBYA_text+=ui->obyaline->text()+"\n";
    ui->obyaBrowser->append(ui->obyaline->text());
    ui->obyaline->clear();
}

void Dialog::on_obyaline_textChanged()
{
    ui->obya_label->clear();
    ui->ob_len_lab->setText(QString::number(ui->obyaline->text().length()));
    return;
}

void Dialog::on_addminus_clicked()
{
    QStringList qsl=ui->plus_minus_line->text().split(" ",QString::SkipEmptyParts);
     for (uint i = 0; i < (uint)qsl.size(); ++i)
     {
         minus_words.append(qsl.at(i));
     }
     ui->minusBrowser->clear();

     QString temp="";
     for (uint i = 0; i < (uint)minus_words.size(); ++i)
     {
         temp+=minus_words.at(i)+"\n";
     }
    ui->minusBrowser->append(temp);
    zapisat_v_fail(ui->minus_word_file_string->text(),temp);
    ui->plus_minus_line->clear();
}

void Dialog::on_addplus_clicked()
{

    QStringList qsl=ui->plus_minus_line->text().split(" ",QString::SkipEmptyParts);
     for (uint i = 0; i < (uint)qsl.size(); ++i)
     {
         plus_words.append(qsl.at(i));
     }
     ui->plusBrowser->clear();

     QString temp="";
     for (uint i = 0; i < (uint)plus_words.size(); ++i)
     {
         temp+=plus_words.at(i)+"\n";
     }
    ui->plusBrowser->append(temp);
    zapisat_v_fail(ui->plus_word_file_string->text(),temp);

    ui->plus_minus_line->clear();

}

void Dialog::on_clear_plus_clicked()
{
    ui->plusBrowser->clear();
}

void Dialog::on_clear_minus_clicked()
{
    ui->minusBrowser->clear();
}

void Dialog::on_reloading_clicked()
{
    config_file_name=QCoreApplication::applicationDirPath()+"/dh.config";


    QString errors="";

    if ( config_file_name != "") {
        QFile file( config_file_name);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open  config file"));
            return;
        } else {
        QTextStream in(&file);
        QString temp;
         temp=in.readAll();

      QStringList tempqsl, file_names=temp.split("\r\n");

      for (uint i = 0; i < (uint)file_names.size(); ++i){
      if (file_names.at(i).contains("Plus")) { tempqsl=file_names.at(i).split("==") ; ui->plus_word_file_string->setText(tempqsl[1]); };
      if (file_names.at(i).contains("Minus")) { tempqsl=file_names.at(i).split("==") ; ui->minus_word_file_string->setText(tempqsl[1]); };
      if (file_names.at(i).contains("Zamena")) { tempqsl=file_names.at(i).split("==") ; zamena_file_name=tempqsl[1]; };
      if (file_names.at(i).contains("file1")) { tempqsl=file_names.at(i).split("==") ; name_file1=tempqsl[1]; };
      if (file_names.at(i).contains("file2")) { tempqsl=file_names.at(i).split("==") ; name_file2=tempqsl[1]; };
      if (file_names.at(i).contains("Mystem")) { tempqsl=file_names.at(i).split("==") ; MYSTEM=tempqsl[1]; };
      if (file_names.at(i).contains("Temp")) { tempqsl=file_names.at(i).split("==") ; Tempfile=tempqsl[1]; };
      }
      if(MYSTEM.size()<3) MYSTEM=QCoreApplication::applicationDirPath()+"/mystem.exe";
      if(Tempfile.size()<3) Tempfile=QCoreApplication::applicationDirPath()+"/tempfile.txt";


        file.close(); }
    }


   // ui->minus_word_file_string->setText(QCoreApplication::applicationDirPath()+"/Minus13.txt");
    //ui->plus_word_file_string->setText(QCoreApplication::applicationDirPath()+"/Plus13.txt");

    if (ui->minus_word_file_string->text() == "") {ui->minus_word_file_string->setText(QCoreApplication::applicationDirPath()+"/Minus.txt");}
    QString fileName =ui->minus_word_file_string->text();

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                  errors+="Minus file not open!\r\n";

            } else {
            QTextStream in(&file);
            QString temp;
             temp=in.readAll();
            ui->file1_brows->setText("Минус слова константы \n"+temp);
            ui->minusBrowser->append(temp);
            minus_words=temp.split("\n",QString::SkipEmptyParts);


            file.close(); }
        } else errors+="Minus file not name!\r\n";

    if (ui->plus_word_file_string->text() == "") {ui->plus_word_file_string->setText(QCoreApplication::applicationDirPath()+"/Plus.txt");}
    fileName = ui->plus_word_file_string->text();


        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                errors+="Plus file not open!\r\n";

            } else {
            QTextStream in(&file);
            QString temp;
             temp=in.readAll();
            ui->file2_brows->setText("Плюс слова константы \n"+temp);
             ui->plusBrowser->append(temp);
            plus_words=temp.split("\n",QString::SkipEmptyParts);


            file.close(); }
        }  else errors+="Plus file not name!\r\n";


        if(name_file2=="") { name_file2=QCoreApplication::applicationDirPath()+"/f2.txt";}
        fileName=name_file2;

            if (fileName != "") {
                QFile file(fileName);
                if (!file.open(QIODevice::ReadOnly)) {
                    //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                    errors+="File2 not open!\r\n";
                } else {
                QTextStream in(&file);
                ui->file2_brows->setText(string_file2=in.readAll());
                //textEdit->setText(in.readAll());
                file.close();}
            } else errors+="File2 file not name!\r\n";

            if(name_file1=="") { name_file1=QCoreApplication::applicationDirPath()+"/f1.txt";}
            fileName=name_file1;

                if (fileName != "") {
                    QFile file(fileName);
                    if (!file.open(QIODevice::ReadOnly)) {
                        //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                        errors+="File1 not open!\r\n";
                    } else {
                    QTextStream in(&file);
                    ui->file1_brows->setText(string_file1=in.readAll());
                    //textEdit->setText(in.readAll());
                    file.close();}
                } else errors+="File1 file not name!\r\n";
                zam_src.clear(); zam_res.clear();

                if(zamena_file_name=="") { zamena_file_name=QCoreApplication::applicationDirPath()+"/Zamena.txt";}
                fileName=zamena_file_name;

                    if (fileName != "") {
                        QFile file(fileName);
                        if (!file.open(QIODevice::ReadOnly)) {
                            //QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                            errors+="Zamena file not open!\r\n";
                        } else {
                        QTextStream in(&file);
                        QString ttemp;
                        ttemp=in.readAll();
                        QStringList tt, tempqsl;
                        tempqsl=ttemp.split("\r\n");
                         for (uint i = 0; i < (uint)tempqsl.size(); i++){
                             tt=tempqsl.at(i).split("==");
                             if(tt.size()==2){
                             zam_src.push_back(tt.at(0));
                             ui->zamsrc->append(tt.at(0));
                             zam_res.push_back(tt.at(1));
                             ui->zamres->append(tt.at(1));
                             }

                         }
                        file.close();

                        }
                    } else errors+="Zamena file not name!\r\n";


                if(errors!="") QMessageBox::critical(this, tr("Error"), errors);



}
