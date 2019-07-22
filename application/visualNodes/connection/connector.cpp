#include "connector.h"


Connector::Connector(VisualNodeBase *parent, int x, int y, ConnectorType type, int diameter, double angle)
    :parent(parent),x(x),y(y),type(type),connectionDiameter(diameter),angle(angle)
{

}
Connector::~Connector()
{
    QListIterator<VisualConnection*> iterator(connections);
    while(iterator.hasNext())
    {
        delete iterator.next();
    }
}
QRectF Connector::getRect(int margins)
{
    margins += connectionDiameter/2;
    return QRectF(x-margins,y-margins,margins*2,margins*2);
}
QPoint Connector::getPoint()
{
    return QPoint(x,y);
}
QPoint Connector::getScenePos()
{
    return QPoint(parent->x() + x ,parent->y() + y);
}
bool Connector::connect(VisualConnection *connection)
{
    connections.append(connection);
    return true;
}
void Connector::disconnect(VisualConnection *connection)
{
    if(connections.contains(connection))
    {
        if(connections.removeOne(connection))
        {

        }
        else {
            qDebug("[error,Connector] remove connection failed");
        }
    }
    else {
        qDebug("[error,Connector] disconnect failed connection not in connections");
    }
}

VisualNodeBase *Connector::getParent()
{
#ifdef QT_DEBUG
    if(parent == nullptr)
    {
        qFatal("[fatal][VisualNodeBase] parent is nullptr");
    }
#endif
    return parent;
#
}
bool Connector::requestConnector()
{
    parent->requestConnection(this);
}

bool Connector::requestConnector(VisualConnection *connection)
{
    parent->requestConnection(this,connection);
}
