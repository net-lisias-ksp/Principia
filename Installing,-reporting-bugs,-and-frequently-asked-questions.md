**Read *all* of the frequently asked questions (and their answers), or you will incur the wrath of the egg.**

In these FAQ, `<KSP directory>` is the directory such that the KSP executable is found in `<KSP directory>/KSP.exe`.

Note that Principia Cantor targets KSP 1.1.3. It will *not* work with later versions of KSP, including the current version.

# Installing
The binaries for Windows and Ubuntu x64 can be found [here](https://goo.gl/eZbr4e).

For Macintosh 64-bit users, we don't have a build at this point.  Contact us if you are interested in contributing one.

Don't reuse an existing save after installing Principia, create a new one (see below).

# Troubleshooting 
## It's not starting!
#### Windows users
32-bit platforms are no longer supported, you must be on a 64-bit platform.

Make sure you put the DLL in the right place. The Principia DLL should be at `<KSP directory>\GameData\Principia\x64\principia.dll`.

If you get the message "Dependencies, namely the Visual C++ Redistributable Packages for Visual Studio 2015 on x64, were not found", well, you need to install the [Visual C++ Redistributable Packages for Visual Studio 2015 on x64](http://download.microsoft.com/download/9/3/F/93FCF1E7-E6A4-478B-96E7-D4B285925B00/vc_redist.x64.exe).

Make sure the permissions are set correctly on the folder containing KSP. If in doubt, set its permissions for that folder to `Full Control` for `Everyone`.

#### Linux users
You need libc++ and libc++abi 3.5-2.

Also, your working directory *needs* to be `<KSP directory>`, otherwise `principia.so` will not be found.

Different distros seem to behave in different manners.  If you run into trouble, feel free to contribute a pull request.

## My vessels are all over the place
After installing Principia, you should start from a clean slate with all vessels on the ground.  If you try to reuse an existing save the vessels might be all over the place and behave strangely because the physics has effectively changed.

# Usage recommendations
## Timewarping
Timewarping with vessels is very slow above timewarp 100'000x. While we will try to improve that in a future version, when waiting for a specific date, it is best to reduce the number of vessels in game. In particular, asteroids being vessels as far as the game is concerned, removing them is a good idea if you are not interested in them (if you're using RealSolarSystem, these asteroids are fairly silly). In order to do that, simply delete the `<KSP directory>\GameData\Squad\Parts\Misc\PotatoRoid` folder.

When no vessels are present timewarp should be very smooth, even at 6'000'000x (in RealSolarSystem).

## RealSolarSystem users
Principia comes with initial state and gravity models configs for all celestial bodies in RealSolarSystem as of 2016-08-22. Moreover, initial states and gravity models are provided for the following celestials from pozine's *RSS Planets & Moons expanded*:
- Titania
- Oberon
- Ariel
- Umbriel
- Miranda
- Ceres
- Vesta (fresh data from the Dawn mission :smiley:).

*No other celestial bodies are supported*, so if you do install pozine's pack, make sure you remove all other bodies: if RealSolarSystem is installed and unsupported celestials are found, the game will crash. This means that you must remove them from the `RSS Planets & Moons.cfg` file, as well as remove their respective folders. You should probably remove their textures too, to reduce memory usage.

## Kopernicus users
If you are trying to build your own solar system, you might run into stability problems. This manifests itself by a pop-up message like "Apocalypse occurred at..." and an error in the logs.  To solve the problem, you might need to simulate your solar system in an external tool and find its regions of stability.

In particular, if you simply add bodies to the existing Kerbal system, even if they are themselves stable and do not perturb the Kerbal system significantly, issues will appear in the existing Jool system, whose stock version is unstable: when no modifications are made to the solar system we detect that and change the Jool system, but as soon as you have a custom system, you need to deal with Jool yourself too.

A possible solution to the Jool problem specifically is to increase the size of the orbits of the Joolian moons, while making Bop's orbit retrograde. [This Kopernicus configuration](https://gist.githubusercontent.com/eggrobin/31f6d0c246ecbe50423488f867fe7051/raw/55b814cd14b3c9fdd63119cee96dacb847e2e9ea/retrobop.cfg) will do this, like Principia does on a stock system. A word of warning: if your mod rescales the stock system, that config will not do the job; make a big (or small) retrobop yourself.

# Reporting bugs
So, you crashed, or something similarly unpleasant happened.

We would like to hear from this.  Please create a [github issue](https://github.com/mockingbirdnest/Principia/issues).  Be specific about the kind of failure you had: did you get an Unity dialog box? Did you get a Windows dialog box, or on *nix, did the process terminate by SIGABRT? What were you doing when the game crashed?  In addition, give us the specific crash files as explained below.  The more information the better, otherwise we might be unable to reproduce your problem.

## Windows dialog box or SIGABRT
You probably encountered a glog `CHECK` failure. Go to `<KSP directory>\glog`, check that there is a recent `FATAL` file.  Take the most recent `FATAL` and `INFO` files, upload them on gist.  Link the gist in your github issue.

## Have a crash folder, i.e., a folder whose name is the date in your KSP install directory
Put the contents of the `error.log` on gist as well as the contents of the `output_log.txt` (a copy may exist in the crash folder, otherwise if the game has not been restarted since the crash it is found at a location is documented on the KSP fora). In that case this may either be a stock KSP bug or a bug on our side, we will determine that by looking at the logs.  Link the gist in your github issue.

# Known bugs

The list of [issues](https://github.com/mockingbirdnest/Principia/issues) contains mostly ideas for future improvements.  We use the label [bug](https://github.com/mockingbirdnest/Principia/labels/bug) for issues that lead to incorrect behavior (not necessarily crashes, though).

# Interesting things to do

## Go to L<sub>4</sub> or L<sub>5</sub>?
[This Imgur album](http://imgur.com/a/H4jij#0) shows the trip there, starting right after getting out of the atmosphere.

## Go to L<sub>3</sub>?
Note that the orbit is *unstable*, which means that no matter how fine your adjustments are, eventually you'll get kicked out of your orbit. However with fine enough tuning you can stay a while, and of course if you come back from time to time to correct your trajectory you can stay there as long as your have fuel.
The first user to orbit an L<sub>3</sub> point was, as far as we can tell, **Yargnit**, his Twitch stream has sadly disappeared.

## Are trajectories around the Minmus-Kerbin L<sub>4</sub> or L<sub>5</sub> points stable?
It should really be Minmus-(Kerbin-Mun barycentre), but surprisingly, yes! As far as we know **Yargnit** is the one who first got there, his Twitch stream has sadly disappeared.

## Why can't I get a stable trajectory around the Ike-Duna L<sub>4</sub> or L<sub>5</sub> points?
Ike is too big (or duna is too small).

## Can I get into heliosynchronous orbits (RSS)?
Yes, see for instance https://goo.gl/photos/6AQCcNyskfsHG9xF7.

## Can I get into молния orbits (RSS)?
You can get into an eccentric orbit with inclination 63.4° even without Principia, but with Principia the inclination is crucial: with other inclinations the orbit will suffer from apsidal precession.

## Can I observe astronomical events (RSS)?
Eclipses can be observed (there is a toggle to disable the Sun's lens flare to help with that), however as mentioned in the "known bugs" section they lose a bit of accuracy after a decade or so. They're quite fun to watch.

For instance, this is the solar eclipse of 1952-02-25, as seen from Semnan:
![](http://i.imgur.com/DJy03zo.png)

## Can I do rendezvous?
Yes, but it's a bit tricky because we don't have (yet) a plotting frame that helps with this.  [This video](https://www.youtube.com/watch?v=uWTsh1KswDg) shows how it can be done (near the end).

# Getting Help
## IRC channel
The IRC channel is the #principia channel on EsperNet.
The operators are in the following timezones:

Channel operators | Timezone | [How is this still a thing](https://www.youtube.com/watch?v=br0NW9ufUUw)
---|---|---
**regex** | PST (UTC-08:00) | PDT (UTC-07:00)
**Felger**, **UmbralRaptor** | CST (UTC-06:00) | CDT (UTC-05:00)
**armed_troop**, **ferram4**, **NathanKell**, **sdrodge** | EST (UTC-05:00) | EDT (UTC-04:00)
**Norgg**, **TechnicalFool** | WET (UTC+00:00) | WEST (UTC+01:00)
**diomedea**, **egg**, **e_14159**, **Thomas**, **Sarbian** | CET (UTC+01:00) | CEST (UTC+02:00)
**darklight** | AEST (UTC+10:00) | it's not a thing there

# Random user comments
## I don't like your navballs!
The brown/blue navball can be reverted to its stock texture by removing the `<KSP directory>\Principia\assets\navball_compass.png` file.
The other two textures cannot be removed (this would cause a crash), but you can replace them by any png you like.
If you are simply dissatisfied with the colours, but like the general style, this repository contains *Mathematica* code to generate navballs, that you can tweak to your liking.

## Why don't you keep the planets on rails, it would improve performance?
While "rails" (Keplerian evolution) is not entirely unrelated to something that *could* improve performance, it would do the exact opposite with the current choice of integrator. One still needs to compute the positions of all bodies every time the force on a spacecraft is needed, so the Keplerian evolution would have to be computed instead of the forces on the bodies. Given that the computation of Keplerian evolution is costly (one needs to solve [Kepler's equation](http://en.wikipedia.org/wiki/Kepler%27s_equation), which requires a big lookup table or a handful of trigonometric function evaluations) the quadratic-to-linear change is completely dwarfed by this cost for 20 or so massive bodies.

It is true that some splittings of the Hamiltonian, e.g., those given by Wisdom and Holman (1991), Duncan, Levison and Lee (1998), Beust (2003), have Keplerian parts, and we will implement these, if only for comparison purposes to see which one we keep in the final implementation.

At this point we will have code for Kepler evolution and integrators that could be shoehorned into having Keplerian-only behaviour for massive bodies, but we will nonetheless not provide Keplerian-only behaviour, because in the end we're just not interested in that, we're here for the numerical integration problem.

## Orbits are wobbly
The orbits you see plotted in KSP with Principia (e.g. Jool around the Sun, or the Mun around Kerbin) are wobbly not because the actual orbits are wobbly, but because the wrong thing is plotted (specifically, the osculating orbital elements of the bodies are plotted, rather than the mean elements of subsystem barycentres). The orbit of the Mun is plotted *as if it were orbiting the centre of Kerbin*, rather than as an orbit around the barycentre of the Kerbin-Mun system. Similarly the orbit of *the centre of Jool* is plotted *as if it were orbiting the centre of the Sun*, rather than the orbit of the barycentre of the Jool system around the barycentre of the solar system.
Eventually we will replace KSP's faulty stock plots with our own and the orbits will cease to appear wobbly.

## Ok, they're not really wobbly, but I'd like the planets to follow their stock orbits
This would break physics. As an example, if planets were to do that, you would not get Lagrange points. It is an interesting exercise to compute the sum of the centrifugal and gravitational potentials for a body orbiting *the centre* of another (rather than their barycentre) in the reference frame that fixes both bodies and the orbital plane, and computing its gradient. It is easily seen that this gradient does not vanish in 5 points, but in only 3 instead.

## Why don't you parallelize?
It would hardly improve performance and it would be messy to implement. This is just the kind of algorithm that doesn't lend itself well to that.  Let's look at numbers. The only thing that's performance-critical here is the computation of trajectory predictions and flight plans. For those we're simulating the interactions of all massive bodies, and only one massless body. Computing all the forces costs 30 μs, and we *need* to synchronize outside of the force computation. Let's say we have a pool of 8 threads. We have to enqueue pointers to our data to our threads, and dequeue them, that's 16 locks. An uncontended lock costs about 50 ns, so that's 800 ns to start working, and 800 ns to synchronize when we're done. On a task that's 30 μs when single-threaded, we've spent 1.6 μs doing nothing. Whatever we might nibble away like that is not worth it.

There is a small opportunity for parallelization in issue [761](https://github.com/mockingbirdnest/Principia/issues/761).  Even so it's not clear if the benefits will overcome the cost of contention.

## I'm using a custom solar system mod, why isn't it stable?
It all depends on whether your system was sanely designed. If it has 50 Duna-sized planets orbiting a Jool-sized body, many of these are going to interplanetary space today.

## Couldn't you gain performance by ignoring the influence/oblateness of far-away bodies or by using a nonsymplectic integrator instead
We have thought about these options, and we will implement those that might yield improvements in due time in order to get as much accuracy as we can out of a given computational cost.

## What is oblateness / *J*<sub>2</sub> / *C*<sub>2</sub><sup>0</sup>?
The Earth is not a point mass nor a homogeneous sphere: it is an extended body. This has an effect on its gravitational field [that can be described by coefficients corresponding to spherical harmonics](https://en.wikipedia.org/wiki/Geopotential_model#The_deviations_of_Earth.27s_gravitational_field_from_that_of_a_homogeneous_sphere). Notably, the earth has an equatorial bulge, which corresponds to the *J*<sub>2</sub> coefficient---the *J*<sub>2</sub> coefficient can be referred to in terms of the related *C*<sub>2</sub><sup>0</sup> coefficient, for more details see [this NASA page](http://gracetellus.jpl.nasa.gov/data/J2/).
The *J*<sub>2</sub> coefficient strongly affects orbits around the Earth, causing apsidal and [nodal precession](https://en.wikipedia.org/wiki/Nodal_precession). For instance, [молния orbits minimize apsidal precessiond by having an inclination of 63.4 °](https://en.wikipedia.org/wiki/Molniya_orbit#Properties), and [heliosynchronous](https://en.wikipedia.org/wiki/Sun-synchronous_orbit) orbits [exploit nodal precession](https://en.wikipedia.org/wiki/Sun-synchronous_orbit#Technical_details) to stay aligned with the sun.

The initial config for RSS currently gives their proper *J*<sub>2</sub> coefficients to the Sun, the planets, the Moon, and Vesta. Other spherical harmonics are not yet implemented, but *C*<sub>2</sub><sup>2</sup> would definitely be relevant for tidally-locked bodies.

## What is the epoch of the RSS initial state, and what timescale is used?
The initial state config gives the solar system its state as given by the JPL HORIZONS service for 1950-01-01T00:00:00 *Temps Dynamique Barycentrique*. The state is however integrated before the game starts, so that the
game starts at 1951-01-01T00:00:00 *Temps Dynamique Barycentrique*.