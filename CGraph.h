#pragma once
#include <wtypes.h>
#include <atltypes.h>
class CGraph
{
public:
	UINT m_nDrawType;
	CPoint m_ptOrign;
	CPoint m_ptEnd;
	CGraph(UINT m_nDrawType, CPoint m_ptOrigin, CPoint m_ptEnd);
};

