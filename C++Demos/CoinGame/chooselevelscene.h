#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include "playscene.h"
#include <QMainWindow>
#include <QPaintEvent>

class ChooseLevelScene : public QMainWindow {
    Q_OBJECT
  public:
    explicit ChooseLevelScene( QWidget *parent = 0 );
    void paintEvent( QPaintEvent * );

    PlayScene *playScene;

  signals:
    chooseSceneBack();

  public slots:
};

#endif // CHOOSELEVELSCENE_H
