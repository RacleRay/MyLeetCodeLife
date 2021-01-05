#include "playscene.h"
#include "dataconfig.h"
#include "mycoin.h"
#include "mypushbutton.h"
#include <QAction>
#include <QDebug>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QSound>
#include <QTimer>

PlayScene::PlayScene( int index ) {
    // qDebug() << "当前关卡为"<< index;
    this->levalIndex = index;
    this->setFixedSize( 320, 588 );
    this->setWindowIcon( QPixmap( ":/res/Coin0001.png" ) );
    this->setWindowTitle( "翻金币" );

    QMenuBar *bar = this->menuBar();
    this->setMenuBar( bar );
    QMenu *  startMenu  = bar->addMenu( "开始" );
    QAction *quitAction = startMenu->addAction( "退出" );
    connect( quitAction, &QAction::triggered, [ = ]() { this->close(); } );

    //翻金币音效
    QSound *flipSound = new QSound( ":/res/ConFlipSound.wav", this );
    //胜利按钮音效
    QSound *winSound = new QSound( ":/res/LevelWinSound.wav", this );
    //返回按钮音效
    QSound *backSound = new QSound( ":/res/BackButtonSound.wav", this );

    //返回按钮
    MyPushButton *closeBtn = new MyPushButton( ":/res/BackButton.png",
                                               ":/res/BackButtonSelected.png" );
    closeBtn->setParent( this );
    closeBtn->move( this->width() - closeBtn->width(),
                    this->height() - closeBtn->height() );

    //返回按钮功能实现
    connect( closeBtn, &MyPushButton::clicked, [ = ]() {
        backSound->play();
        QTimer::singleShot( 200, this, [ = ]() {
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
        } );
    } );

    //当前关卡标题
    QLabel *label = new QLabel;
    label->setParent( this );
    QFont font;
    font.setFamily( "华文新魏" );
    font.setPointSize( 14 );
    label->setFont( font );
    QString str = QString( "Leavel: %1" ).arg( this->levalIndex );
    label->setText( str );
    label->setGeometry(
        QRect( 20, this->height() - 40, 120, 50 ) ); //设置大小和位置

    //关卡配置
    dataConfig config;
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            gameArray[ i ][ j ] = config.mData[ this->levalIndex ][ i ][ j ];
        }
    }

    //胜利时显示的图片
    QLabel *winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load( ":/res/LevelCompletedDialogBg.png" );
    winLabel->setGeometry( 0, 0, tmpPix.width(), tmpPix.height() );
    winLabel->setPixmap( tmpPix );
    winLabel->setParent( this );
    winLabel->move( ( this->width() - tmpPix.width() ) * 0.5,
                    -tmpPix.height() );

    //创建金币的背景图片
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            QLabel *label = new QLabel;
            label->setGeometry( 0, 0, 50, 50 );
            label->setPixmap( QPixmap( ":/res/BoardNode.png" ) );
            label->setParent( this );
            label->move( 57 + i * 50, 200 + j * 50 );

            //金币对象
            QString img;
            if ( gameArray[ i ][ j ] == 1 ) {
                img = ":/res/Coin0001.png";
            } else {
                img = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin( img );
            coin->setParent( this );
            coin->move( 59 + i * 50, 204 + j * 50 );
            coin->posX = i;                   //记录x坐标
            coin->posY = j;                   //记录y坐标
            coin->flag = gameArray[ i ][ j ]; //记录正反标志

            coinBtn[ i ][ j ] = coin;
            connect( coin, &MyCoin::clicked, [ = ]() {
                coin->changeFlag();
                flipSound->play();
                gameArray[ i ][ j ] = gameArray[ i ][ j ] == 0 ? 1 : 0;

                // 改变周围的flag
                QTimer::singleShot( 200, this, [ = ]() {
                    if ( coin->posX + 1 <= 3 ) {
                        coinBtn[ coin->posX + 1 ][ coin->posY ]->changeFlag();
                        gameArray[ coin->posX + 1 ][ coin->posY ] =
                            gameArray[ coin->posX + 1 ][ coin->posY ] == 0 ? 1
                                                                           : 0;
                    }
                    if ( coin->posX - 1 >= 0 ) {
                        coinBtn[ coin->posX - 1 ][ coin->posY ]->changeFlag();
                        gameArray[ coin->posX - 1 ][ coin->posY ] =
                            gameArray[ coin->posX - 1 ][ coin->posY ] == 0 ? 1
                                                                           : 0;
                    }
                    if ( coin->posY + 1 <= 3 ) {
                        coinBtn[ coin->posX ][ coin->posY + 1 ]->changeFlag();
                        gameArray[ coin->posX ][ coin->posY + 1 ] =
                            gameArray[ coin->posX + 1 ][ coin->posY ] == 0 ? 1
                                                                           : 0;
                    }
                    if ( coin->posY - 1 >= 0 ) {
                        coinBtn[ coin->posX ][ coin->posY - 1 ]->changeFlag();
                        gameArray[ coin->posX ][ coin->posY - 1 ] =
                            gameArray[ coin->posX + 1 ][ coin->posY ] == 0 ? 1
                                                                           : 0;
                    }

                    // 判断是否胜利：全部为正面时，胜利
                    for ( int i = 0; i < 4; i++ ) {
                        for ( int j = 0; j < 4; j++ ) {
                            if ( coinBtn[ i ][ j ]->flag == false ) {
                                qDebug() << coinBtn[ i ][ j ]->flag << " " << i
                                         << " " << j;
                                this->isWin = false;
                                break;
                            } else {
                                coinBtn[ i ][ j ]->isWin = true;
                            }
                        }
                    }

                    if ( this->isWin ) {
                        // qDebug() << "胜利";
                        winSound->play();
                        QPropertyAnimation *animation1 =
                            new QPropertyAnimation( winLabel, "geometry" );
                        animation1->setDuration( 1000 );
                        animation1->setStartValue(
                            QRect( winLabel->x(), winLabel->y(),
                                   winLabel->width(), winLabel->height() ) );
                        animation1->setEndValue(
                            QRect( winLabel->x(), winLabel->y() + 114,
                                   winLabel->width(), winLabel->height() ) );
                        animation1->setEasingCurve( QEasingCurve::OutBounce );
                        animation1->start();
                    }
                } );
            } );
        }
    }
}

void PlayScene::paintEvent( QPaintEvent * ) {
    QPainter painter( this );
    QPixmap  pix;
    pix.load( ":/res/PlayLevelSceneBg.png" );
    painter.drawPixmap( 0, 0, this->width(), this->height(), pix );

    pix.load( ":/res/Title.png" );
    pix = pix.scaled( pix.width() * 0.5, pix.height() * 0.5 );
    painter.drawPixmap( 10, 30, pix.width(), pix.height(), pix );
}
