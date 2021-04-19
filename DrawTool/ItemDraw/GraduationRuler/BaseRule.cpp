#include "BaseRule.h"

BaseRule::BaseRule()
{
    initData();
}

BaseRule::~BaseRule()
{

}

double BaseRule::ScaleConverCoord(const double &scale)
{

}

double BaseRule::CoordConverScale(const double &coord)
{

}

void BaseRule::initData()
{
    m_Max = 0;
    m_Mix = 0;
    m_Length = 0;
}
