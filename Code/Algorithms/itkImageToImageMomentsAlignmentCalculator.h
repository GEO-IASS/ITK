/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImageToImageMomentsAlignmentCalculator.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

#ifndef __itkImageToImageMomentsAlignmentCalculator_h
#define __itkImageToImageMomentsAlignmentCalculator_h

#include "itkAffineTransform.h"
#include "itkObject.h"
#include "itkImageMomentsCalculator.h"

namespace itk
{

/** 
 * \Compute initial parameters for an affine transformation.
 *  The two inputs are images that we want to adjust.
 *  The output is the transformation that aligns the two images
 * 
 * \ingroup Operators
 */

template <class TReference, class TTarget>          
class ITK_EXPORT ImageToImageMomentsAlignmentCalculator: public Object 
{
public:

  /**
   * Standard "Self" typedef.
   */
  typedef ImageToImageMomentsAlignmentCalculator  Self;


  /**
   * Standard "Superclass" typedef.
   */
  typedef Object  Superclass;


  /** 
   * Smart pointer typedef support 
   */
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /**
   *  Type of the Reference
   */
  typedef TReference  ReferenceType;

  /**
   *  Type of the Target
   */
  typedef TTarget TargetType;

  /**
   *  Pointer type for the Reference 
   */
  typedef typename ReferenceType::ConstPointer ReferenceConstPointer;
  
  /**
   *  Pointer type for the Target 
   */
  typedef typename TargetType::ConstPointer TargetConstPointer;

  /**
   *  Typedef for the image moments calculator
   */
  typedef ImageMomentsCalculator<ReferenceType>  ImageMomentsCalculatorType;

  /**
   * Standard affine transform type for this class
   */  
  enum {ImageDimension = ReferenceType::ImageDimension};

  typedef AffineTransform<double, ImageDimension> AffineTransformType;

  /** 
   * Run-time type information (and related methods).
   */
  itkTypeMacro(Self, Object);

  /**
   * Method for creation through the object factory.
   */
  itkNewMacro(Self);

  /**
   * Set the Target
   */
  void SetTarget( TargetType * );
   
  /**
   * Set the Reference
   */
  void SetReference( ReferenceType * );

  /**
   * Execute 
   */
  void Execute(void);

  /**
   * Get the Tranformation
   */
  itkGetMacro(OutputTransform ,AffineTransformType);


protected:

  ImageToImageMomentsAlignmentCalculator();
  virtual ~ImageToImageMomentsAlignmentCalculator();
  ImageToImageMomentsAlignmentCalculator(const Self&);
  const Self & operator=(const Self&);
  
private:
   
  ReferenceConstPointer     m_Reference;
  TargetConstPointer        m_Target;
  AffineTransformType       m_OutputTransform;

};  


}; // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkImageToImageMomentsAlignmentCalculator.txx"
#endif

#endif 
