#include "logowidget.h"

logoWidget::logoWidget(QWidget *parent) {}

void logoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter (this);
    painter.setBackground(QBrush (Qt::white));
    painter.setPen (QPen(Qt::black));
    painter.setBrush (QBrush(Qt::green));


    QPoint center_widget(width () / 2, height () / 2);
    int radius = std::min(width (), height ()) / 3;
    painter.drawEllipse(center_widget, radius, radius);
    painter.drawText(9, 19, tr("*"));
}
