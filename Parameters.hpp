/* 
 * File:   Parameters.hpp
 * Author: Rajesh
 *
 * Created on March 8, 2016, 8:19 PM
 */

#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

class Parameters {
public:

  static QPointF leftBtnPressPoint;
  static QPointF leftBtnReleasePoint;
  static QPointF translate;  
};

QPointF Parameters::leftBtnPressPoint = QPointF(0, 0);
QPointF Parameters::leftBtnReleasePoint = QPointF(0, 0);
QPointF Parameters::translate = QPointF(0, 0);

#endif /* PARAMETERS_HPP */

