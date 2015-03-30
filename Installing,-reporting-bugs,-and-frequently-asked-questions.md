**NOTE:
The current version is not stable,
it can corrupt or otherwise destroy saves,
it has been known to crash, and predictions are horrendously slow.**

**Read *all* of the frequently asked questions (and their answers), or you will incur the wrath of the egg.**

##General
###IRC channel
The IRC channel is the the #principia channel on EsperNet.
The operators are in the following timezones:

Channel operators | Timezone | [Why is this still a thing](https://www.youtube.com/watch?v=br0NW9ufUUw)
---|---|---
ferram4, NathanKell | EST (UTC-05:00) | EDT (UTC-04:00)
Norgg, TechnicalFool | WET (UTC+00:00) | WEST (UTC+01:00)
diomedea, egg | CET (UTC+01:00) | CEST (UTC+02:00)


###Terminology
`<KSP directory>` is the directory such that the KSP executable is found in `<KSP directory>/KSP.exe`.

##Installing
Go to the IRC channel.
There is a build available for Windows users (32-bit version of KSP only), ask channel operators. 
For Linux users, ask @Norgg for a build or build instructions, bearing in mind that his build is much more failure-prone than the Windows one at the moment.
For Macintosh users, **armed_troop** is working on something.


###It's not starting! (`DLLNotFoundException`)
####Windows users
Well, first, make sure you put the DLL in the right place. The Principia DLL should be at `<KSP directory>\GameData\Principia\principia.dll`.
You need the [Visual C++ Redistributable Packages for Visual Studio 2013](http://www.microsoft.com/en-us/download/details.aspx?id=40784) (just press the big red `Download` button, download the x86 version, install it).
Make sure the permissions are set correctly on the folder containing KSP. If in doubt, set its permissions for that folder to `Full Control` for `Everyone` (ask the channel operators how to do that if you don't know).
####Linux users
You need libc++ when using @Norgg's code. For other issues, ask @Norgg.

##Bug reporting
So, you crashed, or something similarly unpleasant happened.
If you crashed or froze, be specific about the kind of failure you had: did you get an Unity dialog box? Did you get a Windows dialog box, or on *nix, did the process terminate by SIGABRT? Did you get a crash folder (a folder whose name is the date in your KSP install directory?
###Windows dialog box or SIGABRT
You probably encountered a glog `CHECK` failure. Go to `<KSP directory>\glog`, check that there is a recent FATAL file. Do not send the FATAL file only. Instead, take the most recent INFO file, upload it on gist or pastebin, and link it in the IRC channel. Ask the channel ops for further guidance.
###Have a crash folder
Send the contents of the `error.log` via gist or pastebin, as well as the contents of the `output_log.txt` (a copy may exist in the crash folder, otherwise if the game has not been restarted since the crash it is found at a location is documented on the KSP fora).
###Nothing, it just froze
It is likely that your save got too big and that you ran out of memory while the game was writing the persistence file. Your save is almost certainly corrupted, and will crash on load.

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
Principia does not currently interpret the orbital elements correctly, because this has not been a priority up to now, it will eventually. In the meantime, enjoy watching Vall grazing Jool before going for a stroll around the solar system.
###Why don't you parallelize?
It would hardly improve performance and it would be messy to implement. This is just the kind of algorithm that doesn't lend itself well to that.
####But...
Ok, let's look at numbers. The only thing that's performance-critical here is the computation of trajectory predictions (the pink lines). For those we're simulating the interactions of all massive bodies, and only one massless body. Computing all the forces costs 30 μs, and we *need* to synchronize outside of the force computation. Let's say we have a thread pool of 8 threads. We have to enqueue pointers to our data to our threads, and dequeue them, that's 16 locks. An uncontended lock costs about 50 ns, so that's 800 ns to start working, and 800 ns to synchronize when we're done. On a task that's 30 μs when single-threaded, we've spent 1.6 μs doing nothing. Whatever we might nibble away like that is not worth it.
####But...
Seriously, better choices of integrators and splittings or even saner handling of timestep will yield speedups to the tune of 100x or 1000x. The current force computation will probably be replaced by something completely different in the meantime, maybe at that point parallelism will make sense (or maybe it will still not make sense).
####But...
You're welcome to go ahead and implement parallelized force computations, and to benchmark that of course.
###How do I get rid of the annoying GUI?
You don't. Not in the current version. We'll try fixing that in Borel.
###I'm using a custom solar system mod, why isn't it stable / is it going to be stable once the initial conditions are properly interpreted?
Systems stabilized by resonance like the stock Jool system are broken by the incorrect interpetation of the initial conditions, see the section on Jool above.

That being said, even once the orbital elements are interpreted correctly, it all depends on whether your system was sanely designed. If it has 50 Duna-sized planets orbiting a Jool-sized body, many of these are going to interplanetary space today.
###Do you simulate collisions and tidal forces causing breakup between bodies?
... Now you see *this* would be very expensive to calculate.
###My save keeps getting bigger, eventually it crashes KSP
Your save remembers all of history, which means it keeps getting longer. We will add a setting in Borel to only keep some finite amount of history and forget what's before. In the meantime, you need to clear history from time to time by getting out of timewarp, pressing `Force Stop` / `Force Start` and hoping that you do not hit the Melonbug (#463).