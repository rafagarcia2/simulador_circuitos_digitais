#ifndef ERROFILE_H
#define ERROFILE_H

#include <QDialog>

namespace Ui {
class errofile;
}

class errofile : public QDialog
{
    Q_OBJECT

public:
    explicit errofile(QWidget *parent = 0);
    ~errofile();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::errofile *ui;
};

#endif // ERROFILE_H
