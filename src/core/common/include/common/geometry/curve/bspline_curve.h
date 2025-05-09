/**
 * *********************************************************
 *
 * @file: bspline_curve.h
 * @brief: B-Spline curve generation
 * @author: Yang Haodong
 * @date: 2023-12-20
 * @version: 1.0
 *
 * Copyright (c) 2024, Yang Haodong.
 * All rights reserved.
 *
 * --------------------------------------------------------
 *
 * ********************************************************
 */
#ifndef RMP_COMMON_GEOMETRY_BSPLINE_CURVE_H_
#define RMP_COMMON_GEOMETRY_BSPLINE_CURVE_H_

#include "common/geometry/curve/curve.h"

namespace rmp
{
namespace common
{
namespace geometry
{
class BSplineCurve : public Curve
{
public:
  /**
   * @brief Construct a new B-Spline generation object
   * @param step        Simulation or interpolation size (default: 0.01)
   * @param order       Degree of curve (default: 3)
   * @param param_mode  Parameterization mode (default: PARAM_MODE_CHORDLENGTH)
   * @param spline_mode B-Spline generation mode (default: SPLINE_MODE_INTERPOLATION)
   */
  BSplineCurve();
  BSplineCurve(double step, int order, int param_mode, int spline_mode);

  /**
   * @brief Destroy the B-Spline generation object
   */
  ~BSplineCurve();

  /**
   * @brief Running trajectory generation
   * @param points path points <x, y>
   * @param path generated trajectory
   * @return true if generate successfully, else failed
   */
  bool run(const Points2d& points, Points3d& path);

  /**
   * @brief Running trajectory generation
   * @param points path points <x, y, theta>
   * @param path generated trajectory
   * @return true if generate successfully, else failed
   */
  bool run(const Points3d& points, Points3d& path);

  /**
   * @brief Calculate base function using Cox-deBoor function.
   * @param i       The index of base function
   * @param k       The degree of curve
   * @param t       Parameter
   * @param knot    Knot vector
   * @return  Nik_t The value of base function Nik(t)
   */
  double baseFunction(int i, int k, double t, const std::vector<double>& knot);

  /**
   * @brief Calculate parameters using the `uniform spaced` or `chrod length` or `centripetal` method.
   * @param points      Path points
   * @return parameters The parameters of given points
   */
  std::vector<double> paramSelection(const Points2d& points);

  /**
   * @brief Generate knot vector.
   * @param parameters The parameters of given points
   * @param n          The number of data points
   * @return knot The knot vector
   */
  std::vector<double> knotGeneration(const std::vector<double>& param, int n);

  /**
   * @brief Given a set of N data points, D0, D1, ..., Dn and a degree k, find a B-spline curve of degree
   *      k defined by N control points that passes all data points in the given order.
   * @param points          Path points
   * @param parameters      The parameters of given points
   * @param knot            The knot vector
   * @return control_points The control points
   */
  Points2d interpolation(const Points2d& points, const std::vector<double>& param, const std::vector<double>& knot);

  /**
   * @brief Given a set of N data points, D0, D1, ..., Dn, a degree k, and a number H, where N > H > k >= 1,
   *    find a B-spline curve of degree k defined by H control points that satisfies the following conditions:
          1. this curve contains the first and last data points;
          2. this curve approximates the data polygon in the sense of least square
   * @param points          Path points
   * @param parameters      The parameters of given points
   * @param knot            The knot vector
   * @return control_points The control points
   */
  Points2d approximation(const Points2d& points, const std::vector<double>& param, const std::vector<double>& knot);

  /**
   * @brief Generate the path.
   * @param k               The degree of curve
   * @param knot            The knot vector
   * @param control_points  The control points
   * @return path The smoothed trajectory points
   */
  Points2d bsplineGeneration(int k, const std::vector<double>& knot, Points2d control_pts);

  /**
   * @brief Generate the path.
   * @param start Initial pose (x, y, yaw)
   * @param goal  Target pose (x, y, yaw)
   * @param path  The smoothed trajectory points
   * @return true if generate successfully, else failed
   */
  bool generation(const Point3d& start, const Point3d& goal, Points3d& path);

  /**
   * @brief Configure the degree of the curve.
   * @param order  The degree of curve
   */
  void setSplineOrder(int order);

  /**
   * @brief Configure the parameterization mode.
   * @param param_mode  The parameterization mode
   */
  void setParamMode(int param_mode);

  /**
   * @brief Configure the B-Spline generation mode.
   * @param spline_mode  The B-Spline generation mode
   */
  void setSPlineMode(int spline_mode);

public:
  enum PARAM_MODE
  {
    UNIFORMSPACED = 0,
    CENTRIPETAL = 1,
    CHORDLENGTH = 2,
  };

  enum SPLINE_MODE
  {
    INTERPOLATION = 0,
    APPROXIMATION = 1,
  };

protected:
  int order_;        // Degree of curve
  int param_mode_;   // Parameterization mode
  int spline_mode_;  // B-Spline generation mode
  double start_angle_{ 0.0 }, goal_angle_{ 0.0 };
};
}  // namespace geometry
}  // namespace common
}  // namespace rmp
#endif