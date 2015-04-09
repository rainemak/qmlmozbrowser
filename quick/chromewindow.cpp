#include "chromewindow.h"

#include <QQmlContext>
#include <QRegion>

#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>

#include <QDebug>

ChromeWindow::ChromeWindow(QWindow *parent)
    : QQuickView(parent)
{
    qDebug() << "-------------------------- ChromeWindow: " << parent;

    resize(1536, 2048);
    setTransientParent(parent);
    rootContext()->setContextProperty("BrowserWindow", parent);
    setSource(QUrl("qrc:/qml/MainPageQuickSf.qml"));
    installEventFilter(this);

    QPlatformNativeInterface *native = QGuiApplication::platformNativeInterface();
    create();
    native->setWindowProperty(handle(), QLatin1String("MOUSE_REGION"), QVariant(QRegion(0, 2048-100, 1536, 100)));
}

bool ChromeWindow::eventFilter(QObject *obj, QEvent *e)
{
#if 0
    qDebug() << e << e->type();
    static bool moro = false;
    if (e->type() == QEvent::Expose && !moro && transientParent()) {

        qDebug() << "what what...:" << transientParent();
        moro = true;
    }
#endif
    return false;
}
