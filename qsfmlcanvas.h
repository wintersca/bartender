#include <QWidget>
#include <QObject>
#include <QTimer>
#include <SFML/Graphics.hpp>

#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

/**
 * QSFMLCanvas provides a Qt-SFML hybrid class to better merge the two frameworks together to allow
 * for easy animation and drawing inside a Qt application.
 *
 * This class has been borrowed heavily from https://www.sfml-dev.org/tutorials/1.6/graphics-qt.php
 * as a base class for the game development process. Most credit to the authors thereof. Some modifications
 * have been made in the implementation from the source.
 *
 * Author: Kylee Fluckiger
 */
class QSFMLCanvas : public QWidget, public sf::RenderWindow
{

    Q_OBJECT

public :

    /**
     * Constructs a QSFMLCanvas object as a Qt-type object for use.
     *
     * Frame time should be set to 0 so that the canvas paints itself as often as possible.
     */
    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, int FrameTime = 0);

private :

    /**
     * This serves as the constructor for all SFML components.
     */
    virtual void OnInit() = 0;

    /**
     * This function is called as often as possible (as determined by FrameTime in the constructor)
     * to update SFML components and draw.
     */
    virtual void OnUpdate() = 0;

    /**
     * A Qt paint engine, if necessary. May be set to null in implementation to allow SMFL drawing.
     */
    virtual QPaintEngine* paintEngine() const;

    /**
     * A method to better integrate SFML aspects with Qt.
     */
    virtual void showEvent(QShowEvent*);

    /**
     * Implement Qt's paint events.
     */
    virtual void paintEvent(QPaintEvent*);

    /**
     * Controls the rate of redrawing.
     */
    QTimer myTimer;

    /**
     * Used to assist in initializing and running the canvas.
     */
    bool   myInitialized;

};

#endif // QSFMLCANVAS_H
