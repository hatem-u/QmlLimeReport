#include "qmlreportengine.h"

QmlReportEngine::QmlReportEngine(QObject *parent) : QObject(parent)
{
    qrySet = false;
    reportLoaded = false;
    re = new LimeReport::ReportEngine(this);
    model = new QSqlQueryModel(this);
    re->setSaveToFileVisible(false);
}

void QmlReportEngine::setReportQuery(QString qry){
    model->setQuery(qry);
    re->dataManager()->addModel("model", model, false);
    qrySet = true;
}

void QmlReportEngine::reportFromFile(QString file){
    re->loadFromFile(file);
    reportLoaded = true;
}

void QmlReportEngine::reportFromString(QString str){
    re->loadFromString(str);
    reportLoaded = true;
}

void QmlReportEngine::printReport(){
    if (reportLoaded)
        re->printReport();
}

void QmlReportEngine::previewReport(){
    if (reportLoaded)
        re->previewReport();
}

void QmlReportEngine::designReport(){
    re->designReport();
}

void QmlReportEngine::printToPDF(QString fileName){
    if (reportLoaded)
        re->printToPDF(fileName);
}

void QmlReportEngine::addVariable(QString name, QVariant val){
    re->dataManager()->setReportVariable(name, val);
}
