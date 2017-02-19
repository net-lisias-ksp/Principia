> anyone that doubts the wisdom of retrograde bop needs to get the hell out  
―Scott Manley

Principia computes the trajectory of the celestial bodies by integrating the equations of
motion<sup name="a1">[1](#f1)</sup>; as a result,
if the system is unstable, it may break down in-game. This is in fact the case of the stock system: while the
specifics depend on how KSP's Keplerian orbital elements are translated into a Cartesian initial state, with
Principia's interpretation as hierarchical Jacobi elements, the Jool system breaks down within 19 days, with
a close encounter between Vall and Laythe.

|18 days | 19 days |
|---|---|
| ![](http://i.imgur.com/KgSIAoU.png) | ![](http://i.imgur.com/tXsXZeI.png) |

What would actually happen in that encounter is unclear (impact, breakup by tidal forces, or simply ejection
of Vall are all possibilities), and Principia is unable to properly simulate it: besides these physical
considerations, the integration error explodes, and the sharp bend in the trajectory causes a failure of the
polynomial fitting<sup name="a2">[2](#f2)</sup>. This can be seen in the image on the right above. In any case,
the final outcome is likely to have a very wild dependence on the initial conditions.

Principia remedies to this by [modifying the Jool system](https://github.com/mockingbirdnest/Principia/blob/2016081314-Cantor/ksp_plugin_adapter/ksp_plugin_adapter.cs#L1400-L1468),
specifically:

- by increasing the size of the orbits of Vall and Tylo, thereby preventing breakdowns of the inner
  Jool system due to resonances;
- by making the orbit of Bop retrograde<sup name = "a3">[3](#f3)</sup>, as suggested by Scott Manley and [@pdn4kd](https://github.com/pdn4kd), so that it doesn't get boosted out
  of the system by Tylo (which now comes closer to it).
While the resulting system does not appear likely to break down within a century, we find that it is highly
chaotic, mostly because of interactions between Bop and Tylo. In the remainder of this document, we discuss
the implications of this chaotic behaviour on the predictability of the system, and look at some features of
the motion of the Joolian moons.
## Global error
When discussing a numerical integration of a physical system, there are several sources of error:

1. Round-off error, from using floating-point arithmetic rather than real numbers;
1. Truncation error, from using a nonzero step size in a numerical integrator;
1. Measurement errors in the initial state;
1. Modeling assumptions: considering bodies as point masses, ignoring general relativity, ignoring radiative effects (Ярковский, Poynting–Robertson), etc.

Here we ignore errors from modeling assumptions. While there is no measurement of the initial state *per se*
in our problem, the concept is still sensible, since we are dealing with a physical system.

### Forward error
We estimate numerical (truncation and round-off) errors by comparing the result of an integration at a step of 5 min with
the same integration at a step of 2.5 min. The actual error should be of the same order of magnitude as the difference
between the computed solutions. The estimated errors are shown in the following table.

|time|error in position in the Joolian barycentre frame (moon)|
|---|---|
|1 a| +3.74739719791592596e-01 m (Laythe) |
|2 a| +1.39224971456813140e+00 m (Pol) |
|3 a| +8.49396516257019307e+00 m (Bop) |
|4 a| +5.10756172599136136e+01 m (Bop) |
|5 a| +5.41899643855711815e+02 m (Bop) |
|6 a| +4.96393026229186398e+03 m (Bop) |
|7 a| +3.01654772715498148e+04 m (Bop) |
|8 a| +3.07834670458512919e+04 m (Bop) |
|9 a| +2.62286978937739448e+05 m (Bop) |
|10 a| +1.47840118400542252e+06 m (Bop) |
|11 a| +1.05332515433050469e+07 m (Bop) |
|12 a| +2.31910395306165308e+08 m (Bop) |

As expected from a chaotic system, the error is amplified exponentially with time, so that after 12 years we cannot tell
where Bop lies on its orbit. While we could reduce these errors by decreasing the step size, exponential growth means that
eventually the numerical errors will get amplified to the point where we cannot predict anything accurately.

### Bounding the backward error
We answer the question of whether these numerical errors are "good enough" by considering whether a hypothetical observer
of the system could tell the difference between our integration and the laws of physics.

A property of our chosen integrator is that, being conjugate-symplectic, it does not exhibit energy drift:
our observer cannot measure the energy at various times and notice an unphysical systematic drift.
There will be some bounded variations, but by lowering the time step, their amplitude can be reduced as needed.
The same holds for angular and linear momentum.

The observer would have measurement errors on the initial state: let us say that the errors are millimetric.
We take a cluster of 100 systems where the Joolian system is millimetrically perturbed in random directions, and we compare
the integration of the unperturbed system with that of all perturbed systems, at a 5 min time step. We record the greatest
divergence in the following table.

|time|error in position in the Joolian barycentre frame (moon)|
|---|---|
|1 a| +2.02320983591245245e+01 m (Laythe) |
|2 a| +9.58347695454694644e+02 m (Bop) |
|3 a| +9.56218220833261330e+03 m (Bop) |
|4 a| +5.76096439285006418e+04 m (Bop) |
|5 a| +6.17599349619004526e+05 m (Bop) |
|6 a| +5.87323334232143965e+06 m (Bop) |
|7 a| +4.96615832782097757e+07 m (Bop) |
|8 a| +1.97354446171970442e+07 m (Bop) |
|9 a| +3.14420956432531476e+08 m (Bop) |

These errors dominate the numerical errors, so that our simulation is within the measurement errors of that potential observer.
Further, the observer cannot accurately predict the behaviour of the system beyond about five years. We call those first five
years "predictable".

## Plots
Here are the trajectories for the first five years.

|1 a|2 a|
|---|---|
| ![](http://i.imgur.com/ltlra6w.png) | ![](http://i.imgur.com/xQbH821.png) |

|5 a|
|---|
| ![](http://i.imgur.com/WYVTzsM.jpg) |

Some properties are better seen as a function of time: here are some plots of the apsides of the various bodies.

|1 a|10 a|
|---|---|
| ![](http://i.imgur.com/mIMdaLo.png) | ![](http://i.imgur.com/rApM7B8.png)|

|100 a|
|---|
| ![](http://i.imgur.com/3gSB56V.png) |

Notice, in the plot over 1 Julian year, that the eccentricity of Vall's orbit oscillates between 0 and ~0.05 over
a handful of orbits. Bop's orbit varies wildly; we can look at the individual orbital elements. In the following
plots, the blue points are Jool-centric elements as shown by KSP, and the yellow points are elements around the
barycentre of the inner Jool system.

|eccentricity|inclination|longitude of ascending node|argument of periapsis|
|---|---|---|---|
| ![](http://i.imgur.com/BZ6BX0r.png) | ![](http://i.imgur.com/rTpSP6l.png) | ![](http://i.imgur.com/u0JxXl5.png) | ![](http://i.imgur.com/LY1PEO5.png) |

We can see strong nodal and apsidal precession, as can be expected from orbiting the inner Jool system, which behaves
roughly like a very oblate mass<sup name = "a4">[4](#f4)</sup>. The behaviour of the eccentricity and inclination is
complex. Again the specifics after a decade depend on amplified numerical errors; we look at the first five "predictable"
years.

|eccentricity|inclination|
|---|---|
| ![](http://i.imgur.com/ACVmX0G.png) | ![](http://i.imgur.com/JgKh3FU.png) |

## TODO
There are many flaws in the error analysis above, and there are additional things to be studied about this system.
### Local error
We have only looked at the global error above, *i.e.*, the error between the true solution starting from the initial state,
and the one we compute. An observer however can look at the state at any time, and see whether the computed solution behaves
correctly (within measurement errors) on a short interval. For instance, if a close encounter happens, they might notice the
numerical error on that time step, even though their uncertainties on the initial state have been amplified beyond the point of usefulness.
We should estimate the local error, and possibly the local backward error too.
We should also detect very close encounters specifically: when those happen, the error from modeling
assumptions becomes unacceptable, since we do not simulate bodies colliding or breaking up from tidal effects.
### Ляпунов time
While we may take a guess at the Ляпунов time from the errors above, it would be interesting to give a proper estimate, ideally
computed by integrating the variational equation.
### Statistical analysis
Once we have local error control and close encounter detection, we could simulate a large number of millimetrically perturbed systems
to estimate the probability that the system will last a given time.
### Understand the behaviour of Bop's eccentricity and inclination
There are clearly several periodic effects at work on the first five years, which affect both eccentricity and inclination in
similar ways. Do the periods match those of the inner moons? Could we see something from a Fourier transform?

---
<b><a name="f1">1.</a></b> [↑](#a1) Principia offers a plethora of integrators; in this document we use a 12th order symmetric linear multistep
integrator from a paper by
[Gerald Quinlan and Scott Tremaine (1990), Symmetric multistep methods for the numerical integration of planetary orbits](http://adsabs.harvard.edu/full/1990AJ....100.1694Q).  
<b name="f2">2.</b> [↑](#a2) We call the failure to fit a polynomial to the trajectory an apocalypse; the check was introduced in [#612](https://github.com/mockingbirdnest/Principia/pull/612/files#diff-d8d4eb7565ea0fc981a4f857def9715bR345), in response to a bug that reminded us of a tweet by [Katie Mack (2014)](https://twitter.com/AstroKatie/status/518697246305439745).  
<b name="f3">3.</b> [↑](#a3) We call it [retrobop](https://github.com/mockingbirdnest/Principia/blob/2016081314-Cantor/ksp_plugin/plugin.cpp#L179).  
<b name="f4">4.</b> [↑](#a4) As [@pdn4kd](https://github.com/pdn4kd) puts it, an oblate megajool (megajoule?).  