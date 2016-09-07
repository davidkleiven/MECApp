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
Facets::Facets(): facets(new vector<Facet>()), boundaries(new set<RegionBoundary>()), fresnel(new Fresnel()){};
Facets::Facets( const Facets &other ): facets(new vector<Facet>()), boundaries(new set<RegionBoundary>()), fresnel(new Fresnel())
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
  delete fresnel;
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
  *fresnel = *other.fresnel;
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

  vtkSmartPointer<vtkDoubleArray> eqElectric = vtkSmartPointer<vtkDoubleArray>::New();
  eqElectric->SetNumberOfComponents(3);
  eqElectric->SetName("Equivalent Electric Current");

   
  vtkSmartPointer<vtkDoubleArray> eqMagnetic = vtkSmartPointer<vtkDoubleArray>::New();
  eqMagnetic->SetNumberOfComponents(3);
  eqMagnetic->SetName("Equivalent Magnetic Current");
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

    if ( hasComputedEqCurrents )
    {
      double elX = abs((*facets)[i].getEquivalentCurrent().electric.getX());
      double elY = abs((*facets)[i].getEquivalentCurrent().electric.getY());
      double elZ = abs((*facets)[i].getEquivalentCurrent().electric.getZ());
      double magX = abs((*facets)[i].getEquivalentCurrent().magnetic.getX());
      double magY = abs((*facets)[i].getEquivalentCurrent().magnetic.getY());
      double magZ = abs((*facets)[i].getEquivalentCurrent().magnetic.getZ());
      eqElectric->InsertNextTuple3(elX,elY,elZ);
      eqMagnetic->InsertNextTuple3(magX,magY,magZ);
    }
  }

  // Unstructured grid
  vtkSmartPointer<vtkPolyData> polys = vtkSmartPointer<vtkPolyData>::New(); 
  polys->SetPoints( points );
  polys->SetPolys( triangles );  
  polys->GetCellData()->SetScalars( ilumnData );
  polys->GetCellData()->AddArray( eqElectric );
  polys->GetCellData()->AddArray( eqMagnetic );

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

void Facets::addRegion( RegionBoundary &boundary )
{
  boundaries->insert(boundary);
} 

void Facets::computeEquivalentCurrent( const Vec3<double> &E_inc, const Vec3<double> &waveVector )
{
  set<RegionBoundary>::iterator currentBoundary = boundaries->begin();
  fresnel->setMaterial( currentBoundary->getMat(RegionBoundary::Domain_t::INCIDENT), RegionBoundary::Domain_t::INCIDENT );
  fresnel->setMaterial( currentBoundary->getMat(RegionBoundary::Domain_t::SCATTERED), RegionBoundary::Domain_t::SCATTERED );  
  for ( unsigned int i=0;i<facets->size();i++ )
  {
    if ( !(*facets)[i].getIllumination() )
    {
      continue;
    }
    if ( i >= currentBoundary->getMaxElm() )
    {
      if ( currentBoundary != boundaries->end() )
      {
        ++currentBoundary;
      }
      // Using a pointer to a stack variable inside Region boundary
      // This requires that the compiler does not free the RegionBoundary object
      // Potential errors if using compiler optimization, think it should be OK though
      fresnel->setMaterial( currentBoundary->getMat(RegionBoundary::Domain_t::INCIDENT), RegionBoundary::Domain_t::INCIDENT );
      fresnel->setMaterial( currentBoundary->getMat(RegionBoundary::Domain_t::SCATTERED), RegionBoundary::Domain_t::SCATTERED );  
    }
    Vec3<double> normal = (*facets)[i].getNormal();
    fresnel->equivalentCurrent( E_inc, normal, waveVector, (*facets)[i].getEquivalentCurrent() );
  }
  hasComputedEqCurrents = true;
} 
    
