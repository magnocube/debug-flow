#include "visualconnection.h"

VisualConnection::VisualConnection(Connector *connector1)
    :connector1(connector1)
{
    setConnector1(connector1);
}

VisualConnection::VisualConnection(Connector *connector1, Connector *connector2)
    :connector1(connector1),connector2(connector2)
{
    setConnector1(connector1);
    setConnector2(connector2);
}

VisualConnection::~VisualConnection()
{
    //delete the double links
    if(connection1Set)
    {
        connector1->disconnect(this);
    }
    if(connection2Set)
    {
        connector2->disconnect(this);
    }
    emit onDelete(this);
}

void VisualConnection::draw(QPainter* painter)
{
    painter->setBrush(QColor::fromRgbF(1,1,1,0.7));
    QPen pen(QColor::fromRgbF(1,1,1,0.7));
    pen.setWidth(8);
    painter->setPen(pen);

    QPoint point1,point2;
    if(connection1Set)
    {
        point1 = connector1->getScenePos();
    }
    else {
        point1 = mousePos;
    }
    if(connection2Set)
    {
        point2 = connector2->getScenePos();
    }
    else {
        point2 = mousePos;
    }
    painter->drawLine(point1,point2);
}

bool VisualConnection::intersect(QPointF position)
{
    QPoint point1,point2;
    if(connection1Set)
    {
        point1 = connector1->getScenePos();
    }
    else {
        point1 = mousePos;
    }
    if(connection2Set)
    {
        point2 = connector2->getScenePos();
    }
    else {
        point2 = mousePos;
    }

    QLineF line(point1,point2);
    qreal distance =  Utils::dist(position,line);
    if(distance < 5)
    {
        return true;
    }
    return false;
}

void VisualConnection::setMousePos(QPoint _mousePos)
{
    mousePos = _mousePos;
}

void VisualConnection::disconnect1()
{
    connector1 = nullptr;
    connection1Set = false;
}
void VisualConnection::disconnect2()
{
    connector2 = nullptr;
    connection2Set = false;
}

Connector *VisualConnection::getConnector1() const
{
    return connector1;
}
Connector *VisualConnection::getConnector2() const
{
    return connector2;
}

void VisualConnection::setConnector1(Connector *value)
{
    connector1 = value;
    connector1->connect(this);
    connection1Set = true;
}
void VisualConnection::setConnector2(Connector *value)
{
    connector2 = value;
    connector2->connect(this);
    connection2Set = true;
}