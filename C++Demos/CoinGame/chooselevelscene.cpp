#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QSound>

ChooseLevelScene::ChooseLevelScene( QWidget *parent )
    : QMainWindow( parent ) {
    this->setFixedSize( 320, 588 );
    this->setWindowIcon( QPixmap( ":/res/Coin0001.png" ) );
    this->setWindowTitle( "选择关卡" );

    //创建菜单栏
    QMenuBar *bar = this->menuBar();
    this->setMenuBar( bar );
    //创建开始菜单
    QMenu *  startMenu  = bar->addMenu( "开始" );
    QAction *quitAction = startMenu->addAction( "退出" );

    connect( quitAction, &QAction::triggered, [ = ]() { this->close(); } );

    QSound *backSound = new QSound( ":/res/BackButtonSound.wav", this );
    // 返回按钮
    MyPushButton *closeBtn = new MyPushButton( ":/res/BackButton.png",
                                               ":/res/BackButtonSelected.png" );
    closeBtn->setParent( this );
    closeBtn->move( this->width() - closeBtn->width(),
                    this->height() - closeBtn->height() );

    connect( closeBtn, &MyPushButton::clicked, [ = ]() {
        backSound->play();
        QTimer::singleShot( 200, this, [ = ]() {
            this->hide();
            emit this->chooseSceneBack();
        } );
    } );

    playScene           = NULL;
    QSound *chooseSound = new QSound( ":/res/TapButtonSound.wav", this );
    //创建关卡按钮
    for ( int i = 0; i < 20; i++ ) {
        MyPushButton *menuBtn = new MyPushButton( ":/res/LevelIcon.png" );
        menuBtn->setParent( this );
        menuBtn->move( 25 + ( i % 4 ) * 70, 130 + ( i / 4 ) * 70 );

        connect( menuBtn, &MyPushButton::clicked, [ = ]() {
            // qDebug() <<"您选择的是第"<< i+1 << "关";
            playScene = new PlayScene( i + 1 );
            chooseSound->play();

            this->hide();
            this->playScene->setGeometry( this->geometry() );
            this->playScene->show();

            //监听游戏场景中点击返回按钮 发送的自定义信号
            connect( this->playScene, &PlayScene::chooseSceneBack, [ = ]() {
                this->setGeometry( this->playScene->geometry() );
                delete this->playScene;
                this->playScene = NULL;
                this->show();
            } );
        } );

        //按钮上显示的文字
        QLabel *label = new QLabel;
        label->setParent( this );
        label->setFixedSize( menuBtn->width(), menuBtn->height() );
        label->setText( QString::number( i + 1 ) );
        label->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter ); // 居中
        label->move( 25 + ( i % 4 ) * 70, 130 + ( i / 4 ) * 70 );
        label->setAttribute( Qt::WA_TransparentForMouseEvents,
                             true ); //鼠标事件穿透Label
    }
}

void ChooseLevelScene::paintEvent( QPaintEvent * ) {
    QPainter painter( this );
    QPixmap  pix;
    pix.load( ":/res/OtherSceneBg.png" );
    painter.drawPixmap( 0, 0, this->width(), this->height(), pix );

    //加载标题
    pix.load( ":/res/Title.png" );
    painter.drawPixmap( ( this->width() - pix.width() ) * 0.5, 30, pix.width(),
                        pix.height(), pix );
}
