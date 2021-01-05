#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "chooselevelscene.h"
#include <QDebug>
#include <QMainWindow>
#include <QPainter>

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainScene( QWidget *parent = 0 );
    ~MainScene();

    void paintEvent( QPaintEvent * );

    ChooseLevelScene *chooseScene;

  private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
