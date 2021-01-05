#include "mypushbutton.h"

MyPushButton::MyPushButton( QWidget *parent )
    : QPushButton( parent ) {}

MyPushButton::MyPushButton( QString normalImg, QString pressImg ) {
    this->normalImgPath  = normalImg;
    this->pressedImgPath = pressImg;
    QPixmap pixmap;
    bool    ret = pixmap.load( normalImgPath );
    if ( !ret ) {
        qDebug() << normalImg << "加载图片失败!";
    }

    this->setFixedSize( pixmap.width(), pixmap.height() );
    this->setStyleSheet( "QPushButton{border:0px;}" );
    this->setIcon( pixmap );
    this->setIconSize( QSize( pixmap.width(), pixmap.height() ) );
}

void MyPushButton::zoom1() {
    //创建动画对象
    QPropertyAnimation *animation1 = new QPropertyAnimation( this, "geometry" );
    //设置时间间隔，单位毫秒
    animation1->setDuration( 200 );
    animation1->setStartValue(
        QRect( this->x(), this->y(), this->width(), this->height() ) );
    animation1->setEndValue(
        QRect( this->x(), this->y() + 10, this->width(), this->height() ) );
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation1->setEasingCurve( QEasingCurve::OutBounce );
    animation1->start( QAbstractAnimation::DeleteWhenStopped );
}

void MyPushButton::zoom2() {
    QPropertyAnimation *animation1 = new QPropertyAnimation( this, "geometry" );
    animation1->setDuration( 200 );
    animation1->setStartValue(
        QRect( this->x(), this->y() + 10, this->width(), this->height() ) );
    animation1->setEndValue(
        QRect( this->x(), this->y(), this->width(), this->height() ) );
    animation1->setEasingCurve( QEasingCurve::OutBounce );
    animation1->start( QAbstractAnimation::DeleteWhenStopped );
}

// 返回键的效果
void MyPushButton::mousePressEvent( QMouseEvent *e ) {
    if ( pressedImgPath != "" )
    {
        QPixmap pixmap;
        bool    ret = pixmap.load( pressedImgPath );
        if ( !ret ) {
            qDebug() << pressedImgPath << "加载图片失败!";
        }

        this->setFixedSize( pixmap.width(), pixmap.height() );
        this->setStyleSheet( "QPushButton{border:0px;}" );
        this->setIcon( pixmap );
        this->setIconSize( QSize( pixmap.width(), pixmap.height() ) );
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent( e );
}

void MyPushButton::mouseReleaseEvent( QMouseEvent *e ) {
    if ( normalImgPath != "" )
    {
        QPixmap pixmap;
        bool    ret = pixmap.load( normalImgPath );
        if ( !ret ) {
            qDebug() << normalImgPath << "加载图片失败!";
        }
        this->setFixedSize( pixmap.width(), pixmap.height() );
        this->setStyleSheet( "QPushButton{border:0px;}" );
        this->setIcon( pixmap );
        this->setIconSize( QSize( pixmap.width(), pixmap.height() ) );
    }
    //交给父类执行 释放事件
    return QPushButton::mouseReleaseEvent( e );
}
