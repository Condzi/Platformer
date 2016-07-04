#include "Frame.hpp"



Frame::Frame()
{
}


Frame::~Frame()
{
}

bool CutValues::operator==(const CutValues & a)
{
	return (x == a.x &&
		y == a.y &&
		width == a.width &&
		height == a.height)
		? true : false;
}

bool CutValues::operator!=(const CutValues & a)
{
	return (operator==(a))?false:true;
}
