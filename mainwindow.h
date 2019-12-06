#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setText1(int a);
    void setText2(int a);
    void setText3(int a, int b);
    void setText4(int a);
    void gameStart();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
