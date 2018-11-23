#include <QtWidgets>
#include "dragwidget.h"


DragWidget::DragWidget(QWidget *parent) : QFrame(parent)
{
    // set up the frame
   setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
   setAcceptDrops(true);
   // this is for testing, all of the setup will be in the controller.
   addSprite(20, 20, QPixmap("/home/wintersc/3505/final/a8-an-educational-app-f18-kathrynriding-1/images/lemon2"));
}

/*
 * addSprite(int locX, int locY, QPixmap)
 *
 * This function adds a sprite to the parent DragWidget. The sprites are
 * created as QLabels and then painted with the provided pixmap and moved to the
 * location provided by the calling function.
 */
void DragWidget::addSprite(int locX, int locY, QPixmap sprite)
{
    QLabel *newIcon = new QLabel(this);
    newIcon->setPixmap(sprite);
    newIcon->move(locX, locY);
    newIcon->show();
    newIcon->setAttribute(Qt::WA_DeleteOnClose);
}

/*
 * dragEnterEvent(QDragEnterEvent *event)
 *
 * This function detectes when the mouse is over the DragWidget
 */
void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

/*
 * dragMoveEvent(QDragMoveEvent *event)
 *
 * This function allows a user to drag a selected sprite. Sprites
 * can be dragged within the parent DragWidget or to a different DragWidget
 */
void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

/*
 * dropEvent(QDropEvent *event)
 *
 * This function allows a user to drop a selected sprite. Sprites
 * can be dragged and dropped within the parent DragWidget or dragged to
 * a different DragWidget and dropped there.
 *
 * If the sprite is not dropped on a DragWidget, it snaps back to where it
 * was picked up from.
 */
void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

/*
 * dragEnterEvent(QDragEnterEvent *event)
 *
 * This function detectes when a sprite has been selected within the borders
 * of the DragWidget. If a child has been selected it allows you to then perform
 * other actions with it. If a Sprite has not been selected, nothing happens.
 */
void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap(); // save the image from the child(sprite)

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap; //creates a darker version of the image that stays in the original location
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
