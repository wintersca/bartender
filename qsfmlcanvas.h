#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <SFML/Graphics.hpp>

/*
 * This Qt-SFML hybrid class has been borrowed from https://www.sfml-dev.org/tutorials/1.6/graphics-qt.php
 * as a base class for the game development process. All credit to the authors thereof. Some modifications
 * have been made in the implementation from the source.
 */
class QSFMLCanvas : public QWidget, public sf::RenderWindow
{

    Q_OBJECT

public :

    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, int FrameTime = 0);

private :

    virtual void OnInit() = 0;

    virtual void OnUpdate() = 0;

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};

#endif // QSFMLCANVAS_H
