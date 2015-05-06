**NOTE:
The current version is not stable,
it can corrupt or otherwise destroy saves,
it has been known to crash, and predictions are horrendously slow.**

**Read *all* of the frequently asked questions (and their answers), or you will incur the wrath of the egg.**

##General
###IRC channel
The IRC channel is the the #principia channel on EsperNet.
The operators are in the following timezones:

Channel operators | Timezone | [How is this still a thing](https://www.youtube.com/watch?v=br0NW9ufUUw)
---|---|---
**ferram4**, **NathanKell** | EST (UTC-05:00) | EDT (UTC-04:00)
**Norgg**, **TechnicalFool** | WET (UTC+00:00) | WEST (UTC+01:00)
**diomedea**, **egg** | CET (UTC+01:00) | CEST (UTC+02:00)


###Terminology
`<KSP directory>` is the directory such that the KSP executable is found in `<KSP directory>/KSP.exe`.

##Installing
Go to the IRC channel.
There is a build available for Windows users (32-bit version of KSP only), ask channel operators. 
For Linux users, ask **Norgg** for a build or build instructions, bearing in mind that his build is much more failure-prone than the Windows one at the moment.
For Macintosh users, **armed_troop** is working on something.


###It's not starting! (`DLLNotFoundException`)
####Windows users
Well, first, make sure you put the DLL in the right place. The Principia DLL should be at `<KSP directory>\GameData\Principia\principia.dll`.
You need the [Visual C++ Redistributable Packages for Visual Studio 2013](http://www.microsoft.com/en-us/download/details.aspx?id=40784) (just press the big red `Download` button, download the x86 version, install it).
Make sure the permissions are set correctly on the folder containing KSP. If in doubt, set its permissions for that folder to `Full Control` for `Everyone` (ask the channel operators how to do that if you don't know).
####Linux users
You need libc++ when using **Norgg**'s code. For other issues, ask **Norgg**.

##Bug reporting
So, you crashed, or something similarly unpleasant happened.
If you crashed or froze, be specific about the kind of failure you had: did you get an Unity dialog box? Did you get a Windows dialog box, or on *nix, did the process terminate by SIGABRT? Did you get a crash folder (a folder whose name is the date in your KSP install directory?
###Windows dialog box or SIGABRT
You probably encountered a glog `CHECK` failure. Go to `<KSP directory>\glog`, check that there is a recent FATAL file. Do not send the FATAL file only. Instead, take the most recent INFO file, upload it on gist or pastebin, and link it in the IRC channel. Ask the channel ops for further guidance.
###Have a crash folder
Send the contents of the `error.log` via gist or pastebin, as well as the contents of the `output_log.txt` (a copy may exist in the crash folder, otherwise if the game has not been restarted since the crash it is found at a location is documented on the KSP fora).
###Nothing, it just froze
It is likely that your save got too big and that you ran out of memory while the game was writing the persistence file. Your save is almost certainly corrupted, and will crash on load.

##Known bugs
* The autopilot sometimes targets the stock prograde/retrograde vectors rather than the displayed ones when
fix navball in plotting frame is selected.

##Frequently asked questions
###Why don't you keep the planets on rails...
####...it would improve performance
While "rails" (Keplerian evolution) is not entirely unrelated to something that *could* improve performance, it would do the exact opposite with the current choice of integrator. One still needs to compute the positions of all bodies every time the force on a spacecraft is needed, so the the Keplerian evolution would have to be computed instead of the forces on the bodies. Given that the computation of Keplerian evolution is costly (one needs to solve [Kepler's equation](http://en.wikipedia.org/wiki/Kepler%27s_equation), which requires a big lookup table or a handful of trigonometric function evaluations. The quadratic-to-linear change is completely dwarfed by this cost for 20 or so massive bodies.

It is true that some splittings of the Hamiltonian, e.g., those given by Wisdom and Holman (1991), Duncan, Levison and Lee (1998), Beust (2003), have Keplerian parts, and we will implement these, if only for comparison purposes to see which one we keep in the final implementation.

At this point we will have code for Kepler evolution and integrators that could be shoehorned into having Keplerian-only behaviour for massive bodies, but we will nonetheless not provide Keplerian-only behaviour, because in the end we're just not interested in that, we're here for the numerical integration problem.
####...orbits are wobbly
The orbits you see plotted in KSP with principia (e.g. Jool around the Sun, or the Mun around Kerbin) are wobbly not because the actual orbits are wobbly, but because the wrong thing is plotted. The orbit of the Mun is plotted *as if it were orbiting the centre of Kerbin*, rather than as an orbit around the barycentre of the Kerbin-Mun system. Similarly the orbit of *the centre of Jool* is plotted *as if it were orbiting the centre of the Sun*, rather than the orbit of the barycentre of the Jool system around the barycentre of the solar system.
Eventually we will replace KSP's faulty stock plots with our own and the orbits will cease to appear wobbly.
####...ok, they're not really wobbly, but I'd like the planets to follow their stock orbits
This would break physics. As an example, if planets were to do that, you would not get Lagrange points. It is an interesting exercise to compute the sum of the centrifugal and gravitational potentials for a body orbiting *the centre* of another (rather than their barycentre) in the reference frame that fixes both bodies and the orbital plane, and computing its gradient. It is easily seen that this gradient does not vanish in 5 points, but in only 3 instead.
####...it would make the Jool system stable
The Jool system should be stable if the orbital elements were interpreted correctly (as barycentric rather than as body-centric). Simulations which show it as unstable, such as Matt Roesle's, use a body-centric interpretation of the orbital elements. Specifically, Scott Manley (private communication) has simulated the Jool system for 1000 years (probably with the MERCURY integrator), and has found it to be stable. While this was before the inclusion of Pol, this is unlikely to matter.
Principia does not currently interpret the orbital elements correctly, because this has not been a priority up to now, it will eventually.

In the meantime, enjoy watching Vall grazing Jool before going for a stroll around the solar system.
###Why don't you parallelize?
It would hardly improve performance and it would be messy to implement. This is just the kind of algorithm that doesn't lend itself well to that.
####But...
Ok, let's look at numbers. The only thing that's performance-critical here is the computation of trajectory predictions (the pink lines). For those we're simulating the interactions of all massive bodies, and only one massless body. Computing all the forces costs 30 μs, and we *need* to synchronize outside of the force computation. Let's say we have a thread pool of 8 threads. We have to enqueue pointers to our data to our threads, and dequeue them, that's 16 locks. An uncontended lock costs about 50 ns, so that's 800 ns to start working, and 800 ns to synchronize when we're done. On a task that's 30 μs when single-threaded, we've spent 1.6 μs doing nothing. Whatever we might nibble away like that is not worth it.
####But...
Seriously, better choices of integrators and splittings or even saner handling of timestep will yield speedups to the tune of 100x or 1000x. The current force computation will probably be replaced by something completely different in the meantime, maybe at that point parallelism will make sense (or maybe it will still not make sense).
####But...
You're welcome to go ahead and implement parallelized force computations, and to benchmark that of course.
###I'm using a custom solar system mod, why isn't it stable / is it going to be stable once the initial conditions are properly interpreted?
Systems stabilized by resonance like the stock Jool system are broken by the incorrect interpetation of the initial conditions, see the section on Jool above.

That being said, even once the orbital elements are interpreted correctly, it all depends on whether your system was sanely designed. If it has 50 Duna-sized planets orbiting a Jool-sized body, many of these are going to interplanetary space today.
###Do you simulate collisions and tidal forces causing breakup between bodies?
... Now you see *this* would be very expensive to calculate.
###How do I predict my path?
The *pink* line is your predicted trajectory. You can predict for a longer duration by increasing the prediction length setting in the GUI. This will slow things down (sometimes to the point of a crash). If you want to make the prediction faster (or just avoid crashes), you can increase the prediction step. This will however make the prediction less accurate.
###How do I plan a burn?
For now, you cannot, you have to burn by the seat of your pants, or if you are somewhere where the 2-body approximation is good enough, you can use the stock manoeuvre nodes. Eventually we will add support for this.
###Do you simulate the gravity of player-created vessels and asteroids?
I'll let **ferram4** answer that one.
> Umm... Yes, actually!  It's only a few μm/s<sup>2</sup> from most vessels, but we do simulate it.  Really.  It actually doesn't cost any overhead at all!

On a more serious note, no. And we will not.
###Couldn't you gain performance by ignoring the influence/oblateness of far-away bodies / using a nonsymplectic integrator instead / caching the trajectories of the massive bodies?
We have thought about these options, and we will implement those that might yield improvements in due time in order to get as much accuracy as we can out of a given computational cost.
###The pink line (the prediction) is wagging wildly, why is that?
It is encountering a point where the problem gets too stiff. If you don't care about what happens this far in the future, reduce the prediction length, or if you do, reduce the timestep. You will also run into issues where KSP's imprecision when out of timewarp makes the prediction on stiff problems wag, no matter how small the prediction is. A collision a long time away will yield that sort of behaviour. Eventually we'll try being smart and set the length and step of the prediction appropriately, and marking where the prediction cannot be continued without being wildly unreliable.
###Should I use the patched conics predictions?
Unless you're in a low orbit, no. You'll waste a lot of fuel on corrections, they are inaccurate. Use Principia's predictions instead, using an appropriate reference frame (for a transfer, one that fixes the place you want to go to).

It is amusing to compare Principia's and KSP's predictions (in the same frame), see for instance [**Yargnit**'s stream](http://www.twitch.tv/yargnit/b/642525716) at 4:53.
###How do I get into an orbit around L<sub>4</sub> or L<sub>5</sub>?
[This Imgur album](http://imgur.com/a/H4jij#0) shows the trip there, starting right after getting out of the atmosphere.
###How do I get into an orbit around L<sub>3</sub>?
Note that the orbit is *unstable*, which means that no matter how fine your adjustments are, eventually you'll get kicked out of your orbit. However with fine enough tuning you can stay a while, and of course if you come back from time to time to correct your trajectory you can stay there as long as your have fuel.
The first user to orbit an L<sub>3</sub> point was, as far as I can tell, **Yargnit**, see [his stream](http://www.twitch.tv/yargnit/b/642525716) at 5:40 to see how he did that.
###Are trajectories around the Minmus-Kerbin L<sub>4</sub> or L<sub>5</sub> points stable?
It should really be Minmus-(Kerbin-Mun barycentre), but surprisingly, yes! As far as I know **Yargnit** is the one who first got there, see [his stream](http://www.twitch.tv/yargnit/b/642525716) at 5:24.
###Why can't I get a stable trajectory around the Ike-Duna L<sub>4</sub> or L<sub>5</sub> points?
Ike is too big (or duna is too small).
###Why don't trajectory plots break at SOI boundaries like in stock?
SOI boundaries do not matter to us. Instead you choose an appropriate reference frame yourself, with even the option of rotating frames (more options will be added). Eventually we want to put the navball and camera in the same reference frame as the plots, and we definitely want a smoother way of selecting relevant reference frames. For now, you have to deal with the big ugly GUI.