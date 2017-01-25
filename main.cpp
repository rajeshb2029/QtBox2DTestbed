/*
 * File:   main.cpp
 * Author: Rajesh
 *
 * Created on March 8, 2016, 3:08 AM
 */

#include <QApplication>
#include <QtWidgets/QMainWindow>
//#include "GraphicsViewWidget5.hpp"
#include "GraphicsViewWidget6.hpp"
#include "Parameters.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

//  Parameters::init();
//  GraphicsViewWidget5 *widget = new GraphicsViewWidget5;
  GraphicsViewWidget6 *widget = new GraphicsViewWidget6;
  
  
  QMainWindow mainWindow;
  mainWindow.setCentralWidget(widget);  
  mainWindow.setWindowTitle("Graphics View Widget");
  mainWindow.show();

  return app.exec();
}
