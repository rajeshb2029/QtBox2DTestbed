/* 
 * File:   CircularNode.hpp
 * Author: Rajesh
 *
 * Created on March 7, 2016, 11:37 PM
 */

#ifndef CIRCULARNODE_HPP
#define CIRCULARNODE_HPP

#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QBrush>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <Box2D/Box2D.h>

class CircularNode : public QGraphicsItem {
public:
  b2Body *body;
  b2Vec2 pos;
  b2Vec2 vel;
  qreal radius;
  QColor color;
  
  b2Vec2 leftBtnPressPoint, rightBtnPressPoint;
  bool leftBtnPress, rightBtnPress;
  int transx, transy;
  
  CircularNode(b2Vec2 pos, qreal radius, QColor color, b2World* world) {
    this->radius = radius;
    this->color = color;
    this->pos = pos;
    createCirclePhysicsBody(world);
    setPos(pos.x, pos.y);
    
    this->setFlags(QGraphicsItem::ItemIsMovable);
  }
  
  QRectF boundingRect() const {
    return QRectF(-radius, -radius, 2*radius, 2*radius);
  }

  void setVel(qreal x, qreal y) {
    vel.x = x;
    vel.y = y;
    body->SetLinearVelocity(b2Vec2(vel.x, vel.y));
  }
  
  void paint(QPainter *qp, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override {
    Q_UNUSED(option);
    Q_UNUSED(widget);
            
    qp->setPen(QColor("#d4d4d4"));
//    qp->setBrush(QBrush("#c56c00"));
    qp->setBrush(QBrush(color));    
    qp->setOpacity(0.5);
    qp->drawEllipse(-radius, -radius, 2*radius, 2*radius);    
  }
  
  void advance(int step) {
    Q_UNUSED(step);
    b2Vec2 vec = body->GetWorldCenter();
    this->pos.Set(vec.x, vec.y);
    setPos(vec.x, vec.y);
  }
  
  void createCirclePhysicsBody(b2World* world) {
    
    b2CircleShape cshape;
    cshape.m_radius = radius;

    b2FixtureDef fd;
    fd.density = 1.0;
    fd.restitution = 1.0;
    fd.shape = &cshape;

    b2BodyDef bdf;
    bdf.type = b2_dynamicBody;
    bdf.position.Set(pos.x, pos.y);

    body = world->CreateBody(&bdf);
    body->CreateFixture(&fd);
    
//    b2Vec2 vec = body->GetWorldCenter();
//    std::cout << vec.x << " " << vec.y << std::endl;            
  }  
  
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override {    
    QGraphicsItem::mousePressEvent(event);
    switch(event->button()) {
      case Qt::LeftButton:
        leftBtnPress = true;
        leftBtnPressPoint.Set(event->pos().x(), event->pos().y());
        std::cout << "MouseL press: " << event->pos().x() << " " << event->pos().y() << std::endl;
        break;
        
      default:
        break;
    }
    update();
  }
  
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {    
    QGraphicsItem::mouseReleaseEvent(event);
    switch(event->button()) {
      case Qt::LeftButton:
        leftBtnPress = false;
        transx = event->pos().x() - leftBtnPressPoint.x;
        transy = event->pos().y() - leftBtnPressPoint.y;
        std::cout << transx << " " << transy << std::endl;
        std::cout << "MouseL release: " << event->pos().x() << " " << event->pos().y() << std::endl;
        break;
        
      default:
        break;
    }
    update();
  }
  
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
    QGraphicsItem::mouseMoveEvent(event);
    std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
    update();
  }

  
};

#endif /* CIRCULARNODE_HPP */

