#include <QString>
#include <QDebug>
#include <syslog.h>

#define LOG_APP_NAME "myApp"

void syslogMessageHandler(QtMsgType type, const char *msg) {
  QString txt;
  QString clean = QString(msg).section("] ", 1);
  openlog(LOG_APP_NAME, LOG_ODELAY, LOG_USER);
  switch (type) {
  case QtDebugMsg:
    txt = QString("Debug: %1").arg(msg);
    if (!clean.isEmpty()) {
      clean.prepend("Debug: ");
      syslog(LOG_DEBUG, qPrintable(clean));
    }
    fprintf(stderr, "%s\n", msg);
    break;
  case QtWarningMsg:
    txt = QString("Warning: %1").arg(msg);
    if (!clean.isEmpty()) {
      clean.prepend("Warning: ");
      syslog(LOG_WARNING, qPrintable(clean));
    }
    fprintf(stderr, "\033[1;33mWarning\033[0m: %s\n", msg);
    break;
  case QtCriticalMsg:
    txt = QString("Critical: %1").arg(msg);
    if (!clean.isEmpty()) {
      clean.prepend("Critical: ");
      syslog(LOG_CRIT, qPrintable(clean));
    }
    fprintf(stderr, "\033[31mCritical\033[0m: %s\n", msg);
    break;
  case QtFatalMsg:
    txt = QString("Fatal: %1").arg(msg);
    if (!clean.isEmpty()) {
      clean.prepend("Fatal: ");
      syslog(LOG_ERR, qPrintable(clean));
    }
    fprintf(stderr, "\033[31mFatal\033[0m: %s\n", msg);
    abort();
    break;
  }
  closelog();
}

// Set up
// qInstallMsgHandler(syslogMessageHandler);

// qDebug()    << "test";
// qWarning()  << "test";
// qCritical() << "test";
// qFatal()    << "test";
