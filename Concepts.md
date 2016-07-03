This page is a bit of a wall of text.  Why should you read it, when you have just downloaded Principia and want to go play with it and have fun?

Well, it turns out that N-body celestial mechanics is rather more complicated than the 2-body simplification offered by stock KSP.  In order to help planning and understanding elaborate missions that take advantage of N-body physics, Principia provides a number of tools that let you look at trajectories in different frames, use more advanced navballs, or plan complex flight paths.

So if you want to become a senior rocket pilot, to execute [gravity assists](https://en.wikipedia.org/wiki/Gravity_assist), [horseshoe orbits](https://en.wikipedia.org/wiki/Horseshoe_orbit), [Lissajous orbits](https://en.wikipedia.org/wiki/Lissajous_orbit), [heliosynchronous orbits](https://en.wikipedia.org/wiki/Sun-synchronous_orbit), [ballistic captures](https://en.wikipedia.org/wiki/Ballistic_capture) and [Oberth manœuvres](https://en.wikipedia.org/wiki/Oberth_effect), please read on.  Oh, and you'll be able to say these [six words you never say at NASA](https://xkcd.com/1244/).

# Trajectories

A trajectory is a line depicting the positions of a vessel.  In stock KSP, all trajectories are conics so there is not a lot of complexity to displaying or understanding them.  With N-body physics, though, trajectories may become more complex (and are certainly not conics in the interesting cases) so Principia comes with additional tools for plotting trajectories.

For each vessel, Principia may display three trajectories:
* The *history*, painted in acid green, shows where your vessel was in the past.
* The *prediction*, painted in fuchsia, shows where your vessel will go if you just sit on your hands: no engine burns, no separations, no nothing.
* The *flight plan*, painted in alternative segments of solid orange red and dashed baby blue, shows where your vessel will go if you execute the planned flight plan with no errors (more on flight planning later).

The main Principia UI let you control the length of the history (`Max history length`) and the settings of the prediction and flight plan (`Tolerance` and `Length` under `Prediction Settings`).  There are trade-offs in using these parameters: keeping a long history is aesthetically pleasing but it may also be confusing and may consume a lot of memory.  Computing a long prediction (or flight plan) with a low tolerance may end up consuming lots of CPU and make the game feel unresponsive.  Use your judgement: you probably don't need a 1 metre tolerance when planning a multi-month trip to Jupiter, but you may need that when entering orbit.

# Plotting frame

Once Principia has computed a trajectory (maybe the prediction showing where your vessel will go based on its current position and velocity) it must display it.  It is important to understand that the same trajectory will look very different depending on the frame in which it's plotted.

Let's make the following thought experiment: you may have a parabolic TV antenna on your roof.  This antenna points towards a satellite in geostationary orbit.  You cannot see the satellite with the naked eye but if you could you would notice that it virtually doesn't move in the sky.  In truth it wiggles a bit around its average position, but it's as good as fixed.  That's why you can have your antenna installed once and for all and never need to touch it again.

Now transport yourself to the surface of the Moon, and bring a telescope with you.  You can see your house and of course it rotates with the Earth every 24 hours.  The antenna is bolted to your house and also rotates every 24 hours.  The satellite is not bolted to anything but, by virtue of being geostationary, it also rotates every 24 hours, so its trajectory *seen from the Moon* is a circle around the Earth.  Actually, seen from the Moon the Earth slowly revolves with a period of about a month so the trajectory of the satellite looks more like a broken watch spring.

Which one of these is the real trajectory of the satellite?  Well, both.  They are both correct, but they are not both equally useful.  Imagine that you are a flight controller trying to adjust the satellite so that it remains exactly on top of your house.  The second representation is useless because a small drift that would cause you to completely lose TV reception would just manifest itself as a minor twist of the broken watch spring.  The first representation is what the flight controller wants to use: they can use precision thrusters to nudge the satellite a bit so that TV reception stays optimal in the desired region.

For the same reason, Principia offers a choice of *plotting frame* that you can use to display your trajectories.  Each of these plotting frame is most useful in specific circumstances.  You can choose between two kinds of plotting  frames using the `Plotting frame selection...` panel.

* Non-rotating reference frames centred on a celestial

    You can use the panel to pick the celestial (a planet or one of its natural satellite) to use as the centre.  This plotting frame is pinned to the centre of the celestial, moves with it and doesn't rotate with respect to distant stars.  For instance, if you use such a frame centered on Jupiter, Jupiter will look like it doesn't move, and if you look at a distant star like Sirius it will also appear immobile.  On the other hand the Sun and the natural satellites of Jupiter will appear to move around.

    This frame is mostly useful when entering or leaving an orbit around a celestial: because the celestial looks immobile you can tune your approach and make sure that you don't come in too fast, don't enter the atmosphere or (horror!) don't crash on the surface.  It is also the most useful for any manœuvre that happens in low orbit (think International Space Station for instance).

    This frame is the one in which the stock KSP displays its conics (the trajectories are only conics in this particular kind of frame).

* Reference frame fixing the barycentre of two celestials and the line between them

    Again, you can use the panel to pick the two celestials that determine the plotting frame.  This plotting frame is pinned on the barycentre (i.e., centre of mass) of the two celestials and the line between the celestials appears immobile.  Take the case of the Earth and the Moon.  Curiously the barycentre of the Earth-Moon system is located about 1700 km *inside* the Earth.  That point will appear immobile (not that it matters because you don't want your rocket to go there).  More interestingly, both the Earth and the Moon will stay in fixed directions, although their distance will vary a bit over time (due to the eccentricity of the Moon's orbit).  The distant stars, the Sun and all other celestials will appear to move around.

    In addition, the plane defined by the velocities of the two celestials is also pinned.  Generally this plane is what you might think of as the plane of the "orbit" of one celestial around the other, e.g., the plane of the Moon orbit in the above example.

    This frame is useful for planning and executing a trajectory that goes from one celestial to another.  Imagine that you try to play an Apollo mission: you can very accurately plan your trajectory from the Earth to the Moon and see its general shape: free return, gravity boost, etc.  This frame is also useful for reaching [Lagrangian points](https://en.wikipedia.org/wiki/Lagrangian_point) since these points appear immobile.

We'll probably add more kinds of plotting frames in future versions, to help with other kinds of manœuvres (e.g., landing, rendezvous, etc.).

# Navball

In stock KSP your vessel is always within the *sphere of influence* of a single celestial (roughly, the celestial closest to you).  The navball is defined by that celestial: the blue/brown color separation is parallel to the surface, and the 0/180 line is the North/South axis.

In Principia things get more complicated because (in the interesting missions at least) your vessel is not under the influence of a single celestial, but of several (or many) celestials.  This is for instance the case when navigating to a [Lagrangian points](https://en.wikipedia.org/wiki/Lagrangian_point) or when orbiting a complex system like Jupiter and its natural satellites.  Having the navball align on the celestial that currently has the largest influence is not very helpful because it would appear to flip semi-randomly depending on who pulls the stronger.

The Principia UI has a button `Fix navball in plotting frame` which you can use to align the navball on the elements that are invariant in the plotting frame that you selected.  The navball also changes color to give you a visual clue of its meaning.  The exact meaning of the navball in each plotting frame is as follows:

* Non-rotating reference frames centred on a celestial

    The navball is painted light and dark grey.  When using the unmodified stock game, the separation between the colors is parallel to the equator of Kerbin.  When using RealSolarSystem the separation between the colors is parallel to the equator of the Earth and the 0/180 line is parallel to the line joining the Spring and Autumn equinoxes.  In all cases, the navball is immobile with respect to distant stars.

* Reference frame fixing the barycentre of two celestials and the line between them

    The navball is painted light and dark purple.  The separation between the colors is parallel to the orbital plane of the two celestials (remember that this plane is pinned) and the 0/180 line is parallel to the line between the two celestials.

# Flight planning

<<TBW>>