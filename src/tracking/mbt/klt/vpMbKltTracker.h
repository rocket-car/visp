/****************************************************************************
 *
 * $Id$
 *
 * Copyright (C) 1998-2010 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * Model based tracker using only KLT
 *
 * Authors:
 * Romain Tallonneau
 * Aurelien Yol
 *
 *****************************************************************************/

#ifndef vpMbKltTracker_h
#define vpMbKltTracker_h

#if (VISP_HAVE_OPENCV_VERSION >= 0x020101)
#   include <opencv2/imgproc/imgproc.hpp>
#else
#   include <cv.h>
#endif

#include <visp/vpConfig.h>
#include <visp/vpMbTracker.h>
#include <visp/vpKltOpencv.h>
#include <visp/vpMbtKltHiddenFace.h>
#include <visp/vpMeterPixelConversion.h>
#include <visp/vpPixelMeterConversion.h>
#include <visp/vpDisplayX.h>
#include <visp/vpMbtKltXmlParser.h>
#include <visp/vpHomography.h>
#include <visp/vpRobust.h>
#include <visp/vpSubColVector.h>
#include <visp/vpSubMatrix.h>
#include <visp/vpExponentialMap.h>

/*!
  \class vpMbKltTracker

  \ingroup ModelBasedTracking
*/
class VISP_EXPORT vpMbKltTracker: virtual public vpMbTracker
{
private:
  //! Temporary OpenCV image for fast conversion.
  IplImage* cur;
  //! Initial pose.
  vpHomogeneousMatrix c0Mo;
  //! Angle used to detect a face apparition
  double angleAppears;
  //! Angle used to detect a face disparition
  double angleDesappears;
  //! If true, compute the interaction matrix at each iteration of the minimisation. Otherwise, compute it only on the first iteration.
  bool compute_interaction;
  //! Flag to specify whether the init method is called the first or not (specific calls to realise in this case).
  bool firstInitialisation;
  //! Erosion of the mask
  unsigned int maskBorder;
  //! The gain of the virtual visual servoing stage. 
  double lambda;
  //! The maximum iteration of the virtual visual servoing stage. 
  unsigned int  maxIter;
  //! Threshold below which the weight associated to a point to consider this one as an outlier.
  double threshold_outlier;
  
protected:
  //! The estimated displacement of the pose between the current instant and the initial position.
  vpHomogeneousMatrix ctTc0;
  //! Points tracker.
  vpKltOpencv tracker;
  //! Map of the points in the initial image with their unique identifier as a key.
  std::map<int, vpImagePoint> iPI0;
  //! Each face currently tracked.
  vpMbtKltHiddenFaces faces;
  
public:
  
            vpMbKltTracker();
  virtual   ~vpMbKltTracker();
  
  virtual void            display(const vpImage<unsigned char>& _I, const vpHomogeneousMatrix &_cMo, const vpCameraParameters &_cam, const vpColor& col , const unsigned int l=1, const bool displayFullModel = false);
  virtual void            display(const vpImage<vpRGBa>& _I, const vpHomogeneousMatrix &_cMo, const vpCameraParameters &_cam, const vpColor& col , const unsigned int l=1, const bool displayFullModel = false);

protected:
  virtual void            init(const vpImage<unsigned char>& _I);
  
public:
  virtual void            loadConfigFile(const std::string& _configFile);
          void            loadConfigFile(const char* filename);
          
          /*!
            Get the threshold for the acceptation of a point.

            \return threshold_outlier : Threshold for the weight below which a point is rejected.
          */
  inline  double          getThresholdAcceptation() { return threshold_outlier;}
  
          /*!
            Get the erosion of the mask used on the Model faces.

            \return The erosion.
          */
  inline  unsigned int    getMaskBorder() { return maskBorder; }
          
          /*!
            Get the value of the gain used to compute the control law.
            
            \return the value for the gain.
          */
  inline  double          getLambda() {return lambda;}
  
          /*!
            Get the maximum iteration of the virtual visual servoing stage.
            
            \return the number of iteration
          */
  inline  unsigned int    getMaxIter() {return maxIter;}
  
          void            setCameraParameters(const vpCameraParameters& _cam);
          
          /*!
            Set the value of the gain used to compute the control law.
            
            \param lambda : the desired value for the gain.
          */
  inline  void            setLambda(const double lambda) {this->lambda = lambda;}
  
          /*!
            Set the erosion of the mask used on the Model faces.

            \param  e : The desired erosion.
          */
          void            setMaskBorder(unsigned int &e){ maskBorder = e; }
  
          /*!
            Set the maximum iteration of the virtual visual servoing stage.
            
            \param max : the desired number of iteration
          */
  inline  void            setMaxIter(const unsigned int max) {maxIter = max;}
  
          void            setPose(const vpHomogeneousMatrix &_cMo);
          
          /*!
            Set the threshold for the acceptation of a point.

            \param _th : Threshold for the weight below which a point is rejected.
          */
  inline  void            setThresholdAcceptation(const double _th) {threshold_outlier = _th;}
  
  virtual void            testTracking();
  virtual void            track(const vpImage<unsigned char>& _I);
  
protected:
          void            computeVVS(const unsigned int &nbInfos, vpColVector &w);
          
  virtual void            initFaceFromCorners(const std::vector<vpPoint>& _corners, const unsigned int _indexFace = -1);
  virtual void            initCylinder(const vpPoint& , const vpPoint , const double , const unsigned int ){};
  
          void            preTracking(const vpImage<unsigned char>& _I, unsigned int &nbInfos, unsigned int &nbFaceUsed);
          bool            postTracking(const vpImage<unsigned char>& _I, vpColVector &w);
};

#endif