/** \file TdkCoordTransformer.h
  * This file contains an implementation of a class to handle transformation between real world (window) coordinate system and device (viewport) coordinate system.
  */

#ifndef  __TDK_INTERNAL_COORDTRANSFORMER_H
#define  __TDK_INTERNAL_COORDTRANSFORMER_H

#include "TdkPrimitiveCoord.h"
#include "TeGeometry.h"
#include <tdk.h>

//! Defines the TdkCoordTransformer class.
/*!
@ingroup graphics
*/


/** \class TdkCoordTransformer
  * \brief This class implements a coordinate transformation service between Window (World) coordinate system and Device (Viewport) coordinate system.
  * 
  *
  * This class has methods that transform a coordinate from
  * window (world) system to a value in device coordinate system and
  * in the opposite way.
  *
  *
  * \sa TdkPrimitiveCoord, TeCoord2D, TeLine2D, TePolygon
  */
class TDK_API TdkCoordTransformer 
{
	public:

		/** @name This enum specifies the possible transformation types.
		  */
		enum TdkTransformationType
		{
			TdkDiscrete = 1,      /**< Discrete transformation. */
			TdkNotDiscrete = 2    /**< Not a discrete transformation . */
		};

		/** @name Constructor and Destructor Methods
		  * Methods related to instantiation and destruction.
		  */
		//@{		

		/** \brief Empty constructor
		  */
		TdkCoordTransformer(const TdkTransformationType& transformationType = TdkDiscrete);

		/** \brief Destructor.
		  */
		~TdkCoordTransformer() {}

		//@}

		/** @name Window (World) and Viewport (Device) Set Methods
		  * Methods used to set world and device coordinates area.
		  */
		//@{

		/** \brief Adjusts world (or window) coordinates area (supposing a cartesian reference system).
			\param llx Lower left abscissa. (Input)
			\param lly Lower left ordinate. (Input)
			\param urx Upper left abscissa. (Input)
			\param ury Upper left ordinate. (Input)
		  */
		void setWindow(const double& llx, const double& lly, const double& urx, const double& ury);
		
		/** \brief Adjusts world (window) coordinates area (supposing a cartesian reference system).
			\param box Bounding box of world. (Input)
		  */
		void setWindow(const TeBox& box);
		
		/** \brief Returns the world (window) coordinates area (supposing a cartesian reference system).
			\param llx Lower left abscissa. (Output)
			\param lly Lower left ordinate. (Output)
			\param urx Upper left abscissa. (Output)
			\param ury Upper left ordinate. (Output)
		  */
		void getWindow(double& llx, double& lly, double& urx, double& ury);
		
		/** \brief Adjusts device coordinates area (supposing a cartesian reference system).
			\param llx Lower left abscissa. (Input)
			\param lly Lower left ordinate. (Input)
			\param urx Upper left abscissa. (Input)
			\param ury Upper left ordinate. (Input)
		  */
		void setViewport(const double& llx, const double& lly, const double& urx, const double& ury);

		/** \brief Adjusts device coordinates area (supposing a cartesian reference system).
			\param box Device bounding box. (Input)
		  */
		void setViewport(const TeBox& box);
		
		/** \brief Returns the device coordinates area.
			\param llx Lower left abscissa. (Output)
			\param lly Lower left ordinate. (Output)
			\param urx Upper left abscissa. (Output)
			\param ury Upper left ordinate. (Output)
		  */
		void getViewport(double& llx, double& lly, double& urx, double& ury);

		/** \brief Transform world (or window) coordinates to device (or viewpoort) coordinates.
			\param wx World (or window) abscissa. (Input)
			\param wy World (or window) ordinate. (Input)
			\param vx Viewport (or device) abscissa. (Output)
			\param vy Viewport (or device) ordinate. (Output)
		  */
		void window2Viewport(const double& wx, const double& wy, double& vx, double& vy);

		/** \brief Transform world (or window) value to device (or viewpoort) value.
			\param wc World (or window) value. (Input)
			\param vc Viewport (or device) value. (Output)
		  */
		void window2Viewport(const TeCoord2D& wc, TeCoord2D& vc);

		/** \brief Transform world (or window) value to device (or viewpoort) value.
			\param wc World (or window) value. (Input)
			\param vc Viewport (or device) value. (Output)
		  */
		void window2Viewport(const TdkPrimitiveCoord& wc, TdkPrimitiveCoord& vc);

		/** \brief Transform world (or window) value to device (or viewpoort) value.
			\param wbox World (or window) value. (Input)
			\param vbox Viewport (or device) value. (Output)
		  */
		void window2Viewport(const TeBox& wbox, TeBox& vbox);

		/** \brief Transform world (or window) value to device (or viewpoort) value according to one axis.
			\param w World (or window) value. (Input)
			\param v Viewport (or device) value. (Output)
			\param xdirection If world and device don't keep aspect ratio you should specify what axis to consider.
		  */
		void window2Viewport(const double& w, double& v, const bool& xdirection = true);		

		/** \brief Transform line world (or window) coordinates to device (or viewport) coordinates.
			\param lineIn  A line with vertexes in world (or window) coordinates. (Input)
			\param lineOut A copy of the first line with vertexes in viewport (or device) coordinates. (Output)
		  */
		void window2Viewport(const TeLine2D& lineIn, TeLine2D& lineOut);

		/** \brief Transform polygon world (or window) coordinates to device (or viewport) coordinates.
			\param polyIn  A polygon with vertexes in world (or window) coordinates. (Input)
			\param polyOut A copy of the first polygon with vertexes in viewport (or device) coordinates. (Output)
		  */
		void window2Viewport(const TePolygon& polyIn, TePolygon& polyOut);

		/** \brief Transform the array of coordinates in world (or window) coordinates to device (or viewport) coordinates.
		    You should pass an output array pre-allocated with the same size as inputCoords array.
			\param inputCoords  A pointer to an array of coordinates in world (or window) coordinates. (Input)
			\param outputCoords A copy of the array with coordinates in viewport (or device) coordinates. (Output)
			\param numCoords    The number of coordinates of inputCoords array.
			\note You should pass an output array pre-allocated with the same size as inputCoords array.
		  */
		void window2Viewport(TdkPrimitiveCoord* inputCoords, TdkPrimitiveCoord* outputCoords, const int& numCoords);

		/** \brief Transform viewport (or device) coordinates to world (or window) coordinates.
			\param vx Viewport (or device) abscissa. (Input)
			\param vy Viewport (or device) ordinate. (Input)
			\param wx World (or window) abscissa. (Output)
			\param wy World (or window) ordinate. (Output)
		  */
		void viewport2Window(const double& vx, const double& vy, double& wx, double& wy);

		/** \brief Transform viewport (or device) coordinates to world (or window) coordinates.			
			\param vc Viewport (or device) value. (Input)
			\param wc World (or window) value. (Output)
		  */
		void viewport2Window(const TdkPrimitiveCoord& vc, TdkPrimitiveCoord& wc);

		/** \brief Transform device (or viewpoort) value to world (or window) value according to one axis.
			\param v Viewport (or device) value. (Input)
			\param w World (or window) value. (Output)			
			\param xdirection If world and device don't keep aspect ratio you should specify what axis to consider.
		  */
		void viewport2Window(const double& v, double& w, const bool& xdirection = true);

		/** \brief Transform line device (or viewport) coordinates to world (or window) coordinates.
			\param lineIn  A line with vertexes in viewport (or device) coordinates. (Input)
			\param lineOut A copy of the first line with vertexes in world (or window) coordinates. (Output)
		  */
		void viewport2Window(const TeLine2D& lineIn, TeLine2D& lineOut);

		/** \brief Transform polygon device (or viewport) coordinates to world (or window) coordinates.
			\param polyIn  A polygon with vertexes in device (or viewport) coordinates. (Input)
			\param polyOut A copy of the first polygon with vertexes in world (or window) coordinates. (Output)
		  */
		void viewport2Window(const TePolygon& polyIn, TePolygon& polyOut);

		/** \brief Transform the array of coordinates in device (or viewport) coordinates to world (or window) coordinates.
		    You should pass an output array pre-allocated with the same size as inputCoords array.
			\param inputCoords  A pointer to an array of coordinates in viewport (or device) coordinates. (Input)
			\param outputCoords A copy of the array with coordinates in world (or window) coordinates. (Output)
			\param numCoords    The number of coordinates of inputCoords array.
			\note You should pass an output array pre-allocated with the same size as inputCoords array.
		  */
		void viewport2Window(TdkPrimitiveCoord* inputCoords, TdkPrimitiveCoord* outputCoords, const int& numCoords);

		//@}

		/** @name Auxliary Methods
		  * These methods can be used to calculate aspect ratio between world coordinates area and
		  * device coordinates area.
		  */
		//@{

		/** \brief Gets transformation type.
		  */
		const TdkTransformationType& getTransformationType() const;

		/** \brief Sets transformation type.
		    If your canvas is discrete (e.g., countable number of lines an columns),
			like QtCanvas, you should set as discrete
			and if you are using a device not discrete (e.g. PDF document) you should
			set it as not discrete.
			\param transformationType Transformation type. (Input)
		  */
		void setTransformationType(const TdkTransformationType& transformationType);

		/** \brief Adjust the informed window (world) bounding box according to a device bounding box.
		    This may be helpfull when you want to keep the aspect ratio during a drawing of a theme (layer).
			The box will be expaded in the correct direction, and you can choose to centralize the
			draw informaing the last paramenter as true.
		    \param llxW  Window lower left abscissa. (Input and Output)
			\param llyW  Window lower left ordinate. (Input and Output)
			\param urxW  Window upper right abscissa. (Input and Output)
			\param uryW  Window upper right ordinate. (Input and Output)
			\param llxV  Viewport lower left abscissa. (Input)
			\param llyV  Viewport lower left ordinate. (Input)
			\param urxV  Viewport upper right abscissa. (Input)
			\param uryV  Viewport upper right ordinate. (Input)
			\param transformationType Transformation type. (Input)
			\param centralized Tells if the expanded bounding box will be in the middle.
		  */
		static void adjustWindowBox(double& llxW, double& llyW,
			                        double& urxW, double& uryW,
			                        const double& llxV, const double& llyV,
									const double& urxV, const double& uryV,
									const TdkTransformationType& transformationType,
									const bool& centralized = false);

		/** \brief Adjust the informed window (world) bounding box according to a device bounding box.
		    This may be helpfull when you want to keep the aspect ratio during a drawing of a theme (layer).
			The box will be expaded in the correct direction, and you can choose to centralize the
			draw informaing the last paramenter as true.
		*/
		static TeBox adjustWindowBox(const TeBox &boxW,const TeBox &boxV);
		
		//@}

	protected:

		/** @name Mapping Function Definition Methods
		  * Methods that can be used to calculate the factor
		  * used in mapping from device to world and world to device.
		  */
		//@{

		inline void updateTransformation();	

		//@}

        double sX_;		//!< Factor used in coordinate system transformation along "x" axis.
		double sY_;		//!< Factor used in coordinate system transformation along "y" axis.
        double s_;
        double tX_;
        double tY_;

// world coordinates
		double llxW_;	//!< Window (World) lower left abscissa.
		double llyW_;   //!< Window (World) lower left ordinate.
		double urxW_;   //!< Window (World) upper right abscissa.
		double uryW_;   //!< Window (World) upper right ordinate.

		double widthW_;		//!< Window (World) width.
		double heightW_;	//!< Window (World) height.

// device coordinates
		double llxV_;	//!< Viewport (Device) lower left abscissa.
		double llyV_;   //!< Viewport (Device) lower left abscissa.
		double urxV_;   //!< Viewport (Device) upper right abscissa.
		double uryV_;   //!< Viewport (Device) upper right abscissa.

		double widthV_;		//!< Viewport (Device) width.
		double heightV_;	//!< Viewport (Device) height.

		TdkTransformationType transformationType_;	//!< Indicates if it is a discrete transformation or not.
};

#endif	// __TDK_INTERNAL_COORDTRANSFORMER_H
