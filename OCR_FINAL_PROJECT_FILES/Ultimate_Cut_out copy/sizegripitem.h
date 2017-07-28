#ifndef SIZEGRIPITEM_H
#define SIZEGRIPITEM_H


#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>

/**
 * @brief The SizeGripItem class
 */
class SizeGripItem : public QGraphicsItem
{
    signals:

    protected:

    private:
        enum
        {
            Top         = 0x1,
            Bottom      = 0x2,
            Left        = 0x4,
            TopLeft     = Top | Left,
            BottomLeft  = Bottom | Left,
            Right       = 0x8,
            TopRight    = Top | Right,
            BottomRight = Bottom | Right
        };

        class HandleItem : public QGraphicsRectItem
        {
            public:
                HandleItem(int positionFlags, SizeGripItem* parent);
                int positionFlags() const;

            protected:
                virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

            private:
                QPointF restrictPosition(const QPointF& newPos);

                int positionFlags_;
                SizeGripItem* parent_;
        };

    public:
        class Resizer
        {
            public:
                virtual void operator()(QGraphicsItem* item, const QRectF& rect) = 0;
        };

        SizeGripItem(Resizer* resizer = 0, QGraphicsItem* parent = 0);
        virtual ~SizeGripItem();
        virtual QRectF boundingRect() const;
        virtual void paint(QPainter* painter,
                           const QStyleOptionGraphicsItem* option,
                           QWidget* widget = 0);
        void setTopLeft(const QPointF& pos);
        void setTop(qreal y);
        void setTopRight(const QPointF& pos);
        void setRight(qreal x);
        void setBottomRight(const QPointF& pos);
        void setBottom(qreal y);
        void setBottomLeft(const QPointF& pos);
        void setLeft(qreal x);

    private:
        void doResize();
        void updateHandleItemPositions();

        QList<HandleItem*> handleItems_;
        QRectF rect_;
        Resizer* resizer_;
};
#endif // SIZEGRIPITEM_H
