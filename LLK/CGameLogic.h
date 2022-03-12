#pragma once
#include"global.h"

class CGameLogic
{
public:
	void InitMap(int anMap[][4]);
	bool IsLink(int anMap[][4], Vertex v1, Vertex v2);
	void Clear(int anMap[][4], Vertex v1, Vertex v2);
};

