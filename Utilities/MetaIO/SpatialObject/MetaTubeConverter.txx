/*=========================================================================

  Program:   itkUNC
  Module:    MetaTubeConverter.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$
  Author:    Julien Jomier (julien@jomier.com)

  Copyright (c) 2002 CADDLab @ UNC. All rights reserved.
  See itkUNCCopyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __MetaTubeConverter__txx
#define __MetaTubeConverter__txx

#include "MetaTubeConverter.h"

/** Constructor */ 
template <unsigned int NDimensions>                                          
MetaTubeConverter<NDimensions>
::MetaTubeConverter()
{
  
}


/** Convert a metaTube into an Tube SpatialObject  */
template <unsigned int NDimensions>       
typename MetaTubeConverter<NDimensions>::SpatialObjectPointer
MetaTubeConverter<NDimensions>
::MetaTubeToTubeSpatialObject(MetaTube * tube)
{ 
  typedef itk::TubeSpatialObject<NDimensions> TubeSpatialObjectType;
  typename TubeSpatialObjectType::Pointer tub = TubeSpatialObjectType::New();
  double spacing[NDimensions];

  tub->SetReferenceCount(2);

  unsigned int ndims = tube->NDims();
  for(unsigned int i=0;i<ndims;i++)
  {
    spacing[i]=tube->ElementSpacing()[i];
  }

  tub->GetIndexToObjectTransform()->SetScaleComponent(spacing);
  tub->GetProperty()->SetName((char*)tube->Name());
  tub->SetParentPoint(tube->ParentPoint());
  tub->SetId(tube->ID());
  tub->SetParentId(tube->ParentID());
  tub->GetProperty()->SetRed(tube->Color()[0]);
  tub->GetProperty()->SetGreen(tube->Color()[1]);
  tub->GetProperty()->SetBlue(tube->Color()[2]);
  tub->GetProperty()->SetAlpha(tube->Color()[3]);

  typedef itk::TubeSpatialObjectPoint<NDimensions> TubePointType;
  typedef TubePointType* TubePointPointer;

  typedef MetaTube::PointListType ListType;
  ListType::iterator it2 = tube->GetPoints().begin();
    
  itk::CovariantVector<double,NDimensions> v; 
  itk::Vector<double,NDimensions> t;
  
  for(unsigned int id=0;id< tube->GetPoints().size();id++)
  {
    TubePointType pnt;
    
    typedef typename TubeSpatialObjectType::PointType PointType;
    PointType point;

    for(unsigned int i=0;i<ndims;i++)
    {
      point[i]=(*it2)->m_X[i];
    }

    pnt.SetPosition(point);
    pnt.SetRadius((*it2)->m_R);
    pnt.SetMedialness((*it2)->m_Medialness);
    pnt.SetRidgeness((*it2)->m_Ridgeness); 
    pnt.SetBranchness((*it2)->m_Branchness);
    pnt.SetMark((*it2)->m_Mark);  

    for(unsigned int i=0;i<ndims;i++)
      {
      v[i]=(*it2)->m_V1[i];
      }
    pnt.SetNormal1(v);

    for(unsigned int i=0;i<ndims;i++)
      {
      v[i]=(*it2)->m_V2[i];
      }
    pnt.SetNormal2(v);

    for(unsigned int i=0;i<ndims;i++)
      {
      t[i]=(*it2)->m_T[i];
      }
    pnt.SetTangent(t);

    pnt.SetAlpha1((*it2)->m_Alpha1);
    pnt.SetAlpha2((*it2)->m_Alpha2);
    pnt.SetAlpha3((*it2)->m_Alpha3);
   
    pnt.SetRed((*it2)->m_Color[0]);
    pnt.SetGreen((*it2)->m_Color[1]);
    pnt.SetBlue((*it2)->m_Color[2]);
    pnt.SetAlpha((*it2)->m_Color[3]);

    pnt.SetID((*it2)->m_ID);

    tub->GetPoints().push_back(pnt);

    it2++;
  }
 
  return tub;
}

/** Convert an Tube SpatialObject into a metaTube */
template <unsigned int NDimensions>       
MetaTube*
MetaTubeConverter<NDimensions>
::TubeSpatialObjectToMetaTube(SpatialObjectType * spatialObject)
{ 
  MetaTube* tube = new MetaTube(NDimensions);

  // fill in the tube information
   
  typename SpatialObjectType::PointListType::const_iterator i;
  for(i = dynamic_cast<SpatialObjectType*>(spatialObject)->GetPoints().begin(); 
      i != dynamic_cast<SpatialObjectType*>(spatialObject)->GetPoints().end();
      i++)
  {
    TubePnt* pnt = new TubePnt(NDimensions);

    for(unsigned int d=0;d<NDimensions;d++)
    {
      pnt->m_X[d] = (*i).GetPosition()[d];
    }
      
    pnt->m_ID = (*i).GetID();
    pnt->m_R=(*i).GetRadius();
    pnt->m_Alpha1=(*i).GetAlpha1();
    pnt->m_Alpha2=(*i).GetAlpha2();
    pnt->m_Alpha3=(*i).GetAlpha3();
    pnt->m_Medialness=(*i).GetMedialness();
    pnt->m_Ridgeness=(*i).GetRidgeness();
    pnt->m_Branchness=(*i).GetBranchness();
    pnt->m_Mark=(*i).GetMark();

    for(unsigned int d=0;d<NDimensions;d++)
    {
      pnt->m_V1[d]=(*i).GetNormal1()[d];
    }

    for(unsigned int d=0;d<NDimensions;d++)
    {
      pnt->m_V2[d]=(*i).GetNormal2()[d];
    }

    for(unsigned int d=0;d<NDimensions;d++)
    {
      pnt->m_T[d]=(*i).GetTangent()[d];
    }
              
    pnt->m_Color[0] = (*i).GetRed();
    pnt->m_Color[1] = (*i).GetGreen();
    pnt->m_Color[2] = (*i).GetBlue();
    pnt->m_Color[3] = (*i).GetAlpha();

    tube->GetPoints().push_back(pnt); 

  }


    
  if(NDimensions == 2)
  {
    tube->PointDim("x y r rn mn bn mk v1x v1y tx ty a1 a2 red green blue alpha id");
  }
  else
  {
    tube->PointDim("x y z r rn mn bn mk v1x v1y v1z v2x v2y v2z tx ty tz a1 a2 a3 red green blue alpha id");
  }

  float color[4];
  for(unsigned int i=0;i<4;i++)
  {
    color[i]=spatialObject->GetProperty()->GetColor()[i];
  }

  tube->Color(color);
  tube->ID( spatialObject->GetId());

  if(spatialObject->GetParent())
  {
    tube->ParentID(spatialObject->GetParent()->GetId());
  }
  tube->ParentPoint(spatialObject->GetParentPoint());
  tube->NPoints(tube->GetPoints().size());

  for(unsigned int i=0;i<NDimensions;i++)
  {
    tube->ElementSpacing(i,spatialObject->GetIndexToObjectTransform()->GetScaleComponent()[i]);
  }
  return tube;
}


/** Read a meta file give the type */
template <unsigned int NDimensions>       
typename MetaTubeConverter<NDimensions>::SpatialObjectPointer
MetaTubeConverter<NDimensions>
::ReadMeta(const char* name)
{
  SpatialObjectPointer spatialObject;
  MetaTube* Tube = new MetaTube();
  Tube->Read(name);
  spatialObject = MetaTubeToTubeSpatialObject(Tube);
  delete Tube;
  return spatialObject;
}


/** Write a meta Tube file */
template <unsigned int NDimensions>
bool
MetaTubeConverter<NDimensions>
::WriteMeta(SpatialObjectType* spatialObject,const char* name)
{
  MetaTube* Tube = TubeSpatialObjectToMetaTube(spatialObject);
  Tube->Write(name);
  delete Tube;
  return true;
}

#endif
