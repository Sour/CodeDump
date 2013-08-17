#include "stdafx.h"
//#include "Terrain.h"
//
//void Terrain::setupTerrain(RECT windowRect)
//{
//	Point p;
//	p.x = 0;
//	p.y = 768;
//	points.push_back(p);
//
//	p.x = 1080;
//	p.y = 768;
//	points.push_back(p);
//
//}
//
//void Terrain::applyFractals()
//{
//	if ( points.size() - 1 >= 1000 )
//		return;
//
//	int tx, ty, tx1, ty1, midx, midy, miny;
//	float complexity = 1;
//	Point tp;
//	float range = 1;
//	int mass = 500;
//	std::vector<Point>::iterator it = points.begin();
//
//		for ( it; it != points.end(); ++it )
//		{
//			tx = points[it].x;
//			ty = points[it].y;
//
//			tx1 = points[it + 1].x;
//			ty1 = points[it + 1].y;
//
//			midx = ( tx + tx1 ) / 2;
//			midy = ( ty + ty1 ) / 2;
//			miny = ty;
//
//			tp.x = midx;
//			tp.y = miny + ( rand() % (int)floor( range * mass * 2 + 1 ) );
//
//			if( abs( tp.y - miny ) > ( mass * range * 0.7 ) )
//				tp.y = tp.y * 0.4;
//
//			points.insert( points.begin() + it + 1, tp );
//			
//
//			range *+ 0.3;
//		}
//
//
//}