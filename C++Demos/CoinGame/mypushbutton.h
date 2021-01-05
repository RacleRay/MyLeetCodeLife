#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QDebug>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QWidget>

class MyPushButton : public QPushButton {
  public:
    explicit MyPushButton( QWidget *parent = 0 );
    MyPushButton( QString normalImg, QString pressImg = "" );

    QString normalImgPath;  //默认显示图片路径
    QString pressedImgPath; //按下后显示图片路径

    void zoom1();
    void zoom2();

    void mouseReleaseEvent( QMouseEvent *e );
    void mousePressEvent( QMouseEvent *e );

  signals:
    chooseSceneBack();

  public slots:
    //
};

#endif // MYPUSHBUTTON_H
