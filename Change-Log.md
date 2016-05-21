# Burnside

## User-facing features

* Changed the prediction parameters to be per vessel as opposed to global.  Thus, different vessels may have predictions of different lengths or accuracies.
* Changed the way that the trajectories of celestials are recorded in saves: instead of recording everything that was computed in the course of the game, only the next 6 months or so are saved.  The rest is recomputed when the save is loaded.  The advantage is that the saves are considerably smaller (a factor of 100x has been observed in simple games).  The drawback is that loading a save is more CPU-intensive and may therefore take longer.
* The plugin has a new icon.

## Bug fixes

* Fixed the stabilization of the Jool system in the stock game which had stopped working in Буняковский.
* Fixed a situation where adaptive step integration would crash when the system was already integrated to the desired final time.
* Fixed a problem where the start of a flight plan would be discarded to the point that it had no burns anymore and various pieces of the code would disagree as to whether the vessel still had a flight plan.

# Буняковский

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