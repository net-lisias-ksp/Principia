# Principia configuration files

## Definitions of scalar types

<a id=string></a>[`string`](#string) is any text that can be stored in a value of a KSP configuration node and retrieved by `GetValue`. 

<a id=fixed_step_size_integrator></a>[`fixed_step_size_integrator`](#fixed_step_size_integrator) is the name of a [fixed step size integrator](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/integrators/integrators.hpp#L73-L132) supported by Principia.
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


<a id=floating_point_number></a>[`floating_point_number`](#floating_point_number) is a floating point number as accepted by
[`std::strtod`](http://en.cppreference.com/w/cpp/string/byte/strtod).

<a id=signed_integer></a>[`signed_integer`](#signed_integer) is a signed integer as accepted by [`std::strtol`](http://en.cppreference.com/w/cpp/string/byte/strtol) in base 10.

<a id=unit></a>[`unit`](#unit) is one of the following units, as defined
[in quantities/parser_body.hpp](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/quantities/parser_body.hpp#L100-L143):
```
length_unit      ⩴ μm | mm | cm | m | km | au
time_unit        ⩴ ms | s | min | h | d
power_unit       ⩴ W
angle_unit       ⩴ deg | ° | rad
solid_angle_unit ⩴ sr

unit             ⩴ length_unit | time_unit | power_unit | angle_unit | solid_angle_unit
```

<a id=quantity></a>[`quantity`](#quantity) is defined by the following grammar from
[quantities/parser.hpp](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/quantities/parser.hpp#L12-L18):
<pre>
quantity            ⩴ <a href=#floating_point_number>floating_point_number</a> quotient_unit
quotient_unit       ⩴ quotient_unit / exponentiation_unit
                    | / exponentiation_unit
                    | product_unit
product_unit        ⩴ exponentiation_unit [product_unit]
exponentiation_unit ⩴ <a href=#unit>unit</a> [^ exponent]
exponent            ⩴ <a href=#signed_integer>signed_integer</a>
</pre>

We will use `quantity(length)`, `quantity(length / time^2)`, etc. to refer to quantities that are required
to have the dimensions given in parentheses.

> *Example*: `-1.5e+09 km/s` is a `quantity(length / time)`.

<a id=instant></a>[`instant`](#instant) is a date either given as a Julian Date or a Modified Julian Date (where the decimal mark must be a full stop "."), or as an ISO 8601 complete representation of date and time, where Principia requires that the comma "," be used as a decimal sign if a decimal fraction of seconds is used.
It is interpreted as [TT (*Temps Terrestre*, terrestrial time)](https://www.iers.org/IERS/EN/Science/Recommendations/recommendation4.html).

> *Example*: `JD2451545.0`, `MJD51544.5`, `2000-01-01T12:00:00`, `1999-W52-6T12:00:00,000`, `2000001T120000` all represent the standard epoch [J2000](https://en.wikipedia.org/wiki/J2000).

<a id=colour></a>[`colour`](#colour) is an HTML style colour code in RGB order.

> *Example*: `#aaff32`

<a id=style></a>[`style`](#style) is one of the following styles, as defined
[in ksp_plugin_adapter/gl_lines.cs](https://github.com/mockingbirdnest/Principia/blob/3e38c957ce70d276c7a2d0944d69e3b01ef82236/ksp_plugin_adapter/gl_lines.cs#L7-10):
```
style            ⩴ solid | dashed | faded
```

## The top-level configurations

Principia supports four top-level configuration nodes.
There may be at most one of each node [for instance, having two `principia_gravity_model` nodes will result in a crash].
These are `principia_gravity_model` which defines the physical properties of the celestial bodies,
`principia_initial_state` which defines their initial positions and velocities,
`principia_numerics_blueprint` which defines the numerical methods used to compute the evolution of the system,
and `principia_draw_styles` which defines drawing styles for trajectories.

If `principia_initial_state` is provided, it must define the initial positions and velocities for all celestial bodies,
and `principia_gravity_model` must be [*sufficient*](#principia_gravity_model.body:sufficient) for all celestial bodies.

If `principia_initial_state` is *not* provided, the initial state is obtained by interpreting KSP's orbital elements
as [osculating elements](https://en.wikipedia.org/wiki/Osculating_orbit#Kepler_elements) for [Jacobi coordinates](https://en.wikipedia.org/wiki/Jacobi_coordinates).
In that case, `principia_gravity_model` need not cover all celestial bodies. It must be [*nominal*](#principia_gravity_model.body:nominal) for the bodies it covers.

### The `principia_gravity_model` configuration
The `principia_gravity_model` configuration consists of a sequence of [`body`](#principia_gravity_model.body) configuration nodes.

<a id=principia_gravity_model.body></a>A [`body`](#principia_gravity_model.body) configuration node contains the following values:
- <a id=principia_gravity_model.body.name></a>[`name`](#principia_gravity_model.body.name): a required [`string`](#string).

  This is the [`name`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L7) of the celestial body whose gravity model is being defined.
- <a id=principia_gravity_model.body.gravitational_parameter></a>[`gravitational_parameter`](#principia_gravity_model.body.gravitational_parameter): an optional [`quantity(length^3 / time^2)`](#quantity).

  The gravitational parameter *μ*. Corresponds to the stock [`gravParameter`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L14).
- <a id=principia_gravity_model.body.reference_instant></a>[`reference_instant`](#principia_gravity_model.body.reference_instant): an optional [`instant`](#instant).

  This is the instant *t*<sub>0</sub> at which the rotation *W* of the body is *W*<sub>0</sub>.
  
  Defaults to JD2451545.0 (2000-01-01T12:00:00).
- <a id=principia_gravity_model.body.axis_right_ascension></a>[`axis_right_ascension`](#principia_gravity_model.body.axis_right_ascension): an optional [`quantity(angle)`](#quantity). 

  The angle *α*<sub>0</sub>.
  
  Defaults to -90°.
- <a id=principia_gravity_model.body.axis_declination></a>[`axis_declination`](#principia_gravity_model.body.axis_declination): an optional [`quantity(angle)`](#quantity). 

  The angle *δ*<sub>0</sub>.
  
  Defaults to 90°.
- <a id=principia_gravity_model.body.reference_angle></a>[`reference_angle`](#principia_gravity_model.body.reference_angle): an optional [`quantity(angle)`](#quantity).

  The angle *W*<sub>0</sub>.

  Defaults to the stock [`initialRotation`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L18).
- <a id=principia_gravity_model.body.angular_frequency></a>[`angular_frequency`](#principia_gravity_model.body.angular_frequency): an optional [`quantity(angle / time)`](#quantity).

  The time derivative *Ẇ* of the angle *W*.

  Defaults to the stock [`angularV`](https://kerbalspaceprogram.com/api/class_celestial_body.html#a30efc17a6ccf98a1e25a3239f08ab83a), which is indirectly configurable in Kopernicus, as it is |2π rad / [`rotationPeriod`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L16)|.

  TODO(eggrobin): we don't handle retrograde rotation correctly when configured with Kopernicus (with a negative period), since `angularV` is an absolute value...
- <a id=principia_gravity_model.body.reference_radius></a>[`reference_radius`](#principia_gravity_model.body.reference_radius): an optional [`quantity(length)`](#quantity).

  The reference radius *a*<sub>*e*</sub> used to make the spherical harmonics dimensionless.
  
  Defaults to the stock [`radius`](https://github.com/Kopernicus/kittopia-dumps/blob/e09154a/Configs/Bop.cfg#L11).

- <a id=principia_gravity_model.body.j2></a>[`j2`](#principia_gravity_model.body.j2): an optional [`floating_point_number`](#floating_point_number).

  The unnormalized zonal harmonic *J*<sub>2</sub>.
  
  Defaults to 0.
- <a id=principia_gravity_model.body.geopotential_row></a>[`geopotential_row`](#principia_gravity_model.body.geopotential_row): an optional sequence of `geopotential_row` configuration nodes describing the spherical harmonics of the geopotential of the body.  A `geopotential_row` contains the following values:

    - <a id=principia_gravity_model.body.geopotential_row.degree></a>[`degree`](#principia_gravity_model.body.geopotential_row.degree): a required [`signed_integer`](#signed_integer).

      The degree of the geopotential row.

    - <a id=principia_gravity_model.body.geopotential_row.geopotential_column></a>[`geopotential_column`](#principia_gravity_model.body.geopotential_row.geopotential_column): an optional sequence of `geopotential_column` configuration nodes describing the spherical harmonics for the given degree.  A `geopotential_column` contains the following values:

      - <a id=principia_gravity_model.body.geopotential_row.geopotential_column.order></a>[`order`](#principia_gravity_model.body.geopotential_row.geopotential_column.order): a required [`signed_integer`](#signed_integer).

        The order of the geopotential column.

      - <a id=principia_gravity_model.body.geopotential_row.geopotential_column.j></a>[`j`](#principia_gravity_model.body.geopotential_row.geopotential_column.j): an optional [`floating_point_number`](#floating_point_number).

        The unnormalized coefficient of the zonal spherical harmonic of the given degree.  For degree *n*, this is traditionally known as *J*<sub>*n*</sub>.

      - <a id=principia_gravity_model.body.geopotential_row.geopotential_column.cos></a>[`cos`](#principia_gravity_model.body.geopotential_row.geopotential_column.cos): an optional [`floating_point_number`](#floating_point_number).

        The normalized coefficient of the cosine spherical harmonic of the given degree and order.  For degree *n* and order *m* this is traditionally known as *C*<sub>*nm*</sub>.

      - <a id=principia_gravity_model.body.geopotential_row.geopotential_column.sin></a>[`sin`](#principia_gravity_model.body.geopotential_row.geopotential_column.sin): a required [`floating_point_number`](#floating_point_number).

        The normalized coefficient of the sine spherical harmonic of the given degree and order.  For degree *n* and order *m* this is traditionally known as *S*<sub>*nm*</sub>.

<a id=principia_gravity_model.body:nominal></a>A `body` configuration node is [*nominal*](#principia_gravity_model.body:nominal) if:
- `j2` and `geopotential_row`s are not present at the same time;
- either `reference_radius` is absent, or one of `j2` and `geopotential_row` is present;
- no two `geopotential_row`s share the same `degree`;
- within each `geopotential_row`, no two `geopotential_columns` share the same `order`;
- each `geopotential_column` contains exactly one of `cos` and `j`;
- each `geopotential_column` whose `degree` is not 0 contains a `cos`.

<a id=principia_gravity_model.body:sufficient></a>A [*sufficient*](#principia_gravity_model.body:sufficient) `body` configuration node is a [*nominal*](#principia_gravity_model.body:nominal) `body` configuration node where:
- `gravitational_parameter`, `reference_instant`, `axis_right_ascension`, `axis_declination`, `reference_angle`, and `angular_frequency` are present;
- `reference_radius` is present if and only if `j2` or `geopotential_row`s are present.

> *Example*: All `body` nodes in [sol_gravity_model.cfg](https://github.com/mockingbirdnest/Principia/blob/2018011702-Clifford/astronomy/sol_gravity_model.cfg),
provided with Principia, are *sufficient*.  The Sun has a `j2`.  The giant planets have `geopotential_row`s that use `j`.  The Earth, the Moon, Mars, and some other planets have `geopotential_row`s that use `cos`.

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
- `fitting_tolerance`, a required `quantity(length)`.
- `geopotential_tolerance`, a required `floating_point_number`.

The integration of the motion of the celestial bodies is performed by the ephemeris with the
given `fixed_step_size_integrator` at the given `integration_step_size`.  The result of the integration is approximated by a polynomial with a maximum error given by `fitting_tolerance`.  Any geopotential effects are ignored if their relative magnitude with respect to the central force is less than `geopotential_tolerance`.

> *Example*: The following `principia_numerics_blueprint` node describes the default numerics blueprint used by Principia.
> ```ini
>principia_numerics_blueprint {
>  ephemeris {
>    fixed_step_size_integrator = QUINLAN_TREMAINE_1990_ORDER_12
>    integration_step_size      = 10 min
>    fitting_tolerance = 1 mm
>    geopotential_tolerance = 0x1.0p-24
>  }
>}
>```

### The `principia_draw_styles` configuration
The `principia_draw_styles` configuration consists of:
- an optional `history` node;
- an optional `prediction` node;
- an optional `flight_plan` node;
- an optional `burn` node;
- an optional `target_history` node;
- an optional `target_prediction` node.

Each of these nodes contain the same set of values:
- `colour`, a required `colour`;
- `style`, a required `style`.

> *Example*: The following `principia_draw_styles` node describes the default draw styles used by Principia.
> ```ini
>principia_draw_styles {
>  history {
>    colour = #aaff32    // Lime
>    style = faded
>  }
>  prediction {
>    colour = #ed0dd9    // Fuchsia
>    style = solid
>  }
>  flight_plan {
>    colour = #8f99fb    // Periwinkle Blue
>    style = solid
>  }
>  burn {
>    colour = #ff81c0    // Pink
>    style = solid
>  }
>  target_history {
>    colour = #fac205    // Goldenrod
>    style = faded
>  }
>  target_prediction {
>    colour = #c292a1    // LightMauve
>    style = solid
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

Solar system designers should test the actual stability of their system with a symplectic Runge-Kutta-Nyström method
and a small time step, and then try increasing the step size and switching to a linear multistep integrator
to reduce computational cost for their users.

## Annex: a note on ModuleManager
The constraint that there may be at most one of each top-level configuration applies *after* ModuleManager has run.

In the absence of other mods, none of the configurations are present.
With RealSolarSystem, the `principia_gravity_model` and `principia_initial_state` nodes are both present, since they
use a `:NEEDS[RealSolarSystem]` clause.

Modders should make careful use the `@` operator (modify an existing node) and `:NEEDS[]` clause (condition on the presence of a mod) to ensure the requirement is met.

> *Example*: a modder creating a mod AdditionalRealBodies which adds bodies to RealSolarSystem should append
their initial states to `principia_initial_state` and their *sufficient* gravity models to
`principia_gravity_model` with
`@principia_initial_state:FOR[AdditionalRealBodies]:NEEDS[RealSolarSystem]` and
`@principia_gravity_model:FOR[AdditionalRealBodies]:NEEDS[RealSolarSystem]`.

> A modder creating a new solar system mod NeuesSonnensystem should create *nominal* gravity models in a node
without any ModuleManager predicates, `principia_gravity_model`.  Alternatively, they can create *sufficient*
gravity models in that node and provide an initial state in`principia_initial_state`.

> If the author of NeuesSonnensystem wishes some aspect of the system to be conditioned on the presence or
absence of Principia, they can do so in a patch
`@Kopernicus:FOR[NeuesSonnensystem]:NEEDS[Principia]` or
`@Kopernicus:FOR[NeuesSonnensystem]:NEEDS[!Principia]`.

Note that the mathematical operators of ModuleManager will not work on the `quantity` values of Principia
configuration nodes.  Since ModuleManager is [Turing-complete](https://forum.kerbalspaceprogram.com/index.php?/topic/50533--/&page=142&tab=comments#comment-2530142), we
leave it as an exercise to the reader to perform arithmetic on these values.

Modders should refer to the [ModuleManager thread](https://forum.kerbalspaceprogram.com/index.php?/topic/50533--)
for documentation. 