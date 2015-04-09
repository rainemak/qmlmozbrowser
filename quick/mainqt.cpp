#include <QGuiApplication>
#include <QQuickView>
#include <QTimer>
#include "qmozcontext.h"
#include "quickmozview.h"
#include "qmozscrolldecorator.h"
#include "browserwindow.h"
#include "chromewindow.h"

int main(int argc, char **argv)
{
    qDebug() << "-------------------------- main";

    QGuiApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(true);

    QString componentPath(DEFAULT_COMPONENTS_PATH);
    qDebug() << "Load components from:" << componentPath + QString("/components") + QString("/EmbedLiteBinComponents.manifest");
    QMozContext::GetInstance()->addComponentManifest(componentPath + QString("/components") + QString("/EmbedLiteBinComponents.manifest"));
    qDebug() << "Load components from:" << componentPath + QString("/components") + QString("/EmbedLiteJSComponents.manifest");
    QMozContext::GetInstance()->addComponentManifest(componentPath + QString("/components") + QString("/EmbedLiteJSComponents.manifest"));
    qDebug() << "Load components from:" << componentPath + QString("/chrome") + QString("/EmbedLiteJSScripts.manifest");
    QMozContext::GetInstance()->addComponentManifest(componentPath + QString("/chrome") + QString("/EmbedLiteJSScripts.manifest"));
    qDebug() << "Load components from:" << componentPath + QString("/chrome") + QString("/EmbedLiteOverrides.manifest");
    QMozContext::GetInstance()->addComponentManifest(componentPath + QString("/chrome") + QString("/EmbedLiteOverrides.manifest"));

    qmlRegisterType<BrowserWindow>("Test", 1, 0, "WebView");
    qmlRegisterUncreatableType<QOpenGLWebPage>("Test", 1, 0, "WebPage", "");
    qmlRegisterUncreatableType<QMozScrollDecorator>("Test", 1, 0, "ScrollD", "");

//    BrowserWindow bwindow;
//    bwindow.showFullScreen();

    ChromeWindow *chrome = new ChromeWindow();
//    QObject::connect(&bwindow, SIGNAL(showChrome()), chrome, SLOT(showFullScreen()));
//    chrome->showFullScreen();

    QTimer::singleShot(0, QMozContext::GetInstance(), SLOT(runEmbedding()));
    QObject::connect(&app, SIGNAL(lastWindowClosed()), QMozContext::GetInstance(), SLOT(stopEmbedding()));

    return app.exec();
}
