#include "Arduino.h"
#include <QtDebug>
#include <qsqlquery.h>

Arduino::Arduino(){
    foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        qDebug() << "Port name " << serial_port_info.portName();
        qDebug() << "Vendor " << serial_port_info.vendorIdentifier();
        qDebug() << "Product" << serial_port_info.productIdentifier();
    }
}

Arduino::~Arduino(){

}

int Arduino::connect_arduino(){
    QSerialPort * port;
    port = NULL;
    foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasVendorIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_product_id){
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << serial_port_info.portName();
            }
        }
    }
    qDebug() << "arduino_port_name is : " << arduino_port_name;
    port = new QSerialPort(arduino_port_name);
    if(arduino_is_available){
        port->setPortName(arduino_port_name);
        port->open(QSerialPort::ReadWrite);
        qDebug() << "test";
        port->setBaudRate(QSerialPort::Baud9600);
        port->setDataBits(QSerialPort::Data8);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);
        port->setFlowControl(QSerialPort::NoFlowControl);
    }
    /*if(arduino_is_available){
        serial->setPortName(arduino_port_name);
        serial->open(QSerialPort::ReadWrite);
        qDebug() << "test";
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
    }*/
    serial = port;
    return 0;
}

int Arduino::close_arduino(){
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray Arduino::read_from_arduino(){
    if(serial->isReadable()){
        data = serial->readAll();
        return data;
    }
}

int Arduino::write_to_arduino(QByteArray d){
    if(serial->isWritable()){
        serial->write(d);
        return 1;
    }
    else{
        qDebug();
        return 0;
    }
}

bool Arduino::Access(){
    bool test = false;

    QSqlQuery query;
    query.prepare("SELECT * FROM STAFF");
    query.exec();
    while((!test)&&(query.next())){
        if(query.value(0).toString() == code){
            test = true;
            qDebug() << code;
        }
        qDebug() << query.value(0).toString();
    }
    return test;
}

QSerialPort * Arduino::getserial(){
    return this->serial;
}

QString Arduino::getarduino_port_name(){
    return arduino_port_name;
}



