#include "chromewindow.h"

#include <QQmlContext>
#include <QRegion>

#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>

ChromeWindow::ChromeWindow(QWindow *parent)
    : QQuickView(parent)
{
    resize(1536, 2048);
    setSource(QUrl("qrc:/qml/MainPageQuickSf.qml"));
    installEventFilter(this);

    QPlatformNativeInterface *native = QGuiApplication::platformNativeInterface();
    create();
    native->setWindowProperty(handle(), QLatin1String("MOUSE_REGION"), QVariant(QRegion(0, 2048-100, 1536, 100)));
}

bool ChromeWindow::eventFilter(QObject *obj, QEvent *e)
{
    return false;
}
