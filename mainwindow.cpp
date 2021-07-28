#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <QCursor>
#include <QTimer>
#include <QPushButton>
#include <bits/stdc++.h>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QFileDialog>
#include <QTextStream>
//#define TEXT "SomeText"

QMainWindow * this1;

std::map <QString, int> libA = {{"Pattern",   -1},
                                {"Begin",      0},
                                {"End",        1},
                                {"Arithmetic", 2},
                                {"Out",        3},
                                {"In",         4},
                                {"ArrayWork",  5},
                                {"If",         6},
                                {"While",      7}};

QString TypePas(QString t){
    int w=0;
    for (int i=0; i<t.length(); i++){
        if (t[i]>='0' && t[i]<='9'){

        }else{
            if (w==0 && t[i]=='.'){
                w=1;
            }else{
                w=2;
            }
        }
    }
    if (w==0){
        return "Integer";
    }
    if (w==1){
        return "Real";
    }
    if (w==2){
        return "String";
    }
}

QString TypeCPlusPlus(QString t){
    int w=0;
    for (int i=0; i<t.length(); i++){
        if (t[i]>='0' && t[i]<='9'){

        }else{
            if (w==0 && t[i]=='.'){
                w=1;
            }else{
                w=2;
            }
        }
    }
    if (w==0){
        return "int";
    }
    if (w==1){
        return "double";
    }
    if (w==2){
        return "string";
    }
}

std::map <int, QPoint> LibPoints = {{0, QPoint(4, 50)},
                                    {1, QPoint(4, 100)},
                                    {2, QPoint(4, 150)},
                                    {4, QPoint(4, 200)},
                                    {3, QPoint(4, 250)},
                                    {6, QPoint(4, 300)},
                                    {7, QPoint(4, 350)}};
std::map <QString, std::vector<item*> > PatternMap;

std::map <QString, QString> TranlateL = {{"Begin",      "Начало"},
                                         {"End",        "Конец"},
                                         {"Arithmetic", "Арифметика"},
                                         {"Out",        "Вывод"},
                                         {"In",         "Ввод"},
                                         {"ArrayWork",  "Рабочее Поле"},
                                         {"If",         "Условие"},
                                         {"While",      "Пока"},
                                         {"Pattern",   ""}};

void MainWindow::NewBlock(QString type, int u){
    item *it;
    bool Kaif=0;
    it = new item(type, this, landg);
    //it->land=landg;
    if (libA.find(type)==libA.end()){
        libA[type]=libA.size()-2;
        if (libA[type]==8){
            LibPoints[libA.size()-2]=QPoint(this->width()*4/1050, this->height()*(LibPoints[libA.size()-3].y()+80)/820);
            ui->comboBox_2->show();
        }else {
            LibPoints[libA.size()-2]=QPoint(this->width()*4/1050, this->height()*LibPoints[libA.size()-3].y()/820);
        }
        ui->comboBox_2->addItem(type);
        Kaif=1;
    }
    if (libA[type]!=5){
        int w=ScreenWidth*75/1600, h=ScreenHeigth*40/860;
        it->Label_Instructions.push_back(new QLabel(this));
        it->Label_Instructions[0]->setAlignment(Qt::AlignCenter);
        it->Label_Instructions[0]->setStyleSheet("color : blue;");
        it->Label_Instructions[0]->show();
        if (landg=="Eng")
            it->SetTextOnLabel(type);
        else{
            if (libA[type]>7){
                QChar cc= 49+libA[type]-8;
                QString c;
                c+=cc;
                it->SetTextOnLabel("Шаблон"+c);
            }else{
                it->SetTextOnLabel(TranlateL[type]);
            }
        }
        it->Label_Instructions[0]->setFont(FontLove);
        it->Label_Instructions[0]->move((w-it->Label_Instructions[0]->width())/2, (h-it->Label_Instructions[0]->height())/2);
        if (libA[type]<3){
            it->setGeometry(w, h, 0, 0);
            if (libA[type]==2){
                it->Butt->setFont(FontLove);
            }
        }else if(libA[type]==6 || libA[type]==7){
            if (landg=="Eng"){
                it->Butt->Frame3.push_back(new QLabel("Yes", this));
                it->Butt->Frame3.push_back(new QLabel("No", this));
            }else{
                it->Butt->Frame3.push_back(new QLabel("Да", this));
                it->Butt->Frame3.push_back(new QLabel("Нет", this));
            }
            it->Butt->Frame3[0]->hide();
            it->Butt->Frame3[1]->hide();
            it->Butt->Frame3[0]->setFont(FontLove);
            it->Butt->Frame3[1]->setFont(FontLove);
            it->setGeometry(w, h, 0, 0);
            NewBlock("ArrayWork", 1);
            it->MyItems.push_back(items[KolLayout-1]);
            it->MyItems[0]->Pa=it;
            it->MyItems[0]->resize(100, 60);
            it->MyItems[0]->move(w/2+width()*5/1050, h+height()*15/820);
            it->MyItems[0]->Hiden=1;
            it->Butt->setFont(FontLove);
            it->ShowHeigth=155*height()/820;
            if(libA[type]==6){
                it->Butt->Frame3[0]->setGeometry(80*width()/1050, 0, 50*width(), 20*height()/820);
                it->Butt->Frame3[1]->setGeometry(-25*width()/1050, 0, 50*width(), 20*height()/820);
            NewBlock("ArrayWork", 1);
                it->MyItems.push_back(items[KolLayout-1]);
                it->MyItems[1]->Pa=it;
                it->MyItems[1]->resize(100, 60);
                it->MyItems[1]->move(w/2-width()*5/1050-it->MyItems[1]->width, h+height()*15/820);
                it->MyItems[1]->Hiden=1;
                it->ShowHeigth=140*height()/820;
            }else{
                it->Butt->Frame3[0]->setGeometry(13*width()/1050, 35*height()/820, 50*width(), 20*height()/820);
                it->Butt->Frame3[1]->setGeometry(80*width()/1050, 0, 50*width(), 20*height()/820);
            }

        }else if (type=="In" || type=="Out"){
            it->setGeometry(w, h, 0, 0);
            it->Butt->setFont(FontLove);
        }else{
            it->setGeometry(w, h, 0, 0);
            if (libA.find(type)!=libA.end()){
                it->EnabledItems=PatternMap[type];
            }
        }
        it->move(LibPoints[libA[type]].x()*width()/1050, LibPoints[libA[type]].y()*height()/820);
        //it->position=items.size();
        items.push_back(it);
    }else{
        int w, h;
            w=width()*it->width/1050; h=height()-height()*5/820-ui->menuBar->height()-5*height()/820;
            it->width=width()*it->width/1050; it->height=height()-height()*5/820-ui->menuBar->height()-5*height()/820;
        if (u<1){
            it->move(width()*97/1050, height()*5/820+ui->menuBar->height());
            it->MaxHeigth=height()-height()*5/820-ui->menuBar->height()-5*height()/820;
        }else{
            it->height=70*height()/820;
        }
        it->position=KolLayout;
        std::vector <item*>::iterator it1 = items.begin() + KolLayout;
        KolLayout++;
        items.insert(it1, it);
    }
    if (Kaif){
        it->hh=0;
        it->Hide(1);
    }
}

void MainWindow::SaveAsCode(){
    QString add;
    if (ui->comboBox->currentIndex()==1)
        add=QFileDialog::getSaveFileName(this, "SaveCode", "", "*.pas");
    else if (ui->comboBox->currentIndex()==0){
        add=QFileDialog::getSaveFileName(this, "SaveCode", "", "*.cpp");
    }else if (ui->comboBox->currentIndex()==2){
        add=QFileDialog::getSaveFileName(this, "SaveCode", "", "*.py");
    }
    if (add!=""){
        QFile r1(add);
        r1.open(QIODevice :: WriteOnly);
        QTextStream r(&r1);
        Suk->TE->setText("");
        //CodeLineL.clear();
        items[0]->LineVariables.clear();
        items[0]->KolFuckVariable=0;
        std::vector <QString> F=Translate(items[0], 0, 0);

        for (int i=0; i<F.size(); i++){
            //CodeLineL.push_back(new QLabel(this));
            Suk->TE->append(F[i]);
            //CodeLineL[i]->move(800, 150+i*25);
            //CodeLineL[i]->show();
            //TE->resize(300, 17*i+17);
            r << F[i] << "\n";
        }
        if (!(ui->comboBox->currentIndex()==2))
            r << "//Powered by PCP blocks v1.0.4";
        else {
            r << "#Powered by PCP blocks v1.0.4";
        }
    }else{
        if (landg=="Eng")
            QMessageBox::critical(this, "Error", "Way to directory not found");
        else
            QMessageBox::critical(this, "Ошибка", "Путь к директории не обнаружен");
    }
}

void MainWindow::SaveArrea(QTextStream *r, item *MainItem){
    int Sz=MainItem->EnabledItems.size();
    *r << Sz << " ";
    for (int i=0; i<Sz; i++){
        QString Type=MainItem->EnabledItems[i]->Type;
        *r << Type << " ";
        if (Type=="Arithmetic" || Type=="Out"){
            int k=MainItem->EnabledItems[i]->Butt->Frame2.size();
            //QMessageBox::critical(this, "", QString::number(k));
            *r << k << " ";
            for (int j=0; j<k; j++){
                *r << MainItem->EnabledItems[i]->Butt->Frame2[j]->text()+"001Ni&&&" << " ";
            }
        }else if (Type=="In"){
            int k=MainItem->EnabledItems[i]->Butt->Frame2.size();
            //QMessageBox::critical(this, "", QString::number(k));
            *r << k << " ";
            for (int j=0; j<k; j++){
                *r << MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex() << " ";
                *r << MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked() << " ";
                *r << MainItem->EnabledItems[i]->Butt->Frame2[j]->text()+"001Ni&&&" << " ";
            }
        }else if (Type=="If"){
            *r << MainItem->EnabledItems[i]->Butt->Frame2[0]->text()+"001Ni&&&" << " ";
            SaveArrea(r, MainItem->EnabledItems[i]->MyItems[0]);
            SaveArrea(r, MainItem->EnabledItems[i]->MyItems[1]);
        }else if (Type=="While"){
            *r << MainItem->EnabledItems[i]->Butt->Frame2[0]->text()+"001Ni&&&" << " ";
            SaveArrea(r, MainItem->EnabledItems[i]->MyItems[0]);
            //SaveArrea(r, MainItem->EnabledItems[i]->MyItems[1]);
        }else if (Type=="Pattern"){
            SaveArrea(r, MainItem->EnabledItems[i]);
        }
    }
    repaint();
}

void MainWindow::SaveButton(){
    if (addres==""){
        //addres=QFileDialog::getExistingDirectory(this, "Directory Dialog", "");
        addres=QFileDialog::getSaveFileName(this, "Save", "", "*.PCPb");
    }
    //addres+=".PCPb";
    if (addres!=""){
        QFile r1(addres);
        r1.open(QIODevice :: WriteOnly);
        QTextStream r(&r1);
        SaveArrea(&r, items[0]);
        r1.close();
    }else if (landg=="Eng")
        QMessageBox::critical(this, "Error", "Way to directory not found");
    else
        QMessageBox::critical(this, "Ошибка", "Путь к директории не обнаружен");
}

void MainWindow::SaveAsButton(){
        //addres=QFileDialog::getExistingDirectory(this, "Directory Dialog", "");
        addres=QFileDialog::getSaveFileName(this, "Save", "", "*.PCPb");
        if (addres!=""){
            //addres+=".PCPb";
            QFile r1(addres);
            r1.open(QIODevice :: WriteOnly);
            QTextStream r(&r1);
            SaveArrea(&r, items[0]);
            r1.close();
        }
        else if (landg=="Eng")
                QMessageBox::critical(this, "Error", "Way to directory not found");
            else
                QMessageBox::critical(this, "Ошибка", "Путь к директории не обнаружен");
}

void MainWindow::OpenArrea(QTextStream *r, item *MainItem){
    int kol;
    *r >> kol;
    for (int i=0; i<kol; i++){
        QString Type;
        *r >> Type;
        //QMessageBox::critical(this, "", Type);
        if (Type!="Pattern"){
            NewBlock(Type, 0);

            if (MainItem->Hiden)
                items[items.size()-1]->Hide(1);
            items[items.size()-1]->Layout=MainItem;
            MainItem->EnabledItems.push_back(items[items.size()-1]);

            if (i==0){
                item* ok=MainItem->EnabledItems[0];
                ok->setGeometry(ok->width, ok->height, MainItem->left+(MainItem->width-ok->width)/2, MainItem->top+15*height()/820);
                for (int jor=1; jor<MainItem->EnabledItems.size(); jor++){
                    MainItem->EnabledItems[jor]->move(0, ok->height+15*height()/820);
                }
            }else{
                int hh=0;
                for (; hh<MainItem->EnabledItems.size(); hh++){
                    if (MainItem->EnabledItems[hh]==items[items.size()-1]){
                        break;
                    }
                }
                //if (hh==items[qq]->EnabledItems.size()-1){
                    items[items.size()-1]->setGeometry(items[items.size()-1]->width, items[items.size()-1]->height, MainItem->EnabledItems[hh-1]->left, MainItem->EnabledItems[hh-1]->top+15*height()/820+MainItem->EnabledItems[hh-1]->height);

                /*hh++;
                for (;  hh<MainItem->EnabledItems.size(); hh++){
                    MainItem->EnabledItems[hh]->move(0, 15*height()/820+items[items.size()-1]->height);
                }*/
            }
            //ReconstructItem0();
            if (Type=="Arithmetic" || Type=="Out"){
                int k;
                *r >> k;
                if (k>0){
                    for (int q=0; q<k; q++){
                        QString temp;
                        QString Water;
                        *r >> Water;
                        while (!(Water[Water.length()-1]=='&' && Water[Water.length()-2]=='&' && Water[Water.length()-3]=='&' && Water[Water.length()-4]=='i' && Water[Water.length()-5]=='N' && Water[Water.length()-6]=='1' && Water[Water.length()-7]=='0' && Water[Water.length()-8]=='0')){
                            //QMessageBox::critical(this, "", Water);
                            temp+=Water+" ";
                            *r >> Water;
                        }
                        Water.remove(Water.length()-8, 8);
                        temp+=Water;
                        items[items.size()-1]->Butt->Frame2.push_back(new QLineEdit(this));
                        //items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->show();
                        items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->move(items[items.size()-1]->Butt->LeftFrame+10*width()/1050, items[items.size()-1]->Butt->TopFrame+10*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame2.size()-1));
                        items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->resize(170*width()/1050, 25*height()/820);
                        if (items[items.size()-1]->Butt->Frame4.size()!=0)
                        items[items.size()-1]->Butt->Frame4[0]->move(items[items.size()-1]->Butt->Frame4[0]->geometry().left(), items[items.size()-1]->Butt->Frame4[0]->geometry().top()+35*height()/820);
                        items[items.size()-1]->Butt->HeigthFrame+=35*height()/820;
                        items[items.size()-1]->Butt->Frame6.push_back(new ButtonClose(items[items.size()-1]->Butt->LeftFrame+185*width()/1050, 15*width()/1050, items[items.size()-1]->Butt->TopFrame+15*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame6.size()), 15*height()/820));
                        items[items.size()-1]->Butt->FrameCorrect();
                        items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->setText(temp);
                        //repaint();
                    }
                }
            }else if (Type=="In"){
                int k;
                *r >> k;
                if (k>0){
                    for (int q=0; q<k; q++){
                        int indeks;
                        int chek;
                        *r >>indeks >> chek;
                        QString temp;
                        QString Water;
                        *r >> Water;
                        while (Water.length()<=8 || !(Water[Water.length()-1]=='&' && Water[Water.length()-2]=='&' && Water[Water.length()-3]=='&' && Water[Water.length()-4]=='i' && Water[Water.length()-5]=='N' && Water[Water.length()-6]=='1' && Water[Water.length()-7]=='0' && Water[Water.length()-8]=='0')){
                            //QMessageBox::critical(this, "", Water);
                            temp+=Water+" ";
                            *r >> Water;
                        }
                        Water.remove(Water.length()-8, 8);
                        temp+=Water;
                        items[items.size()-1]->Butt->Frame1.push_back(new QComboBox(this));
                        //items[i]->Butt->Frame1[items[i]->Butt->Frame1.size()-1]->show();
                        items[items.size()-1]->Butt->Frame1[items[items.size()-1]->Butt->Frame1.size()-1]->addItem("Целочисленное");
                        items[items.size()-1]->Butt->Frame1[items[items.size()-1]->Butt->Frame1.size()-1]->addItem("Вещественное");
                        items[items.size()-1]->Butt->Frame1[items[items.size()-1]->Butt->Frame1.size()-1]->addItem("Текст");
                        items[items.size()-1]->Butt->Frame1[items[items.size()-1]->Butt->Frame1.size()-1]->move(items[items.size()-1]->Butt->LeftFrame+10*width()/1050, items[items.size()-1]->Butt->TopFrame+10*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame1.size()-1));
                        items[items.size()-1]->Butt->Frame1[items[items.size()-1]->Butt->Frame1.size()-1]->resize(100*width()/1050, 25*height()/820);
                        items[items.size()-1]->Butt->Frame1[items[items.size()-1]->Butt->Frame1.size()-1]->setCurrentIndex(indeks);
                        items[items.size()-1]->Butt->Frame2.push_back(new QLineEdit(this));
                        //items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->show();
                        items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->move(items[items.size()-1]->Butt->LeftFrame+110*width()/1050, items[items.size()-1]->Butt->TopFrame+10*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame2.size()-1));
                        items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->resize(50*width()/1050, 25*height()/820);
                        //if (items[items.size()-1]->Butt->Frame4.size()!=0)
                        items[items.size()-1]->Butt->Frame4[0]->move(items[items.size()-1]->Butt->Frame4[0]->geometry().left(), items[items.size()-1]->Butt->Frame4[0]->geometry().top()+35*height()/820);
                        items[items.size()-1]->Butt->HeigthFrame+=35*height()/820;
                        items[items.size()-1]->Butt->Frame6.push_back(new ButtonClose(items[items.size()-1]->Butt->LeftFrame+165*width()/1050, 12*width()/1050, items[items.size()-1]->Butt->TopFrame+7*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame6.size()), 12*height()/820));
                        items[items.size()-1]->Butt->FrameCorrect();
                        items[items.size()-1]->Butt->Frame5.push_back(new QCheckBox(this));
                        items[items.size()-1]->Butt->Frame5[items[items.size()-1]->Butt->Frame5.size()-1]->move(items[items.size()-1]->Butt->LeftFrame+165*width()/1050, items[items.size()-1]->Butt->TopFrame+15*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame1.size()-1));
                        items[items.size()-1]->Butt->Frame5[items[items.size()-1]->Butt->Frame5.size()-1]->setText("Ввод");
                        items[items.size()-1]->Butt->Frame5[items[items.size()-1]->Butt->Frame5.size()-1]->setChecked(chek);
                        items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->setText(temp);
                        //repaint();
                    }
                }
            }else if (Type=="If"){
                QString temp;
                QString Water;
                *r >> Water;
                while (Water.length()<=8 || !(Water[Water.length()-1]=='&' && Water[Water.length()-2]=='&' && Water[Water.length()-3]=='&' && Water[Water.length()-4]=='i' && Water[Water.length()-5]=='N' && Water[Water.length()-6]=='1' && Water[Water.length()-7]=='0' && Water[Water.length()-8]=='0')){
                    //QMessageBox::critical(this, "", Water);
                    temp+=Water+" ";
                    *r >> Water;
                }
                Water.remove(Water.length()-8, 8);
                temp+=Water;
                    items[items.size()-1]->MyItems[1]->MaxHeigth=MainItem->MaxHeigth*3/5;
                    items[items.size()-1]->MyItems[0]->MaxHeigth=MainItem->MaxHeigth*3/5;
                    items[items.size()-1]->MyItems[0]->n=MainItem->n+1;
                    items[items.size()-1]->MyItems[1]->n=MainItem->n+1;
                    items[items.size()-1]->MyItems[0]->setGeometry((MainItem->width-50)/2, items[items.size()-1]->MyItems[0]->ShowHeigth, items[items.size()-1]->left+items[items.size()-1]->width/2-5-(MainItem->width-50)/2, items[items.size()-1]->top+items[items.size()-1]->height+15*height()/820);
                    items[items.size()-1]->MyItems[1]->setGeometry((MainItem->width-50)/2, items[items.size()-1]->MyItems[1]->ShowHeigth, items[items.size()-1]->left+items[items.size()-1]->width/2+5, items[items.size()-1]->top+items[items.size()-1]->height+15*height()/820);
                    items[items.size()-1]->HelpLine.clear();
                    items[items.size()-1]->HelpLine.push_back(QLine(items[items.size()-1]->left, items[items.size()-1]->top+20*height()/820, items[items.size()-1]->left+items[items.size()-1]->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+20*height()/820));
                    items[items.size()-1]->HelpLine.push_back(QLine(items[items.size()-1]->left+items[items.size()-1]->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+40*height()/820+15*height()/820, items[items.size()-1]->left+items[items.size()-1]->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+20*height()/820));
                    items[items.size()-1]->HelpLine.push_back(QLine(items[items.size()-1]->left+items[items.size()-1]->width, items[items.size()-1]->top+20*height()/820, items[items.size()-1]->left+items[items.size()-1]->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+20*height()/820));
                    items[items.size()-1]->HelpLine.push_back(QLine(items[items.size()-1]->left+items[items.size()-1]->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+40*height()/820+15*height()/820, items[items.size()-1]->left+items[items.size()-1]->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+20*height()/820));

                    items[items.size()-1]->HelpLine.push_back(QLine(items[items.size()-1]->left+38*width()/1050, items[items.size()-1]->top+40*height()/820+15*height()/820+items[items.size()-1]->MyItems[0]->height+15*height()/820, items[items.size()-1]->left+items[items.size()-1]->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+40*height()/820+30*height()/820+items[items.size()-1]->MyItems[0]->height));
                    items[items.size()-1]->HelpLine.push_back(QLine(items[items.size()-1]->left+items[items.size()-1]->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+40*height()/820+15*height()/820+items[items.size()-1]->MyItems[0]->height+15*height()/820, items[items.size()-1]->left+items[items.size()-1]->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+40*height()/820+15*height()/820+items[items.size()-1]->MyItems[0]->height));
                    items[items.size()-1]->HelpLine.push_back(QLine(items[items.size()-1]->left+38*width()/1050, items[items.size()-1]->top+40*height()/820+15*height()/820+items[items.size()-1]->MyItems[0]->height+15*height()/820, items[items.size()-1]->left+items[items.size()-1]->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+40*height()/820+30*height()/820+items[items.size()-1]->MyItems[0]->height));
                    items[items.size()-1]->HelpLine.push_back(QLine(items[items.size()-1]->left+items[items.size()-1]->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+40*height()/820+15*height()/820+items[items.size()-1]->MyItems[0]->height,  items[items.size()-1]->left+items[items.size()-1]->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+40*height()/820+30*height()/820+items[items.size()-1]->MyItems[0]->height));

                    items[items.size()-1]->Butt->Frame2.push_back(new QLineEdit(this));
                //items[items.size()-1]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->show();
                items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->move(items[items.size()-1]->Butt->LeftFrame+10*width()/1050, items[items.size()-1]->Butt->TopFrame+10*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame2.size()-1));
                items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->resize(170*width()/1050, 25*height()/820);
                items[items.size()-1]->Butt->Frame4[0]->move(items[items.size()-1]->Butt->Frame4[0]->geometry().left(), items[items.size()-1]->Butt->Frame4[0]->geometry().top()+35*height()/820);
                items[items.size()-1]->Butt->Frame4[0]->setText("Показать/Скрыть");
                items[items.size()-1]->Butt->HeigthFrame+=35*height()/820;
                items[items.size()-1]->Butt->Frame6.push_back(new ButtonClose(items[items.size()-1]->Butt->LeftFrame+185*width()/1050, 15*width()/1050, items[items.size()-1]->Butt->TopFrame+15*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame6.size()), 15*height()/820));
                items[items.size()-1]->Butt->FrameCorrect();
                items[items.size()-1]->Butt->Frame2[0]->setText(temp);
                item* K=items[items.size()-1];
                /*K->hh=0;
                K->height=70+K->Layout->height/2;
                K->MyItems[0]->Hide(0);
                K->MyItems[1]->Hide(0);
                */
                OpenArrea(r, items[items.size()-1]->MyItems[0]);
                OpenArrea(r, K->MyItems[1]);
                K->hh=0;
                //K->height=40;
                K->MyItems[0]->Hide(1);
                K->MyItems[1]->Hide(1);

                //HideBlocks(K->MyItems[0], 1);
                //HideBlocks(K->MyItems[1], 1);
            }else if (Type=="While"){
                QString temp;
                QString Water;
                *r >> Water;
                while (Water.length()<=8 || !(Water[Water.length()-1]=='&' && Water[Water.length()-2]=='&' && Water[Water.length()-3]=='&' && Water[Water.length()-4]=='i' && Water[Water.length()-5]=='N' && Water[Water.length()-6]=='1' && Water[Water.length()-7]=='0' && Water[Water.length()-8]=='0')){
                    //QMessageBox::critical(this, "", Water);
                    temp+=Water+" ";
                    *r >> Water;
                }
                Water.remove(Water.length()-8, 8);
                temp+=Water;
                    items[items.size()-1]->MyItems[0]->MaxHeigth=MainItem->MaxHeigth*3/5;
                    items[items.size()-1]->MyItems[0]->n=MainItem->n+1;
                    items[items.size()-1]->MyItems[0]->setGeometry((MainItem->width-50*width()/1050)/2, items[items.size()-1]->MyItems[0]->ShowHeigth, items[items.size()-1]->left+items[items.size()-1]->width/2-(MainItem->width-50*width()/1050)/4, items[items.size()-1]->top+items[items.size()-1]->height+15*height()/820);
                    //items[items.size()-1]->MyItems[1]->setGeometry((MainItem->width-50)/2, MainItem->height/3, items[items.size()-1]->left+items[items.size()-1]->width/2+5, items[items.size()-1]->top+items[items.size()-1]->height+15);
                    item * ChoosingItem=items[items.size()-1];
                    ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top-5*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, ChoosingItem->top-5*height()/820));
                    ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820, ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820));
                    ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+30*height()/820+ChoosingItem->MyItems[0]->height));
                    ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820, ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height));
                    ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, ChoosingItem->top-5*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(MainItem->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820));

                    ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width, ChoosingItem->top+20*height()/820, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, ChoosingItem->top+20*height()/820));
                    ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+45*height()/820+ChoosingItem->MyItems[0]->height, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, ChoosingItem->top+20*height()/820));
                    ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+30*height()/820, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(MainItem->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+30*height()/820));

                    items[items.size()-1]->Butt->Frame2.push_back(new QLineEdit(this));
                //items[items.size()-1]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->show();
                items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->move(items[items.size()-1]->Butt->LeftFrame+10*width()/1050, items[items.size()-1]->Butt->TopFrame+10*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame2.size()-1));
                items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->resize(170*width()/1050, 25*height()/820);
                items[items.size()-1]->Butt->Frame4[0]->move(items[items.size()-1]->Butt->Frame4[0]->geometry().left(), items[items.size()-1]->Butt->Frame4[0]->geometry().top()+35*height()/820);
                items[items.size()-1]->Butt->Frame4[0]->setText("Показать/Скрыть");
                items[items.size()-1]->Butt->HeigthFrame+=35*height()/820;
                items[items.size()-1]->Butt->Frame6.push_back(new ButtonClose(items[items.size()-1]->Butt->LeftFrame+185*width()/1050, 15*width()/1050, items[items.size()-1]->Butt->TopFrame+15*height()/820+35*height()/820*(items[items.size()-1]->Butt->Frame6.size()), 15*height()/820));
                items[items.size()-1]->Butt->FrameCorrect();
                items[items.size()-1]->Butt->Frame2[0]->setText(temp);
                item* K=items[items.size()-1];
                //K->hh=0;
                //K->height=85+K->Layout->height/2;
                //K->MyItems[0]->Hide(0);
                //K->MyItems[1]->Hide(1);
                OpenArrea(r, items[items.size()-1]->MyItems[0]);
                //OpenArrea(r, K->MyItems[1]);
                K->hh=0;
                //K->height=40;
                K->MyItems[0]->Hide(1);
                //K->MyItems[1]->Hiden=0;
                //HideBlocks(K->MyItems[0], 1);
                //HideBlocks(K->MyItems[1], 1);
            }

            repaint();
        }else{
            OpenArrea(r, MainItem);
        }
    }
    ReconstructItem0();
    repaint();
}

void MainWindow::OpenButton(){
    addres=QFileDialog::getOpenFileName(this, "Open Dialog", "", "*.PCPb");
    if (addres!=""){
        QFile r1(addres);
        if (r1.isOpen())
                r1.close();
        r1.open(QIODevice::ReadOnly);
        QTextStream r(&r1);
        int i;
        for (i=addres.length()-1; addres[i]!='.'; i--);
        QString Path="";
        for (i=i+1; i<addres.length(); i++){
            Path+=addres[i];
        }
        int lkp=ui->comboBox->currentIndex();
        ui->comboBox->setCurrentIndex(0);
        if (Path=="PCPb"){
            OpenArrea(&r, items[0]);
            for (int i=0; i<items[0]->EnabledItems.size(); i++){
                if (items[0]->EnabledItems[i]->Type=="If" || items[0]->EnabledItems[i]->Type=="While"){
                    for (int j=0; j<items[0]->EnabledItems[i]->MyItems.size(); j++){
                        items[0]->EnabledItems[i]->MyItems[j]->Hide(1);
                    }
                }
            }
        }
        r1.close();
        ui->comboBox->setCurrentIndex(lkp);
        ReconstructItem0();
        repaint();
    }else if (landg=="Eng")
        QMessageBox::critical(this, "Error", "Way to directory not found");
    else
        QMessageBox::critical(this, "Ошибка", "Путь к директории не обнаружен");
}

void MainWindow::ClearButton(){
    if (TT==0){
        for (int i=items.size()-1; i>=KolLayout; i--){
            if (items[i]->Butt!=nullptr && items[i]->Butt->IsActivate){
                items[i]->Butt->Activate();
                break;
            }
        }
        repaint();
        for (int i=items[0]->EnabledItems.size()-1; i>=0; i--){
            DeleteBlock(items[0]->EnabledItems[i]);
        }
        Suk->TE->setText("");
        items[0]->LineVariables.clear();
        std::vector <QString> F=Translate(items[0], 0, 0);

        for (int i=0; i<F.size(); i++){
            //CodeLineL.push_back(new QLabel(this));
            Suk->TE->append(F[i]);
            //CodeLineL[i]->move(800, 150+i*25);
            //CodeLineL[i]->show();
            //TE->resize(300, 17*i+17);
        }
        ReconstructItem0();
        repaint();
    }else{
        Spr->show();
    }

    //QMessageBox::critical(this, "", QString::number(items[0]->EnabledItems[0]->MyItems[0]->EnabledItems[0]->height));
}

void MainWindow::AddArray(QTextStream *r, item *MainItem, QString Name){
    int kol;
    *r >> kol;
    for (int i=0; i<kol; i++){
        QString Type;
        *r >> Type;
        //NewBlock(Type, 0);
        //items[items.size()-1]->Layout=MainItem;
        MainItem->EnabledItems.push_back(new item(Type, this, landg));
        item *uo=MainItem->EnabledItems[MainItem->EnabledItems.size()-1];
        //ReconstructItem0();
        if (Type=="Arithmetic" || Type=="Out"){
            int k;
            *r >> k;
            if (k>0){
                for (int q=0; q<k; q++){
                    QString temp;
                    QString Water;
                    *r >> Water;
                    while (!(Water[Water.length()-1]=='&' && Water[Water.length()-2]=='&' && Water[Water.length()-3]=='&' && Water[Water.length()-4]=='i' && Water[Water.length()-5]=='N' && Water[Water.length()-6]=='1' && Water[Water.length()-7]=='0' && Water[Water.length()-8]=='0')){
                        //QMessageBox::critical(this, "", Water);
                        temp+=Water+" ";
                        *r >> Water;
                    }
                    Water.remove(Water.length()-8, 8);
                    temp+=Water;
                    uo->Butt->Frame2.push_back(new QLineEdit(this));
                    //items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->show();
                    //uo->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->move(items[items.size()-1]->Butt->LeftFrame+10, items[items.size()-1]->Butt->TopFrame+10+35*(items[items.size()-1]->Butt->Frame2.size()-1));
                    //uo->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->resize(170, 25);
                    //if (uo->Butt->Frame4.size()!=0)
                    //uo->Butt->Frame4[0]->move(uo->Butt->Frame4[0]->geometry().left(), uo->Butt->Frame4[0]->geometry().top()+35);
                    //uo->Butt->HeigthFrame+=35;
                    //uo->Butt->Frame6.push_back(new ButtonClose(uo->Butt->LeftFrame+185, 15, uo->Butt->TopFrame+15+35*(items[items.size()-1]->Butt->Frame6.size()), 15));
                    //uo->Butt->FrameCorrect();
                    uo->Butt->Frame2[uo->Butt->Frame2.size()-1]->setText(temp);
                    //repaint();
                }
            }
        }else if (Type=="In"){
            int k;
            *r >> k;
            if (k>0){
                for (int q=0; q<k; q++){
                    int indeks;
                    int chek;
                    *r >>indeks >> chek;
                    QString temp;
                    QString Water;
                    *r >> Water;
                    while (Water.length()<=8 || !(Water[Water.length()-1]=='&' && Water[Water.length()-2]=='&' && Water[Water.length()-3]=='&' && Water[Water.length()-4]=='i' && Water[Water.length()-5]=='N' && Water[Water.length()-6]=='1' && Water[Water.length()-7]=='0' && Water[Water.length()-8]=='0')){
                        //QMessageBox::critical(this, "", Water);
                        temp+=Water+" ";
                        *r >> Water;
                    }
                    Water.remove(Water.length()-8, 8);
                    temp+=Water;
                    uo->Butt->Frame1.push_back(new QComboBox(this));
                    //items[i]->Butt->Frame1[items[i]->Butt->Frame1.size()-1]->show();
                    uo->Butt->Frame1[uo->Butt->Frame1.size()-1]->addItem("Целочисленное");
                    uo->Butt->Frame1[uo->Butt->Frame1.size()-1]->addItem("Вещественное");
                    uo->Butt->Frame1[uo->Butt->Frame1.size()-1]->addItem("Текст");
                    uo->Butt->Frame1[uo->Butt->Frame1.size()-1]->setCurrentIndex(indeks);
                    uo->Butt->Frame2.push_back(new QLineEdit(this));
                    //items[items.size()-1]->Butt->Frame2[items[items.size()-1]->Butt->Frame2.size()-1]->show();
                    //if (items[items.size()-1]->Butt->Frame4.size()!=0)
                    uo->Butt->Frame5.push_back(new QCheckBox(this));
                    uo->Butt->Frame5[uo->Butt->Frame5.size()-1]->setChecked(chek);
                    uo->Butt->Frame2[uo->Butt->Frame2.size()-1]->setText(temp);
                    //repaint();
                }
            }
        }else if (Type=="If"){
            QString temp;
            QString Water;
            *r >> Water;
            while (Water.length()<=8 || !(Water[Water.length()-1]=='&' && Water[Water.length()-2]=='&' && Water[Water.length()-3]=='&' && Water[Water.length()-4]=='i' && Water[Water.length()-5]=='N' && Water[Water.length()-6]=='1' && Water[Water.length()-7]=='0' && Water[Water.length()-8]=='0')){
                //QMessageBox::critical(this, "", Water);
                temp+=Water+" ";
                *r >> Water;
            }
            Water.remove(Water.length()-8, 8);
            temp+=Water;
                uo->Butt->Frame2.push_back(new QLineEdit(this));
            //items[items.size()-1]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->show();
            uo->Butt->Frame2[0]->setText(temp);
            //item* K=items[items.size()-1];
            item * I1 = new item("ArrayWork", this, landg);
            item * I2 = new item("ArrayWork", this, landg);
            uo->MyItems.push_back(I1);
            uo->MyItems.push_back(I2);
            //uo->MyItems.push_back(I1);
            AddArray(r, uo->MyItems[0], "");
            AddArray(r, uo->MyItems[1], "");
         }else if (Type=="While"){
            QString temp;
            QString Water;
            *r >> Water;
            while (Water.length()<=8 || !(Water[Water.length()-1]=='&' && Water[Water.length()-2]=='&' && Water[Water.length()-3]=='&' && Water[Water.length()-4]=='i' && Water[Water.length()-5]=='N' && Water[Water.length()-6]=='1' && Water[Water.length()-7]=='0' && Water[Water.length()-8]=='0')){
                //QMessageBox::critical(this, "", Water);
                temp+=Water+" ";
                *r >> Water;
            }
            Water.remove(Water.length()-8, 8);
            temp+=Water;
                //items[items.size()-1]->MyItems[1]->setGeometry((MainItem->width-50)/2, MainItem->height/3, items[items.size()-1]->left+items[items.size()-1]->width/2+5, items[items.size()-1]->top+items[items.size()-1]->height+15);
                item * ChoosingItem=uo;
                uo->Butt->Frame2.push_back(new QLineEdit(this));
            //items[items.size()-1]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->show();
            uo->Butt->Frame2[0]->setText(temp);
            item * I1 = new item("ArrayWork", this, landg);
            //item * I2 = new item("ArrayWork", this);
            uo->MyItems.push_back(I1);
            AddArray(r, uo->MyItems[0], "");
            //OpenArrea(r, K->MyItems[1]);
            //HideBlocks(K->MyItems[1], 1);
        }
        //repaint();
    }
}

void MainWindow::AddPattern(){
    addres=QFileDialog::getOpenFileName(this, "Add Patern", "", "*.PCPb");
    if (addres!=""){
        QFile r1(addres);
        r1.open(QIODevice::ReadOnly);
        QTextStream r(&r1);
        //QString Name;
        //r << Name;
        QString Name;
        if (landg=="Eng")
            Name="Pattern "+QString::number(libA.size()-8);
        else {
            Name="Шаблон "+QString::number(libA.size()-8);
        }
        NewBlock(Name, 0);
        AddArray(&r, items[items.size()-1], Name);
        std::vector <item *> temp7;
        for (int i=0; i<items[items.size()-1]->EnabledItems.size(); i++){
            temp7.push_back(items[items.size()-1]->EnabledItems[i]);
        }
        PatternMap [Name]=temp7;
        r1.close();
        PatternOfItems.push_back(items[items.size()-1]);
        /*CodeLineL.clear();
    items[0]->LineVariables.clear();
    std::vector <QString> F=Translate(items[items.size()-1], 0);

    for (int i=0; i<F.size(); i++){
        //CodeLineL.push_back(new QLabel(this));
        TE->append(F[i]);
        //CodeLineL[i]->move(800, 150+i*25);
        //CodeLineL[i]->show();
        //TE->resize(300, 17*i+17);
    }*/
        addres="";
    }else if (landg=="Eng")
        QMessageBox::critical(this, "Error", "Way to directory not found");
    else
        QMessageBox::critical(this, "Ошибка", "Путь к директории не обнаружен");

    //QStringList line = addres.split("\");
    //QMessageBox::critical(this, "", line);
}

void MainWindow::ChangeLanguage(){
    std::ofstream r1 ("1r4.settings");

    if (landg=="Eng"){
        r1 << "Russian";
        landg="Russian";
        Suk->landg=landg;
        Spr->landg=landg;
    }else{
        r1 << "Eng";
        landg="Eng";
        Suk->landg=landg;
        Spr->landg=landg;
    }
    UpdateLanguage();
    Suk->UpdateLanguage();
    Spr->UpdateLanguage();
    r1.close();
}

QMenu* pmnuFile=nullptr;
//QMenu* pmnuFile2=nullptr;
QMenu* pmnuFile1=nullptr;

void MainWindow::UpdateLanguage(){
    if (TT==0){
        if (landg!="Eng"){
            ui->menu->setTitle("Задания");
            pmnuFile->setTitle("Файл");

            pmnuFile->clear();
            pmnuFile->addAction("&Соханить", this, SLOT(SaveButton()));
            pmnuFile->addAction("&Сохранить как", this, SLOT(SaveAsButton()));
            pmnuFile->addAction("&Открыть", this, SLOT(OpenButton()));
            pmnuFile->addAction("&Добавить шаблон", this, SLOT(AddPattern()));
            pmnuFile->addAction("&Сохранить код", this, SLOT(SaveAsCode()));
            pmnuFile1->setTitle("Настройки") ;
            pmnuFile1->clear();
            pmnuFile1->addAction("&Изменить язык на Английский", this, SLOT(ChangeLanguage()));
            pmnuFile1->addAction("&О программе", this, SLOT(RukR()));
            ui->pushButton->setText("Перевод");
            ui->pushButton_2->setText("Очистить");
        }else{
            ui->menu->setTitle("Tasks");
            pmnuFile->setTitle("File");
            pmnuFile->clear();
            pmnuFile->addAction("&Save", this, SLOT(SaveButton()));
            pmnuFile->addAction("&Save As", this, SLOT(SaveAsButton()));
            pmnuFile->addAction("&Open", this, SLOT(OpenButton()));
            pmnuFile->addAction("&Add Pattern", this, SLOT(AddPattern()));
            pmnuFile->addAction("&SaveAsCode", this, SLOT(SaveAsCode()));
            pmnuFile1->setTitle("Settings") ;
            pmnuFile1->clear();
            pmnuFile1->addAction("&Сhange language to Russian", this, SLOT(ChangeLanguage()));

            pmnuFile1->addAction("&About Programm", this, SLOT(RukR()));
            ui->pushButton->setText("Translate");
            ui->pushButton_2->setText("Clear");
        }
        for (int i=0; i<items.size(); i++){
            items[i]->UpdateLanuage(landg);
            if (libA[items[i]->Type]>=0){
                if (landg=="Eng"){
                    if (items[i]->Label_Instructions.size()>0)
                        items[i]->SetTextOnLabel(items[i]->Type2);
                }else{
                    if (items[i]->Label_Instructions.size()>0)
                    items[i]->SetTextOnLabel(TranlateL[items[i]->Type2]);
                }
            }
        }
    }else if (TT==2){
        if (landg=="Eng")
            ui->label->setText("Powered by PCP blocks v1.0.4");
        else{
            ui->label->setText("При поддержке PCP blocks v1.0.4");
        }
        if (landg=="Eng")
            th->setWindowTitle("PCP blocks v1.0.4 Translate");
        else {
            th->setWindowTitle("PCP blocks v1.0.4 Перевод");
        }
    }else {
        repaint();
    }
}

void MainWindow::RukR(){
    //this->Ruco->show();
    this->Spr->show();
}

void MainWindow::SetStartingSetting(){
    if (landg!="Eng")
        ui->menu->setTitle("Задания");
    ui->comboBox_2->move(this->width()*6/1050, this->height()*38/82);
    //this->resize(1050, 820);
    //ui->centralWidget->Setw
    //QMenu* pmnuFile;
    ui->label->hide();
    if (landg=="Eng"){
        pmnuFile = new QMenu("&File") ;
    }else{
        pmnuFile = new QMenu("&Файл") ;
    }
    if (landg=="Eng"){
        pmnuFile->addAction("&Save", this, SLOT(SaveButton()));
        pmnuFile->addAction("&Save As", this, SLOT(SaveAsButton()));
        pmnuFile->addAction("&Open", this, SLOT(OpenButton()));
        pmnuFile->addAction("&Add Pattern", this, SLOT(AddPattern()));
        pmnuFile->addAction("&SaveAsCode", this, SLOT(SaveAsCode()));
    }else{
        pmnuFile->addAction("&Соханить", this, SLOT(SaveButton()));
        pmnuFile->addAction("&Сохранить как", this, SLOT(SaveAsButton()));
        pmnuFile->addAction("&Открыть", this, SLOT(OpenButton()));
        pmnuFile->addAction("&Добавить шаблон", this, SLOT(AddPattern()));
        pmnuFile->addAction("&Сохранить код", this, SLOT(SaveAsCode()));
    }
    menuBar()->addMenu(pmnuFile);
    if (landg=="Eng"){
        pmnuFile1 = new QMenu("&Settings") ;
    }else{
        pmnuFile1 = new QMenu("&Настройки") ;
    }
    if (landg=="Eng"){
        pmnuFile1->addAction("&Сhange language to Russian", this, SLOT(ChangeLanguage()));
    }else{
        pmnuFile1->addAction("&Изменить язык на Английский", this, SLOT(ChangeLanguage()));
        pmnuFile1->addAction("&О программе", this, SLOT(RukR()));
    }

    menuBar()->addMenu(pmnuFile1);
    int fh=ui->pushButton->height(), fw=ui->pushButton->width();
    ui->pushButton->setGeometry(this->width()*9/1050, this->height()*(513+28)/820, this->width()*ui->pushButton->width()/1050, this->height()*ui->pushButton->height()/820);
    if (landg=="Eng"){
        ui->pushButton->setText("Translate");
    }else{
        ui->pushButton->setText("Перевод");
    }
    QFontMetrics f(ui->pushButton->font());
    //QFontMetr f=ui->pushButton->font();
    int zh=fh*100/f.height();
    int zw=fw*100/f.width(ui->pushButton->text());
    QFont fr=ui->pushButton->font();
    for (;;){
        QFontMetrics k(fr);
        if (ui->pushButton->height()*100/k.height()>=zh && ui->pushButton->width()*100/k.width(ui->pushButton->text())>=zw){
            //QMessageBox::critical(this, "", QString::number(fr.pointSize()));
            break;
        }
        fr.setPointSize(fr.pointSize()-1);
    }
    ui->pushButton->setFont(fr);
    FontLove=fr;
    FontLove.setPointSize(fr.pointSize());
    //QMessageBox::critical(this, "", QString::number(FontLove.pointSize()));
    //for (int i=0; i<f.)
    //ui->pushButton->setFont()
    ui->pushButton_2->setGeometry(this->width()*9/1050, this->height()*(513)/820, this->width()*ui->pushButton_2->width()/1050, this->height()*ui->pushButton_2->height()/820);
    if (landg=="Eng"){
        ui->pushButton_2->setText("Clear");
    }else{
        ui->pushButton_2->setText("Очистить");
    }
    ui->pushButton_2->setFont(FontLove);
    ui->comboBox->move(this->width()*9/1050, this->height()*(485)/820);
    ui->comboBox->resize(this->width()*75/1050, this->height()*25/820);
    ui->comboBox->addItem("C++");
    ui->comboBox->addItem("Pascal");
    ui->comboBox->addItem("Python");
    ui->comboBox->setFont(FontLove);
    //                                                                     ui->label->hide();
    NewBlock("ArrayWork", 0);
    //items[0]->move(0, 50);
    //ui->mainToolBar->addAction("Open", this, SLOT(OpenButton()));
    //ui->mainToolBar->addAction("Save", this, SLOT(SaveButton()));
    this->ui->mainToolBar->hide();
    connect(this->Timer1, SIGNAL(timeout()), this, SLOT(FollowMouse()));
    NewBlock("Begin", 0);
    PatternOfItems.push_back(items[items.size()-1]);
    NewBlock("End", 0);
    PatternOfItems.push_back(items[items.size()-1]);
    NewBlock("Arithmetic", 0);
    PatternOfItems.push_back(items[items.size()-1]);
    NewBlock("Out", 0);
    PatternOfItems.push_back(items[items.size()-1]);
    NewBlock("In", 0);
    PatternOfItems.push_back(items[items.size()-1]);
    NewBlock("If", 0);
    PatternOfItems.push_back(items[items.size()-1]);
    NewBlock("While", 0);
    PatternOfItems.push_back(items[items.size()-1]);
    //items[5]->Hide();
    //NewBlock("ArrayWork");
    //this->ui->label->hide();
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(PushButton()));
    connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(ClearButton()));
    //ui->lineEdit->setFocus();
    //QMessageBox::critical(this, "", QString::number(FontLove.pointSize()));
    repaint();
}

MainWindow::MainWindow(QWidget *parent, int type, QRect r, std::string lan) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->scrollArea_2->setWidget(ui->widget);
    landg=lan;
    TT=type;
    th=this;
    //this->Suk=Suka;
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    //QMessageBox::critical(this, QString::number(r.width()), QString::number(r.height()));
    //this->ScreenTop=r.top();
    //this->ScreenLeft=r.left();
    this->ScreenHeigth=r.height();
    this->ScreenWidth=r.width();
    ui->comboBox_2->hide();
    ui->scrollArea->hide();
    if (type==0){
        th->setGeometry(ScreenWidth/40, ScreenHeigth*5/860+30, ScreenWidth*105/160, ScreenHeigth*82/86);
        this->SetStartingSetting();
        ui->widget->hide();
        //QMessageBox::critical(this, QString::number((double)820/height()), QString::number((double)1050/height()));
        this1=this;
        //std::ofstream r1 ("1r4.settings");
        //r1 << "Russian";
    }else if (type==1){
        th->setGeometry(ScreenWidth*1100/1600, 50*ScreenHeigth/860+30, 440*ScreenWidth/1600, 730*ScreenHeigth/860);
        ui->pushButton->setEnabled(0);
        //ui->label->setEnabled(0);
        ui->menuBar->hide();
        ui->statusBar->hide();
        ui->scrollArea->hide();
        //ui->widget->hide();
        if (landg=="Eng")
            ui->label->setText("Powered by PCP blocks v1.0.4");
        else{
            ui->label->setText("При поддержке PCP blocks v1.0.4");
        }
        ui->label->setPalette(QPalette(QColor("#000000")));
        ui->label->setFont(QFont("Courier New", 11, QFont::NoFontMerging));
        int fh=15, fw=690;
        ui->label->setGeometry(5*width()/440, 702*height()/730, 690*width()/440, 15*height()/730);
        //ui->label->resize(690, 10);
        QFontMetrics f(ui->label->font());
        //QFontMetr f=ui->pushButton->font();
        int zh=fh*1000/f.height();
        int zw=fw*1000/f.width(ui->label->text());
        QFont fr=ui->label->font();
        for (;;){
            QFontMetrics k(fr);
            if (ui->label->height()*1000/k.height()>=zh && ui->label->width()*1000/k.width(ui->label->text())>=zw){
                //QMessageBox::critical(this, "", QString::number(fr.pointSize()));
                break;
            }
            fr.setPointSize(fr.pointSize()-1);
        }
        //ui->label->setFont(fr);
        //FontLove=fr;
        FontLove.setPointSize(fr.pointSize());
        ui->label->setFont(FontLove);
        ui->pushButton_2->setEnabled(0);
        ui->mainToolBar->setEnabled(0);
        ui->comboBox->setEnabled(0);
        ui->pushButton->hide();
        //ui->label->hide();
        ui->pushButton_2->hide();
        ui->mainToolBar->hide();
        ui->comboBox->hide();
        TE=new QTextEdit(this);
        TE->setReadOnly(1);
        TE->show();
        TE->setGeometry(10*width()/440, 10*height()/730, 420*width()/440, 690*height()/730);
        //TE->resize(420, 690);
        TE->setFont(FontLove);
        if (landg=="Eng")
            th->setWindowTitle("PCP blocks v1.0.4 Translate");
        else {
            th->setWindowTitle("PCP blocks v1.0.4 Перевод");
        }
        //this->ui->centralWidget->update();

    }else if (TT==2){
        th->setGeometry(ScreenWidth*150/1600, 75*ScreenHeigth/860+30, 800*ScreenWidth/1600, 554*ScreenHeigth/860);
        //ui->pushButton->setEnabled(0);
        //ui->label->setEnabled(0);
        ui->menuBar->hide();
        ui->statusBar->hide();
        ui->label->hide();
        if (landg=="Eng"){
            ui->pushButton->setText("Get started");
            ui->pushButton_2->setText("About program");
        }else{
            ui->pushButton->setText("Начать работу");
            ui->pushButton_2->setText("О программе");
        }
        //ui->pushButton->setPalette(QPalette(QColor("#000000")));
        ui->pushButton_2->setGeometry(670*width()/800, 510*height()/554, 100*width()/800, 30*height()/554);
        ui->pushButton->setGeometry(500*width()/800, 510*height()/554, 100*width()/800, 30*height()/554);
        ui->pushButton->setFont(QFont("Courier New", 11, QFont::NoFontMerging));
        int fh=25, fw=80;
        //ui->label->resize(690, 10);
        QFontMetrics f(ui->pushButton_2->font());
        //QFontMetr f=ui->pushButton->font();
        int zh=fh*1000/f.height();
        int zw=fw*1000/f.width(ui->pushButton_2->text());
        QFont fr=ui->pushButton_2->font();
        for (;;){
            QFontMetrics k(fr);
            if (ui->pushButton_2->height()*1000/k.height()>=zh && ui->pushButton_2->width()*1000/k.width(ui->pushButton_2->text())>=zw){
                //QMessageBox::critical(this, "", QString::number(fr.pointSize()));
                break;
            }
            fr.setPointSize(fr.pointSize()-1);
        }
        //ui->label->setFont(fr);
        //FontLove=fr;
        FontLove.setPointSize(fr.pointSize());
        ui->pushButton_2->setFont(FontLove);
        ui->pushButton->setFont(FontLove);
        //ui->pushButton_2->setEnabled(0);
        ui->mainToolBar->setEnabled(0);
        ui->comboBox->setEnabled(0);
        //ui->pushButton->hide();
        //ui->label->hide();
        //ui->pushButton_2->hide();
        ui->mainToolBar->hide();
        ui->comboBox->hide();
        ui->scrollArea->hide();
        //TE=new QTextEdit(this);
        //TE->setReadOnly(1);
        //TE->show();
        //TE->setGeometry(10*width()/440, 10*height()/730, 420*width()/440, 690*height()/730);
        //TE->resize(420, 690);
        //TE->setFont(FontLove);
        if (landg=="Eng")
            th->setWindowTitle("PCP blocks v1.0.4 greeting");
        else {
            th->setWindowTitle("PCP blocks v1.0.4 приветсвие");
        }
        connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(PushButton()));
        connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(ClearButton()));
    }else if (TT==3){
        th->setGeometry(ScreenWidth*150/1600, 75*ScreenHeigth/860+30, 795*ScreenWidth/1600, 592*ScreenHeigth/860);
        //ui->pushButton->setEnabled(0);
        //ui->label->setEnabled(0);
        ui->menuBar->hide();
        ui->statusBar->hide();
        ui->label->hide();
        ui->mainToolBar->hide();
        ui->comboBox->hide();
        ui->mainToolBar->setEnabled(0);
        ui->comboBox->setEnabled(0);
        ui->pushButton_2->hide();
        ui->pushButton->hide();
        ui->pushButton_2->setEnabled(0);
        ui->scrollArea->hide();
        ui->pushButton->setEnabled(0);
    }
    else if (TT==4){
            th->setGeometry(ScreenWidth*150/1600, 75*ScreenHeigth/860+30, 868*ScreenWidth/1600, 750*ScreenHeigth/860);
            ui->widget->show();
            //ui->pushButton->setEnabled(0);
            //ui->label->setEnabled(0);
            ui->menuBar->hide();
            ui->statusBar->hide();
            ui->label->hide();
            ui->mainToolBar->hide();
            ui->comboBox->hide();
            ui->mainToolBar->setEnabled(0);
            ui->comboBox->setEnabled(0);
            ui->pushButton_2->hide();
            ui->pushButton->hide();
            ui->pushButton_2->setEnabled(0);
            ui->pushButton->setEnabled(0);
            QString addresI;
            addresI=QDir::currentPath()+"/resources/RUCR.jpg";
            QLabel * imageLabel = new QLabel (this);
            QImage image(addresI);
            imageLabel->resize(868, 3844);
            imageLabel->setPixmap ( QPixmap :: fromImage (image));

            ui->scrollArea->setBackgroundRole ( QPalette :: Dark);
            //ui->scrollArea->setWidget (imageLabel);
            imageLabel->show();
            //ui->scrollArea->setWidget(ui->widget);
        }
    //Suk=new QDialog;

    //QWindow.;
    //Suk->setParent(this);
    //Suk->show();
}

//QWidget* SukO;

MainWindow::~MainWindow()
{
    /*if (Spr!=nullptr)
        delete Spr->ui;
    if (Ruco!=nullptr)
        delete Ruco->ui;
    if (Suk!=nullptr)
        delete Suk->ui;*/
    //SukO->destroyed();
    //SukO->~QWidget();
    //QMessageBox::critical(this, "", "");
    //delete Suk;
    //SukO->hide();
    //Suk=nullptr;
    //delete Suk;
    delete ui;
}

bool IsMassive (QString name){
    for (int i=0; i<name.length(); i++){
        if (name[i]=='[') {QMessageBox::critical(this1, name, "fuck");return true;}

    }
}

QString SGiveIndex(QString name){
    QString Te;
    for (int i=0; i<name.length(); i++){
        if (name[i]=='['){
            i++;
            for (; name[i]!=']' && i<name.length(); i++){
                Te+=name[i];

            }
            break;
        }
    }
    //QMessageBox::critical(this1, "", "");
    return Te;
}

QString TypeVariable (QString a, std::vector <Variable> VA){
    QString w="Number";
    if (a.length()==0){
        w="Trash";
        return w;
    }
    int kol=0;
    for (int i=0; i<a.length(); i++){
        if (a[i]=='"'){
            kol++;
        }
    }
    if (kol==2){
        if (a[0]=='"' && a[a.length()-1]=='"'){
            w="String";
            goto EndThisFunc;
        }else{
            w="Trash";
            goto EndThisFunc;
        }
    }else if (kol>2){
        if (a[0]=='"' && a[a.length()-1]=='"'){
            for (int j=1; j<a.length()-2; j++){
                if (a[j]=='"')
                    if (a[j-1]!='\\'){
                        w="Trash";
                        goto EndThisFunc;
                    }
            }
            w="String";
            goto EndThisFunc;
        }else{
            w="Trash";
            goto EndThisFunc;
        }
    }else{
        int uy=0;
        for (int i=0; i<a.length(); i++){
            if (!(a[i]>='0' && a[i]<='9')){
                if (a[i]=='.'){
                    if (w=="Number" && i>=1)
                        w="Number with point";
                    else{
                        w="Trash";
                        break;
                    }
                }else{
                    if ((a[i]>='a' && a[i]<='z') || (a[i]>='A' && a[i]<='Z') || a[i]=='_')
                        if (w=="Number")
                            if (i==0)
                                w="Variable name";
                            else{
                                w="Trash";
                                break;
                            }
                        else{
                            if (w!="Variable name"){
                                w="Trash";
                                break;
                            }
                        }
                    else if(a[i]=="[" && uy==0 && w=="Variable name"){

                        uy++;
                    }else if(a[i]=="]" && uy==1 && w=="Variable name"){

                        uy++;
                    }else{
                        w="Trash";
                        break;
                    }
                }
            }
        }
        if (uy==1){
            w="Trash";
        }else if (uy==2){
            QString Jt=SGiveIndex(a);
            QString Ok;
            Ok=TypeVariable(Jt, VA);
            if (Ok!="Number"){
                if (Ok=="Variable name") {
                    bool kk=0;
                    int l=0;
                    for (; l<VA.size(); l++){
                        if (Jt==VA[l].name){
                            kk=1;
                            break;
                        }
                    }
                    if (kk && (VA[l].type=="int" || VA[l].type=="integer")){
                        goto EndThisFunc;
                    }
                }
                w="Trash";
                goto EndThisFunc;
            }
        }
    }
    EndThisFunc:{}
    //QMessageBox::critical(this1, w, '('+a+')');
    return w;
}

bool MassiveRav(QString a, QString b){
    int i=0;
    for (; i<a.length(); i++){
        if (a[i]=='[')
            break;
    }
    int j=0;
    for (; j<b.length(); j++){
        if (b[j]=='[')
            break;
    }
    if (i<a.length() && j<b.length()){
        a.remove(i, a.length()-i);
        b.remove(j, b.length()-j);
        //QMessageBox::critical(this1, a, b);
        return a==b;
    }else if (i==a.length() && j==b.length()){
        //QMessageBox::critical(this1, a, b);
        return a==b;
    }else{
        //QMessageBox::critical(this1, a, b);
        return 0;
    }
}

QString MainWindow::IsArithmeticTrue(QString *Line, std::vector<Variable> Variables){
    QString Answer;
    std::vector <QString> op;
    QString temp;
    std::vector <int> LineOpers;
    for (int i=0; i<(*Line).length(); i++){
        if ((*Line)[i]==' '){

        }else if ((*Line)[i]=='"'){
            if (temp==""){
                temp+="\"";
                i++;
                for (; i<(*Line).length(); i++){
                    temp+=(*Line)[i];
                    if ((*Line)[i]=='"'){
                        break;
                    }
                }
                op.push_back(temp);
                temp="";
            }else{
                return "Trash";
            }
        }else if ((*Line)[i]=='+' || (*Line)[i]=='-' || (*Line)[i]=='*' || (*Line)[i]=='/' || (*Line)[i]=='^' || (*Line)[i]=='(' || (*Line)[i]==')' || (*Line)[i]=='%'){
            {
                op.push_back(temp);
                temp="";
                QString kl;
                kl+=(*Line)[i];
                LineOpers.push_back(i);
                op.push_back(kl);
            }
        }else{
            temp+=(*Line)[i];
        }
    }
    if (temp!=""){
        op.push_back(temp);
        temp="";
    }
    bool w=1;
    int y=0;
    for (int i=0; i<op.size(); i++){
        if (op[i]=='+' || op[i]=='-' || op[i]=='*' || op[i]=='/' || op[i]=='^' || op[i]=='(' || op[i]==')' || op[i]=='%'){

        }else{
            int j=0;
            for (; j<Variables.size(); j++){
                if (MassiveRav(op[i], Variables[j].name)){
                    //QMessageBox::critical(this, "", "");
                    if (Variables[j].type=="string"){
                        if (y==0 || w==0){
                           w=0;
                        }else{
                           return "Trash";
                        }
                    }else{
                        if (w==0){
                            return "Trash";
                        }
                    }
                    y++;
                    goto F;
                }
            }if (TypeVariable(op[i], Variables)!="Trash" && TypeVariable(op[i], Variables)!="Variable name"){
                if (TypeVariable(op[i], Variables)=="String"){
                    if (ui->comboBox->currentIndex()==1){
                        op[i][0]='\'';
                        op[i][op[i].length()-1]='\'';
                    }
                    if (y==0 || w==0){
                       w=0;
                    }else{
                       return "Trash";
                    }
                }else{
                    if (w==0){
                       return "Trash";
                    }
                }
            }else{
                //QMessageBox::critical(this, "", "");
                return "Trash";
            }
            y++;
        }
F:{}
    }
    std::vector <int> kol1I, kol2I;
    for (int i=LineOpers.size()-1; i>=0; i--){
        if ((*Line)[LineOpers[i]]=='('){
            kol1I.push_back(LineOpers[i]);
        }else if ((*Line)[LineOpers[i]]==')'){
            kol2I.push_back(LineOpers[i]);
        }else if ((*Line)[LineOpers[i]]=='%' && ui->comboBox->currentIndex()==1){
            (*Line).remove(LineOpers[i], 1);
            (*Line).insert(LineOpers[i], " mod ");
        }else if ((*Line)[LineOpers[i]]=='/' && ui->comboBox->currentIndex()==2){
            (*Line).remove(LineOpers[i], 1);
            (*Line).insert(LineOpers[i], "//");
        }else if ((*Line)[LineOpers[i]]=='/' && ui->comboBox->currentIndex()==1){
            (*Line).remove(LineOpers[i], 1);
            (*Line).insert(LineOpers[i], " div ");
        }
    }
    if (kol1I.size()!=kol2I.size()){
        //QMessageBox::critical(this, QString::number(kol1I.size()), QString::number(kol2I.size()));
        return "Trash";
    }
    QString T;
    for (int i=0; i<kol1I.size(); i++){
        T+="0";
    }
    QString Ans=T;
Fk:{}
    while (kol1I.size()>0 || kol2I.size()>0){
        if (kol2I.size()<=0 || kol1I[kol1I.size()-1]<kol2I[kol2I.size()-1]){
            T.remove(T.length()-1, 1);
            std::vector <int>::iterator iq=kol1I.begin()+(kol1I.size()-1);
            kol1I.erase(iq);
        }else{
            T+=')';
            std::vector <int>::iterator iq=kol2I.begin()+(kol2I.size()-1);
            kol2I.erase(iq);
        }
        //QMessageBox::critical(this, "("+T+")", "("+Ans+")");
        goto Fk;
    }
    if (T!=Ans){

        return "Trash";
    }
    if (w){
        //QMessageBox::critical(this, "int", "("+*Line+")");
        return "int";
    }
    //QMessageBox::critical(this, "string", "("+*Line+")");
    return "string";
}

QString SGiveName(QString name){
    int i=0;
    for (; name[i]!='['; i++);
    name.remove(i, name.length()-i);
    return name;
}

QString LastWord(QString Line){
    int i;
    for (i=Line.length(); i>=0 && Line[i]!=' '; i--);
    Line.remove(0, i+1);
    return Line;
}

std::vector <QString> MainWindow::Translate(item* MainItem, int ots, int y){
    MainItem->CodeLine.clear();
    if (ui->comboBox->currentIndex()==0){
        for (int i=0; i<MainItem->EnabledItems.size(); i++){
            MainItem->EnabledItems[i]->Status=-1;
                //QMessageBox::critical(this, "", MainItem->EnabledItems[i]->Type);
                if (libA[MainItem->EnabledItems[i]->Type]== 0){
                    MainItem->CodeLine.push_back("#include <bits/stdc++.h>");
                    MainItem->CodeLine.push_back("using namespace std;");
                    MainItem->CodeLine.push_back("int main(){");
                    ots++;
                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 1){
                    MainItem->CodeLine.push_back("return 0;");
                    for (int ot=0; ot<ots; ot++){
                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                    }
                    MainItem->CodeLine.push_back("}");
                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 3){
                    int Status=-1;
                    for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line.operator=(MainItem->EnabledItems[i]->Butt->Frame2[j]->text());
                        if (Line.length()!=0){
                            //Line+"\"";
                            std::vector <QString> op;
                            QString temp;
                            for (int q=0; q<Line.size(); q++){
                                QChar t;
                                t=Line[q];
                                if (t=='"'){
                                    temp+=t;
                                    int e=q+1;
                                    q++;
                                    for (; e<Line.size(); e++){
                                        if (Line[e]!='"'){
                                            temp+=Line[e];
                                            q++;
                                        }else{
                                            break;
                                        }
                                    }
                                    temp+='"';
                                    q++;
                                    op.push_back(temp);
                                    temp="";
                                }else
                                if (t==' '){
                                    if (temp.length()!=0){
                                        op.push_back(temp);
                                        temp="";
                                    }
                                }else{
                                    temp+=t;
                                }
                            }
                            if (temp.size()!=0){
                                op.push_back(temp);
                                temp="";
                            }
                            Step2:{}
                            if (op.size()>0){
                            MainItem->CodeLine.push_back("cout");
                            for (int ot=0; ot<ots; ot++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                            }
                            if (j>0){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]+=" << \"\\n\"";
                            }
                            bool wc=0;
                            for (int q=0; q<op.size(); q++){
                                QString Type=TypeVariable(op[q], MainItem->LineVariables);
                                if (Type=="Trash"){
                                    MainItem->EnabledItems[i]->Status=1;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                    std::vector<QString>::iterator itq = op.begin()+q;
                                    op.erase(itq);
                                    MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                    goto Step2;
                                }else{
                                    if (Type=="Variable name"){
                                        int wal=0;
                                        for (; wal<op[q].length(); wal++){
                                            if (op[q][wal]=='['){
                                                break;
                                            }
q:{}
                                        }

                                        QString ht=op[q];
                                        if (wal!=op[q].length()){
                                            ht.remove(wal, ht.length()-wal);
                                            QString Change=ht;
                                            ht=op[q];
                                            op[q]=Change;
                                            for (wal=0; wal<MainItem->LineVariables.size(); wal++){
                                                for (int Wt=0; Wt<MainItem->LineVariables[wal].name.length(); Wt++){
                                                    if (MainItem->LineVariables[wal].name[Wt]=='['){
                                                        QString Tt=MainItem->LineVariables[wal].name;
                                                        Tt.remove(Wt, Tt.length()-Wt);
                                                        if (op[q]==Tt){
                                                            op[q]=ht;
                                                            goto PointYes1;
                                                        }
                                                    }
                                                }
                                            }
                                            MainItem->EnabledItems[i]->Status=1;
                                            Status=std::max(Status,(MainItem->EnabledItems[i]->Status));
                                            std::vector<QString>::iterator itq = op.begin()+q;
                                            op.erase(itq);
                                            MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                            goto Step2;
                                        }else{
                                            for (wal=0; wal<MainItem->LineVariables.size(); wal++){
                                                if ((op[q])==MainItem->LineVariables[wal].name){
                                                    op[q]=ht;
                                                    goto PointYes1;
                                                }
                                            }
                                            MainItem->EnabledItems[i]->Status=1;
                                            Status=std::max(Status,(MainItem->EnabledItems[i]->Status));
                                            std::vector<QString>::iterator itq = op.begin()+q;
                                            op.erase(itq);
                                            MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                            goto Step2;
                                        }
                                    }else{
                                        PointYes1:{}
                                        if (Status<1){
                                            MainItem->EnabledItems[i]->Status=0;
                                            Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                        }
                                    }
                                }
                            }
                                for (int q=0; q<op.size(); q++){
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]+=" << "+op[q];
                                }
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]+=";";
                            }else{
                                if (Status<1){
                                    MainItem->EnabledItems[i]->Status=0;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                }
                                MainItem->CodeLine.push_back("cout << \"\\n\";");
                                for (int ot=0; ot<ots; ot++){
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                }
                            }
                        }else{
                            if (Status<1){
                                MainItem->EnabledItems[i]->Status=0;
                                Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                            }
                            MainItem->CodeLine.push_back("cout << \"\\n\";");
                            for (int ot=0; ot<ots; ot++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                            }
                        }
                    }
                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 4){ //IN
                    for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line.operator=(MainItem->EnabledItems[i]->Butt->Frame2[j]->text());
Bt:{}
                        if (Line.length()!=0){
                            //Line+"\"";
                            std::vector <QString> op;
                            QString temp;
                            for (int q=0; q<Line.size(); q++){
                                QChar t;
                                t=Line[q];
                                if (temp.length()==0 && t=='"'){
                                    temp+=t;
                                    int e=q+1;
                                    q++;
                                    for (; e<Line.size(); e++){
                                        if (Line[e]!='"'){
                                            temp+=Line[e];
                                            q++;
                                        }else{
                                            break;
                                        }
                                    }
                                    temp+='"';
                                    q++;
                                    op.push_back(temp);
                                    temp="";
                                }else
                                if (t==' '){
                                    if (temp.size()!=0){
                                        op.push_back(temp);
                                        temp="";
                                    }
                                }else{
                                    temp+=t;
                                }
                            }
                            if (temp.length()!=0){

                                op.push_back(temp);
                                temp="";
                            }
                            int Status=-1;

                            Step1:{}
                            if (MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked() && op.size()>0){
                                MainItem->CodeLine.push_back("cin");
                                for (int ot=0; ot<ots; ot++){
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                }
                            }
                            for (int q=0; q<op.size(); q++){
                                QString Type=TypeVariable(op[q], MainItem->LineVariables);
                                if (Type=="Variable name"){
                                    if (Status<1){
                                        MainItem->EnabledItems[i]->Status=0;
                                        Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                    }
                                }else{
                                    MainItem->EnabledItems[i]->Status=1;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                    std::vector<QString>::iterator itq = op.begin()+q;
                                    op.erase(itq);
                                    MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                    goto Step1;
                                }
                                if (Type=="Variable name"){
                                int u=0;
                                        for (; u<MainItem->LineVariables.size(); u++){
                                            if (MassiveRav(op[q], MainItem->LineVariables[u].name)){
                                                break;
                                            }
                                        }
                                        if (u==MainItem->LineVariables.size()){
                                            Variable ttt;
                                            ttt.name=op[q];
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==0)
                                                ttt.type="int";
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==1)
                                                ttt.type="double";
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==2)
                                                ttt.type="string";
                                            MainItem->LineVariables.push_back(ttt);
                                            std::vector <QString>::iterator iyo=MainItem->CodeLine.begin()+MainItem->CodeLine.size()-1;
                                            if (!MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked()) iyo++;
                                            MainItem->CodeLine.insert(iyo, ttt.type+" "+ttt.name+";");
                                            int qws=MainItem->CodeLine.size()-2;
                                            if (!MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked()) qws++;
                                            for (int ot=0; ot<ots; ot++){
                                                MainItem->CodeLine[qws]="   "+MainItem->CodeLine[qws];
                                            }
                                        }else{
                                            Variable ttt;
                                            ttt.name=op[q];
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==0)
                                                ttt.type="int";
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==1)
                                                ttt.type="double";
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==2)
                                                ttt.type="string";
                                        }
                                        if (MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked()){

                                            if (std::find((op[q]).begin(), op[q].end(), '[')!=op[q].end() && SGiveIndex(op[q])==SGiveIndex(MainItem->LineVariables[u].name)){
                                                //QMessageBox::warning(this, "this shit", "["+op[q]+"]");
                                                QString ML=MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                if (ML[ML.length()-1]!="n" && ML[ML.length()-2]!="i" && ML[ML.length()-3]!="c" && ML[ML.length()-4]!=" "){
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]+=";";
                                                    MainItem->CodeLine.push_back("{");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                }else{
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="{";
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                }
                                                    ots++;
                                                    MainItem->CodeLine.push_back("int __someVar_=0;");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    MainItem->CodeLine.push_back("while (__someVar_<"+SGiveIndex(op[q])+"){");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    ots++;
                                                    MainItem->CodeLine.push_back("cin >> "+SGiveName(op[q])+"[__someVar_];");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    MainItem->CodeLine.push_back("__someVar_=__someVar_+1;");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    ots--;
                                                    MainItem->CodeLine.push_back("}");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    ots--;
                                                    MainItem->CodeLine.push_back("}");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    for (int kl=q-1; kl>=0; kl--){
                                                        std::vector<QString>::iterator it=op.begin()+kl;
                                                        op.erase(it);
                                                    }
                                                    if (op.size()>1){
                                                        std::vector<QString>::iterator it=op.begin();
                                                        op.erase(it);
                                                        goto Step1;
                                                    }
                                            }
                                            else
                                                MainItem->CodeLine[MainItem->CodeLine.size()-1]+=" >> "+op[q];
                                        }
                                }
                            }
                            if (op.size()==0){
                                if (Status<1){
                                    MainItem->EnabledItems[i]->Status=0;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                }
                                MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                            }else{
                                if (MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked() && MainItem->CodeLine[MainItem->CodeLine.size()-1][MainItem->CodeLine[MainItem->CodeLine.size()-1].length()-1]!='}')
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]+=";";
                            }
                        }
                    }

                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 6 || libA[MainItem->EnabledItems[i]->Type]== 7){
                for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                    QString Line=MainItem->EnabledItems[i]->Butt->Frame2[j]->text();
                    //QMessageBox::critical(this, "", Line);
                    std::vector <QString> IfBlocks;
                    QString temp;
                    for (int Varii=0; Varii<Line.length(); Varii++){
                        if (Line[Varii]==' '){

                        }else if (Line[Varii]=='"'){
                            if (temp==""){
                                temp+=Line[Varii];
                                for (; Varii<Line.length(); Varii++){
                                    temp+=Line[Varii];
                                    if (Line[Varii]=='"'){
                                        break;
                                    }
                                }
                                //Varii++;
                                goto FFFF;
                            }else{
                                MainItem->EnabledItems[i]->Status=1;
                                goto FuckIWantSleep;
                            }
                        }else if((Line[Varii]=='&' && Varii<Line.length()-1 && Line[Varii+1]=='&') || (Line[Varii]=='|' && Varii<Line.length()-1 && Line[Varii+1]=='|')){
                            //if (temp!=""){
                                IfBlocks.push_back(temp);
                                temp="";
                                QString y;
                                y+=Line[Varii];
                                y+=Line[Varii];
                                IfBlocks.push_back(y);
                            //}
                            Varii++;
                        }else{
                            temp+=Line[Varii];
                        }
FFFF:{}
                    }
                    if (temp!=""){
                        IfBlocks.push_back(temp);
                        temp="";
                    }
                    //MainItem->EnabledItems[i]->Status=1;
                    //Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                    Line="";
                    if (IfBlocks.size()!=0){
                        for (int Vari=0; Vari<IfBlocks.size(); Vari++){
                            if (IfBlocks[Vari]=="&&" || IfBlocks[Vari]=="||"){
                                Line+=" "+IfBlocks[Vari]+" ";
                            }else{
                                for (int rq=0; rq<IfBlocks[Vari].length(); rq++){
                                    if (IfBlocks[Vari][rq]=='"'){
                                        temp+="\"";
                                        rq++;
                                        for (; rq<Line.length(); rq++){
                                            temp+=IfBlocks[Vari][rq];
                                            if (IfBlocks[Vari][rq]=='"'){
                                                goto PointL2;
                                            }
                                        }
                                        MainItem->EnabledItems[i]->Status=1;
                                        goto FuckIWantSleep;
                                    }else if (IfBlocks[Vari][rq]=='>' || IfBlocks[Vari][rq]=='<'){
                                        //IfBlocks[Vari].remove(0, rq);
                                        break;
                                    }else if ((IfBlocks[Vari][rq]=='=' || IfBlocks[Vari][rq]=='!')){
                                        if (IfBlocks[Vari].length()-1>Vari && IfBlocks[Vari][rq+1]=='='){
                                            //IfBlocks[Vari].remove(0, rq+1);
                                            break;
                                        }else{
                                            MainItem->EnabledItems[i]->Status=1;
                                            goto FuckIWantSleep;
                                        }
                                    }else{
                                        temp+=IfBlocks[Vari][rq];
                                    }
PointL2:{}
                                }
                                if (temp==Line){
                                    QString Type1=IsArithmeticTrue(&IfBlocks[Vari], MainItem->LineVariables);
                                    if (Type1!="int"){
                                        MainItem->EnabledItems[i]->Status=1;
                                        goto FuckIWantSleep;
                                    }else{
                                        Line+=IfBlocks[Vari];
                                    }
                                }
                                IfBlocks[Vari].remove(0, temp.length());
                                QString Type1=IsArithmeticTrue(&temp, MainItem->LineVariables);
                                QString T;
                                if (IfBlocks[Vari][0]=='>' || IfBlocks[Vari][0]=='<'){
                                    T=IfBlocks[Vari][0];
                                }else{
                                    T+=IfBlocks[Vari][0];
                                    T+=IfBlocks[Vari][1];
                                }
                                IfBlocks[Vari].remove(0, T.length());
                                QString Type2=IsArithmeticTrue(&IfBlocks[Vari], MainItem->LineVariables);
                                if (Type1==Type2 && Type1!="Trash"){

                                }else{
                                    MainItem->EnabledItems[i]->Status=1;
                                    goto FuckIWantSleep;
                                }
                                Line+=temp+T+IfBlocks[Vari];
                                //MainItem->EnabledItems[i]->Status=0;
                            }
                            temp="";
                        }
                    }else{
                        MainItem->EnabledItems[i]->Status=1;
                        goto FuckIWantSleep;
                    }

                    MainItem->EnabledItems[i]->Status=0;
                    if (libA[MainItem->EnabledItems[i]->Type]== 6){
                        MainItem->CodeLine.push_back("if("+Line+"){");
                        for (int ot=0; ot<ots; ot++){
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                        }

                        MainItem->EnabledItems[i]->MyItems[1]->LineVariables=MainItem->LineVariables;
                        MainItem->EnabledItems[i]->MyItems[1]->KolFuckVariable=MainItem->LineVariables.size();
                        std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i]->MyItems[1], ots+1, 0);
                        for (int key=0; key<IHateThisProgramm.size(); key++){
                            MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                        }
                        MainItem->CodeLine.push_back("}else{");
                        for (int ot=0; ot<ots; ot++){
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                        }
                    }else{
                        MainItem->CodeLine.push_back("while("+Line+"){");
                        for (int ot=0; ot<ots; ot++){
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                        }
                    }
                    MainItem->EnabledItems[i]->MyItems[0]->LineVariables=MainItem->LineVariables;
                    MainItem->EnabledItems[i]->MyItems[0]->KolFuckVariable=MainItem->LineVariables.size();
                    std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i]->MyItems[0], ots+1, 0);
                    for (int key=0; key<IHateThisProgramm.size(); key++){
                        MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                    }
                    MainItem->CodeLine.push_back("}");
                    for (int ot=0; ot<ots; ot++){
                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                    }
                }
FuckIWantSleep:{}
                }else
                if (MainItem->EnabledItems[i]->Type=="Pattern"){

                    MainItem->EnabledItems[i]->LineVariables=MainItem->LineVariables;
                    MainItem->EnabledItems[i]->KolFuckVariable=MainItem->LineVariables.size();
                    std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i], ots, 1);
                    for (int key=0; key<IHateThisProgramm.size(); key++){
                        MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                    }
                    MainItem->LineVariables=MainItem->EnabledItems[i]->LineVariables;
                    //MainItem->KolFuckVariable=MainItem->EnabledItems[i]->KolFuckVariable;
                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 2){
                    for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line=MainItem->EnabledItems[i]->Butt->Frame2[j]->text();
                        QString temp;
                        for (int r=0; r<Line.length(); r++){
                            if (Line[r]=='"'){
                                temp+="\"";
                                r++;
                                for (; r<Line.length(); r++){
                                    temp+=Line[r];
                                    if (Line[r]=='"'){
                                        goto PointL;
                                    }
                                }
                                MainItem->EnabledItems[i]->Status=1;
                                goto EdThisM;
                            }else if (Line[r]=='='){
                                Line.remove(0, r+1);
                                break;
                            }else{
                                temp+=Line[r];
                            }
                            PointL:{}
                        }
                        //QMessageBox::critical(this, "("+temp+")", "");
                        if (temp==Line || TypeVariable(temp, MainItem->LineVariables)!="Variable name"){
OhhhhYeeeee:{}
                            MainItem->EnabledItems[i]->Status=1;
                            goto EdThisM;
                        }
                        for (int r=0; r<MainItem->LineVariables.size(); r++){
                            if (MassiveRav(MainItem->LineVariables[r].name, temp)){
                                if (((IsArithmeticTrue(&Line, MainItem->LineVariables)=="int" && (MainItem->LineVariables[r].type=="int" || MainItem->LineVariables[r].type=="double")) || (IsArithmeticTrue(&Line, MainItem->LineVariables)=="string" && MainItem->LineVariables[r].type=="string")) && MainItem->EnabledItems[i]->Status<1){
                                    Line+=";";
                                    MainItem->EnabledItems[i]->Status=0;
                                    MainItem->CodeLine.push_back(temp+"="+Line);
                                    for (int ot=0; ot<ots; ot++){
                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                    }
                                    goto Eggs;
                                }else{
                                    //QMessageBox::critical(this, "", IsArithmeticTrue(Line, LineVariables));
                                    MainItem->EnabledItems[i]->Status=1;
                                }
                            }
                        }
                        goto OhhhhYeeeee;
Eggs:{}
                    }
EdThisM:{}

                }
        }

        /*if (y==0 && MainItem->CodeLine.size()!=0 && MainItem->CodeLine[0]=="#include <bits/stdc++.h>")
            for (int i=0; i<MainItem->LineVariables.size(); i++){
                std::vector<QString>::iterator it=MainItem->CodeLine.begin()+3;
                MainItem->CodeLine.insert(it, "");
                MainItem->CodeLine[3]+=MainItem->LineVariables[i].type+" "+MainItem->LineVariables[i].name+";";
                for (int ot=0; ot<ots; ot++){
                    MainItem->CodeLine[3]="   "+MainItem->CodeLine[3];
                }
            }
        else{
            if (y==0)
            for (int i=MainItem->KolFuckVariable; i<MainItem->LineVariables.size(); i++){
                std::vector<QString>::iterator it=MainItem->CodeLine.begin();
                MainItem->CodeLine.insert(it, "");
                MainItem->CodeLine[0]+=MainItem->LineVariables[i].type+" "+MainItem->LineVariables[i].name+";";
                for (int ot=0; ot<ots; ot++){
                    MainItem->CodeLine[0]="   "+MainItem->CodeLine[0];
                }
            }
        }*/

        return MainItem->CodeLine;
    }else if (ui->comboBox->currentIndex()==1){
        for (int i=0; i<MainItem->EnabledItems.size(); i++){
            if (libA[MainItem->EnabledItems[i]->Type]== 0){
                MainItem->CodeLine.push_back("Begin");
                ots++;
            }
            else
            if (libA[MainItem->EnabledItems[i]->Type]== 1){
                ots--;
                MainItem->CodeLine.push_back("End.");
                for (int ot=0; ot<ots; ot++){
                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                }
                //MainItem->CodeLine.push_back("}");
            }
            else
            if (libA[MainItem->EnabledItems[i]->Type]== 3){
                int Status=-1;
                for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                    QString Line;
                    Line.operator=(MainItem->EnabledItems[i]->Butt->Frame2[j]->text());
                    if (Line.length()!=0){
                        //Line+"\"";
                        std::vector <QString> op;
                        QString temp;
                        for (int q=0; q<Line.size(); q++){
                            QChar t;
                            t=Line[q];
                            if (t=='"'){
                                temp+=t;
                                int e=q+1;
                                q++;
                                for (; e<Line.size(); e++){
                                    if (Line[e]!='"'){
                                        temp+=Line[e];
                                        q++;
                                    }else{
                                        break;
                                    }
                                }
                                temp+='"';
                                q++;
                                op.push_back(temp);
                                temp="";
                            }else
                            if (t==' '){
                                if (temp.length()!=0){
                                    op.push_back(temp);
                                    temp="";
                                }
                            }else{
                                temp+=t;
                            }
                        }
                        if (temp.size()!=0){
                            op.push_back(temp);
                            temp="";
                        }
                        Step2P:{}
                        if (op.size()>0){
                        MainItem->CodeLine.push_back("Write(");

                        if (MainItem->EnabledItems[i]->Butt->Frame2.size()>1 && j!=MainItem->EnabledItems[i]->Butt->Frame2.size()-1){
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="Writeln(";
                        }
                        for (int ot=0; ot<ots; ot++){
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                        }
                        bool wc=0;
                        for (int q=0; q<op.size(); q++){
                            QString Type=TypeVariable(op[q], MainItem->LineVariables);
                            if (Type=="Trash"){
                                MainItem->EnabledItems[i]->Status=1;
                                Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                std::vector<QString>::iterator itq = op.begin()+q;
                                op.erase(itq);
                                MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                goto Step2P;
                            }else{
                                if (Type=="Variable name"){
                                    for (int wal=0; wal<items[0]->LineVariables.size(); wal++){
                                        if (MassiveRav(op[q], items[0]->LineVariables[wal].name)){
                                            goto PointYes1P;
                                        }
                                    }
                                    MainItem->EnabledItems[i]->Status=1;
                                    Status=std::max(Status,(MainItem->EnabledItems[i]->Status));
                                    std::vector<QString>::iterator itq = op.begin()+q;
                                    op.erase(itq);
                                    MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                    goto Step2P;
                                }else{
                                    if (Type=="String"){
                                        op[q][0]='\'';
                                        op[q][op[q].length()-1]='\'';
                                    }
                                    PointYes1P:{}
                                    if (Status<1){
                                        MainItem->EnabledItems[i]->Status=0;
                                        Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                    }
                                }
                            }
                        }
                        if (op.size()!=0){
                         MainItem->CodeLine[MainItem->CodeLine.size()-1]+=op[0];
                        }
                            for (int q=1; q<op.size(); q++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]+=", "+op[q];
                            }
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]+=");";
                        }else{
                            if (Status<1){
                                MainItem->EnabledItems[i]->Status=0;
                                Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                            }
                            MainItem->CodeLine.push_back("Writeln()");
                            for (int ot=0; ot<ots; ot++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                            }
                        }
                    }else{
                        if (Status<1){
                            MainItem->EnabledItems[i]->Status=0;
                            Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                        }
                        MainItem->CodeLine.push_back("Writeln()");
                        for (int ot=0; ot<ots; ot++){
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                        }
                    }
                }
            }
            else
            if (libA[MainItem->EnabledItems[i]->Type]== 4){ //IN
                for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                    QString Line;
                    Line.operator=(MainItem->EnabledItems[i]->Butt->Frame2[j]->text());
                    if (Line.length()!=0){
                        //Line+"\"";
                        std::vector <QString> op;
                        QString temp;
                        for (int q=0; q<Line.size(); q++){
                            QChar t;
                            t=Line[q];
                            if (temp.length()==0 && t=='"'){
                                temp+=t;
                                int e=q+1;
                                q++;
                                for (; e<Line.size(); e++){
                                    if (Line[e]!='"'){
                                        temp+=Line[e];
                                        q++;
                                    }else{
                                        break;
                                    }
                                }
                                temp+='"';
                                q++;
                                op.push_back(temp);
                                temp="";
                            }else
                            if (t==' '){
                                if (temp.size()!=0){
                                    op.push_back(temp);
                                    temp="";
                                }
                            }else{
                                temp+=t;
                            }
                        }
                        if (temp.length()!=0){
                            op.push_back(temp);
                            temp="";
                        }
                        int Status=-1;

                        Step1P:{}
                        QString Shab;
                        if (MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked() && op.size()>0){
                            MainItem->CodeLine.push_back("read(");
                            for (int ot=0; ot<ots; ot++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                            }
                            Shab=MainItem->CodeLine[MainItem->CodeLine.size()-1];
                        }
                        for (int q=0; q<op.size(); q++){
                            QString Type=TypeVariable(op[q], items[0]->LineVariables);
                            if (Type=="Variable name"){
                                if (Status<1){
                                    MainItem->EnabledItems[i]->Status=0;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                }
                            }else{
                                MainItem->EnabledItems[i]->Status=1;
                                Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                std::vector<QString>::iterator itq = op.begin()+q;
                                op.erase(itq);
                                MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                goto Step1P;
                            }
                            if (Type=="Variable name"){
                            int u=0;
                                    for (; u<items[0]->LineVariables.size(); u++){
                                        if (MassiveRav(op[q], items[0]->LineVariables[u].name)){
                                            break;
                                        }
                                    }
                                    if (u==items[0]->LineVariables.size()){
                                        Variable ttt;
                                        ttt.name=op[q];
                                        if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==0)
                                            ttt.type="integer";
                                        if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==1)
                                            ttt.type="real";
                                        if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==2)
                                            ttt.type="string";
                                        items[0]->LineVariables.push_back(ttt);
                                        //MainItem->LineVariables.push_back(ttt);
                                        //MainItem->KolFuckVariable++;
                                    }else{
                                        Variable ttt;
                                        ttt.name=items[0]->LineVariables[u].name;
                                        if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==0)
                                            ttt.type="integer";
                                        if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==1)
                                            ttt.type="real";
                                        if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==2)
                                            ttt.type="string";
                                        //items[0]->LineVariables[u]=(ttt);

                                    }
                                    if (MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked()){
                                        if (std::find((op[q]).begin(), op[q].end(), '[')!=op[q].end() && SGiveIndex(op[q])==SGiveIndex(MainItem->LineVariables[u].name)){
                                            int uMassive=0;
                                            for (; uMassive<items[0]->LineVariables.size() && !MassiveRav("__someVar_", items[0]->LineVariables[uMassive].name); uMassive++);
                                            if (uMassive==items[0]->LineVariables.size()){
                                                Variable ttt;
                                                ttt.name="__someVar_";
                                                if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==0)
                                                    ttt.type="integer";
                                                items[0]->LineVariables.push_back(ttt);
                                            }
                                            QString ML=MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                            if (!(LastWord(ML)=="read(" || LastWord(ML)=="readln(")){
                                                MainItem->CodeLine[MainItem->CodeLine.size()-1]+=");";
                                                MainItem->CodeLine.push_back("__someVar_:=0;");
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                }
                                            }else{
                                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="__someVar_:=0;";
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                }
                                            }
                                                MainItem->CodeLine.push_back("while __someVar_<"+SGiveIndex(op[q])+" do");
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                }
                                                MainItem->CodeLine.push_back("Begin");
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                }
                                                ots++;
                                                MainItem->CodeLine.push_back("read("+SGiveName(op[q])+"[__someVar_]);");
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                }
                                                MainItem->CodeLine.push_back("__someVar_:=__someVar_+1;");
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                }
                                                ots--;
                                                MainItem->CodeLine.push_back("End;");
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                }
                                                for (int kl=q-1; kl>=0; kl--){
                                                    std::vector<QString>::iterator it=op.begin()+kl;
                                                    op.erase(it);
                                                }
                                                if (op.size()>1){
                                                    std::vector<QString>::iterator it=op.begin();
                                                    op.erase(it);
                                                    goto Step1P;
                                                }
                                        }
                                        else
                                         if(MainItem->CodeLine[MainItem->CodeLine.size()-1]==Shab)
                                             MainItem->CodeLine[MainItem->CodeLine.size()-1]+=op[q];
                                         else
                                             MainItem->CodeLine[MainItem->CodeLine.size()-1]+=", "+op[q];
                                    }
                            }
                        }
                        if (op.size()==0){
                            if (Status<1){
                                MainItem->EnabledItems[i]->Status=0;
                                Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                            }
                            MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                        }else{
                            if (MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked() && !(LastWord(MainItem->CodeLine[MainItem->CodeLine.size()-1])=="End;"))
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]+=");";
                        }
                    }
                }
            }
            else
            if (libA[MainItem->EnabledItems[i]->Type]== 6 || libA[MainItem->EnabledItems[i]->Type]== 7){
            for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                QString Line=MainItem->EnabledItems[i]->Butt->Frame2[j]->text();
                //QMessageBox::critical(this, "", Line);
                std::vector <QString> IfBlocks;
                QString temp;
                for (int Varii=0; Varii<Line.length(); Varii++){
                    if (Line[Varii]==' '){

                    }else if (Line[Varii]=='"'){
                        if (temp==""){
                            temp+=Line[Varii];
                            for (; Varii<Line.length(); Varii++){
                                temp+=Line[Varii];
                                if (Line[Varii]=='"'){
                                    break;
                                }
                            }
                            //Varii++;
                            goto FFFFP;
                        }else{
                            MainItem->EnabledItems[i]->Status=1;
                            goto FuckIWantSleepP;
                        }
                    }else if((Line[Varii]=='&' && Varii<Line.length()-1 && Line[Varii+1]=='&') || (Line[Varii]=='|' && Varii<Line.length()-1 && Line[Varii+1]=='|')){
                        //if (temp!=""){
                            IfBlocks.push_back(temp);
                            temp="";
                            QString y;
                            y+=Line[Varii];
                            y+=Line[Varii];
                            IfBlocks.push_back(y);
                        //}
                        Varii++;
                    }else{
                        temp+=Line[Varii];
                    }
 FFFFP:{}
                }
                if (temp!=""){
                    IfBlocks.push_back(temp);
                    temp="";
                }
                //MainItem->EnabledItems[i]->Status=1;
                //Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                Line="";
                if (IfBlocks.size()!=0){
                    for (int Vari=0; Vari<IfBlocks.size(); Vari++){
                        if (IfBlocks[Vari]=="&&" || IfBlocks[Vari]=="||"){
                            if (IfBlocks[Vari]=="&&")
                                Line+=" and ";
                            else
                                Line+=" or ";
                        }else{
                            bool Ok=0;
                            for (int rq=0; rq<IfBlocks[Vari].length(); rq++){
                                if (IfBlocks[Vari][rq]=='"'){
                                    temp+="\"";
                                    rq++;
                                    for (; rq<Line.length(); rq++){
                                        temp+=IfBlocks[Vari][rq];
                                        if (IfBlocks[Vari][rq]=='"'){
                                            goto PointL2P;
                                        }
                                    }
                                    MainItem->EnabledItems[i]->Status=1;
                                    goto FuckIWantSleepP;
                                }else if (IfBlocks[Vari][rq]=='>' || IfBlocks[Vari][rq]=='<'){
                                    Ok=1;
                                    break;
                                }else if ((IfBlocks[Vari][rq]=='=' || IfBlocks[Vari][rq]=='!')){
                                    if (IfBlocks[Vari].length()-1>Vari && IfBlocks[Vari][rq+1]=='='){
                                        Ok=1;
                                        break;
                                    }else{
                                        MainItem->EnabledItems[i]->Status=1;
                                        goto FuckIWantSleepP;
                                    }
                                }else{
                                    temp+=IfBlocks[Vari][rq];
                                }
PointL2P:{}
                            }
                            if (!Ok){
                                //QMessageBox::critical(this, "("+temp+")", Line);
                                MainItem->EnabledItems[i]->Status=1;
                                goto FuckIWantSleepP;
                            }
                            IfBlocks[Vari].remove(0, temp.length());
                            QString Type1=IsArithmeticTrue(&temp, items[0]->LineVariables);
                            QString T;
                            if (IfBlocks[Vari][0]=='>' || IfBlocks[Vari][0]=='<'){
                                T=IfBlocks[Vari][0];
                            }else{
                                T+=IfBlocks[Vari][0];
                                T+=IfBlocks[Vari][1];
                            }
                            IfBlocks[Vari].remove(0, T.length());
                            QString Type2=IsArithmeticTrue(&IfBlocks[Vari], items[0]->LineVariables);
                            if (Type1==Type2 && Type1!="Trash"){

                            }else{
                                MainItem->EnabledItems[i]->Status=1;
                                goto FuckIWantSleepP;
                            }
                            if (T=="==")
                                T="=";
                            if (T=="!=")
                                T="<>";
                            Line+="("+temp+T+IfBlocks[Vari]+")";
                            //QMessageBox::critical(this, "("+temp+")", Line);
                            if ("("+temp+")"==Line){
                                //QMessageBox::critical(this, "("+temp+")", Line);
                                MainItem->EnabledItems[i]->Status=1;
                                goto FuckIWantSleepP;
                            }
                        }
                        temp="";
                    }
                }else{
                    MainItem->EnabledItems[i]->Status=1;
                    goto FuckIWantSleepP;
                }
                MainItem->EnabledItems[i]->Status=0;
                if (libA[MainItem->EnabledItems[i]->Type]== 6){
                    MainItem->CodeLine.push_back("if "+Line+" then");

                    for (int ot=0; ot<ots; ot++){
                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                    }
                    MainItem->CodeLine.push_back("begin");
                    for (int ot=0; ot<ots; ot++){
                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                    }
                    MainItem->EnabledItems[i]->MyItems[1]->LineVariables=MainItem->LineVariables;
                    MainItem->EnabledItems[i]->MyItems[1]->KolFuckVariable=MainItem->LineVariables.size();
                    std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i]->MyItems[1], ots+1, 0);
                    for (int key=0; key<IHateThisProgramm.size(); key++){
                        MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                    }
                    MainItem->CodeLine.push_back("end");
                    for (int ot=0; ot<ots; ot++){
                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                    }
                    MainItem->CodeLine.push_back("else");
                    for (int ot=0; ot<ots; ot++){
                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                    }
                }else{
                    MainItem->CodeLine.push_back("while "+Line+" do");
                    for (int ot=0; ot<ots; ot++){
                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                    }
                }
                MainItem->CodeLine.push_back("begin");
                for (int ot=0; ot<ots; ot++){
                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                }
                MainItem->EnabledItems[i]->MyItems[0]->LineVariables=MainItem->LineVariables;
                MainItem->EnabledItems[i]->MyItems[0]->KolFuckVariable=MainItem->LineVariables.size();
                std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i]->MyItems[0], ots+1, 0);
                for (int key=0; key<IHateThisProgramm.size(); key++){
                    MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                }
                MainItem->CodeLine.push_back("end;");
                for (int ot=0; ot<ots; ot++){
                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                }
            }
 FuckIWantSleepP:{}
            }else
            if (MainItem->EnabledItems[i]->Type=="Pattern"){

                MainItem->EnabledItems[i]->LineVariables=MainItem->LineVariables;
                MainItem->EnabledItems[i]->KolFuckVariable=MainItem->LineVariables.size();
                std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i], ots, 1);
                for (int key=0; key<IHateThisProgramm.size(); key++){
                    MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                }
                std::vector<Variable> V=MainItem->EnabledItems[i]->LineVariables;
                for (int lr=V.size()-1; lr>=0; lr--){
                    for (int lt=0; lt<MainItem->LineVariables.size(); lt++){
                        if (MassiveRav(V[lr].name, MainItem->LineVariables[lt].name)){
                            goto Fio;
                        }
                    }
                    MainItem->LineVariables.push_back(V[lr]);
Fio:{}
                }
                //MainItem->KolFuckVariable=MainItem->EnabledItems[i]->KolFuckVariable;
            }
            else
            if (libA[MainItem->EnabledItems[i]->Type]== 2){
                for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                    QString Line;
                    Line=MainItem->EnabledItems[i]->Butt->Frame2[j]->text();
                    QString temp;
                    for (int r=0; r<Line.length(); r++){
                        if (Line[r]=='"'){
                            temp+="\"";
                            r++;
                            for (; r<Line.length(); r++){
                                temp+=Line[r];
                                if (Line[r]=='"'){
                                    goto PointLP;
                                }
                            }
                            MainItem->EnabledItems[i]->Status=1;
                            goto EdThisMP;
                        }else if (Line[r]=='='){
                            Line.remove(0, r+1);
                            break;
                        }else{
                            temp+=Line[r];
                        }
                        PointLP:{}
                    }
                    //QMessageBox::critical(this, "("+temp+")", "");
                    if (temp==Line || TypeVariable(temp, items[0]->LineVariables)!="Variable name"){
 OhhhhYeeeeeP:{}
                        MainItem->EnabledItems[i]->Status=1;
                        goto EdThisMP;
                    }
                    for (int r=0; r<items[0]->LineVariables.size(); r++){
                        if (MassiveRav(items[0]->LineVariables[r].name, temp)){
                            if (((IsArithmeticTrue(&Line, items[0]->LineVariables)=="int" && (items[0]->LineVariables[r].type=="integer" || items[0]->LineVariables[r].type=="real")) || (IsArithmeticTrue(&Line, items[0]->LineVariables)=="string" && items[0]->LineVariables[r].type=="string")) && items[0]->EnabledItems[i]->Status<1){
                                Line+=";";
                                MainItem->EnabledItems[i]->Status=0;
                                MainItem->CodeLine.push_back(temp+":="+Line);
                                for (int ot=0; ot<ots; ot++){
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                }
                                goto EggsP;
                            }else{
                                //QMessageBox::critical(this, "", IsArithmeticTrue(Line, LineVariables));
                                MainItem->EnabledItems[i]->Status=1;
                            }
                        }
                    }
                    goto OhhhhYeeeeeP;
 EggsP:{}
                }
 EdThisMP:{}

            }

         }
         std::vector<QString>::iterator it1=MainItem->CodeLine.begin();
         if (MainItem->LineVariables.size()>MainItem->KolFuckVariable)
             MainItem->CodeLine.insert(it1, "Var");
         for (int i=MainItem->KolFuckVariable; i<MainItem->LineVariables.size(); i++){
             std::vector<QString>::iterator it=MainItem->CodeLine.begin()+1;
             MainItem->CodeLine.insert(it, "");
             MainItem->CodeLine[1]+=MainItem->LineVariables[i].name+" : "+MainItem->LineVariables[i].type+";";
             for (int ot=0; ot<ots; ot++){
                 MainItem->CodeLine[1]="   "+MainItem->CodeLine[1];
             }

         }
         return MainItem->CodeLine;

    }else{
        for (int i=0; i<MainItem->EnabledItems.size(); i++){
            MainItem->EnabledItems[i]->Status=-1;
                //QMessageBox::critical(this, "", MainItem->EnabledItems[i]->Type);
                if (libA[MainItem->EnabledItems[i]->Type]== 0){
                    MainItem->CodeLine.push_back("def main():");
                    ots++;
                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 1){
                    MainItem->CodeLine.push_back("\n");
                    MainItem->CodeLine.push_back("if __name__ == \"__main__\":");
                    MainItem->CodeLine.push_back("main()");
                    for (int ot=0; ot<ots; ot++){
                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                    }
                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 3){
                    int Status=-1;
                    for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line.operator=(MainItem->EnabledItems[i]->Butt->Frame2[j]->text());
                        if (Line.length()!=0){
                            //Line+"\"";
                            std::vector <QString> op;
                            QString temp;
                            for (int q=0; q<Line.size(); q++){
                                QChar t;
                                t=Line[q];
                                if (t=='"'){
                                    temp+=t;
                                    int e=q+1;
                                    q++;
                                    for (; e<Line.size(); e++){
                                        if (Line[e]!='"'){
                                            temp+=Line[e];
                                            q++;
                                        }else{
                                            break;
                                        }
                                    }
                                    temp+='"';
                                    q++;
                                    op.push_back(temp);
                                    temp="";
                                }else
                                if (t==' '){
                                    if (temp.length()!=0){
                                        op.push_back(temp);
                                        temp="";
                                    }
                                }else{
                                    temp+=t;
                                }
                            }
                            if (temp.size()!=0){
                                op.push_back(temp);
                                temp="";
                            }
                            Step2M:{}
                            if (op.size()>0){
                            MainItem->CodeLine.push_back("print(");
                            for (int ot=0; ot<ots; ot++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                            }
                            bool wc=0;
                            for (int q=0; q<op.size(); q++){
                                QString Type=TypeVariable(op[q], MainItem->LineVariables);
                                if (Type=="Trash"){
                                    MainItem->EnabledItems[i]->Status=1;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                    std::vector<QString>::iterator itq = op.begin()+q;
                                    op.erase(itq);
                                    MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                    goto Step2M;
                                }else{
                                    if (Type=="Variable name"){
                                        int wal=0;
                                        for (; wal<op[q].length(); wal++){
                                            if (op[q][wal]=='['){
                                                break;
                                            }
qM:{}
                                        }

                                        QString ht=op[q];
                                        if (wal!=op[q].length()){
                                            ht.remove(wal, ht.length()-wal);
                                            QString Change=ht;
                                            ht=op[q];
                                            op[q]=Change;
                                            for (wal=0; wal<MainItem->LineVariables.size(); wal++){
                                                for (int Wt=0; Wt<MainItem->LineVariables[wal].name.length(); Wt++){
                                                    if (MainItem->LineVariables[wal].name[Wt]=='['){
                                                        QString Tt=MainItem->LineVariables[wal].name;
                                                        Tt.remove(Wt, Tt.length()-Wt);
                                                        if (op[q]==Tt){
                                                            op[q]=ht;
                                                            goto PointYes1M;
                                                        }
                                                    }
                                                }
                                            }
                                            MainItem->EnabledItems[i]->Status=1;
                                            Status=std::max(Status,(MainItem->EnabledItems[i]->Status));
                                            std::vector<QString>::iterator itq = op.begin()+q;
                                            op.erase(itq);
                                            MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                            goto Step2M;
                                        }else{
                                            for (wal=0; wal<MainItem->LineVariables.size(); wal++){
                                                if ((op[q])==MainItem->LineVariables[wal].name){
                                                    op[q]=ht;
                                                    goto PointYes1M;
                                                }
                                            }
                                            MainItem->EnabledItems[i]->Status=1;
                                            Status=std::max(Status,(MainItem->EnabledItems[i]->Status));
                                            std::vector<QString>::iterator itq = op.begin()+q;
                                            op.erase(itq);
                                            MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                            goto Step2M;
                                        }
                                    }else{
                                        PointYes1M:{}
                                        if (Status<1){
                                            MainItem->EnabledItems[i]->Status=0;
                                            Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                        }
                                    }
                                }
                            }
                                for (int q=0; q<op.size(); q++){
                                    if (!q==0) MainItem->CodeLine[MainItem->CodeLine.size()-1]+=", "+op[q];
                                    else
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]+=op[q];
                                }
                                if (j<MainItem->EnabledItems[i]->Butt->Frame2.size()-1 && MainItem->EnabledItems[i]->Butt->Frame2.size()>1){
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]+=", \"\\n\"";
                                }
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]+=")";
                            }else{
                                if (Status<1){
                                    MainItem->EnabledItems[i]->Status=0;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                }
                                if (j<MainItem->EnabledItems[i]->Butt->Frame2.size()-1 && MainItem->EnabledItems[i]->Butt->Frame2.size()>1){
                                    MainItem->CodeLine.push_back("print(\"\\n\")");
                                }else
                                MainItem->CodeLine.push_back("print(\"\")");
                                for (int ot=0; ot<ots; ot++){
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                }
                            }
                        }else{
                            if (Status<1){
                                MainItem->EnabledItems[i]->Status=0;
                                Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                            }
                            if (j<MainItem->EnabledItems[i]->Butt->Frame2.size()-1 && MainItem->EnabledItems[i]->Butt->Frame2.size()>1){
                                MainItem->CodeLine.push_back("print(\"\\n\")");
                            }else
                            MainItem->CodeLine.push_back("print(\"\")");
                            for (int ot=0; ot<ots; ot++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                            }
                        }
                    }
                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 4){ //IN
                    for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line.operator=(MainItem->EnabledItems[i]->Butt->Frame2[j]->text());
                        if (Line.length()!=0){
                            //Line+"\"";
                            std::vector <QString> op;
                            QString temp;
                            for (int q=0; q<Line.size(); q++){
                                QChar t;
                                t=Line[q];
                                if (temp.length()==0 && t=='"'){
                                    temp+=t;
                                    int e=q+1;
                                    q++;
                                    for (; e<Line.size(); e++){
                                        if (Line[e]!='"'){
                                            temp+=Line[e];
                                            q++;
                                        }else{
                                            break;
                                        }
                                    }
                                    temp+='"';
                                    q++;
                                    op.push_back(temp);
                                    temp="";
                                }else
                                if (t==' '){
                                    if (temp.size()!=0){
                                        op.push_back(temp);
                                        temp="";
                                    }
                                }else{
                                    temp+=t;
                                }
                            }
                            if (temp.length()!=0){
                                op.push_back(temp);
                                temp="";
                            }
                            int Status=-1;

                            Step1M:{}
                            /*if (MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked() && op.size()>0){
                                MainItem->CodeLine.push_back("cin");
                                for (int ot=0; ot<ots; ot++){
                                    MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                }
                            }*/
                            for (int q=0; q<op.size(); q++){
                                QString Type=TypeVariable(op[q], MainItem->LineVariables);
                                if (Type=="Variable name"){
                                    if (Status<1){
                                        MainItem->EnabledItems[i]->Status=0;
                                        Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                    }
                                }else{
                                    MainItem->EnabledItems[i]->Status=1;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                    std::vector<QString>::iterator itq = op.begin()+q;
                                    op.erase(itq);
                                    MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                                    goto Step1M;
                                }
                                if (Type=="Variable name"){
                                int u=0;
                                        for (; u<MainItem->LineVariables.size(); u++){
                                            if (MassiveRav(op[q], MainItem->LineVariables[u].name)){
                                                break;
                                            }
                                        }
                                        Variable ttt;
                                        if (u==MainItem->LineVariables.size()){

                                            ttt.name=op[q];
                                            QString jl;
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==0){
                                                ttt.type="int";
                                                MainItem->LineVariables.push_back(ttt);
                                                jl=ttt.name+"=0";
                                            }
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==1){
                                                ttt.type="float";
                                                MainItem->LineVariables.push_back(ttt);
                                                jl=ttt.name+"=0.0";
                                            }
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==2){
                                                ttt.type="string";
                                                MainItem->LineVariables.push_back(ttt);
                                                jl=ttt.name+"=\"\"";
                                            }
                                            if (!(std::find((op[q]).begin(), op[q].end(), '[')!=op[q].end())){
                                                MainItem->CodeLine.push_back(jl);
                                                int qws=MainItem->CodeLine.size()-1;
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[qws]="   "+MainItem->CodeLine[qws];
                                                }
                                            }
                                        }else{
                                            ttt.name=op[q];
                                            QString jl;
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==0){
                                                ttt.type="int";
                                                MainItem->LineVariables.push_back(ttt);
                                                jl=ttt.name+"=0";
                                            }
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==1){
                                                ttt.type="float";
                                                MainItem->LineVariables.push_back(ttt);
                                                jl=ttt.name+"=0.0";
                                            }
                                            if (MainItem->EnabledItems[i]->Butt->Frame1[j]->currentIndex()==2){
                                                ttt.type="string";
                                                MainItem->LineVariables.push_back(ttt);
                                                jl=ttt.name+"=\"\"";
                                            }

                                        }
                                        if (MainItem->EnabledItems[i]->Butt->Frame5[j]->isChecked()){
                                            if (std::find((op[q]).begin(), op[q].end(), '[')!=op[q].end() && SGiveIndex(op[q])==SGiveIndex(MainItem->LineVariables[u].name)){
                                                QString ML=MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    MainItem->CodeLine.push_back(SGiveName(op[q])+"=[1]");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    MainItem->CodeLine.push_back("if ("+SGiveIndex(op[q])+">0):");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    ots++;
                                                    MainItem->CodeLine.push_back(SGiveName(op[q])+"[0]=int(input(\"Write "+ttt.type+" variable "+SGiveName(op[q])+"[0] \"))");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    MainItem->CodeLine.push_back("__someVar_=1");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    MainItem->CodeLine.push_back("while (__someVar_<"+SGiveIndex(op[q])+"):");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    ots++;
                                                    MainItem->CodeLine.push_back(SGiveName(op[q])+"+=[int(input(\"Write "+ttt.type+" variable "+SGiveName(op[q])+"[\"+str(__someVar_)+\"] \"))]");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    MainItem->CodeLine.push_back("__someVar_=__someVar_+1");
                                                    for (int ot=0; ot<ots; ot++){
                                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                                    }
                                                    ots--;
                                                    ots--;
                                                    for (int kl=q-1; kl>=0; kl--){
                                                        std::vector<QString>::iterator it=op.begin()+kl;
                                                        op.erase(it);
                                                    }
                                                    if (op.size()>1){
                                                        std::vector<QString>::iterator it=op.begin();
                                                        op.erase(it);
                                                        goto Step1M;
                                                    }
                                            }
                                            else{

                                                MainItem->CodeLine.push_back(ttt.name+"="+ttt.type+"(input(\"Write "+ttt.type+" veriable "+ttt.name+" \"))");
                                                int qws=MainItem->CodeLine.size()-1;
                                                for (int ot=0; ot<ots; ot++){
                                                    MainItem->CodeLine[qws]="   "+MainItem->CodeLine[qws];
                                                }
                                            }
                                        }

                                }
                            }
                            if (op.size()==0){
                                if (Status<1){
                                    MainItem->EnabledItems[i]->Status=0;
                                    Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                                }
                                MainItem->CodeLine.erase(--MainItem->CodeLine.end());
                            }
                        }
                    }

                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 6 || libA[MainItem->EnabledItems[i]->Type]== 7){
                for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                    QString Line=MainItem->EnabledItems[i]->Butt->Frame2[j]->text();
                    //QMessageBox::critical(this, "", Line);
                    std::vector <QString> IfBlocks;
                    QString temp;
                    for (int Varii=0; Varii<Line.length(); Varii++){
                        if (Line[Varii]==' '){

                        }else if (Line[Varii]=='"'){
                            if (temp==""){
                                temp+=Line[Varii];
                                for (; Varii<Line.length(); Varii++){
                                    temp+=Line[Varii];
                                    if (Line[Varii]=='"'){
                                        break;
                                    }
                                }
                                //Varii++;
                                goto FFFFM;
                            }else{
                                MainItem->EnabledItems[i]->Status=1;
                                goto FuckIWantSleepM;
                            }
                        }else if((Line[Varii]=='&' && Varii<Line.length()-1 && Line[Varii+1]=='&') || (Line[Varii]=='|' && Varii<Line.length()-1 && Line[Varii+1]=='|')){
                            //if (temp!=""){
                                IfBlocks.push_back(temp);
                                temp="";
                                QString y;
                                y+=Line[Varii];
                                y+=Line[Varii];
                                IfBlocks.push_back(y);
                            //}
                            Varii++;
                        }else{
                            temp+=Line[Varii];
                        }
FFFFM:{}
                    }
                    if (temp!=""){
                        IfBlocks.push_back(temp);
                        temp="";
                    }
                    //MainItem->EnabledItems[i]->Status=1;
                    //Status=std::max(Status,MainItem->EnabledItems[i]->Status);
                    Line="";
                    if (IfBlocks.size()!=0){
                        for (int Vari=0; Vari<IfBlocks.size(); Vari++){
                            if (IfBlocks[Vari]=="&&" || IfBlocks[Vari]=="||"){
                                Line+=" "+IfBlocks[Vari]+" ";
                            }else{
                                for (int rq=0; rq<IfBlocks[Vari].length(); rq++){
                                    if (IfBlocks[Vari][rq]=='"'){
                                        temp+="\"";
                                        rq++;
                                        for (; rq<Line.length(); rq++){
                                            temp+=IfBlocks[Vari][rq];
                                            if (IfBlocks[Vari][rq]=='"'){
                                                goto PointL2M;
                                            }
                                        }
                                        MainItem->EnabledItems[i]->Status=1;
                                        goto FuckIWantSleepM;
                                    }else if (IfBlocks[Vari][rq]=='>' || IfBlocks[Vari][rq]=='<'){
                                        //IfBlocks[Vari].remove(0, rq);
                                        break;
                                    }else if ((IfBlocks[Vari][rq]=='=' || IfBlocks[Vari][rq]=='!')){
                                        if (IfBlocks[Vari].length()-1>Vari && IfBlocks[Vari][rq+1]=='='){
                                            //IfBlocks[Vari].remove(0, rq+1);
                                            break;
                                        }else{
                                            MainItem->EnabledItems[i]->Status=1;
                                            goto FuckIWantSleepM;
                                        }
                                    }else{
                                        temp+=IfBlocks[Vari][rq];
                                    }
PointL2M:{}
                                }
                                if (temp==Line){
                                    QString Type1=IsArithmeticTrue(&IfBlocks[Vari], MainItem->LineVariables);
                                    if (Type1!="int"){
                                        MainItem->EnabledItems[i]->Status=1;
                                        goto FuckIWantSleepM;
                                    }else{
                                        Line+=IfBlocks[Vari];
                                    }
                                }
                                IfBlocks[Vari].remove(0, temp.length());
                                QString Type1=IsArithmeticTrue(&temp, MainItem->LineVariables);
                                QString T;
                                if (IfBlocks[Vari][0]=='>' || IfBlocks[Vari][0]=='<'){
                                    T=IfBlocks[Vari][0];
                                }else{
                                    T+=IfBlocks[Vari][0];
                                    T+=IfBlocks[Vari][1];
                                }
                                IfBlocks[Vari].remove(0, T.length());
                                QString Type2=IsArithmeticTrue(&IfBlocks[Vari], MainItem->LineVariables);
                                if (Type1==Type2 && Type1!="Trash"){

                                }else{
                                    MainItem->EnabledItems[i]->Status=1;
                                    goto FuckIWantSleepM;
                                }
                                Line+=temp+T+IfBlocks[Vari];
                                //MainItem->EnabledItems[i]->Status=0;
                            }
                            temp="";
                        }
                    }else{
                        MainItem->EnabledItems[i]->Status=1;
                        goto FuckIWantSleepM;
                    }

                    MainItem->EnabledItems[i]->Status=0;
                    if (libA[MainItem->EnabledItems[i]->Type]== 6){
                        MainItem->CodeLine.push_back("if("+Line+"):");
                        for (int ot=0; ot<ots; ot++){
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                        }
                        MainItem->EnabledItems[i]->MyItems[1]->LineVariables=MainItem->LineVariables;
                        MainItem->EnabledItems[i]->MyItems[1]->KolFuckVariable=MainItem->LineVariables.size();
                        std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i]->MyItems[1], ots+1, 0);
                        if (IHateThisProgramm.size()>0){
                            for (int key=0; key<IHateThisProgramm.size(); key++){
                                MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                            }
                            MainItem->CodeLine.push_back("else:");
                            for (int ot=0; ot<ots; ot++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                            }
                        }else{
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="if(!("+Line+")):";
                            for (int ot=0; ot<ots; ot++){
                                MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                            }
                        }
                    }else{
                        MainItem->CodeLine.push_back("while("+Line+"):");
                        for (int ot=0; ot<ots; ot++){
                            MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                        }
                    }
                    MainItem->EnabledItems[i]->MyItems[0]->LineVariables=MainItem->LineVariables;
                    MainItem->EnabledItems[i]->MyItems[0]->KolFuckVariable=MainItem->LineVariables.size();
                    std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i]->MyItems[0], ots+1, 0);
                    if (IHateThisProgramm.size()>0){
                        for (int key=0; key<IHateThisProgramm.size(); key++){
                            MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                        }
                    }else{
                        std::vector <QString>::iterator it=MainItem->CodeLine.begin()+(MainItem->CodeLine.size()-1);
                        MainItem->CodeLine.erase(it);
                    }

                }
FuckIWantSleepM:{}
                }else
                if (MainItem->EnabledItems[i]->Type=="Pattern"){

                    MainItem->EnabledItems[i]->LineVariables=MainItem->LineVariables;
                    MainItem->EnabledItems[i]->KolFuckVariable=MainItem->LineVariables.size();
                    std::vector <QString> IHateThisProgramm = Translate(MainItem->EnabledItems[i], ots, 1);
                    for (int key=0; key<IHateThisProgramm.size(); key++){
                        MainItem->CodeLine.push_back(IHateThisProgramm[key]);
                    }
                    MainItem->LineVariables=MainItem->EnabledItems[i]->LineVariables;
                    //MainItem->KolFuckVariable=MainItem->EnabledItems[i]->KolFuckVariable;
                }
                else
                if (libA[MainItem->EnabledItems[i]->Type]== 2){
                    for (int j=0; j<MainItem->EnabledItems[i]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line=MainItem->EnabledItems[i]->Butt->Frame2[j]->text();
                        QString temp;
                        for (int r=0; r<Line.length(); r++){
                            if (Line[r]=='"'){
                                temp+="\"";
                                r++;
                                for (; r<Line.length(); r++){
                                    temp+=Line[r];
                                    if (Line[r]=='"'){
                                        goto PointLM;
                                    }
                                }
                                MainItem->EnabledItems[i]->Status=1;
                                goto EdThisP;
                            }else if (Line[r]=='='){
                                Line.remove(0, r+1);
                                break;

                            }else{
                                temp+=Line[r];
                            }
                            PointLM:{}
                        }
                        //QMessageBox::critical(this, "("+temp+")", "");
                        if (temp==Line || TypeVariable(temp, MainItem->LineVariables)!="Variable name"){
OhhhhYeeeeeM:{}
                            MainItem->EnabledItems[i]->Status=1;
                            goto EdThisP;
                        }
                        for (int r=0; r<MainItem->LineVariables.size(); r++){
                            if (MassiveRav(MainItem->LineVariables[r].name, temp)){
                                if (((IsArithmeticTrue(&Line, MainItem->LineVariables)=="int" && (MainItem->LineVariables[r].type=="int" || MainItem->LineVariables[r].type=="double")) || (IsArithmeticTrue(&Line, MainItem->LineVariables)=="string" && MainItem->LineVariables[r].type=="string")) && MainItem->EnabledItems[i]->Status<1){
                                    MainItem->EnabledItems[i]->Status=0;
                                    MainItem->CodeLine.push_back(temp+"="+Line);
                                    for (int ot=0; ot<ots; ot++){
                                        MainItem->CodeLine[MainItem->CodeLine.size()-1]="   "+MainItem->CodeLine[MainItem->CodeLine.size()-1];
                                    }
                                    goto EggsM;
                                }else{
                                    //QMessageBox::critical(this, "", IsArithmeticTrue(Line, LineVariables));
                                    MainItem->EnabledItems[i]->Status=1;
                                }
                            }
                        }
                        goto OhhhhYeeeeeM;
EggsM:{}
                    }
EdThisP:{}

                }
        }
        for (int jm=MainItem->CodeLine.size()-1; jm>=0; jm--){
            int kb=0;
            for(; MainItem->CodeLine[kb]==' ' && kb<MainItem->CodeLine.size(); kb++);
            if (kb==MainItem->CodeLine.size()){
                std::vector <QString>::iterator it=MainItem->CodeLine.begin()+jm;
                MainItem->CodeLine.erase(it);
            }
        }
        return MainItem->CodeLine;
    }

}

void MainWindow::PushButton(){
    if (TT==0)
    {
        //SukO=Suk;
        Suk->show();
        //Suk->repaint();
        //Suk->close();
        for (int i=items.size()-1; i>=KolLayout; i--){
            if (items[i]->Butt->IsActivate){
                items[i]->Butt->Activate();
                break;
            }
        }
        Suk->TE->setText("");
        //CodeLineL.clear();
        items[0]->LineVariables.clear();
        items[0]->KolFuckVariable=0;
        std::vector <QString> F=Translate(items[0], 0, 0);

        for (int i=0; i<F.size(); i++){
            //CodeLineL.push_back(new QLabel(this));
            Suk->TE->append(F[i]);
            //CodeLineL[i]->move(800, 150+i*25);
            //CodeLineL[i]->show();
            //TE->resize(300, 17*i+17);
        }
        Suk->repaint();
    }else if (TT==2){
        Suk->show();
        th->hide();
    }
    repaint();
}

void MainWindow::DrawWindow(QPainter *p, int x1, int y1, int x2, int y2, int q){
    p->setPen(Qt::NoPen);
    p->drawEllipse(x1, y1, q, q);
    p->drawEllipse(x2-q, y1, q, q);
    p->drawEllipse(x2-q, y2-q, q, q);
    p->drawEllipse(x1, y2-q, q, q);
    p->drawRect(x1, y1+q/2, x2-x1, y2-q-y1);
    p->drawRect(x1+q/2, y1, x2-x1-q, y2-y1);
    p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    p->drawArc(x1, y1, q, q, 90*16, 90*16);
    p->drawLine(x1+q/2, y1, x2-q/2, y1);
    p->drawArc(x2-q, y1, q, q, 0*16, 90*16);
    p->drawLine(x2, y1+q/2, x2, y2-q/2);
    p->drawArc(x2-q, y2-q, q, q, 270*16, 90*16);
    p->drawLine(x1+q/2, y2, x2-q/2, y2);
    p->drawArc(x1, y2-q, q, q, 180*16, 90*16);
    p->drawLine(x1, y1+q/2, x1, y2-q/2);
}

void MainWindow::DrawBlock(QPainter *p, item *i){
    if (libA[i->GetType()]!=5){
        if (i->GetType()=="Begin" || i->GetType()=="End"){
            DrawWindow(p, i->left,
                       i->top,
                       i->left+i->width,
                       i->top+i->height,
                       i->height);
            goto Op;
        }
        p->setPen(QPen(Qt::black, 1, Qt::SolidLine));


            p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
            if (i->Type=="Arithmetic" || i->Type=="Pattern"){
                if (i->Status==-1)
                    p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
                else if (i->Status==0){
                    p->setPen(QPen(Qt::green, 2, Qt::SolidLine));
                }else{
                    p->setPen(QPen(Qt::red, 2, Qt::SolidLine));
                }
                p->drawRect(i->GetLeftAndTop().first,
                            i->GetLeftAndTop().second,
                            i->width,
                            i->height);
                if (i->Type=="Pattern"){
                    p->drawLine(i->left+5*width()/1050, i->top, i->left+5*width()/1050, i->top+i->height);
                    p->drawLine(i->left+i->width-5*width()/1050, i->top, i->left+i->width-5*width()/1050, i->top+i->height);
                }
            } else if (i->Type=="If" || i->Type=="While"){
                    p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
                    if (i->height!=40*height()/820){//1 3
                        if (i->Type=="If"){
                            QPolygon pol;
                            pol << QPoint(i->HelpLine[1].x1(), i->HelpLine[1].y1())
                                << QPoint(i->HelpLine[1].x1()-2*width()/1050, i->HelpLine[1].y1()-6*height()/820)
                                << QPoint(i->HelpLine[1].x1()+2*width()/1050, i->HelpLine[1].y1()-6*height()/820);
                            p->setBrush(QBrush(Qt::black, Qt::SolidPattern));
                            p->drawPolygon(pol);
                            p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
                            QPolygon pol1;
                            pol1 << QPoint(i->HelpLine[3].x1(), i->HelpLine[3].y1())
                                << QPoint(i->HelpLine[3].x1()-2*width()/1050, i->HelpLine[3].y1()-6*height()/820)
                                << QPoint(i->HelpLine[3].x1()+2*width()/1050, i->HelpLine[3].y1()-6*height()/820);
                            p->setBrush(QBrush(Qt::black, Qt::SolidPattern));
                            p->drawPolygon(pol1);
                            p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
                        }
                    }
                    if (!i->MyItems[0]->Hiden){
                        for (int f=0; f<i->HelpLine.size(); f++){
                            p->drawLine(i->HelpLine[f]);
                        }
                    }
                    if (i->Status==-1)
                        p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
                    else if (i->Status==0){
                        p->setPen(QPen(Qt::green, 2, Qt::SolidLine));
                    }else{
                        p->setPen(QPen(Qt::red, 2, Qt::SolidLine));
                    }

                QPolygon poligon;
                //p->setPen(Qt::NoPen);
                poligon << QPoint(i->left, 40*height()/820/2+i->top) << QPoint(i->width/2+i->left, 40*height()/820+i->top) << QPoint(i->width+i->left, 40*height()/820/2+i->top) << QPoint(i->width/2+i->left, i->top);
                p->drawPolygon(poligon);

            }else if (i->Type=="In" || i->Type=="Out"){
                QPolygon poligon;
                if (i->Status==-1)
                    p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
                else if (i->Status==0){
                    p->setPen(QPen(Qt::green, 2, Qt::SolidLine));
                }else{
                    p->setPen(QPen(Qt::red, 2, Qt::SolidLine));
                }
                //p->setPen(Qt::NoPen);
                poligon << QPoint(i->left+i->width/7.5, i->top) << QPoint(i->left+i->width, i->top) << QPoint(i->left+i->width-i->width/7.5, i->top+i->height) << QPoint(i->left, i->top+i->height);
                p->drawPolygon(poligon);
                //QPolygon poligon1;
                //poligon1 << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first-i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second+i->GetWidthAndHeight().second);
                //p->drawPolygon(poligon1);

            }else{

            }
            /*for (int j=0; j<i->lineInstructions.size(); j++){
            p->drawLine(i->lineInstructions[j].x1+i->GetLeftAndTop().first, i->lineInstructions[j].y1+i->GetLeftAndTop().second,
                            i->lineInstructions[j].x2+i->GetLeftAndTop().first, i->lineInstructions[j].y2+i->GetLeftAndTop().second);
            }*/


        p->setPen(QPen(Qt::black, 1, Qt::SolidLine));        
    }
    else{ //ARRAY_WORK
        p->setPen(QPen(QColor("#800080"), 2, Qt::SolidLine));
        p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
        p->drawRect(i->left,
                    i->top,
                    i->width,
                    i->height);
    }
    Op:{}
}

bool Pause=1;

void MainWindow::paintEvent(QPaintEvent *event){
    if (Pause)
    {
        Pause=0;
        QPainter p(this);
        int _BrushSize = 1;
        p.setPen(QPen(Qt::black, _BrushSize, Qt::SolidLine));
        if (TT==0)
        {
            QPainter p(this);
            int _BrushSize = 1;
            p.setPen(QPen(Qt::black, _BrushSize, Qt::SolidLine));
            //p.setBrush(QBrush(QColor("#303030"), Qt::SolidPattern));
            p.fillRect(0,0, th->width(), th->height(), QBrush(QColor("#666666")));
            p.setBrush(QBrush(QColor("#3b3b3b"), Qt::SolidPattern));
            DrawWindow(&p, -50*width()/1050, 30*height()/820, 90*width()/1050, 630*height()/820, 40*height()/820);
            p.fillRect(3*width()/1050 , 500*height()/820, 85*width()/1050, 90*height()/820, QBrush(QColor("#222222")));
            p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            for (int i=0; i<KolLayout; i++){
                if (!items[i]->Hiden){
                    //QMessageBox::critical(this, "", "");
                    DrawBlock(&(p), (items[i]));
                    for (int j=0; j<items[i]->EnabledItems.size(); j++){
                        if(!items[i]->Scroll || (items[i]->EnabledItems[j]->top>=items[i]->top+15*height()/820 && items[i]->EnabledItems[j]->top+items[i]->EnabledItems[j]->height<=items[i]->top-15*height()/820+items[i]->height)){
                            items[i]->EnabledItems[j]->Hiden=0;
                            items[i]->EnabledItems[j]->Label_Instructions[0]->show();
                            items[i]->EnabledItems[j]->Butt->hide(0);
                            if (items[i]->EnabledItems[j]->Type=="If" || items[i]->EnabledItems[j]->Type=="While"){
                                for (int lar=0; lar<items[i]->EnabledItems[j]->MyItems.size(); lar++)
                                    items[i]->EnabledItems[j]->MyItems[lar]->Hide(items[i]->EnabledItems[j]->hh);
                            }
                            DrawBlock(&(p), (items[i]->EnabledItems[j]));
                            //p.drawLine(0, items[i]->EnabledItems[j]->top+items[i]->EnabledItems[j]->height, 1000, items[i]->EnabledItems[j]->top+items[i]->EnabledItems[j]->height);
                            if (items[i]->EnabledItems[j]->NekstItem!=nullptr){
                                p.drawLine(items[i]->EnabledItems[j]->left+items[i]->EnabledItems[j]->width/2,
                                           items[i]->EnabledItems[j]->top+items[i]->EnabledItems[j]->height,
                                           items[i]->EnabledItems[j]->NekstItem->left+items[i]->EnabledItems[j]->NekstItem->width/2,
                                           items[i]->EnabledItems[j]->NekstItem->top);
                                QPolygon pol;
                                pol << QPoint(items[i]->EnabledItems[j]->NekstItem->left+items[i]->EnabledItems[j]->NekstItem->width/2, items[i]->EnabledItems[j]->NekstItem->top)
                                    << QPoint(items[i]->EnabledItems[j]->NekstItem->left+items[i]->EnabledItems[j]->NekstItem->width/2-2*width()/1050, items[i]->EnabledItems[j]->NekstItem->top-6*height()/820)
                                    << QPoint(items[i]->EnabledItems[j]->NekstItem->left+items[i]->EnabledItems[j]->NekstItem->width/2+2*width()/1050, items[i]->EnabledItems[j]->NekstItem->top-6*height()/820);
                                p.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                                p.drawPolygon(pol);
                                p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                            }
                        }else{
                            //ui->pushButton_2->setText("fuck");
                            items[i]->EnabledItems[j]->Hide(1);
                        }
                    }
                    if (items[i]->Scroll){
                        ui->label->setText(QString::number(items[0]->ScrollHeigth));
                        p.drawRect(items[i]->left+items[i]->width-15*width()/1050, items[i]->top, 15*width()/1050, items[i]->height);
                        p.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
                        p.drawRect(items[i]->left+items[i]->width-15*width()/1050, items[i]->ScrollTop+items[i]->top, 15*width()/1050, items[i]->height*items[i]->height/items[i]->SumHeigth);
                        p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                    }
                }
            }
            /*for (int i=0; i<this->items.size(); i++){

        if (!items[i]->Hiden){
            DrawBlock(&(p), (items[i]));
            if (items[i]->Type=="ArrayWork" && items[i]->Scroll){
                p.drawRect(items[i]->left+items[i]->width-15, items[i]->top, 15, items[i]->height);
                p.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
                p.drawRect(items[i]->left+items[i]->width-15, items[i]->ScrollTop+items[i]->top, 15, items[i]->height*items[i]->height/items[i]->SumHeigth);
                p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            }
            if (items[i]->NekstItem!=nullptr){
                p.drawLine(items[i]->GetLeftAndTop().first+items[i]->GetWidthAndHeight().first/2,
                           items[i]->GetLeftAndTop().second+items[i]->GetWidthAndHeight().second,
                           items[i]->NekstItem->GetLeftAndTop().first+items[i]->NekstItem->GetWidthAndHeight().first/2,
                           items[i]->NekstItem->GetLeftAndTop().second);

            }
        }
    }*/
            for (int i=0; i<7; i++){
                //if (!PatternOfItems[i]->Hiden)
                    DrawBlock(&(p), PatternOfItems[i]);
            }
            for (int i=7; i<PatternOfItems.size(); i++){
                if (i!=7+ui->comboBox_2->currentIndex())
                    PatternOfItems[i]->Hide(1);
            }
            if (ui->comboBox_2->count()>0){
                PatternOfItems[7+ui->comboBox_2->currentIndex()]->Hide(0);
                DrawBlock(&(p), PatternOfItems[7+ui->comboBox_2->currentIndex()]);

            }if (ChoosingItem!=nullptr && !ChoosingItem->Hiden) //ChoosingItem->top>ChoosingItem->Layout->top && ChoosingItem->top+ChoosingItem->height<ChoosingItem->Layout->top+ChoosingItem->Layout->height
                DrawBlock(&(p), ChoosingItem);
            for (int i=KolLayout; i<this->items.size(); i++){
                if (items[i]->Butt->IsActivate){
                    p.setPen(QPen(QColor("#20B2AA"), 3, Qt::SolidLine));

                    p.setPen(QPen(QColor("#20B2AA"), 3, Qt::SolidLine));
                    if (items[i]->Type=="Arithmetic"){
                        p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                        p.drawRect(items[i]->left,
                                   items[i]->top,
                                   items[i]->width,
                                   items[i]->height);
                    }
                    else if (items[i]->Type=="If" || items[i]->Type=="While"){
                        p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
                        if (!items[i]->MyItems[0]->Hiden){
                            for (int f=0; f<items[i]->HelpLine.size(); f++){
                                p.drawLine(items[i]->HelpLine[f]);
                            }
                        }

                        p.setPen(QPen(QColor("#20B2AA"), 3, Qt::SolidLine));
                        QPolygon poligon;

                        poligon << QPoint(items[i]->left, 40*height()/820/2+items[i]->top) << QPoint(items[i]->width/2+items[i]->left, 40*height()/820+items[i]->top) << QPoint(items[i]->width+items[i]->left, 40*height()/820/2+items[i]->top) << QPoint(items[i]->width/2+items[i]->left, items[i]->top);
                        p.drawPolygon(poligon);
                        p.setPen(QPen(QColor("#20B2AA"), 3, Qt::SolidLine));
                    }else if (items[i]->Type=="In" || items[i]->Type=="Out"){
                        QPolygon poligon;
                        p.setPen(QPen(QColor("#20B2AA"), 3, Qt::SolidLine));
                        poligon << QPoint(items[i]->left+items[i]->width/7.5, items[i]->top) << QPoint(items[i]->left+items[i]->width, items[i]->top) << QPoint(items[i]->left+items[i]->width-items[i]->width/7.5, items[i]->top+items[i]->height) << QPoint(items[i]->left, items[i]->top+items[i]->height);
                        p.drawPolygon(poligon);
                    }
                    for (int q=0; q<4; q++){
                        p.drawLine(items[i]->Butt->FrameLineInstructions[q].x1, items[i]->Butt->FrameLineInstructions[q].y1,
                                   items[i]->Butt->FrameLineInstructions[q].x2, items[i]->Butt->FrameLineInstructions[q].y2);
                    }
                    p.fillRect(items[i]->Butt->FrameLineInstructions[0].x1,
                            items[i]->Butt->FrameLineInstructions[0].y1,
                            items[i]->Butt->FrameLineInstructions[0].x2-items[i]->Butt->FrameLineInstructions[0].x1,
                            items[i]->Butt->FrameLineInstructions[3].y2-items[i]->Butt->FrameLineInstructions[0].y1, QBrush(Qt::white, Qt::SolidPattern));
                    p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
                    p.setBrush(QBrush(QColor("#DC143C"), Qt::SolidPattern));
                    for (int Hi=0; Hi<items[i]->Butt->Frame6.size(); Hi++){
                        p.drawRect(items[i]->Butt->Frame6[Hi]->Left, items[i]->Butt->Frame6[Hi]->Top, items[i]->Butt->Frame6[Hi]->Width, items[i]->Butt->Frame6[Hi]->Heigth);
                        p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
                        p.drawLine(items[i]->Butt->Frame6[Hi]->Left+3, items[i]->Butt->Frame6[Hi]->Top+3, items[i]->Butt->Frame6[Hi]->Left+items[i]->Butt->Frame6[Hi]->Width-3, items[i]->Butt->Frame6[Hi]->Top+items[i]->Butt->Frame6[Hi]->Heigth-3);
                        p.drawLine(items[i]->Butt->Frame6[Hi]->Left+items[i]->Butt->Frame6[Hi]->Width-3, items[i]->Butt->Frame6[Hi]->Top+3, items[i]->Butt->Frame6[Hi]->Left+3, items[i]->Butt->Frame6[Hi]->Top+items[i]->Butt->Frame6[Hi]->Heigth-3);
                        p.setPen(QPen(QColor("#20B2AA"), 3, Qt::SolidLine));
                    }
                    p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                    break;

                }
            }
        }else if (TT==1){
            p.fillRect(0,0, th->width(), th->height(), QBrush(QColor("#222222")));
        }else if (TT==2){
            QRectF target(0, 0, width(), height());
            QRectF source(0.0, 0.0, 800, 554);
            QString addresI=QDir::currentPath()+"/resources/hello.png";
            QImage image(addresI);
            p.drawImage(target, image, source);
        }
        else if (TT==3){
                    QRectF target(0, 0, width(), height());
                    QRectF source(0.0, 0.0, 795, 592);
                    QString addresI;
                    if (landg!="Eng")
                        addresI=QDir::currentPath()+"/resources/SPRR.png";
                    else {
                        addresI=QDir::currentPath()+"/resources/SPRE.png";
                    }
                    QImage image(addresI);
                    p.drawImage(target, image, source);
        }else if (TT==4){

        }
        Pause=1;
    }

}

item* yt=nullptr;

void MainWindow::FollowMouse(){
    if (Slott==1){
        this->ChoosingItem->move(DeltaX*(-1), DeltaY*(-1));
        for (int i=0; i<ChoosingItem->EnabledItems.size(); i++){
            ChoosingItem->EnabledItems[i]->move(DeltaX*(-1), DeltaY*(-1));
        }
        DeltaX=(QCursor::pos().x()-this->FirstMousePositions.x());
        DeltaY=QCursor::pos().y()-this->FirstMousePositions.y();
        this->ChoosingItem->move(DeltaX, DeltaY);
        for (int i=0; i<ChoosingItem->EnabledItems.size(); i++){
            ChoosingItem->EnabledItems[i]->move(DeltaX, DeltaY);
        }
    }else if(Slott==2){
        //yt->move(0, DeltaY*(-1));
        DeltaX=(QCursor::pos().x()-this->FirstMousePositions.x());
        DeltaY=QCursor::pos().y()-this->FirstMousePositions.y();
        int del;
        del=DeltaY*yt->height/yt->ScrollHeigth;
        yt->ScrollTop+=DeltaY;
        if (yt->ScrollTop<0){
            yt->ScrollTop=0;
            if (yt->EnabledItems.size()>0){
                del=yt->top-yt->EnabledItems[0]->top+15*height()/820;
                for (int j=0; j<yt->EnabledItems.size(); j++){
                    //int del=items[i]->top+15-items[i]->EnabledItems[0]->top;
                    yt->EnabledItems[j]->move(0, del);


                }
            }
        }else if(yt->ScrollTop+yt->height*yt->height/yt->SumHeigth > yt->height){
            yt->ScrollTop=yt->height-yt->height*yt->height/yt->SumHeigth;
            if (yt->EnabledItems.size()>0){
                del=yt->top+yt->height-yt->EnabledItems[yt->EnabledItems.size()-1]->top-yt->EnabledItems[yt->EnabledItems.size()-1]->height-15*height()/820;
                for (int j=0; j<yt->EnabledItems.size(); j++){
                    //int del=items[i]->top+15-items[i]->EnabledItems[0]->top;
                    yt->EnabledItems[j]->move(0, del);
               }
            }

        }else{
            for (int j=0; j<yt->EnabledItems.size(); j++){
                yt->EnabledItems[j]->move(0, del*(-1));
            }
        }
        FirstMousePositions.setY(FirstMousePositions.y()+DeltaY);
    }
    this->repaint();
}

void MainWindow::TimerEvent(){
    this->Timer1->start(10);
}

bool SuperBool=0;

void MainWindow::mouseReleaseEvent( QMouseEvent * event ){
    if (TT==0 && SuperBool)
    {
        this->ui->label->setText("Release");
        //std::sleep(5000);
        if (Slott==1)
            StopMove();
        DeltaX=0; DeltaY=0;
        this->Timer1->stop();
        ChoosingItem=nullptr;
        SuperBool=0;
    }
    Slott=0;
}

void MainWindow::StopMove(){
    if (ChoosingItem!=nullptr){
            if (libA[ChoosingItem->Type]!=5){
                int qq=this->KolLayout-1;

                for (qq; qq>=0; qq--){
                        if (QCursor::pos().x()-this->geometry().left() > items[qq]->GetLeftAndTop().first &&
                            QCursor::pos().x()-this->geometry().left() < items[qq]->GetLeftAndTop().first + items[qq]->GetWidthAndHeight().first &&
                            QCursor::pos().y()-this->geometry().top() > items[qq]->GetLeftAndTop().second &&
                            QCursor::pos().y()-this->geometry().top() < items[qq]->GetLeftAndTop().second + items[qq]->GetWidthAndHeight().second && !items[qq]->Hiden)
                        {
                            bool e=1;
                            for (int opw=0; opw<ChoosingItem->MyItems.size(); opw++){
                                if (items[qq]==ChoosingItem->MyItems[opw]){
                                    e=0;
                                }
                            }
                            if (e)
                                break;
                        }

                    } 
                if (qq!=-1)
                {
                    if (ChoosingItem->Layout==nullptr){
                        NewBlock(ChoosingItem->Type2, 0);
                        for (int kl=0; kl<PatternOfItems.size(); kl++){
                            if (PatternOfItems[kl]==ChoosingItem){
                                PatternOfItems[kl]=items[items.size()-1];
                                break;
                            }
                        }
                    }
                    if (ChoosingItem->Type=="If"){
                        if (ChoosingItem->hh==0){
                            ChoosingItem->height=ChoosingItem->ShowHeigth;
                        }
                        //ChoosingItem->Hide(0);
                        ChoosingItem->MyItems[0]->MaxHeigth=items[qq]->MaxHeigth*3/5;
                        ChoosingItem->MyItems[1]->MaxHeigth=ChoosingItem->MyItems[0]->MaxHeigth;
                        ChoosingItem->MyItems[0]->n=items[qq]->n+1;
                        ChoosingItem->MyItems[1]->n=items[qq]->n+1;
                        ChoosingItem->MyItems[0]->setGeometry((items[qq]->width-50*width()/1050)/2, ChoosingItem->ShowHeigth-70*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/2, ChoosingItem->top+55*height()/820);
                        ChoosingItem->MyItems[1]->setGeometry((items[qq]->width-50*width()/1050)/2, ChoosingItem->ShowHeigth-70*height()/820, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050, ChoosingItem->top+55*height()/820);
                    }
                    if (ChoosingItem->Type=="While"){
                        if (ChoosingItem->hh==0){
                            ChoosingItem->height=ChoosingItem->ShowHeigth;
                        }
                        //ChoosingItem->Hide(0);
                        ChoosingItem->MyItems[0]->n=items[qq]->n+1;
                        ChoosingItem->MyItems[0]->MaxHeigth=items[qq]->MaxHeigth*3/5;
                        ChoosingItem->MyItems[0]->setGeometry((items[qq]->width-50*width()/1050)/2, ChoosingItem->ShowHeigth-85*height()/820, ChoosingItem->left+ChoosingItem->width/2-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+55*height()/820);
                        //ChoosingItem->MyItems[1]->setGeometry((items[qq]->width-50)/2, items[qq]->height/3, ChoosingItem->left+ChoosingItem->width/2+5, ChoosingItem->top+ChoosingItem->height+15);
                    }
                    ChoosingItem->Layout=items[qq];
                    std::vector <item *>::iterator it=GetPos(ChoosingItem, items[qq]);
                    items[qq]->EnabledItems.insert(it, ChoosingItem);
                    if (items[qq]->EnabledItems[0]==ChoosingItem){
                        item* ok=items[qq]->EnabledItems[0];
                        ok->setGeometry(ok->width, ok->height, items[qq]->left+(items[qq]->width-ok->width)/2, items[qq]->top+15*height()/820);
                        for (int jor=1; jor<items[qq]->EnabledItems.size(); jor++){
                            items[qq]->EnabledItems[jor]->move(0, ok->height+15*height()/820);
                        }
                    }else{
                        int hh=0;
                        for (; hh<items[qq]->EnabledItems.size(); hh++){
                            if (items[qq]->EnabledItems[hh]==ChoosingItem){
                                break;
                            }
                        }
                        //if (hh==items[qq]->EnabledItems.size()-1){
                            ChoosingItem->setGeometry(ChoosingItem->width, ChoosingItem->height, items[qq]->EnabledItems[hh-1]->left, items[qq]->EnabledItems[hh-1]->top+15*height()/820+items[qq]->EnabledItems[hh-1]->height);

                        hh++;
                        for (;  hh<items[qq]->EnabledItems.size(); hh++){
                            items[qq]->EnabledItems[hh]->move(0, 15*height()/820+ChoosingItem->height);
                        }

                    }
                }else{
                    if (ChoosingItem->Layout==nullptr){
                        NewBlock(ChoosingItem->Type2, 0);
                        for (int kl=0; kl<PatternOfItems.size(); kl++){
                            if (PatternOfItems[kl]==ChoosingItem){
                                PatternOfItems[kl]=items[items.size()-1];
                                break;
                            }
                        }
                    }
                    DeleteBlock(ChoosingItem);
                    ChoosingItem=nullptr;
                }
                if (qq!=-1){
                    //QMessageBox::critical(this, "", ChoosingItem->Type);
                    if (ChoosingItem->Type=="If"){
                        //ChoosingItem->MyItems[0]->ScrollTop=0;
                        ChoosingItem->HelpLine.clear();
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left, ChoosingItem->top+20*height()/820, ChoosingItem->left+ChoosingItem->width/2-5-(items[qq]->width-50)/4, ChoosingItem->top+20*height()/820));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+20*height()/820));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width, ChoosingItem->top+20*height()/820, ChoosingItem->left+ChoosingItem->width/2+5+(items[qq]->width-50)/4, ChoosingItem->top+20*height()/820));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+20*height()/820));

                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+30*height()/820+ChoosingItem->MyItems[0]->height));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+30*height()/820+ChoosingItem->MyItems[0]->height));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height,  ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+30*height()/820+ChoosingItem->MyItems[0]->height));
                    }else if (ChoosingItem->Type=="While"){
                        ChoosingItem->HelpLine.clear();
                        //ChoosingItem->MyItems[1]->ScrollTop=0;
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top-5*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top-5*height()/820));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820, ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+30*height()/820+ChoosingItem->MyItems[0]->height));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820, ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top-5*height()/820, ChoosingItem->left+ChoosingItem->width/2-5*width()/1050-(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+15*height()/820));

                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width, ChoosingItem->top+20*height()/820, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+20*height()/820));
                         ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+45*height()/820+ChoosingItem->MyItems[0]->height, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+20*height()/820));
                        ChoosingItem->HelpLine.push_back(QLine(ChoosingItem->left+38*width()/1050, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+30*height()/820, ChoosingItem->left+ChoosingItem->width/2+5*width()/1050+(items[qq]->width-50*width()/1050)/4, ChoosingItem->top+40*height()/820+15*height()/820+ChoosingItem->MyItems[0]->height+30*height()/820));

                    }
                }
                //repaint();
            }
        //}

   }
    Slott=0;
    ReconstructItem0();
    Suk->repaint();
    this->repaint();
}

void MainWindow::DeleteBlock(item *it){
    if (it->Type=="If"){
        DeleteBlock(it->MyItems[1]);
    }
    if (it->Type=="If" || it->Type=="While"){
        DeleteBlock(it->MyItems[0]);
    }
    if (it->Type=="ArrayWork"){
        int i=0;
        if (it->Pa!=nullptr){
            for (; it!=it->Pa->MyItems[i]; i++);
            std::vector<item*>::iterator ite=it->Pa->MyItems.begin()+i;
            it->Pa->MyItems.erase(ite);
        }
        for (i=it->EnabledItems.size()-1; i>=0; i--){
            DeleteBlock(it->EnabledItems[i]);
        }
        KolLayout--;
    }
    int i=0;
    for (; items[i]!=it; i++);
    std::vector<item*>::iterator ite=items.begin()+i;
    items.erase(ite);
    it->~item();
}

void MainWindow::wheelEvent(QWheelEvent *event){
    for (int i=KolLayout; i>=0; i--){
        if (!items[i]->Hiden &&
            items[i]->GetLeftAndTop().first                                              <   QCursor::pos().x()-this->geometry().left() &&
            items[i]->GetLeftAndTop().first+this->items[i]->GetWidthAndHeight().first     >   QCursor::pos().x()-this->geometry().left() &&
            items[i]->GetLeftAndTop().second                                             <   QCursor::pos().y()-this->geometry().top() &&
            items[i]->GetLeftAndTop().second+this->items[i]->GetWidthAndHeight().second   >   QCursor::pos().y()-this->geometry().top())
        {
            if (items[i]->Scroll){
                items[i]->ScrollTop+=-1*event->delta()*height()/820/3*(double)(items[i]->height/items[i]->SumHeigth);
                if (items[i]->ScrollTop-15*height()/820*items[i]->height/items[i]->SumHeigth<0){
                    items[i]->ScrollTop=0;
                    if (items[i]->EnabledItems.size()>0){
                        int del=items[i]->top-items[i]->EnabledItems[0]->top+15*height()/820;
                        for (int j=0; j<items[i]->EnabledItems.size(); j++){
                               //int del=items[i]->top+15-items[i]->EnabledItems[0]->top;
                            items[i]->EnabledItems[j]->move(0, del);


                        }
                        repaint();
                    }
                }else if(items[i]->ScrollTop+items[i]->height*items[i]->height/items[i]->SumHeigth > items[i]->height){
                    items[i]->ScrollTop=items[i]->height-items[i]->height*items[i]->height/items[i]->SumHeigth;
                    if (items[i]->EnabledItems.size()>0){
                        int del=items[i]->top+items[i]->height-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->height-15*height()/820;
                        for (int j=0; j<items[i]->EnabledItems.size(); j++){
                               //int del=items[i]->top+15-items[i]->EnabledItems[0]->top;
                            items[i]->EnabledItems[j]->move(0, del);
                            repaint();
                       }
                    }

                }else{
                    for (int j=0; j<items[i]->EnabledItems.size(); j++){
                        items[i]->EnabledItems[j]->move(0, event->delta()*height()/820/3);
                        repaint();
                    }
                }
            }
            break;
        }
    }
    repaint();
}

void MainWindow::HideBlocks(item * i, bool u){
    i->Hide(u);
}

void MainWindow::mousePressEvent( QMouseEvent * event ){
    if (TT==0)
    {
        this->ui->label->setText("Press");
        bool o=1;
        for (int i=KolLayout-1; i>=0; i--){
            for (int j=0; j<items[i]->EnabledItems.size(); j++){
                if (items[i]->EnabledItems[j]->Butt->IsActivate){
                    if ((items[i]->EnabledItems[j]->Butt->GLeft()                              < QCursor::pos().x()-this->geometry().left()) &&
                            (items[i]->EnabledItems[j]->Butt->GLeft()+items[i]->EnabledItems[j]->Butt->GWidth() > QCursor::pos().x()-this->geometry().left()) &&
                            (items[i]->EnabledItems[j]->Butt->GTop()                               < QCursor::pos().y()-this->geometry().top()) &&
                            (items[i]->EnabledItems[j]->Butt->GTop()+items[i]->EnabledItems[j]->Butt->GHeigth() > QCursor::pos().y()-this->geometry().top()))
                    {
                        items[i]->EnabledItems[j]->Butt->Activate();
                        ChoosingItem=nullptr;
                        o=0;
                        break;

                    }else if (!((items[i]->EnabledItems[j]->Butt->LeftFrame                                                             <   QCursor::pos().x()-this->geometry().left()) &&
                          (items[i]->EnabledItems[j]->Butt->LeftFrame +items[i]->EnabledItems[j]->Butt->WidthFrame                  >   QCursor::pos().x()-this->geometry().left()) &&
                          (items[i]->EnabledItems[j]->Butt->TopFrame                                                                <   QCursor::pos().y()-this->geometry().top()) &&
                          (items[i]->EnabledItems[j]->Butt->TopFrame+items[i]->EnabledItems[j]->Butt->HeigthFrame                   >   QCursor::pos().y()-this->geometry().top()))){
                        items[i]->EnabledItems[j]->Butt->Activate();
                        ChoosingItem=nullptr;
                        break;

                    }else{
                        for (int wal=0; wal<items[i]->EnabledItems[j]->Butt->Frame6.size(); wal++){
                            if ((items[i]->EnabledItems[j]->Butt->Frame6[wal]->Left                                                      <   QCursor::pos().x()-this->geometry().left()) &&
                                    (items[i]->EnabledItems[j]->Butt->Frame6[wal]->Left+items[i]->EnabledItems[j]->Butt->Frame6[wal]->Width  >   QCursor::pos().x()-this->geometry().left()) &&
                                    (items[i]->EnabledItems[j]->Butt->Frame6[wal]->Top                                                       <   QCursor::pos().y()-this->geometry().top()) &&
                                    (items[i]->EnabledItems[j]->Butt->Frame6[wal]->Top+items[i]->EnabledItems[j]->Butt->Frame6[wal]->Heigth  >   QCursor::pos().y()-this->geometry().top())){
                                for (int tp=wal+1; tp<items[i]->EnabledItems[j]->Butt->Frame6.size(); tp++){
                                    items[i]->EnabledItems[j]->Butt->Frame6[tp]->Top-=35*height()/820;
                                }
                                for (int tp=wal+1; tp<items[i]->EnabledItems[j]->Butt->Frame5.size(); tp++){
                                    items[i]->EnabledItems[j]->Butt->Frame5[tp]->move(items[i]->EnabledItems[j]->Butt->Frame5[tp]->geometry().left(), items[i]->EnabledItems[j]->Butt->Frame5[tp]->geometry().top()-35*height()/820);
                                }
                                for (int tp=wal+1; tp<items[i]->EnabledItems[j]->Butt->Frame3.size(); tp++){
                                    items[i]->EnabledItems[j]->Butt->Frame3[tp]->move(items[i]->EnabledItems[j]->Butt->Frame3[tp]->geometry().left(), items[i]->EnabledItems[j]->Butt->Frame3[tp]->geometry().top()-35*height()/820);
                                }
                                for (int tp=wal+1; tp<items[i]->EnabledItems[j]->Butt->Frame2.size(); tp++){
                                    items[i]->EnabledItems[j]->Butt->Frame2[tp]->move(items[i]->EnabledItems[j]->Butt->Frame2[tp]->geometry().left(), items[i]->EnabledItems[j]->Butt->Frame2[tp]->geometry().top()-35*height()/820);
                                }
                                for (int tp=wal+1; tp<items[i]->EnabledItems[j]->Butt->Frame1.size(); tp++){
                                    items[i]->EnabledItems[j]->Butt->Frame1[tp]->move(items[i]->EnabledItems[j]->Butt->Frame1[tp]->geometry().left(), items[i]->EnabledItems[j]->Butt->Frame1[tp]->geometry().top()-35*height()/820);
                                }
                                if (items[i]->EnabledItems[j]->Butt->Frame5.size()>wal){
                                    std::vector <QCheckBox *>::iterator it5=items[i]->EnabledItems[j]->Butt->Frame5.begin()+wal;
                                    items[i]->EnabledItems[j]->Butt->Frame5[wal]->hide();
                                    items[i]->EnabledItems[j]->Butt->Frame5.erase(it5);
                                }
                                if (items[i]->EnabledItems[j]->Butt->Frame6.size()>wal){
                                    std::vector <ButtonClose *>::iterator it6=items[i]->EnabledItems[j]->Butt->Frame6.begin()+wal;
                                    items[i]->EnabledItems[j]->Butt->Frame6.erase(it6);
                                }
                                if (items[i]->EnabledItems[j]->Butt->Frame3.size()>wal){
                                    std::vector <QLabel *>::iterator it3=items[i]->EnabledItems[j]->Butt->Frame3.begin()+wal;
                                    items[i]->EnabledItems[j]->Butt->Frame3[wal]->hide();
                                    items[i]->EnabledItems[j]->Butt->Frame3.erase(it3);
                                }
                                if (items[i]->EnabledItems[j]->Butt->Frame2.size()>wal){
                                    std::vector <QLineEdit *>::iterator it2=items[i]->EnabledItems[j]->Butt->Frame2.begin()+wal;
                                    items[i]->EnabledItems[j]->Butt->Frame2[wal]->hide();
                                    items[i]->EnabledItems[j]->Butt->Frame2.erase(it2);
                                }if (items[i]->EnabledItems[j]->Butt->Frame1.size()>wal){
                                    std::vector <QComboBox *>::iterator it1=items[i]->EnabledItems[j]->Butt->Frame1.begin()+wal;
                                    items[i]->EnabledItems[j]->Butt->Frame1[wal]->hide();
                                    items[i]->EnabledItems[j]->Butt->Frame1.erase(it1);
                                }
                                if (items[i]->EnabledItems[j]->Type=="If"){
                                    if (landg=="Eng"){
                                        items[i]->EnabledItems[j]->Butt->Frame4[0]->setText("+Add");
                                    }else{
                                        items[i]->EnabledItems[j]->Butt->Frame4[0]->setText("+Добавить");
                                    }
                                    items[i]->EnabledItems[j]->height=40*height()/820;
                                    items[i]->EnabledItems[j]->MyItems[0]->Hide(1);
                                    items[i]->EnabledItems[j]->MyItems[1]->Hide(1);
                                }else if (items[i]->EnabledItems[j]->Type=="While"){
                                    if (landg=="Eng"){
                                        items[i]->EnabledItems[j]->Butt->Frame4[0]->setText("+Add");
                                    }else{
                                        items[i]->EnabledItems[j]->Butt->Frame4[0]->setText("+Добавить");
                                    }
                                    items[i]->EnabledItems[j]->height=40*height()/820;
                                    items[i]->EnabledItems[j]->MyItems[0]->Hide(1);
                                    //items[i]->EnabledItems[j]->MyItems[1]->Hide(1);
                                }

                                items[i]->EnabledItems[j]->Butt->HeigthFrame-=35*height()/820;
                                items[i]->EnabledItems[j]->Butt->FrameCorrect();
                                items[i]->EnabledItems[j]->Butt->Frame4[0]->move(items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left(), items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()-35*height()/820);
                                repaint();
                                break;
                            }
                        }
                        o=0;
                        ChoosingItem=nullptr;
                        break;
                    }
                }

            }
        }
        for (int i=0; i<PatternOfItems.size(); i++){
            if (PatternOfItems[i]->Butt->IsActivate){
                    if ((PatternOfItems[i]->Butt->GLeft()                              < QCursor::pos().x()-this->geometry().left()) &&
                            (PatternOfItems[i]->Butt->GLeft()+PatternOfItems[i]->Butt->GWidth() > QCursor::pos().x()-this->geometry().left()) &&
                            (PatternOfItems[i]->Butt->GTop()                               < QCursor::pos().y()-this->geometry().top()) &&
                            (PatternOfItems[i]->Butt->GTop()+PatternOfItems[i]->Butt->GHeigth() > QCursor::pos().y()-this->geometry().top()))
                    {
                        PatternOfItems[i]->Butt->Activate();
                        ChoosingItem=nullptr;
                        o=0;
                        break;

                    }else if (!((PatternOfItems[i]->Butt->LeftFrame                                                             <   QCursor::pos().x()-this->geometry().left()) &&
                      (PatternOfItems[i]->Butt->LeftFrame +PatternOfItems[i]->Butt->WidthFrame                  >   QCursor::pos().x()-this->geometry().left()) &&
                      (PatternOfItems[i]->Butt->TopFrame                                                                <   QCursor::pos().y()-this->geometry().top()) &&
                      (PatternOfItems[i]->Butt->TopFrame+PatternOfItems[i]->Butt->HeigthFrame                   >   QCursor::pos().y()-this->geometry().top()))){
                    PatternOfItems[i]->Butt->Activate();
                    ChoosingItem=nullptr;
                    break;

                }else{
                    for (int wal=0; wal<PatternOfItems[i]->Butt->Frame6.size(); wal++){
                        if ((PatternOfItems[i]->Butt->Frame6[wal]->Left                                                      <   QCursor::pos().x()-this->geometry().left()) &&
                                (PatternOfItems[i]->Butt->Frame6[wal]->Left+PatternOfItems[i]->Butt->Frame6[wal]->Width  >   QCursor::pos().x()-this->geometry().left()) &&
                                (PatternOfItems[i]->Butt->Frame6[wal]->Top                                                       <   QCursor::pos().y()-this->geometry().top()) &&
                                (PatternOfItems[i]->Butt->Frame6[wal]->Top+PatternOfItems[i]->Butt->Frame6[wal]->Heigth  >   QCursor::pos().y()-this->geometry().top())){
                            for (int tp=wal+1; tp<PatternOfItems[i]->Butt->Frame6.size(); tp++){
                                PatternOfItems[i]->Butt->Frame6[tp]->Top-=35;
                            }
                            for (int tp=wal+1; tp<PatternOfItems[i]->Butt->Frame5.size(); tp++){
                                PatternOfItems[i]->Butt->Frame5[tp]->move(PatternOfItems[i]->Butt->Frame5[tp]->geometry().left(), PatternOfItems[i]->Butt->Frame5[tp]->geometry().top()-35);
                            }
                            for (int tp=wal+1; tp<PatternOfItems[i]->Butt->Frame3.size(); tp++){
                                PatternOfItems[i]->Butt->Frame3[tp]->move(PatternOfItems[i]->Butt->Frame3[tp]->geometry().left(), PatternOfItems[i]->Butt->Frame3[tp]->geometry().top()-35);
                            }
                            for (int tp=wal+1; tp<PatternOfItems[i]->Butt->Frame2.size(); tp++){
                                PatternOfItems[i]->Butt->Frame2[tp]->move(PatternOfItems[i]->Butt->Frame2[tp]->geometry().left(), PatternOfItems[i]->Butt->Frame2[tp]->geometry().top()-35);
                            }
                            for (int tp=wal+1; tp<PatternOfItems[i]->Butt->Frame1.size(); tp++){
                                PatternOfItems[i]->Butt->Frame1[tp]->move(PatternOfItems[i]->Butt->Frame1[tp]->geometry().left(), PatternOfItems[i]->Butt->Frame1[tp]->geometry().top()-35);
                            }
                            if (PatternOfItems[i]->Butt->Frame5.size()>wal){
                                std::vector <QCheckBox *>::iterator it5=PatternOfItems[i]->Butt->Frame5.begin()+wal;
                                PatternOfItems[i]->Butt->Frame5[wal]->hide();
                                PatternOfItems[i]->Butt->Frame5.erase(it5);
                            }
                            if (PatternOfItems[i]->Butt->Frame6.size()>wal){
                                std::vector <ButtonClose *>::iterator it6=PatternOfItems[i]->Butt->Frame6.begin()+wal;
                                PatternOfItems[i]->Butt->Frame6.erase(it6);
                            }
                            if (PatternOfItems[i]->Butt->Frame3.size()>wal){
                                std::vector <QLabel *>::iterator it3=PatternOfItems[i]->Butt->Frame3.begin()+wal;
                                PatternOfItems[i]->Butt->Frame3[wal]->hide();
                                PatternOfItems[i]->Butt->Frame3.erase(it3);
                            }
                            if (PatternOfItems[i]->Butt->Frame2.size()>wal){
                                std::vector <QLineEdit *>::iterator it2=PatternOfItems[i]->Butt->Frame2.begin()+wal;
                                PatternOfItems[i]->Butt->Frame2[wal]->hide();
                                PatternOfItems[i]->Butt->Frame2.erase(it2);
                            }if (PatternOfItems[i]->Butt->Frame1.size()>wal){
                                std::vector <QComboBox *>::iterator it1=PatternOfItems[i]->Butt->Frame1.begin()+wal;
                                PatternOfItems[i]->Butt->Frame1[wal]->hide();
                                PatternOfItems[i]->Butt->Frame1.erase(it1);
                            }
                            if (PatternOfItems[i]->Type=="If"){
                                if (landg=="Eng"){
                                    PatternOfItems[i]->Butt->Frame4[0]->setText("+Add");
                                }else{
                                    PatternOfItems[i]->Butt->Frame4[0]->setText("+Добавить");
                                }
                                PatternOfItems[i]->height=40*height()/820;
                                PatternOfItems[i]->MyItems[0]->Hide(1);
                                PatternOfItems[i]->MyItems[1]->Hide(1);
                            }else if (items[i]->Type=="While"){
                                if (landg=="Eng"){
                                    PatternOfItems[i]->Butt->Frame4[0]->setText("+Add");
                                }else{
                                    PatternOfItems[i]->Butt->Frame4[0]->setText("+Добавить");
                                }
                                PatternOfItems[i]->height=40;
                                PatternOfItems[i]->MyItems[0]->Hide(1);
                                //items[i]->EnabledItems[j]->MyItems[1]->Hide(1);
                            }

                            PatternOfItems[i]->Butt->HeigthFrame-=35;
                            PatternOfItems[i]->Butt->FrameCorrect();
                            PatternOfItems[i]->Butt->Frame4[0]->move(PatternOfItems[i]->Butt->Frame4[0]->geometry().left(), PatternOfItems[i]->Butt->Frame4[0]->geometry().top()-35);
                            repaint();
                            break;
                        }
                    }
                    o=0;
                    ChoosingItem=nullptr;
                    break;
                }
            }
        }
        if (o){
            int i=KolLayout-1;
            for (; i>=0; i--){
                if (
                        items[i]->left                                              <   QCursor::pos().x()-this->geometry().left() &&
                        items[i]->left+this->items[i]->width                        >   QCursor::pos().x()-this->geometry().left() &&
                        items[i]->top                                               <   QCursor::pos().y()-this->geometry().top() &&
                        items[i]->top+this->items[i]->height                        >   QCursor::pos().y()-this->geometry().top() && !items[i]->Hiden)
                {
                    if (items[i]->Scroll &&
                        items[i]->top+items[i]->ScrollTop <= QCursor::pos().y()-this->geometry().top() &&
                        items[i]->top+items[i]->ScrollTop+items[i]->ScrollHeigth >= QCursor::pos().y()-this->geometry().top() &&
                        items[i]->left+items[i]->width-15*width()/1050 <= QCursor::pos().x()-this->geometry().left() &&
                        items[i]->left+items[i]->width >= QCursor::pos().x()-this->geometry().left()){
                        yt=items[i];
                        this->FirstMousePositions.setX(QCursor::pos().x());
                        this->FirstMousePositions.setY(QCursor::pos().y());
                        Slott=2;
                        this->TimerEvent();

                        goto YbrbnfLjbr;
                    }else{
                        for (int j=0; j<items[i]->EnabledItems.size(); j++){
                            if (
                                    items[i]->EnabledItems[j]->left                                              <   QCursor::pos().x()-this->geometry().left() &&
                                    items[i]->EnabledItems[j]->left+this->items[i]->EnabledItems[j]->width                        >   QCursor::pos().x()-this->geometry().left() &&
                                    items[i]->EnabledItems[j]->top                                               <   QCursor::pos().y()-this->geometry().top() &&
                                    items[i]->EnabledItems[j]->top+this->items[i]->EnabledItems[j]->height                        >   QCursor::pos().y()-this->geometry().top())
                            {
                                SuperBool=1;
                                ChoosingItem=items[i]->EnabledItems[j];
                                //ChoosingItem->hh=0;
                                if ((ChoosingItem->Butt->GLeft()                              < QCursor::pos().x()-this->geometry().left()) &&
                                        (ChoosingItem->Butt->GLeft()+ChoosingItem->Butt->GWidth() > QCursor::pos().x()-this->geometry().left()) &&
                                        (ChoosingItem->Butt->GTop()                               < QCursor::pos().y()-this->geometry().top()) &&
                                        (ChoosingItem->Butt->GTop()+ChoosingItem->Butt->GHeigth() > QCursor::pos().y()-this->geometry().top()))
                                {
                                    ChoosingItem->Butt->Activate();
                                    ChoosingItem=nullptr;
                                    repaint();
                                }else{
                                    if (ChoosingItem->Layout!=nullptr){
                                        int q=0;
                                        while (ChoosingItem!=ChoosingItem->Layout->EnabledItems[q]){
                                            q++;
                                        }
                                        //ChoosingItem->height=40*height()/820;
                                        std::vector <item *> ::iterator it = ChoosingItem->Layout->EnabledItems.begin()+q;
                                        q++;
                                        for (; q<ChoosingItem->Layout->EnabledItems.size(); q++){
                                            item * ok=ChoosingItem->Layout->EnabledItems[q];
                                            ok->move(0, -1*ChoosingItem->height-15*height()/820);
                                        }
                                        ChoosingItem->NekstItem=nullptr;
                                        ChoosingItem->Layout->EnabledItems.erase(it);
                                        ReconstructItem0();
                                    }
                                    if (ChoosingItem->Type=="If"){
                                        ChoosingItem->height=40*height()/820;
                                        ChoosingItem->MyItems[0]->Hide(1);
                                        ChoosingItem->MyItems[1]->Hide(1);
                                        if (items[i]->EnabledItems.size()>0){
                                            if(!items[i]->Scroll){
                                                items[i]->ScrollTop=0;
                                                /*int del=items[i]->top-items[i]->EnabledItems[0]->top+15*height()/820;
                                                for (int q=0; q<items[i]->EnabledItems.size(); q++){
                                                    items[i]->EnabledItems[q]->move(0, del);
                                                }*/
                                            }else{
                                                if (items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top<=items[i]->top+items[i]->height-15*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->height){
                                                    items[i]->ScrollTop=items[i]->height-items[i]->height*items[i]->height/items[i]->SumHeigth;
                                                    /*int del=items[i]->top+items[i]->height-15*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top;
                                                    for (int q=0; q<items[i]->EnabledItems.size(); q++){
                                                        items[i]->EnabledItems[q]->move(0, del);
                                                    }*/
                                                }
                                            }

                                        }
                                    }else if (ChoosingItem->Type=="While"){
                                        ChoosingItem->height=40*height()/820;
                                        ChoosingItem->MyItems[0]->Hide(1);
                                        if (items[i]->EnabledItems.size()>0){
                                            if(!items[i]->Scroll){
                                                items[i]->ScrollTop=0;
                                                                            int del=items[i]->top-items[i]->EnabledItems[0]->top+15*height()/820;
                                                                            for (int q=0; q<items[i]->EnabledItems.size(); q++){
                                                                                items[i]->EnabledItems[q]->move(0, del);
                                                                            }
                                            }else{
                                                if (items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top<items[i]->top+items[i]->height-15*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->height){
                                                    items[i]->ScrollTop=items[i]->height-items[i]->height*items[i]->height/items[i]->SumHeigth;
                                                                            int del=items[i]->top+items[i]->height-15*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top;
                                                                            for (int q=0; q<items[i]->EnabledItems.size(); q++){
                                                                                items[i]->EnabledItems[q]->move(0, del);
                                                                            }
                                                }
                                            }

                                        }
                                    }
                                    //ReconstructItem0();
                                    this->FirstMousePositions.setX(QCursor::pos().x());
                                    this->FirstMousePositions.setY(QCursor::pos().y());
                                    Slott=1;
                                    this->TimerEvent();
                                    this->moveEvent=true;
                                }
                                break;
                            }

                        }
                    }
                    break;
                }
            }
            //QMessageBox::critical(this, "", QString::number(i));
            if (i==-1){
                for (int q=0; q<PatternOfItems.size(); q++){
                    if (
                            PatternOfItems[q]->left                                              <   QCursor::pos().x()-this->geometry().left() &&
                            PatternOfItems[q]->left+this->PatternOfItems[q]->width               >   QCursor::pos().x()-this->geometry().left() &&
                            PatternOfItems[q]->top                                               <   QCursor::pos().y()-this->geometry().top() &&
                            PatternOfItems[q]->top+this->PatternOfItems[q]->height               >   QCursor::pos().y()-this->geometry().top() && !PatternOfItems[q]->Hiden)
                    {
                        SuperBool=1;
                        ChoosingItem=PatternOfItems[q];
                        if ((ChoosingItem->Butt->GLeft()                              < QCursor::pos().x()-this->geometry().left()) &&
                                (ChoosingItem->Butt->GLeft()+ChoosingItem->Butt->GWidth() > QCursor::pos().x()-this->geometry().left()) &&
                                (ChoosingItem->Butt->GTop()                               < QCursor::pos().y()-this->geometry().top()) &&
                                (ChoosingItem->Butt->GTop()+ChoosingItem->Butt->GHeigth() > QCursor::pos().y()-this->geometry().top()))
                        {
                            ChoosingItem->Butt->Activate();
                            ChoosingItem=nullptr;
                            //repaint();
                        }else{
                            if (ChoosingItem->Layout!=nullptr){
                                int q=0;
                                while (ChoosingItem!=ChoosingItem->Layout->EnabledItems[q]){
                                    q++;
                                }
                                std::vector <item *> ::iterator it = ChoosingItem->Layout->EnabledItems.begin()+q;

                                ChoosingItem->NekstItem=nullptr;
                                ChoosingItem->Layout->EnabledItems.erase(it);
                            }
                            if (ChoosingItem->Type=="If"){
                                ChoosingItem->height=40*height()/820;
                                ChoosingItem->MyItems[0]->Hide(1);
                                ChoosingItem->MyItems[1]->Hide(1);
                            }else if (ChoosingItem->Type=="While"){
                                ChoosingItem->height=40*height()/820;
                                ChoosingItem->MyItems[0]->Hide(1);
                            }
                            //ReconstructItem0();
                            this->FirstMousePositions.setX(QCursor::pos().x());
                            this->FirstMousePositions.setY(QCursor::pos().y());
                            Slott=1;
                            this->TimerEvent();
                            this->moveEvent=true;
                        }
                        break;

                    }
                }
            }

        }
        ReconstructItem0();
    }
YbrbnfLjbr:{}
    repaint();
}

std::vector<item *>::iterator MainWindow::GetPos(item* Item, item* Layout){
        int h;
        if (Layout->EnabledItems.size()>0){
            int q;
            for (q=0; q<Layout->EnabledItems.size() && Item->GetLeftAndTop().second>Layout->EnabledItems[q]->GetLeftAndTop().second; q++){

            }
            std::vector<item *>::iterator it = Layout->EnabledItems.begin()+q;
            return it;
        }else{
            std::vector<item *>::iterator it = Layout->EnabledItems.begin();
            return it;
        }
    //return Layout->EnabledItems.begin();

}

void MainWindow::ReconstructItem0(){
    if (TT==0)
    {
        for (int j=KolLayout-1; j>=0; j--){
            items[j]->SumHeigth=0;
        }
        for (int j=KolLayout-1; j>=0; j--){
            int PointY=items[j]->top+15*height()/820;
            for (int i=0; i<items[j]->EnabledItems.size(); i++){
                if (i<items[j]->EnabledItems.size()-1){
                    items[j]->EnabledItems[i]->NekstItem=items[j]->EnabledItems[i+1];
                }else{
                    items[j]->EnabledItems[i]->NekstItem=nullptr;
                }
                if (!items[j]->Scroll)
                    if (items[j]->EnabledItems[i]->Type!="ArrayWork"){
                        items[j]->EnabledItems[i]->setGeometry(items[j]->EnabledItems[i]->GetWidthAndHeight().first, items[j]->EnabledItems[i]->GetWidthAndHeight().second ,
                                                               items[j]->GetLeftAndTop().first+(items[j]->GetWidthAndHeight().first - items[j]->EnabledItems[i]->GetWidthAndHeight().first)/2, PointY);
                    }else{
                        items[j]->EnabledItems[i]->setGeometry(items[j]->EnabledItems[i]->width, items[j]->EnabledItems[i]->height ,
                                                               items[j]->left+5*width()/1050, PointY);
                        /*j++;
                        items[j]->EnabledItems[i]->setGeometry(items[j]->EnabledItems[i]->GetWidthAndHeight().first, items[j]->EnabledItems[i]->GetWidthAndHeight().second ,
                                                               items[j]->GetLeftAndTop().first/2+5*width()/1050, PointY);
                        */
                    }
                PointY+=items[j]->EnabledItems[i]->height+15*height()/820;
            }
            items[j]->SumHeigth=PointY-items[j]->top;
            if (items[j]->EnabledItems.size()==0){
                items[j]->SumHeigth=15*height()/820;
            }
            //QMessageBox::critical(this, QString::number(items[j]->SumHeigth), QString::number(items[j]->height));
            if (items[j]->Pa!=nullptr){
                //ui->label->setText(QString::number(items[j]->SumHeigth));
                if (items[j]->Pa->Type=="If"){

                }
                if ((items[j]->Pa->Type=="While" && items[j]->SumHeigth+55*height()/820<=items[j]->MaxHeigth) || (items[j]->Pa->Type=="If" && std::max(items[j]->Pa->MyItems[0]->SumHeigth, items[j]->Pa->MyItems[1]->SumHeigth)+55*height()/820<=items[j]->MaxHeigth)){
                    if (items[j]->Pa->Type=="While")
                        items[j]->height=items[j]->SumHeigth+55*height()/820;
                    if (items[j]->Pa->Type=="If"){
                        items[j]->Pa->MyItems[0]->height=std::max(items[j]->Pa->MyItems[0]->SumHeigth, items[j]->Pa->MyItems[1]->SumHeigth)+55*height()/820;
                        items[j]->Pa->MyItems[1]->height=std::max(items[j]->Pa->MyItems[0]->SumHeigth, items[j]->Pa->MyItems[1]->SumHeigth)+55*height()/820;
                    }
                    items[j]->Pa->ShowHeigth=items[j]->height;
                }else{
                    items[j]->Pa->ShowHeigth=items[j]->MaxHeigth;
                    if (!items[j]->Hiden) items[j]->Pa->height=items[j]->Pa->ShowHeigth;
                    if (items[j]->Pa->Type=="While")
                        items[j]->height=items[j]->MaxHeigth;
                    else{
                        items[j]->Pa->MyItems[0]->height=items[j]->MaxHeigth;
                        items[j]->Pa->MyItems[1]->height=items[j]->MaxHeigth;
                    }
                }
                items[j]->Pa->ShowHeigth+=70*height()/820;
                if (items[j]->Pa->Type=="While"){
                    items[j]->Pa->ShowHeigth+=15*height()/820;                   
                }
                if (!items[j]->Hiden) items[j]->Pa->height=items[j]->Pa->ShowHeigth;
                if (items[j]->Pa->Layout!=nullptr){
                    if (items[j]->Pa->Type=="If"){
                        items[j]->Pa->HelpLine.clear();
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left, items[j]->Pa->top+20*height()/820, items[j]->Pa->left+items[j]->Pa->width/2-5-(items[j]->Pa->Layout->width-50)/4, items[j]->Pa->top+20*height()/820));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+items[j]->Pa->width/2-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+15*height()/820, items[j]->Pa->left+items[j]->Pa->width/2-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+20*height()/820));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+items[j]->Pa->width, items[j]->Pa->top+20*height()/820, items[j]->Pa->left+items[j]->Pa->width/2+5+(items[j]->Pa->Layout->width-50)/4, items[j]->Pa->top+20*height()/820));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+15*height()/820, items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+20*height()/820));

                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+38*width()/1050, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height+15*height()/820, items[j]->Pa->left+items[j]->Pa->width/2-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+30*height()/820+items[j]->Pa->MyItems[0]->height));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+items[j]->Pa->width/2-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height+15*height()/820, items[j]->Pa->left+items[j]->Pa->width/2-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+38*width()/1050, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height+15*height()/820, items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+30*height()/820+items[j]->Pa->MyItems[0]->height));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height,  items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+30*height()/820+items[j]->Pa->MyItems[0]->height));
                    }else if (items[j]->Pa->Type=="While"){
                        items[j]->Pa->HelpLine.clear();
                        //ChoosingItem->MyItems[1]->ScrollTop=0;
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+38*width()/1050, items[j]->Pa->top-5*height()/820, items[j]->Pa->left+items[j]->Pa->width/2-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top-5*height()/820));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+38*width()/1050, items[j]->Pa->top+40*height()/820+15*height()/820, items[j]->Pa->left+38*width()/1050, items[j]->Pa->top+40*height()/820));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+38*width()/1050, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height+15*height()/820, items[j]->Pa->left+items[j]->Pa->width/2-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+30*height()/820+items[j]->Pa->MyItems[0]->height));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+38*width()/1050, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height+15*height()/820, items[j]->Pa->left+38*width()/1050, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+38*width()/1050-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top-5*height()/820, items[j]->Pa->left+items[j]->Pa->width/2-5*width()/1050-(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height+15*height()/820));

                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+items[j]->Pa->width, items[j]->Pa->top+20*height()/820, items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+20*height()/820));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+45*height()/820+items[j]->Pa->MyItems[0]->height, items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+20*height()/820));
                        items[j]->Pa->HelpLine.push_back(QLine(items[j]->Pa->left+38*width()/1050, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height+30*height()/820, items[j]->Pa->left+items[j]->Pa->width/2+5*width()/1050+(items[j]->Pa->Layout->width-50*width()/1050)/4, items[j]->Pa->top+40*height()/820+15*height()/820+items[j]->Pa->MyItems[0]->height+30*height()/820));

                    }
                }

            }
            if (items[j]->SumHeigth>items[j]->height){
                items[j]->Scroll=1;
                if (items[j]->ScrollTop!=0){
                    items[j]->ScrollTop=items[j]->ScrollTop*items[j]->height*items[j]->height/items[j]->SumHeigth/items[j]->ScrollHeigth;
                    items[j]->ScrollHeigth=items[j]->height*items[j]->height/items[j]->SumHeigth;
                }
            }else{
                items[j]->Scroll=0;
            }
            if (items[j]->Scroll && items[j]->EnabledItems[items[j]->EnabledItems.size()-1]->top<items[j]->top+items[j]->height-15*height()/820-items[j]->EnabledItems[items[j]->EnabledItems.size()-1]->height){
                int del=items[j]->top+items[j]->height-15*height()/820-items[j]->EnabledItems[items[j]->EnabledItems.size()-1]->height-items[j]->EnabledItems[items[j]->EnabledItems.size()-1]->top;
                for (int i=0; i<items[j]->EnabledItems.size(); i++){
                    items[j]->EnabledItems[i]->move(0, del);
                }
                items[j]->ScrollTop=items[j]->height-items[j]->height*items[j]->height/items[j]->SumHeigth;
            }
        }
        std::vector <item *> li;
        int FS=0, k=0;
        while (FS!=li.size() || FS==0){
            FS=li.size();
            for (int i=0; i<KolLayout; i++){
                if (items[i]->n==k){
                    li.push_back(items[i]);
                }
            }
            k++;
        }
        for (int i=0; i<li.size(); i++){
            items[i]=li[i];
        }
        Suk->TE->setText("");
        items[0]->LineVariables.clear();
        items[0]->KolFuckVariable=0;
        std::vector <QString> F=Translate(items[0], 0, 0);
        for (int i=0; i<F.size();
             i++){
            //CodeLineL.push_back(new QLabel(this));
            Suk->TE->append(F[i]);
            //CodeLineL[i]->move(800, 150+i*25);
            //CodeLineL[i]->show();
            //TE->resize(300, 17*i+17);
        }
        Suk->repaint();
        //ui->pushButton->setText(QString::number(items[1]->SumHeigth));
    }
}

void MainWindow::InButton(){
    for (int i=0; i<KolLayout; i++){
        for (int j=0; j<items[i]->EnabledItems.size(); j++)
        if (items[i]->EnabledItems[j]->Type=="In")
            if ((items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left()  +items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()  +items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                //QMessageBox::critical(this, "", "");
                if (items[i]->EnabledItems[j]->Butt->Frame2.size()==0 || items[i]->EnabledItems[j]->Butt->Frame2[items[i]->EnabledItems[j]->Butt->Frame2.size()-1]->text()!=""){
                    items[i]->EnabledItems[j]->Butt->Frame2.push_back(new QLineEdit(this));
                    items[i]->EnabledItems[j]->Butt->Frame2[items[i]->EnabledItems[j]->Butt->Frame2.size()-1]->show();
                    items[i]->EnabledItems[j]->Butt->Frame1.push_back(new QComboBox(this));
                    items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->show();
                    if (landg!="Eng"){
                        items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->addItem("Целочисленное");
                        items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->addItem("Вещественное");
                        items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->addItem("Текст");
                    }else{
                        items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->addItem("Integer");
                        items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->addItem("Real");
                        items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->addItem("Text");
                    }
                    items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->move(items[i]->EnabledItems[j]->Butt->LeftFrame+10*width()/1050, items[i]->EnabledItems[j]->Butt->TopFrame+10*height()/820+35*height()/820*(items[i]->EnabledItems[j]->Butt->Frame1.size()-1));
                    items[i]->EnabledItems[j]->Butt->Frame2[items[i]->EnabledItems[j]->Butt->Frame2.size()-1]->move(items[i]->EnabledItems[j]->Butt->LeftFrame+112*width()/1050, items[i]->EnabledItems[j]->Butt->TopFrame+10*height()/820+35*height()/820*(items[i]->EnabledItems[j]->Butt->Frame2.size()-1));
                    items[i]->EnabledItems[j]->Butt->Frame2[items[i]->EnabledItems[j]->Butt->Frame2.size()-1]->resize(50*width()/1050, 25*height()/820);
                    items[i]->EnabledItems[j]->Butt->Frame1[items[i]->EnabledItems[j]->Butt->Frame1.size()-1]->resize(100*width()/1050, 25*height()/820);
                    items[i]->EnabledItems[j]->Butt->Frame4[0]->move(items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left(), items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()+35*height()/820);
                    items[i]->EnabledItems[j]->Butt->HeigthFrame+=35*height()/820;
                    items[i]->EnabledItems[j]->Butt->Frame5.push_back(new QCheckBox(this));
                    items[i]->EnabledItems[j]->Butt->Frame5[items[i]->EnabledItems[j]->Butt->Frame5.size()-1]->move(items[i]->EnabledItems[j]->Butt->LeftFrame+165*width()/1050, items[i]->EnabledItems[j]->Butt->TopFrame+15*height()/820+35*height()/820*(items[i]->EnabledItems[j]->Butt->Frame1.size()-1));
                    if (landg!="Eng")
                        items[i]->EnabledItems[j]->Butt->Frame5[items[i]->EnabledItems[j]->Butt->Frame5.size()-1]->setText("Ввод");
                    else
                        items[i]->EnabledItems[j]->Butt->Frame5[items[i]->EnabledItems[j]->Butt->Frame5.size()-1]->setText("input");
                    items[i]->EnabledItems[j]->Butt->Frame5[items[i]->EnabledItems[j]->Butt->Frame5.size()-1]->show();
                    items[i]->EnabledItems[j]->Butt->Frame6.push_back(new ButtonClose(items[i]->EnabledItems[j]->Butt->LeftFrame+165*width()/1050, 12*width()/1050, items[i]->EnabledItems[j]->Butt->TopFrame+7*height()/820+35*height()/820*(items[i]->EnabledItems[j]->Butt->Frame6.size()), 12*height()/820));
                    items[i]->EnabledItems[j]->Butt->FrameCorrect();
                    repaint();
                }
            }
    }
}

void MainWindow::OutButton(){
    for (int i=0; i<KolLayout; i++){
        for (int j=0; j<items[i]->EnabledItems.size(); j++)
        if (items[i]->EnabledItems[j]->Type=="Out"){
            if ((items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left()  +items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()  +items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                //QMessageBox::critical(this, "", "");
                items[i]->EnabledItems[j]->Butt->Frame2.push_back(new QLineEdit(this));
                items[i]->EnabledItems[j]->Butt->Frame2[items[i]->EnabledItems[j]->Butt->Frame2.size()-1]->show();
                items[i]->EnabledItems[j]->Butt->Frame2[items[i]->EnabledItems[j]->Butt->Frame2.size()-1]->move(items[i]->EnabledItems[j]->Butt->LeftFrame+10*width()/1050, items[i]->EnabledItems[j]->Butt->TopFrame+10*height()/820+35*height()/820*(items[i]->EnabledItems[j]->Butt->Frame2.size()-1));
                items[i]->EnabledItems[j]->Butt->Frame2[items[i]->EnabledItems[j]->Butt->Frame2.size()-1]->resize(170*width()/1050, 25*height()/820);
                items[i]->EnabledItems[j]->Butt->Frame4[0]->move(items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left(), items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()+35*height()/820);
                items[i]->EnabledItems[j]->Butt->HeigthFrame+=35*height()/820;
                items[i]->EnabledItems[j]->Butt->Frame6.push_back(new ButtonClose(items[i]->EnabledItems[j]->Butt->LeftFrame+185*width()/1050, 15*width()/1050, items[i]->EnabledItems[j]->Butt->TopFrame+15*height()/820+35*height()/820*(items[i]->EnabledItems[j]->Butt->Frame6.size()), 15*height()/820));
                items[i]->EnabledItems[j]->Butt->FrameCorrect();
                repaint();
                break;
            }
        }else if (items[i]->EnabledItems[j]->Type=="Pattern"){
            if ((items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().left()  +items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                    (items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().top()  +items[i]->EnabledItems[j]->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                int q=0;
                for (; items[i]->EnabledItems[j]!=PatternOfItems[q]; q++);
                if (items[i]->EnabledItems[j]->Butt->Frame2[0]->text()!=""){
                    ui->comboBox_2->setItemText(q-7, items[i]->EnabledItems[j]->Butt->Frame2[0]->text());
                    std::map <QString, int>::iterator ith=libA.find(items[i]->EnabledItems[j]->Type2);
                    libA.erase(ith);
                    std::map <QString, std::vector <item*> >::iterator plq=PatternMap.find(items[i]->EnabledItems[j]->Type2);
                    std::vector <item*> tempV=PatternMap[items[i]->EnabledItems[j]->Type2];
                    PatternMap.erase(plq);
                    PatternMap[items[i]->EnabledItems[j]->Butt->Frame2[0]->text()]=tempV;
                    std::pair <QString, int> tye (items[i]->Butt->Frame2[0]->text(), q+1);
                    libA.insert(ith, tye);
                    QString hj=items[i]->EnabledItems[j]->Type2;
                    for (j=0; j<items.size(); j++){
                        if (items[j]->EnabledItems[j]->Type2==hj && items[j]->EnabledItems[j]->Type=="Pattern"){
                            items[j]->EnabledItems[j]->Type2=items[i]->Butt->Frame2[0]->text();
                            items[j]->EnabledItems[j]->Butt->Frame2[0]->setText(items[j]->EnabledItems[j]->Type2);
                            items[j]->EnabledItems[j]->Label_Instructions[0]->setText(items[i]->EnabledItems[j]->Butt->Frame2[0]->text());
                        }
                    }
                }else{
                    if (landg=="Eng"){
                        QMessageBox::critical(this, "Error", "The field should not be empty");
                    }else{
                        QMessageBox::critical(this, "Ошибка", "Поле не должно быть пустым");
                    }
                    items[i]->EnabledItems[j]->Butt->Frame2[0]->setText(items[i]->EnabledItems[j]->Type2);
                }
                break;
            }
        }
    }

}

void MainWindow::ArithmeticButton(){
    for (int i=KolLayout-1; i>=0; i--){
        for (int j=0; j<items[i]->EnabledItems.size(); j++){
            item* ite=items[i]->EnabledItems[j];
            if (ite->Type=="Arithmetic" && ite->Butt->IsActivate){
                if ((ite->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                        (ite->Butt->Frame4[0]->geometry().left()  +ite->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                        (ite->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                        (ite->Butt->Frame4[0]->geometry().top()  +ite->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                    //QMessageBox::critical(this, "", "");
                    ite->Butt->Frame2.push_back(new QLineEdit(this));
                    ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->show();
                    ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->move(ite->Butt->LeftFrame+10*width()/1050, ite->Butt->TopFrame+10*height()/820+35*height()/820*(ite->Butt->Frame2.size()-1));
                    ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->resize(170*width()/1050, 25*height()/820);
                    ite->Butt->Frame4[0]->move(ite->Butt->Frame4[0]->geometry().left(), ite->Butt->Frame4[0]->geometry().top()+35*height()/820);
                    ite->Butt->HeigthFrame+=35*height()/820;
                    ite->Butt->Frame6.push_back(new ButtonClose(ite->Butt->LeftFrame+185*width()/1050, 15*width()/1050, ite->Butt->TopFrame+15*height()/820+35*height()/820*(ite->Butt->Frame6.size()), 15*height()/820));
                    ite->Butt->FrameCorrect();
                    repaint();
                    break;
                }
            }else if (ite->Type=="If" && ite->Butt->IsActivate){
                if (((ite->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                        (ite->Butt->Frame4[0]->geometry().left()  +ite->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                        (ite->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                        ite->Butt->Frame4[0]->geometry().top()  +ite->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                    //QMessageBox::critical(this, "", "");
                    if (ite->Butt->Frame2.size()==0){
                        ite->Butt->Frame2.push_back(new QLineEdit(this));
                        ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->show();
                        ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->move(ite->Butt->LeftFrame+10*width()/1050, ite->Butt->TopFrame+10*height()/820+35*height()/820*(ite->Butt->Frame2.size()-1));
                        ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->resize(170*width()/1050, 25*height()/820);
                        ite->Butt->Frame4[0]->move(ite->Butt->Frame4[0]->geometry().left(), ite->Butt->Frame4[0]->geometry().top()+35*height()/820);
                        if (landg!="Eng")
                            ite->Butt->Frame4[0]->setText("Показать/Скрыть");
                        else {
                            ite->Butt->Frame4[0]->setText("Show/Hide");
                        }
                        ite->Butt->HeigthFrame+=35*height()/820;
                        ite->Butt->Frame6.push_back(new ButtonClose(ite->Butt->LeftFrame+185*width()/1050, 15*width()/1050, ite->Butt->TopFrame+15*height()/820+35*height()/820*(ite->Butt->Frame6.size()), 15*height()/820));
                        ite->Butt->FrameCorrect();
                    }else{
                        ite->Butt->Activate();
                        if (ite->MyItems[0]->Hiden)
                            ite->hh=0;
                        else{
                            ite->hh=1;
                        }
                        //QMessageBox::critical(this, QString::number(height()), QString::number(ite->height));
                        if (ite->height==40*height()/820){
                            ite->Butt->Frame3[0]->show();
                            ite->Butt->Frame3[1]->show();
                            //QMessageBox::critical(this, "+", "");
                            if (ite->Layout!=nullptr){
                                ite->height=ite->ShowHeigth;

                                int qq=0;
                                for (; ite->Layout->EnabledItems[qq]!=ite; qq++);
                                qq++;
                                for (; qq<ite->Layout->EnabledItems.size(); qq++){
                                    ite->Layout->EnabledItems[qq]->move(0, ite->ShowHeigth-40*height()/820);
                                }
                                ReconstructItem0();
                                ite->MyItems[0]->Hide(0);
                                ite->MyItems[1]->Hide(0);
                                //HideBlocks(items[i], 0);

                            }
                        }else if (ite->height==ite->ShowHeigth){
                            ite->Butt->Frame3[0]->hide();
                            ite->Butt->Frame3[1]->hide();
                            //QMessageBox::critical(this, "-", "");
                            if (ite->Layout!=nullptr){
                                    int qq=0;
                                    for (; ite->Layout->EnabledItems[qq]!=ite; qq++);
                                    qq++;
                                    for (; qq<ite->Layout->EnabledItems.size(); qq++){
                                        ite->Layout->EnabledItems[qq]->move(0, 40*height()/820-ite->ShowHeigth);
                                    }
                                ite->height=40*height()/820;
                                ReconstructItem0();
                            }
                            ite->MyItems[0]->Hide(1);
                            ite->MyItems[1]->Hide(1);
                        }
                        if (items[i]->EnabledItems.size()>0){
                            if(!items[i]->Scroll){
                                items[i]->ScrollTop=0;
                                int del=items[i]->top-items[i]->EnabledItems[0]->top+15*height()/820;
                                for (int q=0; q<items[i]->EnabledItems.size(); q++){
                                    items[i]->EnabledItems[q]->move(0, del);
                                }
                            }else{
                                if (items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top<items[i]->top+items[i]->height-15*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->height){
                                    items[i]->ScrollTop=items[i]->height-items[i]->height*items[i]->height/items[i]->SumHeigth;
                                    int del=items[i]->top+items[i]->height-15*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top;
                                    for (int q=0; q<items[i]->EnabledItems.size(); q++){
                                        items[i]->EnabledItems[q]->move(0, del);
                                    }
                                }
                            }

                        }
                    }
                    goto L;
                }
            }else if(ite->Type=="While" && ite->Butt->IsActivate){
                if ((ite->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                        (ite->Butt->Frame4[0]->geometry().left()  +ite->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                        (ite->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                        (ite->Butt->Frame4[0]->geometry().top()  +ite->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                    //QMessageBox::critical(this, "", "");
                    if (ite->Butt->Frame2.size()==0){
                        ite->Butt->Frame2.push_back(new QLineEdit(this));
                        ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->show();
                        ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->move(ite->Butt->LeftFrame+10*width()/1050, ite->Butt->TopFrame+10*height()/820+35*height()/820*(ite->Butt->Frame2.size()-1));
                        ite->Butt->Frame2[ite->Butt->Frame2.size()-1]->resize(170*width()/1050, 25*height()/820);
                        ite->Butt->Frame4[0]->move(ite->Butt->Frame4[0]->geometry().left(), ite->Butt->Frame4[0]->geometry().top()+35*height()/820);
                        if (landg!="Eng")
                            ite->Butt->Frame4[0]->setText("Показать/Скрыть");
                        else {
                            ite->Butt->Frame4[0]->setText("Show/Hide");
                        }
                        ite->Butt->HeigthFrame+=35*height()/820;
                        ite->Butt->Frame6.push_back(new ButtonClose(ite->Butt->LeftFrame+185*width()/1050, 15*width()/1050, ite->Butt->TopFrame+15*height()/820+35*height()/820*(ite->Butt->Frame6.size()), 15*height()/820));
                        ite->Butt->FrameCorrect();
                    }else{
                        //items[i]->Butt->Activate();
                        ite->Butt->Activate();
                        if (ite->MyItems[0]->Hiden)
                            ite->hh=0;
                        else{
                            ite->hh=1;
                        }
                        if (ite->height==40*height()/820){
                            ite->Butt->Frame3[0]->show();
                            ite->Butt->Frame3[1]->show();
                            if (ite->Layout!=nullptr){
                                ite->height=ite->ShowHeigth;
                                int qq=0;
                                for (; ite->Layout->EnabledItems[qq]!=ite; qq++);
                                qq++;
                                for (; qq<ite->Layout->EnabledItems.size(); qq++){
                                    ite->Layout->EnabledItems[qq]->move(0, ite->ShowHeigth-40*height()/820);
                                }
                                //Reco
                                ReconstructItem0();
                                ite->MyItems[0]->Hide(0);
                                //items[i]->MyItems[1]->Hide(0);
                                //HideBlocks(items[i], 0);
                            }
                        }else{
                            ite->Butt->Frame3[0]->hide();
                            ite->Butt->Frame3[1]->hide();
                            if (ite->Layout!=nullptr){
                                if (ite->height!=40*height()/820){
                                    int qq=0;
                                    for (; ite->Layout->EnabledItems[qq]!=ite; qq++);
                                    qq++;
                                    for (; qq<ite->Layout->EnabledItems.size(); qq++){
                                        ite->Layout->EnabledItems[qq]->move(0, 40*height()/820-ite->ShowHeigth);
                                    }
                                }
                                ite->height=40*height()/820;
                                ReconstructItem0();
                            }
                            ite->MyItems[0]->Hide(1);
                            //items[i]->MyItems[1]->Hide(1);
                        }
                        if (items[i]->EnabledItems.size()>0 && ite->height==40*height()/820){
                            if(!items[i]->Scroll){
                                items[i]->ScrollTop=0;
                                int del=items[i]->top-items[i]->EnabledItems[0]->top+15*height()/820;
                                for (int q=0; q<items[i]->EnabledItems.size(); q++){
                                    items[i]->EnabledItems[q]->move(0, del);
                                }
                            }else{
                                if (items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top<items[i]->top+items[i]->height-15*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->height){
                                    items[i]->ScrollTop=items[i]->height-items[i]->height*items[i]->height/items[i]->SumHeigth;
                                    int del=items[i]->top+items[i]->height-15*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top;
                                    for (int q=0; q<items[i]->EnabledItems.size(); q++){
                                        items[i]->EnabledItems[q]->move(0, del);
                                    }
                                }
                            }

                        }
                    }
                    goto L;
                }
            }
        }
        if (0){
L:{}
            /*if (items[i]->EnabledItems.size()>0){
                if(items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top < items[i]->height+items[i]->top-40*height()/820){
                    items[i]->ScrollTop=items[i]->height-items[i]->height*items[i]->height/items[i]->SumHeigth;
                    int del=items[i]->top+items[i]->height-40*height()/820-items[i]->EnabledItems[items[i]->EnabledItems.size()-1]->top;
                    for (int j=0; j<items[i]->EnabledItems.size(); j++){
                        items[i]->EnabledItems[j]->move(0, del);
                    }
                }
                if (items[i]->EnabledItems[0]->top>items[i]->top+15*height()/820){
                    items[i]->ScrollTop=0;
                    int del=items[i]->top-items[i]->EnabledItems[0]->top+15*height()/820;
                    for (int j=0; j<items[i]->EnabledItems.size(); j++){
                        items[i]->EnabledItems[i]->move(0, del);
                    }
                }
            }*/
            break;
        }
    }
    ReconstructItem0();
    repaint();
}


void MainWindow::on_action_triggered()
{
    for (int i=items[0]->EnabledItems.size()-1; i>=0; i--){
        DeleteBlock(items[0]->EnabledItems[i]);
    }
    Suk->TE->setText("");
    items[0]->LineVariables.clear();
    std::vector <QString> F=Translate(items[0], 0, 0);

    for (int i=0; i<F.size(); i++){
        //CodeLineL.push_back(new QLabel(this));
        Suk->TE->append(F[i]);
        //CodeLineL[i]->move(800, 150+i*25);
        //CodeLineL[i]->show();
        //TE->resize(300, 17*i+17);
    }
    ReconstructItem0();
    repaint();
    addres=QDir::currentPath()+"/Blocks/PAndS_prim.PCPb";
    //QMessageBox::critical(this, "", addres);
    QFile r1(addres);
    r1.open(QIODevice::ReadOnly);
        QTextStream r(&r1);
        OpenArrea(&r, items[0]);
        for (int i=0; i<items[0]->EnabledItems.size(); i++){
            if (items[0]->EnabledItems[i]->Type=="If" || items[0]->EnabledItems[i]->Type=="While"){
                for (int j=0; j<items[0]->EnabledItems[i]->MyItems.size(); j++){
                    items[0]->EnabledItems[i]->MyItems[j]->Hide(1);
                }
            }
        }
    r1.close();
    ReconstructItem0();
}

void MainWindow::on_action_2_triggered()
{
    for (int i=items[0]->EnabledItems.size()-1; i>=0; i--){
        DeleteBlock(items[0]->EnabledItems[i]);
    }
    Suk->TE->setText("");
    items[0]->LineVariables.clear();
    std::vector <QString> F=Translate(items[0], 0, 0);

    for (int i=0; i<F.size(); i++){
        //CodeLineL.push_back(new QLabel(this));
        Suk->TE->append(F[i]);
        //CodeLineL[i]->move(800, 150+i*25);
        //CodeLineL[i]->show();
        //TE->resize(300, 17*i+17);
    }
    ReconstructItem0();
    repaint();
    //QMessageBox::critical(this, "", QDir::currentPath());
    addres=QDir::currentPath()+"/Blocks/SumOfDigits_type1.PCPb";
    QFile r1(addres);
    r1.open(QIODevice::ReadOnly);
        QTextStream r(&r1);
        OpenArrea(&r, items[0]);
        for (int i=0; i<items[0]->EnabledItems.size(); i++){
            if (items[0]->EnabledItems[i]->Type=="If" || items[0]->EnabledItems[i]->Type=="While"){
                for (int j=0; j<items[0]->EnabledItems[i]->MyItems.size(); j++){
                    items[0]->EnabledItems[i]->MyItems[j]->Hide(1);
                }
            }
        }
    r1.close();
    ReconstructItem0();
}


void MainWindow::on_action_3_triggered()
{
    for (int i=items[0]->EnabledItems.size()-1; i>=0; i--){
        DeleteBlock(items[0]->EnabledItems[i]);
    }
    Suk->TE->setText("");
    items[0]->LineVariables.clear();
    std::vector <QString> F=Translate(items[0], 0, 0);

    for (int i=0; i<F.size(); i++){
        //CodeLineL.push_back(new QLabel(this));
        Suk->TE->append(F[i]);
        //CodeLineL[i]->move(800, 150+i*25);
        //CodeLineL[i]->show();
        //TE->resize(300, 17*i+17);
    }
    ReconstructItem0();
    repaint();
    addres=QDir::currentPath()+"/Blocks/MaxMin.PCPb";
    QFile r1(addres);
    r1.open(QIODevice::ReadOnly);
        QTextStream r(&r1);
        OpenArrea(&r, items[0]);
        for (int i=0; i<items[0]->EnabledItems.size(); i++){
            if (items[0]->EnabledItems[i]->Type=="If" || items[0]->EnabledItems[i]->Type=="While"){
                for (int j=0; j<items[0]->EnabledItems[i]->MyItems.size(); j++){
                    items[0]->EnabledItems[i]->MyItems[j]->Hide(1);
                }
            }
        }
    r1.close();
    ReconstructItem0();
}

void MainWindow::on_action_4_triggered()
{
    for (int i=items[0]->EnabledItems.size()-1; i>=0; i--){
        DeleteBlock(items[0]->EnabledItems[i]);
    }
    Suk->TE->setText("");
    items[0]->LineVariables.clear();
    std::vector <QString> F=Translate(items[0], 0, 0);

    for (int i=0; i<F.size(); i++){
        //CodeLineL.push_back(new QLabel(this));
        Suk->TE->append(F[i]);
        //CodeLineL[i]->move(800, 150+i*25);
        //CodeLineL[i]->show();
        //TE->resize(300, 17*i+17);
    }
    ReconstructItem0();
    repaint();
    addres=QDir::currentPath()+"/Blocks/IsEven.PCPb";
    QFile r1(addres);
    r1.open(QIODevice::ReadOnly);
        QTextStream r(&r1);
        OpenArrea(&r, items[0]);
        for (int i=0; i<items[0]->EnabledItems.size(); i++){
            if (items[0]->EnabledItems[i]->Type=="If" || items[0]->EnabledItems[i]->Type=="While"){
                for (int j=0; j<items[0]->EnabledItems[i]->MyItems.size(); j++){
                    items[0]->EnabledItems[i]->MyItems[j]->Hide(1);
                }
            }
        }
    r1.close();
    ReconstructItem0();
}

void MainWindow::on_action_5_triggered()
{
    for (int i=items[0]->EnabledItems.size()-1; i>=0; i--){
        DeleteBlock(items[0]->EnabledItems[i]);
    }
    Suk->TE->setText("");
    items[0]->LineVariables.clear();
    std::vector <QString> F=Translate(items[0], 0, 0);

    for (int i=0; i<F.size(); i++){
        //CodeLineL.push_back(new QLabel(this));
        Suk->TE->append(F[i]);
        //CodeLineL[i]->move(800, 150+i*25);
        //CodeLineL[i]->show();
        //TE->resize(300, 17*i+17);
    }
    ReconstructItem0();
    repaint();
    addres=QDir::currentPath()+"/Blocks/SumOfNumbers_Type1.PCPb";
    QFile r1(addres);
    r1.open(QIODevice::ReadOnly);
        QTextStream r(&r1);
        OpenArrea(&r, items[0]);
        for (int i=0; i<items[0]->EnabledItems.size(); i++){
            if (items[0]->EnabledItems[i]->Type=="If" || items[0]->EnabledItems[i]->Type=="While"){
                for (int j=0; j<items[0]->EnabledItems[i]->MyItems.size(); j++){
                    items[0]->EnabledItems[i]->MyItems[j]->Hide(1);
                }
            }
        }
    r1.close();
    ReconstructItem0();
}

void MainWindow::on_action_6_triggered()
{
    for (int i=items[0]->EnabledItems.size()-1; i>=0; i--){
        DeleteBlock(items[0]->EnabledItems[i]);
    }
    Suk->TE->setText("");
    items[0]->LineVariables.clear();
    std::vector <QString> F=Translate(items[0], 0, 0);

    for (int i=0; i<F.size(); i++){
        //CodeLineL.push_back(new QLabel(this));
        Suk->TE->append(F[i]);
        //CodeLineL[i]->move(800, 150+i*25);
        //CodeLineL[i]->show();
        //TE->resize(300, 17*i+17);
    }
    ReconstructItem0();
    repaint();
    //QMessageBox::critical(this, "", QDir::currentPath());
    addres=QDir::currentPath()+"/Blocks/SumOfDigits_Type2.PCPb";
    QFile r1(addres);
    r1.open(QIODevice::ReadOnly);
        QTextStream r(&r1);
        OpenArrea(&r, items[0]);
        for (int i=0; i<items[0]->EnabledItems.size(); i++){
            if (items[0]->EnabledItems[i]->Type=="If" || items[0]->EnabledItems[i]->Type=="While"){
                for (int j=0; j<items[0]->EnabledItems[i]->MyItems.size(); j++){
                    items[0]->EnabledItems[i]->MyItems[j]->Hide(1);
                }
            }
        }
    r1.close();
    ReconstructItem0();
}

void MainWindow::on_comboBox_activated(int index)
{
    Suk->show();
    //Suk->repaint();
    //Suk->close();
    for (int i=items.size()-1; i>=KolLayout; i--){
        if (items[i]->Butt->IsActivate){
            items[i]->Butt->Activate();
            break;
        }
    }
    Suk->TE->setText("");
    //CodeLineL.clear();
    items[0]->LineVariables.clear();
    items[0]->KolFuckVariable=0;
    std::vector <QString> F=Translate(items[0], 0, 0);

    for (int i=0; i<F.size(); i++){
        //CodeLineL.push_back(new QLabel(this));
        Suk->TE->append(F[i]);
        //CodeLineL[i]->move(800, 150+i*25);
        //CodeLineL[i]->show();
        //TE->resize(300, 17*i+17);
    }
    Suk->repaint();
}

void MainWindow::on_comboBox_2_activated(int index)
{
    for (int i=items.size()-1; i>=KolLayout; i--){
        if (items[i]->Butt!=nullptr && items[i]->Butt->IsActivate){
            items[i]->Butt->Activate();
            break;
        }
    }
    repaint();
}
