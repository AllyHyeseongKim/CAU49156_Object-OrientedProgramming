#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <string>
#include <iostream>

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
    void gameStart();
    void initBoard();
    void setHero();
    void setFilePath();
    void gameInit();
    void showAlert(QString n);
    void showSelection(QString message, QString cancel, QString accept);
    void setText4(int a, int b);
    void setText3(int a);
    void gameLoop();
    void clickMapActionBtnWrapUp();
    void showList(std::vector<QString> list, bool should_show_back);
public slots:
    void setUserID();
    void setHero1();
    void setHero2();
    void setHero3();
    void setHero4();
    void clickMapActionBtn1();
    void clickMapActionBtn2();
    void clickMapActionBtn3();
    void clickMapActionBtn4();
    void clickMapActionBtn5();
    void setText5(QString a);
    void setText6(int a, QString name);
    void closeAlert();
    void closeSelectionCancel();
    void closeSelectionAccept();
    void closeList();
    void clickMap(int id);
    void listHero(QString value);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
