// .h
#include <QDateTime>
#include <QString>
#include <QDebug>

#define LOG_LEVEL 9
#define CQ_FUNC_INFO qPrintable(debugFunctionName(Q_FUNC_INFO, __LINE__))
#define DEBUG(level)         if (level <= LOG_LEVEL) qDebug()    << CQ_FUNC_INFO
#define WARN(level)          if (level <= LOG_LEVEL) qWarning()  << CQ_FUNC_INFO
#define CRITICAL(level)      if (level <= LOG_LEVEL) qCritical() << CQ_FUNC_INFO
QString debugFunctionName(QString name, int line);


// .cpp
QString debugFunctionName(QString name, int line)
{
  QString output;
  QStringList classParts = name.split("::");
  QStringList nameAndReturnType = classParts.first().split(" ");

  QString returnType = "";
  if(nameAndReturnType.count() > 1)
    returnType = nameAndReturnType.first() + " ";
  QString className = nameAndReturnType.last();

  QStringList funcAndParamas = classParts.last().split("(");
  funcAndParamas.last().chop(1);
  QString functionName = funcAndParamas.first();
  QStringList params = funcAndParamas.last().split(",");

  output.append("\033[036m");
  output.append(returnType);
  output.append("\033[0m\033[32m");
  output.append(className);
  output.append("\033[0m::");
  output.append("\033[34m");
  output.append(functionName);
  output.append("\033[0m(");

  QStringList::const_iterator param;
  for (param = params.begin(); param != params.constEnd(); ++param) {
    if(param != params.begin()) {
      output.append("\033[0m,");
    }
    output.append("\033[036m");
    output.append((*param));
  }
  output.append("\033[0m)");
  output.append("[");
  output.append(QString("%1").arg(line));
  output.append("]");
  return output;
}

// usage
WARN(1)   << "Very Important !";
DEBUG(10) << "Value: " << value;
