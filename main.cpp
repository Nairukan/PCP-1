#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <bits/stdc++.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRect r = QApplication::desktop()->availableGeometry();
    std::ifstream r1 ("1r4.settings");
    std::string Landguage;
    r1 >> Landguage;
    r1.close();
    //MainWindow ruk(nullptr, 4, r, Landguage);
    MainWindow rec(nullptr, 3, r, Landguage);
    MainWindow hello(nullptr, 2, r, Landguage);
    hello.show();
    hello.Spr=rec.th;
    MainWindow w(nullptr, 0, r, Landguage);
    hello.Suk=w.th;
    w.Spr=rec.th;
    w.landg=Landguage;
    //w.Ruco=ruk.th;
    MainWindow q(nullptr, 1, r, Landguage);
    q.landg=Landguage;
    w.Suk=q.th;
    return a.exec();
}

/*                Цели                     |       Сроки         | Процент выполнения
 *     ____________________________________|_____________________|____________________
 *     Размеры окна                        \                     \
 *     ____________________________________\_____________________\____________________
 *     Python                              \                     \
 *     ____________________________________\_____________________\____________________
 *     Исправление ошибок                  \                     \
 *     _______________________________________________________________________________
 * */
