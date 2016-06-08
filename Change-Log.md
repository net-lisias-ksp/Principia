# [Burnside](https://en.wikipedia.org/wiki/William_Burnside)

## User-facing features

* Changed the prediction parameters to be per vessel as opposed to global.  Thus, different vessels may have predictions of different lengths or accuracies.
* Changed the way that the trajectories of celestials are recorded in saves: instead of recording everything that was computed in the course of the game, only the next 6 months or so are saved.  The rest is recomputed when the save is loaded.  The advantage is that the saves are considerably smaller (a factor of 100x has been observed in simple games) which makes choosing a save in KSP faster as it insists on loading all the saves in memory.  The drawback is that loading a save is more CPU-intensive and may therefore take longer.
* The plugin has a new icon.

## Bug fixes

* Fixed the stabilization of the Jool system in the stock game which had stopped working in Буняковский.  This is the hotfix previously released as *Буняковский 6*.
* Fixed a situation where adaptive step integration would crash when the system was already integrated to the desired final time ([#1024](https://github.com/mockingbirdnest/Principia/issues/1024)).
* Fixed a problem where the start of a flight plan would be discarded to the point that it had no burns anymore and various pieces of the code would disagree as to whether the vessel still had a flight plan ([#1022](https://github.com/mockingbirdnest/Principia/issues/1022), [#1023](https://github.com/mockingbirdnest/Principia/issues/1023)).

See all [16](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2016-05-05T16%3A00%3A00..2016-05-20T21%3A59%3A59+sort%3Acreated-asc) pull requests between Буняковский and Burnside.

# [Буняковский](https://en.wikipedia.org/wiki/Viktor_Bunyakovsky)

## User-facing features

* Added code to try to detect bad installations.
* Joint Windows and Linux build.
* Give the user more control over the length of the predicted flight plan trajectory.
* Prevent accidental deletion of a non-empty flight plan.
* Display the total Δv of the flight plan.
* Limit the amount of time that we are willing to spend computing the trajectory of celestials.  This prevents the game from freezing when trying to extend e.g., the prediction to be very long.  The prediction is just going to be progressively extended over several seconds.
* Compute and display the apsides of trajectories, which makes it easier to evaluate the altitude of the predicted flight plan.  Note that, for trajectories that are very far from a conic, there may be many apsides. Note that apsides are only displayed with respect to the fixed celestial, if there is one.
* Tweaked the colours and styles used to display trajectories.
* Added a button to time warp to the next manœuvre (1 min ahead of the time of ignition).
* Changed the prediction computation to be defined by a number of steps, not a length.  This makes the amount of work performed at each frame roughly constant.
* Support for KSP 1.1.2.

## Bug fixes

* Fixed a crash when saving with RealSolarSystem installed ([#905](https://github.com/mockingbirdnest/Principia/issues/905)).  This is the hotfix previously released as *Buffon 12*.
* Fixed yet another use-after-free bug ([#908](https://github.com/mockingbirdnest/Principia/issues/908)) and added checks to detect situations that can lead to this kind of bug.
* Fixed a problem where burns would sometimes result in an infinite Δv.

## Optimizations

* Stopped serializing the trajectories of the flight plan, recompute them instead.  Also properly discard past trajectories (we used to keep them around for no good reason).  This makes the saves smaller.
* Moved to x64 on Windows and stopped supporting Win32.  This brought significant performance improvements (about 30%) for the integrators.
* Increased the protocol buffer deserialization limit to 512 MiB, which should make it possible to re-read very large saves.  Since we are now creating significantly smaller saves, this should suffice for most missions.

## Library changes

* Added parameterization to limit the number of integration steps performed by adaptive integrators.
* Improved the encapsulation and testing of the Vessel class.  Hopefully this will improve the stability of the plugin.
* Two-step journaling makes it easier to reproduce crashes.

See all [75](
https://github.com/mockingbirdnest/Principia/pulls?page=1&q=is%3Apr+is%3Aclosed+merged%3A2016-02-22T20%3A00%3A00..2016-05-05T16%3A59%3A59+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Buffon and Буняковский.

# [Buffon](https://en.wikipedia.org/wiki/Georges-Louis_Leclerc,_Comte_de_Buffon)

## User-facing features

* The integrators now limit the number of steps they perform, and terminate if their step size vanishes. This avoids issues where the plugin would hang when the trajectory would accidentally get very close to the centre of a celestial body or spend a long time in a low orbit.
* The version identifier of the plugin is now displayed in the UI to make it is easier to assert what version is running.

## Bug fixes

* A use-after-free bug has been fixed which caused a variety of crashes ([#872](https://github.com/mockingbirdnest/Principia/issues/872), [#881](https://github.com/mockingbirdnest/Principia/issues/881), [#889](https://github.com/mockingbirdnest/Principia/issues/889), [#896](https://github.com/mockingbirdnest/Principia/issues/896)) when the historical trajectory was shortened in a way that would cause it to start after the beginning of the flight plan.

## Library changes

* A verbosity option has been added to the journalling which makes it easier for us to reproduce crashes.

For more details see all [19](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+merged%3A2016-02-09T21%3A00%3A00..2016-02-22T20%3A00%3A00+is%3Aclosed+) pull requests between Brouwer and Buffon.

# [Brouwer](https://en.wikipedia.org/wiki/L._E._J._Brouwer)

## User-facing features

* The whole Frenet trihedron is now displayed in the correct reference frame when "fix navball in plotting frame" is selected.
* The initial state (and thus the evolution) of the system is now deterministic even when not using RealSolarSystem.
Tidally locked bodies no longer spin back and forth madly (on the other hand, they may not be tidally locked if their mean period differs from their Jacobi osculating period).
* When using stock, the Jool system is modified, cancelling the apocalypse. Specifically, we make the inner Jool system nonresonant, since we have been unable to replicate the results (Manley, priv. comm.) according to which some interpretations of the orbital elements yielded a stable Laplace resonance, despite systematic searches of the Jacobi osculating elements. In addition, at Scott Manley (@illectro)'s and @UmbralRaptor's suggestion, we put Bop in a surprisingly stable, though highly precessing, retrograde orbit. The modified system is stable for upwards of a century.
* Flight planning has been implemented.

## Modder-facing changes

* When a Cartesian initial state cfg is not given, the KSP orbital elements are interpreted in a hierarchical osculating Jacobi fashion; for instance, the orbital elements of Jool are the osculating elements at game start of the orbit of the barycentre of the Jool system around the barycentre of the (sun, moho, eve, gilly, kerbin, mun, minmus, duna, ike, dres) system; the elements of Laythe are the osculating elements at game start of the orbit of Laythe around Jool; the elements of Vall are the osculating elements at game start of the orbit of Vall around the Laythe-Jool barycentre.

## Optimizations:

* The Windows build now uses profile-guided optimization (we estimate that this improves performance by ~20%); in theory this could be extended to other platforms.
* The evaluation of the Чебышёв series has been significantly optimized.
* @sarbian made trajectory rendering faster (as he pointed out, there is still lots of room for improvement).
Other features:

# Library changes

* Everything that crosses the C++/C# interface can now be journalled if the right flag is set, allowing us to replay the C++ side of a session; this is useful for tracking down tricky bugs, and it enables profile-guided optimization.
* In order to get the full Frenet trihedron, (which was needed for manœuvres, since the Δv is defined in the Frenet frame at the point of ignition) geometric acceleration (the acceleration of a free-falling trajectory) in any reference frame was needed. To do that we created two abstractions, RigidMotion, the derivative of a RigidTransformation, and DynamicFrame, the definition of an arbitrary reference frame. The navigation frames (the frames in which the trajectory is drawn, or with which the manœuvres are defined) implement that (see BodyCentredNonRotatingDynamicFrame and BarycentricRotatingDynamicFrame).
* In order to interpret the orbital elements of KSP in the hierarchical Jacobi fashion described above, support was added for Kepler orbits (implementation), Jacobi coordinates, and hierarchical systems.
* Discrete trajectories were reworked, with a heavy dose of CRTP.
* In preparation for the surface frame in the future, RotatingBody was added.
* The C++ interface headers and C# extern declarations were repetitive and error-prone, this was exacerbated by the addition of journalling code and replaying code, so a generator was written to produce all of that from an annotated proto.
* @UmbralRaptor contributed some tests of lunar eclipse timings.
* For both Kepler orbits and lunar eclipse timings, a simple root finder was needed, bisection does the job for now.
* A bibliography was written, at @UmbralRaptor's request (it is somewhat out of date).
* SolarSystem, a class for initializing ephemerides from protobuf text format configuration files for testing purposes was written.
* A script for generating the initial state configuration files from the emails sent by JPL's HORIZONS system was written (the gravity model configuration file is hand-curated).
* An utility turns the protobuf text format configuration files into KSP ModuleManager configuration files for RSS support.
* Various geometric utilities were added: angles (implementation), spherical coordinates (more are needed).
* More C++11/14 features were used as they became available (for instance, the units are now constexpr), in addition we now use std::experimental::optional.
* C++14-related improvements were made to not_null.

For more details, see all [195](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2015-08-15T15%3A00%3A00..2016-02-09T22%3A00%3A00+sort%3Acreated-asc) pull requests between Bourbaki and Brouwer.