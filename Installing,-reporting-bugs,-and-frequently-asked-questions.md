**Read *all* of the frequently asked questions (and their answers), or you will incur the wrath of the egg.**

In these FAQ, `<KSP directory>` is the directory such that the KSP executable is found in `<KSP directory>/KSP.exe`.

Note that Principia currently targets KSP 1.5.1, 1.6.1, 1.7.x, and 1.8.1.

# Installing Principia
The binaries for Windows, macOS, and Ubuntu x64 can be found in the [README](https://github.com/mockingbirdnest/Principia/blob/master/README.md).  Unzip the archive and copy the `Principia` folder into the `GameData` folder of your installation of KSP.

Don't reuse an existing save after installing Principia for the first time, create a new one ([see below](#existing_save)).  When upgrading to a new version of Principia it's fine to reuse an existing save as we maintain backward compatibility.

# Installing “Trappist-1 for Principia”
“Trappist-1 for Principia” is a mini-mod that simulates the [TRAPPIST-1](https://en.wikipedia.org/wiki/TRAPPIST-1) extrasolar planetary system. TRAPPIST-1 is composed of seven tightly coupled Earth-like planets orbiting close to an ultracool dwarf star where *n*-body gravitation plays an important role, so it's an interesting application of Principia.

The simulation uses the most recently published observational data (from [K2](https://en.wikipedia.org/wiki/Kepler_(spacecraft)#Second_Light_(K2)) and [Spitzer](https://en.wikipedia.org/wiki/Spitzer_Space_Telescope)) and is based on a [transit-timing variation](https://en.wikipedia.org/wiki/Transit-timing_variation) optimization.  It accurately models the real-life behavior of the planetary system: the transits are accurate to within a minute.

Our mini-mod comes as a patch on top of [@GregroxMun](https://github.com/GregroxMun)'s SLIPPIST-1 mod.  To install, do the following:
* Install [SLIPPIST-1](https://forum.kerbalspaceprogram.com/index.php?/topic/157020-143-seven-worlds-around-slippist-1-v05-update-june-7th-2018/).
* Install [Kopernicus](https://forum.kerbalspaceprogram.com/index.php?/topic/181547-181-1-kopernicus-kittopiatech/).
* Optionally, install [RSSTimeFormatter](https://github.com/KSP-RO/RSSTimeFormatter/releases) to display the correct date for the state of the TRAPPIST-1 system.
* Download the [`trappist-1 for principia fáry.zip`](https://bit.ly/2ZHf3Tt) file, unzip it, and drop the `Trappist-1 for Principia` folder in the `GameData` folder of your installation of KSP.
* Start KSP and enjoy the view: ![](https://i.imgur.com/aynfI5j.png)

# Troubleshooting 
## It's not starting!
32-bit platforms are no longer supported, you must be on a 64-bit platform.

Make sure you put the DLL in the right place. The Principia DLL should be at `<KSP directory>\GameData\Principia\{Linux64,MacOS64,x64}\principia.dll`.

#### Windows users
If you get the message "Dependencies, namely the Microsoft Visual C++ 2015-2019 Redistributable, were not found", well, you need to install the [Microsoft Visual C++ 2015-2019 Redistributable](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads).

#### Mac users
You need Sierra or later.

#### Linux users
You need libc++ and libc++abi 8.

Also, your working directory *needs* to be `<KSP directory>`, otherwise `principia.so` will not be found.

Different distros seem to behave in different manners.  If you run into trouble, feel free to contribute a pull request.

## <a name="existing_save"></a>My vessels are all over the place
After installing Principia, you should start from a clean slate with all vessels on the ground.  If you try to reuse an existing save, you may or may not like the result. We will restart integration of the solar system since the origin (it will take a little while the first time you start the game with Principia) and we'll move the celestials to the positions that we have computed. As an example, the Moon is likely to move quite a bit, so if you were flying towards the Moon you may find yourself going towards the-moon-is-not-here-anymore.

# Usage recommendations
## Timewarping
Timewarping with vessels is smooth at timewarp 100 000× (the maximum warp supported by the stock KSP) but janky at timewarp 1 000 000× (permitted by some mods). This can be alleviated by reducing the number of vessels in the game. In particular, asteroids being vessels as far as the game is concerned, removing them is a good idea if you are not interested in them (if you're using RealSolarSystem, these asteroids are fairly silly). In order to do that, simply delete the `<KSP directory>\GameData\Squad\Parts\Misc\PotatoRoid` folder.

When no vessels are present timewarp should be very smooth, even at 6 000 000× (in RealSolarSystem).

## Compatibility with other mods
Any mod that tries to move vessels or otherwise change orbits either (1) without using engines or (2) during time warp, is incompatible with Principia.

Many mods do that, and they are as a consequence all incompatible with Principia.  We document some high-profile incompatibilities below, but we cannot really know about all of them.  Mod users are advised to think about possible incompatibilities when using multiple mods.

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

## SigmaBinary users

SigmaBinary and Principia are mutually incompatible.  Install one or the other.  In the [words of the author of SigmaBinary](
https://forum.kerbalspaceprogram.com/index.php?/topic/162200-wip131-145-principia%E2%80%94version-desargues-released-2018-08-11%E2%80%94n-body-and-extended-body-gravitation-axial-tilt/&do=findComment&comment=3289320):

> My mod is a hack to allow fake binaries in KSP physics, Principia "hacks" KSP to use real physics.
>
> I would say, Principia should be able to provide binaries without the need of extra plugins, it's probably just a matter of setting the initial conditions correctly I would assume.

## Orbital Decay users

Orbital Decay and Principia are mutually incompatible.  Install one or the other.  Orbital Decay changes the orbits of vessels in time warp and Principia keeps an authoritative copy of the state of every vessels: the two mods would fight each other and Principia would win.

## PersistentRotation users

PersistentRotation and Principia are mutually incompatible.  Install one or the other.  PersistentRotation is not physically correct, and the two mods would fight each other.

# Reporting bugs
So, you crashed, or something similarly unpleasant happened.

We would like to hear from this.  Please create a [github issue](https://github.com/mockingbirdnest/Principia/issues).  Be specific about the kind of failure you had: did you get an Unity dialog box? Did you get a Windows dialog box, or on *nix, did the process terminate by SIGABRT? What were you doing when the game crashed?  In addition, give us the specific crash files as explained below.  The more information the better, otherwise we might be unable to reproduce your problem.

## Windows dialog box or SIGABRT
You probably encountered a glog `CHECK` failure. Go to `<KSP directory>\glog`, check that there is a recent `FATAL` file.  Take the most recent `FATAL` and `INFO` files, upload them on gist.  Link the gist in your github issue.

## Have a crash folder
That's a folder whose name is the date in the `%USERPROFILE%\AppData\LocalLow\Squad\Kerbal Space Program\Crashes` or `%USERPROFILE%\AppData\Local\Temp\Squad\Kerbal Space Program\Crashes` directories.
Put the contents of the `error.log` on gist as well as the contents of the `output_log.txt` (a copy may exist in the crash folder, otherwise if the game has not been restarted since the crash it is found at a location is documented on the KSP fora). In that case this may either be a stock KSP bug or a bug on our side, we will determine that by looking at the logs.  Link the gist in your github issue.

## Journaling
In order to help us analyse the most complicated bugs, Principia includes a journaling mechanism that records all the interactions between KSP and Principia.  We will replay these interactions to understand what happened, e.g., in case of a crash.  If we ask you for a journal, please follow the following steps:
1. open `Logging Settings` in the main Principia window;
1. select `Record journal (starts on load)` at the bottom left;
1. do a scene change to make sure that journaling is enabled (you should see `Journaling is ON` at the bottom right of the Principia window);
1. try to reproduce the problem that you ran into (note that journaling makes the game slow as it writes lots of data to disk);
1. if you are successful in reproducing the problem, send us the relevant `*.log` files and the `JOURNAL.*` file found in your `glog\Principia` directory.

Don't forget to deselect `Record journal (starts on load)` or your game will be slow forever.  The journal does not contain any personally identifiable information other than the name of your machine, and the names and configuration of your vessels and celestials.

# Known bugs

The list of [issues](https://github.com/mockingbirdnest/Principia/issues) contains mostly ideas for future improvements.  We use the label [bug](https://github.com/mockingbirdnest/Principia/labels/bug) for issues that lead to incorrect behavior (not necessarily crashes, though).

## The case of `BadImageFormatException`

The following traces are expected and harmless; seeing them in the KSP logs should not be cause for alarm:
```
Load(Assembly): Principia/x64/<some assembly>
AssemblyLoader: Loading assembly at <ksp path>\GameData\Principia\x64\<some assembly>.dll
Failed to load assembly <ksp path>\GameData\Principia\x64\<some assembly>.dll:
System.BadImageFormatException: Format of the executable (.exe) or library (.dll) is invalid.
<stack trace>
```

As outlined in the [technical overview](https://github.com/mockingbirdnest/Principia/wiki/Technical-Overview), all the work is done in native DLLs (compiled from C++) called from a comparatively lightweight C♯ adapter that handles UI and interactions with the game itself.

These native DLLs are not loaded by KSP directly, and cannot be, but KSP tries to load any DLL it sees, resulting in these exceptions.

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
Yes; we have a plotting frame for that, target-centred local-vertical, local-horizontal, which is a fan favourite. See [this guide](https://github.com/mockingbirdnest/Principia/wiki/A-guide-to-performing-low-orbit-rendezvous).

# Getting Help
## IRC channel
The IRC channel is the #principia channel on EsperNet.
The operators are in the following timezones:

Channel operators | Timezone | [How is this still a thing](https://www.youtube.com/watch?v=br0NW9ufUUw)
---|---|---
**NathanKell**, **regex** | PST (UTC-08:00) | PDT (UTC-07:00)
**Felger**, **UmbralRaptor** | CST (UTC-06:00) | CDT (UTC-05:00)
**armed_troop**, **ferram4**, **sdrodge** | EST (UTC-05:00) | EDT (UTC-04:00)
**Norgg**, **TechnicalFool** | WET (UTC+00:00) | WEST (UTC+01:00)
**diomedea**, **egg**, **e_14159**, **Thomas**, **Sarbian** | CET (UTC+01:00) | CEST (UTC+02:00)
**darklight** | AEST (UTC+10:00) | it's not a thing there

# Random user comments
## I don't like your navballs!
The `<KSP directory>\Principia\assets\navball_compass.png` file can be removed and it will revert to the stock navball.
The other textures cannot be removed (this would cause a crash), but you can replace them by any `png` you like, including the stock navball which can be found, e.g., in the [forums](http://forum.kerbalspaceprogram.com/index.php?/topic/138490-request-navball-map/#comment-2549941).  Note that you may have to rotate the stock navball for some of our reference frames.

There are also useful threads in the [forums](http://forum.kerbalspaceprogram.com/index.php?/topic/63113-making-high-contrast-nav-ball/&page=8) where users publish custom navballs.

If you are simply dissatisfied with the colours, but like the general style, this repository contains *Mathematica* [code](https://github.com/mockingbirdnest/Principia/blob/master/mathematica/navball.wl) to generate navballs, that you can tweak to your liking.

## Why don't you keep the planets on rails, it would improve performance?
While "rails" (Keplerian evolution) is not entirely unrelated to something that *could* improve performance, it would do the exact opposite with the current choice of integrator. One still needs to compute the positions of all bodies every time the force on a spacecraft is needed, so the Keplerian evolution would have to be computed instead of the forces on the bodies. Given that the computation of Keplerian evolution is costly (one needs to solve [Kepler's equation](http://en.wikipedia.org/wiki/Kepler%27s_equation), which requires a big lookup table or a handful of trigonometric function evaluations) the quadratic-to-linear change is completely dwarfed by this cost for 20 or so massive bodies.

It is true that some splittings of the Hamiltonian, e.g., those given by Wisdom and Holman (1991), Duncan, Levison and Lee (1998), Beust (2003), have Keplerian parts, and we will implement these, if only for comparison purposes to see which one we keep in the final implementation.

At this point we will have code for Kepler evolution and integrators that could be shoehorned into having Keplerian-only behaviour for massive bodies, but we will nonetheless not provide Keplerian-only behaviour, because in the end we're just not interested in that, we're here for the numerical integration problem.

## I'd like the planets to follow their stock orbits
This would break physics. As an example, if planets were to do that, you would not get Lagrange points. It is an interesting exercise to compute the sum of the centrifugal and gravitational potentials for a body orbiting *the centre* of another (rather than their barycentre) in the reference frame that fixes both bodies and the orbital plane, and computing its gradient. It is easily seen that this gradient does not vanish in 5 points, but in only 3 instead.

## Why don't you parallelize?
It would hardly improve performance and it would be messy to implement. This is just the kind of algorithm that doesn't lend itself well to that.  Let's look at numbers. The only thing that's performance-critical here is the computation of trajectory predictions and flight plans. For those we're simulating the interactions of all massive bodies, and only one massless body. Computing all the forces costs 30 μs, and we *need* to synchronize outside of the force computation. Let's say we have a pool of 8 threads. We have to enqueue pointers to our data to our threads, and dequeue them, that's 16 locks. An uncontended lock costs about 50 ns, so that's 800 ns to start working, and 800 ns to synchronize when we're done. On a task that's 30 μs when single-threaded, we've spent 1.6 μs doing nothing. Whatever we might nibble away like that is not worth it.

## I'm using a custom solar system mod, why isn't it stable?
It all depends on whether your system was sanely designed. If it has 50 Duna-sized planets orbiting a Jool-sized body, many of these are going to interplanetary space today.

## Couldn't you gain performance by ignoring the influence of far-away bodies or by using a nonsymplectic integrator instead
We have thought about these options, and we will implement those that might yield improvements in due time in order to get as much accuracy as we can out of a given computational cost.

## What is oblateness / *J*<sub>2</sub> / *C*<sub>2</sub><sup>0</sup>?
The Earth is not a point mass nor a homogeneous sphere: it is an extended body. This has an effect on its gravitational field [that can be described by coefficients corresponding to spherical harmonics](https://en.wikipedia.org/wiki/Geopotential_model#The_deviations_of_Earth.27s_gravitational_field_from_that_of_a_homogeneous_sphere). Notably, the earth has an equatorial bulge, which corresponds to the *J*<sub>2</sub> coefficient---the *J*<sub>2</sub> coefficient can be referred to in terms of the related *C*<sub>2</sub><sup>0</sup> coefficient, for more details see [this NASA page](http://gracetellus.jpl.nasa.gov/data/J2/).
The *J*<sub>2</sub> coefficient strongly affects orbits around the Earth, causing apsidal and [nodal precession](https://en.wikipedia.org/wiki/Nodal_precession). For instance, [молния orbits minimize apsidal precessiond by having an inclination of 63.4 °](https://en.wikipedia.org/wiki/Molniya_orbit#Properties), and [heliosynchronous](https://en.wikipedia.org/wiki/Sun-synchronous_orbit) orbits [exploit nodal precession](https://en.wikipedia.org/wiki/Sun-synchronous_orbit#Technical_details) to stay aligned with the sun.

The initial config for RSS currently gives their proper *J*<sub>2</sub> coefficients to the Sun, the planets, the Moon, and Vesta. Other spherical harmonics are not yet implemented, but *C*<sub>2</sub><sup>2</sup> would definitely be relevant for tidally-locked bodies.

## What is the epoch of the RSS initial state, and what timescale is used?
The initial state config gives the solar system its state as given by the JPL HORIZONS service for 1950-01-01T00:00:00 *Temps Dynamique Barycentrique*. The state is however integrated before the game starts, so that the
game starts at 1951-01-01T00:00:00 *Temps Dynamique Barycentrique*.