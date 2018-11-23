#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>

class QDragEnterEvent;
class QDropEvent;

class DragWidget : public QFrame
{
public:
    explicit DragWidget(QWidget *parent = nullptr);
    void addSprite(int locX, int locY, QPixmap sprite);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGWIDGET_H
