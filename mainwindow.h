#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <set>
#include <QComboBox>
#include <QMessageBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QPainter>
#include <bits/stdc++.h>
#include <QTextEdit>
/*std::map <std::string, int> libB = {{"Begin", 0},
                                    {"End", 1},
                                    {"In", 2},
                                    {"Out", 3},
                                    {"ArrayWork", 4}};
*/

namespace Ui {
class MainWindow;
}

class PointToPoint{
public:
    int x1, x2, y1, y2;
    PointToPoint(int x1, int y1, int x2, int y2){
        this->x1=x1;
        this->x2=x2;
        this->y1=y1;
        this->y2=y2;
    }
};

class ButtonClose{
public:
    ButtonClose (int Left, int Width, int Top, int Heigth){
        this->Left=Left;
        this->Width=Width;
        this->Top=Top;
        this->Heigth=Heigth;
    }
    int Left, Top, Width, Heigth;
};

class item;

struct Variable{
    QString name, type;
};

class LilButton{
public:
    LilButton(int left, int top, int width, int height, QWidget* parent, int Type, std::string landg){
        this->Type=Type;
        land=landg;
        Mi = parent;
        WidthFrame=210*parent->width()/1050;
        HeigthFrame=125*parent->height()/820;
        LeftFrame=left+width;
        TopFrame=top;
        Text="...";
        Width=13*parent->width()/1050;
        Heigth=10*parent->height()/820;
        if (Type==1 || Type==2 || Type==5 || Type==6)
            width-=width/7.5;
        Left=left+width-Width;
        Top=top+height-Heigth-3*Mi->height()/820;
        Lb = new QLabel(parent);
        Lb->setText(Text);
        Lb->setGeometry(this->Left, this->Top, Width, Heigth);
        Lb->setAlignment(Qt::AlignCenter);
        Lb->setStyleSheet("color : black;");
        Lb->show();
        if (Type==2){
            Frame4.push_back(new QPushButton(parent));
            //Frame4[0]->setEnabled(0);
            Frame4[0]->resize(150*parent->width()/1050, 25*parent->height()/820);
            WidthFrame=210*parent->width()/1050;
            HeigthFrame=45*parent->height()/820;
            if (land!="Eng")
                Frame4[0]->setText("+Добавить");
            else{
                Frame4[0]->setText("+Add");
            }
            Frame4[0]->move(LeftFrame+WidthFrame/2-75*parent->width()/1050, TopFrame+10*parent->height()/820);
            parent->connect(Frame4[0], SIGNAL(clicked()), parent, SLOT(InButton()));
        }if (Type==5){
            Frame4.push_back(new QPushButton(parent));
            //Frame4[0]->setEnabled(0);
            Frame4[0]->resize(150*parent->width()/1050, 25*parent->height()/820);
            WidthFrame=210*parent->width()/1050;
            HeigthFrame=45*parent->height()/820;
            if (land!="Eng")
                Frame4[0]->setText("+Добавить");
            else{
                Frame4[0]->setText("+Add");
            }
            Frame4[0]->move(LeftFrame+WidthFrame/2-75*parent->width()/1050, TopFrame+10*parent->height()/820);
            parent->connect(Frame4[0], SIGNAL(clicked()), parent, SLOT(InButton()));
        }else if (Type==1){
            Frame4.push_back(new QPushButton(parent));
            //Frame4[0]->setEnabled(0);
            Frame4[0]->resize(150*parent->width()/1050, 25*parent->height()/820);
            WidthFrame=210*parent->width()/1050;
            HeigthFrame=45*parent->height()/820;
            if (land!="Eng")
                Frame4[0]->setText("+Добавить");
            else{
                Frame4[0]->setText("+Add");
            }
            Frame4[0]->move(LeftFrame+WidthFrame/2-75*parent->width()/1050, TopFrame+10*parent->height()/820);
            parent->connect(Frame4[0], SIGNAL(clicked()), parent, SLOT(OutButton()));
        }else if (Type==3){
            Frame4.push_back(new QPushButton(parent));
            //Frame4[0]->setEnabled(0);
            Frame4[0]->resize(150*parent->width()/1050, 25*parent->height()/820);
            WidthFrame=210*parent->width()/1050;
            HeigthFrame=45*parent->width()/1050;
            if (land!="Eng")
                Frame4[0]->setText("+Добавить");
            else{
                Frame4[0]->setText("+Add");
            }
            Frame4[0]->move(LeftFrame+WidthFrame/2-75*parent->width()/1050, TopFrame+10*parent->height()/820);
            parent->connect(Frame4[0], SIGNAL(clicked()), parent, SLOT(ArithmeticButton()));
        }else if (Type==4){
            Frame4.push_back(new QPushButton(parent));
            Frame4[0]->resize(150*parent->width()/1050, 20*parent->height()/820);
            WidthFrame=210*parent->width()/1050;
            HeigthFrame=60*parent->height()/820;
            if (land!="Eng")
                Frame4[0]->setText("Применить новое имя");
            else{
                Frame4[0]->setText("Apply the new name");
            }
            Frame4[0]->move(LeftFrame+WidthFrame/2-75*parent->width()/1050, TopFrame+35*parent->height()/820);
            parent->connect(Frame4[0], SIGNAL(clicked()), parent, SLOT(OutButton()));
            Frame2.push_back(new QLineEdit(parent));
            Frame2[0]->resize(150*parent->width()/1050, 25*parent->height()/820);
            Frame2[0]->move(LeftFrame+WidthFrame/2-75*parent->width()/1050, TopFrame+10*parent->height()/820);
        }
        for (int i=0; i<Frame1.size(); i++){
            Frame1[i]->hide();
        }
        for (int i=0; i<Frame2.size(); i++){
            Frame2[i]->hide();
        }
        //for (int i=0; i<Frame3.size(); i++){
        //    Frame3[i]->hide();
        //}
        for (int i=0; i<Frame4.size(); i++){
            Frame4[i]->hide();
        }
        for (int i=0; i<Frame5.size(); i++){
            Frame5[i]->hide();
        }
        FrameCorrect();
    }
    void setFont(QFont f){
        Lb->setFont(f);
    }
    void Activate(){
        IsActivate=!IsActivate;
        if (!IsActivate){
            for (int i=0; i<Frame1.size(); i++){
                Frame1[i]->hide();
            }
            for (int i=0; i<Frame2.size(); i++){
                Frame2[i]->hide();
            }
            //for (int i=0; i<Frame3.size(); i++){
            //    Frame3[i]->hide();
            //}
            for (int i=0; i<Frame4.size(); i++){
                Frame4[i]->hide();
            }
            for (int i=0; i<Frame5.size(); i++){
                Frame5[i]->hide();
            }
        }else{
            for (int i=0; i<Frame1.size(); i++){
                Frame1[i]->show();
            }
            for (int i=0; i<Frame2.size(); i++){
                Frame2[i]->show();
            }
            //for (int i=0; i<Frame3.size(); i++){
            //    Frame3[i]->show();
            //}
            for (int i=0; i<Frame4.size(); i++){
                Frame4[i]->show();
            }
            for (int i=0; i<Frame5.size(); i++){
                Frame5[i]->show();
            }
        }
    }
    void FrameCorrect(){
        FrameLineInstructions.clear();
        FrameLineInstructions.reserve(4);
        FrameLineInstructions.push_back(PointToPoint(LeftFrame, TopFrame, LeftFrame+WidthFrame, TopFrame));
        FrameLineInstructions.push_back(PointToPoint(LeftFrame, TopFrame, LeftFrame, TopFrame+HeigthFrame));
        FrameLineInstructions.push_back(PointToPoint(LeftFrame, TopFrame+HeigthFrame, LeftFrame+WidthFrame, TopFrame+HeigthFrame));
        FrameLineInstructions.push_back(PointToPoint(LeftFrame+WidthFrame, TopFrame, LeftFrame+WidthFrame, TopFrame+HeigthFrame));
    }
    void SetGeometry(int left, int top, int width, int height){ //w(1-1/7.5)=width
        WidthFrame=210;
        HeigthFrame=125*Mi->height()/820;
        LeftFrame=left+width;
        TopFrame=top;
        Text="...";
        Width=18;
        Heigth=10*Mi->height()/820;
        if (Type==1)
            width-=width/7.5;
        Left=left+width-Lb->width()-5;
        Top=top+height;
        Lb->setGeometry(this->Left-40, this->Top-10*Mi->height()/820, Lb->width(), Lb->height());
        FrameCorrect();
    }
    void move(int x1, int y1){
        Lb->move(x1+Lb->geometry().left(), y1+Lb->geometry().top());
        TopFrame+=y1;
        LeftFrame+=x1;
        Top+=y1;
        Left+=x1;
        for (int i=0; i<Frame1.size(); i++){
            Frame1[i]->move(x1+Frame1[i]->geometry().left(), y1+Frame1[i]->geometry().top());
        }
        for (int i=0; i<Frame2.size(); i++){
            Frame2[i]->move(x1+Frame2[i]->geometry().left(), y1+Frame2[i]->geometry().top());
        }
        for (int i=0; i<Frame3.size(); i++){
            Frame3[i]->move(x1+Frame3[i]->geometry().left(), y1+Frame3[i]->geometry().top());
        }
        for (int i=0; i<Frame4.size(); i++){
            Frame4[i]->move(x1+Frame4[i]->geometry().left(), y1+Frame4[i]->geometry().top());
        }
        for (int i=0; i<Frame5.size(); i++){
            Frame5[i]->move(x1+Frame5[i]->geometry().left(), y1+Frame5[i]->geometry().top());
        }
        for (int i=0; i<Frame6.size(); i++){
            Frame6[i]->Left+=x1;
            Frame6[i]->Top+=y1;
        }
        FrameCorrect();
    }
    void Frame_Move(int x1, int y1){
        TopFrame+=y1;
        LeftFrame+=x1;
        FrameCorrect();
    }
    ~LilButton(){
        Lb->~QLabel();
        for (int i=0; i<Frame1.size(); i++){
            Frame1[i]->hide();
        }
        for (int i=0; i<Frame2.size(); i++){
            Frame2[i]->hide();
        }
        for (int i=0; i<Frame3.size(); i++){
            Frame3[i]->hide();
        }
        for (int i=0; i<Frame4.size(); i++){
            Frame4[i]->hide();
        }
        for (int i=0; i<Frame5.size(); i++){
            Frame5[i]->hide();
        }
        for (int i=Frame1.size()-1; i>=0; i--){
            Frame1[i]->~QComboBox();
        }
        for (int i=Frame2.size()-1; i>=0; i--){
            Frame2[i]->~QLineEdit();
        }
        for (int i=Frame3.size()-1; i>=0; i--){
            Frame3[i]->~QLabel();
        }
        for (int i=Frame4.size()-1; i>=0; i--){
            Frame4[i]->~QPushButton();
        }
        for (int i=Frame5.size()-1; i>=0; i--){
            Frame5[i]->~QCheckBox();
        }
        Frame1.clear();
        Frame2.clear();
        Frame3.clear();
        Frame4.clear();
        Frame5.clear();
    }
    int GLeft(){
        return Left;
    }
    int GTop(){
        return Top;
    }
    int GWidth(){
        return Width;
    }
    int GHeigth(){
        return Heigth;
    }
    void hide(bool q){
        if (q){
            Lb->hide();
        }else{
            Lb->show();
        }
    }
    bool IsActivate=0;
    std::vector <PointToPoint> FrameLineInstructions;
    std::vector <QComboBox *> Frame1;
    std::vector <QLineEdit *> Frame2;
    std::vector <QLabel *> Frame3;
    std::vector <QPushButton *> Frame4;
    std::vector <QCheckBox *> Frame5;
    std::vector <ButtonClose *> Frame6;
    std::string land;
    int HeigthFrame, WidthFrame, TopFrame, LeftFrame;
    friend item;
    QLabel* Lb=nullptr;
private:
    QString Text;
    //int top, width, left;
    int Heigth, Width, Top, Left;
    QWidget * Mi;
    int Type;
};

class item{
public:

    int MaxHeigth=70, ShowHeigth;
    item* Pa=nullptr;
    std::string land;
    int n=0;
    item(QString Type, QWidget* Mi, std::string la){
        Father=Mi;
        land=la;
        if (Type!="ArrayWork"){
            /*if (Type=="If"){

            }else{*/
                height=Mi->height()*40/820;
                width=75*Mi->width()/1050;
            //}
        }else{
            height=790;
            width=950;
        }
        top=0;
        left=0;
        if (Type=="If") ShowHeigth=130*Mi->height()/820;
        else if (Type=="While") ShowHeigth=145*Mi->height()/820;
        this->Type=Type;
        this->Type2=Type;
        if (Type!="ArrayWork"){

            if (Type=="Out"){
                Butt = new LilButton(left, top, width, height, Mi, 1, la);
            }else if (Type=="In"){
                Butt = new LilButton(left, top, width, height, Mi, 2, la);
            }else if (Type=="Arithmetic" || Type=="If" || Type=="While"){
                Butt = new LilButton(left, top, width, height, Mi, 3, la);
            }else if (Type=="Begin"){
                Butt = new LilButton(left, top, width, height, Mi, 5, la);
            }else if (Type=="End"){
                Butt = new LilButton(left, top, width, height, Mi, 6, la);
            }else{
                Butt = new LilButton(left, top, width, height, Mi, 4, la);
                this->Type="Pattern";
                Butt->Frame2[0]->setText(Type2);
                //Butt->Lb->setText("");
                //Butt->Lb->hide();
            }
        }else{
            Butt = new LilButton(left, top, 0, 0, Mi, 0, la);
            Butt->Lb->setText("");
            Butt->Lb->hide();
        }
        Butt->land=this->land;
    }
    ~item(){
        if (Label_Instructions.size()>0)
           Label_Instructions[0]->~QLabel();
        if (Butt!=nullptr)
            Butt->~LilButton();
        if (Layout!=nullptr){
            int i=0;
            for (; Layout->EnabledItems[i]!=this && i<Layout->EnabledItems.size(); i++);
            //Layout->EnabledItems[i]=nullptr;
            std::vector<item*>::iterator ite=Layout->EnabledItems.begin()+i;
            if (i!=Layout->EnabledItems.size())
            Layout->EnabledItems.erase(ite);
        }
        //delete this;
    }

    void UpdateLanuage(std::string lan){
        if (Type=="In"){
            if (lan=="Eng"){
                Butt->Frame4[0]->setText("+Add");
                for (int i=0; i<Butt->Frame5.size(); i++){
                    Butt->Frame5[i]->setText("input");
                    Butt->Frame1[i]->setItemText(0, "integer");
                    Butt->Frame1[i]->setItemText(1, "real");
                    Butt->Frame1[i]->setItemText(2, "text");
                    Butt->Frame5[i]->update();
                }
                Butt->Frame4[0]->update();
            }else{
                Butt->Frame4[0]->setText("+Добавить");
                for (int i=0; i<Butt->Frame5.size(); i++){
                    Butt->Frame5[i]->setText("Ввод");
                    Butt->Frame1[i]->setItemText(0, "Целочисленное");
                    Butt->Frame1[i]->setItemText(1, "Вещественное");
                    Butt->Frame1[i]->setItemText(2, "Текст");
                    Butt->Frame5[i]->update();
                }
                Butt->Frame4[0]->update();
            }
        }else if (Type=="Out" || Type=="Arithmetic"){
            if (lan=="Eng"){
                Butt->Frame4[0]->setText("+Add");
            }else{
                Butt->Frame4[0]->setText("+Добавить");
            }
            Butt->Frame4[0]->update();
        }else if (Type=="If" || Type=="While"){
            if (lan=="Eng"){
                if ("+Добавить"==Butt->Frame4[0]->text())
                    Butt->Frame4[0]->setText("+Add");
                if ("Показать/Скрыть"==Butt->Frame4[0]->text())
                    Butt->Frame4[0]->setText("Show/Hide");
            }else{
                if ("+Add"==Butt->Frame4[0]->text())
                    Butt->Frame4[0]->setText("+Добавить");
                if ("Show/Hide"==Butt->Frame4[0]->text())
                    Butt->Frame4[0]->setText("Показать/Скрыть");
            }
            Butt->Frame4[0]->update();
        }else if (Type=="Pattern"){
            if (land!="Eng")
                Butt->Frame4[0]->setText("Применить новое имя");
            else{
                Butt->Frame4[0]->setText("Apply the new name");
            }
            Butt->Frame4[0]->update();
        }
    }

    void move(int x1, int y1){
        this->left+=x1;
        this->top+=y1;
        /*for (int i=0; i<this->lineInstructions.size(); i++){
            lineInstructions[i].x1+=x1;
            lineInstructions[i].x2+=x1;
            lineInstructions[i].y1+=y1;
            lineInstructions[i].y2+=y1;
        }*/
        //if (libB[this->Type]<4)

        for (int i=0; i<this->Label_Instructions.size(); i++){
            this->Label_Instructions[i]->move(this->Label_Instructions[i]->geometry().left()+x1,
                                              this->Label_Instructions[i]->geometry().top()+y1);
        }
        for (int i=0; i<MyItems.size(); i++){

            MyItems[i]->move(x1, y1);
        }
        //if (Type!="ArrayWork")
        if (Butt!=nullptr)
            Butt->move(x1, y1);
        if (HelpLine.size()!=0){
            for (int i=0; i<HelpLine.size(); i++){
                QLine TLine(HelpLine[i].x1()+x1, HelpLine[i].y1()+y1, HelpLine[i].x2()+x1, HelpLine[i].y2()+y1);
                HelpLine[i]=TLine;
            }
        }
        if (Type=="ArrayWork"){
            for (int i=0; i<EnabledItems.size(); i++){
                EnabledItems[i]->move(x1, y1);
            }
        }
    }

    void SetTextOnLabel(QString Text){
        Label_Instructions[0]->setText(Text);
        //Label_Instructions[0]->repaint();
    }

    QString GetTextOnlabel(){
        return Label_Instructions[0]->text();
    }

    void resize(int width, int height){
        double kofX, kofY;
        kofX=(double)width/this->width;
        kofY=(double)height/this->height;
        this->width=(int)(this->width*kofX);
        this->height=(int)(this->height*kofY);

        //QMessageBox::critical(Father, QString::number(lineInstructions[0].x1), "");
        /*if (width>50 && height>10)
            Label_Instructions[0]->setGeometry(this->left+width/2-47, this->top+height/2-20, 30, 10);
        if (Type!="In" && Type!="Out")
            Butt->SetGeometry(this->left, this->top, this->width, this->height);
        else{
            Butt->SetGeometry(this->left, this->top, width-width/7.5, height);
        }*/
    }

    void setGeometry(int width, int height, int left, int top){
        this->move((-1)*this->left, (-1)*this->top);
        this->resize(width, height);
        this->move(left, top);
    }

    std::pair <int, int> GetLeftAndTop(){
        std::pair <int, int> LeftAndTop;
        LeftAndTop.first=this->left;
        LeftAndTop.second=this->top;
        return LeftAndTop;
    }

    QString GetType(){
        return Type;
    }

    std::pair <int, int> GetWidthAndHeight(){
        std::pair <int, int> WidthAndHeight;
        WidthAndHeight.first=this->width;
        WidthAndHeight.second=this->height;
        return WidthAndHeight;
    }

    void ActivateMove(bool MoveVariable){
        Moved=MoveVariable;
    }

    void Hide(int a){
        if (Type=="If" || Type=="While"){
            for (int i=0; i<MyItems.size(); i++){
                MyItems[i]->Hide(a);
            }
            if (a){
                Hiden=1;
                Label_Instructions[0]->hide();
                Butt->hide(1);
            }else{
                Hiden=0;
                Label_Instructions[0]->show();
                Butt->hide(0);
            }
        }else if (Type=="ArrayWork"){
            for (int i=0; i<EnabledItems.size(); i++){
                EnabledItems[i]->Hide(a);
            }
            if (a){
                Hiden=1;
                //Label_Instructions[0]->hide();
                //Butt->hide(1);
            }else{
                Hiden=0;
                //Label_Instructions[0]->show();
                //Butt->hide(0);
            }
        }else{
            if (a){
                Hiden=1;
                if (Label_Instructions.size()>0)
                    Label_Instructions[0]->hide();
                if (Butt!=nullptr)
                    Butt->hide(1);
            }else{
                Hiden=0;
                if (Label_Instructions.size()>0)
                    Label_Instructions[0]->show();
                if (Butt!=nullptr)
                    Butt->hide(0);
            }
        }
    }
    //QString PatternTekst;

    std::vector <QLine> HelpLine;
    //std::map<int, int> InstruktionLink;
    int DeltaX=0, DeltaY=0;
    QString Type;
    QPoint FirstPositions;
    std::vector <QLabel*> Label_Instructions;
    std::vector <item *> EnabledItems;
    item* Layout=nullptr;
    item* NekstItem=nullptr;
    int position;
    LilButton* Butt;
    friend LilButton;
    double SumHeigth=0;
    int Status=-1;
    int height=1, width=1, left=0, top=0;
    std::vector <item*> MyItems;
    bool Hiden=0;
    QString Type2;
    int ScrollTop=0, ScrollHeigth=0;
    bool Scroll=0;
    std::vector <QString> CodeLine;
    int KolFuckVariable=0;
    int hh=1;
    std::vector <Variable> LineVariables;
private:
    QString Text="";
    bool Moved=0;
    QWidget* Father;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow* Ruco=nullptr;
    MainWindow* Spr=nullptr;
    std::string landg;
    int ScreenTop, ScreenLeft, ScreenWidth, ScreenHeigth;
    std::vector <item *> PatternOfItems;
    int Slott=0;
    int TT=0;
    MainWindow * Suk;
    MainWindow * th;
    QFont FontLove;
    QStringList Tee;
    explicit MainWindow(QWidget *parent = nullptr, int type=0, QRect r=QRect(), std::string lan="");
    ~MainWindow();
    void SetStartingSetting ();
    void paintEvent (QPaintEvent *event);
    void DrawWindow(QPainter *p, int x1, int y1, int x2, int y2, int q);
    void DrawBlock(QPainter *p, item *i);
    void mouseReleaseEvent( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event );
    void wheelEvent(QWheelEvent *event);
    void StopMove();
    void HideBlocks(item * i, bool u);
    void TimerEvent();
    void ReconstructItem0();
    void SaveArrea (QTextStream * r, item * MainItem);
    void OpenArrea (QTextStream * r, item * MainItem);
    std::vector<item *>::iterator GetPos(item* Item, item* Layout);
    void NewBlock(QString type, int u);
    void DeleteBlock(item* it);
    std::vector <QString> Translate (item * MainItem, int ots, int y);
    int DeltaX=0, DeltaY=0;
    QLabel *Lb = new QLabel(this);
    int KolLayout=0;
    item * PushItem=nullptr;
    //std::vector <QLabel*> CodeLineL;
    QTextEdit * TE;
    QString addres="";
    void UpdateLanguage();
public slots:
    QString IsArithmeticTrue(QString *Line, std::vector <Variable> Variables);
    void AddPattern();
    void FollowMouse();
    void PushButton();
    void InButton();
    void OutButton();
    void ArithmeticButton();
    void SaveButton();
    void SaveAsButton();
    void OpenButton();
    void AddArray(QTextStream *r, item *MainItem, QString Name);
    void ClearButton();
    void SaveAsCode();
    void ChangeLanguage();
    void RukR();
    //void Slot1();
    //void Slot2();
    //void Slot3();
    //void Slot4();
    //void Slot5();
private slots:
    //void on_comboBox_2_currentIndexChanged(int index);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

private:
    std::vector <QLabel*> LabQ;
    QPushButton * Pi;
    bool moveEvent=false;
    Ui::MainWindow *ui;
    std::vector <item*> items;
    item* ChoosingItem=nullptr;
    QTimer *Timer1 = new QTimer(this);
    QPoint FirstMousePositions;
};


#endif // MAINWINDOW_H
