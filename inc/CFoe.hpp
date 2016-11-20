#ifndef __CFOE_HPP
#define __CFOE_HPP

#include <random>

#include "CCharacter.hpp"

class CFoe : public CCharacter
{
	private :
		
		float m_type;

	public :
		CFoe(float type, float psX, float psY);
		~CFoe();
		
		void update(float dt, float limit);		
};

#endif //__CFOE_HPP

