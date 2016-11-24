#ifndef __COBSTACLE_HPP
#define __COBSTACLE_HPP

#include "CEntity.hpp"

class CObstacle : public CEntity
{
	private :
		bool m_movable;
	
	public :
		CObstacle();
		~CObstacle();
};


#endif //__COBSTACLE_HPP

