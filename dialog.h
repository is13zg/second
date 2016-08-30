#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QString"
#include "QStringList"
#include "QFile"
#include "QFileDialog"
#include "QTextStream"
#include "QMessageBox"
#include <QTextCodec>
#include "QChar"
#include "QCoreApplication"
#include "QProcess"
#include <cstdlib>
#include <ctime>


namespace Ui {
class Dialog;
}


class Dialog : public QDialog
{
    Q_OBJECT

public:
    static bool MyLessThan(const QString &s1, const QString &s2)
    {
        if (s1.size() == s2.size())
            return (s1.toLower() < s2.toLower());
        else
            return (s1.size() > s2.size());
    }

    static bool MyMoreThan(const QString &s1, const QString &s2)
    {
        if (s1.size() == s2.size())
            return (s1.toLower() < s2.toLower());
        else
            return (s1.size() < s2.size());
    }
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString string_file1, string_file2,name_file1,name_file2, normal_string_file1, normal_string_file2;
    QStringList minus_words, plus_words,zam_src,zam_res;
    QString config_file_name, zamena_file_name, MYSTEM, Tempfile, OBYA_text;
    int podshet_sootvetstvia(QString str1, QString str2, int min_dlinna_slova);
    int perezapisati1v2(QString filename1, QString filename2);
    int zapisat_v_fail(QString filename, QString src_string);
    QString chitat_fail(QString filename);
    QString get_normal(QString qs);
    QString get_normal2(QString qs);


private slots:
    void on_select_file2_clicked();

    void on_do_task_clicked();

    void on_select_file1_clicked();

    void on_clear_fb1_clicked();

    void on_clear_fb2_clicked();   

    void on_minus_word_select_file_clicked();

    void on_plus_word_select_file_clicked();


    void on_do_tab2_clicked();

    void on_add_zam_clicked();

    void on_do_zamena_clicked();


    void on_clear_obya_clicked();

    void on_pushButton_clicked();

    void on_obyaline_textChanged();

    void on_addminus_clicked();

    void on_addplus_clicked();

    void on_clear_plus_clicked();

    void on_clear_minus_clicked();

    void on_reloading_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
