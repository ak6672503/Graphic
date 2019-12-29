#include "pch.h"
#include "CGraph.h"


CGraph::CGraph(UINT m_nDrawType,CPoint m_ptOrigin,CPoint m_ptEnd)
{
	this->m_nDrawType = m_nDrawType;
	this->m_ptEnd = m_ptEnd;
	this->m_ptOrign = m_ptOrigin;
}

