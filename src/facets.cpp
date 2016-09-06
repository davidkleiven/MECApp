#include "facets.h"
#include <stdexcept>
#include <algorithm>
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

void Facets::saveIlluminationVTK( const string &fname ) const
{
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New(); 
  points->SetDataTypeToDouble();

  // Fill the points array
  for ( unsigned int i=0;i<Facet::nodesCrd.size();i++ )
  {
    Vec3 vec = Facet::nodesCrd[i];
    points->InsertNextPoint(vec.getX(), vec.getY(), vec.getZ() );
  } 

  vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();

  // Fill triangle array
  vtkSmartPointer<vtkUnsignedCharArray> ilumnData = vtkSmartPointer<vtkUnsignedCharArray>::New();
  ilumnData->SetNumberOfComponents(3);
  ilumnData->SetName("Illumination");
  unsigned char red[3] = {255,0,0};
  unsigned char grey[3] = {80,80,80};
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
      ilumnData->InsertNextTypedTuple(red); // New in VTK 7.1 TypedTuple was TupleValue before
    }
    else
    {
      ilumnData->InsertNextTypedTuple(grey); // New in VTK 7.1 TypedTuple was TupleValue before
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
