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

class item;

class LilButton{
public:
    LilButton(int left, int top, int width, int height, QWidget* parent, int Type){
        this->Type=Type;
        Mi = parent;
        WidthFrame=200;
        HeigthFrame=125;
        LeftFrame=left+width;
        TopFrame=top;
        Text="...";
        Width=18;
        Heigth=10;
        if (Type==1 || Type==2)
            width-=width/7.5;
        this->Left=left+width-Width;
        this->Top=top+height-Heigth;
        Lb = new QLabel(parent);
        Lb->setText(Text);
        Lb->move(this->Left-40, this->Top-14);
        Lb->setAlignment(Qt::AlignCenter);
        Lb->setStyleSheet("color : black;");
        Lb->show();
        if (Type==2){
            Frame4.push_back(new QPushButton(parent));
            //Frame4[0]->setEnabled(0);
            Frame4[0]->resize(150, 25);
            WidthFrame=200;
            HeigthFrame=45;
            Frame4[0]->setText("+Добавить");
            Frame4[0]->move(LeftFrame+WidthFrame/2-75, TopFrame+10);
            parent->connect(Frame4[0], SIGNAL(clicked()), parent, SLOT(InButton()));
        }else if (Type==1){
            Frame4.push_back(new QPushButton(parent));
            //Frame4[0]->setEnabled(0);
            Frame4[0]->resize(150, 25);
            WidthFrame=200;
            HeigthFrame=45;
            Frame4[0]->setText("+Добавить");
            Frame4[0]->move(LeftFrame+WidthFrame/2-75, TopFrame+10);
            parent->connect(Frame4[0], SIGNAL(clicked()), parent, SLOT(OutButton()));
        }else if (Type==3){
            Frame4.push_back(new QPushButton(parent));
            //Frame4[0]->setEnabled(0);
            Frame4[0]->resize(150, 25);
            WidthFrame=200;
            HeigthFrame=45;
            Frame4[0]->setText("+Добавить");
            Frame4[0]->move(LeftFrame+WidthFrame/2-75, TopFrame+10);
            parent->connect(Frame4[0], SIGNAL(clicked()), parent, SLOT(ArithmeticButton()));
        }
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
        FrameCorrect();
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
            for (int i=0; i<Frame3.size(); i++){
                Frame3[i]->hide();
            }
            for (int i=0; i<Frame4.size(); i++){
                Frame4[i]->hide();
            }
        }else{
            for (int i=0; i<Frame1.size(); i++){
                Frame1[i]->show();
            }
            for (int i=0; i<Frame2.size(); i++){
                Frame2[i]->show();
            }
            for (int i=0; i<Frame3.size(); i++){
                Frame3[i]->show();
            }
            for (int i=0; i<Frame4.size(); i++){
                Frame4[i]->show();
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
        WidthFrame=200;
        HeigthFrame=125;
        LeftFrame=left+width;
        TopFrame=top;
        Text="...";
        Width=18;
        Heigth=10;
        if (Type==1)
            width-=width/7.5;
        Left=left+width-Lb->width()-5;
        Top=top+height;
        Lb->setGeometry(this->Left-40, this->Top-14, Lb->width(), Lb->height());
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
        FrameCorrect();
    }
    void Frame_Move(int x1, int y1){
        TopFrame+=y1;
        LeftFrame+=x1;
        FrameCorrect();
    }

    ~LilButton(){
        Lb->~QLabel();
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
    bool IsActivate=0;
    std::vector <PointToPoint> FrameLineInstructions;
    std::vector <QComboBox *> Frame1;
    std::vector <QLineEdit *> Frame2;
    std::vector <QLabel *> Frame3;
    std::vector <QPushButton *> Frame4;
    int HeigthFrame, WidthFrame, TopFrame, LeftFrame;
    friend item;
private:
    QLabel* Lb=nullptr;
    QString Text;
    //int top, width, left;
    int Heigth, Width, Top, Left;
    QWidget * Mi;
    int Type;
};

class item{
public:
    item(QString Type, QWidget* Mi){
        Father=Mi;
        if (Type!="ArrayWork"){
            /*if (Type=="If"){

            }else{*/
                height=40;
                width=75;
            //}
        }else{
            height=600;
            width=550;
        }
        top=0;
        left=0;
        this->Type=Type;
        if (Type!="ArrayWork" && Type!="Begin" && Type!="End"){

            if (Type=="Out"){
                Butt = new LilButton(left, top, width, height, Mi, 1);
            }else if (Type=="In"){
                Butt = new LilButton(left, top, width, height, Mi, 2);
            }else{
                Butt = new LilButton(left, top, width, height, Mi, 3);
            }/*else{
                Butt = new LilButton(left, top, width, height, Mi, 4);
            }*/
        }else{
            Butt = new LilButton(left, top, 1, 1, Mi, 0);
            Butt->Lb->setText("");
            Butt->Lb->hide();
        }
    }
    ~item(){
        Label_Instructions[0]->~QLabel();
        //if (Type!="ArrayWork")
            Butt->~LilButton();
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
            this->Label_Instructions[i]->move(left+width/2-47,
                                              top+height/2-20);
        }
        //if (Type!="ArrayWork")
            Butt->move(x1, y1);
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
        lineInstructions[0].x1=(lineInstructions[0].x1*kofX);
        lineInstructions[0].x2=(lineInstructions[0].x2*kofX);
        lineInstructions[1].x1=(lineInstructions[1].x1*kofX);
        lineInstructions[1].y2=(lineInstructions[1].y2*kofY);
        lineInstructions[2].x2=(lineInstructions[2].x2*kofX);
        lineInstructions[2].y2=(lineInstructions[2].y2*kofY);
        lineInstructions[2].x1=(lineInstructions[2].x1*kofX);
        lineInstructions[3].x1=(lineInstructions[3].x1*kofX);
        lineInstructions[3].x2=(lineInstructions[3].x2*kofX);
        lineInstructions[3].y1=(lineInstructions[3].y1*kofY);
        lineInstructions[3].y2=(lineInstructions[3].y2*kofY);
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
    std::map<int, int> InstruktionLink;
    int DeltaX=0, DeltaY=0;
    std::vector <PointToPoint> lineInstructions;
    QString Type;
    QPoint FirstPositions;
    std::vector <QLabel*> Label_Instructions;
    std::vector <int> EnabledItems;
    item* Layout=nullptr;
    item* NekstItem=nullptr;
    int position;
    LilButton* Butt;
    friend LilButton;
private:    
    int height=1, width=1, left=0, top=0;
    QString Text="";
    bool Moved=0;
    QWidget* Father;
    std::vector <item*> MyItems;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetStartingSetting ();
    void paintEvent (QPaintEvent *event);
    void DrawWindow(QPainter *p, int x1, int y1, int x2, int y2, int q);
    void DrawBlock(QPainter *p, item *i);
    void mouseReleaseEvent( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event );
    //void AddToFrame();
    void StopMove();
    void TimerEvent();
    void ReconstructItem0();
    std::vector<int>::iterator GetPos(item* Item, item* Layout);
    void NewBlock(QString type);
    void Translate (item * MainItem);
    int DeltaX=0, DeltaY=0;
    QLabel *Lb = new QLabel(this);
    int KolLayout=0;
    item * PushItem=nullptr;
    std::vector <QString> CodeLine;
    std::vector <QLabel*> CodeLineL;
    std::vector <std::pair<QString, QString> > LineVariables;
public slots:
    void FollowMouse();
    void PushButton();
    void InButton();
    void OutButton();
    void ArithmeticButton();
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
