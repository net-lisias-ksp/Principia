# [Cesàro](https://en.wikipedia.org/wiki/Ernesto_Ces%C3%A0ro)

*This is a draft of the change log.  Cesàro is not available yet.*

## User-facing features

* The history of the vessels is now integrated on multiple threads, one per vessel.  This brings significant performance gains on multi-core processors.  This is particularly visible when warping at 1 000 000× and above with multiple vessels.  Note that the asteroids are vessels from the perspective of KSP, so most game situations actually have many vessels.

## Bug fixes

* Principia might die when crashing a vessel into another.  This has been fixed by detecting that some parts are in the process of being destroyed and ignoring them in the physics computations ([#1553](https://github.com/mockingbirdnest/Principia/issues/1553)).

* An incompatibility between Principia and Kerbal Inventory System (KIS) which caused Principia to crash has been fixed in KIS, thanks to [@ihsoft](https://github.com/ihsoft) ([#1549](https://github.com/mockingbirdnest/Principia/issues/1549) and [KIS #221](https://github.com/ihsoft/KIS/issues/221)).

For more details see all [24](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-08-13T21%3A00%3A00..2017-09-16T23%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Чебышёв and Cesàro.

# [Чебышёв](https://en.wikipedia.org/wiki/Pafnuty_Chebyshev)

## User-facing features

* The speed of trajectory plotting (the main performance issue in previous versions of Principia) has been increased considerably (of the order of 5× to 10× faster) by implementing our own plotting of trajectories.  By cleverly choosing the segments to draw we are able to spend less time drawing or processing the trajectory, while at the same time making the trajectories much smoother (no more angles in the prediction, in particular).  This addresses numerous user complaints, for instance [#1487](https://github.com/mockingbirdnest/Principia/issues/1487).

* Support for tracking burns has been added.  These are burns where the force stays tangent to the trajectory instead of being applied in a fixed direction ([#876](https://github.com/mockingbirdnest/Principia/issues/876)). This is a significant improvement in usability for long, low-thrust burns, which are frequent in RealSolarSystem.

* Both KSP 1.2.2 and KSP 1.3 are supported by this version.  Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).

## Bug fixes

* The plotting frame would revert to 'body-centred inertial' when reverting to launch.  This has been fixed by correctly keeping track of the display mode ([#1453](https://github.com/mockingbirdnest/Principia/issues/1453)).

* The performance in the space centre view was very poor.  This was a regression introduced in Cayley and it has been fixed by avoiding frequent calls to find the tracking station ([#1486](https://github.com/mockingbirdnest/Principia/issues/1486)).

For more details see all [40](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-07-21T22%3A00%3A00..2017-08-13T20%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cayley and Чебышёв.

# [Cayley](https://en.wikipedia.org/wiki/Arthur_Cayley)
## User-facing features

* Vessel trajectories are now displayed for the selected vessel in the tracking station ([#1457](https://github.com/mockingbirdnest/Principia/issues/1457)).

* The colour of the horizon in the inertial frame navball has been changed to use "horizon blue" instead of "dark dark blue".  This makes the manœuvre marker more readable, as it happened to have the same colour as the horizon band, see [#1449](https://github.com/mockingbirdnest/Principia/issues/1449).

* A reminder has been added in the UI when it's time to update Principia because a new moon has passed.

* The release we distribute now includes the Macintosh version.

## Bug fixes

* Since KSP 1.2, the parts of unpacked vessels are lagging behind the current time (and the parts of loaded packed vessels), instead of the orbits being ahead of the current time. This challenged some assumptions made by Principia, and was the root cause of many bugs (including bugs worked around in previous versions), such as [#1272](https://github.com/mockingbirdnest/Principia/issues/1272), [#1416](https://github.com/mockingbirdnest/Principia/issues/1416), [#1441](https://github.com/mockingbirdnest/Principia/issues/1441), and [#1473](https://github.com/mockingbirdnest/Principia/issues/1473), as well as mysterious and worrying errors in the logs. This was fixed by advancing vessels in time when KSP expects them to be advanced.

* In some circumstances KSP would report a collision with a null collider, which confused Principia and caused a crash ([#1447](https://github.com/mockingbirdnest/Principia/issues/1447)). This has been fixed by ignoring such collisions.

* A Kerbal in EVA would sometimes be spawned several metres away from the vessel.  This is because in this case the Kerbal ignores collisions with the ship for a little while, and is nudged back to the airlock.  This nudging conflicted with the nudging done by Principia ([#1452](https://github.com/mockingbirdnest/Principia/issues/1452)).

* A crash would occur when a Kerbal on EVA was unloaded.  This has been fixed by better checking the state of the EVA controller ([#1466](https://github.com/mockingbirdnest/Principia/issues/1466)). This issue was not in Cauchy, since it was introduced in pull request [#1459](https://github.com/mockingbirdnest/Principia/issues/1459), but it affected at least one user who built from master between releases.

## Library changes

* Support has been added for efficiently computing the parts of a segment hidden by a sphere.  This is a significant step towards the goal of making the rendering of trajectories faster and smoother.

For more details see all [16](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-06-17T12%3A30%3A00..2017-07-21T21%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cauchy and Cayley.

# [Cauchy](https://en.wikipedia.org/wiki/Augustin-Louis_Cauchy)

## User-facing features

* The speed of the vessel in the plotting frame is now shown on the periapsis, apoapsis, and locally closest approach markers. The speed normal to the reference plane is shown on the ascending/descending node markers.  This helps in particular when tuning approaches and rendezvous.

* The speed display mode (surface vs. orbit) has been unified with our reference frame selection: the speed display is in surface mode if and only if the surface frame (Body-Centred Body-Fixed) is selected.

* The speed displayed on the navball is always the speed of the vessel in the plotting frame, even when the vessel is not being managed by Principia.

* The nodes—intersections with the reference (orbit) plane—are now displayed in the body-centred parent-aligned and barycentric rotating frames; this should make interplanetary flight planning easier.

* The trajectory of the target vessel is now rendered in reference frames where the target is not fixed. Its history is goldenrod, and its prediction is pig pink.

* The UI has been make a bit simpler and smaller by removing useless information about the state of the plugin.

* For compatibility with 3rd party mods that require celestial targeting for some of their features, it is now possible to target a celestial. This has no interaction with Principia, in particular it is independent from reference frame selection: it exists solely for compatibility. 

## Bug fixes

* Vessels would sometimes slowly rotate away from the closest celestial, even if no torque had been previously applied.  This has been fixed by making the positions and transforms passed to Unity consistent ([#1307](https://github.com/mockingbirdnest/Principia/issues/1307)).

* Switching vessels via the Principia UI would sometimes lock the menu and the map view.  This has been fixed by clearing the lock at the proper place ([#1402](https://github.com/mockingbirdnest/Principia/issues/1402)).

* A spurious change of velocity would sometimes show up as a result of quick-loading.  For instance, when quick-loading in atmospheric flight around Kerbin, the speed would jump by 200 m/s, which is the surface speed of Kerbin.  This was due to vessels being temporarily registered as in orbit on rails, and thus managed by Principia, which would set speeds in the nonrotating frame which were then interpreted in the rotating frame when KSP picked them up as flying.  Principia now keeps managing these vessels to avoid the problem ([#1410](https://github.com/mockingbirdnest/Principia/issues/1410)).

* A vessel would sometimes accelerate when a Kerbal was performing an EVA.  This boils down to ladders being magic in KSP, as illustrated by this hilarious [video](https://www.youtube.com/watch?v=-THq8Gip-Us).  When a Kerbal holds a ladder, that ladder exerts on the Kerbal a force equal to its weight, even if the Kerbal is in weightlessness. When the Kerbal lets go of the ladder, that force goes down to zero.  This was fixed by ignoring the magic ladder force ([#1415](https://github.com/mockingbirdnest/Principia/issues/1415)).

* Some parts would sometimes be offset from their expected position on the launch pad.  This was due to the vessel being in the "prelaunch" state for a few frames, and has been fixed by having Principia wait until it exits that state ([#1421](https://github.com/mockingbirdnest/Principia/issues/1421)).

* Reading saves that had long trajectories would sometimes crash because data structures for the oldest parts of the trajectories would become corrupted.  This has been fixed, and the saves that had this problem in Catalan should be loadable again in Cauchy ([#1422](https://github.com/mockingbirdnest/Principia/issues/1422)).

* Principia would sometimes crash if a save was happening at the same time as exiting physical time warp.  This has been fixed by making sure that the plugin doesn't do any integration if its time is before that of the vessel trajectories ([#1441](https://github.com/mockingbirdnest/Principia/issues/1441)).

* Markers, in particular for apoapsides and periapsides, would sometimes be drawn in the middle of nowhere (i.e., not on the trajectory).  This was due to a data corruption in the vessel trajectories ([#1395](https://github.com/mockingbirdnest/Principia/issues/1395)).

* Landing on the Moon with RealSolarSystem was sometime problematic.  This has been fixed in RealSolarSystem by raising the minimum timewarp altitude ([#1440](https://github.com/mockingbirdnest/Principia/issues/1440)).

## Library changes

* Some support has been added for projective geometry and pinhole camera perspective.  This will allow us in the future to make the rendering of trajectories faster and smoother.

For more details see all [40](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-05-21T12%3A00%3A00..2017-06-17T11%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Catalan and Cauchy.

# [Catalan](https://en.wikipedia.org/wiki/Eug%C3%A8ne_Charles_Catalan)

## User-facing features

No new features in this version, we have focused on fixing bugs, repaying technical debt and doing code restructuring that will be necessary for implementing new features in the future.

## Bug fixes

* When using BetterTimeWarp, the game would crash when trying to do an EVA after landing on a celestial with no atmosphere (such as Mün).  This has been fixed by tweaking the manageability altitude of the vessel ([#1345](https://github.com/mockingbirdnest/Principia/issues/1345)).

* When using BetterTimeWarp, and trying to land on a celestial with no atmosphere, the vessel would sink below the ground, or the celestial surface would jitter, making it hard or impossible to land.  This has been fixed by the same change as the previous bug ([#1346](https://github.com/mockingbirdnest/Principia/issues/1346)).

* When transitioning from space to the atmosphere of a planet (such as Kerbin) the velocity would sometimes increase by the velocity of the surface (200 m/s on Kerbin).  This has been fixed by setting the degrees of freedom in the proper frame during the transition ([#1366](https://github.com/mockingbirdnest/Principia/issues/1366)).

* The planets would sometimes be moving back and forth along their trajectory, or even leave it.  This seemed more likely to happen with a custom solar system that has a double planet.  This has been fixed by asking KSP to properly update the positions ([#1369](https://github.com/mockingbirdnest/Principia/issues/1369)).

* The radial-in and radial-out direction of the autopilot were inverted when in space.  This boiled down to a confusion in KSP where the radial-in icon sets the autopilot to radial-out and vice-versa.  Principia has been modified to compensate for this ([#1370](https://github.com/mockingbirdnest/Principia/issues/1370)).

* The Apocalypse window would freeze the UI.  This problem had been reported in Cardano but we couldn't reproduce it at the time.  We have now been able to reproduce it and to fix it ([#1319](https://github.com/mockingbirdnest/Principia/issues/1319), [#1376](https://github.com/mockingbirdnest/Principia/issues/1376)).

* A `NullReferenceException` would sometimes be propagated to KSP and result in an error message in the logs and the UI.  This has been fixed by properly checking for null pointers in the C♯ code ([#1380](https://github.com/mockingbirdnest/Principia/issues/1380)).

## Library changes

* It is now possible to describe a solar system using a data file containing [keplerian coordinates](https://github.com/mockingbirdnest/Principia/blob/2017052520-Catalan/astronomy/kerbol_initial_state_0_0.proto.txt) (cartesian coordinates have been supported for a long time).

* Date literals can now be written as [Julian](https://github.com/mockingbirdnest/Principia/blob/2017052520-Catalan/astronomy/time_scales_test.cpp#L363) or [Modified Julian](https://github.com/mockingbirdnest/Principia/blob/2017052520-Catalan/astronomy/time_scales_test.cpp#L368) dates, which are convenient when describing astronomical phenonema.

* Orbits may now be described using a large variety of [keplerian elements](https://github.com/mockingbirdnest/Principia/blob/2017052520-Catalan/physics/kepler_orbit.hpp#L27) which obviates the need to perform offline computations to transform the characteristics of a body into something acceptable by Principia. Note that while it is possible to specify a large number of combinations of elements, the computations are numerically quite naïve, and may be result in large errors near singularities.

For more details see all [28](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-04-23T11%3A59%3A00..2017-05-21T11%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cartan and Catalan.

# [Cartan](https://en.wikipedia.org/wiki/%C3%89lie_Cartan)

NOTE: Cartan is save-compatible with Cardano.  However, existing saves won't take advantage of the faster integrators.  You'll need to create a new save to see the speed-up.

## User-facing features

* Principia now supports a vessel-centred frame directed along the horizontal and the vertical of a celestial.  This is useful for performing rendezvous.  The points of closest approach and the points where the active vessel crosses the plane of the target vessel trajectory are displayed on the prediction and flight plan.  See the description of plotting frames in the [Concepts](https://github.com/mockingbirdnest/Principia/wiki/Concepts) document and our [guide to rendezvous](https://github.com/mockingbirdnest/Principia/wiki/A-guide-to-performing-low-orbit-rendezvous/3bb254e1378bcba1c014a5990eec15c3ae5eb17d) for details regarding the use of this frame.

* The integrators used for computing the positions of the celestials and the histories of the vessels have been changed.  We now use symmetric linear multistep integrators instead of symplectic Runge-Kutta-Nyström integrators.  The former are conjugate-symplectic, which is nearly as good as symplectic, and they produce much denser output.  As a consequence the integration of the celestials is much more precise (errors in the meters per year instead of thousands of kilometers) and the integration of the vessels is about 5 times faster.  Warping at 100 000× is completely smooth even with 20 vessels, and warping at 1 000 000× is janky but usable.

## Bug fixes

* The stabilization of the Jool system that was introduced in Brouwer got lost in Cardano, causing an Apocalypse in some situations.  This has been fixed ([#1319](https://github.com/mockingbirdnest/Principia/issues/1319)).

* A crash might happen during EVA if the unfortunate Kerbal would touch a non-physically-significant part, such as a barometre.  This has been fixed by going up the part tree until a physically-significant part is found ([#1308](https://github.com/mockingbirdnest/Principia/issues/1308)).

* A crash might happen when warping from the sphere of influence of a celestial to that of another, especially if the second celestial is large (e.g., Kerbol).  This has been fixed by properly detecting the change of sphere of influence ([#1302](https://github.com/mockingbirdnest/Principia/issues/1302)).

* Creating a manœuvre with the reference frame fixing the centre of a celestial and the line towards another celestial (e.g. Earth-Centred Sun-Aligned, ECSA) would systematically cause a crash ([#1293](https://github.com/mockingbirdnest/Principia/issues/1293)).

* In some cases Principia would lose track of a vessel and then find it again, but it would be confused about its sphere of influence.  Combined with the tilt this might cause strange drifts ([#1299](https://github.com/mockingbirdnest/Principia/issues/1299)).  

For more details see all [50](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-03-25T17%3A00%3A00..2017-04-23T11%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cardano and Cartan.

# [Cardano](https://en.wikipedia.org/wiki/Gerolamo_Cardano)

**WARNING: Cardano is *not* save-compatible with previous versions of Principia.  If you have a game saved with Cantor or earlier, it won't load (or it will crash) if you try to use it in Cardano.**

## User-facing features

* Principia now works with KSP version 1.2.2.  Older versions of KSP are no longer supported ([#1150](https://github.com/mockingbirdnest/Principia/issues/1150), [#1237](https://github.com/mockingbirdnest/Principia/issues/1237), [#1244](https://github.com/mockingbirdnest/Principia/issues/1244)).

* Celestials may now have proper axial tilt and rotation.  This is particularly useful when using RealSolarSystem.  For instance, the [rings of Saturn](http://i.imgur.com/I5DqakT.png) are (correctly) shown in the same plane as its satellites.  Previously they would show up as being in the plane of Earth's equator, at an angle from the satellites.  Similarly the [lightning of the Earth](http://i.imgur.com/LknBHOL.png) correctly reflects the seasons.

* Two new plotting frames have been added:
  * A frame centred on a body and directed towards a second body.
  * A frame centred on a body and rotating with the surface of that body.  For that frame, the navball tracks the surface and is oriented North-East-Down.

* The handling of the physics bubble has been completely rewritten to take advantage of the new features of KSP version 1.2.x.  Unless engines (including RCS) are thrusting, a vessel will follow its free-falling trajectory regardless of whether or not it is timewarping.

## Bug fixes

* When using an unstable solar system, the "apocalypse" that occurs when two celestials collide is now reported in the UI instead of causing a mysterious crash ([#1114](https://github.com/mockingbirdnest/Principia/issues/1114), [#1115](https://github.com/mockingbirdnest/Principia/issues/1115)).

* The rewrite of the physics bubble fixed several bugs:
  * The phantom accelerations which sometimes prevented warping are gone ([#1138](https://github.com/mockingbirdnest/Principia/issues/1138)).
  * The gravitational acceleration is now calculated for each vessel, not for the centre of mass of the loaded vessels.  This fixes problems where accelerations would be incorrect on some vessels, resulting in jumps and sudden shifts of the gravity vector ([#1048](https://github.com/mockingbirdnest/Principia/issues/1048)).

## Library changes

* Implemented [symmetric linear multistep integrators](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/symmetric_linear_multistep_integrator.hpp) (not used in this release).
* Ported the [symplectic partitioned Runge-Kutta integrators](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/symplectic_partitioned_runge_kutta_integrator.hpp) (more general than the symplectic Runge-Kutta-Nyström integrators), including [leapfrog, which appears in Newton's *Principia*](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/symplectic_partitioned_runge_kutta_integrator.hpp#L108-L133), to a form compatible with the implementation used for the existing [symplectic Runge-Kutta-Nyström integrators](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/symplectic_runge_kutta_nystr%C3%B6m_integrator.hpp).
Principia's `integrators` library now has 37 different fixed step conjugate-symplectic and symplectic integrators.
* Integrators are now based on [`Instance`s](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/ordinary_differential_equations.hpp#L136-L167), which hold any persistent state that the integrator might need in addition to the state of the system; this is important for resumability of multistep or variable-step integrators.
* Constructors of `Rotation`s from [Euler angles and (appropriately for this release) Cardano angles](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/geometry/rotation.hpp#L44-L62) have been added. These are used in [pre-existing code](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/physics/kepler_orbit_body.hpp#L217-L220) (Keplerian elements) as well as for the rotations defining [the surface frame of celestials](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/physics/rotating_body_body.hpp#L99-L104), used to implement axial tilt.
* Implemented a proper [double-double addition](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/numerics/double_precision_body.hpp#L203-L210), since the (pre-existing) [compensated summation](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/numerics/double_precision_body.hpp#L51-L60) was not up to the task of the ill-conditioned sum in linear multistep integrators.

## Astronomy

* We had noticed that we were not able to predict very precisely the position of some small bodies of the solar system, so we made a thorough analysis of the behaviour of Phobos.  It turns out that the spherical harmonics *C*₂₂ and *S*₂₂ of Mars have a considerable influence on the orbit of its satellites.  Unfortunately, adding them to our model would, as things stand, make the game too slow, and was too complex for implementation in Cardano.  We'll try to improve this in the future, maybe by using symmetric linear multistep integrators.
* We analysed [the dynamical stability of the retrobop system](https://github.com/mockingbirdnest/Principia/wiki/On-the-dynamical-stability-of-Principia's-modified-Jool-system), noticing that it is highly chaotic.

We have not released for 8 months.  Going forward, we plan to release more often, even if that means making smaller changes in each release.  We'll try to have a new release coincident with each new moon.

For more details see all [166](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2016-07-23T18%3A59%3A59..2017-03-25T17%3A00%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cantor and Cardano.

# [Cantor](https://en.wikipedia.org/wiki/Georg_Cantor)

[And we're out of β, we're releasing on time!](https://www.youtube.com/watch?v=Y6ljFaKRTrI)  We believe that the mod as now sufficiently functional and stable to be fun to play with, so we are making it more broadly available.  Download it [here](https://goo.gl/eZbr4e).

## User-facing features

* When using stock KSP, the clock now properly uses 6-hour days instead of 24-hour days ([#1085](https://github.com/mockingbirdnest/Principia/issues/1085)).

## Library changes

* Implemented date and time literals that are interpreted at compile time. Using these, [four time scales](https://github.com/mockingbirdnest/Principia/blob/2016081314-Cantor/astronomy/time_scales.hpp#L31-L34) are available to write [`Instant` literals, again interpreted at compile time](https://github.com/mockingbirdnest/Principia/blob/2016081314-Cantor/astronomy/time_scales_test.cpp#L78-L101): *Temps Terrestre* (TT), *Temps Atomique International* (TAI), Coordinated Universal Time (UTC), and UT1. [The dates in the lunar eclipse tests now use UT1 literals](https://github.com/mockingbirdnest/Principia/blob/2016081314-Cantor/astronomy/lunar_eclipse_test.cpp#L243-L248). Since Principia does not support general relativity, and has a unified `Instant` type for the time coordinate, *Temps Dynamique Barycentrique* (TDB), which is used for the ephemerides of the solar system, is identified with TT, and *Temps-Coordonnée Géocentrique* (TCG) and *Temps-Coordonnée Barycentrique* (TCB) are not supported.

For more details see all [8](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2016-06-26T19%3A00%3A00..2016-07-23T18%3A59%3A59+sort%3Acreated-asc) pull requests between بوژگانی and Cantor.

# [بوژگانی](https://en.wikipedia.org/wiki/Abu_al-Wafa%27_Buzjani)

## User-facing features

* Principia now works with KSP version 1.1.3.  Older versions of KSP are no longer supported.
* The times of periapsides and apoapsides are now displayed on the trajectories.
* The norm of the velocity in the plotting frame is displayed when the navball is fixed in the plotting frame.
* The check that the C++ 2015 Redistributable runtime is properly installed on Windows has been tightened.

## Modder-facing changes

* The state of the ephemeris at startup is now logged to help in debugging modified solar systems.
* The fix that prevents the Jool system from getting unstable is now applied more strictly, so that modified stock solar system don't get clobbered by this fix.
* Gravity models may now be specified using Keplerian elements (in addition to Cartesian elements).

## Bug fixes

* An obscure bug has been fixed that would infrequently cause the trajectories of the celestials to be discontinuous because of cancellations in Чебышёв series.
* Fixed a bug where the vessels would take a hard turn when the sphere-of-influence changes ([#1053](https://github.com/mockingbirdnest/Principia/issues/1053)).

## Known issues

* The release name, being in Farsi, is written right-to-left.  KSP doesn't know how to do such an advanced thing, so it shows up inverted in the UI.  Apologies to Farsi speakers.

For more details see all [33](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2016-05-20T21%3A00%3A00..2016-06-26T18%3A59%3A59+sort%3Acreated-asc) pull requests between Burnside and بوژگانی.

# [Burnside](https://en.wikipedia.org/wiki/William_Burnside)

## User-facing features

* Changed the prediction parameters to be per vessel as opposed to global.  Thus, different vessels may have predictions of different lengths or accuracies.
* Changed the way that the trajectories of celestials are recorded in saves: instead of recording everything that was computed in the course of the game, only the next 6 months or so are saved.  The rest is recomputed when the save is loaded.  The advantage is that the saves are considerably smaller (a factor of 100x has been observed in simple games) which makes choosing a save in KSP faster as it insists on loading all the saves in memory.  The drawback is that loading a save is more CPU-intensive and may therefore take longer.
* The plugin has a new icon.

## Bug fixes

* Fixed the stabilization of the Jool system in the stock game which had stopped working in Буняковский.  This is the hotfix previously released as *Буняковский 6*.
* Fixed a situation where adaptive step integration would crash when the system was already integrated to the desired final time ([#1024](https://github.com/mockingbirdnest/Principia/issues/1024)).
* Fixed a problem where the start of a flight plan would be discarded to the point that it had no burns anymore and various pieces of the code would disagree as to whether the vessel still had a flight plan ([#1022](https://github.com/mockingbirdnest/Principia/issues/1022), [#1023](https://github.com/mockingbirdnest/Principia/issues/1023)).

For more details see all [16](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2016-05-05T16%3A00%3A00..2016-05-20T21%3A59%3A59+sort%3Acreated-asc) pull requests between Буняковский and Burnside.

# [Буняковский](https://en.wikipedia.org/wiki/Viktor_Bunyakovsky)

## User-facing features

* Added code to try to detect bad installations.
* Joint Windows and Linux build.
* Give the user more control over the length of the predicted flight plan trajectory.
* Prevent accidental deletion of a non-empty flight plan.
* Display the total Δv of the flight plan.
* Limit the amount of time that we are willing to spend computing the trajectory of celestials.  This prevents the game from freezing when trying to extend e.g., the prediction to be very long.  The prediction is just going to be progressively extended over several seconds.
* Compute and display the apsides of trajectories, which makes it easier to evaluate the altitude of the predicted flight plan.  Note that, for trajectories that are very far from a conic, there may be many apsides. Note that apsides are only displayed with respect to the fixed celestial, if there is one.
* Tweaked the colours and styles used to display trajectories.
* Added a button to time warp to the next manœuvre (1 min ahead of the time of ignition).
* Changed the prediction computation to be defined by a number of steps, not a length.  This makes the amount of work performed at each frame roughly constant.
* Support for KSP 1.1.2.

## Bug fixes

* Fixed a crash when saving with RealSolarSystem installed ([#905](https://github.com/mockingbirdnest/Principia/issues/905)).  This is the hotfix previously released as *Buffon 12*.
* Fixed yet another use-after-free bug ([#908](https://github.com/mockingbirdnest/Principia/issues/908)) and added checks to detect situations that can lead to this kind of bug.
* Fixed a problem where burns would sometimes result in an infinite Δv.

## Optimizations

* Stopped serializing the trajectories of the flight plan, recompute them instead.  Also properly discard past trajectories (we used to keep them around for no good reason).  This makes the saves smaller.
* Moved to x64 on Windows and stopped supporting Win32.  This brought significant performance improvements (about 30%) for the integrators.
* Increased the protocol buffer deserialization limit to 512 MiB, which should make it possible to re-read very large saves.  Since we are now creating significantly smaller saves, this should suffice for most missions.

## Library changes

* Added parameterization to limit the number of integration steps performed by adaptive integrators.
* Improved the encapsulation and testing of the Vessel class.  Hopefully this will improve the stability of the plugin.
* Two-step journaling makes it easier to reproduce crashes.

For more details see all [75](
https://github.com/mockingbirdnest/Principia/pulls?page=1&q=is%3Apr+is%3Aclosed+merged%3A2016-02-22T20%3A00%3A00..2016-05-05T16%3A59%3A59+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Buffon and Буняковский.

# [Buffon](https://en.wikipedia.org/wiki/Georges-Louis_Leclerc,_Comte_de_Buffon)

## User-facing features

* The integrators now limit the number of steps they perform, and terminate if their step size vanishes. This avoids issues where the plugin would hang when the trajectory would accidentally get very close to the centre of a celestial body or spend a long time in a low orbit.
* The version identifier of the plugin is now displayed in the UI to make it is easier to assert what version is running.

## Bug fixes

* A use-after-free bug has been fixed which caused a variety of crashes ([#872](https://github.com/mockingbirdnest/Principia/issues/872), [#881](https://github.com/mockingbirdnest/Principia/issues/881), [#889](https://github.com/mockingbirdnest/Principia/issues/889), [#896](https://github.com/mockingbirdnest/Principia/issues/896)) when the historical trajectory was shortened in a way that would cause it to start after the beginning of the flight plan.

## Library changes

* A verbosity option has been added to the journalling which makes it easier for us to reproduce crashes.

For more details see all [19](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+merged%3A2016-02-09T21%3A00%3A00..2016-02-22T20%3A00%3A00+is%3Aclosed+) pull requests between Brouwer and Buffon.

# [Brouwer](https://en.wikipedia.org/wiki/L._E._J._Brouwer)

## User-facing features

* The whole Frenet trihedron is now displayed in the correct reference frame when "fix navball in plotting frame" is selected.
* The initial state (and thus the evolution) of the system is now deterministic even when not using RealSolarSystem.
Tidally locked bodies no longer spin back and forth madly (on the other hand, they may not be tidally locked if their mean period differs from their Jacobi osculating period).
* When using stock, the Jool system is modified, cancelling the apocalypse. Specifically, we make the inner Jool system nonresonant, since we have been unable to replicate the results (Manley, priv. comm.) according to which some interpretations of the orbital elements yielded a stable Laplace resonance, despite systematic searches of the Jacobi osculating elements. In addition, at [Scott Manley](https://www.youtube.com/user/szyzyg)'s and [@pdn4kd](https://github.com/pdn4kd)'s suggestion, we put Bop in a surprisingly stable, though highly precessing, retrograde orbit. The modified system is stable for upwards of a century.
* Flight planning has been implemented.

## Modder-facing changes

* When a Cartesian initial state cfg is not given, the KSP orbital elements are interpreted in a hierarchical osculating Jacobi fashion; for instance, the orbital elements of Jool are the osculating elements at game start of the orbit of the barycentre of the Jool system around the barycentre of the (sun, moho, eve, gilly, kerbin, mun, minmus, duna, ike, dres) system; the elements of Laythe are the osculating elements at game start of the orbit of Laythe around Jool; the elements of Vall are the osculating elements at game start of the orbit of Vall around the Laythe-Jool barycentre.

## Optimizations

* The Windows build now uses profile-guided optimization (we estimate that this improves performance by ~20%); in theory this could be extended to other platforms.
* The evaluation of the Чебышёв series has been significantly optimized.
* [@sarbian](https://github.com/sarbian) made trajectory rendering faster (as he pointed out, there is still lots of room for improvement).

## Library changes

* Everything that crosses the C++/C# interface can now be journalled if the right flag is set, allowing us to replay the C++ side of a session; this is useful for tracking down tricky bugs, and it enables profile-guided optimization.
* In order to get the full Frenet trihedron, (which was needed for manœuvres, since the Δv is defined in the Frenet frame at the point of ignition) geometric acceleration (the acceleration of a free-falling trajectory) in any reference frame was needed. To do that we created two abstractions, RigidMotion, the derivative of a RigidTransformation, and DynamicFrame, the definition of an arbitrary reference frame. The navigation frames (the frames in which the trajectory is drawn, or with which the manœuvres are defined) implement that (see BodyCentredNonRotatingDynamicFrame and BarycentricRotatingDynamicFrame).
* In order to interpret the orbital elements of KSP in the hierarchical Jacobi fashion described above, support was added for Kepler orbits (implementation), Jacobi coordinates, and hierarchical systems.
* Discrete trajectories were reworked, with a heavy dose of CRTP.
* In preparation for the surface frame in the future, RotatingBody was added.
* The C++ interface headers and C# extern declarations were repetitive and error-prone, this was exacerbated by the addition of journalling code and replaying code, so a generator was written to produce all of that from an annotated proto.
* [@pdn4kd](https://github.com/pdn4kd) contributed some tests of lunar eclipse timings.
* For both Kepler orbits and lunar eclipse timings, a simple root finder was needed, bisection does the job for now.
* A bibliography was written, at [@pdn4kd](https://github.com/pdn4kd)'s request (it is somewhat out of date).
* SolarSystem, a class for initializing ephemerides from protobuf text format configuration files for testing purposes was written.
* A script for generating the initial state configuration files from the emails sent by JPL's HORIZONS system was written (the gravity model configuration file is hand-curated).
* An utility turns the protobuf text format configuration files into KSP ModuleManager configuration files for RSS support.
* Various geometric utilities were added: angles (implementation), spherical coordinates (more are needed).
* More C++11/14 features were used as they became available (for instance, the units are now constexpr), in addition we now use std::experimental::optional.
* C++14-related improvements were made to not_null.

For more details see all [195](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2015-08-15T15%3A00%3A00..2016-02-09T22%3A00%3A00+sort%3Acreated-asc) pull requests between Bourbaki and Brouwer.

# [Bourbaki](https://en.wikipedia.org/wiki/Nicolas_Bourbaki)

## User-facing features

* Ephemeris: the celestial bodies are integrated on their own, with their own (much larger) timestep (45 min);
their trajectories are then fitted using чебышёв series, yielding continuous trajectories. This means that when there are no vessels (including asteroids, see the FAQ), timewarp at very high speed (6'000'000x was tested in RealSolarSystem) is smooth.
* The predictions are computed using an adaptive step size, so they're faster and less fiddly (you still get a tolerance setting, but it doesn't need as much attention as the step size setting; the step size will shorten near periapsis and lengthen near apoapsis on its own). The histories are still in fixed steps of 10 s.
* There is an initial configuration for RealSolarSystem: the planets will start in the right places as given by the JPL HORIZONS service, and they are given gravity models using the freshest data available (Vesta's model is from Dawn data, some Cassini data gets used).  A side effect of that is that the moon becomes far more accurate: since the motion of the moon is very much a 3-body problem, it cannot be accurately represented in RealSolarSystem alone. In particular, real-life eclipses can be observed in Principia + RealSolarSystem. This configuration also includes *J*₂ for the Sun, the planets, the Moon, and Vesta, so the resulting effects are felt (precession of Earth orbits, the possibility of heliosynchronous orbits, etc.).
* Bourbaki is save-compatible with Borel.  However, for RealSolarSystem users, please note that unless you reset the plugin, the new initial state and gravity model configuration files will not be taken into account.

## Library changes

* Reimplemented the integrators: the symplectic Runge-Kutta-Nyström integrator was reimplemented more cleanly, an embedded explicit Runge-Kutta-Nyström integrator was implemented. Abstractions for differential equations were created.

For more details see all [89](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-05-06T22%3A00%3A00..2015-08-15T15%3A59%3A59+sort%3Acreated-asc) pull requests between Borel and Bourbaki.

# [Borel](https://en.wikipedia.org/wiki/%C3%89mile_Borel)

## User-facing features
* Ported to version 1.0.x of KSP.
* Added custom navball settings, so that the navball can be fixed in the reference frame in which the trajectory is plotted; the IVA navball is unaffected; when using the custom navball, the prograde/retrograde vectors are now in the correct reference frame, consistent with what is shown is map view; the rest of the Frenet trihedron (the radial and normal vectors) are unaffected at the moment and will be fixed in another version.
* Added a setting to clip histories.
* Added a toolbar button to show/hide the UI.
* The UI now acknowledges the F2 key.
* Less memory-hungry.

## Bug fixes
* Fixed a crash ([#463](https://github.com/mockingbirdnest/Principia/issues/463)) when attempting to integrate with tmax_is_exact and tmax is at the end of the trajectory.
* Fixed a crash ([#480](https://github.com/mockingbirdnest/Principia/issues/480)) caused by an access a non-existent vessel.
* Fixed a UI bug ([#502](https://github.com/mockingbirdnest/Principia/issues/502) where, if the vessel is switched, the map kept showing the trace from the last viewed vessel.

For more details see all [27](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-03-22T15%3A00%3A00..2015-05-06T21%3A59%3A59+sort%3Acreated-asc+) pull requests between Bolzano and Borel.

# [Bolzano](https://en.wikipedia.org/wiki/Bernard_Bolzano)

## Optimizations

* Changed the serialization code to read/write data in chunks instead of holding several copies of the entire serialized form in memory.

## Library changes

* Added numerous integrators, and restructured the code to separate the symplectic Runge-Kutta-Nyström integrators from the symplectic partitioned Runge-Kutta integrators.  Started to analyze their numerical characteristics and performance.

For more details see all [11](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-02-28T14%3A00%3A00..2015-03-22T14%3A59%3A59+sort%3Acreated-asc+) pull requests between Bessel and Bolzano.

# [Bessel](https://en.wikipedia.org/wiki/Friedrich_Bessel)

## User-facing features

* Rudimentary predictions have been added.  The predictions are currently using the same integration method (McLachlan and Atela's 1992 optimal 5th order method), with the same splitting of the Hamiltonian (kinetic + potential energy), this is somewhat usable but unacceptably slow.

## Bug fixes

* Fixed a bug ([#461](https://github.com/mockingbirdnest/Principia/issues/461)) where Principia would switch to a nonrotating reference frame while still in the atmosphere.

For more details see all [5](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-02-23T23%3A00%3A00..2015-02-28T13%3A59%3A59+sort%3Acreated-asc+) pull requests between Бернштейн and Bessel.

# [Бернштейн](https://en.wikipedia.org/wiki/Sergei_Natanovich_Bernstein)

## Bug fixes

* Fixed a crash on revert to VAB: when reverting to VAB, the old save was loaded immediately, but the time was only reset when exiting the VAB. Running Principia in the editor caused it to integrate back to the future, and caused a crash when KSP's time was reverted.  Thanks to [@diomedea](https://github.com/diomedea) for reporting this.

For more details see all [6](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-02-22T23%3A00%3A00..2015-02-23T22%3A59%3A59+sort%3Acreated-asc+) pull requests between Bernoulli and Бернштейн.

# [Bernoulli](https://en.wikipedia.org/wiki/Daniel_Bernoulli)

## User-facing features

* Improved logging by printing out the stack trace in case of crash, as well as the base address of the DLL.
* Minor UI improvements.

For more details see all [6](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-02-16T21%3A00%3A00..2015-02-22T22%3A59%3A59+sort%3Acreated-asc+) pull requests between Banach and Bernoulli.

# [Banach](https://en.wikipedia.org/wiki/Stefan_Banach)

First non-ɑ release (also known as: first β release).  It might be possible to play.

## User-facing features

* Serialization has been implemented.  It is now possible to save the state of Principia.

## Optimization

* Improved rendering performance by not reallocating gigantic objects at every frame.  Thanks to [@sarbian](https://github.com/sarbian) for pointing this out.

For more details see all [39](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-01-21T21%3A00%3A00..2015-02-16T20%3A59%3A59+sort%3Acreated-asc+) pull requests between Agnesi and Banach.

# [Agnesi](https://en.wikipedia.org/wiki/Maria_Gaetana_Agnesi)

## Bug fixes

* Fixed a crash due to adding 0-part vessels to the physics bubble.
* Fixed a bug where the plugin would still manage the physics bubble at ground level on bodies without an atmosphere.
* Fixed a bug where a crashed vessel would keep being simulated.

## Optimization

* Improved performance by not calling FindObjectOfType at every frame.

## Library changes

* Started work on serialization using the Google protocol buffer library.

For more details see all [4](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-01-18T23%3A00%3A00..2015-01-21T20%3A59%3A59+sort%3Acreated-asc+) pull requests between Ackermann and Agnesi.

# [Ackermann](https://en.wikipedia.org/wiki/Wilhelm_Ackermann)

## User-facing features

* Better logging and UI controls for logging.

For more details see all [2](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-01-17T17%3A00%3A00..2015-01-18T22%3A59%3A59+sort%3Acreated-asc+) pull requests between Abel and Ackermann.

# [Abel](https://en.wikipedia.org/wiki/Niels_Henrik_Abel)

First public ɑ release.  Not exactly usable.  About 9 months of development before that point.

For more details see all [300](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2010-01-01T01%3A00%3A00..2015-01-17T16%3A59%3A59+sort%3Acreated-asc+) pull requests before Abel.