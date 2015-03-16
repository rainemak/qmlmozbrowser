#ifndef CHROMEWINDOW_H
#define CHROMEWINDOW_H

#include <QQuickView>
#include "browserwindow.h"

class ChromeWindow : public QQuickView
{
    Q_OBJECT
public:
    ChromeWindow(QWindow *parent = 0);

protected:
    virtual bool eventFilter(QObject *obj, QEvent *ev);
};

#endif
