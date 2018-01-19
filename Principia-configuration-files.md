# Principia configuration files

## Definitions of scalar types

`string` is any text that can be stored in a value of a KSP configuration node and retrieved by `GetValue`. 

`fixed_step_size_integrator` is the name of a [fixed step size integrator](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/integrators/integrators.hpp#L73-L132) supported by Principia.
[Note that this is case-sensitive.]

See also the comments on the declarations of the [symplectic partitioned Runge-Kutta integrators](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/integrators/symplectic_partitioned_runge_kutta_integrator.hpp#L108-L344), [symplectic Runge-Kutta-Nyström integrators](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/integrators/symplectic_runge_kutta_nystr%C3%B6m_integrator.hpp#L141-L222), and [symmetric linear multistep integrators](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/integrators/symmetric_linear_multistep_integrator.hpp#L134-L168) and the references cited therein for more on these integrators.
```
fixed_step_size_integrator ⩴ BLANES_MOAN_2002_SRKN_6B
                           | BLANES_MOAN_2002_SRKN_11B
                           | BLANES_MOAN_2002_SRKN_14A
                           | MCLACHLAN_1995_SB3A_4
                           | MCLACHLAN_1995_SB3A_5
                           | MCLACHLAN_ATELA_1992_ORDER_4_OPTIMAL
                           | MCLACHLAN_ATELA_1992_ORDER_5_OPTIMAL
                           | OKUNBOR_SKEEL_1994_ORDER_6_METHOD_13
                           | QUINLAN_1999_ORDER_8A
                           | QUINLAN_1999_ORDER_8B
                           | QUINLAN_TREMAINE_1990_ORDER_8
                           | QUINLAN_TREMAINE_1990_ORDER_10
                           | QUINLAN_TREMAINE_1990_ORDER_12
                           | QUINLAN_TREMAINE_1990_ORDER_14
```


`floating_point_number` is a floating point number as accepted by
[`std::strtod`](http://en.cppreference.com/w/cpp/string/byte/strtod).

`signed_integer` is a signed integer as accepted by [`std::strtol`](http://en.cppreference.com/w/cpp/string/byte/strtol) in base 10.

`unit` is one of the following units, as defined
[in quantities/parser_body.hpp](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/quantities/parser_body.hpp#L100-L143):
```
length_unit      ⩴ μm | mm | cm | m | km | au
time_unit        ⩴ ms | s | min | h | d
power_unit       ⩴ W
angle_unit       ⩴ deg | ° | rad
solid_angle_unit ⩴ sr

unit             ⩴ length_unit | time_unit | power_unit | angle_unit | solid_angle_unit
```

`quantity` is defined by the following grammar from
[quantities/parser.hpp](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/quantities/parser.hpp#L12-L18):
```
quantity            ⩴ floating_point_number quotient_unit
quotient_unit       ⩴ quotient_unit / exponentiation_unit
                    | product_unit
product_unit        ⩴ exponentiation_unit [product_unit]
exponentiation_unit ⩴ unit [^ exponent]
exponent            ⩴ signed_integer
```

We will use `quantity(length)`, `quantity(length / time^2)`, etc. to refer to quantities that are required
to have the dimensions given in parentheses.

> *Example*: `-1.5e+09 km/s` is a `quantity(length / time)`.

`instant` is a date either given as a Julian Date or a Modified Julian Date (where the decimal mark must be a full stop "."), or as an ISO 8601 complete representation of date and time, where Principia requires that the comma "," be used as a decimal sign if a decimal fraction of seconds is used.
It is interpreted as [TT (*Temps Terrestre*, terrestrial time)](https://www.iers.org/IERS/EN/Science/Recommendations/recommendation4.html).

> *Example*: `JD2451545.0`, `MJD51544.5`, `2000-01-01T12:00:00`, `1999-W52-6T12:00:00,000`, `2000001T120000` all represent the standard epoch [J2000](https://en.wikipedia.org/wiki/J2000).

## The top-level configurations

Principia supports three top-level configuration nodes.
There may be at most one of each node [for instance, having two `principia_gravity_model` nodes will result in a crash].
These are `principia_gravity_model` which defines the physical properties of the celestial bodies,
`principia_initial_state` which defines their initial positions and velocities,
and `principia_numerics_blueprint` which defines the numerical methods used to compute the evolution of the system.

If `principia_initial_state` is provided, it must define the initial positions and velocities for all celestial bodies,
and `principia_gravity_model` must be *sufficient* for all celestial bodies.

If `principia_initial_state` is *not* provided, the initial state is obtained by interpreting KSP's orbital elements
as [osculating elements](https://en.wikipedia.org/wiki/Osculating_orbit#Kepler_elements) for [Jacobi coordinates](https://en.wikipedia.org/wiki/Jacobi_coordinates).
In that case, `principia_gravity_model` need not cover all celestial bodies. It must be *nominal* for the bodies it covers.

### The `principia_gravity_model` configuration
The `principia_gravity_model` configuration consists of a sequence of `body` configuration nodes.

A *nominal* `body` configuration node contains the following values.
- `name`: a required `string`.

  This is the [`name`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L7) of the celestial body whose gravity model is being defined.
- `gravitational_parameter`: an optional `quantity(length^3 / time^2)`.

  The gravitational parameter *μ*. Corresponds to the stock [`gravParameter`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L14).
- `reference_instant`: an optional `instant`.

  This is the instant *t*<sub>0</sub> at which the rotation *W* of the body is *W*<sub>0</sub>.
  
  Defaults to JD2451545.0 (2000-01-01T12:00:00).
- `mean_radius`: an optional `quantity(length)`.

  Vessels going below this radius will be destroyed by Principia, even at high time warp.
  
  Defaults to the stock [`radius`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L11). 
- `axis_right_ascension`: an optional `quantity(angle)`. 

  The angle *α*<sub>0</sub>.
  
  Defaults to -90°.
- `axis_declination`: an optional `quantity(angle)`. 

  The angle *δ*<sub>0</sub>.
  
  Defaults to 90°.
- `reference_angle`: an optional `quantity(angle)`.

  The angle *W*<sub>0</sub>.

  Defaults to the stock [`initialRotation`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L18).
- `angular_frequency`: an optional `quantity(angle / time)`.

  The time derivative *Ẇ* of the angle *W*.

  Defaults to the stock [`angularV`](https://kerbalspaceprogram.com/api/class_celestial_body.html#a30efc17a6ccf98a1e25a3239f08ab83a), which is indirectly configurable in Kopernicus, as it is |2π rad / [`rotationPeriod`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L16)|.

  TODO(eggrobin): we don't handle retrograde rotation correctly when configured with Kopernicus (with a negative period), since `angularV` is an absolute value...
- `j2`: an optional `floating_point_number`.

  The dimensionless zonal harmonic *J*<sub>2</sub>.
  
  Defaults to 0.
- `reference_radius`: an optional `quantity(length)`.

  The reference radius *a*<sub>*e*</sub> used to make the spherical harmonics dimensionless.
  
  Defaults to the stock [`radius`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L11).

A *sufficient* `body` configuration node is a *nominal* `body` configuration node where:
- `gravitational_parameter`, `reference_instant`, `mean_radius`, `axis_right_ascension`, `axis_declination`, `reference_angle`, and `angular_frequency` are present;
- `j2` and `reference_radius` are either both present or both absent.

> *Example*: All `body` nodes in [sol_gravity_model.cfg](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/astronomy/sol_gravity_model.cfg),
provided with Principia, are *sufficient*.

#### Semantics of the quantities used for body rotation
The quantities *W* = *W*<sub>0</sub> + *Ẇ* (*t* - *t*<sub>0</sub>), *α*<sub>0</sub>, and *δ*<sub>0</sub> are Euler angles defining the orientation of the celestial body, as shown on figure 1 of [the 2009 report of the IAU Working Group on Cartographic Coordinates and Rotational Elements](https://astropedia.astrogeology.usgs.gov/download/Data/WGCCRE/WGCCRE2009reprint.pdf), where *t* is terrestrial time.

#### Semantics of the quantities used for extended-body gravitation
The gravitational potential used is the one given in equation 6.1 of [IERS technical note 36 (IERS conventions 2010)](https://www.iers.org/SharedDocs/Publikationen/EN/IERS/Publications/tn/TechnNote36/tn36_079.pdf?__blob=publicationFile&v=1), where:

*μ* = *GM* and *J*<sub>2</sub> = -*C̄*<sub>20</sub> √5.

> *Note*: A dynamically oblate body has a positive *J*<sub>2</sub>. The values for the planets of the solar system can be found, with references, in [sol_gravity_model.proto.txt](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/astronomy/sol_gravity_model.proto.txt).

### The `principia_initial_state` configuration
The `principia_initial_state` configuration consists of:
- a `game_epoch` value;
- a `solar_system_epoch` value;
- a sequence of `body` configuration nodes.

The `game_epoch` is a required `instant`, which is the instant at which the game starts.
The `solar_system_epoch` is a required `instant`, which is the instant at which the initial state is given.

It is required that `solar_system_epoch`≤`game_epoch`.

The `body` nodes must contain the following values:
- `name`: a required `string`. This is the [`name`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L7) of the celestial body whose initial state is being defined.
- `x`: a required `quantity(length)`. The *x* coordinate of the position.
- `y`: a required `quantity(length)`. The *y* coordinate of the position.
- `z`: a required `quantity(length)`. The *z* coordinate of the position.
- `vx`: a required `quantity(length / time)`. The *x* coordinate of the velocity.
- `vy`: a required `quantity(length / time)`. The *y* coordinate of the velocity.
- `vz`: a required `quantity(length / time)`. The *z* coordinate of the velocity.

> *Example*: The [sol_initial_state_jd_2433282_500000000.cfg](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/astronomy/sol_initial_state_jd_2433282_500000000.cfg) configuration file, provided with Principia, is a valid `principia_initial_state` node.

### The `principia_numerics_blueprint` configuration

The `principia_numerics_blueprint` configuration consists of:
- an optional `ephemeris` node;
- an optional `history` node;
- an optional `psychohistory` node.

The `ephemeris` node contains the following values:
- `fixed_step_size_integrator`, a required `fixed_step_size_integrator`;
- `integration_step_size`, a required `quantity(time)`.

The integration of the motion of the celestial bodies is performed by the ephemeris with the
given `fixed_step_size_integrator` at the given `integration_step_size`.

> *Example*: The following `principia_numerics_blueprint` node describes the default integration
method used by Principia.
> ```ini
>principia_numerics_blueprint {
>  ephemeris {
>    fixed_step_size_integrator = QUINLAN_TREMAINE_1990_ORDER_12
>    integration_step_size      = 10 min
>  }
>}
>```

**☡ The `history` and `psychohistory` nodes are reserved for internal use.
Modders should not define these nodes.**

The `history` node contains the following values:
- `fixed_step_size_integrator`, a required `fixed_step_size_integrator`;
- `integration_step_size`, a required `quantity(time)`.

The `psychohistory` node contains the following values:
- `adaptive_step_size_integrator`, a required `adaptive_step_size_integrator`;
- `length_integration_tolerance`, a required `quantity(length)`;
- `speed_integration_tolerance`, a required `quantity(length / time)`.

## Annex: choosing a fixed step size integrator
The symmetric linear multistep integrators tend to be faster when they have converged to small errors,
but they can fail catastrophically if they are not yet converged.

The single-step methods (symplectic partitioned Runge-Kutta, symplectic Runge-Kutta-Nyström) produce physically
credible behaviour even when they have errors resulting from an overly large time step.

Solar system designers should test the actual stability of their system with a symplectic Runge-Kutta-Nyström
and a small time step, and then try increasing the step size and switching to a linear multistep integrator
to reduce computational cost for their users.

## Annex: a note on ModuleManager
The constraint that there may be at most one of each top-level configuration applies *after* ModuleManager has run.

In the absence of other mods, none of the configurations are present.
With RealSolarSystem, the `principia_gravity_model` and `principia_initial_state` nodes are both present, since they
use a `:NEEDS[RealSolarSystem]` clause.

Modders should make careful use the `@` operator (modify an existing node), `%` operator (modify or create),
`:NEEDS` clause (condition on the presence of a mod) to ensure the requirement is met.

> *Example*: a modder creating a mod AdditionalRealBodies which adds bodies to RealSolarSystem should append
their initial states to `principia_initial_state` and their *sufficient* gravity models to
`principia_gravity_model` with
`@principia_initial_state:FOR[AdditionalRealBodies]:NEEDS[RealSolarSystem]:FINAL` and
`@principia_gravity_model:FOR[AdditionalRealBodies]:NEEDS[RealSolarSystem]:FINAL`.

> TODO(egg): the `:FINAL` requirement is a defect. Principia should use the operator `%` and have a `FOR` clause
so that modders can use the `%` operator if they do not collide, and an `AFTER` clause if they do.

> A modder creating a new solar system mod NeuesSonnensystem should create *nominal* gravity models using
`%principia_gravity_model:FOR[NeuesSonnensystem]`.  Alternatively, they can create *sufficient* gravity models
in that node and provide an initial state with `%principia_initial_state:FOR[NeuesSonnensystem]`

Modders should refer to the [ModuleManager thread](https://forum.kerbalspaceprogram.com/index.php?/topic/50533--)
for documentation. 