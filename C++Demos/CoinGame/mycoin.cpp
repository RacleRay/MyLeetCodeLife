#include "mycoin.h"
#include <QDebug>
#include <QTimer>

MyCoin::MyCoin( QString butImg ) {

    QPixmap pixmap;
    bool    ret = pixmap.load( butImg );
    if ( !ret ) {
        qDebug() << butImg << "加载图片失败!";
    }

    this->setFixedSize( pixmap.width(), pixmap.height() );
    this->setStyleSheet( "QPushButton{border:0px;}" );
    this->setIcon( pixmap );
    this->setIconSize( QSize( pixmap.width(), pixmap.height() ) );

    //初始化定时器
    timer1 = new QTimer( this );
    timer2 = new QTimer( this );

    connect( timer1, &QTimer::timeout, [ = ]() {
        QPixmap pixmap;
        QString str = QString( ":/res/Coin000%1.png" ).arg( this->min++ );
        pixmap.load( str );
        this->setFixedSize( pixmap.width(), pixmap.height() );
        this->setStyleSheet( "QPushButton{border:0px;}" );
        this->setIcon( pixmap );
        this->setIconSize( QSize( pixmap.width(), pixmap.height() ) );
        if ( this->min > this->max ) {
            this->min         = 1;
            this->isAnimation = false;
            timer1->stop();
        }
    } );

    connect( timer2, &QTimer::timeout, [ = ]() {
        QPixmap pixmap;
        QString str = QString( ":/res/Coin000%1.png" ).arg( ( this->max )-- );
        pixmap.load( str );
        this->setFixedSize( pixmap.width(), pixmap.height() );
        this->setStyleSheet( "QPushButton{border:0px;}" );
        this->setIcon( pixmap );
        this->setIconSize( QSize( pixmap.width(), pixmap.height() ) );
        if ( this->max < this->min ) {
            this->max         = 8;
            this->isAnimation = false;
            timer2->stop();
        }
    } );
}

void MyCoin::changeFlag() {
    if ( this->flag ) {
        timer1->start( 30 );
        this->isAnimation = true;
        this->flag        = false;
    } else {
        timer2->start( 30 );
        this->isAnimation = true;
        this->flag        = true;
    }
}

void MyCoin::mousePressEvent( QMouseEvent *e ) {
    if ( this->isAnimation || isWin == true ) {
        return;
    } else {
        return QPushButton::mousePressEvent( e );
    }
}
