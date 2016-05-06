- [Free return (1211 m/s, 4 h 55 min)](https://github.com/mockingbirdnest/Principia/wiki/A-guide-to-going-to-the-Mun-with-Principia#free-return-1211-ms-4-h-55-min)
- [Hohmann (1144 m/s, 6 h 23 min)](https://github.com/mockingbirdnest/Principia/wiki/A-guide-to-going-to-the-Mun-with-Principia#hohmann-1144-ms-6-h-23-min)
- [Low energy transfer: an inner resonance transfer (1031 m/s, 2 days 16 h 41 min)](https://github.com/mockingbirdnest/Principia/wiki/A-guide-to-going-to-the-Mun-with-Principia#low-energy-transfer-an-inner-resonance-transfer-1031-ms-2-days-16-h-41-min)

Let us compare different approaches to going to the Mun, and see how to plan them using the tools provided by Principia.
For the following examples, we will start from an 80 km altitude circular Kerbin orbit, and reach a 30 km altitude circular Mun orbit. We will use the spacecraft show below (all tanks full), and perform both burns using the main engine (LV-909).
![LV-909; FL-T400; FL-R25; Small Inline Reaction Wheel; OKTO2; PB-NUK; 4x RV-105.](http://i.imgur.com/8RKDnPk.png)
###Free return (1211 m/s, 4 h 55 min)
We create a flight plan, set the reference frame to Kerbin-centred non-rotating, and create a manœuvre. We give it enough tangent Δv to reach the orbit of the Mun. This part is very similar to stock.
![](http://i.imgur.com/3OOJFoc.gif)
Since there are no spheres of influence, there is no such thing as an encounter in principia; in order to aim for the Mun, we first switch to the Kerbin-Mun barycentric rotating frame. In that frame, Kerbin and the Mun move very little, and only towards and away from each other (the reference frame fixes the Kerbin-Mun line).
![](http://i.imgur.com/wg3efAO.png)
We then change the timing of the manœuvre until it passes close to the Mun; since we want a free return, we then push the trajectory past the Mun, so it gets slowed down.
![](http://i.imgur.com/3JGUnPg.gif)
We then increase the Δv until we get something that looks like a free return trajectory.
![](http://i.imgur.com/kyhvb3t.gif)
The periapse of the above trajectory is too high, since we're aiming for a 30 km Mun orbit. Some tweaking (looking at the Mun and Kerbin frames to get Mun and Kerbin apsides) is needed to get a 30 km Mun periapsis and a roughly similar Kerbin periapsis on the way back (our craft isn't designed for recoverability, but this would be a reasonable return periapsis).
The behaviour here is that increasing the Δv lowers the Kerbin periapsis and increases the Mun periapsis, while moving the burn back in time increases the Kerbin periapsis and lowers the Mun periapsis. The exchange rate between the apsis altitudes are different for timing and Δv changes, so tweaking the two allows to get the desired apsides, at a Δv of about 875.3 m/s.
![](http://i.imgur.com/Lr1kDfz.png)
![](http://i.imgur.com/8UXrdqv.png)
The reader may have noticed that while we were fooling with apsis altitudes, we entirely missed the mark for the manœuvre (we're now more than 4 min past scheduled ignition). Fortunately, we're in a parking orbit, we can wait around until the next orbit. Let's switch back to the Kerbin-Mun frame, and move our manœuvre forward in time to the next orbit.
![](http://i.imgur.com/sMINV5k.gif)
We can then tune our timing so that the Mun periapsis is at an altitude of 30 km. Note that we do not need to change the Δv.
If we look at the resulting free-return trajectory in the barycentric rotating frame, we can see clearly its overall behaviour, going to the Mun and getting swung back towards Kerbin.
![](http://i.imgur.com/7ym9wMo.png)
In the Kerbin-centred frame, we can compare our prediction to KSP's patched conics. Note that KSP predicts an impact.
![](http://i.imgur.com/ygZs5DB.png)
We can now go back to the Mun-centred frame, and add a circularization burn at periapsis. This is very much akin to stock.
![](http://i.imgur.com/fF207qf.gif)
Shortening the flight plan to show a single orbital period, we see that the orbit has four roughly equally-spaced apsides (instead of the expected two), all around 30 km altitude. This is because minor perturbations affect our altitude more strongly than our 2-body eccentricity does: the orbit is as circular as it gets.
![](http://i.imgur.com/OMuQRwN.png)
Here is a look at the overall trajectory. The total Δv cost is about 1211 m/s, and the transfer takes 4 h 55 min from the start of injection burn to the end of the insertion burn.
![](http://i.imgur.com/FotbpcY.png)
###Hohmann (1144 m/s, 6 h 23 min)
Let us look at a more common Mun transfer, the Hohmann-like approach with which veteran players of KSP will be familiar. The planning of the injection burn is very similar to the free return case above, except we aim for the other side of the Mun, which is far cheaper.

We aim for the Mun, on the cheap side.
![](http://i.imgur.com/ZUeuXsX.gif)
We then tune the periapsis. Here we seek to minimize the Δv while getting the periapsis to 30 km. Again we need to adjust both Δv and timing, but since we have only one periapsis to watch, this is much easier than in the free return case. In the end, we get something close to 856 m/s.
![](http://i.imgur.com/G8n6yC3.png)
Here is a comparison with the patched conics, in the Kerbin-centred non-rotating frame. Note that KSP predicts that the Kerbin periapsis will slightly rise, whereas in reality this will result in an escape from the Kerbin system.
![](http://i.imgur.com/F4bPwt4.png)
We can now add a circularization burn.
![](http://i.imgur.com/ppEhqaK.png)
Here is the overall trajectory in the Kerbin-Mun barycentric reference frame. The total Δv cost is about 1144 m/s, the duration is 6 h 23 min.
![](http://i.imgur.com/WCqbNih.png)
Veteran KSP players might note that in stock, such a transfer can be executed with only ~1113 m/s of Δv; this is an artifact of patched conics.
###Low energy transfer: an inner resonance transfer (1031 m/s, 2 days 16 h 41 min)
While the previous two transfers were usual KSP operations planned using principia's tools, this one truly relies on *N*-body dynamics.
It gains 10% Δv over the more conventional approach, but takes a lot more time.

We increase the maximal number of steps per segment in our flight plan computations to 10'000, in order to allow the whole transfer to be plotted.

We first plan a manœuvre that aims for the Mun (or rather, a little behind the Mun), but significantly undershoots. However, in doing so it passes close enough to the L1 libration point to be boosted a little.
![](http://i.imgur.com/5vaHzGV.png)
Prolonging the prediction, we can see that we make two more weakly-interacting Kerbin orbits, then come back; however, since we're in a higher orbit, the Mun's influence can be felt much more strongly.
![](http://i.imgur.com/w1FFMP0.png)
By moving our first approach a little, we can achieve a ballistic capture on the second approach, that is, we transfer into a weakly-bound unstable Mun orbit only from the influence of gravity.
![](http://i.imgur.com/mbrZDaq.png)
Again, we can finely tune our Δv and timing to get our Mun periapsis on one of the weakly-bound orbits to 30 km.
![](http://i.imgur.com/VxOWJI7.png)
It is interesting to see what would happen without a circularization burn; let us lengthen the flight plan. We see that we end up impacting the Mun, after some highly non-Keplerian orbits.
![](http://i.imgur.com/43LExnF.png)
Comparing with the patched conics in the Kerbin-centred non-rotating reference frame, we see that they're not even remotely close. In some cases the first Mun approach is seen as a patched conics encounter, but its effect is not captured well enough to get the second encounter; in any case, ballistic captures (or weakly-bound orbits in general) are impossible to get with patched conics.
Looking at the principia trajectory, we can see that from the perturbed Keplerian viewpoint, our initial transfer gets its periapsis boosted once, then on a subsequent encounter gets turned into a rather mysterious trajectory that strongly interacts with both bodies.
![](http://i.imgur.com/WgrQB6v.png)
In contrast, the rotating frame allows us to clearly see the resonant nature of the transfer, with the fourth orbit coming back in the same direction as the first, but higher, and weakly bound orbit resulting from the ballistic capture is clearly legible.

Let us now switch back to the Mun-centred non-rotating frame to plan our circularization burn.
![](http://i.imgur.com/AKVWsqc.png)
Here is the overall trajectory, in the rotating frame. The Δv cost is 1031 m/s, and the duration is 2 days 16 h 41 min. This is 10% less Δv than the Hohmann transfer, but 10 times the duration.
![](http://i.imgur.com/4mCM4r6.png)
