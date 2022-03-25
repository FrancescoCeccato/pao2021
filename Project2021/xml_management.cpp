#include "xml_management.h"

xml_management::xml_management(){}

void xml_management::write_xml(chart* c){
    QDomElement root = chart_xml.createElement("Chart");
    chart_xml.appendChild(root);
    QDomElement title = chart_xml.createElement(QString::fromStdString(c->get_title()));
    root.appendChild(title);
    QFile chart_file("C:/Users/mstoc/Desktop/xml_test.xml");
    if(!chart_file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() <<"Non è stato possibile aprire il file";
    }else{
        QTextStream stream(&chart_file);
        stream<< chart_xml.toString();
        chart_file.close();
        qDebug() <<"Operazione conclusa";
    }
}
