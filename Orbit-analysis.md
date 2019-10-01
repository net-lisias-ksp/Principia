The orbit analysis tool provides information about the current trajectory, seen as a perturbed Kepler orbit.

## Overview

The orbit analysis tool analyses the current trajectory of the active vessel, as an orbit around the body selected in the `Plotting frame selection` window. The trajectory is analysed over a given mission duration. 

The computation occurs in the background; it is tracked by a progress bar.

Below the progress bar is the orbit analysis report from the last computation.

## Orbital elements

### Periods

Three periods are given.

- The sidereal period is the period of the mean longitude Ω+ω+M. 
- The nodal period is the period of the (mean) mean argument of latitude ω&#773;+M&#773;. This approximately corresponds to the time between successive ascending nodes.
- The anomalistic period is the period of the (mean) mean anomaly M&#773;. This approximately corresponds to the time between successive periapsides.

In a Kepler orbit, the longitude of the ascending node Ω and the argument of the periapsis ω are constant, so that all these periods are the same; this is not the case when the orbit is perturbed, and both Ω and ω vary.

### Mean elements

The elements given here are free from *short-period* variations, that is, variations whose period is approximately one revolution.
This is in contrast to the osculating elements (those shown, e.g., by the MechJeb `Orbit Info` window, or the Kerbal Engineer Redux orbital display), which will exhibit strong periodic variations over a revolution.

While short-period variations are eliminated, long-period and secular variations remain in these elements.
In order to express the magnitude of these variations, the elements are given as a range expressed as `midpoint`±`half-width`, indicating that the mean element remains within `half-width` of `midpoint` over the mission duration.

The following elements are displayed:
- the mean semimajor axis a&#773;;
- the mean eccentricity e&#773;;
- the mean inclination i&#773;;
- the mean longitude of the ascending node Ω&#773;;
- the mean argument of the periapsis ω&#773;.

In addition, the precession rate of Ω (the rate of [nodal precession](https://en.wikipedia.org/wiki/Nodal_precession), i.e., how fast ascending node moves along the equator) is shown. Indeed, in most situations, the nodes will precess at a mostly constant rate.

## Recurrence properties

## Equatorial crossings

## Mean solar time
(Not yet implemented)