/* 
 * File:   DrawBoard.hpp
 * Author: Rajesh
 *
 * Created on March 7, 2016, 11:19 PM
 */

#ifndef DRAWBOARD_HPP
#define DRAWBOARD_HPP

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QWidget>
#include <QtCore/QPointF>
#include <QtCore/QList>
#include <QtGui/QBrush>
#include <Box2D/Box2D.h>
#include "CircularNode.hpp"
#include "PolygonNode.hpp"
#include "Parameters.hpp"

class DrawBoard : public QGraphicsScene {
public:
  QList<CircularNode*> circleNodes;
  CircularNode* cnode;
  PolygonNode* pnode;
  int sceneWidth, sceneHeight;
  int sceneBoundary;
  b2World *world;
  QPointF LT, RT, LB, RB;
  int timerId;
  int timeStep;
  int velocity;
  int radius;
  int N;

  DrawBoard(QWidget *parent = 0) : QGraphicsScene(parent) {
    sceneWidth = 1000;
    sceneHeight = 1000;
    sceneBoundary = 50;
    timeStep = 10;
    radius = 5;
    velocity = 10;
    N = 100; // max=2500

    this->setSceneRect(-sceneWidth / 2 - sceneBoundary, -sceneHeight / 2 - sceneBoundary,
            sceneWidth + 2 * sceneBoundary, sceneHeight + 2 * sceneBoundary);
    this->setBackgroundBrush(Qt::black);

    timerId = startTimer(timeStep);

    createPhysicsWorld();

    addPhysicsBodies();
//    drawBodies();
  }

  void addPhysicsBodies() {
    b2Vec2 pos;
//    qreal x, y;    
//    x = -sceneWidth/2+radius;
//    y = sceneHeight/2-radius;
    for (int i = 0; i < N; i++) {
//      pos = getSeqPosition(x, y);
//      x = pos.x;
//      y = pos.y;

      pos = getRandomPosition();
//      std::cout << x << " " << y << std::endl;      
      b2Vec2 vel((float) qrand() / RAND_MAX - 0.5, (float) qrand() / RAND_MAX - 0.5);
      vel.Normalize();
      vel *= velocity;
//      std::cout << vx << " " << vy << std::endl;

      CircularNode *node = new CircularNode(pos, radius, QColor("#c56c00"), world);
      node->setVel(vel.x, vel.y);
      circleNodes.append(node);
      this->addItem(node);
    }
    
    pnode = new PolygonNode(b2Vec2(0, 0), 100, 100, QColor("#c56c00"), world);
    pnode->setVel(0, -2);
    this->addItem(pnode);
    
    cnode = new CircularNode(b2Vec2(200, 200), 50, QColor("#c56c00"), world);
    cnode->setVel(2, 0);
    this->addItem(cnode);
  }

  b2Vec2 getSeqPosition(qreal x, qreal y) {
    x += 2 * radius;
    if (x > sceneWidth / 2) {
      x -= sceneWidth;
      y -= 2 * radius;
    }
    return b2Vec2(x, y);
  }

  b2Vec2 getRandomPosition() {
    qreal x, y;
    x = ((float) qrand() / RAND_MAX - 0.5) * sceneWidth;
    y = ((float) qrand() / RAND_MAX - 0.5) * sceneHeight;
    return b2Vec2(x, y);
  }

  void drawBorders() {

    QPen outlinePen(Qt::red);
    this->addLine(LT.x(), LT.y(), RT.x(), RT.y(), outlinePen);
    this->addLine(LT.x(), LT.y(), LB.x(), LB.y(), outlinePen);
    this->addLine(LB.x(), LB.y(), RB.x(), RB.y(), outlinePen);
    this->addLine(RB.x(), RB.y(), RT.x(), RT.y(), outlinePen);

    this->addLine(LB.x(), 0, RB.x(), 0, outlinePen);
    this->addLine(0, LT.y(), 0, LB.y(), outlinePen);
  }

  void drawBodies() {
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::red);

    int width = 100;
    int height = 100;

    this->addRect(-width / 2, -height / 2, width, height, outlinePen, blueBrush);
    this->addRect(-sceneWidth / 2, -sceneHeight / 2, width, height, outlinePen, blueBrush);
    this->addRect(sceneWidth / 2 - width, -sceneHeight / 2, width, height, outlinePen, blueBrush);
    this->addRect(-sceneWidth / 2, sceneHeight / 2 - height, width, height, outlinePen, blueBrush);
    this->addRect(sceneWidth / 2 - width, sceneHeight / 2 - height, width, height, outlinePen, blueBrush);
  }

  void createPhysicsWorld() {
    world = new b2World(b2Vec2(0.0, 0.0));    
    createWorldBoundaries();
    drawBorders();
  }

  void createWorldBoundaries() {

    LT = QPointF(-sceneWidth / 2, -sceneHeight / 2);
    RT = QPointF(sceneWidth / 2, -sceneHeight / 2);
    LB = QPointF(-sceneWidth / 2, sceneHeight / 2);
    RB = QPointF(sceneWidth / 2, sceneHeight / 2);
//    std::cout << RT.x() << " " << RT.y() << std::endl;

    b2EdgeShape eshape;
    b2FixtureDef fd;
    fd.restitution = 1.0;
    b2BodyDef bdf;
    bdf.type = b2_staticBody;

    eshape.Set(b2Vec2(LT.x(), LT.y()), b2Vec2(RT.x(), RT.y()));
    fd.shape = &eshape;
    b2Body* body1 = world->CreateBody(&bdf);
    body1->CreateFixture(&fd);

    eshape.Set(b2Vec2(LT.x(), LT.y()), b2Vec2(LB.x(), LB.y()));
    fd.shape = &eshape;
    b2Body* body2 = world->CreateBody(&bdf);
    body2->CreateFixture(&fd);

    eshape.Set(b2Vec2(LB.x(), LB.y()), b2Vec2(RB.x(), RB.y()));
    fd.shape = &eshape;
    b2Body* body3 = world->CreateBody(&bdf);
    body3->CreateFixture(&fd);

    eshape.Set(b2Vec2(RT.x(), RT.y()), b2Vec2(RB.x(), RB.y()));
    fd.shape = &eshape;
    b2Body* body4 = world->CreateBody(&bdf);
    body4->CreateFixture(&fd);
  }

  void timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    world->Step(timeStep / 100.0, 10, 10);
    world->SetContinuousPhysics(true);

    for (CircularNode *node : circleNodes) {
      node->advance(timeStep);
    }
    pnode->advance(timeStep);
    cnode->advance(timeStep);    
  }

};

#endif /* DRAWBOARD_HPP */

