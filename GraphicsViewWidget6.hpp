/* 
 * File:   GraphicsViewWidget6.hpp
 * Author: Rajesh
 *
 * Created on March 8, 2016, 10:22 PM
 */

#ifndef GRAPHICSVIEWWIDGET6_HPP
#define GRAPHICSVIEWWIDGET6_HPP

#include <iostream>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QKeyEvent>
#include <Box2D/Box2D.h>
#include "PhysicsWorld.hpp"
#include "Parameters.hpp"

class GraphicsViewWidget6 : public QGraphicsView {
public:
  PhysicsWorld *world;

  int sceneWidth, sceneHeight;
  int windowWidth, windowHeight;
  bool boardTranslateMode;

  GraphicsViewWidget6(QWidget *parent = 0) : QGraphicsView(parent) {

    windowWidth = 1000;
    windowHeight = 1000;
    
    boardTranslateMode = false;    
    
    world = new PhysicsWorld(windowWidth, windowHeight);    

    this->setScene(world->scene);
    this->setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setRenderHint(QPainter::Antialiasing);
    this->setTransformationAnchor(AnchorUnderMouse);
    this->setMinimumSize(windowWidth, windowHeight);
    this->setWindowTitle("Graphics View Widget");
  }

  void keyPressEvent(QKeyEvent *event) override {
    switch (event->key()) {
      case Qt::Key_Escape:
        QApplication::quit();
        break;
      case Qt::Key_Alt:
        boardTranslateMode = true;
        break;
      case Qt::Key_S:
        togglePointerMode();
        break;
    }
  }
  
  void keyReleaseEvent(QKeyEvent* event) override {
    switch(event->key()) {
      case Qt::Key_Alt:
        boardTranslateMode = false;
        break;
    }
  }


  void wheelEvent(QWheelEvent* event) override {
    if (event->delta() > 0) {
      zoomIn();
    } else {
      zoomOut();
    }
  }

  void scaleView(qreal scaleFactor) {
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
      return;

    this->scale(scaleFactor, scaleFactor);
  }

  void zoomIn() {
    scaleView(qreal(1.1));
  }

  void zoomOut() {
    scaleView(1 / qreal(1.1));
  }
  
  void togglePointerMode() {    
    boardTranslateMode = !boardTranslateMode;
    this->setDragMode(boardTranslateMode ? QGraphicsView::ScrollHandDrag : QGraphicsView::RubberBandDrag);
//    this->setInteractive(boardTranslateMode ? true : false);
  }  
  
  void mousePressEvent(QMouseEvent* event) {    
    std::cout << "MouseL press: " << event->pos().x() << " " << event->pos().y() << std::endl;
    QPointF scenePos = mapToScene(event->pos());
    std::cout << "MouseL scene press: " << scenePos.x() << " " << scenePos.y() << std::endl;
    Parameters::leftBtnPressPoint = scenePos;
    QGraphicsView::mousePressEvent(event);
  }
  
  void mouseReleaseEvent(QMouseEvent* event) {    
    std::cout << "MouseL release: " << event->pos().x() << " " << event->pos().y() << std::endl;
    QPointF scenePos = mapToScene(event->pos());
    std::cout << "MouseL scene release: " << scenePos.x() << " " << scenePos.y() << std::endl;
    Parameters::leftBtnReleasePoint = scenePos;
    Parameters::translate = Parameters::leftBtnReleasePoint - Parameters::leftBtnPressPoint;
    std::cout << "MouseL translate: " << Parameters::translate.x() << " " << Parameters::translate.y() << std::endl;    
    QGraphicsView::mouseReleaseEvent(event);
  }

};

#endif /* GRAPHICSVIEWWIDGET6_HPP */

