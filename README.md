# QmlLimeReport
This is my humble beginnings in porting LimeReport over to QML but it doesn't work until after a few tweaks which are the following:

1. Obviously, you have to build LimeReport and add it to your project.
2. You have to add the following in the main '.pro' file:

  `QT += core gui sql printsupport xml`
  
  these are the dependencies of LimeReport and they're required for your Qt Quick application to even compile
3. Replace the QGuiApplication with QApplication.
  Every Qt application runs a single QCoreApplication object which is instantiated in the 'main.cpp' file but in QML application the child QGuiApplication class is used instead of QApplication because it is made for QtWidgets applications so we have to put QApplication instead of QGuiApplication because, while it's true our app is made only using Qt Quick/QML, LimeReport is still dependent on QtWidgets so we have to make that change as follows:
  
  `int main(int argc, char * argv[])
   {
      ...

      QApplication app(argc, argv);
    
      ...
    
   }`

You can now use the 'setContextProperty()' function to expose the C++ wrapper for use in QML and use it as follows:

__Main.cpp__

`
QmlReportEninge *engine = new QmlReportEngine();
...
engine.setContextProperty("ReportEngine", engine);
`

__myQml.qml__

`
Button {
  id: print
  onClicked: {
    ReportEngine.setReportQuery("SELECT * FROM Payroll) //This will set the query for the QSqlQueryModel inside ReportEngine
    ReportEngine.addVariable("monthFilter", Date().getMonth) //You can add external variables here
    ReportEngine.reportFromFile("/path/to/template.lrxml") //Load the report template from file or use reportFromString(str)
    ReportEngine.previewReport() //Show a preview of the report
  }
}
`
