#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mycoin.h"
#include <QMainWindow>

class PlayScene : public QMainWindow {
    Q_OBJECT
  public:
    PlayScene( int levalIndex );
    void paintEvent( QPaintEvent * ); //重写绘图事件

    int levalIndex; //具体选择的关卡号

    int     gameArray[ 4 ][ 4 ]; //关卡配置二维数组
    MyCoin *coinBtn[ 4 ][ 4 ];   //金币按钮数组

    bool isWin = true; //是否胜利

  signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
