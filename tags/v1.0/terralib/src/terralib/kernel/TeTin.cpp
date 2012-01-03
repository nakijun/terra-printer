/************************************************************************************
TerraLib - a library for developing GIS applications.
Copyright � 2001-2007 INPE and Tecgraf/PUC-Rio.

This code is part of the TerraLib library.
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

You should have received a copy of the GNU Lesser General Public
License along with this library.

The authors reassure the license terms regarding the warranties.
They specifically disclaim any warranties, including, but not limited to,
the implied warranties of merchantability and fitness for a particular purpose.
The library provided hereunder is on an "as is" basis, and the authors have no
obligation to provide maintenance, support, updates, enhancements, or modifications.
In no event shall INPE and Tecgraf / PUC-Rio be held liable to any party for direct,
indirect, special, incidental, or consequential damages arising out of the use
of this library and its documentation.
*************************************************************************************/

#include "TeTin.h"
#include "TeStdFile.h"
#include "TeException.h"
#include "TeGeometryAlgorithms.h"
#include "TeUtils.h"
//#include "geo.h"

#include <iostream>
#include <fstream>
#include <algorithm>

// TeTinTriangleSet

bool
TeTinTriangleSet::loadFromFile(std::string &fileName)
{
//	Open tin triangles file
	std::string trianglesFile = fileName;
	trianglesFile += ".tpl";

	std::ifstream inStream;
	inStream.open( trianglesFile.data(), std::ios::in | std::ios::binary );

	if (! inStream.good() )
		return false;

	long laux;
//#if defined(SPRWIN) || defined(LITTLEENDIAN) - File is saved in LITTLEENDIAN
	inStream.read((char*)&laux, sizeof(long));
	long numTriangles = laux;

//	Create and std::set tin triangles std::vector
	if ( this->size () )
		this->clear ();
	this->reserve (numTriangles);

//	Read file for triangles data load
	long lineid [3];
	for (long i = 0; i < numTriangles; i++)
	{
		for (long j = 0; j < 3; j++)
		{
			if (! inStream.good() )
				return false;
			inStream.read((char*)&laux, sizeof(long));
			lineid[j] = laux;
		}
		this->add ( TeTinTriangle (lineid[0],lineid[1],lineid[2]) );
	}
	return true;
}

bool
TeTinVertexSet::loadFromFile(std::string &fileName)
{
//	Open tin vertices file
	std::string verticesFile = fileName;
	verticesFile += ".tnd";

	std::ifstream inStream;
	inStream.open( verticesFile.data(), std::ios::in | std::ios::binary );

	if (! inStream.good() )
		return false;

	long laux;
//#if defined(SPRWIN) || defined(LITTLEENDIAN) - File is saved in LITTLEENDIAN
	inStream.read((char*)&laux, sizeof(long));
	long numVertices = laux;

//	Create and std::set tin vertices std::vector
	if ( this->size () )
		this->clear ();
	this->reserve (numVertices);

//	Read file for vertices data load
	double x, y;
	double value;
	short vertexType;
	for (long i = 0; i < numVertices; i++)
	{
		if (! inStream.good() )
			return false;
		inStream.read((char*)&x, sizeof(double));
		if (! inStream.good() )
			return false;
		inStream.read((char*)&y, sizeof(double));
		if (! inStream.good() )
			return false;
		inStream.read((char*)&value, sizeof(double));
		if (! inStream.good() )
			return false;
		inStream.read((char*)&vertexType, sizeof(short));
		this->add( TeTinVertex (TeCoord2D (x,y), value,
			(TeTinVertexType) vertexType, -1 ) );
	}
	return true;
}

bool
TeTinEdgeSet::loadFromFile(std::string &fileName)
{
//	Open tin edges file
	std::string edgesFile = fileName;
	edgesFile += ".tln";

	std::ifstream inStream;
	inStream.open( edgesFile.data(), std::ios::in | std::ios::binary );

	if (! inStream.good() )
		return false;

	long laux;
//#if defined(SPRWIN) || defined(LITTLEENDIAN) - File is saved in LITTLEENDIAN
	inStream.read((char*)&laux, sizeof(long));
	long numEdges = laux;

//	Create and std::set tin edges std::vector
	if ( this->size () )
		this->clear ();
	this->reserve (numEdges);

//	Read file for edges data load
	long from, to, left, right;
	for (long i = 0; i < numEdges; i++)
	{
		if (! inStream.good() )
			return false;
		inStream.read((char*)&from, sizeof(long));
		if (! inStream.good() )
			return false;
		inStream.read((char*)&to, sizeof(long));

		if (! inStream.good() )
			return false;
		inStream.read((char*)&left, sizeof(long));
		if (! inStream.good() )
			return false;
		inStream.read((char*)&right, sizeof(long));

		this->add( TeTinEdge (from, to, left, right, NORMALEDGE) );
	}
	return true;
}


// TeTin

bool
TeTin::loadFromFile(std::string &fileName)
{
	if ( triangleSet_.loadFromFile ( fileName ) )
	{
		if ( vertexSet_.loadFromFile ( fileName ) )
		{
			if ( edgeSet_.loadFromFile ( fileName ) )
				return true;
		}
	}
	return false;
}

bool
TeTin::getLines(TeLineSet &lineSet)
{
	std::vector<TeTinEdge>::iterator i = edgeSet_.begin();
	while ( i != edgeSet_.end() )
	{
		long from = (*i).from();
		long to = (*i).to();
		TeCoord2D ptf = vertexSet_[from].location();
		TeCoord2D ptt = vertexSet_[to].location();
		i++;

		TeLine2D line;
		line.add (ptf);
		line.add (ptt);
		lineSet.add(line);
	}
	return true;
}

long
TeTin::oneEdgeWithVertex(long v)
{
	long vsize = vertexSet_.size();
	long edge;
	if (v < vsize)
	{
		TeTinVertex vv = vertexSet_[v];
		edge = vv.oneEdge();
	}
	else
		return -1;

	// Test to make sure there is no wrong index
	if ( edge != -1 )
		if ( ( edgeSet_[edge].to() == v ) ||
			 ( edgeSet_[edge].from() == v ) )
		return edge;

	//Fail safe code, must return from previous code
	static long	oldedge = 0;	// Set one edge only once

	long j = 0;
	while (j < 2)
	{
		unsigned long i;
		for (i = oldedge; i < edgeSet_.size(); i++)
		{
			long from = edgeSet_[i].from();
			long to   = edgeSet_[i].to();
			if ( from == -1 || to == -1 )
				continue;
			if (from == v || to == v)
			{
				oldedge = i;
				return i;
			}
		}
		oldedge = 0;
		j++;
	}
	return -1;
}

long
TeTin::edgeOppVertex(TeTinTriangle& t, long v)
{
	long edges[3];
	t.edges(edges[0],edges[1],edges[2]);

	for (long i = 0; i < 3; i++)
	{
		if ( edgeSet_[edges[i]].from() != v &&
		     edgeSet_[edges[i]].to()   != v )
			return edges[i];
	}
	return -1;
}

long
TeTin::vertexOppEdge(long t, long e)
{
	long edges[3];
	triangleSet_[t].edges(edges[0],edges[1],edges[2]);

	long vef(-1), vet(-1);
	unsigned long i;
	for (i = 0; i < 3; i++)
	{
		if ( edges[i] == e )
		{
			vef = edgeSet_[edges[i]].from();
			vet = edgeSet_[edges[i]].to();
			break;
		}
	}
	if ( vef == -1 )
		return -1;

	for (i = 0; i < 3; i++)
	{
		if ( edges[i] != e )
		{
			if ( vef == edgeSet_[edges[i]].from() ||
			     vet == edgeSet_[edges[i]].from() )
				return edgeSet_[edges[i]].to();
			if ( vef == edgeSet_[edges[i]].to() ||
			     vet == edgeSet_[edges[i]].to() )
				return edgeSet_[edges[i]].from();
			return -1;
		}
	}
	return -1;
}

long
TeTin::edgeWithVertexDiffFromEdge(long t, long v, long e)
{
	long edges[3];
	triangleSet_[t].edges(edges[0],edges[1],edges[2]);

	for (long i = 0; i < 3; i++)
	{
		if ( edges[i] == e )
			continue;
		if ( edgeSet_[edges[i]].from() == v ||
		     edgeSet_[edges[i]].to()   == v )
			return edges[i];
	}
	return -1;
}

bool
TeTin::vertexOppEdges(long v, std::list<long> &edges)
{
//	Find one line that contains node
	long a = oneEdgeWithVertex(v);
	if (a == -1)
		return false;

//	1. Defina td como sendo o tri�ngulo que est� � direita da aresta a e
	long td = edgeSet_[a].right(); // te como sendo o tri�ngulo que est�
	long te = edgeSet_[a].left();  // � esquerda de a,

	long ai = a; // 2. Defina ai como sendo aresta a 
	long ti = td;//    e ti como sendo o tri�ngulo td,

	long ao;
 
	if ( ti != -1 ) // 3. Se o tri�ngulo ti n�o for nulo,
	{				//    insira aresta ao de ti que n�o � diretamente
		ao = edgeOppVertex ( ti, v );// conectado a v no conjunto A,
		if (ao == -1)
			return false;
		edges.push_back (ao);
	}

	while (ti != te)// 4. Enquanto ti for diferente do tri�ngulo te,
	{
		if (ti == -1)//	4.1. Se o tri�ngulo ti � nulo (esta' na
		{			 //  borda da triangula��o) fa�a:
			ti = te; //	 4.1.1. Defina ti como sendo o tri�ngulo te,
			te = -1; //  4.1.2. Defina te como sendo nulo,
			ai = a;  //  4.1.3. Defina ai como sendo aresta a,
			if ( ti != -1 ) // 4.1.4. Se o tri�ngulo ti n�o for nulo,
			{				// insira aresta ao de ti que n�o � diretamente
				ao = edgeOppVertex ( ti, v );// conectado a v
				if (ao == -1)
					return false;
				edges.push_back (ao); // a v no conjunto A,
			}
			continue;//	 4.1.5. Retorne a 4.
		}

		long aaux = edgeWithVertexDiffFromEdge ( ti, v, ai );// 4.2. Defina a
		if (aaux == -1)	 // aresta aaux do tri�ngulo ti que conecta o
			return false;// v�rtice v e � diferente de ai,

		long taux;
		if (edgeSet_[aaux].right() == ti) // 4.3. Defina taux como sendo  
			taux = edgeSet_[aaux].left();//  o tri�ngulo que compartilha
		else if (edgeSet_[aaux].left() == ti)// a aresta aaux com ti,
			taux = edgeSet_[aaux].right();
		else
			return false;

		ti = taux;// 4.4. Defina ti como sendo o tri�ngulo taux e ai 
		ai = aaux;//	  como sendo aresta aaux,

		if ( ti != -1 )// 4.5. Se o tri�ngulo ti n�o for nulo, insira
		{			   //      aresta ao de ti que n�o � diretamente
			ao = edgeOppVertex ( ti, v ); // conectado a v
			if (ao == -1)							// no conjunto A,
				return false;
			edges.push_back (ao);
		}
	} // 4.6. Retorne a 4.
	return true;
}

bool
TeTin::vertexEdges(long v, std::list<long> &edges)
{
//	Find one line that contains node
	long a = oneEdgeWithVertex(v);
	if (a == -1)
		return false;

//	1. Defina td como sendo o tri�ngulo que est� � direita da aresta a e
	long td = edgeSet_[a].right(); // te como sendo o tri�ngulo que est�
	long te = edgeSet_[a].left();  // � esquerda de a,

	long ai = a; // 2. Defina ai como sendo aresta a 
	long ti = td;//    e ti como sendo o tri�ngulo td,

	edges.push_back (ai);//	3. Insira a aresta ai no conjunto A,

	while (ti != te)//	4. Enquanto ti for diferente do tri�ngulo te,
	{
		if (ti == -1)
		{// 4.1. Se o tri�ngulo ti � nulo (esta' na borda da triangula��o) fa�a:
			ti = te;// 4.1.1. Defina ti como sendo o tri�ngulo te,
			te = -1;// 4.1.2. Defina te como sendo nulo,
			ai = a;// 4.1.3. Defina ai como sendo aresta a,
			continue;// 4.1.4. Retorne a 4.
		}

		long aaux = edgeWithVertexDiffFromEdge ( ti, v, ai );// 4.2. Defina a
		if (aaux == -1)	 // aresta aaux do tri�ngulo ti que conecta o
			return false;// v�rtice v e � diferente de ai,

		long taux;
		if (edgeSet_[aaux].right() == ti) // 4.3. Defina taux como sendo  
			taux = edgeSet_[aaux].left();//  o tri�ngulo que compartilha
		else if (edgeSet_[aaux].left() == ti)// a aresta aaux com ti,
			taux = edgeSet_[aaux].right();
		else
			return false;

		ti = taux;// 4.4. Defina ti como sendo o tri�ngulo taux e ai 
		ai = aaux;//	  como sendo aresta aaux,

		edges.push_back (ai);// 4.5. Se o tri�ngulo ti n�o for nulo, insira
	} // 4.6. Retorne a 4.
	return true;
}

bool
TeTin::vertexOppVertices(long v, std::list<long> &vertices)
{
//	Find one line that contains node
	long a = oneEdgeWithVertex(v);
	if (a == -1)
		return false;

//	1. Defina td como sendo o tri�ngulo que est� � direita da aresta a e
	long td = edgeSet_[a].right(); // te como sendo o tri�ngulo que est�
	long te = edgeSet_[a].left();  // � esquerda de a,

	long ai = a; // 2. Defina ai como sendo aresta a 
	long ti = td;//    e ti como sendo o tri�ngulo td,

	long vi = edgeSet_[a].from();// 3. Insira o v�rtice diferente de v
	if (vi == v)				// conectado � aresta ai no conjunto V,
		vi = edgeSet_[a].to();
	vertices.push_back (vi);

	while (ti != te)// 4. Enquanto ti for diferente do tri�ngulo te,
	{
		if (ti == -1)// 4.1. Se o tri�ngulo ti � nulo (esta' na borda 
		{			 // da triangula��o) fa�a:
			ti = te; //	4.1.1. Defina ti como sendo o tri�ngulo te,
			te = -1; //	4.1.2. Defina te como sendo nulo,
			ai = a;  //	4.1.3. Defina ai como sendo aresta a,
			continue;//	4.1.4. Retorne a 4.
		}

		long aaux = edgeWithVertexDiffFromEdge ( ti, v, ai );// 4.2. Defina a
		if (aaux == -1)	 // aresta aaux do tri�ngulo ti que conecta o
			return false;// v�rtice v e � diferente de ai,

		long taux;
		if (edgeSet_[aaux].right() == ti) // 4.3. Defina taux como sendo  
			taux = edgeSet_[aaux].left();//  o tri�ngulo que compartilha
		else if (edgeSet_[aaux].left() == ti)// a aresta aaux com ti,
			taux = edgeSet_[aaux].right();
		else
			return false;

		ti = taux;// 4.4. Defina ti como sendo o tri�ngulo taux e ai 
		ai = aaux;//	  como sendo aresta aaux,

		vi = edgeSet_[ai].from();//	4.5. Insira o v�rtice diferente
		if (vi == v)	// de v conectado � aresta ai no conjunto V,
			vi = edgeSet_[ai].to();
		vertices.push_back (vi);
	}//	4.6. Retorne a 4.
	return true;
}

bool
TeTin::vertexTriangles(long v, std::list<long> &triangles)
{
//	Find one line that contains node
	long a = oneEdgeWithVertex(v);
	if (a == -1)
		return false;

//	1. Defina td como sendo o tri�ngulo que est� � direita da aresta a e
	long td = edgeSet_[a].right(); // te como sendo o tri�ngulo que est�
	long te = edgeSet_[a].left();  // � esquerda de a,

	long ai = a; // 2. Defina ai como sendo aresta a 
	long ti = td;//    e ti como sendo o tri�ngulo td,
 
	if ( ti != -1 ) // 3. Se o tri�ngulo ti n�o for nulo,
	{				//    insira ti no conjunto T,
		triangles.push_back (ti);
	}

	while (ti != te)// 4. Enquanto ti for diferente do tri�ngulo te,
	{
		if (ti == -1)//	4.1. Se o tri�ngulo ti � nulo (esta' na
		{			 //  borda da triangula��o) fa�a:
			ti = te; //	 4.1.1. Defina ti como sendo o tri�ngulo te,
			te = -1; //  4.1.2. Defina te como sendo nulo,
			ai = a;  //  4.1.3. Defina ai como sendo aresta a,
			if ( ti != -1 ) // 4.1.4. Se o tri�ngulo ti n�o for nulo,
			{				// insira ti no conjunto T,
				triangles.push_back (ti);
			}
			continue;//	 4.1.5. Retorne a 4.
		}

		long aaux = edgeWithVertexDiffFromEdge ( ti, v, ai );// 4.2. Defina a
		if (aaux == -1)	 // aresta aaux do tri�ngulo ti que conecta o
			return false;// v�rtice v e � diferente de ai,

		long taux;
		if (edgeSet_[aaux].right() == ti) // 4.3. Defina taux como sendo  
			taux = edgeSet_[aaux].left();//  o tri�ngulo que compartilha
		else if (edgeSet_[aaux].left() == ti)// a aresta aaux com ti,
			taux = edgeSet_[aaux].right();
		else
			return false;

		ti = taux;// 4.4. Defina ti como sendo o tri�ngulo taux e ai 
		ai = aaux;//	  como sendo aresta aaux,

		if ( ti != -1 )// 4.5. Se o tri�ngulo ti n�o for nulo, insira
		{			   //      aresta ao de ti que n�o � diretamente
			triangles.push_back (ti);
		}
	} // 4.6. Retorne a 4.
	return true;
}

bool
TeTin::vertexOppEdges(long v, std::list<long> &triset, std::list<long> &edges)
{
	std::list<long>::iterator tii;
	for (tii = triset.begin(); tii != triset.end(); tii++)
	{
		long ti = *tii;
		long nedge = this->edgeOppVertex(ti, v);
		edges.push_back(nedge);
	}
	return true;
}

long
TeTin::oneTriangleWithVertex(long v)
{
//	Find one line that contains node
	long a = oneEdgeWithVertex(v);
	if (a == -1)
		return -1;

	long td = edgeSet_[a].right();
	if ( td == -1 )
		return edgeSet_[a].left();
	else
		return td;
}

bool
TeTin::triangleContainsPoint(TeTinTriangle& t, TeCoord2D& pt) 
{
	double	totalArea, triangleArea;
	TeCoord2D	vert[3];

	this->trianglePoints(t, vert[0], vert[1], vert[2]);

//	Calculate the base triangle area
	triangleArea = fabs(( (vert[1].x() - vert[0].x()) *
		              (vert[2].y() - vert[0].y()) ) -
	 	            ( (vert[2].x() - vert[0].x()) *
	 	              (vert[1].y() - vert[0].y()) ));
	triangleArea *= 1.00001;
	totalArea = fabs(( (vert[0].x() - pt.x()) * (vert[1].y() - pt.y()) ) -
		         ( (vert[1].x() - pt.x()) * (vert[0].y() - pt.y()) ));
	if (totalArea > triangleArea)
		return false;

	totalArea += fabs(( (vert[1].x() - pt.x()) * (vert[2].y() - pt.y()) ) -
		          ( (vert[2].x() - pt.x()) * (vert[1].y() - pt.y()) ));
	if (totalArea > triangleArea) 
		return false;

	totalArea += fabs(( (vert[0].x() - pt.x()) * (vert[2].y() - pt.y()) ) -
		          ( (vert[2].x() - pt.x()) * (vert[0].y() - pt.y()) ));
	if (totalArea > triangleArea) 
		return false;

	return true;
}

long
TeTin::triangleAt (TeCoord2D& pt)
{
//Seja v um v�rtice qualquer da triangula��o T e p o ponto para o qual se deseja saber qual tri�ngulo t
//	o cont�m.
	long vi1;

	TeTinEdgeSet::reverse_iterator i = edgeSet_.rbegin();
	while ( i != edgeSet_.rend() )
	{
		vi1 = (*i++).from();
		if (vi1 >= 0 ) // -1L)
			break;
	}
	if ( i == edgeSet_.rend() )
		return -1;

//1. Defina o conjunto T={t1,..., tm} com os m tri�ngulos que compartilham o v�rtice vi,
	std::list<long> triset;
	this->vertexTriangles(vi1, triset);

	TeCoord2D pf = vertexSet_[vi1].location();
	if ( pf == pt )
//2. Se vi � igual a p, o tri�ngulo que cont�m p � um dos tri�ngulos que compartilham vi.
// Escolha qualquer um dos tri�ngulos e termine o algoritmo.
		return ( *(triset.begin()) );

//3. Defina A={a1,...,an} com as n arestas opostas a vi,
	std::list<long> aedges;
	this->vertexOppEdges(vi1, triset, aedges);

//4. Defina V={v1,...,vm} com os m v�rtices dos tri�ngulos que cont�m o v�rtice vi,
	std::list <long> vvertex;
	this->vertexOppVertices(vi1, vvertex);

//5. Insira o v�rtice v no conjunto VI de v�rtices intersectados,
	std::set <long> viset;
	viset.insert(vi1);

//6. Defina o v�rtice auxiliar vaux como sendo vi,
	long vaux = vi1;
//   e aresta aaux como sendo inv�lida
	long aaux = -1;
	std::vector<long> auxset(3);
	for (;;)
	{
//7. Para cada tri�ngulo ti de T, fa�a:
		std::list<long>::iterator tii;
		for (tii = triset.begin(); tii != triset.end(); tii++)
		{
			long ti = *tii;
//7.1. Se o tri�ngulo ti cont�m o ponto pn, termine o algoritmo.
			if ( this->triangleContainsPoint( ti, pt ) )
				return ti;
		}
//8.	Para cada v�rtice vi de V, fa�a:
		std::list<long>::iterator vii;
		for (vii = vvertex.begin(); vii != vvertex.end(); vii++)
		{
			long vi = *vii;
			TeCoord2D ptvi = vertexSet_[vi].location();
			if ( ptvi == pt )
//8.1. Se vi � igual a p, o tri�ngulo que cont�m p � um dos tri�ngulos que compartilham vi.
			{
				for (tii = triset.begin(); tii != triset.end(); tii++)
				{
					long ti = *tii;
					long v0, v1, v2;
					this->triangleVertices(ti, v0, v1, v2);
					if ( v0 == vi || v1 == vi || v2 == vi)
						return ti;
				}
				return -1;
			}
		}
//9. Para cada v�rtice vi de V, fa�a:
		for ( vii = vvertex.begin(); vii != vvertex.end(); vii++)
		{
			long vi = *vii;
//9.1.	Se vi est� sobre r, fa�a:
			TeCoord2D ptvi = vertexSet_[vi].location();
			TeCoord2D pinter;
			double tolerance = TePrecision::instance().precision();
			if ( TePerpendicularDistance(pf, pt, ptvi, pinter) < TePrecision::instance().precision() )
			{
				TeBox box1;
				updateBox (box1, pf);
				updateBox (box1, pt);
				//extra cases
				TeLine2D linter;
				linter.add(pf);
				linter.add(pt);
				if (TeWithin (pinter, box1) || (TeWithin(pinter,linter)))
				{
//9.1.1.	Redefina o conjunto A={a1,..., an} com as n arestas opostas a vi, diferentes de aaux,
					aedges.clear();
					this->vertexOppEdges(vi, aedges);
//9.1.2.	Defina o conjunto Aaux={a1,..., am} com as m arestas compartilhadas por vaux,
					std::list <long> vauxedges;
					this->vertexEdges(vaux, vauxedges);
//9.1.3.	Exclua do conjunto A todas as arestas que pertencem ao conjunto Aaux,
					for (std::list<long>::iterator vai = vauxedges.begin(); vai != vauxedges.end(); vai++)
						aedges.remove ( *vai );
//9.1.4.	Exclua do conjunto A a aresta aaux,
					aedges.remove ( aaux ); // better perfomance than remove algorithm
//9.1.5.	Redefina o conjunto V={v1,..., vm} com os m v�rtices dos tri�ngulos que cont�m o v�rtice vi,
//			diferentes de vaux,
					vvertex.clear();
					this->vertexOppVertices(vi, vvertex);
//9.1.6.	Exclua do conjunto V todos os v�rtices que pertencem ao conjunto VI,
					for (std::set<long>::iterator vvi = viset.begin(); vvi != viset.end(); vvi++)
						vvertex.remove ( *vvi );
//9.1.7.	Redefina o conjunto T={t1, ..., tk } com os k tri�ngulos que cont�m o v�rtice vi,
					triset.clear();
					this->vertexTriangles(vi, triset);
//9.1.8.	Redefina o v�rtice auxiliar vaux como sendo vi,
					vaux = vi;
//9.1.8.	Insira o v�rtice vi no conjunto VI de v�rtices intersectados,
					viset.insert(vi);
//9.1.8.	Retorne a 7,
					//pf = vertexSet_[vi].location();
					break;
				}
			}
		}
		if ( vii != vvertex.end() )
			continue; // do for (;;)

//10.	Para cada aresta ai de A, fa�a:
		std::list<long>::iterator aii;
		for (aii = aedges.begin(); aii != aedges.end(); aii++)
		{
			long ai = *aii;
//10.1.	Se o ponto p est� sobre ai, fa�a:
			TeCoord2D pfr = vertexSet_[edgeSet_[ai].from()].location();
			TeCoord2D pto = vertexSet_[edgeSet_[ai].to()].location();
			TeCoord2D pinter;
			if ( TePerpendicularDistance(pfr, pto, pt, pinter) < TePrecision::instance().precision() )
			{
				TeBox box1;
				updateBox (box1, pfr);
				updateBox (box1, pto);
				if (TeWithin(pinter, box1) )
				{
//10.1.1. Escolha qualquer um dos tri�ngulos que compartilham ai.
					long ti = edgeSet_[ai].left();
//10.1.2.	Termine o algoritmo.
					if ( (ti != -1) && (this->triangleContainsPoint(ti, pt)) )
						return ( ti );
					else
					{
						ti = edgeSet_[ai].right();
						if ( (ti != -1) && (this->triangleContainsPoint(ti, pt)) )
							return ( ti );
						return -1;
					}
				}
			}
		}

//11.	Para cada aresta ai de A, fa�a:
		for (aii = aedges.begin(); aii != aedges.end(); aii++)
		{
			long ai = *aii;
			long vt = edgeSet_[ai].to();
			long vf = edgeSet_[ai].from();
			TeCoord2D pi;
//11.1.	Se ai intersecta r, fa�a:
			if (TeSegmentsIntersectPoint(vertexSet_[vt].location(), vertexSet_[vf].location(), pf, pt, pi) )
			{
//11.1.2.	Defina os tri�ngulos t1 e t2 que compartilham a aresta ai.
//11.1.3.	Se t2 est� contido no conjunto T , ent�o fa�a taux=t1,
				long taux = edgeSet_[ai].left();
				if (taux == -1)
					return -1;
				std::list<long>::iterator pos1 = find (triset.begin(), triset.end(), taux);
				if ( pos1 != triset.end() )
//11.1.4.	Sen�o, fa�a taux=t2,
					taux = edgeSet_[ai].right();
				if (taux == -1)
					return -1;
//11.1.5.	Se o tri�ngulo taux cont�m o ponto pn, termine o algoritmo.
				if ( this->triangleContainsPoint( taux, pt ) )
					return taux;
//11.1.6.	Redefina o conjunto A={a1, a2} com as arestas do tri�ngulo taux diferentes de ai,
				triangleSet_[taux].edges ( auxset[0], auxset[1], auxset[2] );
				aedges.clear();
				aedges.insert( aedges.begin(), auxset.begin(), auxset.end() );
				aedges.remove( ai );
//11.1.7.	Redefina o conjunto V={v1}. O v�rtice v1 � o v�rtice do tri�ngulo taux que n�o est�
//			em nenhuma extremidade da aresta ai,
				long vaux1 = edgeSet_[ai].from();
				long vaux2 = edgeSet_[ai].to();
				this->triangleVertices ( taux, auxset[0], auxset[1], auxset[2]);
				vvertex.clear();
				vvertex.insert ( vvertex.begin(), auxset.begin(), auxset.end() );
				vvertex.remove ( vaux1 );
				vvertex.remove ( vaux2 );

//11.1.8.	Redefina o conjunto T={taux},
				triset.clear();
				triset.push_back ( taux );
//11.1.9.	Redefina aaux como sendo ai,
				aaux = ai;
//11.1.10.	Retorne a 8;
				break;
			}
		}
//12.	Se n�o h� mais arestas em A, ent�o:
		//if ( aii == aedges.end() )
		//{
//12.1.	Para cada tri�ngulo ti de T, fa�a:
//			TeTinTriangleIterator tii;
//			for ( tii = triangleBegin(); tii != triangleEnd(); tii++)
			long ti;
			long tEnd = triangleSet_.size();
			for ( ti = 0; ti < tEnd; ti++)
			{
//				TeTinTriangle ti = *tii;
	//12.1.1.	Se o tri�ngulo ti cont�m o ponto pn, termine o algoritmo.
				if ( this->triangleContainsPoint( ti, pt ) )
					return ti;
			}
			if (ti == tEnd )
				return -1;
		//}
	} // Do for (;;)
	return -1;
}

bool
TeTin::insertPoint(double x, double y, double value)
{
	if ((x == 183782) && (y == 8246442))
		bool teste = true;

	double tol;
	if (minedgesize_ == 0)
		tol = TePrecision::instance().precision();
	else
		tol = minedgesize_;

//	Get Point to be inserted from std::vector
	TeCoord2D	pt(x,y);
	if ( ! TeWithin (pt, vertexSet_.box()) )
		return false;

//	Find the triangle that owns the point pt	
	long t = triangleAt ( pt );

	if (t == -1)
		return false;

	vertexSet_.add( TeTinVertex (pt, value, type_, -1 ) );
	long v = vertexSet_.size()-1;

	double ptx = vertexSet_[v].location().x();
	double pty = vertexSet_[v].location().y();

	TeCoord2D vert[3];
	trianglePoints(t, vert[0], vert[1], vert[2]);

	//long vertex1[3];
	//this->triangleVertices(t, vertex1[0], vertex1[1], vertex1[2]);

//	Verify if point is too close to one triangle vertex
	long j;
	for ( j = 0; j < 3; j++)
	{
		//if (pt == vert[j]) // Using precision to compare
		//	return false;

		if ((fabs(ptx - vert[j].x()) < tol) && (fabs(pty - vert[j].y()) < tol))
		{
			long vert1[3];
			this->triangleVertices(t, vert1[0], vert1[1], vert1[2]);
			this->vertexExchange(vert1[j], v);
			vertexSet_[vert1[j]].setType(DELETEDVERTEX);

			return false;
		}
	}

	long neighids[3];
	this->triangle3Neighbors(t, neighids[0],neighids[1],neighids[2]);
	long eds[3];
	triangleSet_[t].edges( eds[0], eds[1], eds[2] );

//	Test if the point is on an edge
	long nedge = -1;
	double dmin = TeMAXFLOAT;
	TeCoord2D pmin;
	for (j = 0; j < 3; j++)
	{
		//if ((pt.x() > vert[j].x()) &&
		//	(pt.x() > vert[(j+1)%3].x()))
		//	continue;
		//if ((pt.x() < vert[j].x()) &&
		//	(pt.x() < vert[(j+1)%3].x()))
		//	continue;
		//if ((pt.y() > vert[j].y()) &&
		//	(pt.y() > vert[(j+1)%3].y()))
		//	continue;
		//if ((pt.y() < vert[j].y()) &&
		//	(pt.y() < vert[(j+1)%3].y()))
		//	continue;
		if ( TeWithinOrTouches (pt, vert[j], vert[(j+1)%3]) == false )
			continue;

		TeCoord2D paux;
		double daux = TePerpendicularDistance(vert[j], vert[(j+1)%3], pt, paux);
		//double daux = this->pointToSegmentDistance(&vert[j], &vert[(j+1)%3], &pt, &paux);
		//if ((daux < TePrecision::instance().precision()) && (daux < dmin))
		//{//			On edge j    --> if ((daux < tol) && (daux < dmin))
		//	nedge = j;
		//	dmin = daux;
		//	pmin = paux;
		//}
		
		if ((daux < tol) && (daux < dmin))
		{//			On edge j
			nedge = j;
			dmin = daux;
			pmin = paux;
		}
	}

	//vertexSet_.add( TeTinVertex (pt, value, NORMALVERTEX, -1 ) );
	//vertexSet_.add( TeTinVertex (pt, value, type_, -1 ) );
	//long v = vertexSet_.size()-1;

	std::set<long> trianglesToTest;
	if (nedge == -1)	// Not on an edge
	{
		this->twoNewTriangles(t, v, trianglesToTest);	//If not, split triang
	}
	else
	{
		vertexSet_[v].location().setXY(pmin.x(), pmin.y());
		//ptx = pmin.x();
		//pty = pmin.y();

		for (j = 0; j < 3; j++)
		{	// Check if neighbor triangle opposite vertex is too close
			if ( neighids[j] == -1 )
				continue;
			//long oppVertex = edgeOppVertex(neighids[j], eds[j]);
			long oppVertex = this->oppositeVertex(neighids[j], eds[j]);
			long vsize = vertexSet_.size();
			if ( oppVertex < vsize )
			{
			TeCoord2D ptaux = vertexSet_[oppVertex].location();
			//if ( ptaux == pt )
			//{
			//	return false;
			//}
			//long vert1[3];
			//this->triangleVertices(t, vert1[0], vert1[1], vert1[2]);

			//if ((fabs(vertexSet_[vert1[j]].location().x() - ptaux.x()) < minedgesize_) && (fabs(vertexSet_[vert1[j]].location().y() - ptaux.y()) < minedgesize_))
			if ((fabs(ptx - ptaux.x()) < tol) && (fabs(pty - ptaux.y()) < tol))
			{
			//	// If necessary add code to change oppVertex type and value
				long vert1[3];
				this->triangleVertices(t, vert1[0], vert1[1], vert1[2]);				
				this->vertexExchange(vert1[j], v);
				vertexSet_[vert1[j]].setType(DELETEDVERTEX);

				return false;
			}
			}
		}

//		Duplicate triangle and its neighbor on the same edge
		long an0 = this->duplicateTriangle( t, nedge, v, trianglesToTest);
		if (neighids[nedge] != -1)
		{
			long tv = neighids[nedge];
			this->dupNeighTriangle( tv, an0, v, trianglesToTest);
		}
	}
	std::set<long> trianglesToTest1;
	trianglesToTest1 = trianglesToTest;

	this->testDelaunayForVertex(v, trianglesToTest);

	return true;
}

bool
TeTin::insertPoint1(double x, double y, double value)
{
//	Get Point to be inserted from std::vector
	TeCoord2D	pt(x,y);
	if ( ! TeWithin (pt, vertexSet_.box()) )
		return false;

//	Find the triangle that owns the point pt	
	long t = triangleAt ( pt );

	if (t == -1)
		return false;

	//vertexSet_.add( TeTinVertex (pt, value, NORMALVERTEX, -1 ) );
	//long v = vertexSet_.size()-1;

	TeCoord2D vert[3];
	trianglePoints(t, vert[0], vert[1], vert[2]);

//	Verify if point is too close to one triangle vertex
	long j;
	for ( j = 0; j < 3; j++)
	{
		if (pt == vert[j]) // Using precision to compare
			return false;

		if ((fabs(x - vert[j].x()) < minedgesize_) && (fabs(y - vert[j].y()) < minedgesize_))
		{
		//	long vert1[3];
		//	this->triangleVertices(t, vert1[0], vert1[1], vert1[2]);
		//	for (long e = 0; e < 3; e++)
		//	{
		//		if ((edgeSet_[edges[e]].from() == vert1[j]) ||
		//			(edgeSet_[edges[e]].to() == vert1[j]))
		//			edgeSet_[edges[e]].exchangeVertex(vert1[j], v);
		//	}

			return false;
		}
	}

	vertexSet_.add( TeTinVertex (pt, value, type_, -1 ) );
	long v = vertexSet_.size()-1;

	long e[3];
	triangleSet_[t].edges(e[0], e[1], e[2]);
	long neigh[3];
	this->triangle3Neighbors(t, neigh[0], neigh[1], neigh[2]);

//	Test if the point is on an edge
	long nedge = -1;
	double dmin = TeMAXFLOAT;
	TeCoord2D pmin;
	for (j = 0; j < 3; j++)
	{
		if ((pt.x() > vert[j].x()) && (pt.x() > vert[(j+1)%3].x()))
			continue;
		if ((pt.x() < vert[j].x()) && (pt.x() < vert[(j+1)%3].x()))
			continue;
		if ((pt.y() > vert[j].y()) && (pt.y() > vert[(j+1)%3].y()))
			continue;
		if ((pt.y() < vert[j].y()) && (pt.y() < vert[(j+1)%3].y()))
			continue;

		TeCoord2D paux;
		//double daux = TePerpendicularDistance(vert[j], vert[(j+1)%3], pt, paux);
		double daux = this->pointToSegmentDistance(&vert[j], &vert[(j+1)%3], &pt, &paux);
		//if ((daux < TePrecision::instance().precision()) && (daux < dmin))
		//{//			On edge j    --> if ((daux < tol) && (daux < dmin))
		//	nedge = j;
		//	dmin = daux;
		//	pmin = paux;
		//}
		
		if ((daux < minedgesize_) && (daux < dmin))
		{//			On edge j
			nedge = j;
			dmin = daux;
			pmin = paux;
		}
	}

	long ntri1, ntri2;

	std::set<long> edgesToTest;
	if (nedge == -1)	// Not on an edge
	{
		this->twoNewTriangles(t, v, edgesToTest);	//If not, split triang

		//while (edgesToTest.size())
		//{
		//	std::set<long>::iterator i = edgesToTest.begin();
		//	long ed = *i;
		//	edgesToTest.erase(ed);
		//	this->testDelaunay(ed);
		//}

		std::set<long>::iterator i = edgesToTest.begin();
		for (int k = 0; k < 6; k++)
		{
			long ed = *i;

			if (ed == -1)
				break;

			if (this->testDelaunay(ed))
			{
				i = edgesToTest.begin();
				k = -1;
				continue;
			}

			i++;
		}

		ntri1 = triangleSet_.size() - 1;
		ntri2 = triangleSet_.size() - 2;

		//this->testDelaunay(t, ntri1, ntri2);

		//if ((ntri1 >= 0) && (ntri2 >= 0))
		//{
		this->triangle3Neighbors(t, neigh[0], neigh[1], neigh[2]);
		this->testDelaunay(t, 0);
		this->testDelaunay(t, 1);
		this->testDelaunay(t, 2);

		this->testDelaunay(neigh[0], 0);
		this->testDelaunay(neigh[0], 1);
		this->testDelaunay(neigh[0], 2);
		this->testDelaunay(neigh[1], 0);
		this->testDelaunay(neigh[1], 1);
		this->testDelaunay(neigh[1], 2);
		this->testDelaunay(neigh[2], 0);
		this->testDelaunay(neigh[2], 1);
		this->testDelaunay(neigh[2], 2);
		this->testDelaunay(ntri1, 0);
		this->testDelaunay(ntri1, 1);
		this->testDelaunay(ntri1, 2);
		this->testDelaunay(ntri2, 0);
		this->testDelaunay(ntri2, 1);
		this->testDelaunay(ntri2, 2);
		//}
	}
	else
	{
		vertexSet_[v].location().setXY(pmin.x(), pmin.y());

		for (j = 0; j < 3; j++)
		{	// Check if neighbor triangle opposite vertex is too close
			if ( neigh[j] == -1L )
				continue;
			long oppVertex = this->oppositeVertex(neigh[j], e[j]);

			//if ((fabs(vertexSet_[vert1[j]].location().x() - ptaux.x()) < minedgesize_) && (fabs(vertexSet_[vert1[j]].location().y() - ptaux.y()) < minedgesize_))
			if ((fabs(x - vertexSet_[oppVertex].location().x()) < minedgesize_) && (fabs(y - vertexSet_[oppVertex].location().y()) < minedgesize_))
			{
				return false;
			}
		}

//		Duplicate triangle and its neighbor on the same edge
		long an0 = this->duplicateTriangle( t, nedge, v, edgesToTest);
		if (neigh[nedge] != -1L)
		{
			long tv = neigh[nedge];
			this->dupNeighTriangle( tv, an0, v, edgesToTest);

			//while (edgesToTest.size())
			//{
			//	std::set<long>::iterator i = edgesToTest.begin();
			//	long ed = *i;
			//	edgesToTest.erase(ed);
			//	this->testDelaunay(ed);
			//}

			std::set<long>::iterator i = edgesToTest.begin();
			for (int k = 0; k < 2; k++)
			{
				long ed = *i;

				if (ed == -1)
					break;

				if (this->testDelaunay(ed))
				{
					i = edgesToTest.begin();
					k = -1;
					continue;
				}

				i++;
			}

			ntri1 = triangleSet_.size() - 1;
			ntri2 = triangleSet_.size() - 2;

			//this->testDelaunay(t, tv, ntri1, ntri2);

			//if ((ntri1 >= 0) && (ntri2 >= 0))
			//{
			this->triangle3Neighbors(t, neigh[0], neigh[1], neigh[2]);
			this->testDelaunay(t, 0);
			this->testDelaunay(t, 1);
			this->testDelaunay(t, 2);
			this->testDelaunay(tv, 0);
			this->testDelaunay(tv, 1);
			this->testDelaunay(tv, 2);

			this->testDelaunay(neigh[0], 0);
			this->testDelaunay(neigh[0], 1);
			this->testDelaunay(neigh[0], 2);
			this->testDelaunay(neigh[1], 0);
			this->testDelaunay(neigh[1], 1);
			this->testDelaunay(neigh[1], 2);
			this->testDelaunay(neigh[2], 0);
			this->testDelaunay(neigh[2], 1);
			this->testDelaunay(neigh[2], 2);
			this->testDelaunay(ntri1, 0);
			this->testDelaunay(ntri1, 1);
			this->testDelaunay(ntri1, 2);
			this->testDelaunay(ntri2, 0);
			this->testDelaunay(ntri2, 1);
			this->testDelaunay(ntri2, 2);
			//}
		}
		else
		{
			//while (edgesToTest.size())
			//{
			//	std::set<long>::iterator i = edgesToTest.begin();
			//	long ed = *i;
			//	edgesToTest.erase(ed);
			//	this->testDelaunay(ed);
			//}

			std::set<long>::iterator i = edgesToTest.begin();
			for (int k = 0; k < 5; k++)
			{
				long ed = *i;

				if (ed == -1)
					break;

				if (this->testDelaunay(ed))
				{
					i = edgesToTest.begin();
					k = -1;
					continue;
				}

				i++;
			}

			this->triangle3Neighbors(t, neigh[0], neigh[1], neigh[2]);
			ntri1 = triangleSet_.size() - 1;
			this->testDelaunay(t, 0);
			this->testDelaunay(t, 1);
			this->testDelaunay(t, 2);
			this->testDelaunay(neigh[0], 0);
			this->testDelaunay(neigh[0], 1);
			this->testDelaunay(neigh[0], 2);
			this->testDelaunay(neigh[1], 0);
			this->testDelaunay(neigh[1], 1);
			this->testDelaunay(neigh[1], 2);
			this->testDelaunay(neigh[2], 0);
			this->testDelaunay(neigh[2], 1);
			this->testDelaunay(neigh[2], 2);
			this->testDelaunay(ntri1, 0);
			this->testDelaunay(ntri1, 1);
			this->testDelaunay(ntri1, 2);
		}
	}

	return true;
}

bool
TeTin::triangle3DPoints(TeTinTriangle& t, TeCoord2D& pt0, TeCoord2D& pt1,
					TeCoord2D& pt2, double& val0, double& val1, double& val2)
{
	long vertex0, vertex1, vertex2;
	this->triangleVertices(t, vertex0, vertex1, vertex2);

	pt0 = vertexSet_[vertex0].location();
	pt1 = vertexSet_[vertex1].location();
	pt2 = vertexSet_[vertex2].location();

	val0 = vertexSet_[vertex0].value();
	val1 = vertexSet_[vertex1].value();
	val2 = vertexSet_[vertex2].value();

	return true;
}

bool
TeTin::trianglePoints(TeTinTriangle& t, TeCoord2D& pt0, TeCoord2D& pt1, TeCoord2D& pt2)
{
	long vertex0, vertex1, vertex2;
	this->triangleVertices(t, vertex0, vertex1, vertex2);

	pt0 = vertexSet_[vertex0].location();
	pt1 = vertexSet_[vertex1].location();
	pt2 = vertexSet_[vertex2].location();

	return true;
}

bool
TeTin::triangleVertices(TeTinTriangle& t, long& vertex0, long& vertex1, long& vertex2)
{
	long edge0, edge1, edge2;
	t.edges(edge0,edge1,edge2);

	if (edgeSet_[edge0].to() == edgeSet_[edge1].to())
	{
		vertex0 = edgeSet_[edge0].from();
		vertex1 = edgeSet_[edge0].to();
		vertex2 = edgeSet_[edge1].from();
	}
	else if (edgeSet_[edge0].to() == edgeSet_[edge1].from())
	{
		vertex0 = edgeSet_[edge0].from();
		vertex1 = edgeSet_[edge0].to();
		vertex2 = edgeSet_[edge1].to();
	}
	else if (edgeSet_[edge0].from() == edgeSet_[edge1].from())
	{
		vertex0 = edgeSet_[edge0].to();
		vertex1 = edgeSet_[edge0].from();
		vertex2 = edgeSet_[edge1].to();
	}
	else if (edgeSet_[edge0].from() == edgeSet_[edge1].to())
	{
		vertex0 = edgeSet_[edge0].to();
		vertex1 = edgeSet_[edge0].from();
		vertex2 = edgeSet_[edge1].from();
	}
	else
		return false;

	return true;
}

bool
TeTin::triangle3Neighbors(long t, long& neighbor0, long& neighbor1, long& neighbor2)
{
	long edge0, edge1, edge2;
	triangleSet_[t].edges(edge0,edge1,edge2);

	if (edgeSet_[edge0].left() == t)
		neighbor0 = edgeSet_[edge0].right();
	else
		neighbor0 = edgeSet_[edge0].left();

	if (edgeSet_[edge1].left() == t)
		neighbor1 = edgeSet_[edge1].right();
	else
		neighbor1 = edgeSet_[edge1].left();

	if (edgeSet_[edge2].left() == t)
		neighbor2 = edgeSet_[edge2].right();
	else
		neighbor2 = edgeSet_[edge2].left();

	return true;
}

long
TeTin::triangleVertexAt(long t, long vertex)
{
	long vertices[3];
	this->triangleVertices ( t, vertices[0],vertices[1],vertices[2] );

	return vertices[vertex];
}

bool
TeTin::twoNewTriangles(long t, long v, std::set<long>& triangles)
{
//1. Crie o v�rtice vn com os dados da amostra s,
//	Sint4 vn = nodeId;

//2. Crie 2 novos tri�ngulos t1 e t2,
	long t1 = triangleSet_.size();
	long t2 = t1+1;

//3. Crie a nova aresta an0 que conecta os v�rtices vn e v0 e
//   tem t e t1 como os tri�ngulos que compartilham a aresta.
	long v0 = this->triangleVertexAt(t,0); //v0 e' o vertice 0 de t
	edgeSet_.add( TeTinEdge (v, v0, t, t1, NORMALEDGE) );
	long an0 = edgeSet_.size()-1;
	vertexSet_[v].setOneEdge(an0);

//4. Crie a nova aresta an1 que conecta os v�rtices vn e v1 e
// 	tem t1 e t2 como os tri�ngulos que compartilham a aresta.
	long v1 = this->triangleVertexAt(t,1); //v1 e' o vertice 1 de t
	edgeSet_.add( TeTinEdge (v, v1, t1, t2, NORMALEDGE) );
	long an1 = edgeSet_.size()-1;

//5. Crie a nova aresta an2 que conecta os v�rtices vn e v2 e
//	tem t2 e t como os tri�ngulos que compartilham a aresta.
	long v2 = this->triangleVertexAt(t,2); //v2 e' o vertice 2 de t
	edgeSet_.add( TeTinEdge (v, v2, t2, t, NORMALEDGE) );
	long an2 = edgeSet_.size()-1;

//6. Troque o tri�ngulo t por t1 na aresta a0,
	long a0 = triangleSet_[t].edgeAt(0); // retorna aresta 0 de t
	edgeSet_[a0].exchangeTriangle(t,t1);

//7. Defina as arestas de t1 como sendo an0, a0 e an1,
	triangleSet_.add ( TeTinTriangle (an0, a0, an1) );

//8. Troque o tri�ngulo t por t2 na aresta a1,
	long a1 = triangleSet_[t].edgeAt(1); // retorna aresta 1 de t
	edgeSet_[a1].exchangeTriangle(t, t2);

//9. Defina as arestas de t2 como sendo an1, a1 e an2,
	triangleSet_.add ( TeTinTriangle (an1, a1, an2) );

//10. Defina as arestas de t como sendo an2, a2 e an0,
	long a2 = triangleSet_[t].edgeAt(2); // retorna aresta 2 de t
	triangleSet_[t].setEdges(an2, a2, an0);

	triangles.insert(t);
	triangles.insert(t1);
	triangles.insert(t2);
	//triangles.insert(a0);
	//triangles.insert(a1);
	//triangles.insert(a2);
	//triangles.insert(an0);
	//triangles.insert(an1);
	//triangles.insert(an2);
	return true;
}

long
TeTin::duplicateTriangle(long t, long n, long v, std::set<long>& triangles)
{
// Seja t o tri�ngulo que cont�m cuja n-�sima aresta an � a aresta 
// pr�xima a amostra s ( n E {0,1,2} ). A aresta an conecta os v�rtices 
// vn e vj, a aresta aj conecta os v�rtices vj e vk e a aresta ak conecta
// os v�rtices vk e vn, sendo j o resto da divis�o de n+1 por 3 e k o resto
// da divis�o de n+2 por 3.
	long edges[3];
	triangleSet_[t].edges(edges[0],edges[1],edges[2]);

	long an = edges [ n ];
	long aj = edges [ (n+1)%3 ];
	long ak = edges [ (n+2)%3 ];

	long vn = this->triangleVertexAt( t, n );

	//triangles.insert(aj);
	//triangles.insert(ak);

//	1. Crie o v�rtice v com os dados da amostra s,
//	2. Defina o tri�ngulo tv que compartilha a aresta an com t,
	long tv = 0;
	if (edgeSet_[an].left() == t)
		tv = edgeSet_[an].right();
	else if (edgeSet_[an].right() == t)
		tv = edgeSet_[an].left();

//	3. Defina o v�rtice vop do tri�ngulo t que n�o � conectado a aresta an,
	long vop = this->triangleVertexAt ( t, (n+2)%3 );

//	4. Crie o novo tri�ngulos t1,
	long t1 = triangleSet_.size();

//	5. Crie a nova aresta an0 que conecta os v�rtices v e vn e
//	   tem t1 e tv como os tri�ngulos que compartilham a aresta.
	edgeSet_.add( TeTinEdge (v, vn, t1, tv, NORMALEDGE) );
	long an0 = edgeSet_.size()-1;

	//triangles.insert(an);
	//triangles.insert(an0);

//	6. Crie a nova aresta an1 que conecta os v�rtices v e vop e
//	   tem t e t1 como os tri�ngulos que compartilham a aresta.
	edgeSet_.add( TeTinEdge (v, vop, t, t1, NORMALEDGE) );
	long an1 = edgeSet_.size()-1;

	//triangles.insert(an1);

//	7. Modifique a aresta an para conectar o v�rtice v ao inv�s de vn,
	edgeSet_[an].exchangeVertex( vn, v );
	vertexSet_[vn].setOneEdge ( an0 );

//	8. Defina as arestas de t como sendo an, aj e an1,
	triangleSet_[t].setEdges( an, aj, an1 );

//	9. Modifique a aresta ak para compartilhar o tri�ngulo t1 ao inv�s de t,
	edgeSet_[ak].exchangeTriangle( t, t1 );

//	10. Defina as arestas de t1 como sendo an0, an1 e ak,
	triangleSet_.add ( TeTinTriangle (an0, an1, ak) );

	triangles.insert(t);
	triangles.insert(t1);

	return an0;
}

bool
TeTin::dupNeighTriangle(long tv, long an0, long v, std::set<long>& triangles)
{
//	11.1. Crie o novo tri�ngulo t2,
	long t2 = triangleSet_.size();

//	11.2. Defina a aresta av do tri�ngulo tv que cont�m o v�rtice vn
//	      (obs: s� h� uma aresta porque a outra foi modificada),
	long vn = edgeSet_[an0].to(); //Due to assembly, dangerous
	if ( vn == v )
		vn = edgeSet_[an0].from();

	long edges[3];
	triangleSet_[tv].edges(edges[0],edges[1],edges[2]);
	long i;
	for (i = 0; i < 3; i++)
	{
		if ( (edgeSet_[edges[i]].from() == vn) ||
			 (edgeSet_[edges[i]].to() == vn) )
			break;
	}
	if (i == 3)
		return false;
	long av = edges[i];

	//triangles.insert(av);

//	11.3. Defina as outras arestas de tv como sendo av1 e av2.
	long av1 = edges[ (i+1)%3];
	long av2 = edges[ (i+2)%3];

	//triangles.insert(av1);

//	11.4. Defina o v�rtice vvo conectado a vn por meio da aresta av,
	long vvo;
	if (edgeSet_[av].from() == vn)
		vvo = edgeSet_[av].to();
	else
		vvo = edgeSet_[av].from();

//	11.5. Crie a nova aresta an2 que conecta os v�rtices v e vvo e
//	      tem t e t2 como os tri�ngulos que compartilham a aresta.
	edgeSet_.add( TeTinEdge (v, vvo, tv, t2, NORMALEDGE) );
	long an2 = edgeSet_.size()-1;

//	11.6. Troque o tri�ngulo tv por t2 na aresta av,
	edgeSet_[av].exchangeTriangle( tv, t2 );

//	11.7. Troque o tri�ngulo tv por t2 na aresta an0,
	edgeSet_[an0].exchangeTriangle( tv, t2 );

//	11.8. Defina as arestas de tv como sendo an2, av1 e av2.
	triangleSet_[tv].setEdges( an2, av1, av2 );

//	11.9. Defina as arestas de t2 como sendo an0, av e an2,
	triangleSet_.add ( TeTinTriangle ( an0, av, an2 ) );

	triangles.insert(tv);
	triangles.insert(t2);

	return true;
}

void
TeTin::testDelaunayForVertex(long v, std::set<long>& triangles)
{
	while ( triangles.size() )
	{
		std::set<long>::iterator i = triangles.begin();
		long t = *i;
		triangles.erase(t);
		this->testDelaunayAt(t, v, triangles);
	}
}

bool
TeTin::testDelaunayAt(long t, long v, std::set<long>& triangles)
{
	//	Retrieve line of triangle common to neighbor triangle
	long e = this->edgeOppVertex (t, v);

//	Retrieve neighbour triangle (tviz) pointer
	long tviz = edgeSet_[e].left();
	if ( edgeSet_[e].left() == t )
		tviz = edgeSet_[e].right();
	if ( tviz == -1 )
		return false;

//	Define base triangle (tri) center point
	TeCoord2D vert[3];
	this->trianglePoints(t, vert[0], vert[1], vert[2]);

//	Find opposite point to base triangle (tri) inside neighbour (tviz)
	long vo = this->vertexOppEdge ( tviz, e );
	TeCoord2D pto = vertexSet_[vo].location();

//	To avoid overflow
	TeCoord2D ptmin( TeMAXFLOAT, TeMAXFLOAT );
	long i;
	for (i = 0; i < 3; i++)
		if ( vert[i] < ptmin )
			ptmin = vert[i];

	if ( ! ptmin.tooBig() )
	{
		TeCoord2D mptmin ( -ptmin.x(), -ptmin.y() );
		for (i = 0; i < 3; i++)
			vert[i] += mptmin;
		pto += mptmin;
	}

	TeCoord2D ptc;
	if ( ! TeFindTriangleCenter( vert[0], vert[1], vert[2], ptc ) )
		return false;

//	Calculate base triangle (tri) radius
	double xaux = ptc.x() - vert[0].x();
	double yaux = ptc.y() - vert[0].y();
	double raio2 = xaux * xaux + yaux * yaux;

//	Calculate distance from opposite point (tviz) to center point (tri)
	xaux = ptc.x() - pto.x();
	yaux = ptc.y() - pto.y();
	double dist2 = xaux * xaux + yaux * yaux; 

/*	float fr = (float)sqrt(raio2);
	float fd = (float)sqrt(dist2);
	if (fr <= fd)
		return false; */

	if ( raio2 <= dist2 )
		return false;

	//	If not, change edge between tri and ntri
	bool status;
	if ( status = this->swapEdges(t, tviz, e) )
	{
		triangles.insert(t);
		triangles.insert(tviz);
	}
	return status;
}

bool
TeTin::testDelaunay(long t1, long t2, long t3)
{
	long neigh[3];
	this->triangle3Neighbors(t1, neigh[0], neigh[1], neigh[2]);

	int k;
	for (k = 0; k < 3; k++)
	{
		if ((neigh[k] != t2) && (neigh[k] != t3))
			break;
	}

	if (k == 3)
		return false;

	//if (IsNeighborOnIsoOrBreakline(t1, k) == FALSE)
	this->testDelaunay(t1, k);

	this->triangle3Neighbors(t2, neigh[0], neigh[1], neigh[2]);

	for (k = 0; k < 3; k++)
	{
		if ((neigh[k] != t1) && (neigh[k] != t3))
			break;
	}

	if (k == 3)
		return false;

	//if (IsNeighborOnIsoOrBreakline(t2, k) == FALSE)
	this->testDelaunay(t2, k);

	this->triangle3Neighbors(t3, neigh[0], neigh[1], neigh[2]);

	for (k = 0; k < 3; k++)
	{
		if ((neigh[k] != t1) && (neigh[k] != t2))
			break;
	}

	if (k == 3)
		return false;

	//if (IsNeighborOnIsoOrBreakline(t2, k) == FALSE)
	this->testDelaunay(t3, k);

	return true;
}

bool
TeTin::testDelaunay(long t1, long t2, long t3, long t4)
{
	long neigh[3];
	this->triangle3Neighbors(t1, neigh[0], neigh[1], neigh[2]);

	int k;
	for (k = 0; k < 3; k++)
	{
		if ((neigh[k] != t2) && (neigh[k] != t3) && (neigh[k] != t4))
			break;
	}

	if (k == 3)
		return false;

	//if (IsNeighborOnIsoOrBreakline(t1, k) == FALSE)
	this->testDelaunay(t1, k);

	this->triangle3Neighbors(t2, neigh[0], neigh[1], neigh[2]);

	for (k = 0; k < 3; k++)
	{
		if ((neigh[k] != t1) && (neigh[k] != t3) && (neigh[k] != t4))
			break;
	}

	if (k == 3)
		return false;

	//if (IsNeighborOnIsoOrBreakline(t1, k) == FALSE)
	this->testDelaunay(t2, k);

	this->triangle3Neighbors(t3, neigh[0], neigh[1], neigh[2]);

	for (k = 0; k < 3; k++)
	{
		if ((neigh[k] != t1) && (neigh[k] != t2) && (neigh[k] != t4))
			break;
	}

	if (k == 3)
		return false;

	//if (IsNeighborOnIsoOrBreakline(t1, k) == FALSE)
	this->testDelaunay(t3, k);

	this->triangle3Neighbors(t4, neigh[0], neigh[1], neigh[2]);

	for (k = 0; k < 3; k++)
	{
		if ((neigh[k] != t1) && (neigh[k] != t2) && (neigh[k] != t3))
			break;
	}

	if (k == 3)
		return false;

	//if (IsNeighborOnIsoOrBreakline(t1, k) == FALSE)
	this->testDelaunay(t4, k);

	return true;
}

bool
TeTin::testDelaunay(long e)
{
	long tv = edgeSet_[e].left();

	if (tv == -1)
		return false;

	long edges[3];
	triangleSet_[tv].edges(edges[0], edges[1], edges[2]);

	int j;
	for (j = 0; j < 3; j++)
	{
		if (edges[j] == e)
			break;
	}

	bool test = false;

	if (j != 3)
		test = this->testDelaunay(tv, j);

	return test;
}

bool
TeTin::testDelaunay(long t, long v)
{
	if (t == -1)
		return false;

	//	Retrieve neighbour triangle (tviz) pointer
	long neigh[3];
	this->triangle3Neighbors(t, neigh[0], neigh[1], neigh[2]);

	if (neigh[v] == -1)
		return false;

	//	Retrieve line of triangle common to neighbor triangle
	long e = triangleSet_[t].edgeAt(v);

	//	Define base triangle (tri) center point
	TeCoord2D vert[3];
	this->trianglePoints(t, vert[0], vert[1], vert[2]);

	//	Find opposite point to base triangle (tri) inside neighbour (tviz)
	long opvertex = this->vertexOppEdge(neigh[v], e);

	double minx = TeMAXFLOAT;
	double miny = TeMAXFLOAT;

	for (int i = 0; i < 3; i++)
	{
		if (vert[i].x() < minx)
			minx = vert[i].x();
		if (vert[i].y() < miny)
			miny = vert[i].y();
	}

	double x0, y0;

	if ((minx < TeMAXFLOAT) && (miny < TeMAXFLOAT))
	{
		for (int i = 0; i < 3; i++)
		{
			vert[i].x(vert[i].x() - minx);
			vert[i].y(vert[i].y() - miny);
		}

		x0 = vertexSet_[opvertex].location().x() - minx;
		y0 = vertexSet_[opvertex].location().y() - miny;
	}
	else
	{
		x0 = vertexSet_[opvertex].location().x();
		y0 = vertexSet_[opvertex].location().y();
	}

	TeCoord2D ptc;
	if ( ! TeFindTriangleCenter( vert[0], vert[1], vert[2], ptc ) )
		return false;

	double xaux = ptc.x() - vert[0].x();
	double yaux = ptc.y() - vert[0].y();
	double raio2 = (xaux * xaux) + (yaux * yaux);

	//	Calculate distance from opposite point (tviz) to center point (tri)
	xaux = ptc.x() - x0;
	yaux = ptc.y() - y0;
	double dist2 = (xaux * xaux) + (yaux * yaux);
	double fr = sqrt(raio2);
	double fd = sqrt(dist2);

	if (fr <= fd)
		return false;


	bool status = this->swapEdges(t, neigh[v], e);

	return status;
}

bool
TeTin::createDelaunay()
{
	long contr = 0;
	long npoly = -1;

	for (long t = 1; t < triangleSet_.size(); t++)
	{
		if (t > npoly)
			npoly = t;

		if (this->generateDelaunay(npoly, npoly, contr) == false)
		{
			return false;
		}
	}

	return true;
}

bool
TeTin::generateDelaunay(long nt, long ntbase, long& contr)
{
	contr++;

	if (contr > triangleSet_.size())
		return false;

	for (long j = 0; j < 3; j++)
	{
		long neigh[3];
		this->triangle3Neighbors(nt, neigh[0], neigh[1], neigh[2]);

		long aux = neigh[j];
		if (aux == nt)
			continue;

		//Test with each neighbor, if it exists
		if (aux == -1)
			continue;

		if (this->testDelaunay(nt, j))
		{
			//If changed:
			if (ntbase > aux)
				this->generateDelaunay(aux, ntbase, contr);

			j = -1;
		}
	}

	return true;
}

void
TeTin::vertexExchange(long oldVertex, long newVertex)
{
	std::list<long> edges;
	this->vertexEdges(oldVertex, edges);

	long e;
	std::list<long>::iterator it = edges.begin();
	while (it != edges.end())
	{
		e = *it;
		edgeSet_[e].exchangeVertex(oldVertex, newVertex);

		it++;
	}

	double x = vertexSet_[oldVertex].location().x();
	double y = vertexSet_[oldVertex].location().y();
	double z = vertexSet_[oldVertex].value();

	vertexSet_[newVertex].location().setXY(x, y);
	vertexSet_[newVertex].value(z);
	vertexSet_[newVertex].setOneEdge(e);
}

void
TeTin::testSmallerAngleForVertex(long v, std::set<long>& triangles)
{
	while ( triangles.size() )
	{
		std::set<long>::iterator i = triangles.begin();
		long t = *i;
		triangles.erase(t);
		this->testSmallerAngleAt(t, v, triangles);
	}
}

bool
TeTin::testSmallerAngleAt(long t, long v, std::set<long>& triangles)
{
	if (t == -1)
		return false;

//	Retrieve line of triangle common to neighbor triangle
	//long e = this->edgeOppVertex (t, v);
	//long e = triangleSet_[t].edgeAt(v);
	//TeTinEdge edge = edgeSet_[e];

//	Retrieve neighbour triangle (tviz) pointer
	//long tviz = this->edge(e).left();//edgeSet_[e].left();
	//if ( this->edge(e).left() == t )//edgeSet_[e].left() == t )
	//	tviz = this->edge(e).right();//edgeSet_[e].right();
	//if ( tviz == -1 )
	//	return false;
	long neigh[3];
	this->triangle3Neighbors(t, neigh[0], neigh[1], neigh[2]);

	long tviz = neigh[v];

	if (tviz == -1)
		return false;

	long e = triangleSet_[t].edgeAt(v);
	if (e == -1)
		return false;
	TeTinEdge edge = edgeSet_[e];

	long nodeid1 = edgeSet_[e].to();
	long nodeid2;
	if (nodeid1 > edgeSet_[e].from())
	{
		nodeid1 = edgeSet_[e].from();
		nodeid2 = edgeSet_[e].to();
	}
	else
		nodeid2 = edgeSet_[e].from();

	if ((vertexSet_[nodeid1].value() > TeMAXFLOAT) || (vertexSet_[nodeid2].value() > TeMAXFLOAT))
		return false;

	TeCoord2D vert[3], vert1[3];
	this->trianglePoints(t, vert[0], vert[1], vert[2]);
	this->trianglePoints(tviz, vert1[0], vert1[1], vert1[2]);

	long vertice[3], vertice1[3];
	this->triangleVertices(t, vertice[0], vertice[1], vertice[2]);
	this->triangleVertices(tviz, vertice1[0], vertice1[1], vertice1[2]);

	std::vector<TeTinVertex> vertexVec1, vertexVec2;
	for (int j = 0; j < 3; j++)
	{
		vertexVec1.push_back(this->vertex(vertice[j]));
		vertexVec2.push_back(this->vertex(vertice1[j]));
	}

	//for (int i = 0; i < 3; i++)
	//{
	//	TeTinVertex vertex = vertexSet_[vertice[i]];//this->vertex(vertice[i]);
	//	TeTinVertex vertex1 = vertexSet_[vertice1[i]];//this->vertex(vertice1[i]);

	//	if ((vertex.value() > TeMAXFLOAT) || (vertex1.value() > TeMAXFLOAT))
	//		return false;
	//}

	std::vector<double> nvector, nvector1;
//	Define base triangle (tri) normal vector
	this->normalTriangle(vertexVec1, nvector);//(triangleSet_[t], nvector); 
	this->normalizeVector(nvector);

//	Define opposite triangle (nviz) normal vector
	this->normalTriangle(vertexVec2, nvector1);//(triangleSet_[tviz], nvector1);
	this->normalizeVector(nvector1);

//	Calculate cosine between triangles
	double cos1 = (nvector[0] * nvector1[0]) + (nvector[1] * nvector1[1]) + (nvector[2] * nvector1[2]);

//	Find opposite point to common edge on base triangle
	nodeid1 = this->vertexOppEdge ( t, e );
	if (nodeid1 == -1)
		return false;
	TeCoord2D pt0 = vertexSet_[nodeid1].location();

//	Find opposite point to common edge on neighbor triangle
	nodeid2 = this->vertexOppEdge ( tviz, e );
	if (nodeid2 == -1)
		return false;
	TeCoord2D pt1 = vertexSet_[nodeid2].location();

	//	Fill in first possible triangle points
	vertexVec1[0].location().x(pt0.x());
	vertexVec1[0].location().x(pt0.y());
	vertexVec1[0].value(vertexSet_[nodeid1].value());
	vertexVec1[1].location().x(pt1.x());
	vertexVec1[1].location().x(pt1.y());
	vertexVec1[1].value(vertexSet_[nodeid2].value());
	vertexVec1[2].location().x(vertexSet_[edge.from()].location().x());
	vertexVec1[2].location().x(vertexSet_[edge.from()].location().y());
	vertexVec1[2].value(vertexSet_[edge.from()].value());
	//long vertex0, vertex1, vertex2;
	//this->triangleVertices(t, vertex0, vertex1, vertex2);
	//vertexSet_[vertex0].location().x(pt0.x());
	//vertexSet_[vertex0].location().x(pt0.y());
	//vertexSet_[vertex0].value(vertexSet_[nodeid1].value());
	//vertexSet_[vertex1].location().x(pt1.x());
	//vertexSet_[vertex1].location().x(pt1.y());
	//vertexSet_[vertex1].value(vertexSet_[nodeid2].value());
	//vertexSet_[vertex2].location().x(vertexSet_[edge.from()].location().x());
	//vertexSet_[vertex2].location().x(vertexSet_[edge.from()].location().y());
	//vertexSet_[vertex2].value(vertexSet_[edge.from()].value());

	//	Fill in second possible triangle points
	vertexVec2[0].location().x(pt0.x());
	vertexVec2[0].location().x(pt0.y());
	vertexVec2[0].value(vertexSet_[nodeid1].value());
	vertexVec2[1].location().x(pt1.x());
	vertexVec2[1].location().x(pt1.y());
	vertexVec2[1].value(vertexSet_[nodeid2].value());
	vertexVec2[2].location().x(vertexSet_[edge.to()].location().x());
	vertexVec2[2].location().x(vertexSet_[edge.to()].location().y());
	vertexVec2[2].value(vertexSet_[edge.to()].value());
	//this->triangleVertices(tviz, vertex0, vertex1, vertex2);
	//vertexSet_[vertex0].location().x(pt0.x());
	//vertexSet_[vertex0].location().x(pt0.y());
	//vertexSet_[vertex0].value(vertexSet_[nodeid1].value());
	//vertexSet_[vertex1].location().x(pt1.x());
	//vertexSet_[vertex1].location().x(pt1.y());
	//vertexSet_[vertex1].value(vertexSet_[nodeid2].value());
	//vertexSet_[vertex2].location().x(vertexSet_[edge.to()].location().x());
	//vertexSet_[vertex2].location().x(vertexSet_[edge.to()].location().y());
	//vertexSet_[vertex2].value(vertexSet_[edge.to()].value());

	//	Define first possible triangle normal vector
	this->normalTriangle(vertexVec1, nvector);
	this->normalizeVector(nvector);

	//	Define second possible triangle normal vector
	this->normalTriangle(vertexVec2, nvector);
	this->normalizeVector(nvector1);

	//	Calculate cosine between triangles
	double cos2 = (nvector[0] * nvector1[0]) + (nvector[1] * nvector1[1]) + (nvector[2] * nvector1[2]);

	//	If new triangles normal vector angle difference smaller than old triangle's
	bool status = false;

	if (cos2 > cos1)
	{
		//status = this->swapEdges(t, tviz, e);
		if ( status = this->swapEdges(t, tviz, e) )
		{
			triangles.insert(t);
			triangles.insert(tviz);
		}

		//UpdateTriangles
	}

	return status;
}

void
TeTin::createSmallerAngleTriangulation()
{/*
	long neighbor[3];
	long triang = 0;
	long taux = -1;

	int test1 = 0;

	for (long t = 1; t < triangleSet_.size(); t++)
	{
		//triang = t;
		if (t > 29)
			bool teste = true;

		//this->triangle3Neighbors(triang, neighbor[0], neighbor[1], neighbor[2]);
		this->triangle3Neighbors(t, neighbor[0], neighbor[1], neighbor[2]);

		int test = 0;
		for (long v = 0; v < 3; v++)
		{
			if (this->testSmallerAngleAt(t, v))//triang, v))
			{//Se triangulo t e seu vizinho tv forem alterados:

				if (neighbor[v] < t)//triang)
				{//Se vizinho j� foi testado:
					t = neighbor[v] - 1;
					v = 3;
					//triang = neighbor[v];
					//this->triangle3Neighbors(triang, neighbor[0], neighbor[1], neighbor[2]);
					//v = -1;
				}
				else
				{//Se vizinho ainda n�o foi testado:
					//this->triangle3Neighbors(t, neighbor[0], neighbor[1], neighbor[2]);

					if (test1 > 100)
						break;

					test++;

					if (test == 3)
						test1++;

					if (test < 3)
						v = -1;
					
					//v = 3;
				}
			}
		}
	}*/
}

bool
TeTin::testSmallerAngleAt(long t, long v)
{/*
	if (t == -1)
		return false;

//	Retrieve neighbour triangle (tviz) pointer
	long neigh[3];
	this->triangle3Neighbors(t, neigh[0], neigh[1], neigh[2]);

	long tviz = neigh[v];

	if (tviz == -1)
		return false;

	//	Retrieve line of triangle common to neighbor triangle
	long e = triangleSet_[t].edgeAt(v);
	if (e == -1)
		return false;

	long nodeid1 = edgeSet_[e].to();
	long nodeid2;
	if (nodeid1 > edgeSet_[e].from())
	{
		nodeid1 = edgeSet_[e].from();
		nodeid2 = edgeSet_[e].to();
	}
	else
		nodeid2 = edgeSet_[e].from();

	if ((vertexSet_[nodeid1].value() > TeMAXFLOAT) || (vertexSet_[nodeid2].value() > TeMAXFLOAT))
		return false;

	TeCoord2D vert[3], vert1[3];
	this->trianglePoints(t, vert[0], vert[1], vert[2]);
	this->trianglePoints(tviz, vert1[0], vert1[1], vert1[2]);

	long vertice[3], vertice1[3];
	this->triangleVertices(t, vertice[0], vertice[1], vertice[2]);
	this->triangleVertices(tviz, vertice1[0], vertice1[1], vertice1[2]);

	std::vector<TeTinVertex> vertexVec1, vertexVec2;
	for (int i = 0; i < 3; i++)
	{
		TeTinVertex vertex = vertexSet_[vertice[i]];
		TeTinVertex vertex1 = vertexSet_[vertice1[i]];

		if ((vertex.value() > TeMAXFLOAT) || (vertex1.value() > TeMAXFLOAT))
			return false;

		vertexVec1.push_back(vertexSet_[vertice[i]]);
		vertexVec2.push_back(vertexSet_[vertice1[i]]);
	}

	std::vector<double> nvector, nvector1;

//	Define base triangle (tri) normal vector
	this->normalTriangle(vertexVec1, nvector); 
	this->normalizeVector(nvector);

//	Define opposite triangle (nviz) normal vector
	this->normalTriangle(vertexVec2, nvector1);
	this->normalizeVector(nvector1);

//	Calculate cosine between triangles
	double cos1 = (nvector[0] * nvector1[0]) + (nvector[1] * nvector1[1]) + (nvector[2] * nvector1[2]);

//	Find opposite point to common edge on base triangle
	//nodeid1 = this->vertexOppEdge ( t, e );
	nodeid1 = this->oppositeVertex(t, e);
	//if (nodeid1 == -1)
	//	return false;

//	Find opposite point to common edge on neighbor triangle
	//nodeid2 = this->vertexOppEdge ( tviz, e );
	nodeid2 = this->oppositeVertex(tviz, e);
	//if (nodeid2 == -1)
	//	return false;

	TeTinVertex pt0 = vertexSet_[nodeid1];
	TeTinVertex pt1 = vertexSet_[nodeid2];

	//	Fill in first possible triangle points
	vertexVec1[0].location().x(pt0.location().x());
	vertexVec1[0].location().x(pt0.location().y());
	vertexVec1[0].value(pt0.value());
	vertexVec1[1].location().x(pt1.location().x());
	vertexVec1[1].location().x(pt1.location().y());
	vertexVec1[1].value(pt1.value());
	vertexVec1[2].location().x(vertexSet_[edgeSet_[e].from()].location().x());
	vertexVec1[2].location().x(vertexSet_[edgeSet_[e].from()].location().y());
	vertexVec1[2].value(vertexSet_[edgeSet_[e].from()].value());

	//	Fill in second possible triangle points
	vertexVec2[0].location().x(pt0.location().x());
	vertexVec2[0].location().x(pt0.location().y());
	vertexVec2[0].value(pt0.value());
	vertexVec2[1].location().x(pt1.location().x());
	vertexVec2[1].location().x(pt1.location().y());
	vertexVec2[1].value(pt1.value());
	vertexVec2[2].location().x(vertexSet_[edgeSet_[e].to()].location().x());
	vertexVec2[2].location().x(vertexSet_[edgeSet_[e].to()].location().y());
	vertexVec2[2].value(vertexSet_[edgeSet_[e].to()].value());

	//	Define first possible triangle normal vector
	this->normalTriangle(vertexVec1, nvector);
	this->normalizeVector(nvector);

	//	Define second possible triangle normal vector
	this->normalTriangle(vertexVec2, nvector1);
	this->normalizeVector(nvector1);

	//	Calculate cosine between triangles
	double cos2 = (nvector[0] * nvector1[0]) + (nvector[1] * nvector1[1]) + (nvector[2] * nvector1[2]);

	//	If new triangles normal vector angle difference smaller than old triangle's
	bool status = false;

	if ((float)cos2 > (float)cos1)//1.2))// * 0.02))
		status = this->swapEdges(t, tviz, e);

	return status;*/
	return true;
}

void
TeTin::testWithIsolinesForVertex(long v, std::set<long>& triangles)
{
	while ( triangles.size() )
	{
		std::set<long>::iterator i = triangles.begin();
		long t = *i;
		triangles.erase(t);
		this->testWithIsolinesAt(t, v, triangles);
	}
}

bool
TeTin::testWithIsolinesAt(long t, long v, std::set<long>& triangles)
{
	//	Retrieve line of triangle common to neighbor triangle
	long e = this->edgeOppVertex (t, v);

//	Retrieve neighbour triangle (tviz) pointer
	long tviz = edgeSet_[e].left();
	if ( edgeSet_[e].left() == t )
		tviz = edgeSet_[e].right();
	if ( tviz == -1 )
		return false;

//	Define base triangle (tri) center point
	TeCoord2D vert[3];
	this->trianglePoints(t, vert[0], vert[1], vert[2]);

//	Find opposite point to base triangle (tri) inside neighbour (tviz)
	long vo = this->vertexOppEdge ( tviz, e );
	TeCoord2D pto = vertexSet_[vo].location();

//	To avoid overflow
	TeCoord2D ptmin( TeMAXFLOAT, TeMAXFLOAT );
	long i;
	for (i = 0; i < 3; i++)
		if ( vert[i] < ptmin )
			ptmin = vert[i];

	if ( ! ptmin.tooBig() )
	{
		TeCoord2D mptmin ( -ptmin.x(), -ptmin.y() );
		for (i = 0; i < 3; i++)
			vert[i] += mptmin;
		pto += mptmin;
	}

	TeCoord2D ptc;
	if ( ! TeFindTriangleCenter( vert[0], vert[1], vert[2], ptc ) )
		return false;

//	Calculate base triangle (tri) radius
	double xaux = ptc.x() - vert[0].x();
	double yaux = ptc.y() - vert[0].y();
	double raio2 = xaux * xaux + yaux * yaux;

//	Calculate distance from opposite point (tviz) to center point (tri)
	xaux = ptc.x() - pto.x();
	yaux = ptc.y() - pto.y();
	double dist2 = xaux * xaux + yaux * yaux; 

/*	float fr = (float)sqrt(raio2);
	float fd = (float)sqrt(dist2);
	if (fr <= fd)
		return false; */

	if ( raio2 <= dist2 )
		return false;

	//	If not, change edge between tri and ntri
	bool status;
	if ( status = this->swapEdges(t, tviz, e) )
	{
		triangles.insert(t);
		triangles.insert(tviz);
	}
	return status;
}

long
TeTin::oppositeVertex(long t, long e)
{
	long vto = edgeSet_[e].to();
	long vfrom = edgeSet_[e].from();

	long vert[3];
	this->triangleVertices(t, vert[0], vert[1], vert[2]);

	int i;
	for (i = 0; i < 3; i++)
	{
		if ((vto == vert[i]) || (vfrom == vert[i]))
			continue;

		break;
	}

	if (i == 3)
		return 0;

	return vert[i];
}

bool
TeTin::swapEdges( long t, long tv, long ai )
{
	if ( tv == -1 )
		return false;
// Seja t o tri�ngulo que cont�m cuja i-�sima aresta ai � a aresta
//	que se deseja alterar ( i E {0,1,2} ). A aresta ai conecta os
//	v�rtices vi e vj, a aresta aj conecta os v�rtices vj e vk e a
//	aresta ak conecta os v�rtices vk e vi, sendo j o resto da divis�o
//	de i+1 por 3 e k o resto da divis�o de i+2 por 3.

	long tedges[3];
	triangleSet_[t].edges ( tedges[0], tedges[1], tedges[2] );

	long vertex[3];
	this->triangleVertices ( t, vertex[0], vertex[1], vertex[2]);
	long i;
	for ( i= 0; i < 3; i++ )
		if ( tedges[i] == ai )
			break;

	if (i == 3)
		return false;

	long aj = tedges [ (i+1) % 3 ];
	long ak = tedges [ (i+2) % 3 ];

	long vi = vertex [ i ];
	long vj = vertex [ (i+1) % 3 ];
	long vk = vertex [ (i+2) % 3 ];

// Seja tv o tri�ngulo que compartilha a aresta ai com t. O v�rtice de
//	tv que n�o � conectado pela aresta ai � o v�rtice vn. As outras
//	arestas do tri�ngulo tv s�o am que conecta os v�rtices vi e vn e a
//	aresta an conecta os v�rtices vn e vj.
	
	long vn = this->vertexOppEdge ( tv, ai );

	long tvedges [3];
	triangleSet_[tv].edges ( tvedges[0], tvedges[1], tvedges[2] );

	long am, an = 0;
	for ( long j = 0; j < 3; j++ )
	{
		if ( tvedges [ j ] == ai )
			continue;

		if ( edgeSet_[tvedges[j]].from() == vn )
		{
			if ( edgeSet_[tvedges[j]].to() == vi )
				am = tvedges [ j ];
			else if ( edgeSet_[tvedges[j]].to() == vj )
				an = tvedges [ j ];
		}
		else if ( edgeSet_[tvedges[j]].to() == vn )
		{
			if ( edgeSet_[tvedges[j]].from() == vi )
				am = tvedges [ j ];
			else if ( edgeSet_[tvedges[j]].from() == vj )
				an = tvedges [ j ];
		}
	}

	TeCoord2D ptaux;
	double tol = TePrecision::instance().precision();
	if ( TePerpendicularDistance(vertexSet_[vk].location(), vertexSet_[vn].location(),
								 vertexSet_[vi].location(), ptaux) < tol )
		return false;
	if ( TePerpendicularDistance(vertexSet_[vk].location(), vertexSet_[vn].location(),
								 vertexSet_[vj].location(), ptaux) < TePrecision::instance().precision() )
		return false;

//	1. Se o segmento de reta formado conectando o v�rtice vk do
//	   tri�ngulo t ao v�rtice vn de tv intersecta a aresta ai, fa�a:
	TeCoord2D pi;
	if (TeSegmentsIntersectPoint(vertexSet_[vi].location(), vertexSet_[vj].location(), vertexSet_[vk].location(), vertexSet_[vn].location(), pi) == false )
		return false;

//		1.1. Troque na aresta ai o v�rtice vi pelo vertice vk e o
//			 v�rtice vj pelo v�rtice vn.
	edgeSet_[ai].exchangeVertex ( vi, vk );
	edgeSet_[ai].exchangeVertex ( vj, vn );
	//if (edgeSet_[ai].to() == vi)
	//	edgeSet_[ai].setVertices(vn, vk);
	//else if (edgeSet_[ai].to() == vj)
	//	edgeSet_[ai].setVertices(vk, vn);

	if ( vertexSet_[vi].oneEdge() == ai )
		vertexSet_[vi].setOneEdge ( ak );
	if ( vertexSet_[vj].oneEdge() == ai )
		vertexSet_[vj].setOneEdge ( aj );

//		1.2. Troque na aresta an o tri�ngulo tv pelo tri�ngulo t.
	edgeSet_[an].exchangeTriangle( tv , t );
	//if (edgeSet_[an].right() == tv)
	//	edgeSet_[an].setTriangles(edgeSet_[an].left(), t);
	//else
	//	edgeSet_[an].setTriangles(t, edgeSet_[an].right());

//		1.3. Troque na aresta ak o tri�ngulo t pelo tri�ngulo tv.
	edgeSet_[ak].exchangeTriangle( t, tv );
	//if (edgeSet_[ak].right() == t)
	//	edgeSet_[ak].setTriangles(edgeSet_[ak].left(), tv);
	//else
	//	edgeSet_[ak].setTriangles(tv, edgeSet_[ak].right());

//		1.4. Troque no tri�ngulo t a aresta ai pela aresta an e a
//			 aresta ak pela aresta ai.
	for ( i = 0; i < 3; i++ )
		if ( tedges[i] == ai )
			break;

	tedges[i] = an;
	tedges[(i+2)%3] = ai;
	triangleSet_[t].setEdges ( tedges[0], tedges[1], tedges[2] );

//		1.5. Troque no tri�ngulo tv a aresta ai pela aresta ak
	for ( i = 0; i < 3; i++ )
		if ( tvedges[i] == ai )
			break;
	tvedges [i] = ak;

//		 e a aresta an pela aresta ai.
	for ( i = 0; i < 3; i++ )
		if (tvedges[i] == an )
			break;
	tvedges[i] = ai;

	triangleSet_[tv].setEdges ( tvedges[0], tvedges[1], tvedges[2] );
	
	return true;
}

bool
TeTin::edgesInterBySegment( TeCoord2D& pf, TeCoord2D& pn, std::list<long> &aiset, std::list<long> &viset )
{
//		Seja o segmento de reta r que conecta os pontos pf  e pn,
//1.	Defina o tri�ngulo tf que cont�m o ponto pf,
	long tf = this->triangleAt (pf);
	if (tf == -1)
		return false;

//2.	Defina o v�rtice vaux e aresta aaux, como sendo inv�lidos,
	long vaux = -1;
	long aaux = -1;

//3.	Defina o conjunto A={a1, a2, a3} com as arestas de tf,
	std::vector<long> auxset(3);
	triangleSet_[tf].edges ( auxset[0], auxset[1], auxset[2] );
	std::list<long> aedges ( auxset.begin(), auxset.end() );

//4.	Defina o conjunto V={v1, v2, v3} com os v�rtices de tf,
	this->triangleVertices ( tf, auxset[0], auxset[1], auxset[2]);
	std::list <long> vvertex ( auxset.begin(), auxset.end() );

//5.	Defina o conjunto T={tf},
	std::list<long> triset( 1, tf );
	std::set<long> visetaux;

//6.	Para cada v�rtice vi de V, fa�a:
	std::list<long>::iterator vii;
	for (vii = vvertex.begin(); vii != vvertex.end(); vii++)
	{
		long vi = *vii;
		TeCoord2D ptvi = vertexSet_[vi].location();
		TeCoord2D pinter;

//6.1.	Se o v�rtice vi coincide com pf, fa�a:
		if ( ptvi == pf )
		{
//6.1.1.	Redefina A={a1,...,an} com as n arestas opostas a vi,
			aedges.clear();
			this->vertexOppEdges(vi, aedges);

//6.1.2.	Redefina V={v1,...,vm} com os m v�rtices dos tri�ngulos que cont�m o v�rtice vi,
			vvertex.clear();
			this->vertexOppVertices(vi, vvertex);

//6.1.3.	Redefina o conjunto T={t1,..., tm} com os m tri�ngulos que compartilham o v�rtice vi,
			triset.clear();
			this->vertexTriangles(vi, triset);

//6.1.4.	Redefina o v�rtice auxiliar vaux como sendo vi,
			vaux = vi;
			visetaux.insert(vi);
//6.1.5.	V� para 8,
			break;
		}
	}
	if ( vii == vvertex.end() )
	{
//7.	Para cada aresta ai de A, fa�a:
		for (std::list<long>::iterator aii = aedges.begin(); aii != aedges.end(); aii++)
		{
			long ai = *aii;
//7.1.	Se o ponto pf est� sobre ai, fa�a:
			TeCoord2D pfr = vertexSet_[edgeSet_[ai].from()].location();
			TeCoord2D pto = vertexSet_[edgeSet_[ai].to()].location();
			TeCoord2D pinter;
			if ( TePerpendicularDistance(pfr, pto, pf, pinter) < TePrecision::instance().precision() )
			{
//7.1.1.	Defina o tri�ngulo tv que compartilha ai com tf,
				long tv = edgeSet_[ai].right();
				if (tv == tf)
					tv = edgeSet_[ai].left();
				if (tv == -1)
					return false;
//7.1.2.	Redefina V={v1, v2, v3, v4} com os v�rtices de tv e tf,
				vvertex.clear();
				this->triangleVertices ( tv, auxset[0], auxset[1], auxset[2]);
				vvertex.insert( vvertex.begin(), auxset.begin(), auxset.end() );
				this->triangleVertices ( tf, auxset[0], auxset[1], auxset[2]);
				vvertex.insert( vvertex.begin(), auxset.begin(), auxset.end() );
				vvertex.sort();
				vvertex.unique();
//7.1.3.	Redefina A={a1, a2, a3, a4} com as arestas de tv e tf diferentes de ai,
				aedges.clear();
				triangleSet_[tv].edges ( auxset[0], auxset[1], auxset[2] );
				aedges.insert( aedges.begin(), auxset.begin(), auxset.end() );
				aedges.remove(ai);
				triangleSet_[tf].edges ( auxset[0], auxset[1], auxset[2] );
				aedges.insert( aedges.begin(), auxset.begin(), auxset.end() );
				aedges.remove(ai);

//7.1.4.	Redefina o conjunto T={tv, tf},
				triset.push_back ( tv );
//7.1.5.	Redefina a aresta auxiliar aaux como sendo ai,
				aiset.push_back ( ai );
				aaux = ai;
//7.1.6.	V� para 8,
				break;
			}
		}
	}

	for (;;)
	{
//8.	Para cada tri�ngulo ti de T, fa�a:
		std::list<long>::iterator tii;
		for ( tii = triset.begin(); tii != triset.end(); tii++)
		{
			long ti = *tii;
//8.1.1.	Se o tri�ngulo ti cont�m o ponto pn, termine o algoritmo.
			if ( this->triangleContainsPoint( ti, pn ) )
				return true;
		}
//9.	Para cada v�rtice vi de V, fa�a:
		std::list<long>::iterator vii;
		for (vii = vvertex.begin(); vii != vvertex.end(); vii++)
		{
			long vi = *vii;
			TeCoord2D ptvi = vertexSet_[vi].location();
//9.1.	Se vi coincide com pn, fa�a:
			if ( ptvi == pn )
			{
//9.1.1.	Insira o v�rtice vi no conjunto VI de v�rtices intersectados,
				viset.push_back ( vi );
//9.1.2.	Termine o algoritmo.
				break;
			}
		}
		if ( vii != vvertex.end() )
			break; // do for (;;)

//10.	Para cada v�rtice vi de V, fa�a:
		for ( vii = vvertex.begin(); vii != vvertex.end(); vii++)
		{
			long vi = *vii;
//10.1.	Se vi � diferente de vaux e est� sobre r, fa�a:
			if ( vi != vaux )
			{
				TeCoord2D ptvi = vertexSet_[vi].location();
				TeCoord2D pinter;
				if ( TePerpendicularDistance(pf, pn, ptvi, pinter) < TePrecision::instance().precision() )
				{
					TeBox box1;
					updateBox (box1, pf);
					updateBox (box1, pn);
					if (TeWithin (pinter, box1) )
					{
//10.1.1.	Redefina o conjunto A={a1,..., an} com as n arestas opostas a vi, excluindo as arestas de AI,
						aedges.clear();
						this->vertexOppEdges(vi, aedges);
						std::list<long>::iterator aisi;
						for ( aisi = aiset.begin(); aisi != aiset.end(); aisi++)
							aedges.remove ( *aisi );
//10.1.2.	Redefina o conjunto V={v1,..., vm} com os m v�rtices dos tri�ngulos que cont�m o v�rtice vi,
//			excluindo os vertices de Vi,
						vvertex.clear();
						this->vertexOppVertices(vi, vvertex);
						std::list<long>::iterator visi;
						for ( visi = viset.begin(); visi != viset.end(); aisi++)
							viset.remove ( *visi );
//101.3.	Redefina o conjunto T={t1, ..., tk } com os k tri�ngulos que cont�m o v�rtice vi,
						triset.clear();
						this->vertexTriangles(vi, triset);
//101.4.	Insira o v�rtice vi no conjunto VI de v�rtices intersectados,
						viset.push_back ( vi );
//101.5.	Defina o conjunto Ac={a1,..., aj} com as j arestas que cont�m vi, diferentes de aaux,
//101.6.	Insira as arestas de Ac no conjunto AI de arestas intersectadas,
						this->vertexEdges(vi, aiset);
						aiset.sort();
						aiset.unique();
//10.7.	Redefina o v�rtice auxiliar vaux como sendo vi,
						vaux = vi;
//10.8.	Retorne a 8,
						break;
					}
				}
			}
		}
		if ( vii != vvertex.end() )
			continue; // do for (;;)

//11.	Para cada aresta ai de A, fa�a:
		std::list<long>::iterator aii;
		for (aii = aedges.begin(); aii != aedges.end(); aii++)
		{
			long ai = *aii;
//11.1.	Se o ponto pn est� sobre ai, fa�a:
			TeCoord2D pfr = vertexSet_[edgeSet_[ai].from()].location();
			TeCoord2D pto = vertexSet_[edgeSet_[ai].to()].location();
			TeCoord2D pinter;
			if ( TePerpendicularDistance(pfr, pto, pn, pinter) < TePrecision::instance().precision() )
			{
				TeBox box1;
				updateBox (box1, pfr);
				updateBox (box1, pto);
				if (TeWithin (pinter, box1) )
				{
//11.1.1.	Insira a aresta ai no conjunto AI de arestas intersectadas,
					aiset.push_back ( ai );
//11.1.2.	Termine o algoritmo.
					break;
				}
			}
		}
		if ( aii != aedges.end() )
			break; // do for (;;)

//12.	Para cada aresta ai de A, fa�a:
		for (aii = aedges.begin(); aii != aedges.end(); aii++)
		{
			long ai = *aii;
			TeCoord2D pinter;
			long vt = edgeSet_[ai].to();
			long vf = edgeSet_[ai].from();
//12.1.	Se ai intersecta r, fa�a:
			if ( TeSegmentsIntersectPoint(vertexSet_[vt].location(), vertexSet_[vf].location(), pf, pn, pinter) )
			{
//12.1.1.	Insira a aresta ai no conjunto AI de arestas intersectadas,
				aiset.push_back ( ai );
//12.1.2.	Defina os tri�ngulos t1 e t2 que compartilham a aresta ai.
//12.1.3.	Se t2 est� contido no conjunto T , ent�o fa�a taux=t1,
				long taux = edgeSet_[ai].left();
				if (taux == -1)
					return false;
				std::list<long>::iterator pos1 = find (triset.begin(), triset.end(), taux);
				if ( pos1 != triset.end() )
//12.1.4.	Sen�o, fa�a taux=t2,
					taux = edgeSet_[ai].right();
				if (taux == -1)
					return false;
//12.1.5.	Se o tri�ngulo taux cont�m o ponto pn, termine o algoritmo.
				if ( this->triangleContainsPoint( taux, pn ) )
					return true;
//12.1.6.	Redefina o conjunto A={a1, a2} com as arestas do tri�ngulo taux diferentes de ai,
				triangleSet_[taux].edges ( auxset[0], auxset[1], auxset[2] );
				aedges.clear();
				aedges.insert( aedges.begin(), auxset.begin(), auxset.end() );
				aedges.remove( ai );
//12.1.7.	Redefina o conjunto V={v1}. O v�rtice v1 � o v�rtice do tri�ngulo taux que n�o est�
//			em nenhuma extremidade da aresta ai,
				long vaux1 = edgeSet_[ai].from();
				long vaux2 = edgeSet_[ai].to();
				this->triangleVertices ( taux, auxset[0], auxset[1], auxset[2]);
				vvertex.clear();
				vvertex.insert ( vvertex.begin(), auxset.begin(), auxset.end() );
				vvertex.remove ( vaux1 );
				vvertex.remove ( vaux2 );

//12.1.8.	Redefina o conjunto T={taux},
				triset.clear();
				triset.push_back ( taux );
//12.1.9.	Redefina aaux como sendo ai,
				aaux = ai;
//12.1.10.	Retorne a 8;
				break;
			}
		}
	} // Do for (;;)
	return true;
}

bool
TeTin::insertSegment( TeCoord2D& pf, TeCoord2D& pn )
{
	if ( this->insertPoint( pf.x(), pf.y(), 100.) )
	{
		if ( this->insertPoint( pn.x(), pn.y(), 100.) )
		{
			std::list<long> aiset;
			std::list<long> viset;
			if ( this->edgesInterBySegment( pf, pn, aiset, viset ) )
			{
				if ( viset.size() == 0 )
				{
					while ( aiset.size() > 0 )
					{
//2.	Para cada aresta ai de A, fa�a:
						std::list<long>::iterator aii;
						for (aii = aiset.begin(); aii != aiset.end(); aii++)
						{
							long ai = *aii;
//2.1.	Defina os tri�ngulos td e te compartilham ai,
							long td = edgeSet_[ai].right();
							long te = edgeSet_[ai].left();
//2.2.	Defina os v�rtices vm e vn dos tri�ngulos td e te que n�o est�o sobre a aresta ai,
							long vn = this->vertexOppEdge(td, ai);
							long vm = this->vertexOppEdge(te, ai);
//2.3.	Se r n�o intersecta o segmento que conecta os v�rtices vm e vn, fa�a:
							TeCoord2D pi;
							if ( TeSegmentsIntersectPoint(vertexSet_[vn].location(), vertexSet_[vm].location(), pf, pn, pi) )
							{
//2.3.1.	Se ai intersecta o segmento que conecta os v�rtices vm e vn, fa�a:
								if ( this->swapEdges( td, te, ai ) )
								{
//2.3.1.1.	Redefina ai como sendo o segmento que conecta os v�rtices vm e vn,
//2.3.1.2.	Redefina adequadamente os tri�ngulos tv e tf,
//2.3.1.3.	Remova a aresta ai de A,
									aiset.remove(ai);
									break;
								}
							}
						}
						if ( aii != aiset.end() )
							continue;
//3.	Se n�o h� mais arestas em A, ent�o:
//3.1.	Termine o algoritmo.
//4.	Para cada aresta ai de A, fa�a:
						aii = aiset.begin();
						while ( aii != aiset.end() )
						{
							long ai = *aii;
//4.1.	Defina os tri�ngulos td e te compartilham ai,
							long td = edgeSet_[ai].right();
							long te = edgeSet_[ai].left();
//4.2.	Defina os v�rtices vm e vn dos tri�ngulos td e te que n�o est�o sobre a aresta ai,
//4.3.	Se ai intersecta o segmento que conecta os v�rtices vm e vn, fa�a:
							if ( this->swapEdges( td, te, ai ) )
							{
//4.3.1.	Redefina ai como sendo o segmento que conecta os v�rtices vm e vn,
//4.3.2.	Redefina adequadamente os tri�ngulos tv e tf,
								TeCoord2D pinter;
								long vt = edgeSet_[ai].to();
								long vf = edgeSet_[ai].from();
								TeCoord2D pi;
								if ( ( vertexSet_[vt].location() == pf ) ||
									 ( vertexSet_[vf].location() == pf ) ||
									 ( vertexSet_[vt].location() == pn ) ||
									 ( vertexSet_[vf].location() == pn ) ||
									 ( TeSegmentsIntersectPoint(vertexSet_[vt].location(), vertexSet_[vf].location(), pf, pn, pi) == false ))
								{
//4.3.3.	Se ai n�o intersecta r, fa�a:
//4.3.3.1.	Remova a aresta ai de A
									aiset.remove(ai);
									aii = aiset.begin();
								}
								else
									aii++;
							}
							else
								aii++;
						}
//4.3.3.	Retorne a 2.
					}
					return true;
				}
			}
		}
	}
	return false;
}

bool
TeTin::createInitialTriangles(TeBox &box)
{
	// Make box 1% bigger
	zoomOut(box, 1./1.01);

	//	Create and insert initial nodes of the Tin
 	vertexSet_.add( TeTinVertex (box.lowerLeft(), TeMAXFLOAT, ONBOXVERTEX, 0 ) ); //v0
 	vertexSet_.add( TeTinVertex (TeCoord2D(box.x1(),box.y2()), TeMAXFLOAT,
		                         ONBOXVERTEX, 1 ) ); //v1
 	vertexSet_.add( TeTinVertex (box.upperRight(), TeMAXFLOAT, ONBOXVERTEX, 2 ) ); //v2
 	vertexSet_.add( TeTinVertex (TeCoord2D(box.x2(),box.y1()), TeMAXFLOAT,
		                         ONBOXVERTEX, 3 ) ); //v3

//	Create and insert initial lines of the Tin
	edgeSet_.add( TeTinEdge (0, 1, -1, 0, NORMALEDGE) ); //a0
	edgeSet_.add( TeTinEdge (1, 2, -1, 0, NORMALEDGE) ); //a1
	edgeSet_.add( TeTinEdge (2, 3, -1, 1, NORMALEDGE) ); //a2
	edgeSet_.add( TeTinEdge (3, 0, -1, 1, NORMALEDGE) ); //a3
	edgeSet_.add( TeTinEdge (0, 2,  0, 1, NORMALEDGE) ); //a4

//	Create the two initial triangles of the Tin
//	Update triangles edges
	triangleSet_.add ( TeTinTriangle (0, 1, 4) );
	triangleSet_.add ( TeTinTriangle (2, 3, 4) );

	return true;
}

bool
TeTin::insertLineSamples ( TeContourLine& line )
{
	TeLineSimplify(line, 20., 200.);
	unsigned long i;
	for ( i = 0; i < line.size(); i++ )
	{
		TeCoord2D pt = line[i];
		this->insertPoint(pt.x(), pt.y(), line.value());
	}
	return true;
}

bool
TeTin::isEdgeTriangle (long t)
{
	long neighids[3];
	this->triangle3Neighbors(t, neighids[0],neighids[1],neighids[2]);

	long i;
	for (i = 0; i < 3; i++)
		if ( neighids[i] == -1)
			return true;
	return false;
}

void
TeTin::convexize ()
{
	//unsigned long eii;

	//for (eii = 0; eii < edgeSet_.size(); eii++)
	//{
	//	TeTinEdge ei = this->edge(eii);
	//	if ((this->vertex(ei.from()).value() > TeTinBIGFLOAT ) ||
	//		(this->vertex(ei.to  ()).value() > TeTinBIGFLOAT ) )
	//	{
	//		if ((this->vertex(ei.from()).value() > TeTinBIGFLOAT ) && 
	//			(this->vertex(ei.to  ()).value() > TeTinBIGFLOAT ) )
	//			continue;
	//		else
	//		{
	//			long td = ei.right();
	//			long te = ei.left();
	//			if ( ! this->isEdgeTriangle(td) || ! this->isEdgeTriangle(te) )
	//				this->swapEdges( td, te, eii );
	//		}
	//	}
	//}

	long trids[4];
	long nids[4];
	int i;

	for (i = 0; i < 4; i++)
	{
		trids[i] = 0;
		nids[i] = 0;
	}

	i = 0;

	for (long nid = 1; nid < vertexSet_.size(); nid++)
	{
		if ((vertexSet_[nid].type() != ONBOXVERTEX) &&
			(vertexSet_[nid].type() != DELETEDVERTEX))
			continue;
		if (vertexSet_[nid].value() < TeTinBIGFLOAT)
			continue;

		nids[i] = nid;
		i++;

		if (i == 4)
			break;
	}

	bool modified = false;
	for (i = 0; i < 4; i++)
	{
		std::list<long> edges;
		this->vertexEdges(nids[i], edges);

		std::list<long>::iterator itEdge = edges.begin();
		while (itEdge != edges.end())
		{
			long e = *itEdge;
			long rtri = edgeSet_[e].right();
			long ltri = edgeSet_[e].left();

			if ((rtri != -1) && (ltri != -1))
			{
				long neigh[3];
				this->triangle3Neighbors(rtri, neigh[0], neigh[1], neigh[2]);

				int j;
				for (j = 0; j < 3; j++)
				{
					if (neigh[j] == -1)
						break;
				}

				if (j != 3)
				{
					itEdge++;
					continue;
				}

				if (this->swapEdges(rtri, ltri, e))
					modified = true;
			}
			else
			{
				if (((edgeSet_[e].from() == nids[i]) &&
					((edgeSet_[e].to() == nids[(i+1)%4]) ||
					(edgeSet_[e].to() == nids[(i+2)%4]) ||
					(edgeSet_[e].to() == nids[(i+3)%4]))) ||
					((edgeSet_[e].to() == nids[i]) &&
					((edgeSet_[e].from() == nids[(i+1)%4]) ||
					(edgeSet_[e].from() == nids[(i+2)%4]) ||
					(edgeSet_[e].from() == nids[(i+3)%4]))))
				{
					if (rtri == -1)
						trids[i] = ltri;
					else
						trids[i] = rtri;
				}
			}

			itEdge++;
		}

		if ((i == 3) && (modified == true))
		{
			i = -1;
			modified = false;
		}
	}

	for (i = 0; i < 4; i++)
	{
		long es[3];
		triangleSet_[trids[i]].edges(es[0], es[1], es[2]);

		for (int j = 0; j < 3; j++)
		{
			long rtri = edgeSet_[es[j]].right();
			long ltri = edgeSet_[es[j]].left();

			if ((rtri != -1) && (ltri != -1))
				this->swapEdges(rtri, ltri, es[j]);
		}
	}

	//std::string name = "delaunayPtsTinCoords.spr";
	//fstream sprcfile;
	//sprcfile.open ( name.c_str(), ios::out );
	//sprcfile.precision(10);

	//long t = 0;
	//TeTin::TeTinTriangleIterator ti;
	//for (ti = this->triangleBegin(); ti != this->triangleEnd(); ti++)
	//{
	//	long e[3];
	//	ti->edges(e[0], e[1], e[2]);
	//	TeCoord2D pt[3];
	//	this->trianglePoints(*ti, pt[0], pt[1], pt[2]);
	//	sprcfile << "T " << t << "\n";
	//	sprcfile << pt[0].x() << " " << pt[0].y() << " " << "\n";
	//	sprcfile << pt[1].x() << " " << pt[1].y() << " " << "\n";
	//	sprcfile << pt[2].x() << " " << pt[2].y() << " " << "\n";
	//	//sprcfile << "E " << e[0] << "\n";
	//	//sprcfile << "  From " << edgeSet_[e[0]].from() << " To " << edgeSet_[e[0]].to() << "\n";
	//	//sprcfile << "E " << e[1] << "\n";
	//	//sprcfile << "  From " << edgeSet_[e[1]].from() << " To " << edgeSet_[e[1]].to() << "\n";
	//	//sprcfile << "E " << e[2] << "\n";
	//	//sprcfile << "  From " << edgeSet_[e[2]].from() << " To " << edgeSet_[e[2]].to() << "\n";
	//	sprcfile << "END" << "\n";

	//	t++;
	//}
	//sprcfile << "END" << "\n";
	//sprcfile.close ();
}

//By Fernanda and Eduilson
bool
TeTin::createTIN(TeSampleSet& sampleSet, TeContourLineSet& contourSet)
{
	if ((sampleSet.size() == 0) && (contourSet.size() == 0))
	{
		errorMessage_ = "There is no sample to create TIN.";
		return false;
	}
//Creates original TIN
  //TeBox tinBox(sampleSet.box());

  TeBox tinBox;

  if (sampleSet.size() == 0)
	  tinBox = TeBox(contourSet.box());
  else if (contourSet.size() == 0)
	  tinBox = TeBox(sampleSet.box());
  else
  {
	  double x1, y1, x2, y2;
	  if (sampleSet.box().x1() < contourSet.box().x1())
		  x1 = sampleSet.box().x1();
	  else
		  x1 = contourSet.box().x1();

	  if (sampleSet.box().x2() < contourSet.box().x2())
		  x2 = sampleSet.box().x2();
	  else
		  x2 = contourSet.box().x2();

	  if (sampleSet.box().y1() < contourSet.box().y1())
		  y1 = sampleSet.box().y1();
	  else
		  y1 = contourSet.box().y1();

	  if (sampleSet.box().y2() < contourSet.box().y2())
		  y2 = sampleSet.box().y2();
	  else
		  y2 = contourSet.box().y2();

	  tinBox = TeBox(TeCoord2D(x1, y1), TeCoord2D(x2, y2));
  }

  this->createInitialTriangles(tinBox);

//Sets precision used for building TIN
  double tol = TePrecision::instance().precision(); // Save old precision
  double tinPrecision = tinBox.width() / 1.e6; // 1.e6th of deltaX
  TePrecision::instance().setPrecision(tinPrecision);

 // if (TeProgress::instance())
 // {
 //   TeProgress::instance()->setCaption("Create TIN");
	//TeProgress::instance()->setMessage("Creating TIN...");
	//TeProgress::instance()->setTotalSteps(sampleSet.size() + contourSet.size());
 // }

  std::vector<TeCoord2D> pts;
  int step = 0;

//Insert samples in TIN
  //int i=0;
  TeSampleSet::iterator si;
  for (si = sampleSet.begin(); si != sampleSet.end(); si++)
  {
    step++;
    //i+=1;

	type_ = NORMALVERTEX;
	double x = (*si).location().x();
    double y = (*si).location().y();
	double z = (*si).value();
	this->insertPoint(x, y, z);

	pts.push_back(TeCoord2D(x, y));

	//TeProgress::instance()->setProgress(step);

	//if (TeProgress::instance()->wasCancelled())
	//  return false;
  }

  if (isoTol_ == -1)
	  isoTol_ = tinPrecision*400.;

  if (dist_ == -1)
	  dist_ = tinPrecision*2000;

  TeContourLineSet::iterator ci;
  for (ci = contourSet.begin(); ci != contourSet.end(); ci++)
  {
	step++;

	type_ = ONCONTOURVERTEX;

    TeContourLine line( *ci );

	TeLineSimplify(line, isoTol_, dist_);

	double z = (*ci).value();

	//verificar se j� existe ponto
	TeContourLine::iterator li;
	for (li = line.begin(); li != line.end(); li++)
	{
		bool ptExist = false;

		if (pts.size() == 0)
			pts.push_back(*li);
		else
		{
			std::vector<TeCoord2D>::iterator itPt = pts.begin();
			while (itPt != pts.end())
			{
				if (*li == *itPt)
				{
					ptExist = true;
					break;
				}

				itPt++;
			}
		}

		if (ptExist == true)
			continue;

	  double x = (*li).x();
	  double y = (*li).y();
	  this->insertPoint(x, y, z);

	  pts.push_back(*li);
	}

	//TeProgress::instance()->setProgress(step);

	//if (TeProgress::instance()->wasCancelled())
	//{
	//  TeProgress::instance()->reset();
	//  return false;
	//}
  }

//Fixes edge triangles TIN
  this->convexize();
  //this->borderUp();

 // std::string name = "delaunayPontosTin.spr";
	//fstream sprcfile;
	//sprcfile.open ( name.c_str(), ios::out );
	//sprcfile.precision(10);

	//long t = 0;
	//TeTin::TeTinTriangleIterator ti;
	//for (ti = this->triangleBegin(); ti != this->triangleEnd(); ti++)
	//{
	//	long vert[3];
	//	this->triangleVertices(*ti, vert[0], vert[1], vert[2]);
	//	TeCoord2D pt[3];
	//	this->trianglePoints(*ti, pt[0], pt[1], pt[2]);
	//	sprcfile << "T " << t << "\n";
	//	//sprcfile << pt[0].x() << " " << pt[0].y() << " " << "\n";
	//	//sprcfile << pt[1].x() << " " << pt[1].y() << " " << "\n";
	//	//sprcfile << pt[2].x() << " " << pt[2].y() << " " << "\n";
	//	sprcfile << "V " << vert[0] << " " << vert[1] << " " << vert[2] << "\n";
	//	sprcfile << "END" << "\n";

	//	t++;
	//}
	//sprcfile << "END" << "\n";
	//sprcfile.close ();

  TePrecision::instance().setPrecision(tol);

  //TeProgress::instance()->reset();

  return true;
}

bool 
TeTin::createTIN(TeLayer* inputLayer_ptr, TePolygonSet &ps)
{
  TePolygon tp;
  TeLinearRing tl;
  int id = 0;
  int j = 0;
  int edgeit = 0;

//Set querier parameters
  bool loadGeometries = true;
  bool loadAllAttributes = true;
  TeQuerierParams querierParams(loadGeometries, loadAllAttributes);
  querierParams.setParams(inputLayer_ptr);
  TeQuerier querier(querierParams);

//Load instances from layer based in querier parameters
  if(querier.loadInstances())
  {
//  Returns loaded attributes list 
	TeAttributeList attrList = querier.getAttrList();
  }

  //! Used to store the attribute's values
  vector<string> attrValue (0);
  //! Used to store the attribute's objects ID
  vector<string> attrId (0);
  int it = 0;
  int it_id = 0;
  int vecSize = 0;
  int vecIdSize = 0;
  int I = 0;
  string Id;
  //! Containers used to store the attributes values and objects ID
  map<string, string> val1;
  map<string, string> val2;
  map<string, string> val3;

//Traverse all the instances
  TeSTInstance sti;
  while(querier.fetchInstance(sti))
  {// Get attribute's values
    TePropertyVector vec = sti.getPropertyVector();
	it_id+=1;
	vecIdSize = it_id;
	attrId.resize(vecIdSize);
	attrId[I] = sti.getObjectId();
	Id = attrId[I];
	for(unsigned int i=0; i<vec.size(); ++i)
	{
	  string attrName = vec[i].attr_.rep_.name_;
	  if(attrName == "val1")
	  {
	    it+=1;
		vecSize = it;
		attrValue.resize(vecSize);
		attrValue[j] = vec[i].value_;
		string testeATT = attrValue[j];
		val1[Id] = attrValue[j];
		j+=1;
	  }
	  if(attrName == "val2")
	  {
	    it+=1;
		vecSize = it;
		attrValue.resize(vecSize);
		attrValue[j] = vec[i].value_;
		string testeATT = attrValue[j];
		val2[Id] = attrValue[j];
		j+=1;
	  }
	  if(attrName == "val3")
	  {
		it+=1;
		vecSize = it;
		attrValue.resize(vecSize);
		attrValue[j] = vec[i].value_;
		string testeATT = attrValue[j];
		val3[Id] = attrValue[j];
		j+=1;
	  }
    }
	I+=1;
  }

  TeBox tinBox(ps.box());
  
  for (unsigned int i=0; i<ps.size(); ++i)
  {
    tp=ps[i];
	string psId = tp.objectId();
	string value1 = val1[psId];
	string value2 = val2[psId];
	string value3 = val3[psId];
	tl=tp.first();

//  Get 3 polygon's points
	TeSample sample1 (TeCoord2D(tl[0].x(), tl[0].y()), atof(value1.c_str()));
	TeSample sample2 (TeCoord2D(tl[1].x(), tl[1].y()), atof(value2.c_str()));
	TeSample sample3 (TeCoord2D(tl[2].x(), tl[2].y()), atof(value3.c_str()));
//  Creates samples object ID
	sample1.objectId(Te2String(id));
	sample2.objectId(Te2String(id+1));
	sample3.objectId(Te2String(id+2));
	TeCoord2D s1 = sample1.location();
	double v1 = sample1.value();
	TeCoord2D s2 = sample2.location();
	double v2 = sample2.value();
	TeCoord2D s3 = sample3.location();
	double v3 = sample3.value();

//  Insert TIN nodes
	TeTinVertexSet::iterator vi = vertexSet_.begin();
	//if (!vertexSet_.find( TeTinVertex(s1,v1,NORMALVERTEX,0),vi) )
	//{
	//  vertexSet_.add( TeTinVertex(s1, v1, NORMALVERTEX, 0));
	//  vi=vertexSet_.end()-1;
	//  vi->objectId(sample1.objectId());
	//}
//  Gets vertex id
	string id1 = vi->objectId();
	//if(!vertexSet_.find( TeTinVertex(s2,v2,NORMALVERTEX,0),vi) )
	//{
	//  vertexSet_.add( TeTinVertex(s2, v2, NORMALVERTEX, 0));
	//  vi=vertexSet_.end()-1;
	//  vi->objectId(sample2.objectId());
	//}
	string id2 = vi->objectId();
	//if(!vertexSet_.find( TeTinVertex(s3,v3,NORMALVERTEX,0),vi) )
	//{
	//  vertexSet_.add( TeTinVertex(s3, v3, NORMALVERTEX, 0));
	//  vi=vertexSet_.end()-1;
	//  vi->objectId(sample3.objectId());
	//}
	string id3 = vi->objectId();

//  Insert TIN lines
	TeTinEdgeSet::iterator ei = edgeSet_.begin();
	//if (!edgeSet_.find( TeTinEdge(atol(id1.c_str()),atol(id2.c_str()),-1,-1,
	//	                          NORMALEDGE),ei) )
	//{
	//  edgeSet_.add( TeTinEdge(atol(id1.c_str()),atol(id2.c_str()),-1,-1,
	//	                      NORMALEDGE) );
	//  ei=edgeSet_.end()-1;
	//  ei->objectId(Te2String(edgeit));
	//  ++edgeit;
	//}
//  Gets the edge id
	string idedge1 = ei->objectId();
	//if (!edgeSet_.find( TeTinEdge(atol(id2.c_str()),atol(id3.c_str()),-1,-1,
	//	                          NORMALEDGE),ei) )
	//{
	//  edgeSet_.add( TeTinEdge(atol(id2.c_str()),atol(id3.c_str()),-1,-1,
	//	                      NORMALEDGE) );
	//  ei=edgeSet_.end()-1;
	//  ei->objectId(Te2String(edgeit));
	//  ++edgeit;
	//}
	string idedge2 = ei->objectId();
	//if (!edgeSet_.find( TeTinEdge(atol(id3.c_str()),atol(id1.c_str()),-1,-1,
	//	                          NORMALEDGE),ei) )
	//{
	//  edgeSet_.add( TeTinEdge(atol(id3.c_str()),atol(id1.c_str()),-1,-1,
	//	                      NORMALEDGE) );
	//  ei=edgeSet_.end()-1;
	//  ei->objectId(Te2String(edgeit));
	//  ++edgeit;
	//}
	string idedge3 = ei->objectId();

//  Insert TIN triangles
	triangleSet_.add( TeTinTriangle(atol(idedge1.c_str()),atol(idedge2.c_str()),
		                            atol(idedge3.c_str())) );
	id = id + 3;
  }

  return true;
}

bool
TeTin::createTIN(TeLayer* inputLayer_ptr)
{
	//Set querier parameters
	bool loadGeometries = true;
	bool loadAllAttributes = true;
	TeQuerierParams querierParams(loadGeometries, loadAllAttributes);
	querierParams.setParams(inputLayer_ptr);
	TeQuerier querier(querierParams);
	TeBox tinBox(querierParams.box());

	//Load instances from layer based in querier parameters
	if(!querier.loadInstances())
	{
		cout << "Erro no carregamento dos objetos do layer" << endl;
	}
	
	// Traverse all the instances 
	TeSTInstance sti;
	int i=0;
	TeSampleSet sampleSet;
	double x; 
	double y; 
	double z;
	while(querier.fetchInstance(sti))
	{
		// Plot each attribute, its name and value
		TePropertyVector vec = sti.getPropertyVector();
		for(unsigned int i=0; i<vec.size(); ++i)
		{
			string  attrName = vec[i].attr_.rep_.name_;
			if (attrName =="z")
			{
				string  attrValue = vec[i].value_;
				z = atof (attrValue.c_str());
			}
		}

		//Get geometries
		if(sti.hasPoints())
		{
			TePointSet ponSet;
			TePoint    pt;
			sti.getGeometry(ponSet);

			for(unsigned int i=0; i<ponSet.size(); ++i)
			{
				x = atof ( Te2String(ponSet[i].location().x(), 7).c_str() );
				y = atof ( Te2String(ponSet[i].location().y(), 7).c_str());
			}
		}

		cout << endl << endl;
		//discard ONBOXVERTEX's vertex
		if (z <= 340000000)
			sampleSet.add ( TeSample(TeCoord2D(x, y), z) );

	}
	TeContourLineSet contourSet;
	this->createTIN(sampleSet,contourSet);

  return true;
}

bool
TeTin::createAttrTable(TeTable& attrTable, TeDatabase* db, TeLayer* layer)
{
//Creates an attribute table
//Defines a list of attributes
  TeAttributeList attList;
  TeAttribute at;
  at.rep_.type_ = TeSTRING;
  at.rep_.numChar_ = 16;
  at.rep_.name_ = "object_id";
  at.rep_.isPrimaryKey_ = true;
  attList.push_back(at);

  at.rep_.type_ = TeREAL;
  at.rep_.decimals_ = 6;
  at.rep_.name_ = "val1";
  at.rep_.isPrimaryKey_ = false;
  attList.push_back(at);

  at.rep_.type_ = TeREAL;
  at.rep_.decimals_ = 6;
  at.rep_.name_ = "val2";
  at.rep_.isPrimaryKey_ = false;
  attList.push_back(at);

  at.rep_.type_ = TeREAL;
  at.rep_.decimals_ = 6;
  at.rep_.name_ = "val3";
  at.rep_.isPrimaryKey_ = false;
  attList.push_back(at);

  at.rep_.type_ = TeREAL;
  at.rep_.decimals_ = 6;
  at.rep_.name_ = "slope";
  at.rep_.isPrimaryKey_ = false;
  attList.push_back(at);

  at.rep_.type_ = TeREAL;
  at.rep_.decimals_ = 6;
  at.rep_.name_ = "aspect";
  at.rep_.isPrimaryKey_ = false;
  attList.push_back(at);

  string tablename (attrTable.name());
//Creates an attribute table associated to the new layer
//Creates a table in memory
  TeTable attTable(tablename, attList, "object_id", "object_id");
  if (!layer->createAttributeTable(attTable))
	 return false;

  attrTable = attTable;
  return true;
}

bool
TeTin::createPolygon(TePolygonSet ps, TeTable& attTable, int t, TeCoord2D& pt0,
			         TeCoord2D& pt1, TeCoord2D& pt2, double& val0, double& val1,
					 double& val2)
{
//Creates a set of polygons
  TeLine2D line;
  line.add(pt0);
  line.add(pt1);
  line.add(pt2);
  line.add(pt0);

  TeLinearRing r1(line);
  TePolygon poly1;
  poly1.add(r1);

  poly1.objectId(Te2String(t));

  ps.add(poly1);

//Each row is related to one of the geometries by its objetc_id
  TeTableRow row;
  row.push_back(Te2String(t));
  row.push_back(Te2String(val0,6));
  row.push_back(Te2String(val1,6));
  row.push_back(Te2String(val2,6));
//Adds the row in the attributes table
  attTable.add(row);
  row.clear();

  return true;
}

bool
TeTin::createPolygon(TePolygonSet ps, TeTable& attTable, int t, TeCoord2D& pt0,
			         TeCoord2D& pt1, TeCoord2D& pt2, double& val0, double& val1,
					 double& val2,double& slope, double& aspect)
{
//Creates a set of polygons
  TeLine2D line;
  line.add(pt0);
  line.add(pt1);
  line.add(pt2);
  line.add(pt0);

  TeLinearRing r1(line);
  TePolygon poly1;
  poly1.add(r1);

  poly1.objectId(Te2String(t));

  ps.add(poly1);

//Each row is related to one of the geometries by its objetc_id
  TeTableRow row;
  row.push_back(Te2String(t));
  row.push_back(Te2String(val0,6));
  row.push_back(Te2String(val1,6));
  row.push_back(Te2String(val2,6));
  row.push_back(Te2String(slope,2));
  row.push_back(Te2String(aspect,2));
  
//Adds the row in the attributes table
  attTable.add(row);
  row.clear();

  return true;
}

bool
TeTin::saveTIN(TeDatabase* db, TeLayer* layer, TePolygonSet& ps,
			   TeTable& attTable)
{
//Adds the polygon set to the layer
//As addGeometry wasn�t called before, the table of polygons will have a default name
  if (!layer->addPolygons(ps))
	  return false;

//Saves attributes table in database
  if (!layer->saveAttributeTable(attTable))
	  return false;

  return true;
}

bool
TeTin::saveVertexTIN(TeDatabase* db, TeLayer* layer, TePointSet& ps,
			   TeTable& attTable)
{
//Adds the point set to the layer
//As addGeometry wasn�t called before, the table of polygons will have a default name
	if (!layer->addPoints(ps))
	  return false;

//Saves attributes table in database
  if (!layer->saveAttributeTable(attTable))
	  return false;

  return true;
}


bool
TeTin::saveTINdb(TeDatabase* db, string& outlayername, string& tablename)
{
  int triang = 0;
  TePolygonSet ps;
  TeBox bbox = this->box();

//Creates a projection
  TeDatum mDatum = TeDatumFactory::make("SAD69");
  TeProjection* pUTM = new TeUtm(mDatum,0.0);

//Checks if the attributes table already exist in database
  if(db->tableExist(tablename))
	  return false;

//Checks if the layer already exist in database
  if (db->layerExist(outlayername))
	  return false;

//Creates a new layer with selected layer's name
  TeLayer* layer = new TeLayer(outlayername, db, bbox, pUTM);
  if (layer->id() <= 0)   // layer wasn�t created properly
	  return false;

//Adds the geometry representation Polygons and stores it in a table with default name
  if (!layer->addGeometry(TePOLYGONS))
	  return false;

//Creates attribute table with name selected by user
  TeTable attTable (tablename);
  if(!createAttrTable(attTable, db, layer))
	  return false;

  TeTinTriangleIterator ti;
  for (ti = this->triangleBegin(); ti != this->triangleEnd(); ti++)
  {
	  long v0,v1,v2;
	  this->triangleVertices(*ti,v0,v1,v2);
	  if( vertex(v0).type() != ONBOXVERTEX && vertex(v1).type() != ONBOXVERTEX && vertex(v2).type() != ONBOXVERTEX) 
	  {
          TeCoord2D pt[3];
		  double val[3];

		//  Create triangles points
		  this->triangle3DPoints(*ti, pt[0], pt[1], pt[2], val[0], val[1], val[2]);

		//	Calculates triangle's slope
		  double slope;
		  this->slopeTriangle(*ti,slope,'g');

		// Calculates triangle's aspect
		  double aspect;
		  this->aspectTriangle(*ti,aspect);

		//  Create triangles
		  if (!createPolygon(ps, attTable, triang, pt[0], pt[1], pt[2], val[0],
						val[1], val[2],slope,aspect))
		  return false;

		  triang++;
	  }
  }
 
  if (!saveTIN(db, layer, ps, attTable))
	  return false;
  
  return true;
}

TeLayer*
TeTin::saveTINdb(TeDatabase* db, TeProjection* proj, string& outlayername, string& tablename)
{
  int triang = 0;
  TePolygonSet ps;
  TeBox bbox = this->box();

//Creates a projection
  TeProjection* pUTM = proj;

//Checks if the attributes table already exist in database
  if(db->tableExist(tablename))
	  return NULL;

//Checks if the layer already exist in database
  if (db->layerExist(outlayername))
	  return NULL;

//Creates a new layer with selected layer's name
  TeLayer* layer = new TeLayer(outlayername, db, bbox, pUTM);
  if (layer->id() <= 0)   // layer wasn�t created properly
	  return NULL;

//Adds the geometry representation Polygons and stores it in a table with default name
  if (!layer->addGeometry(TePOLYGONS))
	  return NULL;

//Creates attribute table with name selected by user
  TeTable attTable (tablename);
  if(!createAttrTable(attTable, db, layer))
	  return NULL;

  TeTinTriangleIterator ti;
  for (ti = this->triangleBegin(); ti != this->triangleEnd(); ti++)
  {
	  long v0,v1,v2;
	  this->triangleVertices(*ti,v0,v1,v2);
	  if( vertex(v0).type() != ONBOXVERTEX && vertex(v1).type() != ONBOXVERTEX && vertex(v2).type() != ONBOXVERTEX) 
	  {
          TeCoord2D pt[3];
		  double val[3];

		//  Create triangles points
		  this->triangle3DPoints(*ti, pt[0], pt[1], pt[2], val[0], val[1], val[2]);

		//	Calculates triangle's slope
		  double slope;
		  this->slopeTriangle(*ti,slope,'g');

		// Calculates triangle's aspect
		  double aspect;
		  this->aspectTriangle(*ti,aspect);

		//  Create triangles
		  if (!createPolygon(ps, attTable, triang, pt[0], pt[1], pt[2], val[0],
						val[1], val[2],slope,aspect))
		  return NULL;

		  triang++;
	  }
  }
 
  if (!saveTIN(db, layer, ps, attTable))
	  return NULL;
  
  return layer;
}

bool 
TeTin::saveVertexTINdb(TeDatabase* db, string& outlayername, string& tablename)
{
  int triang = 0;
  TePointSet ps;
  TeBox bbox = this->box();

//Creates a projection
  TeDatum mDatum = TeDatumFactory::make("SAD69");
  TeProjection* pUTM = new TeUtm(mDatum,0.0);

//Checks if the attributes table already exist in database
  if(db->tableExist(tablename))
	  return false;

//Checks if the layer already exist in database
  if (db->layerExist(outlayername))
	  return false;

//Creates a new layer with selected layer's name
  TeLayer* layer = new TeLayer(outlayername, db, bbox, pUTM);
  if (layer->id() <= 0)   // layer wasn�t created properly
	  return false;

//Adds the geometry representation Points and stores it in a table with default name
  if (!layer->addGeometry(TePOINTS))
	  return false;

//Creates attribute table with name selected by user
  TeTable attTable (tablename);

//Creates PointSet with TIN's vertex
  if(!this->createPointSet(ps,attTable,layer,db))
		return false;
   
  if (!saveVertexTIN(db, layer, ps, attTable))
	  return false;
  
  return true;
}

void
TeTin::borderUp ()
{
  unsigned long vii;
  unsigned long eii;
  unsigned long tit;
  long edge0, edge1, edge2;
  TeTinVertex vv;
  TeTinEdge e;
  TeTinTriangle t;

  //Search ONBOXVERTEX vertex
  for (vii = 0; vii < vertexSet_.size(); ++vii)
  {
	  if (vertexSet_[vii].type() == ONBOXVERTEX)
	  {//if vertex has ONBOXVERTEX type
	    //Search adjacent edges to the vertex
	    std::list <long> vauxedges;
		vertexEdges(vii, vauxedges);
		std::list<long>::iterator eit;
		for (eit = vauxedges.begin(); eit != vauxedges.end(); ++eit)
		{
		  //Swaps vertex reference in the edges (from and/or to) for NULL
		  long from = edgeSet_[(*eit)].from();
		  long to = edgeSet_[(*eit)].to();
		  if (from == vii)
			  edgeSet_[(*eit)].setVertices(-1, to);
		  else if (to == vii)
			  edgeSet_[(*eit)].setVertices(from, -1);
		}
		
		unsigned long viiaux;
		//For all vertex with index bigger than removed vertex
		for (viiaux = vii + 1; viiaux < vertexSet_.size(); ++viiaux)
		{
			std::list <long> vedges;
		    this->vertexEdges(viiaux, vedges);
		    //Updates vertex index in the adjacent edges
		    for (eit = vedges.begin(); eit != vedges.end(); ++eit)
		    {
		      long from = edgeSet_[(*eit)].from();
		      long to = edgeSet_[(*eit)].to();
			  if (from == viiaux)
                  edgeSet_[(*eit)].setVertices(from-1, to);
			  else if (to == viiaux)
                  edgeSet_[(*eit)].setVertices(from, to-1);
		    }
		}
		//Removes vertex from vertexSet
		vertexSet_.erase(vii);
		vii = vii - 1;
	  }//end if vertex has ONBOXVERTEX type
  }

  //Search edges with NULL vertex from and/or to
  for (eii = 0; eii < edgeSet_.size(); ++eii)
  {
	long vfrom = edgeSet_[eii].from();
	long vto = edgeSet_[eii].to();
	//if (edgeSet_[eii].from() == -1 || edgeSet_[eii].to() == -1)
	if (vfrom == -1 || vto == -1)
	{//if from or to are NULL
	//Swaps edge reference in the triangles for NULL
	  long tleft = edgeSet_[eii].left();
	  long tright = edgeSet_[eii].right();

	  //Check if triangle edges are equal eii
	  if (tleft != -1)
	  {
	    //left triangle
	    triangleSet_[tleft].edges(edge0, edge1, edge2);
	    if (edge0 == eii)
		    triangleSet_[tleft].setEdges(-1, edge1, edge2);
	    if (edge1 == eii)
		    triangleSet_[tleft].setEdges(edge0, -1, edge2);
	    if (edge2 == eii)
		    triangleSet_[tleft].setEdges(edge0, edge1, -1);
	  }
	  if (tright != -1)
	  {
	    //right triangle
	    triangleSet_[tright].edges(edge0, edge1, edge2);
	    if (edge0 == eii)
		    triangleSet_[tright].setEdges(-1, edge1, edge2);
	    if (edge1 == eii)
		    triangleSet_[tright].setEdges(edge0, -1, edge2);
	    if (edge2 == eii)
		    triangleSet_[tright].setEdges(edge0, edge1, -1);
	  }

	  //Checks if vertex from and to have reference to this edge in onEdge
	  //If, there is the reference, changes it to another adjacent edge.
	  std::list <long> edgesadj;
	  std::list<long>::iterator eit = edgesadj.begin();
	  if (vfrom != -1)
	  {
	    if (vertexSet_[vfrom].oneEdge() == eii)//vertex from
	    {
	      this->vertexEdges(vfrom, edgesadj);
		  for (eit = edgesadj.begin(); eit != edgesadj.end(); ++eit)
		  {
		    if ((*eit) != -1 && (*eit) != eii)
		    {
		      vertexSet_[vfrom].setOneEdge((*eit));
		      break;
		    }
		  }
	    }
	  }

	  if (vto != -1)
	  {
	    if (vertexSet_[vto].oneEdge() == eii)//vertex to
	    {
	      this->vertexEdges(vto, edgesadj);
		  for (eit = edgesadj.begin(); eit != edgesadj.end(); ++eit)
		  {
		    if ((*eit) != -1 && (*eit) != eii)
		    {
		      vertexSet_[vto].setOneEdge((*eit));
			  break;
		    }
		  }
	    }
	  }
	  
	  unsigned long eiiaux;
	  for (eiiaux = eii + 1; eiiaux < edgeSet_.size(); ++eiiaux)
	  {//For all edges with index bigger than removed edge
	    //Updates edge index in the triangles left and right
		  long left = edgeSet_[eiiaux].left();
		  long right = edgeSet_[eiiaux].right();
		  if (left != -1)
	      {
	        //left triangle
	        triangleSet_[left].edges(edge0, edge1, edge2);
	        if (edge0 == eiiaux)
		        triangleSet_[left].setEdges(edge0 - 1, edge1, edge2);
	        if (edge1 == eiiaux)
		        triangleSet_[left].setEdges(edge0, edge1 - 1, edge2);
	        if (edge2 == eiiaux)
		        triangleSet_[left].setEdges(edge0, edge1, edge2 - 1);
	      }
	      if (right != -1)
	      {
            //right triangle
	        triangleSet_[right].edges(edge0, edge1, edge2);
	        if (edge0 == eiiaux)
		        triangleSet_[right].setEdges(edge0 - 1, edge1, edge2);
	        if (edge1 == eiiaux)
		        triangleSet_[right].setEdges(edge0, edge1 - 1, edge2);
	        if (edge2 == eiiaux)
		        triangleSet_[right].setEdges(edge0, edge1, edge2 - 1);
	      }

	    //Updates onEdge of vertex
	    //provavel erro aqui...tem q testar se o onedge e o edge apontado.
		  //vertexSet_[edgeSet_[eiiaux].from()].setOneEdge(eiiaux-1);
		  //vertexSet_[edgeSet_[eiiaux].to()].setOneEdge(eiiaux-1);
		  if (vertexSet_[edgeSet_[eiiaux].from()].oneEdge() >= eiiaux)
		  	  vertexSet_[edgeSet_[eiiaux].from()].setOneEdge(eiiaux-1);
		  if (vertexSet_[edgeSet_[eiiaux].to()].oneEdge() >= eiiaux)
		  	  vertexSet_[edgeSet_[eiiaux].to()].setOneEdge(eiiaux-1);
		  
	  }

	  //Removes edge from edgeSet
	  edgeSet_.erase(eii);
	  eii = eii - 1;
	}//end if from or to are NULL
  }

  //Search triangles with NULL reference
  for (tit = 0; tit < triangleSet_.size(); ++tit)
  {
	triangleSet_[tit].edges(edge0, edge1, edge2);
	if (edge0 == -1 || edge1 == -1 || edge2 == -1)
	{//if triangle has NULL edge
	  //For each triangle to be removed:
	  //Changes triangle reference in the edges (left and right) to -1
	  if (edge0 != -1)
	  {
		if (this->edge(edge0).left() == tit)
		    this->edge(edge0).setTriangles(-1, this->edge(edge0).right());
		else if (this->edge(edge0).right() == tit)
		    this->edge(edge0).setTriangles(this->edge(edge0).left(), -1);
      }

	  if (edge1 != -1)
	  {
	    if (this->edge(edge1).left() == tit)
		    this->edge(edge1).setTriangles(-1, this->edge(edge1).right());
		else if (this->edge(edge1).right() == tit)
		    this->edge(edge1).setTriangles(this->edge(edge1).left(), -1);
	  }
	  if (edge2 != -1)
	  {
	    if (this->edge(edge2).left() == tit)
		    this->edge(edge2).setTriangles(-1, this->edge(edge2).right());
		else if (this->edge(edge2).right() == tit)
		    this->edge(edge2).setTriangles(this->edge(edge2).left(), -1);
	  }

	  //Updates triangle left and/or right of edges
	  for (eii = 0; eii < edgeSet_.size(); ++eii)
	  {
          //Swaps triangles left and/or right reference in the edges for 
          long tleft = edgeSet_[eii].left();
          long tright = edgeSet_[eii].right();
		  if (tleft >= tit)
			  edgeSet_[eii].setTriangles(tleft - 1,tright);
		  if (tright >= tit)
			  edgeSet_[eii].setTriangles(tleft, tright - 1);
	  }

	  //Removes triangle from triangleSet
	  triangleSet_.erase(tit);
	  tit = tit - 1;
	}//end if triangle has NULL edge
  }


}

void
TeTin::writeTriangleEdgesSPRFile (std::string& name, TeRaster* raster)
{
	fstream sprcfile;
	sprcfile.open ( name.c_str(), ios::out );

	sprcfile << "Total de vertices:" << vertexSet_.size()<<"\n"; 
	sprcfile << "Indice Type"<<"\n";
	for(unsigned int i=0;i < vertexSet_.size(); ++i)
	{
		TeCoord2D collin = raster->coord2Index(vertexSet_[i].location());

		sprcfile << i <<" "<< vertexSet_[i].type()<<" "
						   <<collin.x()<<"  "//<<vertexSet_[i].location().x()<<"  "
						   <<collin.y()<<"  "//<<vertexSet_[i].location().y()<<"  "
						   <<vertexSet_[i].value()<<"   "
						   <<vertexSet_[i].oneEdge()<<"\n";
	}

    sprcfile << "Lista de Edges"<<"\n";
	sprcfile << "Total de Edges:" << edgeSet_.size()<<"\n"; 
	sprcfile << "Indice  FROM  TO  LEFT  RIGHT"<<"\n";
	for(unsigned int i=0;i < edgeSet_.size(); ++i)
	{
		sprcfile << i <<"  "<< edgeSet_[i].from()<<"  "<<edgeSet_[i].to()<<"  "<<edgeSet_[i].left()<<"  "<<edgeSet_[i].right()<<"\n";
	}

	sprcfile << "Lista de Triangulos"<<"\n";
	sprcfile << "Total de Triangulos:"<<triangleSet_.size()<<"\n";
	sprcfile << "Indice  Edge0  Edge1  Edge2"<<"\n";
	for (unsigned int i =0; i<triangleSet_.size(); ++i)
	{
		long e0, e1, e2;
		triangleSet_[i].edges(e0,e1,e2);
		sprcfile << i <<"  "<< e0<<"  "<< e1<<"  "<< e2<<"\n";
	}

	TeTin::TeTinTriangleIterator ti;
	for (ti = this->triangleBegin(); ti != this->triangleEnd(); ti++)
	{
		TeCoord2D pt[3];
		long from, to;
		long edge0, edge1, edge2;
		long t1, t2;
		(*ti).edges(edge0, edge1, edge2);
		from = this->edge(edge0).from();
		to = this->edge(edge0).to();
		t1 = edgeSet_[edge0].left();
		t2 = edgeSet_[edge0].right();
		
		sprcfile << "Edge0: " << edge0 << "\n";
		sprcfile << "Left triangle: " << t1 << "\n";
		sprcfile << "Right triangle: " << t2 << "\n";
		sprcfile << "Vertex from: " << from << "\n";
		sprcfile << "Vertex to: " << to << "\n";
		sprcfile << "---------------------------" << "\n";
		sprcfile << "Edge1: " << edge1 << "\n";
		from = this->edge(edge1).from();
		to = this->edge(edge1).to();
		t1 = edgeSet_[edge1].left();
		t2 = edgeSet_[edge1].right();
		sprcfile << "Left triangle: " << t1 << "\n";
		sprcfile << "Right triangle: " << t2 << "\n";
		sprcfile << "Vertex from: " << from << "\n";
		sprcfile << "Vertex to: " << to << "\n";
		sprcfile << "---------------------------" << "\n";
		sprcfile << "Edge2: " << edge2 << "\n";
		from = this->edge(edge2).from();
		to = this->edge(edge2).to();
		t1 = edgeSet_[edge2].left();
		t2 = edgeSet_[edge2].right();
		sprcfile << "Left triangle: " << t1 << "\n";
		sprcfile << "Right triangle: " << t2 << "\n";
		sprcfile << "Vertex from: " << from << "\n";
		sprcfile << "Vertex to: " << to << "\n";
		sprcfile << "---------------------------" << "\n";
	}

	sprcfile.close ();
}

void
TeTin::areaTriangle (TeTinTriangle& t, float &area) //by Eduilson
{
	long v0, v1, v2;
	this->triangleVertices(t, v0, v1, v2);
	TeTinVertex vertex0, vertex1, vertex2;
	vertex0 = this->vertex(v0);
	vertex1 = this->vertex(v1);
	vertex2 = this->vertex(v2);
	//area = TriangleArea2D((float)vertex0.location().x(), (float)vertex0.location().y(),
	//	                  (float)vertex1.location().x(), (float)vertex1.location().y(),
	//					  (float)vertex2.location().x(), (float)vertex2.location().y());
}

bool 
TeTin::normalTriangle(TeTinTriangle& t, std::vector<double> &nvector) //by Eduilson (adaptado do SPRING)
{
	long v0, v1, v2;
	this->triangleVertices(t, v0, v1, v2);
	TeTinVertex vertex0, vertex1, vertex2;
	vertex0 = this->vertex(v0);
	vertex1 = this->vertex(v1);
	vertex2 = this->vertex(v2);

	nvector.clear();
	nvector.push_back(0);
	nvector.push_back(0);
	nvector.push_back(0);

	//	Define normal vector (uvx,uvy,uvz)
	double ux = vertex1.location().x() - vertex0.location().x(); 
	double vx = vertex2.location().x() - vertex0.location().x(); 
	double uy = vertex1.location().y() - vertex0.location().y(); 
	double vy = vertex2.location().y() - vertex0.location().y(); 
	double uz = vertex1.value() - vertex0.value();
	double vz = vertex2.value() - vertex0.value();

	if ( ( ux == 0 ) && ( vx == 0 ) )
	{
		nvector[0] = 1.;
		nvector[1] = 0.;
		nvector[2] = 0.;
		return true;
	}
	if ( ( uy == 0 ) && ( vy == 0 ) )
	{
		nvector[0] = 0.;
		nvector[1] = 1.;
		nvector[2] = 0.;
		return true;
	}
	if ( ( uz == 0 ) && ( vz == 0 ) )
	{
		nvector[0] = 0.;
		nvector[1] = 0.;
		nvector[2] = 1.;
		return true;
	}

	nvector[2] = (ux * vy) - (vx * uy);
	if (nvector[2] < 0.)
	{
		//Make sure that normal vector is always positive
		nvector[2] = -nvector[2];
		nvector[0] = (vy * uz) - (uy * vz);
		nvector[1] = (ux * vz) - (vx * uz);
	}
	else
	{
		nvector[0] = (uy * vz) - (vy * uz);
		nvector[1] = (vx * uz) - (ux * vz);
	}
	return true;
}

bool 
TeTin::normalTriangle(std::vector<TeTinVertex> vert, std::vector<double> &nvector) //by Eduilson (adaptado do SPRING)
{
	//long v0, v1, v2;
	//this->triangleVertices(t, v0, v1, v2);
	//TeTinVertex vertex0, vertex1, vertex2;
	//vertex0 = this->vertex(vert[0]);
	//vertex1 = this->vertex(vert[1]);
	//vertex2 = this->vertex(vert[2]);

	nvector.clear();
	nvector.push_back(0);
	nvector.push_back(0);
	nvector.push_back(0);

	//	Define normal vector (uvx,uvy,uvz)
	double ux = vert[1].location().x() - vert[0].location().x(); 
	double vx = vert[2].location().x() - vert[0].location().x(); 
	double uy = vert[1].location().y() - vert[0].location().y(); 
	double vy = vert[2].location().y() - vert[0].location().y(); 
	double uz = vert[1].value() - vert[0].value();
	double vz = vert[2].value() - vert[0].value();

	if ( ( ux == 0 ) && ( vx == 0 ) )
	{
		nvector[0] = 1.;
		nvector[1] = 0.;
		nvector[2] = 0.;
		return true;
	}
	if ( ( uy == 0 ) && ( vy == 0 ) )
	{
		nvector[0] = 0.;
		nvector[1] = 1.;
		nvector[2] = 0.;
		return true;
	}
	if ( ( uz == 0 ) && ( vz == 0 ) )
	{
		nvector[0] = 0.;
		nvector[1] = 0.;
		nvector[2] = 1.;
		return true;
	}

	nvector[2] = (ux * vy) - (vx * uy);
	if (nvector[2] < 0.)
	{
		//Make sure that normal vector is always positive
		nvector[2] = -nvector[2];
		nvector[0] = (vy * uz) - (uy * vz);
		nvector[1] = (ux * vz) - (vx * uz);
	}
	else
	{
		nvector[0] = (uy * vz) - (vy * uz);
		nvector[1] = (vx * uz) - (ux * vz);
	}
	return true;
}

void
TeTin::normalizeVector(std::vector<double>& nvector)
{
	double vectorSize = sqrt ( (nvector[0]*nvector[0]) + (nvector[1]*nvector[1]) + (nvector[2]*nvector[2]) );

	if ( vectorSize != 0. )
	{
		nvector[0] = nvector[0] / vectorSize;
		nvector[1] = nvector[1] / vectorSize;
		nvector[2] = nvector[2] / vectorSize;
	}
}

void
TeTin::slopeTriangle(TeTinTriangle& t,double &slope, char slopetype)
{
	slope = triangleGradient(t,'s',slopetype);
}

void
TeTin::aspectTriangle(TeTinTriangle& t, double &aspect)
{
	aspect = triangleGradient(t,'a',' ');
}


double
TeTin::triangleGradient(TeTinTriangle& t, char gradtype, char slopetype)
{
	long v0, v1, v2;
	this->triangleVertices(t, v0, v1, v2);
	TeTinVertex vertex0, vertex1, vertex2;
	vertex0 = this->vertex(v0);
	vertex1 = this->vertex(v1);
	vertex2 = this->vertex(v2);
	std::vector<double> nvector;
	double	moduv, decliv,
		pi180 = 180./3.1415927;
	double	m1, m2;
	double tol = (double).01;

	//	Special cases

	m1 = m2 = (double)TeMAXFLOAT;

	if(((double)vertex1.location().y() - (double)vertex0.location().y()) != (double)0.0)
		m1 = (vertex1.location().x() - vertex0.location().x()) / (vertex1.location().y() - vertex0.location().y());

	if(((double)vertex2.location().y() - (double)vertex0.location().y()) != (double)0.0)
		m2 = (vertex2.location().x() - vertex0.location().x()) / (vertex2.location().y() - vertex0.location().y());

	if (fabs(m1 - m2) < tol)
		//		Triangle with DUMMY Value
		return (double)TeMAXFLOAT;

	if ((vertex0.value() > TeTinBIGFLOAT) || (vertex1.value() > TeTinBIGFLOAT) || (vertex2.value() > TeTinBIGFLOAT))
		//		Triangle with DUMMY Value
		return (double)TeMAXFLOAT;

	if ((vertex0.value() == vertex1.value()) && (vertex0.value() == vertex2.value()))
	{
		if (gradtype == 's')
			//	Slope is zero
			return 0.;
		else
			//	exposition DUMMY
			return (double)TeMAXFLOAT;
	}

	this->normalTriangle(t, nvector);
	moduv = sqrt(pow(nvector[0],2.) + pow(nvector[1],2.) +
		pow(nvector[2],2.));

	if (gradtype == 's')
	{
		//Case Slope		
		if (slopetype == 'g') // degres
			decliv = pi180*acos(nvector[2]/moduv);
		else
			decliv = tan(acos(nvector[2]/moduv)) * 100.;
	}
	else
	{
		//Case Aspect		
		decliv = 90. - pi180*atan2(nvector[1],nvector[0]);
		if (decliv < 0.)
			decliv = 360. + decliv;
	}

	return decliv;
}


bool 
TeTin::createPointSet(TePointSet& ps, TeTable& atttable, TeLayer* layer, TeDatabase* db)
{
	//Creates an attribute table
	//Defines a list of attributes
	TeAttributeList attList;
	TeAttribute at;
	at.rep_.type_ = TeSTRING;
	at.rep_.numChar_ = 16;
	at.rep_.name_ = "object_id";
	at.rep_.isPrimaryKey_ = true;
	attList.push_back(at);

	at.rep_.type_ = TeREAL;
	at.rep_.name_ = "z";
	at.rep_.isPrimaryKey_ = false;
	at.rep_.decimals_ = 6;
	attList.push_back(at);

	atttable.setAttributeList(attList);
	atttable.setUniqueName("object_id");
	atttable.setLinkName("object_id");

	if (!layer->createAttributeTable(atttable))
		return false;

	for(unsigned int i=0;i < this->vertexSet_.size(); ++i)
	{
		if(vertexSet_[i].type() != ONBOXVERTEX)
		{
			TePoint pt(vertexSet_[i].location().x(),vertexSet_[i].location().y());
			pt.objectId(Te2String(i));
			ps.add(pt);
			TeTableRow row;
			row.push_back(Te2String(i));
			row.push_back(Te2String(vertexSet_[i].value(),6));
			atttable.add(row);
			row.clear();
		}
	}
	return true;
}

bool
TeTin::defineInterLinesColumns(TeRaster* raster, TeTinTriangle t, int& fline, int& lline, int& fcol, int& lcol)
{
	double rx1 = raster->box().x1();// + (raster->params().resx_ / 2);
	double ry2 = raster->box().y2();// - (raster->params().resy_ / 2);
	
	TeCoord2D llpt(TeCoord2D(TeMAXFLOAT, TeMAXFLOAT));
	TeCoord2D urpt(TeCoord2D(-TeMAXFLOAT, -TeMAXFLOAT));

	long v[3];
	//busca vertices do triangulo
	this->triangleVertices(t, v[0], v[1], v[2]);

	for (int i = 0; i < 3; i++)
	{
		TeTinVertex vertex = this->vertex(v[i]);

		if (vertex.type() == ONBOXVERTEX)
			return false;

		if (vertex.location() < llpt)
			llpt = vertex.location();
		if (urpt < vertex.location())
			urpt = vertex.location();
	}

	llpt.x(llpt.x() - (raster->params().resx_ / 1000));
	urpt.x(urpt.x() + (raster->params().resx_ / 1000));
	llpt.y(llpt.y() - (raster->params().resy_ / 1000));
	urpt.y(urpt.y() + (raster->params().resy_ / 1000));

	//Calculate lines and columns intercepted
	fcol = (int)((llpt.x() - rx1) / raster->params().resx_) - 1;
	lcol = (int)((urpt.x() - rx1) / raster->params().resx_) + 1;
	fline = (int)((ry2 - urpt.y()) / raster->params().resy_) - 1;
	lline = (int)((ry2 - llpt.y()) / raster->params().resy_) + 1;

	if ((raster->params().ncols_ <= fcol) || (lcol < 0) ||
		(raster->params().nlines_ <= fline) || (lline < 0))
		return false;

	return true;
}

void
TeTin::linearInterpolation(TeRaster* raster, int band, TeTinTriangle t, int fline, int lline,int fcol, int lcol)
{
	long v0,v1,v2;
	
	//busca vertices do triangulo
	this->triangleVertices(t,v0,v1,v2);
	std::list<long> vertices;

	TeTinVertex vertex0 = this->vertex(v0);
	TeTinVertex vertex1 = this->vertex(v1);
	TeTinVertex vertex2 = this->vertex(v2);

	double resx = raster->params().resx_;
	double resy = raster->params().resy_;

	double rx1 = raster->box().x1();// + (resx / 2);
	double ry2 = raster->box().y2();// - (resy / 2);

	double x1_x0 = vertex1.location().x() - vertex0.location().x();
	double x2_x0 = vertex2.location().x() - vertex0.location().x();
	double y1_y0 = vertex1.location().y() - vertex0.location().y();
	double y2_y0 = vertex2.location().y() - vertex0.location().y();
	double z1_z0 = vertex1.value() - vertex0.value();
	double z2_z0 = vertex2.value() - vertex0.value();

	for (int l = fline; l <= lline; l++)
	{
		for (int c = fcol; c <= lcol; c++)
		{
			TeCoord2D pt(TeCoord2D(rx1 + (c * resx), ry2 - (l * resy)));

			if (!this->triangleContainsPoint(t, pt))
				continue;

			double detx = ((y1_y0 * z2_z0) - (y2_y0 * z1_z0)) * (pt.x() - vertex0.location().x());
			double dety = ((z1_z0 * x2_x0) - (z2_z0 * x1_x0)) * (pt.y() - vertex0.location().y());
			double detz = (x1_x0 * y2_y0) - (x2_x0 * y1_y0);

			double z = ((detx + dety - (detz * vertex0.value())) / (- detz));

			raster->setElement(c, l, z, band);
		}
	}
}

bool
TeTin::interpolationPoint(TeCoord2D &pt, double &z)
{
	long t,v0,v1,v2;
	//busca triangulo onde incide o ponto
	t = this->triangleAt(pt);
	if (t == -1 || t== NULL)
	{
		z=-1;
		return false;
	}
	
	//busca vertices do triangulo
	this->triangleVertices(t,v0,v1,v2);
	std::list<long> vertices;
	
	//Preenche a lista com todos os vertices vizinhos ao ponto
	this->vertexOppVertices(v0,vertices);
	this->vertexOppVertices(v1,vertices);
	this->vertexOppVertices(v2,vertices);

	//Elimina vertices iguais
	vertices.sort();
	vertices.unique();

	double sum1=0, sum2=0;
	std::list<long>::iterator it_vert;
	for(it_vert = vertices.begin();it_vert!=vertices.end();it_vert++)
	{
		TeTinVertex &v = this->vertex(*it_vert);
		if(v.type() != ONBOXVERTEX ) //eliminar os vertices ONBOXVERTEX
		{
			TeCoord2D pt2(v.location().x(),v.location().y());
			double dist = TeDistance(pt,pt2);
			sum1 = sum1 + (v.value()/dist);
			sum2 = sum2 + (1/dist);
		}
	}

	z = sum1/sum2;
	return true;
}

bool 
TeTin::slopeaspectPoint(TeCoord2D &pt,double &s,double &a)
{
	//busca triangulo onde incide o ponto
	long t = this->triangleAt(pt);
	if (t == -1 || t== NULL)
		return false;
	this->slopeTriangle(triangle(t),s,'g');
	this->aspectTriangle(triangle(t),a);
	return true;
}

bool
TeTin::vertexOncontour(long &v)
{
	std::list<long> edges;
	std::list<long>::iterator ie;
	this->vertexEdges(v,edges);
	for(ie = edges.begin(); ie != edges.end(); ie++)
	{
		if( (edge(*ie).left() == -1) || (edge(*ie).right() == -1))
			return true;
	}
	return false;
}

bool
TeTin::createSampleSet(TeSampleSet& sample)
{
	for(unsigned int i=0;i < vertexSet_.size(); ++i)
		if(vertexSet_[i].type() != ONBOXVERTEX) 
			sample.add ( TeSample(TeCoord2D(vertexSet_[i].location().x(), vertexSet_[i].location().y()), vertexSet_[i].value()) );

	return true;
}

void
TeTin::setTolerances(double minedgesize, double isoTol, double dist)
{
	minedgesize_ = minedgesize;
	isoTol_ = isoTol;
	dist_ = dist;
}

double
TeTin::pointToSegmentDistance(TeCoord2D* fseg, TeCoord2D* lseg, TeCoord2D* pt, TeCoord2D* pti)
{
	double ux = lseg->x() - fseg->x();
	double uy = lseg->y() - fseg->y();
	double vx = pt->x() - fseg->x();
	double vy = pt->y() - fseg->y();
	double uv = ((ux * vx) + (uy * vy));

	if (uv < 0.)
	{
		if (pti != NULL)
			pti->setXY(lseg->x(), lseg->y());
		
		return (sqrt((vx * vx) + (vy * vy)));
	}
	else
	{
		ux = fseg->x() - lseg->x();
		uy = fseg->y() - lseg->y();
		vx = pt->x() - lseg->x();
		vy = pt->y() - lseg->y();
		uv = (ux * vx) + (uy * vy);

		if (uv < 0.)
		{
			if (pti != NULL)
				pti->setXY(lseg->x(), lseg->y());

			return (sqrt((vx * vx) + (vy * vy)));
		}
	}

	double a = lseg->y() - fseg->y();
	double b = fseg->x() - lseg->x();
	double c = (lseg->x() * fseg->y()) - (fseg->x() * lseg->y());
	double aabb = (a * a) + (b * b);

	double dist = fabs(((a * pt->x()) + (b * pt->y()) + c) / (sqrt(aabb)));
	
	//if (pti != NULL)
	//{
		double k = (b * pt->x()) - (a * pt->y());
		double x = ((b * k) - (a * c)) / aabb;
		double y = ((-a * k) - (b * c)) / aabb;
		pti->setXY(x, y);
	//}

	return dist;
}