#include "browserwindow.h"
#include "qmozcontext.h"

#include <QDebug>
#include <QCoreApplication>

BrowserWindow::BrowserWindow(QWindow *parent)
    : QWindow(parent)
    , m_context(0)
    , m_contextSet(false)
{
    qDebug() << "-------------------------- browser window";

    resize(1536, 2048);;
    setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format(requestedFormat());
    format.setAlphaBufferSize(0);
    setFormat(format);

    create();

    m_webPage = new QOpenGLWebPage(this);
    qDebug() << QCoreApplication::arguments();
    QString url = "about:license";
    if (QCoreApplication::arguments().count() > 1) {
        url = QCoreApplication::arguments().at(1);
    }

    m_webPage->load(url);
    m_webPage->loadFrameScript("chrome://embedlite/content/embedhelper.js");
    m_webPage->setSize(QSizeF(1536, 2048));
    setObjectName("BrowserWindow");


    QMozContext::GetInstance()->setPixelRatio(2.0);
    connect(m_webPage, SIGNAL(requestGLContext()), this, SLOT(createGLContext()), Qt::DirectConnection);
    connect(m_webPage, SIGNAL(completedChanged()), this, SLOT(onViewInitialized()));
}

bool BrowserWindow::completed() const
{
    return m_webPage && m_webPage->completed();
}

QOpenGLWebPage *BrowserWindow::contentItem() const
{
    return m_webPage;
}

QWindow *BrowserWindow::chromeWindow() const
{
    return m_chromeWindow;
}

void BrowserWindow::setChromeWindow(QWindow *chromeWindow)
{
    if (chromeWindow != m_chromeWindow) {
        m_chromeWindow = chromeWindow;
        if (m_chromeWindow) {
            m_chromeWindow->setTransientParent(this);
            showFullScreen();
        }
        emit chromeWindowChanged();
    }
}

void BrowserWindow::touchEvent(QTouchEvent *e)
{
    if (m_webPage) {
        m_webPage->touchEvent(e);
    }
}

QVariant BrowserWindow::inputMethodQuery(Qt::InputMethodQuery property) const
{
    if (m_webPage) {
        return m_webPage->inputMethodQuery(property);
    }
    return QVariant();
}

void BrowserWindow::inputMethodEvent(QInputMethodEvent *event)
{
    if (m_webPage) {
        m_webPage->inputMethodEvent(event);
    }
}

void BrowserWindow::keyPressEvent(QKeyEvent *event)
{
    if (m_webPage) {
        m_webPage->keyPressEvent(event);
    }
}

void BrowserWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (m_webPage) {
        m_webPage->keyReleaseEvent(event);
    }
}

void BrowserWindow::focusInEvent(QFocusEvent *event)
{
    if (m_webPage) {
        m_webPage->focusInEvent(event);
    }
}

void BrowserWindow::focusOutEvent(QFocusEvent *event)
{
    if (m_webPage) {
        m_webPage->focusInEvent(event);
    }
}

void BrowserWindow::timerEvent(QTimerEvent *event)
{
    if (m_webPage) {
        m_webPage->timerEvent(event);
    }
}

void BrowserWindow::invalidated()
{
}

void BrowserWindow::createGLContext()
{
    qDebug() << "-------------------------- * createGLContext";
    Q_ASSERT(!m_context);

    m_context = new QOpenGLContext();
    m_context->setFormat(requestedFormat());
    m_context->create();
    m_context->makeCurrent(this);

    initializeOpenGLFunctions();
}

void BrowserWindow::onViewInitialized()
{
    qDebug() << "-------------------------- * onViewInitialized";
    if (m_webPage) {
        emit contentItemChanged();
        emit completedChanged();
    }
}
