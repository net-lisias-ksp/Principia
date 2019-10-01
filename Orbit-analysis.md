The orbit analysis tool provides information about the current trajectory, seen as a perturbed Kepler orbit.

## Overview

The orbit analysis tool analyses the current trajectory of the active vessel, as an orbit around the body selected in the `Plotting frame selection` window. The trajectory is analysed over a given mission duration. 

The computation occurs in the background; it is tracked by a progress bar.

Below the progress bar is the orbit analysis report from the last computation.

## Orbital elements

### Periods

Three periods are given.

- The sidereal period is the period of the mean longitude Ω+ω+M. 
- The nodal period is the period of the (mean) mean argument of latitude ω+M. This approximately corresponds to the time between successive ascending nodes.
- The anomalistic period is the period of the (mean) mean anomaly M. This approximately corresponds to the time between successive periapsides.

In a Kepler orbit, the longitude of the ascending node Ω and the argument of the periapsis ω are constant, so that all these periods are the same; this is not the case when the orbit is perturbed, and both Ω and ω vary.

### Mean elements

The elements given here are free from *short-period* variations, that is, variations whose period is approximately one revolution.
This is in contrast to the osculating elements (those shown, e.g., by the MechJeb `Orbit Info` window, or the Kerbal Engineer Redux orbital display), which will exhibit strong periodic variations over a revolution.

While short-period variations are eliminated, long-period and secular variations remain in these elements.
In order to express the magnitude of these variations, the elements are given as a range expressed as `midpoint`±`half-width`, indicating that the mean element remains within `half-width` of `midpoint` over the mission duration.

The following elements are displayed:
- the mean semimajor axis a;
- the mean eccentricity e;
- the mean inclination i;
- the mean longitude of the ascending node Ω;
- the mean argument of the periapsis ω.

In addition, the precession rate of Ω (the rate of [nodal precession](https://en.wikipedia.org/wiki/Nodal_precession), i.e., how fast ascending node moves along the equator) is shown. Indeed, in most situations, the nodes will precess at a mostly constant rate.

## Recurrence properties

The treatment of that subject in the orbit analysis tooling, and in particular the notation of the recurrence triple, is heavily inspired by Michel Capderou (2012), *Satellites : de Kepler au GPS*. The figures in this section are produced using Capderou's tool [Ἰξίων](https://climserv.ipsl.polytechnique.fr/ixion/).

### Background on ground track recurrence

In many cases, a satellite orbit is designed to have a repeating ground track, i.e., to be periodic in the surface frame.

The most obvious example of this situation is a geosynchronous orbit, whose orbit traces a single closed loop on the surface of the Earth, or, in the geostationary case, a single point on the equator.

![QZSS orbit]()

Semisynchronous orbits, e.g., Молния or GPS, are also an example; these make two nodal revolutions before the ground track returns to its starting point.

Молния | GPS
---|---
![Молния orbit]() | ![GPS orbit]()

Many satellites however have more complex recurrence relations; for instance the ground track of [ГЛОНАСС](https://en.wikipedia.org/wiki/GLONASS) satellites repeats every 17 revolutions, which corresponds to 8 days; the ground track of [Galileo](https://en.wikipedia.org/wiki/Galileo_(satellite_navigation)) satellites repeats every 17 revolutions, which corresponds to 10 days.

![Galileo orbit]()

Low Earth Orbit satellites also tend to have a ground track recurrence, especially when they are dedicated to Earth observation. For instance, the ground track of [Sentinel-3A](https://en.wikipedia.org/wiki/Sentinel-3A) repeats every 385 revolutions, which corresponds to 27 days.  A whole-Earth map of this ground track over the whole cycle would be an unreadable: it track traces a tight net around the planet. We show instead the whole-Earth ground track over a couple of days, and the ground track over Western Europe over one ground track cycle.

| Whole-Earth | Whole-cycle |
|---|---|
| ![Sentinel-3A whole Earth]() | ![Sentinel-3A whole cycle]() |

### The tool

The orbital analysis tool attempts to determine a cycle which is a good match to the current orbit.  While this works reasonably well once the satellite is on the intended orbit, the tool cannot infer your intentions; if you would like to use it to align your orbit to a particular recurrence cycle, you should uncheck the `Auto-detect` box, and type in the appropriate numbers of revolutions and days per cycle.

## Equatorial crossings

## Mean solar time
(Not yet implemented)