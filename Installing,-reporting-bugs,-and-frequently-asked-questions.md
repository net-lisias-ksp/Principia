**NOTE:
The current version is not stable, it has been known to crash, and timewarp with vessels above 100'000x is horrendously slow.**

**Read *all* of the frequently asked questions (and their answers), or you will incur the wrath of the egg.**

##General
###IRC channel
The IRC channel is the #principia channel on EsperNet.
The operators are in the following timezones:

Channel operators | Timezone | [How is this still a thing](https://www.youtube.com/watch?v=br0NW9ufUUw)
---|---|---
**regex** | PST (UTC-08:00) | PDT (UTC-07:00)
**Felger** | CST (UTC-06:00) | CDT (UTC-05:00)
**armed_troop**, **ferram4**, **NathanKell**, **sdrodge** | EST (UTC-05:00) | EDT (UTC-04:00)
**Norgg**, **TechnicalFool** | WET (UTC+00:00) | WEST (UTC+01:00)
**diomedea**, **egg**, **e_14159**, **Thomas**, **Sarbian** | CET (UTC+01:00) | CEST (UTC+02:00)
**darklight** | AEST (UTC+10:00) | it's not a thing there


###Terminology
`<KSP directory>` is the directory such that the KSP executable is found in `<KSP directory>/KSP.exe`.

##Installing
Go to the IRC channel.
There is a build available for Windows users (64-bit version of KSP only) or Linux 64-bit users, ask the bot as indicated by the channel topic.
For Macintosh 64-bit users, we're working on a build.

###General recommendations
Timewarping with vessels is very slow above timewarp 100'000x. While we will try to improve that in a future version, when waiting for a specific date, it is best to reduce the number of vessels in game. In particular, asteroids being vessels as far as the game is concerned, removing them is a good idea if you are not interested in them (in particular, if you're using Real Solar Systems, these asteroids are fairly silly). In order to do that, simply delete the `<KSP directory>\GameData\Squad\Parts\Misc\PotatoRoid` folder.
When no vessels are present timewarp should be very smooth, even at 6'000'000x (in Real Solar System).

###Recommendations for Real Solar System users
Principia comes with initial state and gravity models configs for all bodies in Real Solar System as of 2015-08-16. Moreover, initial states and gravity models are provided for the following bodies from pozine's *RSS Planets & Moons expanded*:
- Charon
- Titania
- Oberon
- Ariel
- Umbriel
- Miranda
- Ceres
- Vesta (fresh data from the Dawn mission :smiley:).

We very strongly recommend that you use Charon, since otherwise Pluto keeps its motion around Charon without having Charon to pull it back, and ends up in a strange orbit.

*No other bodies are supported*, so if you do install pozine's pack, make sure you remove all other bodies: if Real Solar System is installed and unsupported planets are found, the game will crash. This means that you must remove them from the `RSS Planets & Moons.cfg` file, as well as remove their respective folders. You should probably remove their textures too, to reduce memory usage.

###It's not starting! ("The Principia DLL failed to load.")
####Windows users
Well, first, make sure you put the DLL in the right place. The Principia DLL should be at `<KSP directory>\GameData\Principia\x64\principia.dll`.
You need to install the [Visual C++ Redistributable Packages for Visual Studio 2015 on x64](http://download.microsoft.com/download/9/3/F/93FCF1E7-E6A4-478B-96E7-D4B285925B00/vc_redist.x64.exe).
Make sure the permissions are set correctly on the folder containing KSP. If in doubt, set its permissions for that folder to `Full Control` for `Everyone` (ask the channel operators how to do that if you don't know).
####Linux users
You need libc++ when using **Norgg**'s code. For other issues, ask **Norgg**.

Also, your working directory *needs* to be `<KSP directory>`, otherwise `principia.so` will not be found.

##Bug reporting
So, you crashed, or something similarly unpleasant happened.
If you crashed or froze, be specific about the kind of failure you had: did you get an Unity dialog box? Did you get a Windows dialog box, or on *nix, did the process terminate by SIGABRT? Did you get a crash folder (a folder whose name is the date in your KSP install directory?
###Windows dialog box or SIGABRT
You probably encountered a glog `CHECK` failure. Go to `<KSP directory>\glog`, check that there is a recent FATAL file. Do not send the FATAL file only. Instead, take the most recent INFO file, upload it on gist, and link it in the IRC channel. Ask the channel ops for further guidance.
###Have a crash folder
Send the contents of the `error.log` via gist or pastebin, as well as the contents of the `output_log.txt` (a copy may exist in the crash folder, otherwise if the game has not been restarted since the crash it is found at a location is documented on the KSP fora). In that case this may either be a stock KSP bug or a bug on our side, we will determine that by looking at the logs.

##Known bugs
* The autopilot sometimes targets the stock prograde/retrograde vectors rather than the displayed ones when
fix navball in plotting frame is selected.
* When using Real Solar System, while solar eclipses in the early fifties are accurate within measurement error, they are off by 10 min in 1961. The cause of this inaccuracy is unknown, we are investigating this.

##Frequently asked questions
###What's up with the nav ball?
If the *Fix nav ball in plotting frame* setting (under *Reference Frame*) is selected, the nav ball will be fixed in the frame, and oriented as follows:
- if the frame is nonrotating, the reference plane of the navball is Kerbin's equator (or Earth's). The navball therefore indicates right ascension (in hours) and declination (in degrees). Another way of seeing that is that the navball is fixed with respect to the distant stars. The northern celestial hemisphere is grey, the southern one is black.![](https://raw.githubusercontent.com/mockingbirdnest/Principia/master/ksp_plugin_adapter/assets/navball_inertial.png)
- if the frame is the barycentric rotating frame of a 2-body system, the reference plane of the navball is the orbital plane. The reference direction is the line between the two bodies.![](https://raw.githubusercontent.com/mockingbirdnest/Principia/master/ksp_plugin_adapter/assets/navball_barycentric.png)

If the *Fix nav ball in plotting frame* setting is *not* selected, the nav ball has the usual behaviour. For visual consistency with our custom navballs, we provide the following nav ball by default.![](https://raw.githubusercontent.com/mockingbirdnest/Principia/master/ksp_plugin_adapter/assets/navball_compass.png)

####I don't like your navballs!
The brown/blue navball can be reverted to its stock texture by removing the `<KSP directory>\Principia\assets\navball_compass.png` file.
The other two textures cannot be removed (this would cause a crash), but you can replace them by any png you like.
If you are simply dissatisfied with the colours, but like the general style, this repository contains *Mathematica* code to generate nav balls, that you can tweak to your liking. For instance, **diomedea** uses a dark green/dark blue nav ball with instead of the light blue/brown one.

###Why don't you keep the planets on rails...
####...it would improve performance
While "rails" (Keplerian evolution) is not entirely unrelated to something that *could* improve performance, it would do the exact opposite with the current choice of integrator. One still needs to compute the positions of all bodies every time the force on a spacecraft is needed, so the Keplerian evolution would have to be computed instead of the forces on the bodies. Given that the computation of Keplerian evolution is costly (one needs to solve [Kepler's equation](http://en.wikipedia.org/wiki/Kepler%27s_equation), which requires a big lookup table or a handful of trigonometric function evaluations. The quadratic-to-linear change is completely dwarfed by this cost for 20 or so massive bodies.

It is true that some splittings of the Hamiltonian, e.g., those given by Wisdom and Holman (1991), Duncan, Levison and Lee (1998), Beust (2003), have Keplerian parts, and we will implement these, if only for comparison purposes to see which one we keep in the final implementation.

At this point we will have code for Kepler evolution and integrators that could be shoehorned into having Keplerian-only behaviour for massive bodies, but we will nonetheless not provide Keplerian-only behaviour, because in the end we're just not interested in that, we're here for the numerical integration problem.
####...orbits are wobbly
The orbits you see plotted in KSP with principia (e.g. Jool around the Sun, or the Mun around Kerbin) are wobbly not because the actual orbits are wobbly, but because the wrong thing is plotted (specifically, the osculating orbital elements of the bodies are plotted, rather than the mean elements of subsystem barycentres). The orbit of the Mun is plotted *as if it were orbiting the centre of Kerbin*, rather than as an orbit around the barycentre of the Kerbin-Mun system. Similarly the orbit of *the centre of Jool* is plotted *as if it were orbiting the centre of the Sun*, rather than the orbit of the barycentre of the Jool system around the barycentre of the solar system.
Eventually we will replace KSP's faulty stock plots with our own and the orbits will cease to appear wobbly.
####...ok, they're not really wobbly, but I'd like the planets to follow their stock orbits
This would break physics. As an example, if planets were to do that, you would not get Lagrange points. It is an interesting exercise to compute the sum of the centrifugal and gravitational potentials for a body orbiting *the centre* of another (rather than their barycentre) in the reference frame that fixes both bodies and the orbital plane, and computing its gradient. It is easily seen that this gradient does not vanish in 5 points, but in only 3 instead.
###Why don't you parallelize?
It would hardly improve performance and it would be messy to implement. This is just the kind of algorithm that doesn't lend itself well to that.
####But...
Ok, let's look at numbers. The only thing that's performance-critical here is the computation of trajectory predictions (the pink lines). For those we're simulating the interactions of all massive bodies, and only one massless body. Computing all the forces costs 30 μs, and we *need* to synchronize outside of the force computation. Let's say we have a thread pool of 8 threads. We have to enqueue pointers to our data to our threads, and dequeue them, that's 16 locks. An uncontended lock costs about 50 ns, so that's 800 ns to start working, and 800 ns to synchronize when we're done. On a task that's 30 μs when single-threaded, we've spent 1.6 μs doing nothing. Whatever we might nibble away like that is not worth it.
####But...
Seriously, better choices of integrators and splittings or even saner handling of timestep will yield speedups to the tune of 100x or 1000x. The current force computation will probably be replaced by something completely different in the meantime, maybe at that point parallelism will make sense (or maybe it will still not make sense).
####But...
You're welcome to go ahead and implement parallelized force computations, and to benchmark that of course.
###I'm using a custom solar system mod, why isn't it stable?
It all depends on whether your system was sanely designed. If it has 50 Duna-sized planets orbiting a Jool-sized body, many of these are going to interplanetary space today.
###Do you simulate collisions and tidal forces causing breakup between bodies?
... Now you see *this* would be very expensive to calculate.
###How do I predict my path?
The *pink* line is your predicted trajectory. You can predict for a longer duration by increasing the prediction length setting in the GUI. This will slow things down (sometimes to the point of a crash). If you want to make the prediction faster (or just avoid crashes), you can increase the tolerance. This will however make the prediction less accurate.
###Do you simulate the gravity of player-created vessels and asteroids?
I'll let **ferram4** answer that one.
> Umm... Yes, actually!  It's only a few μm/s<sup>2</sup> from most vessels, but we do simulate it.  Really.  It actually doesn't cost any overhead at all!

On a more serious note, no. And we will not.
###Couldn't you gain performance by ignoring the influence/oblateness of far-away bodies / using a nonsymplectic integrator instead
We have thought about these options, and we will implement those that might yield improvements in due time in order to get as much accuracy as we can out of a given computational cost.
###Why don't trajectory plots break at SOI boundaries like in stock?
SOI boundaries do not matter to us. Instead you choose an appropriate reference frame yourself, with even the option of rotating frames (more options will be added). Eventually we want to put the navball and camera in the same reference frame as the plots, and we definitely want a smoother way of selecting relevant reference frames. For now, you have to deal with the big ugly GUI.
###What is oblateness / *J*<sub>2</sub> / *C*<sub>2</sub><sup>0</sup>?
The Earth is not a point mass nor a homogeneous sphere: it is an extended body. This has an effect on its gravitational field [that can be described by coefficients corresponding to spherical harmonics](https://en.wikipedia.org/wiki/Geopotential_model#The_deviations_of_Earth.27s_gravitational_field_from_that_of_a_homogeneous_sphere). Notably, the earth has an equatorial bulge, which corresponds to the *J*<sub>2</sub> coefficient---the *J*<sub>2</sub> coefficient can be referred to in terms of the related *C*<sub>2</sub><sup>0</sup> coefficient, for more details see [this NASA page](http://gracetellus.jpl.nasa.gov/data/J2/).
The *J*<sub>2</sub> coefficient strongly affects orbits around the Earth, causing apsidal and [nodal precession](https://en.wikipedia.org/wiki/Nodal_precession). For instance, [молния orbits minimize apsidal precessiond by having an inclination of 63.4 °](https://en.wikipedia.org/wiki/Molniya_orbit#Properties), and [heliosynchronous](https://en.wikipedia.org/wiki/Sun-synchronous_orbit) orbits [exploit nodal precession](https://en.wikipedia.org/wiki/Sun-synchronous_orbit#Technical_details) to stay aligned with the sun.

The initial config for RSS currently gives their proper *J*<sub>2</sub> coefficients to the Sun, the planets, the Moon, and Vesta. Other spherical harmonics are not yet implemented, but *C*<sub>2</sub><sup>2</sup> would definitely be relevant for tidally-locked bodies.
###What is the epoch of the RSS initial state, and what timescale is used?
The initial state config gives the solar system its state as given by the JPL HORIZONS service for 1950-01-01T00:00:00 *Temps Dynamique Barycentrique*. The state is however integrated before the game starts, so that the
game starts at 1951-01-01T00:00:00 *Temps Dynamique Barycentrique*.

The timescale used is *Temps Dynamique Barycentrique*, in particular if you use Kerbal Alarm Clock, the dates given will be in *Temps Dynamique Barycentrique*.

When using civil times based on UTC (after 1972), note that *Temps Dynamique Barycentrique* is within 2 ms
of *Temps Terrestre*, that *Temps Atomique International* is related to the latter by TT = TAI + 32.184 s,
and use [tables of TAI - UTC](http://stjarnhimlen.se/comp/time.html#deltat72p).

When using civil times based on the rotation of the Earth before 1972, note that for these purposes TDB, TT and Ephemeris Time are equivalent, and use [tables of ET - UT1](http://stjarnhimlen.se/comp/time.html#deltat16201972).

###Can I do [interesting thing]?
####Go to L<sub>4</sub> or L<sub>5</sub>?
[This Imgur album](http://imgur.com/a/H4jij#0) shows the trip there, starting right after getting out of the atmosphere.
####Go to L<sub>3</sub>?
Note that the orbit is *unstable*, which means that no matter how fine your adjustments are, eventually you'll get kicked out of your orbit. However with fine enough tuning you can stay a while, and of course if you come back from time to time to correct your trajectory you can stay there as long as your have fuel.
The first user to orbit an L<sub>3</sub> point was, as far as I can tell, **Yargnit**, his Twitch stream has sadly disappeared.
####Are trajectories around the Minmus-Kerbin L<sub>4</sub> or L<sub>5</sub> points stable?
It should really be Minmus-(Kerbin-Mun barycentre), but surprisingly, yes! As far as I know **Yargnit** is the one who first got there, his Twitch stream has sadly disappeared.
####Why can't I get a stable trajectory around the Ike-Duna L<sub>4</sub> or L<sub>5</sub> points?
Ike is too big (or duna is too small).
####Can I get into heliosynchronous orbits (RSS)?
Yes, see for instance https://goo.gl/photos/6AQCcNyskfsHG9xF7.
####Can I get into молния orbits (RSS)?
You can get into an eccentric orbit with inclination 63.4 ° even without principia, but with principia the inclination is crucial: with other inclinations the orbit will suffer from apsidal precession.
####Can I observe astronomical events (RSS)?
Eclipses can be observed (there is a toggle to disable the Sun's lens flare to help with that), however as mentioned in the "known bugs" section they lose a bit of accuracy after a decade or so. They're quite fun to watch.

For instance, this is the solar eclipse of 1952-02-25, as seen from Semnan:
![](http://i.imgur.com/DJy03zo.png)