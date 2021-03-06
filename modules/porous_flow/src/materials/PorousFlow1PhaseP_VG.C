//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PorousFlow1PhaseP_VG.h"

template <>
InputParameters
validParams<PorousFlow1PhaseP_VG>()
{
  InputParameters params = validParams<PorousFlow1PhaseP>();
  params.addRequiredRangeCheckedParam<Real>(
      "al", "al > 0", "van Genuchten parameter alpha.  Must be positive");
  params.addRequiredRangeCheckedParam<Real>(
      "m",
      "m > 0 & m < 1",
      "van Genuchten exponent m.  Must be between 0 and 1, and optimally should be set to > 0.5");
  params.addClassDescription(
      "This Material is used for the single-phase situation where porepressure is the primary "
      "variable.  Calculates the 1 porepressure and the 1 saturation in a 1-phase isothermal "
      "situation, and derivatives of these with respect to the PorousFlowVariables.  A van "
      "Genuchten effective saturation (1 + (-al * p)^(1 / (1 - m)))^(-m) is assumed");
  return params;
}

PorousFlow1PhaseP_VG::PorousFlow1PhaseP_VG(const InputParameters & parameters)
  : PorousFlow1PhaseP(parameters),

    _al(getParam<Real>("al")),
    _m(getParam<Real>("m"))
{
  mooseDeprecated("PorousFlow1PhaseP_VG is deprecated. Please use PorousFlow1PhaseP and a "
                  "PorousFlowCapillaryPressureVG UserObject instead");
}

Real
PorousFlow1PhaseP_VG::effectiveSaturation(Real pressure) const
{
  return PorousFlowVanGenuchten::effectiveSaturation(pressure, _al, _m);
}

Real
PorousFlow1PhaseP_VG::dEffectiveSaturation_dP(Real pressure) const
{
  return PorousFlowVanGenuchten::dEffectiveSaturation(pressure, _al, _m);
}

Real
PorousFlow1PhaseP_VG::d2EffectiveSaturation_dP2(Real pressure) const
{
  return PorousFlowVanGenuchten::d2EffectiveSaturation(pressure, _al, _m);
}
