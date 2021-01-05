#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton {
    Q_OBJECT
  public:
    MyCoin( QString butImg );
    void mousePressEvent( QMouseEvent *e );

    int  posX;
    int  posY;
    bool flag;
    bool isAnimation = false; //执行动画时，不允许操作

    bool isWin = false; //胜利标志

    void    changeFlag(); //改变标志,执行翻转效果
    QTimer *timer1;       //正面翻反面 定时器
    QTimer *timer2;       //反面翻正面 定时器
    int     min = 1;      //最小图片idx
    int     max = 8;      //最大图片idx

  signals:

  public slots:
};

#endif // MYCOIN_H
