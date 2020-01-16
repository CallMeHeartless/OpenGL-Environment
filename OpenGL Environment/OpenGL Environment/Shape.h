/***********************
 * File:		Shape.h
 * Description: Header file for the Animator component
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __SHAPE_H__
#define __SHAPE_H__

// Local Includes
#include "GameObject.h"

enum EShapeTypes {
	eShapeCircle = 0,
	eShapeTriangle,
	eShapeSquare,
	eShapeHexagon
};

class Shape : public GameObject {

	public:
		static std::shared_ptr<Shape> CreateShape(EShapeTypes _eType);

		EShapeTypes m_eShapeType;
};

#endif // !__SHAPE_H__

