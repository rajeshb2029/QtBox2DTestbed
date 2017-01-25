/* 
 * File:   PhysicsWorld.hpp
 * Author: Rajesh
 *
 * Created on March 8, 2016, 9:08 PM
 */

#ifndef PHYSICSWORLD_HPP
#define PHYSICSWORLD_HPP

#include <QtWidgets/QGraphicsScene>
#include <Box2D/Box2D.h>
#include "CircularNode.hpp"
#include "PolygonNode.hpp"
#include "Parameters.hpp"

class PhysicsWorld : public QWidget {
public:
  b2World* world;
  QPointF LT, RT, LB, RB;
  int worldWidth;
  int worldHeight;
  int sceneBoundary;
  QGraphicsScene* scene;

  QList<CircularNode*> circleNodes;
  CircularNode* cnode;
  PolygonNode* pnode;

  int timerId;
  int timeStep;
  int velocity;
  int radius;
  int N;

  PhysicsWorld(int worldWidth, int worldHeight, QWidget *parent = 0) : QWidget(parent) {
    this->worldWidth = worldWidth;
    this->worldHeight = worldHeight;
    sceneBoundary = 50;
    timeStep = 10;
    radius = 5;
    velocity = 10;
    N = 500; // max=2500

    world = new b2World(b2Vec2(0.0, 0.0));
    createWorldBoundaries();

    createGraphicsScene();
    drawBorders();

    addPhysicsBodies();

    timerId = startTimer(timeStep);
  }

  void createGraphicsScene() {
    scene = new QGraphicsScene;
    scene->setSceneRect(-worldWidth / 2 - sceneBoundary, -worldHeight / 2 - sceneBoundary,
            worldWidth + 2 * sceneBoundary, worldHeight + 2 * sceneBoundary);
    scene->setBackgroundBrush(Qt::black);
  }

  void createWorldBoundaries() {

    LT = QPointF(-worldWidth / 2, -worldHeight / 2);
    RT = QPointF(worldWidth / 2, -worldHeight / 2);
    LB = QPointF(-worldWidth / 2, worldHeight / 2);
    RB = QPointF(worldWidth / 2, worldHeight / 2);

    b2EdgeShape eshape;
    b2FixtureDef fd;
    fd.restitution = 0.0;
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

  void drawBorders() {
    QPen outlinePen(Qt::red);
    scene->addLine(LT.x(), LT.y(), RT.x(), RT.y(), outlinePen);
    scene->addLine(LT.x(), LT.y(), LB.x(), LB.y(), outlinePen);
    scene->addLine(LB.x(), LB.y(), RB.x(), RB.y(), outlinePen);
    scene->addLine(RB.x(), RB.y(), RT.x(), RT.y(), outlinePen);

    scene->addLine(LB.x(), 0, RB.x(), 0, outlinePen);
    scene->addLine(0, LT.y(), 0, LB.y(), outlinePen);
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
      scene->addItem(node);
    }

    pnode = new PolygonNode(b2Vec2(0, 0), 100, 100, QColor("#c56c00"), world);
    pnode->setVel(0, -2);
    pnode->setAngularVelocity(-10);
    scene->addItem(pnode);

    cnode = new CircularNode(b2Vec2(200, 200), 50, QColor("#c56c00"), world);
    cnode->setVel(2, 0);
    scene->addItem(cnode);
  }

  b2Vec2 getSeqPosition(qreal x, qreal y) {
    x += 2 * radius;
    if (x > worldWidth / 2) {
      x -= worldWidth;
      y -= 2 * radius;
    }
    return b2Vec2(x, y);
  }

  b2Vec2 getRandomPosition() {
    qreal x, y;
    x = ((float) qrand() / RAND_MAX - 0.5) * worldWidth;
    y = ((float) qrand() / RAND_MAX - 0.5) * worldHeight;
    return b2Vec2(x, y);
  }

//  void drawWorldBodies() {
//    for(b2Body* body : world->GetBodyList()) {
//      drawShape(body, QColor(Qt::white), QBrush(Qt::red));
//    }
//  }
  
//  void drawShape(b2Body* body, QColor outlineColor, QBrush brush) {
//    switch (body->GetFixtureList()->GetType()) {
//      case b2Shape::e_circle:      
//        b2CircleShape *circle = (b2CircleShape*) fixture.getShape();
//        // Vec2 center = Mul(xf, circle.m_p);
//        b2Transform.mulToOutUnsafe(xf, circle.m_p, center);
//        float radius = circle.m_radius;
//        xf.q.getXAxis(axis);
//        debugDraw.drawSolidCircle(center, radius, NULL, color);      
//        break;
//
//      case b2Shape::e_polygon:
//        b2PolygonShape *poly = (b2PolygonShape*) fixture.getShape();
//        int vertexCount = poly.m_count;
//        assert(vertexCount <= Settings.maxPolygonVertices);
//        b2Vec2[] vertices = tlvertices.get(Settings.maxPolygonVertices);
//
//        for (int i = 0; i < vertexCount; ++i) {
//          // vertices[i] = Mul(xf, poly.m_vertices[i]);
//          b2Transform.mulToOutUnsafe(xf, poly.m_vertices[i], vertices[i]);
//        }
//        debugDraw.drawSolidPolygon(vertices, vertexCount, color);      
//        break;
//        
//      case b2Shape::e_edge:
//        b2EdgeShape edge = (b2EdgeShape*) fixture.getShape();
//        b2Transform.mulToOutUnsafe(xf, edge.m_vertex1, v1);
//        b2Transform.mulToOutUnsafe(xf, edge.m_vertex2, v2);
//        debugDraw.drawSegment(v1, v2, Color3f.GREEN);      
//        break;
//
//      default:
//        break;
//    }
//  }
//
//  void drawShape2(b2Fixture fixture, b2Transform xf, QColor color) {
//    switch (fixture.getType()) {
//      case b2Shape::e_circle:      
//        b2CircleShape *circle = (b2CircleShape*) fixture.getShape();
//        // Vec2 center = Mul(xf, circle.m_p);
//        b2Transform.mulToOutUnsafe(xf, circle.m_p, center);
//        float radius = circle.m_radius;
//        xf.q.getXAxis(axis);
//        debugDraw.drawSolidCircle(center, radius, NULL, color);      
//        break;
//
//      case b2Shape::e_polygon:
//        b2PolygonShape *poly = (b2PolygonShape*) fixture.getShape();
//        int vertexCount = poly.m_count;
//        assert(vertexCount <= Settings.maxPolygonVertices);
//        b2Vec2[] vertices = tlvertices.get(Settings.maxPolygonVertices);
//
//        for (int i = 0; i < vertexCount; ++i) {
//          // vertices[i] = Mul(xf, poly.m_vertices[i]);
//          b2Transform.mulToOutUnsafe(xf, poly.m_vertices[i], vertices[i]);
//        }
//        debugDraw.drawSolidPolygon(vertices, vertexCount, color);      
//        break;
//        
//      case b2Shape::e_edge:
//        b2EdgeShape edge = (b2EdgeShape*) fixture.getShape();
//        b2Transform.mulToOutUnsafe(xf, edge.m_vertex1, v1);
//        b2Transform.mulToOutUnsafe(xf, edge.m_vertex2, v2);
//        debugDraw.drawSegment(v1, v2, Color3f.GREEN);      
//        break;
//
//      default:
//        break;
//    }
//  } // end method drawShape

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

#endif /* PHYSICSWORLD_HPP */

