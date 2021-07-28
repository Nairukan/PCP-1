#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <vector>
#include <map>
#include <QMessageBox>
#include <QMouseEvent>
#include <QCursor>
#include <QTimer>
#include <QPushButton>
#include <iostream>
#include <algorithm>
#include <QComboBox>

//#define TEXT "SomeText"

std::map <QString, int> libA = {{"Begin", 0},
                                    {"End", 1},
                                    {"Arithmetic", 2},
                                    {"Out", 3},
                                    {"In", 4},
                                    {"ArrayWork", 5},
                                    {"If", 6}};

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

std::map <int, QPoint> LibPoints = {{0, QPoint(30, 100)},
                                    {1, QPoint(30, 200)},
                                    {2, QPoint(30, 300)},
                                    {4, QPoint(30, 500)},
                                    {3, QPoint(30, 400)},
                                    {6, QPoint(30, 600)}};

void MainWindow::NewBlock(QString type){
    item *it = new item(type, this);
    if (libA[type]<5 || libA[type]==6){
        int w=75, h=40;
        it->Label_Instructions.push_back(new QLabel(this));
        it->Label_Instructions[0]->setAlignment(Qt::AlignCenter);
        it->Label_Instructions[0]->setStyleSheet("color : blue;");
        it->Label_Instructions[0]->setMinimumSize(w+10, h);
        it->Label_Instructions[0]->show();
        it->SetTextOnLabel(type);
        if (libA[type]<3){
            it->lineInstructions.push_back(*(new PointToPoint(0, 0, w, 0)));
            it->lineInstructions.push_back(*(new PointToPoint(0, 0, 0, h)));
            it->lineInstructions.push_back(*(new PointToPoint(w, 0, w, h)));
            it->lineInstructions.push_back(*(new PointToPoint(0, h, w, h)));
            it->setGeometry(w, h, 0, 0);
        }else if(libA[type]==6){
            it->lineInstructions.push_back(*(new PointToPoint(0, h/2, w/2, 0)));
            it->lineInstructions.push_back(*(new PointToPoint(0, h/2, w/2, h)));
            it->lineInstructions.push_back(*(new PointToPoint(w/2, 0, w, h/2)));
            it->lineInstructions.push_back(*(new PointToPoint(w/2, h, w, h/2)));
            it->setGeometry(w, h, 0, 0);
        }else{
            it->lineInstructions.push_back(*(new PointToPoint(w/7.5, 0, w, 0)));
            it->lineInstructions.push_back(*(new PointToPoint(w/7.5, 0, 0, h)));
            it->lineInstructions.push_back(*(new PointToPoint(w, 0, w-w/7.5, h)));
            it->lineInstructions.push_back(*(new PointToPoint(0, h, w-w/7.5, h)));
            it->setGeometry(w, h, 0, 0);
        }
        it->move(LibPoints[libA[it->Type]].x(), LibPoints[libA[it->Type]].y());
        it->position=items.size();
        items.push_back(it);
    }else{
        int w=550, h=600;
        it->lineInstructions.push_back(*(new PointToPoint(0, 0, w, 0)));
        it->lineInstructions.push_back(*(new PointToPoint(0, 0, 0, h)));
        it->lineInstructions.push_back(*(new PointToPoint(w, 0, w, h)));
        it->lineInstructions.push_back(*(new PointToPoint(0, h, w, h)));
        it->setGeometry(w, h, 0, 0);
        it->move(150, 10);
        it->position=KolLayout;
        std::vector <item*>::iterator it1 = items.begin() + KolLayout;
        KolLayout++;
        items.insert(it1, it);
        for (int i=KolLayout; i<items.size(); i++){
            items[i]->position++;
        }
        if (ChoosingItem!=nullptr){
            QMessageBox::critical(this, "Check 71-79 line", "");
            for (int i=0; i<KolLayout-1; i++){
                for (int j=0; j<items[i]->EnabledItems.size(); j++){
                    if (ChoosingItem->Layout->EnabledItems[i]>=ChoosingItem->position){
                        ChoosingItem->Layout->EnabledItems[i]--;
                    }
                }
            }
        }
    }
    it->Type=type;
}

void MainWindow::SetStartingSetting(){
    this->resize(1280, 720);
    NewBlock("ArrayWork");
    items[0]->move(0, 50);
    this->ui->mainToolBar->hide();
    connect(this->Timer1, SIGNAL(timeout()), this, SLOT(FollowMouse()));
    NewBlock("Begin");
    NewBlock("End");
    NewBlock("Arithmetic");
    NewBlock("Out");
    NewBlock("In");
    NewBlock("If");
    //NewBlock("ArrayWork");
    //this->ui->label->hide();
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(PushButton()));
    //ui->lineEdit->setFocus();
    ui->pushButton->move(710, 300);
    ui->pushButton->setText("Translate");
    ui->comboBox->move(710, 340);
    ui->comboBox->resize(75, 25);
    ui->comboBox->addItem("C++");
    ui->comboBox->addItem("Pascal");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->SetStartingSetting();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Translate(item* MainItem){
    if (ui->comboBox->currentIndex()==0){
        for (int i=0; i<MainItem->EnabledItems.size(); i++){
            switch (libA[items[MainItem->EnabledItems[i]]->Type]) {
                case 0:{
                    CodeLine.push_back("#include <bits/stdc++.h>");
                    CodeLine.push_back("using namespace std;");
                    CodeLine.push_back("int main(){");
                    break;
                }
                case 1:{
                    CodeLine.push_back("return 0;");
                    CodeLine.push_back("}");
                    break;
                }
                case 3:{
                    for (int j=0; j<items[MainItem->EnabledItems[i]]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line.operator=(items[MainItem->EnabledItems[i]]->Butt->Frame2[j]->text());
                        if (Line.length()!=0){
                            Line+"\"";
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
                            if (temp.size()!=0){
                                op.push_back(temp);
                                temp="";
                            }
                            for (int q=0; q<op.size(); q++){
                                if (op[q][0]=='"' && op[q][op[q].size()-1]=='"'){

                                }else{
                                    bool w=1;
                                    for (int yy=0; yy<op[q].length(); yy++){
                                        if (!(op[q][yy]>='0' && op[q][yy]<='9')){
                                            w=0;
                                            break;
                                        }
                                    }
                                    if (!w){
                                        int u=0;
                                        for (; u<LineVariables.size(); u++){
                                            if (op[q]==LineVariables[u].first){
                                                break;
                                            }
                                        }
                                        if (u==LineVariables.size()){
                                            std::pair <QString, QString> ttt;
                                            ttt.first=op[q];
                                            ttt.second="variable is not looking";
                                            LineVariables.push_back(ttt);
                                        }
                                    }
                                }
                            }
                            CodeLine.push_back("cout");
                            if (j>0){
                                CodeLine[CodeLine.size()-1]+=" << endl";
                            }
                            for (int q=0; q<op.size(); q++){
                                CodeLine[CodeLine.size()-1]+=" << "+op[q];
                            }
                            CodeLine[CodeLine.size()-1]+=";";
                            if (op.size()==0){
                                CodeLine.erase(CodeLine.end());
                            }
                        }else{
                            CodeLine.push_back("cout << endl;");
                        }
                    }
                    break;
                }
                case 4:{ //IN
                for (int j=0; j<items[MainItem->EnabledItems[i]]->Butt->Frame2.size(); j++){
                    QString Line;
                    Line.operator=(items[MainItem->EnabledItems[i]]->Butt->Frame2[j]->text());
                    if (Line.length()!=0){
                        Line+"\"";
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
                        if (temp.size()!=0){
                            op.push_back(temp);
                            temp="";
                        }
                        for (int q=0; q<op.size(); q++){
                            if (op[q][0]=='"' && op[q][op[q].size()-1]=='"'){

                            }else{
                                bool w=1;
                                for (int yy=0; yy<op[q].length(); yy++){
                                    if (!(op[q][yy]>='0' && op[q][yy]<='9')){
                                        w=0;
                                        break;
                                    }
                                }
                                if (!w){
                                    int u=0;
                                    for (; u<LineVariables.size(); u++){
                                        if (op[q]==LineVariables[u].first){
                                            break;
                                        }
                                    }
                                    if (u==LineVariables.size()){
                                        std::pair <QString, QString> ttt;
                                        ttt.first=op[q];
                                        if (items[MainItem->EnabledItems[i]]->Butt->Frame1[j]->currentIndex()==0)
                                            ttt.second="0";
                                        if (items[MainItem->EnabledItems[i]]->Butt->Frame1[j]->currentIndex()==1)
                                            ttt.second="0.0";
                                        if (items[MainItem->EnabledItems[i]]->Butt->Frame1[j]->currentIndex()==2)
                                            ttt.second="StartingString";
                                        LineVariables.push_back(ttt);
                                    }
                                }
                            }
                        }
                        CodeLine.push_back("cin");
                        for (int q=0; q<op.size(); q++){
                            CodeLine[CodeLine.size()-1]+=" >> "+op[q];
                        }
                        CodeLine[CodeLine.size()-1]+=";";
                        if (op.size()==0){
                            CodeLine.erase(CodeLine.end());
                        }
                    }
                }
                break;
                }
                case 2:{
                    for (int j=0; j<items[MainItem->EnabledItems[i]]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line.operator=(items[MainItem->EnabledItems[i]]->Butt->Frame2[j]->text());
                        //Line+="\"";
                        std::vector<QString> op;
                        QString temp="";
                        for (int q=0; q<Line.length(); q++){
                            QChar t;
                            t=Line[q];
                            if (t=='"'){
                                temp+=t;
                                q++;
                                for (; q<Line.size(); q++){
                                    t=Line[q];
                                    if (t=='"'){
                                        //op.push_back(temp);
                                        q++;
                                        goto Uiq;
                                    }
                                    temp+=t;
                                }
                            }
                            Uiq:{}
                            if (t=='+' || t=='-' || t=='*' || t=='/' || t=='^' || t=='(' || t==')' || t=='='){
                                op.push_back(temp);
                                temp="";
                                op.push_back(t);
                            }else
                                temp+=t;
                            //Uiq:{}
                        }
                        if (temp!=""){
                            op.push_back(temp);
                        }
                        QString Code;
                        for (int q=0; q<op.size(); q++){
                            Code+=op[q];
                        }
                        if (op.size()>2){
                            Code+=";";
                            CodeLine.push_back(Code);
                        }
                        for (int q=0; q<op.size(); q+=2){
                            if (!(op[q][0]=='"' && op[q][op[q].length()-1]=='"')){
                                int w=1;
                                for (int wq=0; wq<op[q].length(); wq++){
                                    if (!(op[q][wq]>='0' && op[q][wq]<='9')){
                                        if (op[q][wq]=='.' && w==1){
                                            w=2;
                                        }else
                                            w=0;
                                        break;
                                    }
                                }
                                /*if (w==0){
                                    LineVariables
                                }*/
                            }
                        }
                    }           
                }
                default:{
                    break;
                }
            }
        }
        for (int i=0; i<LineVariables.size(); i++){
            std::vector<QString>::iterator it=CodeLine.begin()+3;
            CodeLine.insert(it, "");
            CodeLine[3]+=TypeCPlusPlus(LineVariables[i].second)+" "+LineVariables[i].first+";";
        }
        for (int i=0; i<CodeLine.size(); i++){
            CodeLineL.push_back(new QLabel(this));
            CodeLineL[i]->setText(CodeLine[i]);
            CodeLineL[i]->move(800, 150+i*25);
            CodeLineL[i]->show();
            CodeLineL[i]->resize(500, 20);
        }
    }else{
        for (int i=0; i<MainItem->EnabledItems.size(); i++){
            switch (libA[items[MainItem->EnabledItems[i]]->Type]) {
                case 0:{
                    CodeLine.push_back("Begin");
                    break;
                }
                case 1:{
                    CodeLine.push_back("end.");
                    break;
                }
                case 3:{
                    for (int j=0; j<items[MainItem->EnabledItems[i]]->Butt->Frame2.size(); j++){
                        QString Line;
                        Line.operator=(items[MainItem->EnabledItems[i]]->Butt->Frame2[j]->text());
                        if (Line.length()!=0){
                            Line+"\"";
                            std::vector <QString> op;
                            QString temp;
                            for (int q=0; q<Line.size(); q++){
                                QChar t;
                                t=Line[q];
                                if (temp.length()==0 && t=='"'){
                                    temp+="\'";
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
                                    temp+='\'';
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
                            if (temp.size()!=0){
                                op.push_back(temp);
                                temp="";
                            }
                            for (int q=0; q<op.size(); q++){
                                if (op[q][0]=='\'' && op[q][op[q].size()-1]=='\''){

                                }else{
                                    bool w=1;
                                    for (int yy=0; yy<op[q].length(); yy++){
                                        if (!(op[q][yy]>='0' && op[q][yy]<='9')){
                                            w=0;
                                            break;
                                        }
                                    }
                                    if (!w){
                                        int u=0;
                                        for (; u<LineVariables.size(); u++){
                                            if (op[q]==LineVariables[u].first){
                                                break;
                                            }
                                        }
                                        if (u==LineVariables.size()){
                                            std::pair <QString, QString> ttt;
                                            ttt.first=op[q];
                                            ttt.second="variable is not looking";
                                            LineVariables.push_back(ttt);
                                        }
                                    }
                                }
                            }
                            if (j>0){
                                CodeLine.push_back("writeln()");
                            }
                            CodeLine.push_back("write(");
                            for (int q=0; q<op.size(); q++){
                                if (q!=0)
                                    CodeLine[CodeLine.size()-1]+=", "+op[q];
                                else {
                                    CodeLine[CodeLine.size()-1]+=op[q];
                                }
                            }
                            CodeLine[CodeLine.size()-1]+=");";
                            if (op.size()==0){
                                CodeLine.erase(CodeLine.end());
                            }
                        }else{
                            CodeLine.push_back("writeln();");
                        }
                    }
                    break;
                }
                case 4:{ //IN
            for (int j=0; j<items[MainItem->EnabledItems[i]]->Butt->Frame2.size(); j++){
                QString Line;
                Line.operator=(items[MainItem->EnabledItems[i]]->Butt->Frame2[j]->text());
                if (Line.length()!=0){
                    Line+"\'";
                    std::vector <QString> op;
                    QString temp;
                    for (int q=0; q<Line.size(); q++){
                        QChar t;
                        t=Line[q];
                        if (temp.length()==0 && t=='"'){
                            temp+='\'';
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
                            temp+='\'';
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
                    if (temp.size()!=0){
                        op.push_back(temp);
                        temp="";
                    }
                    for (int q=0; q<op.size(); q++){
                        if (op[q][0]=='\'' && op[q][op[q].size()-1]=='\''){

                        }else{
                            bool w=1;
                            for (int yy=0; yy<op[q].length(); yy++){
                                if (!(op[q][yy]>='0' && op[q][yy]<='9')){
                                    w=0;
                                    break;
                                }
                            }
                            if (!w){
                                int u=0;
                                for (; u<LineVariables.size(); u++){
                                    if (op[q]==LineVariables[u].first){
                                        break;
                                    }
                                }
                                if (u==LineVariables.size()){
                                    std::pair <QString, QString> ttt;
                                    ttt.first=op[q];
                                    if (items[MainItem->EnabledItems[i]]->Butt->Frame1[j]->currentIndex()==0)
                                        ttt.second="0";
                                    if (items[MainItem->EnabledItems[i]]->Butt->Frame1[j]->currentIndex()==1)
                                        ttt.second="0.0";
                                    if (items[MainItem->EnabledItems[i]]->Butt->Frame1[j]->currentIndex()==2)
                                        ttt.second="StartingString";
                                    LineVariables.push_back(ttt);
                                }
                            }
                        }
                    }
                    CodeLine.push_back("read(");
                    for (int q=0; q<op.size(); q++){
                        if (q!=0)
                            CodeLine[CodeLine.size()-1]+=", "+op[q];
                        else {
                            CodeLine[CodeLine.size()-1]+=op[q];
                        }
                    }
                    CodeLine[CodeLine.size()-1]+=");";
                    if (op.size()==0){
                        CodeLine.erase(CodeLine.end());
                    }
                }
            }
            break;
            }
                default:{
                    break;
                }
            }
        }
        std::vector<QString>::iterator it1=CodeLine.begin();
        if (LineVariables.size()!=0)
            CodeLine.insert(it1, "Var");
        for (int i=0; i<LineVariables.size(); i++){
            std::vector<QString>::iterator it=CodeLine.begin()+1;
            CodeLine.insert(it, "");
            CodeLine[1]+=LineVariables[i].first+" : "+TypePas(LineVariables[i].second)+";";
        }
        for (int i=0; i<CodeLine.size(); i++){
            CodeLineL.push_back(new QLabel(this));
            CodeLineL[i]->setText(CodeLine[i]);
            CodeLineL[i]->move(800, 150+i*25);
            CodeLineL[i]->show();
            CodeLineL[i]->resize(500, 20);
        }
    }
}

void MainWindow::PushButton(){
    CodeLine.clear();
    for (int i=0; i<CodeLineL.size(); i++){
        CodeLineL[i]->destroyed();
        CodeLineL[i]->hide();
        CodeLineL[i]->~QLabel();
    }
    CodeLineL.clear();
    LineVariables.clear();
    Translate(items[0]);
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
            DrawWindow(p, i->GetLeftAndTop().first,
                       i->GetLeftAndTop().second,
                       i->GetLeftAndTop().first+i->GetWidthAndHeight().first,
                       i->GetLeftAndTop().second+i->GetWidthAndHeight().second,
                       i->GetWidthAndHeight().second);
            goto Op;
        }
        p->setPen(QPen(Qt::black, 1, Qt::SolidLine));

        if (i->Butt->IsActivate){
            p->setPen(QPen(Qt::red, 2, Qt::SolidLine));
            for (int q=0; q<4; q++){
                p->drawLine(i->Butt->FrameLineInstructions[q].x1, i->Butt->FrameLineInstructions[q].y1,
                            i->Butt->FrameLineInstructions[q].x2, i->Butt->FrameLineInstructions[q].y2);
            }
            p->fillRect(i->Butt->FrameLineInstructions[0].x1,
                        i->Butt->FrameLineInstructions[0].y1,
                        i->Butt->FrameLineInstructions[0].x2-i->Butt->FrameLineInstructions[0].x1,
                        i->Butt->FrameLineInstructions[3].y2-i->Butt->FrameLineInstructions[0].y1, QBrush(Qt::white, Qt::SolidPattern));
            p->setPen(QPen(Qt::red, 1, Qt::SolidLine));
            if (i->Type=="Arithmetic")
                p->fillRect(i->lineInstructions[0].x1+i->GetLeftAndTop().first+2,
                            i->lineInstructions[0].y1+i->GetLeftAndTop().second+2,
                            i->lineInstructions[0].x2-i->lineInstructions[0].x1-2,
                            i->lineInstructions[3].y2-i->lineInstructions[0].y1-2, QBrush(Qt::white, Qt::SolidPattern));
            else if (i->Type=="If"){
                QPolygon poligon;
                //p->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                p->setPen(Qt::NoPen);
                poligon << QPoint(i->GetLeftAndTop().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second/2) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/2, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second/2);
                p->drawPolygon(poligon);
                QPolygon poligon1;
                //p->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                //p->setPen(Qt::NoPen);
                poligon1 << QPoint(i->GetLeftAndTop().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second/2) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/2, i->GetLeftAndTop().second+i->GetWidthAndHeight().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second/2);
                p->drawPolygon(poligon1);
                p->setPen(QPen(Qt::red, 1, Qt::SolidLine));
               // p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
            }else{
                QPolygon poligon;
                //p->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                p->setPen(Qt::NoPen);
                poligon << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first-i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second+i->GetWidthAndHeight().second) << QPoint(i->GetLeftAndTop().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second);
                p->drawPolygon(poligon);
                QPolygon poligon1;
                //p->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                //p->setPen(Qt::NoPen);
                poligon1 << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first-i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second+i->GetWidthAndHeight().second);
                p->drawPolygon(poligon1);
                p->setPen(QPen(Qt::red, 1, Qt::SolidLine));
            }
            for (int j=0; j<i->lineInstructions.size(); j++){
                p->drawLine(i->lineInstructions[j].x1+i->GetLeftAndTop().first, i->lineInstructions[j].y1+i->GetLeftAndTop().second,
                            i->lineInstructions[j].x2+i->GetLeftAndTop().first, i->lineInstructions[j].y2+i->GetLeftAndTop().second);
            }

        }else{
            p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
            if (i->Type=="Arithmetic")
                p->fillRect(i->lineInstructions[0].x1+i->GetLeftAndTop().first+2,
                            i->lineInstructions[0].y1+i->GetLeftAndTop().second+2,
                            i->lineInstructions[0].x2-i->lineInstructions[0].x1-2,
                            i->lineInstructions[3].y2-i->lineInstructions[0].y1-2, QBrush(Qt::white, Qt::SolidPattern));
            else if (i->Type=="If"){
                QPolygon poligon;
                //p->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                p->setPen(Qt::NoPen);
                poligon << QPoint(i->GetLeftAndTop().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second/2) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/2, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second/2);
                p->drawPolygon(poligon);
                QPolygon poligon1;
                //p->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                //p->setPen(Qt::NoPen);
                poligon1 << QPoint(i->GetLeftAndTop().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second/2) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/2, i->GetLeftAndTop().second+i->GetWidthAndHeight().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second/2);
                p->drawPolygon(poligon1);
                p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
               // p->setBrush(QBrush(Qt::white, Qt::SolidPattern));
            }else{
                QPolygon poligon;
                //p->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                p->setPen(Qt::NoPen);
                poligon << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first-i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second+i->GetWidthAndHeight().second) << QPoint(i->GetLeftAndTop().first, i->GetLeftAndTop().second+i->GetWidthAndHeight().second);
                p->drawPolygon(poligon);
                QPolygon poligon1;
                //p->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                //p->setPen(Qt::NoPen);
                poligon1 << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second) << QPoint(i->GetLeftAndTop().first+i->GetWidthAndHeight().first-i->GetWidthAndHeight().first/7.5, i->GetLeftAndTop().second+i->GetWidthAndHeight().second);
                p->drawPolygon(poligon1);
                p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
            }
            for (int j=0; j<i->lineInstructions.size(); j++){
            p->drawLine(i->lineInstructions[j].x1+i->GetLeftAndTop().first, i->lineInstructions[j].y1+i->GetLeftAndTop().second,
                            i->lineInstructions[j].x2+i->GetLeftAndTop().first, i->lineInstructions[j].y2+i->GetLeftAndTop().second);
            }

        }
        p->setPen(QPen(Qt::black, 1, Qt::SolidLine));        
    }
    else{ //ARRAY_WORK
        p->setPen(QPen(Qt::red, 1, Qt::SolidLine));
        for (int j=0; j<i->lineInstructions.size(); j++){
            p->drawLine(i->lineInstructions[j].x1+i->GetLeftAndTop().first, i->lineInstructions[j].y1+i->GetLeftAndTop().second,
                            i->lineInstructions[j].x2+i->GetLeftAndTop().first, i->lineInstructions[j].y2+i->GetLeftAndTop().second);
        }
        p->fillRect(i->lineInstructions[0].x1+i->GetLeftAndTop().first+2,
                    i->lineInstructions[0].y1+i->GetLeftAndTop().second+2,
                    i->lineInstructions[0].x2-i->lineInstructions[0].x1-2,
                    i->lineInstructions[3].y2-i->lineInstructions[0].y1-2, QBrush(Qt::white, Qt::SolidPattern));
    }
    Op:{}
}

void MainWindow::paintEvent(QPaintEvent *event){
    //ui->label->setText("Paint");
    QPainter p(this);
    int _BrushSize = 1;
    p.setPen(QPen(Qt::black, _BrushSize, Qt::SolidLine));
    p.setBrush(QBrush(QColor("#DCDCDC"), Qt::SolidPattern));
    DrawWindow(&p, 5, 45, 145, 675, 50);
    p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    //DrawWindow(&p, 10, 10, 100, 60, 25);
    for (int i=0; i<this->items.size(); i++){
        DrawBlock(&(p), (items[i]));
    }
    for (int i=0; i<items.size(); i++){
        if (items[i]->NekstItem!=nullptr){
            p.drawLine(items[i]->GetLeftAndTop().first+items[i]->GetWidthAndHeight().first/2,
                       items[i]->GetLeftAndTop().second+items[i]->GetWidthAndHeight().second,
                       items[i]->NekstItem->GetLeftAndTop().first+items[i]->NekstItem->GetWidthAndHeight().first/2,
                       items[i]->NekstItem->GetLeftAndTop().second);

        }
    }
    //p.fillRect(10, 10, 100, 100, QBrush(Qt::white, Qt::SolidPattern));
}

void MainWindow::FollowMouse(){
    this->ChoosingItem->move(DeltaX*(-1), DeltaY*(-1));
    for (int i=0; i<ChoosingItem->EnabledItems.size(); i++){
        items[ChoosingItem->EnabledItems[i]]->move(DeltaX*(-1), DeltaY*(-1));
    }
    DeltaX=(QCursor::pos().x()-this->FirstMousePositions.x());
    DeltaY=QCursor::pos().y()-this->FirstMousePositions.y();
    this->ChoosingItem->move(DeltaX, DeltaY);
    for (int i=0; i<ChoosingItem->EnabledItems.size(); i++){
        items[ChoosingItem->EnabledItems[i]]->move(DeltaX, DeltaY);
    }
    this->repaint();
}

void MainWindow::TimerEvent(){
    /*for (int i=items.size()-1; i>=0; i--){
        if (items[i]->Butt->Activate){
            items[i]->Butt->Activate=0;
            items[i]->Butt->IsActivate=0;
            //ChoosingItem=nullptr;
            break;
        }
    }*/
    this->Timer1->start(10);
    //QMessageBox::critical(this, QString::number(1), "");
}

void MainWindow::mouseReleaseEvent( QMouseEvent * event ){
    this->ui->label->setText("Release");
    //std::sleep(5000);
    StopMove();
}

void MainWindow::StopMove(){
    if (ChoosingItem!=nullptr){
        //if (!(ChoosingItem->Butt->Activate) && Choose){
            if (libA[ChoosingItem->Type]!=5){
                int qq=this->KolLayout-1;

                for (qq; qq>=0; qq--){
                        if (QCursor::pos().x()-this->geometry().left() > items[qq]->GetLeftAndTop().first &&
                            QCursor::pos().x()-this->geometry().left() < items[qq]->GetLeftAndTop().first + items[qq]->GetWidthAndHeight().first &&
                            QCursor::pos().y()-this->geometry().top() > items[qq]->GetLeftAndTop().second &&
                            QCursor::pos().y()-this->geometry().top() < items[qq]->GetLeftAndTop().second + items[qq]->GetWidthAndHeight().second)
                        {
                            break;
                        }
                    } 
                if (qq!=-1)
                {
                    if (ChoosingItem->Layout==nullptr){
                        NewBlock(ChoosingItem->Type);
                    }
                    ChoosingItem->Layout=items[qq];
                    std::vector <int>::iterator it=GetPos(ChoosingItem, items[qq]);
                    items[qq]->EnabledItems.insert(it, ChoosingItem->position);
                    it=items[qq]->EnabledItems.begin();
                    int i=0;
                    for (; i<items[qq]->EnabledItems.size(); i++){
                        if (ChoosingItem==items[items[qq]->EnabledItems[i]]){
                            break;
                        }
                    }
                    if (i>0){
                        items[items[qq]->EnabledItems[i-1]]->NekstItem=ChoosingItem;
                    }
                    if (i<items[qq]->EnabledItems.size()-1){
                        ChoosingItem->NekstItem=items[items[qq]->EnabledItems[i+1]];
                    }
                    /* if (it!=items[qq]->EnabledItems.begin()){
                        items[*items[qq]->EnabledItems.begin()]->NekstItem=items[*it];
                        //items[*it2]->NekstItem=items[*it];
                    }
                    /*it2++;

                    it2++;
                    if (it2!=items[qq]->EnabledItems.end()){
                        items[*it]->NekstItem=items[*it2];
                    }*/
                    //ChoosingItem->Layout=items[qq];
                }else{
                    if (ChoosingItem->Layout==nullptr){
                        NewBlock(ChoosingItem->Type);
                    }else{
                        int q=0;
                        while (ChoosingItem->position!=ChoosingItem->Layout->EnabledItems[q]){
                            q++;
                        }
                        int y=0;
                        while (y<ChoosingItem->Layout->EnabledItems.size()){
                            if (ChoosingItem->position<ChoosingItem->Layout->EnabledItems[y]){
                                ChoosingItem->Layout->EnabledItems[y]--;
                            }
                            y++;
                        }
                            if (q<ChoosingItem->Layout->EnabledItems.size()){
                            std::vector <int> ::iterator it = ChoosingItem->Layout->EnabledItems.begin()+q;
                            if (q!=0){
                                if (q!=ChoosingItem->Layout->EnabledItems.size()-1){
                                    items[ChoosingItem->Layout->EnabledItems[q-1]]->NekstItem=items[ChoosingItem->Layout->EnabledItems[q+1]];
                                }else{
                                    items[ChoosingItem->Layout->EnabledItems[q-1]]->NekstItem=nullptr;
                                }
                            }
                            ChoosingItem->NekstItem=nullptr;
                            ChoosingItem->Layout->EnabledItems.erase(it);
                        }
                    }
                    std::vector <item*> ::iterator it1 = items.begin()+ChoosingItem->position;
                    items.erase(it1);
                    for (int i=ChoosingItem->position; i<items.size(); i++){
                        items[i]->position--;
                    }        
                    ChoosingItem->~item();
                    ChoosingItem=nullptr;
                }
                this->repaint();
                ReconstructItem0();
            }
            DeltaX=0; DeltaY=0;
            this->Timer1->stop();
            ChoosingItem=nullptr;
        //}
   }
    this->Timer1->stop();
}

void MainWindow::mousePressEvent( QMouseEvent * event ){
    this->ui->label->setText("Press");
    /*if (this->Timer1->isActive()){
        this->StopMove();
    }*/
    //if (ChoosingItem!=nullptr)
    //QMessageBox::critical(this, QString::number(items.size()-1), "");
    //Choose=0;
    bool o=1;

    for (int i=items.size()-1; i>=KolLayout; i--){
        if (items[i]->Butt->IsActivate){
            if (!((items[i]->Butt->LeftFrame                                              <   QCursor::pos().x()-this->geometry().left()) &&
                (items[i]->Butt->LeftFrame +items[i]->Butt->WidthFrame                  >   QCursor::pos().x()-this->geometry().left()) &&
                (items[i]->Butt->TopFrame                                               <   QCursor::pos().y()-this->geometry().top()) &&
                (items[i]->Butt->TopFrame+items[i]->Butt->HeigthFrame                   >   QCursor::pos().y()-this->geometry().top()))){
                if (!((items[i]->Butt->GLeft()                              < QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->Butt->GLeft()+items[i]->Butt->GWidth()     > QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->Butt->GTop()                               < QCursor::pos().y()-this->geometry().top()) &&
                    (items[i]->Butt->GTop()+items[i]->Butt->GHeigth()     > QCursor::pos().y()-this->geometry().top())))
                {
                    items[i]->Butt->Activate();
                    ChoosingItem=nullptr;
                    break;
                }else{
                    o=0;
                    break;
                }
            }else{
                o=0;
                break;
            }
        }
    }
    if (o){
        for (int i=items.size()-1; i>=KolLayout; i--){
            if (
                items[i]->GetLeftAndTop().first                                              <   QCursor::pos().x()-this->geometry().left() &&
                items[i]->GetLeftAndTop().first+this->items[i]->GetWidthAndHeight().first     >   QCursor::pos().x()-this->geometry().left() &&
                items[i]->GetLeftAndTop().second                                             <   QCursor::pos().y()-this->geometry().top() &&
                items[i]->GetLeftAndTop().second+this->items[i]->GetWidthAndHeight().second   >   QCursor::pos().y()-this->geometry().top())
            {
                    ChoosingItem=(items[i]);

                    if ((i>=KolLayout) && (ChoosingItem->Butt->GLeft()            < QCursor::pos().x()-this->geometry().left()) &&
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
                            while (ChoosingItem->position!=ChoosingItem->Layout->EnabledItems[q]){
                                q++;
                            }
                            std::vector <int> ::iterator it = ChoosingItem->Layout->EnabledItems.begin()+q;
                            if (q!=0){
                                if (q!=ChoosingItem->Layout->EnabledItems.size()-1){
                                    items[ChoosingItem->Layout->EnabledItems[q-1]]->NekstItem=items[ChoosingItem->Layout->EnabledItems[q+1]];
                                }else{
                                    items[ChoosingItem->Layout->EnabledItems[q-1]]->NekstItem=nullptr;
                                }
                            }
                            ChoosingItem->NekstItem=nullptr;
                            ChoosingItem->Layout->EnabledItems.erase(it);
                            ui->label->setText(QString::number(ChoosingItem->Layout->EnabledItems.size()));
                        }
                        //QMessageBox::critical(this, QString::number(i), "");
                        ReconstructItem0();
                        //QMessageBox::critical(this, QString::number(i), "");
                        this->FirstMousePositions.setX(QCursor::pos().x());
                        this->FirstMousePositions.setY(QCursor::pos().y());
                        this->TimerEvent();
                        this->moveEvent=true;
                    }
                    break;
                }
            }
    //    }
    }/*else{
        StopMove();
    }*/
    repaint();
}

std::vector<int>::iterator MainWindow::GetPos(item* Item, item* Layout){
        int h;
        if (Layout->EnabledItems.size()>0){
            int q;
            for (q=0; q<Layout->EnabledItems.size() && Item->GetLeftAndTop().second>items[Layout->EnabledItems[q]]->GetLeftAndTop().second; q++){

            }
            std::vector<int>::iterator it = Layout->EnabledItems.begin()+q;
            return it;
        }else{
            std::vector<int>::iterator it = Layout->EnabledItems.begin();
            return it;
        }

}

void MainWindow::ReconstructItem0(){
    for (int j=0; j<KolLayout; j++){
            int PointY=this->items[j]->GetLeftAndTop().second+50;
            for (int i=0; i<items[j]->EnabledItems.size(); i++){
                if (items[items[j]->EnabledItems[i]]->Type!="ArrayWork"){
                    //QMessageBox::critical(this, "1", "");
                    items[items[j]->EnabledItems[i]]->setGeometry(items[items[j]->EnabledItems[i]]->GetWidthAndHeight().first, items[items[j]->EnabledItems[i]]->GetWidthAndHeight().second ,
                        items[j]->GetLeftAndTop().first+(items[j]->GetWidthAndHeight().first - items[items[j]->EnabledItems[i]]->GetWidthAndHeight().first)/2, PointY);
                }else{
                    items[items[j]->EnabledItems[i]]->setGeometry(items[items[j]->EnabledItems[i]]->GetWidthAndHeight().first, items[items[j]->EnabledItems[i]]->GetWidthAndHeight().second ,
                            items[j]->GetLeftAndTop().first+5, PointY);
                    j++;
                    items[items[j]->EnabledItems[i]]->setGeometry(items[items[j]->EnabledItems[i]]->GetWidthAndHeight().first, items[items[j]->EnabledItems[i]]->GetWidthAndHeight().second ,
                            items[j]->GetLeftAndTop().first/2+5, PointY);
                    //QMessageBox::critical(this, "2", "");
                }
                PointY+=items[items[j]->EnabledItems[i]]->GetWidthAndHeight().second+15;
            }
    }
    this->repaint();
}

void MainWindow::InButton(){
    for (int i=0; i<items.size(); i++)
        if (items[i]->Type=="In")
                if ((items[i]->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->Butt->Frame4[0]->geometry().left()  +items[i]->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                    (items[i]->Butt->Frame4[0]->geometry().top()  +items[i]->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                    //QMessageBox::critical(this, "", "");
                    if (items[i]->Butt->Frame2.size()==0 || items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->text()!=""){
                            items[i]->Butt->Frame2.push_back(new QLineEdit(this));
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->show();
                            items[i]->Butt->Frame1.push_back(new QComboBox(this));
                            items[i]->Butt->Frame1[items[i]->Butt->Frame1.size()-1]->show();
                            items[i]->Butt->Frame1[items[i]->Butt->Frame1.size()-1]->addItem("Целочисленное");
                            items[i]->Butt->Frame1[items[i]->Butt->Frame1.size()-1]->addItem("Вещественное");
                            items[i]->Butt->Frame1[items[i]->Butt->Frame1.size()-1]->addItem("Текст");
                            items[i]->Butt->Frame1[items[i]->Butt->Frame1.size()-1]->move(items[i]->Butt->LeftFrame+10, items[i]->Butt->TopFrame+10+35*(items[i]->Butt->Frame1.size()-1));
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->move(items[i]->Butt->LeftFrame+112, items[i]->Butt->TopFrame+10+35*(items[i]->Butt->Frame2.size()-1));
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->resize(68, 25);
                            items[i]->Butt->Frame4[0]->move(items[i]->Butt->Frame4[0]->geometry().left(), items[i]->Butt->Frame4[0]->geometry().top()+35);
                            items[i]->Butt->HeigthFrame+=35;
                            items[i]->Butt->FrameCorrect();
                            repaint();
                    }
            }
            goto Y;
    Y:{}
}

void MainWindow::OutButton(){
    for (int i=0; i<items.size(); i++)
        if (items[i]->Type=="Out")
                if ((items[i]->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->Butt->Frame4[0]->geometry().left()  +items[i]->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                    (items[i]->Butt->Frame4[0]->geometry().top()  +items[i]->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                    //QMessageBox::critical(this, "", "");
                            items[i]->Butt->Frame2.push_back(new QLineEdit(this));
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->show();
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->move(items[i]->Butt->LeftFrame+10, items[i]->Butt->TopFrame+10+35*(items[i]->Butt->Frame2.size()-1));
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->resize(170, 25);
                            items[i]->Butt->Frame4[0]->move(items[i]->Butt->Frame4[0]->geometry().left(), items[i]->Butt->Frame4[0]->geometry().top()+35);
                            items[i]->Butt->HeigthFrame+=35;
                            items[i]->Butt->FrameCorrect();
                            repaint();
            }
            goto Y;
    Y:{}
}

void MainWindow::ArithmeticButton(){
    for (int i=0; i<items.size(); i++)
        if (items[i]->Type=="Arithmetic")
                if ((items[i]->Butt->Frame4[0]->geometry().left()                                                                   <   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->Butt->Frame4[0]->geometry().left()  +items[i]->Butt->Frame4[0]->geometry().width()                   >   QCursor::pos().x()-this->geometry().left()) &&
                    (items[i]->Butt->Frame4[0]->geometry().top()                                                                    <   QCursor::pos().y()-this->geometry().top()) &&
                    (items[i]->Butt->Frame4[0]->geometry().top()  +items[i]->Butt->Frame4[0]->geometry().height()                   >   QCursor::pos().y()-this->geometry().top())){
                    //QMessageBox::critical(this, "", "");
                            items[i]->Butt->Frame2.push_back(new QLineEdit(this));
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->show();
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->move(items[i]->Butt->LeftFrame+10, items[i]->Butt->TopFrame+10+35*(items[i]->Butt->Frame2.size()-1));
                            items[i]->Butt->Frame2[items[i]->Butt->Frame2.size()-1]->resize(170, 25);
                            items[i]->Butt->Frame4[0]->move(items[i]->Butt->Frame4[0]->geometry().left(), items[i]->Butt->Frame4[0]->geometry().top()+35);
                            items[i]->Butt->HeigthFrame+=35;
                            items[i]->Butt->FrameCorrect();
                            repaint();
            }
            goto Y;
    Y:{}
}
