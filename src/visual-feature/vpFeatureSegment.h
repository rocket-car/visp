/****************************************************************************
 *
 * $Id: vpFeatureThetaU.h 3530 2012-01-03 10:52:12Z fspindle $
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2012 by INRIA. All rights reserved.
 * 
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact INRIA about acquiring a ViSP Professional 
 * Edition License.
 *
 * See http://www.irisa.fr/lagadic/visp/visp.html for more information.
 * 
 * This software was developed at:
 * INRIA Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 * http://www.irisa.fr/lagadic
 *
 * If you have questions regarding the use of this file, please contact
 * INRIA at visp@inria.fr
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * Description:
 * Segment visual feature.
 *
 * Authors:
 * Filip Novotny
 *
 *****************************************************************************/


#ifndef vpFeatureSegment_H
#define vpFeatureSegment_H

/*!
  \file vpFeatureSegment.h
  \brief class that defines the Segment visual feature
*/

#include <visp/vpMatrix.h>
#include <visp/vpPoint.h>
#include <visp/vpBasicFeature.h>
#include <visp/vpRGBa.h>

/*!
  \class vpFeatureSegment
  \ingroup VsFeature3

  \brief Class that defines a Segment visual feature. The segment is 
  described as angle and [...]

*/
class VISP_EXPORT vpFeatureSegment : public vpBasicFeature
{
public:
  

public:
  // Basic construction.
  void init() ;
  // Basic constructor.
  vpFeatureSegment(vpPoint& P1,vpPoint& P2);
  	  
  //! Destructor. Does nothing.
  ~vpFeatureSegment() { if (flags != NULL) delete [] flags; }

  inline static unsigned int selectXc()  { return FEATURE_LINE[0] ; }
  inline static unsigned int selectYc()  { return FEATURE_LINE[1] ; }
  inline static unsigned int selectL()  { return FEATURE_LINE[2] ; }
  inline static unsigned int selectAlpha()  { return FEATURE_LINE[3] ; }
  // compute the interaction matrix from a subset a the possible features
  vpMatrix  interaction(const unsigned int select = FEATURE_ALL);
  // compute the error between two visual features from a subset
  // a the possible features
  vpColVector error(const vpBasicFeature &s_star,
		    const unsigned int select = FEATURE_ALL)  ;
  void print(const unsigned int select= FEATURE_ALL) const ;

  //! Feature duplication.
  vpFeatureSegment *duplicate() const ;

  //! change values of the sengment
  void buildFrom(vpPoint& P1,vpPoint& P2);
public:
  void display(const vpCameraParameters &cam,
               vpImage<unsigned char> &I,
               vpColor color=vpColor::green, 
	       unsigned int thickness=1) const ;
  void display(const vpCameraParameters &cam,
               vpImage<vpRGBa> &I,
               vpColor color=vpColor::green, 
	       unsigned int thickness=1) const ;
 private:
  double l;
  double Xc;
  double Yc;
  double alpha;
  double z1;
  double z2;
  double cos_a;
  double sin_a;
} ;


#endif

/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */