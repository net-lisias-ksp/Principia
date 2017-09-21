﻿
#pragma once

#include "quantities/quantities.hpp"

namespace principia {
namespace quantities {

// The result type of +, -, * and / on arguments of types |Left| and |Right|.
template<typename Left, typename Right>
using Sum = decltype(std::declval<Left>() + std::declval<Right>());
template<typename Left, typename Right = Left>
using Difference = decltype(std::declval<Left>() - std::declval<Right>());
template<typename Left, typename Right>
using Product = decltype(std::declval<Left>() * std::declval<Right>());
template<typename Left, typename Right>
using Quotient = decltype(std::declval<Left>() / std::declval<Right>());

// The result type of the derivative of a |Value|-valued function with respect
// to its |Argument|-valued argument.
template<typename Value, typename Argument>
using Derivative = Quotient<Difference<Value>, Difference<Argument>>;

// |Variation<T>| is the type of the time derivative of a |T|-valued function.
template<typename T>
using Variation = Derivative<T, Time>;

// The solid angle is really the square of the angle: for instance, the surface
// element on the sphere is cos(θ) dθ dφ, and the cylinder with radius r and
// height 2r, whose surface is equal to that of the sphere, has a surface of
// 2r × 2πr: the steradian is the square of the radian.
using SolidAngle   = Square<Angle>;

// General mechanics
using Speed        = Variation<Length>;
using Acceleration = Variation<Speed>;
using Momentum     = Product<Mass, Speed>;
using Force        = Variation<Momentum>;
using Stiffness    = Quotient<Force, Length>;

using Energy = Product<Force, Length>;
using Power  = Variation<Energy>;
using Action = Product<Energy, Time>;

using MomentOfInertia     = Product<Square<Quotient<Length, Angle>>, Mass>;
using AngularFrequency    = Variation<Angle>;
using AngularAcceleration = Variation<AngularFrequency>;
using AngularMomentum     = Product<MomentOfInertia, AngularFrequency>;
using Torque              = Variation<AngularMomentum>;

using GravitationalParameter = Quotient<Exponentiation<Length, 3>,
                                        Exponentiation<Time, 2>>;
using Order2ZonalCoefficient = Quotient<Exponentiation<Length, 5>,
                                        Exponentiation<Time, 2>>;

// Astrodynamics
using SpecificImpulse         = Quotient<Momentum, Mass>;
using SpecificEnergy          = Quotient<Energy, Mass>;
using SpecificAngularMomentum = Quotient<AngularMomentum, Mass>;

// Thermodynamics
using Area           = Square<Length>;
using Volume         = Cube<Length>;
using Pressure       = Quotient<Force, Area>;
using Entropy        = Quotient<Energy, Temperature>;
using Density        = Quotient<Mass, Volume>;
using SpecificVolume = Quotient<Volume, Mass>;
using MolarVolume    = Quotient<Volume, Amount>;

// Fluid dynamics
using DynamicViscosity   = Product<Pressure, Time>;
using KinematicViscosity = Quotient<Area, Time>;

// Chemistry
using Concentration     = Quotient<Amount, Volume>;
using MolarMass         = Quotient<Mass, Amount>;
using CatalyticActivity = Quotient<Amount, Time>;

// Optics
using Wavenumber = Quotient<Angle, Length>;

// Spectroscopy
using Frequency               = Time::Inverse;
using SpectroscopicWavenumber = Length::Inverse;

// Electromagnetism
using Charge              = Product<Current, Time>;
using Voltage             = Quotient<Energy, Charge>;
using Capacitance         = Quotient<Charge, Voltage>;
using Resistance          = Quotient<Voltage, Current>;
using Conductance         = Quotient<Current, Voltage>;
using MagneticFlux        = Quotient<Energy, Current>;
using MagneticFluxDensity = Quotient<MagneticFlux, Area>;
using Inductance          = Quotient<MagneticFlux, Current>;
using ElectricField       = Quotient<Force, Charge>;

using Permeability = Product<Quotient<Inductance, Length>, SolidAngle>;
using Permittivity = Quotient<Quotient<Capacitance, Length>, SolidAngle>;

using ElectricDisplacementField = Product<ElectricField, Permittivity>;
using MagneticField             = Quotient<MagneticFluxDensity, Permeability>;

// Radiometry
using RadiantIntensity = Quotient<Power, SolidAngle>;
using Radiance         = Quotient<RadiantIntensity, Area>;
using RadiantFlux      = Power;
using RadiantEnergy    = Product<RadiantFlux, Time>;
using Irradiance       = Quotient<RadiantFlux, Area>;
using RadiantExposure  = Product<Irradiance, Time>;

// Photometry
using Luminance        = Quotient<LuminousIntensity, Area>;
using LuminousFlux     = Product<LuminousIntensity, SolidAngle>;
using LuminousEnergy   = Product<LuminousFlux, Time>;
using Illuminance      = Quotient<LuminousFlux, Area>;
using LuminousExposure = Product<Illuminance, Time>;
using LuminousEfficacy = Quotient<LuminousFlux, RadiantFlux>;

}  // namespace quantities
}  // namespace principia