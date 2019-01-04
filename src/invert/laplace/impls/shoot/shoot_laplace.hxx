/**************************************************************************
 * Perpendicular Laplacian inversion in serial or parallel
 * 
 * Uses shooting method from outer boundary
 *
 **************************************************************************
 * Copyright 2014 B.D.Dudson
 *
 * Contact: Ben Dudson, bd512@york.ac.uk
 * 
 * This file is part of BOUT++.
 *
 * BOUT++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BOUT++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with BOUT++.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/

#ifndef __LAP_SHOOT_H__
#define __LAP_SHOOT_H__

#include "boutexception.hxx"
#include "invert_laplace.hxx"

#include <map>
#include <vector>

#include "bout/array.hxx"
#include "bout/assert.hxx"
#include "bout_types.hxx"
#include "dcomplex.hxx"
#include "field2d.hxx"
#include "fieldperp.hxx"
#include "globals.hxx"
#include "unused.hxx"

class Mesh;
class Options;

class LaplaceShoot : public Laplacian {
public:
  LaplaceShoot(Options *opt = nullptr, const CELL_LOC = CELL_CENTRE, Mesh *mesh_in = mesh);
  ~LaplaceShoot(){};
  
  using Laplacian::setCoefA;
  void setCoefA(const Field2D &val) override {
    ASSERT1(val.getLocation() == location);
    ASSERT1(localmesh = val.getMesh());
    Acoef = val;
  }
  using Laplacian::setCoefC;
  void setCoefC(const Field2D &val) override {
    ASSERT1(val.getLocation() == location);
    ASSERT1(localmesh = val.getMesh());
    Ccoef = val;
  }
  using Laplacian::setCoefD;
  void setCoefD(const Field2D &val) override {
    ASSERT1(val.getLocation() == location);
    ASSERT1(localmesh = val.getMesh());
    Dcoef = val;
  }
  using Laplacian::setCoefEx;
  void setCoefEx(const Field2D &UNUSED(val)) override {
    throw BoutException("LaplaceShoot does not have Ex coefficient");
  }
  using Laplacian::setCoefEz;
  void setCoefEz(const Field2D &UNUSED(val)) override {
    throw BoutException("LaplaceShoot does not have Ez coefficient");
  }

  using Laplacian::solve;
  const FieldPerp solve(const FieldPerp &b) override;
  const FieldPerp solve(const FieldPerp &b, const FieldPerp &UNUSED(x0)) override {return solve(b);}
private:
  Field2D Acoef, Ccoef, Dcoef;
  
  int nmode;  // Number of modes being solved
  
  Array<dcomplex> km, kc, kp, rhsk;
  
  Array<BoutReal> buffer; // For communications
};

#endif
