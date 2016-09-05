#include "facets.h"
#include <stdexcept>
#include <algorithm>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>

using namespace std;
Facets::Facets(): facets(new vector<Facet>()){};
Facets::Facets( const Facets &other ): facets(new vector<Facet>())
{
  this->swap(other);
}

Facets& Facets::operator =( const Facets &other )
{
  this->swap(other);
  return *this;
}

Facets::~Facets()
{
  delete facets;
}

void Facets::add( Facet facet )
{
  facets->push_back( facet );
}

void Facets::computeDistanceFromSource( const Vec3 &sourcePos )
{
  for ( unsigned int i=0;i<facets->size();i++ )
  {
    (*facets)[i].computeDistanceFromSource( sourcePos );
  }
  hasComputedDistanceFromSource = true;
  reverse( facets->begin(), facets->end() ); // Swap to descending
} 

void Facets::sortByDistanceFromSource()
{
  if ( !hasComputedDistanceFromSource )
  {
    throw (invalid_argument("You have to call computeDistanceFromSource before any call to sortByDistanceFromSource!") );
  }
  sort( facets->begin(), facets->end() );
}


void Facets::swap( const Facets& other )
{
  *facets = *other.facets;
  hasComputedDistanceFromSource = other.hasComputedDistanceFromSource;
} 

void Facets::saveVTK( const string &fname ) const
{
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New(); 
  // Fill the points array
  for ( unsigned int i=0;i<Facet::nodesCrd.size();i++ )
  {
    Vec3 vec = Facet::nodesCrd[i];
    points->InsertNextPoint(vec.getX(), vec.getY(), vec.getZ() );
  } 

  vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();

  // Fill triangle array
  for ( unsigned int i=0;i<this->size();i++ )
  {
    vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
    const unsigned int *nodes = (*facets)[i].getNodes();
    triangle->GetPointIds()->SetId(0, nodes[0]);
    triangle->GetPointIds()->SetId(1, nodes[1]);
    triangle->GetPointIds()->SetId(2, nodes[2]);
    triangles->InsertNextCell(triangle);
  }

  // Unstructured grid
  vtkSmartPointer<vtkUnstructuredGrid> grid = vtkSmartPointer<vtkUnstructuredGrid>::New(); 
  grid->SetPoints( points );
  grid->SetCells( VTK_TRIANGLE, triangles ); 
}
