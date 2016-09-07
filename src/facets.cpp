#include "facets.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "vtkTriangle.h"
#include "vtkCellArray.h"
#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkCellData.h"
#include "vtkPoints.h"
#include "vtkXMLUnstructuredGridWriter.h"
#include "vtkXMLPolyDataWriter.h"
#include "vtkUnstructuredGrid.h"
#include "vtkUnsignedCharArray.h"
#include "vtkDoubleArray.h"

using namespace std;
Facets::Facets(): facets(new vector<Facet>()), boundaries(new set<RegionBoundary>()){};
Facets::Facets( const Facets &other ): facets(new vector<Facet>()), boundaries(new set<RegionBoundary>())
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
  delete boundaries;
}

void Facets::add( const Facet &facet )
{
  facets->push_back( facet );
}

void Facets::computeDistanceFromSource( const Vec3<double> &sourcePos )
{
  for ( unsigned int i=0;i<facets->size();i++ )
  {
    (*facets)[i].computeDistanceFromSource( sourcePos );
  }
  hasComputedDistanceFromSource = true;
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
  *boundaries = *other.boundaries;
  hasComputedDistanceFromSource = other.hasComputedDistanceFromSource;
} 

void Facets::saveIlluminationVTK( const string &fname ) const
{
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New(); 

  // Fill the points array
  for ( unsigned int i=0;i<Facet::nodesCrd.size();i++ )
  {
    Vec3<double> vec = Facet::nodesCrd[i];
    points->InsertNextPoint(vec.getX(), vec.getY(), vec.getZ() );
  } 

  vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();

  // Fill triangle array
  vtkSmartPointer<vtkDoubleArray> ilumnData = vtkSmartPointer<vtkDoubleArray>::New();
  ilumnData->SetNumberOfComponents(1);
  ilumnData->SetName("Illumination");
  for ( unsigned int i=0;i<this->size();i++ )
  {
    vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
    const unsigned int *nodes = (*facets)[i].getNodes();
    triangle->GetPointIds()->SetId(0, nodes[0]);
    triangle->GetPointIds()->SetId(1, nodes[1]);
    triangle->GetPointIds()->SetId(2, nodes[2]);
    triangles->InsertNextCell(triangle);
   
    if ( (*facets)[i].getIllumination() )
    {
      ilumnData->InsertNextTuple1(1.0); // New in VTK 7.1 TypedTuple was TupleValue before
    }
    else
    {
      ilumnData->InsertNextTuple1(0.0); // New in VTK 7.1 TypedTuple was TupleValue before
    }
  }

  // Unstructured grid
  vtkSmartPointer<vtkPolyData> polys = vtkSmartPointer<vtkPolyData>::New(); 
  polys->SetPoints( points );
  polys->SetPolys( triangles );  
  polys->GetCellData()->SetScalars( ilumnData );

  // Write file
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName( fname.c_str() );
  writer->SetInputData( polys );
  writer->Write(); 
}

void Facets::illuminate()
{
  for ( vector<Facet>::iterator it=facets->begin(); it != facets->end(); ++it )
  {
    for ( vector<Facet>::iterator innerIt=facets->begin(); innerIt != it; ++innerIt )
    { 
      if ( it->isBehindOther(*innerIt) )
      {
        it->setIllumination( false );
        break;
      }
    }
  }
}
