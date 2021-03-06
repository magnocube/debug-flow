#pragma once
#include "visualnodebase.h"
#include "contextfilternode.h"
#include "processingstyle.h"
#include "contextfilter.h"
#include "globalconfig.h"
class VisualContextFilter : public VisualNodeBase, public ProcessingStyle
{
    Q_OBJECT
public:
    VisualContextFilter();
    ~VisualContextFilter();
protected:
    QWidget* loadPropertiesWidget(QWidget* parent);
    void releasePropertiesWidget();

    ContextFilterNode* node = nullptr;
    void activate();
    VisualNodeBase *clone();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ContextFilter* contextFilter = nullptr;
};

