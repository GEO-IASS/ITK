/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include <iostream>
#include "itkLabelMap.h"
#include "itkLabelObject.h"
#include "itkLabelMapToLabelImageFilter.h"

int itkLabelMapToLabelImageFilterTest(int argc, char * argv[])
{

  if( argc != 1 )
    {
    std::cerr << "usage: " << argv[0] << "" << std::endl;
    return EXIT_FAILURE;
    }

  const int dim = 2;

  typedef itk::LabelObject< unsigned long, dim > LabelObjectType;
  typedef LabelObjectType::IndexType             IndexType;
  typedef itk::LabelMap< LabelObjectType >       LabelMapType;
  typedef LabelMapType::SizeType                 SizeType;
  typedef itk::Image< unsigned char, dim >       ImageType;

  typedef itk::LabelMapToLabelImageFilter<LabelMapType, ImageType> LabelMapToLabelImageFilterType;

  LabelMapType::Pointer map = LabelMapType::New();

  SizeType sizeIn;
  sizeIn[0] = 11;
  sizeIn[1] = 11;
  map->SetRegions( sizeIn );
  map->Allocate();

  IndexType idxHorizontal;
  idxHorizontal[0] = 0;
  idxHorizontal[1] = 5;
  map->SetLine( idxHorizontal, 11, 1);

  IndexType idxVertical;
  idxVertical[0] = 5;
  for (int ctr=0; ctr<5; ctr++)
    {
    idxVertical[1] = ctr;
    map->SetPixel( idxVertical, 1 );
    }
  for (int ctr=6; ctr<11; ctr++)
    {
    idxVertical[1] = ctr;
    map->SetPixel( idxVertical, 1 );
    }

  LabelMapToLabelImageFilterType::Pointer conversion = LabelMapToLabelImageFilterType::New();
  conversion->SetInput( map );
  conversion->Update( );

  ImageType::Pointer image;
  image = conversion->GetOutput();

  for (int ctrI=0; ctrI<11; ctrI++)
    {
    for (int ctrJ=0; ctrJ<11; ctrJ++)
      {
      IndexType index;
      index[0] = ctrI;
      index[1] = ctrJ;
      unsigned char val;
      val = image->GetPixel(index);
      if ( (ctrI == 5) || (ctrJ==5) )
        {
        itkAssertOrThrowMacro( (val == 1), "Error in Label Image.");
        }
      else
        {
        itkAssertOrThrowMacro( (val == 0), "Error in Label Image.");
        }
      }
    }

  conversion->Print( std::cout );

  return EXIT_SUCCESS;
}
