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
    void initBoard();
    void setHero();
    void setFilePath();
    void setStateLabel(QString state);
public slots:
    void setUserID();
    void setHero1();
    void setHero2();
    void setHero3();
    void setHero4();
    void clickMap1();
    void clickMap2();
    void clickMap3();
    void clickMap4();
    void clickMap5();
    void clickMap6();
    void clickMap7();
    void clickMap8();
    void clickMap9();
    void clickMapActionBtn1();
    void clickMapActionBtn2();
    void clickMapActionBtn3();
    void clickMapActionBtn4();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
