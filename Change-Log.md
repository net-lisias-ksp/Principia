# [Galileo](https://en.wikipedia.org/wiki/Galileo_Galilei)

*This is a draft of the change log; Galileo is not available yet.*

## Bug fixes

* The external APIs that throw an exception in case of error now include in the exception, in addition to the status code, a short message in English detailing the circumstances of the error ([2585](https://github.com/mockingbirdnest/Principia/issues/2585)).

## Modder-facing changes

For more details see all [14](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2020-05-21T11:00:00..2020-06-20T11:59:59+sort%3Acreated-asc) pull requests between Galileo and Fuchs.

# [Fuchs](https://en.wikipedia.org/wiki/Lazarus_Fuchs)

## User-facing features

* This is the last version to support KSP 1.5.x, 1.6.x and 1.7.x. The next version will only support 1.8.1 and up.

* Principia used to only support days of 6 hours (for stock KSP) or 24 hours (for Real Solar System).  It now uses the correct KSP APIs to figure out the length of the day.  This makes it compatible with Kronometer and with Je Ne Sais Quoi which embeds Kronometer and has days of 12 hours ([2520](https://github.com/mockingbirdnest/Principia/issues/2520)).

* The manœuvre node marker on the navball used to follow the Frenet frame prior to ignition, which was not very useful for manual burns and confused MechJeb.  It now shows the initial ignition orientation prior to ignition and then follows the Frenet frame during the burn.  Combined with MechJeb change [MuMech/MechJeb2#1264](https://github.com/MuMech/MechJeb2/pull/1264) (present in MechJeb dev builds ≥ 958), this makes it possible to execute all Principia manœuvres with MechJeb ([2577](https://github.com/mockingbirdnest/Principia/issues/2577)).

## Bug fixes

* The rotational bugs that were introduced in Frobenius and Fubini (uncontrolled spin-up, jerky motion, oscillations, etc.) have been traced to incorrect physics simulation by PhysX and mostly fixed.  We are still aware of one contrived example where after a vessel explodes a part starts rotating wildly, and are investigating it ([2519](https://github.com/mockingbirdnest/Principia/issues/2519)).

* Principia would fail to start with a mysterious error message if installed in a path that includes non-ASCII characters on a system where the code page is not compatible with UTF-8.  The root of the problem appears to be a Mono bug so there is not much that we can do to fix it, but we are now emitting the more understandable error message `<path> contains the non-ASCII character <c>; this is known to confuse Mono` ([2548](https://github.com/mockingbirdnest/Principia/issues/2548)).

## Modder-facing changes

* Three new APIs, [`CelestialGetPosition`](https://github.com/mockingbirdnest/Principia/wiki/Interface-for-other-KSP-mods#celestialgetposition), [`CelestialGetSurfacePosition`](https://github.com/mockingbirdnest/Principia/wiki/Interface-for-other-KSP-mods#celestialgetsurfaceposition), and [`VesselGetPosition`](https://github.com/mockingbirdnest/Principia/wiki/Interface-for-other-KSP-mods#vesselgetposition) have been added to allow third-party mods to access the position of celestials and vessels computed by Principia.  This will be used by KerbalismContracts to correctly check the fulfilment of mission requirements in the presence of *n*-body physics and axial tilt ([2542](https://github.com/mockingbirdnest/Principia/issues/2542)).

For more details see all [28](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2020-04-19T11:00:00..2020-05-21T10:59:59+sort%3Acreated-asc) pull requests between Fuchs and Fubini.

# [Fubini](https://en.wikipedia.org/wiki/Guido_Fubini)

## User-facing features

* Support for KSP 1.9.1 has been added: this version supports 1.5.1, 1.6.1, 1.7.x, 1.8.1 and 1.9.1. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).

* The flight plan is now automatically extended when moving forward the start time of the last manœuvre or increasing its Δv; note that for engines that have very low thrust, this may result in a very long flight plan, in which case the length will effectively be limited by the number of steps of the integrator ([852](https://github.com/mockingbirdnest/Principia/issues/852)).

* The flight planner and the orbit analyser can now be displayed in the tracking station ([2531](https://github.com/mockingbirdnest/Principia/issues/2531)).

## Bug fixes

* The angular momentum correction introduced in [Frobenius](https://github.com/mockingbirdnest/Principia/wiki/Change-Log#frobenius) was found to create non-physical oscillations or rotations, especially when reentering the atmosphere, where large forces apply to the vessel; this has been improved by adjusting the orientation of the vessel instead of its angular velocity, which causes less disruption to the PhysX integrator, but it doesn't completely fix the bug, see below ([2519](https://github.com/mockingbirdnest/Principia/issues/2519)).

* Undocking two vessels would sometimes cause Principia to crash. This is a bug that has been with us for a long time, and suddenly started to bite many users in March, maybe because of changes in some other mod. It was probably triggered by large forces being applied to the vessel at the time of the uncoupling, and has been fixed by skipping the points computed by the adaptive step integrator that turn out to be in the past ([2490](https://github.com/mockingbirdnest/Principia/issues/2490), [2507](https://github.com/mockingbirdnest/Principia/issues/2507)).

* Principia would sometimes crash when parts were about to be destroyed by KSP; this has been fixed by ignoring the parts whose positions, velocities, angular velocities, forces or torques are `NaN`s ([2532](https://github.com/mockingbirdnest/Principia/pull/2532)).

## Known issues

* [2519](https://github.com/mockingbirdnest/Principia/issues/2519) is still known to cause wobble or jerky movements.

For more details see all [23](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2020-03-20T23:30:00..2020-04-19T10:59:59+sort%3Acreated-asc) pull requests between Fubini and Frobenius.

# [Frobenius](https://en.wikipedia.org/wiki/Ferdinand_Georg_Frobenius)

## User-facing features

* After nearly a year of work, Principia now implements the rotational motion of vessels.  This makes the physical simulation more correct in the following areas:
  * Angular momentum is now preserved and the vessel obeys [Euler's equations for the motion of rigid bodies](https://en.wikipedia.org/wiki/Euler%27s_equations_(rigid_body_dynamics)).  This remains true if the geometry or the distribution of mass in a vessel changes over time.
  * Vessels properly rotate during warp, and rotation is continuous when warping/unwarping.
  * Vessels remain properly oriented when crossing the sphere of influence of a celestial; this fixes a longstanding bug ([1639](https://github.com/mockingbirdnest/Principia/issues/1639)).

  Rotational motion brings more realism to the game: please take a moment to watch two short videos which illustrate interesting phenomena:
  * [The figure skater effect](https://youtu.be/QWiRvKfe3SE): Transferring fuel from one tank to another causes the angular velocity to change in the same manner that figure skaters control their speed.
  * [The Джанибеков effect](https://youtu.be/jy-_AUxAA7c): Rotational motion around the second axis of inertia exhibits a surprising instability ([compare with a real experiment in zero-G](https://www.youtube.com/watch?v=1n-HMSCDYtM)).

  Note that the implementation uses closed-form formulæ so its CPU cost is virtually zero even at the highest warp speed, and there is no accumulation of errors or drifts.

  If you have been using PersistentRotation, we recommend that you uninstall it as the two mods would fight each other and PersistentRotation is not physically correct anyway.

* Saves now use [zfp](https://computing.llnl.gov/projects/floating-point-compression) to compress the trajectories of vessels.  This makes them about 4x smaller, and may significantly reduce the time needed to switch scenes.

## Known issues

* KSP gives us no indication of how angular momentum is lost when an engine burns.  In this version we assume that solid rocket boosters lose all their angular momentum and other engines don't lose any.  We will probably want to have better heuristics/models in future versions.
* Games which are very far from the origin of time (e.g., if you are around year 2020 in a RealSolarSystem game) may take a long time to save, load, or switch scene.  We are looking into better representations of the trajectories of celestial over long periods to address this problem ([2400](https://github.com/mockingbirdnest/Principia/issues/2400)).

For more details see all [20](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2020-02-22T18:00:00..2020-03-20T23:29:59+sort%3Acreated-asc) pull requests between Frobenius and Frenet.

# [Frenet](https://en.wikipedia.org/wiki/Jean_Fr%C3%A9d%C3%A9ric_Frenet)

## User-facing features

No new features in this version.  We have spent a fair amount of time implementing the rotational motion of vessels, and hope to be able to release it in the next version (Frobenius).  This release has quite a few (invisible) changes to the management of parts and vessels, so we invite users to upgrade to help us find any problems/bugs that we could have introduced.

For more details see all [16](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2020-01-23T19:30..2020-02-22T17:59:59+sort%3Acreated-asc) pull requests between Frenet and Frege.

# [Frege](https://en.wikipedia.org/wiki/Gottlob_Frege)

## User-facing features

* The celestial histories are now displayed before the beginning of the history of the active vessel.  Long celestial histories can now be seen in map view, along with the shorter history of a vessel. Predictions still end where the active vessel's does.

## Bug fixes

* As mentioned in the [Known issues for Fréchet](https://github.com/mockingbirdnest/Principia/wiki/Change-Log#known-issues), the camera would spin wildly when the game was paused in map view.  This has been fixed by not adjusting the camera when the game is paused.  It also fixes a more subtle issue whereby changing the plotting frame when the game was paused would fail to preserve the orientation of the camera.

* If some prerequisite of Principia (e.g., the Microsoft Visual C++ 2015-2019 Redistributable) was missing, the problem would only be detected *after* loading a save, and the Principia data would be lost from the save; this has been fixed by activating Principia when the KSP main menu is shown, i.e., before touching any save ([2385](https://github.com/mockingbirdnest/Principia/issues/2385)). 

* The `reference_radius` in the `principia_gravity_model` configuration was documented as defaulting to `radius` but in reality it did not default to anything; this has been fixed by making the code consistent with the documentation ([2429](https://github.com/mockingbirdnest/Principia/issues/2429)).

* When a vessel touched the ground, its prediction parameters (tolerance and steps) would be lost, which was annoying when biome hopping; this has been fixed by retaining the prediction parameters of all the vessels, even if they are not managed by Principia  ([2443](https://github.com/mockingbirdnest/Principia/issues/2443)).

For more details see all [39](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-12-26T12:00:00..2020-01-23T19:29:59+sort%3Acreated-asc) pull requests between Frege and Fréchet.

# [Fréchet](https://en.wikipedia.org/wiki/Maurice_Ren%C3%A9_Fr%C3%A9chet)

## User-facing features

* Support for KSP 1.8.1 has been added: this version supports 1.5.1, 1.6.1, 1.7.x and 1.8.1. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).

* The camera is now positioned so that the horizontal in map view is the reference plane of the selected plotting frame.
Further, the camera rotates with the plotting frame (in particular, if the camera is looking at a body which is fixed in the plotting frame, the camera is fixed in the plotting frame). This mean that the plotted trajectories do not rotate as time passes, a behaviour which was somewhat confusing and annoying.

## Known issues

* When bringing up the game menu in map view, the camera will rotate in the background.  We will try to address this problem in a future version.

For more details see all [26](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-11-23T23:00:00..2019-12-26T11:59:59+sort%3Acreated-asc) pull requests between Fréchet and פרנקל.

# [פרנקל](https://en.wikipedia.org/wiki/Abraham_Fraenkel)

## User-facing features

* Principia now plots the trajectories of celestials, instead of relying on KSP to do so.  This plotting obey the settings of the current frame, so trajectories can have rather interesting shapes; for instance, [here](https://user-images.githubusercontent.com/2284290/68534053-8dc47f00-0330-11ea-8f65-1e0504b38bd7.png) is an example of the motion of the Jool system (including its satellites) around the Sun.  We use KSP to decide which bodies to show exactly (so that, at a sufficient distance from Jool, its satellites won't be displayed).  We only plot the trajectories of the celestial bodies since
  - the beginning of the mission when there is an active vessel, or
  - the beginning of the game otherwise,

  so for distant planets (e.g., Pluto) you will only see one arc of the ellipse (unless you are *very* patient).

* The setting for the history length in the main Principia window now hides the histories (for both vessels and celestials) instead of forgetting them.  This means that it is possible to shorten and then extend again the histories without losing any information.  The length is now controlled by a slider which display the duration of the histories in a human-readable manner.

## Library changes

* Support has been added to represent the inertia tensor of a solid and its transforms. This is another step towards properly handling the rotation of vessels around their centre of mass.

## Known issues

* The release name, being in Hebrew, is written right-to-left. KSP doesn't know how to do such an advanced thing, so it shows up inverted in the UI. Apologies to Hebrew speakers.  (We had the same problem with release بوژگانی, around June 2016...)

For more details see all [11](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-10-26T10:00:00..2019-11-23T22:59:59+sort%3Acreated-asc) pull requests between פרנקל and Fourier.

# [Fourier](https://en.wikipedia.org/wiki/Joseph_Fourier)

## Bug fixes

* Changing the flight plan in a way that would cause the last burn to end after the end of the flight plan would sometimes cause Principia to crash; this has been fixed by automatically extending the flight plan in that case ([2357](https://github.com/mockingbirdnest/Principia/issues/2357)).

* If the upcoming manœuvre was anomalous (i.e., happened at a point before which the integrator had encountered a singularity, maybe because it timed out), Principia would crash when trying to display it on the navball; this has been fixed by not displaying the upcoming manœuvre node in that case  ([2358](https://github.com/mockingbirdnest/Principia/issues/2358)).

## Library changes

* A solver has been added for Arnold's equations. This is another step towards properly handling the rotation of vessels around their centre of mass.

For more details see all [15](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-09-29T00:00:00..2019-10-26T09:59:59+sort%3Acreated-asc) pull requests between Fourier and Fibonacci.

# [Fibonacci](https://en.wikipedia.org/wiki/Fibonacci)

## User-facing features

* Support has been added for analysis of orbits.  The main Principia window has a new button `Orbit analysis...` which brings up a separate window showing the mean orbital elements of the predicted trajectory, as well as the properties of its ground track cycle.  This computation is done asynchronously and makes it easier to put a satellite on a particular orbit (geosynchronous, geostationary, Молния, etc.).

## Bug fixes

* The use of the Switch To button to switch to another vessel used to crash Principia; this has been fixed by avoiding accesses to the Principia plugin during scene switches ([2313](https://github.com/mockingbirdnest/Principia/issues/2313)).

* Many users reported that Principia would fail to load on Windows machines which had some Nvidia software (GeForce Experience?) installed because we would try to load Nvidia's `libproto.dll` instead of our own; this has been fixed by using embedded manifests to unambiguously locate our DLLs ([2297](https://github.com/mockingbirdnest/Principia/issues/2297), [2334](https://github.com/mockingbirdnest/Principia/issues/2334)).

For more details see all [28](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-08-25T17:00:00..2019-09-28T23:59:59+sort%3Acreated-asc) pull requests between Fibonacci and del Ferro.

# [del Ferro](https://en.wikipedia.org/wiki/Scipione_del_Ferro)

## User-facing features

* The Principia UI is no longer shown in the space center in the buildings where it is not relevant: administration, astronaut complex, mission control, and research and development ([2262](https://github.com/mockingbirdnest/Principia/issues/2262)).

* The log files produced by Principia now have the extension `.log` which makes them easier to open on Windows.

* In RealSolarSystem, geopotentials have been added for Mercury, Venus, Mars, Jupiter, Saturn, Uranus, and Neptune.  This makes the motion of the satellites of these planets more realistic.  This change only takes effect on new saves.

* Principia used to compute all the apsides and nodes for the prediction and flight plan, even though it only displayed 64.  This led to poor performance for long trajectories.  This has been fixed by limiting the number of computed apsides and nodes to 64.  In addition, the computations have been optimized slightly.

* Detection of bad installations has been improved somewhat.  We now recommend that users install the unified [C++ 2015-2019 Redistributable](https://download.visualstudio.microsoft.com/download/pr/cc0046d4-e7b4-45a1-bd46-b1c079191224/9c4042a4c2e6d1f661f4c58cf4d129e9/vc_redist.x64.exe).

## Bug fixes

* The apsides displayed on the prediction would sometimes have an incorrect text that would not reflect what they represented (e.g., "Kerbin Apoapsis" when the selected body is Minmus).  This has been fixed ([2257](https://github.com/mockingbirdnest/Principia/issues/2257)).

* The minimal radius of celestials is propagated from the game and used (instead of the mean radius) when detecting collisions.  This matters when orbiting or landing on potato-shaped celestials like Phobos, as collisions would improperly be detected above the surface.  This change only takes effect on new saves ([2237](https://github.com/mockingbirdnest/Principia/issues/2237)).  

For more details see all [31](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-07-30T20:00:00..2019-08-25T16:59:59+sort%3Acreated-asc) pull requests between del Ferro and Ferrari.

# [Ferrari](https://en.wikipedia.org/wiki/Lodovico_Ferrari)

## User-facing features

* Support for KSP 1.7.3 has been added.  This version supports 1.5.1, 1.6.1 and 1.7.x.

## Bug fixes

* The "new release" message used to make the main Principia window very wide.  It also improperly detected if KSP was a pre-1.5 version.  This has been fixed so that the message is displayed on multiple lines and the version is correctly determined ([2249](https://github.com/mockingbirdnest/Principia/issues/2249)).
* The prediction parameters (tolerance, number of steps) were not always properly persisted after being changed in the UI.  Also, when no vessel was selected, the default values were displayed, which was confusing.  This has been fixed by persisting the parameter directly in the UI, and by leaving the fields empty when no vessel is selected ([2239](https://github.com/mockingbirdnest/Principia/issues/2239)).

## Library changes

* A solver has been added for [Euler's equations](https://en.wikipedia.org/wiki/Euler%27s_equations_(rigid_body_dynamics)).  This is another step towards properly handling the rotation of vessels around their centre of mass.

* Support for finding the recurrence of orbits has been added.  This is the first step towards computing and displaying orbital elements of vessels.

For more details see all [17](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-06-29T20:00:00..2019-07-30T19:59:59+sort%3Acreated-asc) pull requests between Ferrari and Fermat.

# [Fermat](https://en.wikipedia.org/wiki/Pierre_de_Fermat)

## User-facing features

* Support for KSP 1.7.1 and 1.7.2 has been added, and support for 1.3.1 and 1.4.x has been removed: this version of Principia requires at least KSP 1.5.1.
* All manœuvres in a flight plan can now be edited.  This addresses a long-standing inconvenience where, if you wanted to edit an earlier manœuvre after planning many manœuvres, you had to delete the manœuvres after it.  Also, more precise error messages are emitted to guide the user when formulating the flight plan ([1936](https://github.com/mockingbirdnest/Principia/issues/1936)).
* The duration of manœuvres now takes into account the thrust limiter, just like stock manœuvres do ([2128](https://github.com/mockingbirdnest/Principia/issues/2128)).

## Library changes

* Elliptic integrals and functions have been added.  This is the first step towards properly solving [Euler's equations](https://en.wikipedia.org/wiki/Euler%27s_equations_(rigid_body_dynamics)) and correctly handling the rotation of vessels around their centre of mass, something which KSP does very badly.  This is going to be a multi-month effort.

For more details see all [41](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-06-01T21:00:00..2019-06-29T19:59:59+sort%3Acreated-asc) pull requests between Fermat and Fatou.

# [Fatou](https://en.wikipedia.org/wiki/Pierre_Fatou)

## User-facing features

* Support for KSP 1.7.0 has been added: this version supports 1.3.1, 1.4.x, 1.5.1, 1.6.1 and 1.7.0. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).  Note that we don't use the new widget for editing manœuvres: trying to edit manœuvre parameters in that widget will probably lead to unexpected results.

* This is the last version to support KSP 1.3.1 and 1.4.x.  The next version will only support 1.5.1 and up.

* The nodes of a trajectory with respect to the equator of the closest celestial are now displayed when the trajectory is "sufficiently close" to that celestial; this helps adjusting orbits with respect to the equator and addresses a longstanding feature request ([#1841](https://github.com/mockingbirdnest/Principia/pull/1841)).

## Bug fixes

* The flight plan window would reduce to size 0 when a flight plan had no manœuvres at the time of a scene switch; this has been fixed by properly redisplaying the flight plan final time ([#2158](https://github.com/mockingbirdnest/Principia/pull/2158)).

* The Ap/Pe/AN/DN nodes shown on the trajectories where sometimes displayed without a name or in the wrong color; this was due to improper reuse of nodes and has been fixed by correctly tracking the celestial to which a node refers ([#2162](https://github.com/mockingbirdnest/Principia/pull/2162)).

* Performance was significantly degraded when the flight planning window was displayed compared to when it was hidden; this was due to the UI improperly thinking that the flight plan had been changed at each frame and needed to be recomputed, and has been fixed by properly tracking manœuvre changes ([#2157](https://github.com/mockingbirdnest/Principia/issues/2157)).

* Manœuvres would sometimes move to the future (instead of being fixed in time) when the history was short; this problem was introduced in Fáry where we started to use the beginning of the flight plan as a time base for the manœuvres, and that time base would move in this situation; this was fixed by properly anchoring the manœuvres in time ([#2166](https://github.com/mockingbirdnest/Principia/issues/2166)).

* The description of the "Target Local Vertical/Horizontal" frame in the frame selector was garbled and unreadable; this has been fixed by properly displaying multiline text ([#2169](https://github.com/mockingbirdnest/Principia/issues/2169)).

For more details see all [25](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-04-28T15:00:00..2019-06-01T20:59:59+sort%3Acreated-asc) pull requests between Fatou and Fáry.

# [Fáry](https://en.wikipedia.org/wiki/Istv%C3%A1n_F%C3%A1ry)

## User-facing features

* The Principia UI now scales with the KSP "UI Scale" and "Apps Scale".  This should make the UI easier to use on 4k/8k screens.  Note that changes to the scale only take effect on save load or scene changes.
* The parameters of manœuvres may now be edited using a text field in addition to a slider.  The input is taken into account when _return_ is typed.  The text turns orange if the syntax of the input is incorrect.  ([#2121](https://github.com/mockingbirdnest/Principia/issues/2121)).
* The Principia UI has been made slightly more compact by rearranging the fields and the controls.  Informational messages are now displayed in grey and warnings in orange.
* The “Trappist-1 for Principia” mini-mod has been updated to work with versions 0.7.x of the [SLIPPIST-1](https://github.com/GregroxMun/Seven-Worlds-of-SLIPPIST-1) mod.

## Bug fixes

* A longstanding bug has been fixed whereby the upcoming manœuvre was not always properly shown on the navball ([#1565](https://github.com/mockingbirdnest/Principia/issues/1565)).

For more details see all [19](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-04-02T09:00:00..2019-04-28T14:59:59+sort%3Acreated-asc) pull requests between Fáry and Fano.

# [Fano](https://en.wikipedia.org/wiki/Gino_Fano)

## User-facing features

* Predictions are now computed asynchronously without blocking the UI thread.  This means that it's possible to have long predictions while retaining good playability: this is especially important close to celestials like the Earth or the Moon that have a complex geopotential.  Long predictions just refresh infrequently, which in practice is mostly invisible.  Note however that some computations (e.g., rendering) are still computed on the UI thread, so extremely long predictions  still reduce the frame rate.
* As a consequence of the previous change, we limit the number of nodes that are displayed in map view to 64 by type (apsides, approaches, etc.).  That's because KSP is *extremely* inefficient at displaying large numbers of nodes, and while Principia could easily compute thousands of nodes there is no way that KSP could display them.
* The UI code has been extensively restructured and rewritten.  While it doesn't change the UI much, this rewrite fixes a few minor bugs and improves usability a bit, for instance by properly persisting the state of windows between scene changes.  More importantly, it provides a sound foundation for future improvements.

## Bug fixes

* The map nodes (apsis markers, ascending and descending node markers, etc.) no longer lag behind when the camera is moved in map view.

* The ascending and descending nodes of the flight plan were incorrectly labeled as “Predicted Ascending Node” (or “Predicted Descending Node”), as if they were nodes of the prediction. They now are now correctly labeled as “Planned Ascending Node” (or “Planned Descending Node”).

## Modder-facing changes

Some bugs have been fixed in the APIs provided for accessing our geopotential models.

For more details see all [32](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-02-19T01:00:00..2019-04-02T08:59:59+sort%3Acreated-asc) pull requests between Fano and Euler.

# [Euler](https://en.wikipedia.org/wiki/Leonhard_Euler)

## Bug fixes

In RealSolarSystem, the intrinsic forces (parachutes, engines, etc.) used to be ignored below an altitude of 8.4 m on Earth.  This manifested itself, for instance, by a brutal drop when landing a vessel with a parachute.  This has been fixed by properly accounting for intrinsic forces close to the surface ([#2072](https://github.com/mockingbirdnest/Principia/issues/2072)).

## Modder-facing changes

APIs have been added to make it possible for third-party mods to access our geopotential models ([#2074](https://github.com/mockingbirdnest/Principia/issues/2074)).

For more details see all [9](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-01-30T19:00:00..2019-02-19T00:59:59+sort%3Acreated-asc) pull requests between Euler and Εὐκλείδης.

# [Εὐκλείδης](https://en.wikipedia.org/wiki/Euclid)

## User-facing features

* Support for KSP 1.6.1 has been added: this version supports 1.3.1, 1.4.x, 1.5.1 and 1.6.1. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).

## Bug fixes

* A longstanding bug has been fixed where the prograde/retrograde/etc. directions in SAS were inconsistent with the actual Frenet frame of the trajectory ([#1868](https://github.com/mockingbirdnest/Principia/issues/1868)).

* Principia would crash when a vessel (or a fragment thereof) was getting close to the centre of a celestial.  This could happen during atmospheric reentry followed by rapid unscheduled disassembly: fragments ejected very fast could go below ground without KSP noticing.  This has been fixed by killing the fragment when this situation was detected by Principia ([#2056](https://github.com/mockingbirdnest/Principia/issues/2056)).

For more details see all [9](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2019-01-05T15:00:00..2019-01-30T18:59:59+sort%3Acreated-asc) pull requests between Εὐκλείδης and Εὔδοξος.

# [Εὔδοξος](https://en.wikipedia.org/wiki/Eudoxus_of_Cnidus)

## User-facing features

* We have added a selenopotential (lunar gravity model) complete to degree and order 30 to the Moon for RealSolarSystem, truncated from the GRAIL gravity model [GRGM1200A](https://www.hou.usra.edu/meetings/lpsc2016/pdf/1484.pdf).  This configuration reproduces the complex (and sometimes unstable) orbits caused by mass concentrations on the Moon.  It should now be [significantly harder](https://en.wikipedia.org/wiki/Lunar_orbit#Perturbation_effects) to have stable low-altitude orbits around the Moon.
Note that this change will only take effect if you create a new save; existing saves will retain the simpler gravity model.

* Saves are now encoded in [base64](https://en.wikipedia.org/wiki/Base64) instead of [hexadecimal](https://en.wikipedia.org/wiki/Hexadecimal).  This makes them more compact by 30%, but more importantly they load about twice as fast.

* The “Trappist-1 for Principia” mini-mod has been updated to use a configuration of the Trappist-1 system that correctly fits the observations.  The previous version used an integrator that was not converged for planet *b* ([#1999](https://github.com/mockingbirdnest/Principia/issues/1999)).  You’ll need to start a new game to see the changes.  Also, we are now including a configuration for RSSTimeFormatter that properly displays the (Earth) date and time.

## Bug fixes

* Switching between scenes (or loading a save) was very long if there ever was in the game a very long (years) flight plan or prediction, even if it had been shortened/deleted.  This was because the solar system was recomputed up to the most distant time ever reached.  This has been fixed by only recomputing the solar system as far as needed by the current flight plan and prediction ([#2038](https://github.com/mockingbirdnest/Principia/issues/2038)).

For more details see all [40](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-12-05T13:00:00..2019-01-05T14:59:59+sort%3Acreated-asc) pull requests between Εὔδοξος and Erdős.

# [Erdős](https://en.wikipedia.org/wiki/Paul_Erd%C5%91s)

## User-facing features

* Support for realistic geopotential modeling at arbitrary degrees is finally available, with appropriate damping to ensure that the computations are not overly costly: our benchmarks indicate that this should not have any significant impact on the performance of the game.  We have added a 10th-degree model of the Earth geopotential to our RealSolarSystem configuration, and we'll have more advanced modelling for other bodies (Moon, Mars, etc.) in future versions.

## Bug fixes

* Parallel integration has been changed to use [`absl::Mutex`](https://github.com/abseil/abseil-cpp/blob/master/absl/synchronization/mutex.h) instead of `std::mutex`; this has no effect on Windows or Linux, but it speeds things up considerably on macOS ([#1955](https://github.com/mockingbirdnest/Principia/issues/1955)).

* The `numerics_blueprint.cfg` file releases with the “Trappist-1 for Principia” mini-mod was incorrect, resulting in large errors in the transit times of the `b` planet.  An updated configuration is included in the Erdős version of the mini-mod ([#1999](https://github.com/mockingbirdnest/Principia/issues/1999)) but this is only a stopgap measure.  We'll redo the full Trappist-1 optimization and deliver another update in a future version.

## Library changes

* Our physical units are now compliant with the recent [redefinition of the SI base units](https://en.wikipedia.org/wiki/2019_redefinition_of_SI_base_units).

For more details see all [29](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-11-05T21:00:00..2018-12-05T12:59:59+sort%3Acreated-asc) pull requests between Erdős and Ἐρατοσθένης.

# [Ἐρατοσθένης](https://en.wikipedia.org/wiki/Eratosthenes)

## User-facing features

* Support for KSP 1.5.1 has been added: this version supports 1.3.1, 1.4.x and 1.5.1. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).

## Library changes

* We have been working on damping the effect of the geopotential to make it possible to have complex gravitational fields without performance degradation.

For more details see all [13](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-10-09T21:00:00..2018-11-05T20:59:59+sort%3Acreated-asc) pull requests between Ἐρατοσθένης and Διόφαντος.

# [Διόφαντος](https://en.wikipedia.org/wiki/Diophantus)

## User-facing features

No new features in this version.  We have spent a fair amount of time improving geopotential modeling, but that feature is not fast enough yet.

## Library changes

We now have realistic geopotential modeling at arbitrary degrees, we have validated the correctness of our code and we have done quite a bit of optimization.  We have also added a more realistic model of the rotation of the Earth.  Still, the performance is not yet sufficient to be used in the game.  We will have to implement some screening so as to avoid computing the effect of the Himalayas on Pluto.

For more details see all [17](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-09-09T14:00:00..2018-10-09T20:59:59+sort%3Acreated-asc) pull requests between Διόφαντος and Descartes.

# [Descartes](https://en.wikipedia.org/wiki/Ren%C3%A9_Descartes)

## User-facing features

* Principia no longer supports macOS El Capitan, as that version is no longer supported by Apple.  We now require macOS Sierra or later.  As a consequence of this change we were able to upgrade to a newer version of the C++ standard library.  This brings macOS to parity with the other platform in terms of multithreaded integration of vessels.  Users should see a significant speed-up, especially at high warp ([#1908](https://github.com/mockingbirdnest/Principia/issues/1908)).

* The integration of burns in the flight plan has been rewritten to use an embedded explicit generalized Runge-Kutta-Nyström method.  This is significantly more precise that the previous hacky technique of doing 100 small integrations.  It makes a difference for long burns (e.g., with ion engines) as they are more accurately predicted.

## Library changes

* We started work on improving geopotential modeling.  This should make it possible in future versions to have more realistic orbits around celestials with large mass concentrations such as Mars and the Moon.

For more details see all [30](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-08-10T23:00:00..2018-09-09T13:59:59+sort%3Acreated-asc) pull requests between Descartes and Desargues.

# [Desargues](https://en.wikipedia.org/wiki/Girard_Desargues)

## User-facing features

* Support for KSP 1.4.5 has been added: this version supports 1.3.1 and 1.4.x. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).

No new features in this version as we have been on vacation.

For more details see all [6](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-07-10T21%3A00%3A00..2018-08-10T22%3A59%3A59+sort%3Acreated-asc) pull requests between Desargues and Δημόκριτος.

# [Δημόκριτος](https://en.wikipedia.org/wiki/Democritus)

## User-facing features

* Support for KSP 1.4.4 has been added: this version supports 1.3.1 and 1.4.x. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise). 

* Vessels are now managed by Principia when they are in the atmosphere.  This means that it's possible to see the history and prediction and to prepare flight plans immediately after launch.  This works both with stock KSP and with Ferram Aerospace Research.

* The “Trappist-1 for Principia” mini-mod has been improved to better reflect the physical properties of the celestials.  It works fine with the latest version of SLIPPIST-1 (0.5) but will be more aesthetically pleasing with the upcoming version (0.6?).

## Bug fixes

* Subtle inaccuracies in the adaptive-step integrators would sometimes result in crashes because of attempts to integrate backwards in time or beyond the end of the ephemeris ([#1839](https://github.com/mockingbirdnest/Principia/issues/1839), [#1864](https://github.com/mockingbirdnest/Principia/issues/1864)).  This has been fixed by ensuring that the adaptative-step integrators never undershoot or overshoot the final time.

* The “Trappist-1 for Principia” mini-mod would crash when used with 1.4.3 or later because of an incompatibility with Kopernicus.  This has been fixed.

For more details see all [24](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-06-10T21%3A00%3A00..2018-07-10T20%3A59%3A59+sort%3Acreated-asc) pull requests between Δημόκριτος and Dedekind.

# [Dedekind](https://en.wikipedia.org/wiki/Richard_Dedekind)

## User-facing features

We have added a simulation of the [TRAPPIST-1](https://en.wikipedia.org/wiki/TRAPPIST-1) extrasolar planetary system as a mini-mod, “Trappist-1 for Principia”.  TRAPPIST-1 is a system of seven tightly coupled Earth-like planets orbiting close to an ultracool dwarf star where *n*-body gravitation plays an important role, so it's an interesting application of Principia.  For example, [this picture](https://i.imgur.com/2XwQg3W.png) shows a low-energy transfer from Trappist-1e to Trappist-1f with ballistic capture where the final orbit exhibits resonance with the rest of the system.  And just for eye candy, [this picture](https://i.imgur.com/aynfI5j.png) shows a double transit.

We used the most recently published observational data (from [K2](https://en.wikipedia.org/wiki/Kepler_(spacecraft)#Second_Light_(K2)) and [Spitzer](https://en.wikipedia.org/wiki/Spitzer_Space_Telescope)) and ran a [transit-timing variation](https://en.wikipedia.org/wiki/Transit-timing_variation) optimization to build a configuration that accurately models the real-life behavior of the planetary system (the transits are accurate to within a minute).

Our mini-mod comes as a patch on top of [@GregroxMun](https://github.com/GregroxMun)'s [SLIPPIST-1](https://spacedock.info/mod/1883/Seven%20Worlds%20of%20SLIPPIST-1) mod.  See the [FAQs](https://github.com/mockingbirdnest/Principia/wiki/Installing,-reporting-bugs,-and-frequently-asked-questions#installing-trappist-1-for-principia) for details on installing it and its prerequisites.

## Bug fixes

* A number of bugs have been fixed in the C# code which resulted in memory leaks.  In particular, displaying a long flight plan could leak memory at the rate of 1 GiB/minute, quickly making the machine unusable ([#1797](https://github.com/mockingbirdnest/Principia/issues/1797)).  These issues have been addressed by better management of memory across the C++/C# interface, notably using the [Dispose pattern](https://docs.microsoft.com/en-us/dotnet/standard/design-guidelines/dispose-pattern).

For more details see all [16](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-05-13T21%3A00%3A00..2018-06-10T20%3A59%3A59+sort%3Acreated-asc) pull requests between Dedekind and Darboux.

# [Darboux](https://en.wikipedia.org/wiki/Jean_Gaston_Darboux)

## User-facing features

* The saves are now compressed using [Gipfeli](https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/42050.pdf), which makes saves about 2.5× smaller.  Also, the protocol buffers used for saving are allocated in an arena.  Together, these changes make large saves about twice as fast to read and write.
* We have implemented our own [cube root](https://github.com/mockingbirdnest/Principia/blob/2018051512-Darboux/numerics/cbrt.cpp) for orbital element computations because the ones provided by the platforms are often slow and/or imprecise. 

For more details see all [32](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-04-09T00%3A00%3A00..2018-05-13T20%3A59%3A59+sort%3Acreated-asc) pull requests between Darboux and Cramer.

# [Cramer](https://en.wikipedia.org/wiki/Gabriel_Cramer)

## User-facing features

No new features in this version.  We have spent a fair amount of time upgrading to newer compilers (Visual Studio 2017, Clang 5.0) and to C++17.

**Very importantly, these upgrades mean that you need to upgrade your C++ runtime.**  On Windows you must install the [Visual C++ Redistributable Packages for Visual Studio 2017 on x64](https://go.microsoft.com/fwlink/?LinkId=746572).  On Linux you need to install version 6.0-2 of libc++abi (if using Ubuntu, this comes natively with Bionic Beaver).  On Mac there are no changes, we still support El Capitan or later.

This is the last version to support KSP 1.2.2. The next version will only support KSP 1.3.1 and 1.4.x.

## Bug fixes

* A bug has been fixed where the manœuvre marker would jump at the time of ignition.  This stemmed from a confusion between the vessel's current osculating orbit and the conic patch for the manœuvre node. This this was particularly noticeable when changes of sphere of influence were involved ([#1728](https://github.com/mockingbirdnest/Principia/issues/1728)).

For more details see all [36](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-03-15T23%3A00%3A00..2018-04-08T23%3A59%3A59+sort%3Acreated-asc) pull requests between Cramer and Coxeter.

# [Coxeter](https://en.wikipedia.org/wiki/Harold_Scott_MacDonald_Coxeter)

## User-facing features

* The performance of all the code having to do with numerical analysis (including some of the integrators) has been significantly improved, with benchmarks demonstrating a speed-up of up to 2×.  In particular:
  -  operations involving 3-dimensional vectors, linear algebra and square roots are now implemented using the Intel SSE2 intrinsics to take advantage of SIMD instructions;
  - some costly usages of heap storage and of `std::pow` have been removed.
* The velocities for symmetric linear multistep integrators (used with Real Solar System) are now computed from the accelerations and two positions, instead of being purely computed by a difference formula on the positions. This is more accurate, and it is also significantly cheaper, since it can be done without double-double precision.
* KSP 1.2.2, 1.3.1 and 1.4.1 are supported by this version. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).  Thanks to [@aw1621107](https://github.com/aw1621107) for the 1.4.1 support.

## Bug fixes

* A bug has been fixed where trajectories in frames tied to Pol and Bop would appear horribly wiggly and Pol and Bop would exhibit hourly oscillations ([#1741](https://github.com/mockingbirdnest/Principia/issues/1741)).  This has been addressed by using a different integrator (Blanes-Moan) for the KSP system, which is more resilient to the instabilities present in the Jool system.  For the real solar system we are still using a Quinlan-Tremaine integrator as there are no stability issues and this integrator yields more accurate results.  Note that the benefits of the Blanes-Moan integrator will only be visible if you create a new save.

## Modder-facing changes

* An entry point named `ExternalGetNearestPlannedCoastDegreesOfFreedom` has been added to our API to help mods which want to implement closed-loop guidance ([#1659](https://github.com/mockingbirdnest/Principia/issues/1659) and [#1729](https://github.com/mockingbirdnest/Principia/issues/1729)).

For more details see all [30](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-02-11T23%3A00%3A00..2018-03-15T22%3A59%3A59+sort%3Acreated-asc) pull requests between Cohen and Coxeter.

# [Cohen](https://en.wikipedia.org/wiki/Paul_Cohen)

## User-facing features

* The computation of the positions and velocities of the celestials has been changed.  We used to use the Clenshaw method for polynomials expressed in the Чебышёв basis, we are now using the Estrin method for polynomials expressed in the monomial basis.  This brings up a 30% speed-up at a modest cost in interpolation accuracy (centimetres).

## Bug fixes

* A bug has been fixed where the Principia main window would sometimes be saved off-screen and would be impossible to bring back on screen ([#1677](https://github.com/mockingbirdnest/Principia/issues/1677)).  This has been addressed by making sure that all Principia windows stay on screen by 50 pixels.

* A bug has been fixed where Principia would crash when a vessel collides with a celestial at high warp ([#1703](https://github.com/mockingbirdnest/Principia/issues/1703)).  We now properly detect the collision and refrain from compressing the trajectory as it may be chaotic.

## Miscellaneous

* On Windows, Principia is now distributed as a set of fives DLLs instead of one.  While we don't expect that this will have any effect on users (you'll still install Principia by dropping the `Principia` folder in the `GameData` folder) we anticipate that it will make it easier to optimize the code using profile-guided optimization.

For more details see all [36](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2018-01-13T22%3A59%3A00..2018-02-11T22%3A59%3A00+sort%3Acreated-asc) pull requests between Clifford and Cohen.

# [Clifford](https://en.wikipedia.org/wiki/William_Kingdon_Clifford)

## User-facing features

No new features in this version.  We have been on vacation, and have focused on some deep restructuring for future changes.

## Bug fixes

* A bug has been fixed in double precision subtraction of `Point`s which could have led to small inaccuracies in some computations ([#1624](https://github.com/mockingbirdnest/Principia/issues/1624)).  

## Modder-facing changes

* When building a gravity model, it is now possible to specify the integrator to use and its time step.  The default integrator has been tuned for our solar system, but is not guaranteed to be conservative, especially for systems that are not very stable.  By specifying a different integrator or time step, it is possible to ensure energy conservation at the expense of more costly computations.

## Astronomy

* We started looking into the possibility of building a model of the extrasolar system TRAPPIST-1.  More work is required, but we expect to be able to include this in a future release.

## Numerics

* We are investigating switching from the Clenshaw method of evaluating polynomials expressed in the Чебышёв basis to the Estrin method for polynomials expressed in the monomial basis, as the latter seems significantly faster.  This might show up in a future release.

For more details see all [17](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2017-12-16T17%3A00%3A00..2018-01-13T22%3A59%3A00+sort%3Acreated-asc) pull requests between Christoffel and Clifford.

# [Christoffel](https://en.wikipedia.org/wiki/Elwin_Bruno_Christoffel)

## User-facing features

* Vessels going through a celestial body will now correctly be destroyed, even at high time warp.
* The capability to start and stop the Principia plugin has been removed.  While it was useful at the beginning of the development of Principia when the code was unstable, it had overlived its usefulness and was causing crashes.  It is nowadays critical for Principia and KSP to stay in sync so Principia must be constantly running.
* As announced previously, KSP 1.3.0 is no longer supported.  Principia only works with KSP 1.2.2 and 1.3.1.

## Bug fixes

* Principia used to show, when in the tracking station, the trajectory of the last targetted vessel in addition to the trajectory of the active vessel.  This has been fixed by removing the trajectory of the target in this situation ([#1620](https://github.com/mockingbirdnest/Principia/issues/1620)).
* Principia would sometimes crash when timewarping in the space centre ([#1628](https://github.com/mockingbirdnest/Principia/issues/1628)).  The root cause was that the vessel would go through a celestial and KSP would not detect the collision because of timewarping.  Our integrator would however fail to conserve energy and start to oscillate because the vessel was temporarily too close to the gravitational singularity at the centre of the celestial.  To fix this rather complex bug we had to:
  * replace the Adams-Moulton integrator by a finite difference computation to evaluate the velocities;
  * determine during the force computation if a vessel moves inside a celestial and propagate this information all the way to KSP to kill the vessel;
  * change the downsampling of histories to make it more resilient to failures to downsample.
* When using EditorTime in conjunction with Principia, a crash could occur when waiting more than the maximum history length before launching.  This has been fixed by managing the histories based on the actual time of the Principia plugin ([#1641](https://github.com/mockingbirdnest/Principia/issues/1641)).

For more details see all [25](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-11-15T22%3A00%3A00..2017-12-16T16%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between 陈景润 and Christoffel.

# [陈景润](https://en.wikipedia.org/wiki/Chen_Jingrun)

## User-facing features

* A longstanding problem has been fixed, making the saves smaller and the histories smoother.  Previously, one point was retained every 10 seconds in the history, which would cause the saves to become uncomfortably large after playing for some time.  When warping, we could not afford to retain one point every 10 seconds (the history would have grown to gigabytes) so we opted for only retaining a point "once in a while"; the unfortunate consequence was that the history produced by warp would be drawn incorrectly, with spikes and loops and other nonphysical artifacts.  All these issues have been fixed by intelligently downsampling the history to make its size much smaller while retaining the accuracy necessary to draw it ([#228](https://github.com/mockingbirdnest/Principia/issues/228)).
* This is the last version to support KSP 1.3.0.  The next version will only support KSP 1.2.2 and 1.3.1.

## Bug fixes

* Principia would sometimes crash when switching the camera from the Sun to a vessel when the velocity or altitude were extremely large.  This was due to a subtle bug in the integrator used to compute the prediction, which caused it to lose a small amount of accuracy when computing the times at which the integration takes place ([#1595](https://github.com/mockingbirdnest/Principia/issues/1595)).

* Principia would sometimes crash when a vessel was trying to leave the surface.  This was fixed by properly detecting the case where KSP does not have a collider yet ([#1618](https://github.com/mockingbirdnest/Principia/issues/1618)).

* Deleting the last manœuvre in the flight planner sometimes caused the bottom of the flight planning window to vanish off the top of the screen.  The window was no longer accessible and there was no way for the user to drag it back on-screen.  This has been fixed by making sure that some part of the window always remains on-screen ([#1609](https://github.com/mockingbirdnest/Principia/issues/1609)).  (Thanks to [@aw1621107](https://github.com/aw1621107) for the fix.)

For more details see all [12](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-10-14T13%3A59%3A00..2017-11-15T21%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Chasles and 陈景润.

# [Chasles](https://en.wikipedia.org/wiki/Michel_Chasles)

## User-facing features

* On celestials that don't have an atmosphere, Principia is now able to manage the vessels even when KSP uses a rotating reference frame, all the way down to the ground.  This is the final resolution of issues that has been annoying players for some time as it was virtually impossible to land on mountains (see for example [#1413](https://github.com/mockingbirdnest/Principia/issues/1413), [#1440](https://github.com/mockingbirdnest/Principia/issues/1440), and [#1591](https://github.com/mockingbirdnest/Principia/issues/1591)).  As soon as a vessel touches the ground, Principia hands it over to KSP.  As soon as it leaves the ground, Principia takes control again.  This means that if, for instance, you have a Kerbal frolicking on Minmus, when she jumps and leaves the ground Principia will apply full N-body gravitation until she hits the ground again.

    We plan to do this for celestials that have an atmosphere in a future release, but this requires some synchronization with the releases of [Ferram Aerospace Research](ferram4/Ferram-Aerospace-Research).

* KSP 1.2.2, 1.3.0 and 1.3.1 are supported by this version. Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).

## Bug fixes

* With KSP 1.3, the trajectory markers (apsides, nodes, target approaches) would sometimes get nonsensical multiple labels, e.g. [an apoapsis marker labelled all of "Ap", "AN", and "DN"](https://i.imgur.com/P2Zx7wt.png).  Principia no longer attempts to reuse the `MapNode` objects if the marker type changes, which fixes this.

* Principia would sometimes crash when starting to warp.  While the problem has not been completely elucidated, this is believed to be caused by a violated invariant in predictions.  The management of predictions has been extensively rewritten to enforce stronger invariants ([#1561](https://github.com/mockingbirdnest/Principia/issues/1561)).

* Pressing a non-expanding button on the plotting frame UI would raise (and log) an exception.  This has been fixed by properly handling the celestials that don't have satellites ([#1532](https://github.com/mockingbirdnest/Principia/issues/1532)). 

* A number of compilation warnings emitted by Clang have been fixed, which should make the code easier to port and more correct.  (Thanks to [@aw1621107](https://github.com/aw1621107) for numerous pull requests.)

For more details see all [35](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-09-17T00%3A00%3A00..2017-10-14T13%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cesàro and Chasles.

# [Cesàro](https://en.wikipedia.org/wiki/Ernesto_Ces%C3%A0ro)

## User-facing features

* The history of the vessels is now integrated on multiple threads, one per vessel.  This brings significant performance gains on multi-core processors.  This is particularly visible when warping at 1 000 000× and above with multiple vessels.  Note that the asteroids are vessels from the perspective of KSP, so most game situations actually have many vessels.  (This improvement does not apply to macOS because Apple did not support `shared_mutex` prior to 10.12.)

## Bug fixes

* Principia might die when crashing a vessel into another.  This has been fixed by detecting that some parts are in the process of being destroyed and ignoring them in the physics computations ([#1553](https://github.com/mockingbirdnest/Principia/issues/1553)).

* An incompatibility between Principia and Kerbal Inventory System (KIS) which caused Principia to crash has been fixed in KIS, thanks to [@ihsoft](https://github.com/ihsoft) ([#1549](https://github.com/mockingbirdnest/Principia/issues/1549) and [KIS #221](https://github.com/ihsoft/KIS/issues/221)).

For more details see all [24](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-08-13T21%3A00%3A00..2017-09-16T23%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Чебышёв and Cesàro.

# [Чебышёв](https://en.wikipedia.org/wiki/Pafnuty_Chebyshev)

## User-facing features

* The speed of trajectory plotting (the main performance issue in previous versions of Principia) has been increased considerably (of the order of 5× to 10× faster) by implementing our own plotting of trajectories.  By cleverly choosing the segments to draw we are able to spend less time drawing or processing the trajectory, while at the same time making the trajectories much smoother (no more angles in the prediction, in particular).  This addresses numerous user complaints, for instance [#1487](https://github.com/mockingbirdnest/Principia/issues/1487).

* Support for tracking burns has been added.  These are burns where the force stays tangent to the trajectory instead of being applied in a fixed direction ([#876](https://github.com/mockingbirdnest/Principia/issues/876)). This is a significant improvement in usability for long, low-thrust burns, which are frequent in RealSolarSystem.

* Both KSP 1.2.2 and KSP 1.3 are supported by this version.  Make sure you download the correct binary for your favourite version of KSP (the game will crash otherwise).

## Bug fixes

* The plotting frame would revert to 'body-centred inertial' when reverting to launch.  This has been fixed by correctly keeping track of the display mode ([#1453](https://github.com/mockingbirdnest/Principia/issues/1453)).

* The performance in the space centre view was very poor.  This was a regression introduced in Cayley and it has been fixed by avoiding frequent calls to find the tracking station ([#1486](https://github.com/mockingbirdnest/Principia/issues/1486)).

For more details see all [40](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-07-21T22%3A00%3A00..2017-08-13T20%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cayley and Чебышёв.

# [Cayley](https://en.wikipedia.org/wiki/Arthur_Cayley)
## User-facing features

* Vessel trajectories are now displayed for the selected vessel in the tracking station ([#1457](https://github.com/mockingbirdnest/Principia/issues/1457)).

* The colour of the horizon in the inertial frame navball has been changed to use "horizon blue" instead of "dark dark blue".  This makes the manœuvre marker more readable, as it happened to have the same colour as the horizon band, see [#1449](https://github.com/mockingbirdnest/Principia/issues/1449).

* A reminder has been added in the UI when it's time to update Principia because a new moon has passed.

* The release we distribute now includes the Macintosh version.

## Bug fixes

* Since KSP 1.2, the parts of unpacked vessels are lagging behind the current time (and the parts of loaded packed vessels), instead of the orbits being ahead of the current time. This challenged some assumptions made by Principia, and was the root cause of many bugs (including bugs worked around in previous versions), such as [#1272](https://github.com/mockingbirdnest/Principia/issues/1272), [#1416](https://github.com/mockingbirdnest/Principia/issues/1416), [#1441](https://github.com/mockingbirdnest/Principia/issues/1441), and [#1473](https://github.com/mockingbirdnest/Principia/issues/1473), as well as mysterious and worrying errors in the logs. This was fixed by advancing vessels in time when KSP expects them to be advanced.

* In some circumstances KSP would report a collision with a null collider, which confused Principia and caused a crash ([#1447](https://github.com/mockingbirdnest/Principia/issues/1447)). This has been fixed by ignoring such collisions.

* A Kerbal in EVA would sometimes be spawned several metres away from the vessel.  This is because in this case the Kerbal ignores collisions with the ship for a little while, and is nudged back to the airlock.  This nudging conflicted with the nudging done by Principia ([#1452](https://github.com/mockingbirdnest/Principia/issues/1452)).

* A crash would occur when a Kerbal on EVA was unloaded.  This has been fixed by better checking the state of the EVA controller ([#1466](https://github.com/mockingbirdnest/Principia/issues/1466)). This issue was not in Cauchy, since it was introduced in pull request [#1459](https://github.com/mockingbirdnest/Principia/issues/1459), but it affected at least one user who built from master between releases.

## Library changes

* Support has been added for efficiently computing the parts of a segment hidden by a sphere.  This is a significant step towards the goal of making the rendering of trajectories faster and smoother.

For more details see all [16](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-06-17T12%3A30%3A00..2017-07-21T21%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cauchy and Cayley.

# [Cauchy](https://en.wikipedia.org/wiki/Augustin-Louis_Cauchy)

## User-facing features

* The speed of the vessel in the plotting frame is now shown on the periapsis, apoapsis, and locally closest approach markers. The speed normal to the reference plane is shown on the ascending/descending node markers.  This helps in particular when tuning approaches and rendezvous.

* The speed display mode (surface vs. orbit) has been unified with our reference frame selection: the speed display is in surface mode if and only if the surface frame (Body-Centred Body-Fixed) is selected.

* The speed displayed on the navball is always the speed of the vessel in the plotting frame, even when the vessel is not being managed by Principia.

* The nodes—intersections with the reference (orbit) plane—are now displayed in the body-centred parent-aligned and barycentric rotating frames; this should make interplanetary flight planning easier.

* The trajectory of the target vessel is now rendered in reference frames where the target is not fixed. Its history is goldenrod, and its prediction is pig pink.

* The UI has been make a bit simpler and smaller by removing useless information about the state of the plugin.

* For compatibility with 3rd party mods that require celestial targeting for some of their features, it is now possible to target a celestial. This has no interaction with Principia, in particular it is independent from reference frame selection: it exists solely for compatibility. 

## Bug fixes

* Vessels would sometimes slowly rotate away from the closest celestial, even if no torque had been previously applied.  This has been fixed by making the positions and transforms passed to Unity consistent ([#1307](https://github.com/mockingbirdnest/Principia/issues/1307)).

* Switching vessels via the Principia UI would sometimes lock the menu and the map view.  This has been fixed by clearing the lock at the proper place ([#1402](https://github.com/mockingbirdnest/Principia/issues/1402)).

* A spurious change of velocity would sometimes show up as a result of quick-loading.  For instance, when quick-loading in atmospheric flight around Kerbin, the speed would jump by 200 m/s, which is the surface speed of Kerbin.  This was due to vessels being temporarily registered as in orbit on rails, and thus managed by Principia, which would set speeds in the nonrotating frame which were then interpreted in the rotating frame when KSP picked them up as flying.  Principia now keeps managing these vessels to avoid the problem ([#1410](https://github.com/mockingbirdnest/Principia/issues/1410)).

* A vessel would sometimes accelerate when a Kerbal was performing an EVA.  This boils down to ladders being magic in KSP, as illustrated by this hilarious [video](https://www.youtube.com/watch?v=-THq8Gip-Us).  When a Kerbal holds a ladder, that ladder exerts on the Kerbal a force equal to its weight, even if the Kerbal is in weightlessness. When the Kerbal lets go of the ladder, that force goes down to zero.  This was fixed by ignoring the magic ladder force ([#1415](https://github.com/mockingbirdnest/Principia/issues/1415)).

* Some parts would sometimes be offset from their expected position on the launch pad.  This was due to the vessel being in the "prelaunch" state for a few frames, and has been fixed by having Principia wait until it exits that state ([#1421](https://github.com/mockingbirdnest/Principia/issues/1421)).

* Reading saves that had long trajectories would sometimes crash because data structures for the oldest parts of the trajectories would become corrupted.  This has been fixed, and the saves that had this problem in Catalan should be loadable again in Cauchy ([#1422](https://github.com/mockingbirdnest/Principia/issues/1422)).

* Principia would sometimes crash if a save was happening at the same time as exiting physical time warp.  This has been fixed by making sure that the plugin doesn't do any integration if its time is before that of the vessel trajectories ([#1441](https://github.com/mockingbirdnest/Principia/issues/1441)).

* Markers, in particular for apoapsides and periapsides, would sometimes be drawn in the middle of nowhere (i.e., not on the trajectory).  This was due to a data corruption in the vessel trajectories ([#1395](https://github.com/mockingbirdnest/Principia/issues/1395)).

* Landing on the Moon with RealSolarSystem was sometime problematic.  This has been fixed in RealSolarSystem by raising the minimum timewarp altitude ([#1440](https://github.com/mockingbirdnest/Principia/issues/1440)).

## Library changes

* Some support has been added for projective geometry and pinhole camera perspective.  This will allow us in the future to make the rendering of trajectories faster and smoother.

For more details see all [40](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-05-21T12%3A00%3A00..2017-06-17T11%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Catalan and Cauchy.

# [Catalan](https://en.wikipedia.org/wiki/Eug%C3%A8ne_Charles_Catalan)

## User-facing features

No new features in this version, we have focused on fixing bugs, repaying technical debt and doing code restructuring that will be necessary for implementing new features in the future.

## Bug fixes

* When using BetterTimeWarp, the game would crash when trying to do an EVA after landing on a celestial with no atmosphere (such as Mün).  This has been fixed by tweaking the manageability altitude of the vessel ([#1345](https://github.com/mockingbirdnest/Principia/issues/1345)).

* When using BetterTimeWarp, and trying to land on a celestial with no atmosphere, the vessel would sink below the ground, or the celestial surface would jitter, making it hard or impossible to land.  This has been fixed by the same change as the previous bug ([#1346](https://github.com/mockingbirdnest/Principia/issues/1346)).

* When transitioning from space to the atmosphere of a planet (such as Kerbin) the velocity would sometimes increase by the velocity of the surface (200 m/s on Kerbin).  This has been fixed by setting the degrees of freedom in the proper frame during the transition ([#1366](https://github.com/mockingbirdnest/Principia/issues/1366)).

* The planets would sometimes be moving back and forth along their trajectory, or even leave it.  This seemed more likely to happen with a custom solar system that has a double planet.  This has been fixed by asking KSP to properly update the positions ([#1369](https://github.com/mockingbirdnest/Principia/issues/1369)).

* The radial-in and radial-out direction of the autopilot were inverted when in space.  This boiled down to a confusion in KSP where the radial-in icon sets the autopilot to radial-out and vice-versa.  Principia has been modified to compensate for this ([#1370](https://github.com/mockingbirdnest/Principia/issues/1370)).

* The Apocalypse window would freeze the UI.  This problem had been reported in Cardano but we couldn't reproduce it at the time.  We have now been able to reproduce it and to fix it ([#1319](https://github.com/mockingbirdnest/Principia/issues/1319), [#1376](https://github.com/mockingbirdnest/Principia/issues/1376)).

* A `NullReferenceException` would sometimes be propagated to KSP and result in an error message in the logs and the UI.  This has been fixed by properly checking for null pointers in the C♯ code ([#1380](https://github.com/mockingbirdnest/Principia/issues/1380)).

## Library changes

* It is now possible to describe a solar system using a data file containing [keplerian coordinates](https://github.com/mockingbirdnest/Principia/blob/2017052520-Catalan/astronomy/kerbol_initial_state_0_0.proto.txt) (cartesian coordinates have been supported for a long time).

* Date literals can now be written as [Julian](https://github.com/mockingbirdnest/Principia/blob/2017052520-Catalan/astronomy/time_scales_test.cpp#L363) or [Modified Julian](https://github.com/mockingbirdnest/Principia/blob/2017052520-Catalan/astronomy/time_scales_test.cpp#L368) dates, which are convenient when describing astronomical phenonema.

* Orbits may now be described using a large variety of [keplerian elements](https://github.com/mockingbirdnest/Principia/blob/2017052520-Catalan/physics/kepler_orbit.hpp#L27) which obviates the need to perform offline computations to transform the characteristics of a body into something acceptable by Principia. Note that while it is possible to specify a large number of combinations of elements, the computations are numerically quite naïve, and may be result in large errors near singularities.

For more details see all [28](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-04-23T11%3A59%3A00..2017-05-21T11%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cartan and Catalan.

# [Cartan](https://en.wikipedia.org/wiki/%C3%89lie_Cartan)

NOTE: Cartan is save-compatible with Cardano.  However, existing saves won't take advantage of the faster integrators.  You'll need to create a new save to see the speed-up.

## User-facing features

* Principia now supports a vessel-centred frame directed along the horizontal and the vertical of a celestial.  This is useful for performing rendezvous.  The points of closest approach and the points where the active vessel crosses the plane of the target vessel trajectory are displayed on the prediction and flight plan.  See the description of plotting frames in the [Concepts](https://github.com/mockingbirdnest/Principia/wiki/Concepts) document and our [guide to rendezvous](https://github.com/mockingbirdnest/Principia/wiki/A-guide-to-performing-low-orbit-rendezvous/3bb254e1378bcba1c014a5990eec15c3ae5eb17d) for details regarding the use of this frame.

* The integrators used for computing the positions of the celestials and the histories of the vessels have been changed.  We now use symmetric linear multistep integrators instead of symplectic Runge-Kutta-Nyström integrators.  The former are conjugate-symplectic, which is nearly as good as symplectic, and they produce much denser output.  As a consequence the integration of the celestials is much more precise (errors in the meters per year instead of thousands of kilometers) and the integration of the vessels is about 5 times faster.  Warping at 100 000× is completely smooth even with 20 vessels, and warping at 1 000 000× is janky but usable.

## Bug fixes

* The stabilization of the Jool system that was introduced in Brouwer got lost in Cardano, causing an Apocalypse in some situations.  This has been fixed ([#1319](https://github.com/mockingbirdnest/Principia/issues/1319)).

* A crash might happen during EVA if the unfortunate Kerbal would touch a non-physically-significant part, such as a barometre.  This has been fixed by going up the part tree until a physically-significant part is found ([#1308](https://github.com/mockingbirdnest/Principia/issues/1308)).

* A crash might happen when warping from the sphere of influence of a celestial to that of another, especially if the second celestial is large (e.g., Kerbol).  This has been fixed by properly detecting the change of sphere of influence ([#1302](https://github.com/mockingbirdnest/Principia/issues/1302)).

* Creating a manœuvre with the reference frame fixing the centre of a celestial and the line towards another celestial (e.g. Earth-Centred Sun-Aligned, ECSA) would systematically cause a crash ([#1293](https://github.com/mockingbirdnest/Principia/issues/1293)).

* In some cases Principia would lose track of a vessel and then find it again, but it would be confused about its sphere of influence.  Combined with the tilt this might cause strange drifts ([#1299](https://github.com/mockingbirdnest/Principia/issues/1299)).  

For more details see all [50](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2017-03-25T17%3A00%3A00..2017-04-23T11%3A59%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cardano and Cartan.

# [Cardano](https://en.wikipedia.org/wiki/Gerolamo_Cardano)

**WARNING: Cardano is *not* save-compatible with previous versions of Principia.  If you have a game saved with Cantor or earlier, it won't load (or it will crash) if you try to use it in Cardano.**

## User-facing features

* Principia now works with KSP version 1.2.2.  Older versions of KSP are no longer supported ([#1150](https://github.com/mockingbirdnest/Principia/issues/1150), [#1237](https://github.com/mockingbirdnest/Principia/issues/1237), [#1244](https://github.com/mockingbirdnest/Principia/issues/1244)).

* Celestials may now have proper axial tilt and rotation.  This is particularly useful when using RealSolarSystem.  For instance, the [rings of Saturn](http://i.imgur.com/I5DqakT.png) are (correctly) shown in the same plane as its satellites.  Previously they would show up as being in the plane of Earth's equator, at an angle from the satellites.  Similarly the [lightning of the Earth](http://i.imgur.com/LknBHOL.png) correctly reflects the seasons.

* Two new plotting frames have been added:
  * A frame centred on a body and directed towards a second body.
  * A frame centred on a body and rotating with the surface of that body.  For that frame, the navball tracks the surface and is oriented North-East-Down.

* The handling of the physics bubble has been completely rewritten to take advantage of the new features of KSP version 1.2.x.  Unless engines (including RCS) are thrusting, a vessel will follow its free-falling trajectory regardless of whether or not it is timewarping.

## Bug fixes

* When using an unstable solar system, the "apocalypse" that occurs when two celestials collide is now reported in the UI instead of causing a mysterious crash ([#1114](https://github.com/mockingbirdnest/Principia/issues/1114), [#1115](https://github.com/mockingbirdnest/Principia/issues/1115)).

* The rewrite of the physics bubble fixed several bugs:
  * The phantom accelerations which sometimes prevented warping are gone ([#1138](https://github.com/mockingbirdnest/Principia/issues/1138)).
  * The gravitational acceleration is now calculated for each vessel, not for the centre of mass of the loaded vessels.  This fixes problems where accelerations would be incorrect on some vessels, resulting in jumps and sudden shifts of the gravity vector ([#1048](https://github.com/mockingbirdnest/Principia/issues/1048)).

## Library changes

* Implemented [symmetric linear multistep integrators](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/symmetric_linear_multistep_integrator.hpp) (not used in this release).
* Ported the [symplectic partitioned Runge-Kutta integrators](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/symplectic_partitioned_runge_kutta_integrator.hpp) (more general than the symplectic Runge-Kutta-Nyström integrators), including [leapfrog, which appears in Newton's *Principia*](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/symplectic_partitioned_runge_kutta_integrator.hpp#L108-L133), to a form compatible with the implementation used for the existing [symplectic Runge-Kutta-Nyström integrators](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/symplectic_runge_kutta_nystr%C3%B6m_integrator.hpp).
Principia's `integrators` library now has 37 different fixed step conjugate-symplectic and symplectic integrators.
* Integrators are now based on [`Instance`s](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/integrators/ordinary_differential_equations.hpp#L136-L167), which hold any persistent state that the integrator might need in addition to the state of the system; this is important for resumability of multistep or variable-step integrators.
* Constructors of `Rotation`s from [Euler angles and (appropriately for this release) Cardano angles](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/geometry/rotation.hpp#L44-L62) have been added. These are used in [pre-existing code](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/physics/kepler_orbit_body.hpp#L217-L220) (Keplerian elements) as well as for the rotations defining [the surface frame of celestials](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/physics/rotating_body_body.hpp#L99-L104), used to implement axial tilt.
* Implemented a proper [double-double addition](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/numerics/double_precision_body.hpp#L203-L210), since the (pre-existing) [compensated summation](https://github.com/mockingbirdnest/Principia/blob/61b5bb7b2453b21c34c8463254f7fee3b8d1d7d9/numerics/double_precision_body.hpp#L51-L60) was not up to the task of the ill-conditioned sum in linear multistep integrators.

## Astronomy

* We had noticed that we were not able to predict very precisely the position of some small bodies of the solar system, so we made a thorough analysis of the behaviour of Phobos.  It turns out that the spherical harmonics *C*₂₂ and *S*₂₂ of Mars have a considerable influence on the orbit of its satellites.  Unfortunately, adding them to our model would, as things stand, make the game too slow, and was too complex for implementation in Cardano.  We'll try to improve this in the future, maybe by using symmetric linear multistep integrators.
* We analysed [the dynamical stability of the retrobop system](https://github.com/mockingbirdnest/Principia/wiki/On-the-dynamical-stability-of-Principia's-modified-Jool-system), noticing that it is highly chaotic.

We have not released for 8 months.  Going forward, we plan to release more often, even if that means making smaller changes in each release.  We'll try to have a new release coincident with each new moon.

For more details see all [166](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2016-07-23T18%3A59%3A59..2017-03-25T17%3A00%3A00+sort%3Acreated-asc&utf8=%E2%9C%93) pull requests between Cantor and Cardano.

# [Cantor](https://en.wikipedia.org/wiki/Georg_Cantor)

[And we're out of β, we're releasing on time!](https://www.youtube.com/watch?v=Y6ljFaKRTrI)  We believe that the mod as now sufficiently functional and stable to be fun to play with, so we are making it more broadly available.  Download it [here](https://goo.gl/eZbr4e).

## User-facing features

* When using stock KSP, the clock now properly uses 6-hour days instead of 24-hour days ([#1085](https://github.com/mockingbirdnest/Principia/issues/1085)).

## Library changes

* Implemented date and time literals that are interpreted at compile time. Using these, [four time scales](https://github.com/mockingbirdnest/Principia/blob/2016081314-Cantor/astronomy/time_scales.hpp#L31-L34) are available to write [`Instant` literals, again interpreted at compile time](https://github.com/mockingbirdnest/Principia/blob/2016081314-Cantor/astronomy/time_scales_test.cpp#L78-L101): *Temps Terrestre* (TT), *Temps Atomique International* (TAI), Coordinated Universal Time (UTC), and UT1. [The dates in the lunar eclipse tests now use UT1 literals](https://github.com/mockingbirdnest/Principia/blob/2016081314-Cantor/astronomy/lunar_eclipse_test.cpp#L243-L248). Since Principia does not support general relativity, and has a unified `Instant` type for the time coordinate, *Temps Dynamique Barycentrique* (TDB), which is used for the ephemerides of the solar system, is identified with TT, and *Temps-Coordonnée Géocentrique* (TCG) and *Temps-Coordonnée Barycentrique* (TCB) are not supported.

For more details see all [8](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2016-06-26T19%3A00%3A00..2016-07-23T18%3A59%3A59+sort%3Acreated-asc) pull requests between بوژگانی and Cantor.

# [بوژگانی](https://en.wikipedia.org/wiki/Abu_al-Wafa%27_Buzjani)

## User-facing features

* Principia now works with KSP version 1.1.3.  Older versions of KSP are no longer supported.
* The times of periapsides and apoapsides are now displayed on the trajectories.
* The norm of the velocity in the plotting frame is displayed when the navball is fixed in the plotting frame.
* The check that the C++ 2015 Redistributable runtime is properly installed on Windows has been tightened.

## Modder-facing changes

* The state of the ephemeris at startup is now logged to help in debugging modified solar systems.
* The fix that prevents the Jool system from getting unstable is now applied more strictly, so that modified stock solar system don't get clobbered by this fix.
* Gravity models may now be specified using Keplerian elements (in addition to Cartesian elements).

## Bug fixes

* An obscure bug has been fixed that would infrequently cause the trajectories of the celestials to be discontinuous because of cancellations in Чебышёв series.
* Fixed a bug where the vessels would take a hard turn when the sphere-of-influence changes ([#1053](https://github.com/mockingbirdnest/Principia/issues/1053)).

## Known issues

* The release name, being in Farsi, is written right-to-left.  KSP doesn't know how to do such an advanced thing, so it shows up inverted in the UI.  Apologies to Farsi speakers.

For more details see all [33](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2016-05-20T21%3A00%3A00..2016-06-26T18%3A59%3A59+sort%3Acreated-asc) pull requests between Burnside and بوژگانی.

# [Burnside](https://en.wikipedia.org/wiki/William_Burnside)

## User-facing features

* Changed the prediction parameters to be per vessel as opposed to global.  Thus, different vessels may have predictions of different lengths or accuracies.
* Changed the way that the trajectories of celestials are recorded in saves: instead of recording everything that was computed in the course of the game, only the next 6 months or so are saved.  The rest is recomputed when the save is loaded.  The advantage is that the saves are considerably smaller (a factor of 100x has been observed in simple games) which makes choosing a save in KSP faster as it insists on loading all the saves in memory.  The drawback is that loading a save is more CPU-intensive and may therefore take longer.
* The plugin has a new icon.

## Bug fixes

* Fixed the stabilization of the Jool system in the stock game which had stopped working in Буняковский.  This is the hotfix previously released as *Буняковский 6*.
* Fixed a situation where adaptive step integration would crash when the system was already integrated to the desired final time ([#1024](https://github.com/mockingbirdnest/Principia/issues/1024)).
* Fixed a problem where the start of a flight plan would be discarded to the point that it had no burns anymore and various pieces of the code would disagree as to whether the vessel still had a flight plan ([#1022](https://github.com/mockingbirdnest/Principia/issues/1022), [#1023](https://github.com/mockingbirdnest/Principia/issues/1023)).

For more details see all [16](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2016-05-05T16%3A00%3A00..2016-05-20T21%3A59%3A59+sort%3Acreated-asc) pull requests between Буняковский and Burnside.

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

For more details see all [75](
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
* When using stock, the Jool system is modified, cancelling the apocalypse. Specifically, we make the inner Jool system nonresonant, since we have been unable to replicate the results (Manley, priv. comm.) according to which some interpretations of the orbital elements yielded a stable Laplace resonance, despite systematic searches of the Jacobi osculating elements. In addition, at [Scott Manley](https://www.youtube.com/user/szyzyg)'s and [@pdn4kd](https://github.com/pdn4kd)'s suggestion, we put Bop in a surprisingly stable, though highly precessing, retrograde orbit. The modified system is stable for upwards of a century.
* Flight planning has been implemented.

## Modder-facing changes

* When a Cartesian initial state cfg is not given, the KSP orbital elements are interpreted in a hierarchical osculating Jacobi fashion; for instance, the orbital elements of Jool are the osculating elements at game start of the orbit of the barycentre of the Jool system around the barycentre of the (sun, moho, eve, gilly, kerbin, mun, minmus, duna, ike, dres) system; the elements of Laythe are the osculating elements at game start of the orbit of Laythe around Jool; the elements of Vall are the osculating elements at game start of the orbit of Vall around the Laythe-Jool barycentre.

## Optimizations

* The Windows build now uses profile-guided optimization (we estimate that this improves performance by ~20%); in theory this could be extended to other platforms.
* The evaluation of the Чебышёв series has been significantly optimized.
* [@sarbian](https://github.com/sarbian) made trajectory rendering faster (as he pointed out, there is still lots of room for improvement).

## Library changes

* Everything that crosses the C++/C# interface can now be journalled if the right flag is set, allowing us to replay the C++ side of a session; this is useful for tracking down tricky bugs, and it enables profile-guided optimization.
* In order to get the full Frenet trihedron, (which was needed for manœuvres, since the Δv is defined in the Frenet frame at the point of ignition) geometric acceleration (the acceleration of a free-falling trajectory) in any reference frame was needed. To do that we created two abstractions, RigidMotion, the derivative of a RigidTransformation, and DynamicFrame, the definition of an arbitrary reference frame. The navigation frames (the frames in which the trajectory is drawn, or with which the manœuvres are defined) implement that (see BodyCentredNonRotatingDynamicFrame and BarycentricRotatingDynamicFrame).
* In order to interpret the orbital elements of KSP in the hierarchical Jacobi fashion described above, support was added for Kepler orbits (implementation), Jacobi coordinates, and hierarchical systems.
* Discrete trajectories were reworked, with a heavy dose of CRTP.
* In preparation for the surface frame in the future, RotatingBody was added.
* The C++ interface headers and C# extern declarations were repetitive and error-prone, this was exacerbated by the addition of journalling code and replaying code, so a generator was written to produce all of that from an annotated proto.
* [@pdn4kd](https://github.com/pdn4kd) contributed some tests of lunar eclipse timings.
* For both Kepler orbits and lunar eclipse timings, a simple root finder was needed, bisection does the job for now.
* A bibliography was written, at [@pdn4kd](https://github.com/pdn4kd)'s request (it is somewhat out of date).
* SolarSystem, a class for initializing ephemerides from protobuf text format configuration files for testing purposes was written.
* A script for generating the initial state configuration files from the emails sent by JPL's HORIZONS system was written (the gravity model configuration file is hand-curated).
* An utility turns the protobuf text format configuration files into KSP ModuleManager configuration files for RSS support.
* Various geometric utilities were added: angles (implementation), spherical coordinates (more are needed).
* More C++11/14 features were used as they became available (for instance, the units are now constexpr), in addition we now use std::experimental::optional.
* C++14-related improvements were made to not_null.

For more details see all [195](https://github.com/mockingbirdnest/Principia/pulls?q=is%3Apr+is%3Aclosed+merged%3A2015-08-15T15%3A00%3A00..2016-02-09T22%3A00%3A00+sort%3Acreated-asc) pull requests between Bourbaki and Brouwer.

# [Bourbaki](https://en.wikipedia.org/wiki/Nicolas_Bourbaki)

## User-facing features

* Ephemeris: the celestial bodies are integrated on their own, with their own (much larger) timestep (45 min);
their trajectories are then fitted using чебышёв series, yielding continuous trajectories. This means that when there are no vessels (including asteroids, see the FAQ), timewarp at very high speed (6'000'000x was tested in RealSolarSystem) is smooth.
* The predictions are computed using an adaptive step size, so they're faster and less fiddly (you still get a tolerance setting, but it doesn't need as much attention as the step size setting; the step size will shorten near periapsis and lengthen near apoapsis on its own). The histories are still in fixed steps of 10 s.
* There is an initial configuration for RealSolarSystem: the planets will start in the right places as given by the JPL HORIZONS service, and they are given gravity models using the freshest data available (Vesta's model is from Dawn data, some Cassini data gets used).  A side effect of that is that the moon becomes far more accurate: since the motion of the moon is very much a 3-body problem, it cannot be accurately represented in RealSolarSystem alone. In particular, real-life eclipses can be observed in Principia + RealSolarSystem. This configuration also includes *J*₂ for the Sun, the planets, the Moon, and Vesta, so the resulting effects are felt (precession of Earth orbits, the possibility of heliosynchronous orbits, etc.).
* Bourbaki is save-compatible with Borel.  However, for RealSolarSystem users, please note that unless you reset the plugin, the new initial state and gravity model configuration files will not be taken into account.

## Library changes

* Reimplemented the integrators: the symplectic Runge-Kutta-Nyström integrator was reimplemented more cleanly, an embedded explicit Runge-Kutta-Nyström integrator was implemented. Abstractions for differential equations were created.

For more details see all [89](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-05-06T22%3A00%3A00..2015-08-15T15%3A59%3A59+sort%3Acreated-asc) pull requests between Borel and Bourbaki.

# [Borel](https://en.wikipedia.org/wiki/%C3%89mile_Borel)

## User-facing features
* Ported to version 1.0.x of KSP.
* Added custom navball settings, so that the navball can be fixed in the reference frame in which the trajectory is plotted; the IVA navball is unaffected; when using the custom navball, the prograde/retrograde vectors are now in the correct reference frame, consistent with what is shown is map view; the rest of the Frenet trihedron (the radial and normal vectors) are unaffected at the moment and will be fixed in another version.
* Added a setting to clip histories.
* Added a toolbar button to show/hide the UI.
* The UI now acknowledges the F2 key.
* Less memory-hungry.

## Bug fixes
* Fixed a crash ([#463](https://github.com/mockingbirdnest/Principia/issues/463)) when attempting to integrate with tmax_is_exact and tmax is at the end of the trajectory.
* Fixed a crash ([#480](https://github.com/mockingbirdnest/Principia/issues/480)) caused by an access a non-existent vessel.
* Fixed a UI bug ([#502](https://github.com/mockingbirdnest/Principia/issues/502) where, if the vessel is switched, the map kept showing the trace from the last viewed vessel.

For more details see all [27](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-03-22T15%3A00%3A00..2015-05-06T21%3A59%3A59+sort%3Acreated-asc+) pull requests between Bolzano and Borel.

# [Bolzano](https://en.wikipedia.org/wiki/Bernard_Bolzano)

## Optimizations

* Changed the serialization code to read/write data in chunks instead of holding several copies of the entire serialized form in memory.

## Library changes

* Added numerous integrators, and restructured the code to separate the symplectic Runge-Kutta-Nyström integrators from the symplectic partitioned Runge-Kutta integrators.  Started to analyze their numerical characteristics and performance.

For more details see all [11](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-02-28T14%3A00%3A00..2015-03-22T14%3A59%3A59+sort%3Acreated-asc+) pull requests between Bessel and Bolzano.

# [Bessel](https://en.wikipedia.org/wiki/Friedrich_Bessel)

## User-facing features

* Rudimentary predictions have been added.  The predictions are currently using the same integration method (McLachlan and Atela's 1992 optimal 5th order method), with the same splitting of the Hamiltonian (kinetic + potential energy), this is somewhat usable but unacceptably slow.

## Bug fixes

* Fixed a bug ([#461](https://github.com/mockingbirdnest/Principia/issues/461)) where Principia would switch to a nonrotating reference frame while still in the atmosphere.

For more details see all [5](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-02-23T23%3A00%3A00..2015-02-28T13%3A59%3A59+sort%3Acreated-asc+) pull requests between Бернштейн and Bessel.

# [Бернштейн](https://en.wikipedia.org/wiki/Sergei_Natanovich_Bernstein)

## Bug fixes

* Fixed a crash on revert to VAB: when reverting to VAB, the old save was loaded immediately, but the time was only reset when exiting the VAB. Running Principia in the editor caused it to integrate back to the future, and caused a crash when KSP's time was reverted.  Thanks to [@diomedea](https://github.com/diomedea) for reporting this.

For more details see all [6](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-02-22T23%3A00%3A00..2015-02-23T22%3A59%3A59+sort%3Acreated-asc+) pull requests between Bernoulli and Бернштейн.

# [Bernoulli](https://en.wikipedia.org/wiki/Daniel_Bernoulli)

## User-facing features

* Improved logging by printing out the stack trace in case of crash, as well as the base address of the DLL.
* Minor UI improvements.

For more details see all [6](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-02-16T21%3A00%3A00..2015-02-22T22%3A59%3A59+sort%3Acreated-asc+) pull requests between Banach and Bernoulli.

# [Banach](https://en.wikipedia.org/wiki/Stefan_Banach)

First non-ɑ release (also known as: first β release).  It might be possible to play.

## User-facing features

* Serialization has been implemented.  It is now possible to save the state of Principia.

## Optimization

* Improved rendering performance by not reallocating gigantic objects at every frame.  Thanks to [@sarbian](https://github.com/sarbian) for pointing this out.

For more details see all [39](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-01-21T21%3A00%3A00..2015-02-16T20%3A59%3A59+sort%3Acreated-asc+) pull requests between Agnesi and Banach.

# [Agnesi](https://en.wikipedia.org/wiki/Maria_Gaetana_Agnesi)

## Bug fixes

* Fixed a crash due to adding 0-part vessels to the physics bubble.
* Fixed a bug where the plugin would still manage the physics bubble at ground level on bodies without an atmosphere.
* Fixed a bug where a crashed vessel would keep being simulated.

## Optimization

* Improved performance by not calling FindObjectOfType at every frame.

## Library changes

* Started work on serialization using the Google protocol buffer library.

For more details see all [4](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-01-18T23%3A00%3A00..2015-01-21T20%3A59%3A59+sort%3Acreated-asc+) pull requests between Ackermann and Agnesi.

# [Ackermann](https://en.wikipedia.org/wiki/Wilhelm_Ackermann)

## User-facing features

* Better logging and UI controls for logging.

For more details see all [2](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2015-01-17T17%3A00%3A00..2015-01-18T22%3A59%3A59+sort%3Acreated-asc+) pull requests between Abel and Ackermann.

# [Abel](https://en.wikipedia.org/wiki/Niels_Henrik_Abel)

First public ɑ release.  Not exactly usable.  About 9 months of development before that point.

For more details see all [300](https://github.com/mockingbirdnest/Principia/pulls?utf8=%E2%9C%93&q=is%3Apr+is%3Aclosed+merged%3A2010-01-01T01%3A00%3A00..2015-01-17T16%3A59%3A59+sort%3Acreated-asc+) pull requests before Abel.