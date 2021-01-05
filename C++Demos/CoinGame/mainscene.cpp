#include "mainscene.h"
#include "chooselevelscene.h"
#include "mypushbutton.h"
#include "ui_mainscene.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene( QWidget *parent )
    : QMainWindow( parent )
    , ui( new Ui::MainScene ) {
    ui->setupUi( this );
    this->setFixedSize( 320, 588 );
    this->setWindowIcon( QPixmap( ":/res/Coin0001.png" ) );
    this->setWindowTitle( "Connet The Coins" );

    // 退出按钮
    connect( ui->actionQuit, &QAction::triggered, [ = ]() { this->close(); } );

    // 开始游戏按钮
    MyPushButton *startBtn =
        new MyPushButton( ":/res/MenuSceneStartButton.png" );
    startBtn->setParent( this );
    startBtn->move( this->width() * 0.5 - startBtn->width() * 0.5,
                    this->height() * 0.7 );

    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);

    // 点击开始游戏按钮
    chooseScene = new ChooseLevelScene;
    //   监听选择场景的返回按钮
    connect( chooseScene, &ChooseLevelScene::chooseSceneBack, [ = ]() {
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());
        this->show();
    } );

    connect( startBtn, &MyPushButton::clicked, [ = ]() {
        startBtn->zoom1();
        startSound->play();
        startBtn->zoom2();

        QTimer::singleShot( 500, this, [ = ]() {
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        } );
    } );
}

MainScene::~MainScene() { delete ui; }

void MainScene::paintEvent( QPaintEvent * ) {
    QPainter painter( this );
    QPixmap  pix;
    pix.load( ":/res/PlayLevelSceneBg.png" );
    painter.drawPixmap( 0, 0, this->width(), this->height(), pix );
    pix.load( ":/res/Title.png" );
    pix = pix.scaled( pix.width() * 0.6, pix.height() * 0.6 );
    painter.drawPixmap( 10, 30, pix.width(), pix.height(), pix );
}
