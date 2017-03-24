This page is a bit of a wall of text.  Why should you read it, when you have just downloaded Principia and want to go play with it and have fun?

Well, it turns out that N-body celestial mechanics is rather more complicated than the 2-body simplification offered by stock KSP.  In order to help planning and understanding elaborate missions that take advantage of N-body physics, Principia provides a number of tools that let you look at trajectories in different frames, use more advanced navballs and plan complex flight paths.

So if you want to become a senior rocket pilot, to execute [horseshoe orbits](https://en.wikipedia.org/wiki/Horseshoe_orbit), [Lissajous orbits](https://en.wikipedia.org/wiki/Lissajous_orbit), [heliosynchronous orbits](https://en.wikipedia.org/wiki/Sun-synchronous_orbit) and [ballistic captures](https://en.wikipedia.org/wiki/Ballistic_capture), please read on.  Oh, and you'll be able to say these [six words you never say at NASA](https://xkcd.com/1244/).

# Trajectories

A trajectory is a line depicting the positions of a vessel.  In stock KSP, all trajectories are conics so there is not a lot of complexity to displaying or understanding them.  With N-body physics, though, trajectories may become more complex (and are certainly not conics in the interesting cases) so Principia comes with additional tools for plotting trajectories.

For each vessel, Principia may display three trajectories:
* The *history*, painted in acid green, shows where your vessel was in the past.
* The *prediction*, painted in fuchsia, shows where your vessel will go if you just sit on your hands: no engine burns, no separations, no nothing.
* The *flight plan*, painted in alternative segments of solid orange red and dashed baby blue, shows where your vessel will go if you execute the planned flight plan with no errors (more on flight planning later).

The main Principia UI let you control the length of the history (`Max history length`) and the settings of the prediction and flight plan (`Tolerance` and `Length` under `Prediction Settings`).  There are trade-offs in using these parameters: keeping a long history is aesthetically pleasing but it may also be confusing and may consume a lot of memory.  Computing a long prediction (or flight plan) with a low tolerance may end up consuming lots of CPU and make the game feel unresponsive.  Use your judgement: you probably don't need a 1 metre tolerance when planning a multi-month trip to Jupiter, but you may need that when entering orbit.

# Plotting frame

Once Principia has computed a trajectory (maybe the prediction showing where your vessel will go based on its current position and velocity) it must display it.  It is important to understand that the same trajectory will look very different depending on the frame in which it's plotted.

Let's make the following thought experiment: you may have a parabolic TV antenna on your roof.  This antenna points towards a satellite in geostationary orbit.  You cannot see the satellite with the naked eye but if you could you would notice that it virtually doesn't move in the sky.  In truth it wiggles a bit around its average position, but it's as good as fixed.  That's why you can have your antenna installed once and for all and never need to touch it again.  The Sun, on the other hand, moves around you once every 24 hours, that's the day-night cycle.  The following picture illustrates this situation:

![Earth surface frame](http://i.imgur.com/Qxz3FiZ.png)

Now transport yourself to the surface of the Moon, and bring a telescope with you.  You can see your house and of course it rotates with the Earth every 24 hours.  The antenna is bolted to your house and also rotates every 24 hours.  The satellite is not bolted to anything but, by virtue of being geostationary, it also rotates every 24 hours.  In addition, both the Sun and Earth rotate around you (or rather, the Moon) once every month.  The bottom line is that the trajectory of satellite *seen from the Moon* is the result of the composition of its own circular motion around the Earth and of the circular motion of the Earth around the Moon.  It looks a bit like a crushed spring.  The following picture illustrates the new situation:

![Moon surface frame](http://i.imgur.com/O2eoZRx.png)

Which one of these is the real trajectory of the satellite?  Well, both.  They are both correct, but they are not both equally useful.  Imagine that you are a flight controller trying to adjust the satellite so that it remains exactly on top of your house.  The second representation is useless because a small drift that would cause you to completely lose TV reception would just manifest itself as a minor change in the shape of the crushed spring.  The first representation is what the flight controller wants to use: they can use precision thrusters to nudge the satellite a bit so that TV reception stays optimal in the desired region.

For the same reason, Principia offers a choice of *plotting frame* that you can use to display your trajectories.  Each of these plotting frame is most useful in specific circumstances.  You can choose between four kinds of plotting  frames using the `Plotting frame selection...` panel.

* Reference frame fixing the surface of a celestial

    You can use the panel to pick the celestial (a planet or one of its natural satellite) to use as the centre. This plotting frame is pinned to the centre of the celestial and rotates with its surface.  For instance, if you use such a frame centered on Jupiter, Jupiter will look like it doesn't move, and if you look at its surface the atmospheric features (e.g., the Great Red Spot) will appear immobile.  On the other hand the distant stars like Sirius, the Sun and the natural satellites of Jupiter will appear to move around.

    This frame is useful when taking off or landing: because the celestial looks immobile you can tune your approach and make sure that you don't come in too fast, don't enter the atmosphere or (horror!) don't crash on the surface.  It is also useful for synchronous orbits.

* Non-rotating reference frame fixing the centre of a celestial

    A frame similar to the previous one, except that it doesn't rotate with the celestial and stays fixed with respect to distant stars.  For instance, if you use such a frame centered on Jupiter, Jupiter will look like it doesn't move, and if you look at a distant star like Sirius it will also appear immobile.  On the other hand the Sun and the natural satellites of Jupiter will appear to move around.

    This frame is useful for any manœuvre that happens in low orbit (think International Space Station for instance).

    This frame is the one in which the stock KSP displays its conics (the trajectories are only conics in this particular kind of frame).

* Reference frame fixing the barycentre of two celestials and the line between them

    You can use the panel to pick the two celestials that determine the plotting frame.  This plotting frame is pinned on the barycentre (i.e., centre of mass) of the two celestials and the line between the celestials appears immobile.  Take the case of the Earth and the Moon.  Curiously the barycentre of the Earth-Moon system is located about 1700 km *inside* the Earth.  That point will appear immobile (not that it matters because you don't want your rocket to go there).  More interestingly, both the Earth and the Moon will stay in fixed directions, although their distance will vary a bit over time (due to the eccentricity of the Moon's orbit).  The distant stars, the Sun and all other celestials will appear to move around.

    In addition, the plane defined by the velocities of the two celestials is also pinned.  Generally this plane is what you might think of as the plane of the "orbit" of one celestial around the other, e.g., the plane of the Moon orbit in the above example.

    This frame is useful for planning and executing a trajectory that goes from one celestial to another.  Imagine that you try to play an Apollo mission: you can very accurately plan your trajectory from the Earth to the Moon and see its general shape: free return, gravity boost, etc.  This frame is also useful for reaching [Lagrangian points](https://en.wikipedia.org/wiki/Lagrangian_point) since these points appear immobile.

* Reference frame fixing the centre of a celestial and the line towards another celestial

    A frame similar to the previous one, except that instead of pinning the barycentre of two celestials, it pins the centre of one of the celestials.  In the case of the Earth and the Moon, the Earth will appear immobile and the Moon will stay in a fixed direction, although its distance will vary a bit over time (due to the eccentricity of its orbit).  The distant stars, the Sun and all other celestials will appear to move around.

    This frame is useful for when your vessel is close to a celestial, but the direction of another celestial is important: for instance, if you are in low Earth orbit but must orient your solar panels towards the Sun.

We'll probably add more kinds of plotting frames in future versions, to help with other kinds of manœuvres (e.g., rendezvous, etc.).

# Navball

In stock KSP your vessel is always within the *sphere of influence* of a single celestial.  The navball is defined by that celestial: the blue/brown color separation is parallel to the surface and the line from the N marker to the 180 marker is parallel to the North/South axis.

In Principia things get more complicated because (in the interesting missions at least) your vessel is not under the influence of a single celestial, but of several (or many) celestials.  This is for instance the case when navigating to a [Lagrangian points](https://en.wikipedia.org/wiki/Lagrangian_point) or when orbiting a complex system like Jupiter and its natural satellites.  Having the navball align on the celestial that currently has the largest influence is not very helpful because it would appear to flip semi-randomly depending on who pulls the stronger.

The Principia UI has a button `Fix navball in plotting frame` which you can use to align the navball on the elements that are invariant in the plotting frame that you selected.  The navball also changes color to give you a visual clue of its meaning.  The exact meaning of the navball in each plotting frame is as follows:

* Reference frame fixing the surface of a celestial

    The navball is similar to that of the stock KSP: the ground is brown and the sky is blue.  The separation between the colours is parallel to the surface of the celestial below your vessel.  The line from the N marker to the 180 marker is parallel to the North/South axis.

* Non-rotating reference frame fixing the centre of a celestial

    The navball is painted light and dark grey.  When using the unmodified stock game, the separation between the colors is parallel to the equator of Kerbin.  When using RealSolarSystem the separation between the colours is parallel to the equator of the Earth and the line from the ♈︎ marker to the 12 marker is parallel to the line joining the Spring and Autumn equinoxes.  In all cases, the navball is immobile with respect to distant stars.  (Directions on this navball are given as [right ascensions](https://en.wikipedia.org/wiki/Right_ascension) in hours.)

* Reference frame fixing the barycentre of two celestials and the line between them

    The navball is painted light and dark purple.  The separation between the colours is parallel to the orbital plane of the two celestials (remember that this plane is pinned) and the line from the 0 (I) marker to the 180 (II) marker is parallel to the line between the two celestials.

* Reference frame fixing the centre of a celestial and the line towards another celestial

    The navball is painted light and dark orange.  The separation between the colours is parallel to the orbital plane of the two celestials (remember that this plane is pinned) and the line from the filled circle (●) to the open circle (○) marker is parallel to the line from the pinned celestial to the other celestial.

# Flight planning

In stock KSP, flight planning is done using *manœuvre nodes*.  Manœuvre nodes are only a rough approximation of the real behaviour of your rocket because they assume that any change of velocity is instantaneous.  You may notice this when trying to effect a burn planned using a manœuvre node: you never quite get things right because the actual burn doesn't cause an instantaneous change of velocity.

This is good enough for fly-by-the-seat-of-your-pants, cowboy-style piloting, but it's entirely inappropriate for more complex missions where it's important to make the best use of your engines.  Thus, Principia includes an elaborate flight planning system which let you plan burns in a much more realistic manner.

While Principia makes it possible to plan complex trajectories, it's important to understand that there are two things that it *doesn't* do because, well, they are part of the fun of using realistic N-body physics:

* Principia doesn't help you optimise the flight plan, e.g. by minimising the Δv.  You've got to look for good flight plans yourself, using intuition and trial and errors.  You'll get better over time.  And yes, it's hard, that's what they hire PhDs to do this.

* Principia doesn't help you execute the flight plan.  Once you are done with the planning, you need to execute the manœuvres by hand by starting and cutting off the engines just at the right time.  You will not get this completely right, and in some cases a delay of a fraction of a second may cause significant changes to the trajectory down the road.  That's ok, don't try to overdo it, you can always schedule a minor correction to compensate for any inaccuracies.  In real life rocket scientists do just that as they learn more about the gravitational fields around unexplored celestials or because of intrinsic inaccuracies in the intensity of the burns.

The controls that let you plan your flight won't allow you to tune your Δv or your burn times extremely precisely (typically no finer than 1 mm/s).  That's intentional: even if you were able to construct a flight plan that way, you wouldn't be able to execute it.  If a small change of your Δv has a large effect on your future trajectory, you probably want to make smaller burns at different points along your mission.

## User interface

Now on to flight planning.  A flight plan is made of a number of *manœuvres*, which are segments where your engine is burning.  These segments are painted in solid orange red.  In between manœuvres, your vessel is *coasting*, i.e., is just moving under the influence of gravity. The coasting segments are painted in dashed baby blue.

To create a flight plan, click `Flight plan...` on the main Principia UI.  This opens the flight plan editor.  At the top you can specify the overall `Plan length`.  No burn can be beyond the end of the flight plan, so in order to add burns in the distant future you may have to increase the plan length.  The parameters `Maximal step count per segment` and `Tolerance` control the accuracy of the computation of each segment (burn or coasting) of your plan.  As explained above, a long flight plan with very accurate computations might make the game feel sluggish.

At the bottom of the flight plan editor you'll find buttons to `Delete last manœuvre` or `Add manœuvre`.  Adding a manœuvre opens up a subpanel where you can pick the desired Δv along three different axes, as well as the engines to activate for the burn.

The button `Manœuvring frame selection...` makes it possible to select the frame used for orienting the manœuvre.  Just like for plotting, notions like "prograde", "retrograde", "radial" depend on the frame in which you look at your vessel.  For instance, "prograde" is always tangent to the trajectory, but of course the shape of the trajectory changes from frame to frame.  By picking an appropriate frame for each manœuvre, you effectively define which way is "prograde" and in which direction the burn will move you.

Above the first manœuvre are displayed the total Δv and the count-down to the next manœuvre.  Also, if you tick `Show on navball`, the direction of the next manœuvre is indicated on the navball to help effecting the burn in the right direction.

By checking `Show on navball`, the next manœuvre is shown on the navball using KSP's manœuvre marker ![](http://wiki.kerbalspaceprogram.com/images/1/1f/Maneuver.svg).
Note that, unlike stock KSP, the Δv counter next to the navball _doesn't count down_ as you burn, and the manœuvre marker does not move.  This is because that countdown is only useful as guidance for burns that are modelled as instantaneous (as in stock KSP), but in Principia burns are applied continuously.  In order to execute a manœuvre you have to either take a look at the times in the flight plan editor (a countdown to ignition is provided, followed by a countdown to cut-off), or take a look at the shape of the prediction (which should change to become similar to the flight plan) and control your burn accordingly. Once the burn has been executed, you may want to revise your flight plan with trajectory correction manœuvres to account for errors, as in real life.

All the sliders in the flight plan editor are exponential sliders: the farther to the left (or right) you drag them the bigger effect they have on the quantity that you are tuning.  This makes it possible to enter large quantities (by dragging far to the left or right) while retaining the option to do fine tuning (by dragging very little away from the midpoint).

## Terminology

Veteran players of stock KSP will be familiar with the terms *prograde*, *retrograde*, *radial*, and *normal*.  This terminology makes sense for conics: prograde is a standard term, the next vector is the orthogonalisation of the inward radial vector (towards the planet), the third vector is normal to the orbital plane.

In Principia, all three components of Δv depend on the choice of frame.  In addition, orbits are arbitrary curves in 3D, which may curve away from the nearest body.  Thus, we use a different terminology, closer to mathematical conventions:

|Stock KSP|Principia|Symbol|
|---|---|---|
|Prograde|Tangent|![tangent](http://wiki.kerbalspaceprogram.com/images/thumb/a/a4/Prograde.svg/64px-Prograde.svg.png)|
|Retrograde|-Tangent|![-tangent](http://wiki.kerbalspaceprogram.com/images/thumb/0/02/Retrograde.svg/64px-Retrograde.svg.png)|
|Radial In|Normal|![normal](http://wiki.kerbalspaceprogram.com/images/thumb/8/81/Radial-in.svg/64px-Radial-in.svg.png)|
|Radial Out|-Normal|![-normal](http://wiki.kerbalspaceprogram.com/images/thumb/9/9a/Radial-out.svg/64px-Radial-out.svg.png)|
|Normal|Binormal|![binormal](http://wiki.kerbalspaceprogram.com/images/thumb/0/01/Normal.svg/64px-Normal.svg.png)|
|Anti-Normal|-Binormal|![-binormal](http://wiki.kerbalspaceprogram.com/images/thumb/1/19/Anti-normal.svg/64px-Anti-normal.svg.png)|

## Limitations

The trajectories of celestial bodies and other vessels are currently drawn by KSP, and thus appear to wobble (see the FAQ) and are not drawn in the current plotting frame; eventually principia will handle these trajectories too.

At the moment, flight planning suffers from the following limitations, which we'll try to address in future releases:

* The engines used for a burn are either the active engines, the RCS or an instant impulse.  In practice this means that you'll probably want to have an active engine when doing your planning.  Furthermore, solid-state engines cannot be activated without running them at full power, so it's not really possible to use them in planning.

* The mass used for computing the flight plan is the one when you actually edit the plan.  It you later do a vessel separation, it will change the mass and will effectively make the flight plan useless: you'll need to delete it and re-create it.

* There is no good support for rendezvous between vessels.  You may actually achieve a rendezvous with quite a bit of nudging and fudging and budging, but what is missing is really a plotting frame tied to one vessel that would give a proper view of the approach of the other vessel.