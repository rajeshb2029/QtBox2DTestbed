/* 
 * File:   PolygonNode.hpp
 * Author: Rajesh
 *
 * Created on March 8, 2016, 1:47 AM
 */

#ifndef POLYGONNODE_HPP
#define POLYGONNODE_HPP

#include <QtGui/QColor>
#include <QtGui/QBrush>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <Box2D/Box2D.h>

class PolygonNode : public QGraphicsItem {
public:
  b2Body *body;
  b2Vec2 pos;  
  b2Vec2 vel;
  qreal width;
  qreal height;
  QColor color;
  
  PolygonNode(b2Vec2 pos, qreal width, qreal height, QColor color, b2World* world) {
    this->width = width;
    this->height = height;
    this->color = color;
    this->pos = pos;
    this->setRotation(0.0);
    createPolygonPhysicsBody(world);
    setPos(pos.x, pos.y);
    
    this->setFlags(QGraphicsItem::ItemIsMovable);
  }
  
  QRectF boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
  }

  void setVel(qreal x, qreal y) {
    vel.x = x;
    vel.y = y;
    body->SetLinearVelocity(b2Vec2(vel.x, vel.y));
  }
  
  void setAngularVelocity(qreal omega) {
    body->SetAngularVelocity(omega);
  }
  
  void paint(QPainter *qp, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override {
    Q_UNUSED(option);
    Q_UNUSED(widget);
            
    qp->setPen(QColor("#d4d4d4"));
//    qp->setBrush(QBrush("#c56c00"));    
    qp->setBrush(QBrush(color));    
    qp->setOpacity(0.5);    
    qp->drawRect(-width/2, -height/2, width, height);    
  }
  
  void advance(int step) {
    Q_UNUSED(step);
    b2Vec2 vec = body->GetWorldCenter();
    this->setRotation(body->GetAngle());
    setPos(vec.x, vec.y);
  }
  
  void createPolygonPhysicsBody(b2World* world) {
    
    b2PolygonShape pshape;
    pshape.SetAsBox(width/2, height/2);

    b2FixtureDef fd;
    fd.density = 1.0;
    fd.restitution = 1.0;
    fd.shape = &pshape;

    b2BodyDef bdf;
    bdf.type = b2_dynamicBody;
    bdf.position.Set(pos.x, pos.y);

    body = world->CreateBody(&bdf);
    body->CreateFixture(&fd);
    
//    b2Vec2 vec = body->GetWorldCenter();
//    std::cout << vec.x << " " << vec.y << std::endl;            
  }  
  
};

#endif /* POLYGONNODE_HPP */

