#include "qmlreportengine.h"

QmlReportEngine::QmlReportEngine(QObject *parent) : QObject(parent)
{
    // these boolean variables are for
    // checking whether or not the
    // the script is used as intended
    qrySet = false;
    reportLoaded = false;

    model = new QSqlQueryModel(this);
    // Clients tend to mix this with PDF printing
    re.setSaveToFileVisible(false);
}

void QmlReportEngine::setReportQuery(QString qry){
    model->setQuery(qry);
    re.dataManager()->addModel("model", model, false);
    qrySet = true;
}

void QmlReportEngine::reportFromFile(QString file){
    re.loadFromFile(file);
    reportLoaded = true;
}

void QmlReportEngine::reportFromString(QString str){
    re.loadFromString(str);
    reportLoaded = true;
}

void QmlReportEngine::printReport(){
    if (reportLoaded)
        re.printReport();
}

void QmlReportEngine::previewReport(){
    if (reportLoaded)
        re.previewReport();
}

void QmlReportEngine::designReport(){
    re.designReport();
}

void QmlReportEngine::printToPDF(QString fileName){
    if (reportLoaded)
        re.printToPDF(fileName);
}

void QmlReportEngine::addVariable(QString name, QVariant val){
    re.dataManager()->setReportVariable(name, val);
}

void QmlReportEngine::setResultEditable(bool res){
    re.setResultEditable(res);
}

QString QmlReportEngine::lastError(){
    return re.lastError();
}

void QmlReportEngine::setCurrentReportsDir(QString dir){
    re.setCurrentReportsDir(dir);
}

bool QmlReportEngine::addFunction(QString name, QString script, QString category, QString description){
    return re.scriptManager()->addFunction(name, script, category, description);
}

//This is for adding objects from C++ to the QJSEngine of LimeReport
//This has many use cases like custom manipulation of fields before
//they're drawn
QJSEngine* QmlReportEngine::scriptEngine(){
    return re.scriptManager()->scriptEngine();
}
