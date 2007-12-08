#include "realrect.h"

//constructors
RealRect::RealRect()  { l = 0; r=100; b=0; t=100; }
 
RealRect::RealRect(float left, float right, float bottom, float top)
{ l = left; r=right; b=bottom; t=top; }

void RealRect::set(float left, float right, float bottom, float top)
{ l=left; r=right; b=bottom; t=top; }
