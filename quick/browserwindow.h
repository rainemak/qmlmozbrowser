#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QTimer>
#include <QPointer>
#include <qqml.h>
#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

#include "qopenglwebpage.h"

class BrowserWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(bool completed READ completed NOTIFY completedChanged FINAL)
    Q_PROPERTY(QOpenGLWebPage *contentItem READ contentItem NOTIFY contentItemChanged FINAL)
    Q_PROPERTY(QWindow *chromeWindow READ chromeWindow WRITE setChromeWindow NOTIFY chromeWindowChanged FINAL)

public:
    BrowserWindow(QWindow *parent = 0);

    bool completed() const;

    QOpenGLWebPage *contentItem() const;

    QWindow *chromeWindow() const;
    void setChromeWindow(QWindow *chromeWindow);

signals:
    void completedChanged();
    void contentItemChanged();
    void chromeWindowChanged();

protected:
    virtual void touchEvent(QTouchEvent*);
    virtual QVariant inputMethodQuery(Qt::InputMethodQuery property) const;
    virtual void inputMethodEvent(QInputMethodEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void timerEvent(QTimerEvent *event);

private Q_SLOTS:
    void onViewInitialized();
    void invalidated();
    void createGLContext();
    void createChrome();

private:
    QPointer<QOpenGLWebPage> m_webPage;
    QPointer<QWindow> m_chromeWindow;
    QOpenGLContext *m_context;
    QTimer m_timer;
    bool m_contextSet;

    friend class ChromeWindow;
};

QML_DECLARE_TYPE(BrowserWindow)

#endif
