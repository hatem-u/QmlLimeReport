#ifndef QMLREPORTENGINE_H
#define QMLREPORTENGINE_H

#include <QObject>
#include <LimeReport>
#include <QtSql>

class QmlReportEngine : public QObject
{
    Q_OBJECT
public:
    explicit QmlReportEngine(QObject *parent = nullptr);
    Q_INVOKABLE void setReportQuery(QString qry);
    Q_INVOKABLE void reportFromFile(QString file);
    Q_INVOKABLE void reportFromString(QString str);
    Q_INVOKABLE void printReport();
    Q_INVOKABLE void previewReport();
    Q_INVOKABLE void designReport();
    Q_INVOKABLE void setResultEditable(bool res);
    Q_INVOKABLE void printToPDF(QString fileName);
    Q_INVOKABLE void addVariable(QString name, QVariant val);
    Q_INVOKABLE QString lastError();
    Q_INVOKABLE void setCurrentReportsDir(QString dir);
    Q_INVOKABLE bool addFunction(QString name, QString script, QString category, QString description);
    QJSEngine* scriptEngine();

private:
    bool qrySet;
    bool reportLoaded;
    LimeReport::ReportEngine re;
    QSqlQueryModel *model;
};

#endif // QMLREPORTENGINE_H
