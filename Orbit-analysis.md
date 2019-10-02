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

|![QZSS ground track](https://i.imgur.com/nJnjsqN.png) | ![QZSS orbit](https://i.imgur.com/hODLnIH.png) |
|---|---|

Semisynchronous orbits, e.g., Молния or GPS, are also an example; these make two nodal revolutions before the ground track returns to its starting point.

Молния | GPS
---|---
![Молния orbit, orthographic](https://i.imgur.com/4whFQXO.png) ![Молния orbit, Lambert](https://i.imgur.com/MuuKx0r.png) | ![GPS orbit, Cassini](https://i.imgur.com/KLZil2D.png) ![GPS orbit, Mercator](https://i.imgur.com/3vEFdwT.png)

Many satellites however have more complex recurrence relations; for instance the ground track of [ГЛОНАСС](https://en.wikipedia.org/wiki/GLONASS) satellites repeats every 17 revolutions, which corresponds to 8 days; the ground track of [Galileo](https://en.wikipedia.org/wiki/Galileo_(satellite_navigation)) satellites repeats every 17 revolutions, which corresponds to 10 days.

| ![Galileo orbit, stereographic](https://i.imgur.com/n2J5GDD.png) | ![Galileo orbit, mercator](https://i.imgur.com/vHj6PFJ.png) |
|---|---|

Low Earth Orbit satellites also tend to have a ground track recurrence, especially when they are dedicated to Earth observation. For instance, the ground track of [Sentinel-3A](https://en.wikipedia.org/wiki/Sentinel-3A) repeats every 385 revolutions, which corresponds to 27 days.  A whole-Earth map of this ground track over the whole cycle would be unreadable: it traces a tight net around the planet. We show instead the whole-Earth ground track over a couple of days, and the ground track over Western Europe over one ground track cycle.

| ![Sentinel-3A whole Earth](https://i.imgur.com/irgbQgY.png) | ![Sentinel-3A whole cycle](https://i.imgur.com/99tnSrM.png) |
|---|---|

### The tool

The orbital analysis tool attempts to determine a cycle which is a good match to the current orbit.  While this works reasonably well once the satellite is on the intended orbit, the tool cannot infer your intentions; if you would like to use it to align your orbit to a particular recurrence cycle, you should uncheck the `Auto-detect` box, and type in the appropriate numbers of revolutions and days per cycle.

#### The recurrence triple
The recurrence triple consists of three numbers [ν<sub>o</sub>; D<sub>T<sub>o</sub></sub>; C<sub>T<sub>o</sub></sub>].

C<sub>T<sub>o</sub></sub> is the number of days per cycle.

ν<sub>o</sub> is the number of orbits per day, rounded to the nearest integer.

D<sub>T<sub>o</sub></sub> is the number of orbits per cycle in excess of ν<sub>o</sub> C<sub>T<sub>o</sub></sub>.
In other words, the number of orbits per day is ν<sub>o</sub> + D<sub>T<sub>o</sub></sub> / C<sub>T<sub>o</sub></sub>.

This means that orbits that have similar periods will have similar values of ν<sub>o</sub>, the approximate number of orbits in a single day: even though а ГЛОНАСС satellite has an 8-day, 17-revolution cycle, a Galileo satellite has a 10-day, 17-revolution cycle, a GPS satellite has a 2-day, 1-revolution cycle, and a 北斗 MEO satellite has a 7-day, 13-revolution cycle, all have ν<sub>o</sub> = 2, i.e., they are close to semisynchronous.

If D<sub>T<sub>o</sub></sub> = 0, there is an integer number of orbits per day; the orbit is synchronous or sub-synchronous. Note that this induces stronger resonances with the geopotential, so such orbits are less stable than similar orbits with a longer cycle.

#### The equatorial shift, grid interval, and subcycle

The equatorial shift is the angle, measured on the surface, between successive crossings of the equator; it measures how much the orbit shifts from one ascending pass to the next (as seen from an observer on the ground).
The corresponding distance along the equator is given in parentheses. On planets with prograde rotation, the equatorial shift is almost always negative, i.e., westwards.

| | |
|---|---|
| In this map, we can see an equatorial shift of -25°.2, or 2810 km: the ground track starts north of New Guinea, and, one revolution later, is 2810 km west of its starting point, over Borneo.  | ![One nodal revolution of Sentinel-3A](https://i.imgur.com/BQX9O1A.png) |

The grid interval is the angle, measured on the surface, between neighbouring tracks on the equator; note that neighbouring tracks may be many revolutions apart. As for the equatorial shift, the corresponding distance along the equator is given in parentheses.

| | |
|---|---|
| In this map, we can see grid interval of 0°.93, or 104 km: the ground track traces a grid whose spacing on the equator is 104 km; over the course of 27 days, the satellite will fly over locations 104 km apart along the equator.  | ![Ground track of Sentinel-3A over Borneo](https://i.imgur.com/Vqj9wfq.png) |

The grid interval is important for observation satellites: the instrument swath (the extent of the surface which is seen by the instrument) must be wider than the grid interval in order for the whole surface to be observed.

The subcycle is the number of days after which the ground track comes back to within one grid interval of its starting point.

| | |
|---|---|
| In this map, we can see the ground track of Sentinel-3A over one subcycle (4 days); the last ascending pass (in blue) is one grid interval away from the first one (in red), north of New Guinea. All ascending passes before that are further away. | ![Ground track of Sentinel-3A over one subcycle](https://i.imgur.com/alioW0T.png)

The subcycle measures how quickly the satellite will come “close” (as defined by the grid interval) to any point on the surface; a short grid interval allows the satellite to quickly observe any given target; a long grid interval may require waiting a full ground track cycle before an observation can be made.

## Equatorial crossings

The properties of the recurrence described in the preceding section are purely theoretical. The analysis of the equatorial crossings of the *actual* orbit describes how well that orbit follows the nominal recurrence.

The passes are numbered as follows: on the recurrence grid, the ascending pass whose equatorial crossing has the smallest longitude East of the reference meridian is pass 1; subsequent passes are numbered chronologically, with revolution n comprising ascending pass 2n-1 and descending pass 2n: odd passes are ascending, even passes descending.

The longitude of ascending pass differs from the previous one by the equatorial shift.

The longitudes of the equatorial crossings of the ascending and descending passes are given as ranges of longitudes on the equator. The midpoint describes where the recurrence grid is situated on the planet; the width describes how much the satellite deviates from the nominal recurrence grid. This deviation is also indicated as a distance measured along the equator.

On a well-kept orbit, this deviation should be much smaller than the grid interval.

## Mean solar time
(Not yet implemented)