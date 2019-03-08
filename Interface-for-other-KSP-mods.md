*This is a draft of the API documentation.
The API is not yet implemented.*

Principia provides an API that allows other mods to take its effects into account.

Mods should use the interface by reflection.

# The `ExternalInterface` object

The interface consists of instance methods of the class
`principia.ksp_plugin_adapter.ExternalInterface`.

## `ExternalInterface.Get()`

An instance of this class can be obtained by calling the static method
```C#
principia.ksp_plugin_adapter.ExternalInterface.Get()
```
which:
- returns an object of type `ExternalInterface` if the Principia `ScenarioModule` and the Principia native DLLs are loaded;
- returns `null` if the Principia `ScenarioModule` is not loaded, for instance in the editor scene, where Principia does not run;
- throws `DllNotFoundException` if the Principia native DLL could not be loaded; this indicates an incorrect Principia installation.

# Interface types

The interface types are declared in namespace `principia.ksp_plugin_adapter`.
We give qualitative declarations with fields below, however, *it is unspecified whether the members are fields or properties*; interfacing mods should accept either by reflection.

## `XY`
```C#
struct XY {
  double x;
  double y;
}
```

# Interface functions

The example usages of the interface functions given in this section make use of some utilities to limit the reflection boilerplate at the call site. See the appendix for their definition.

The types of the exceptions thrown by erroneous interface calls are unspecified.
When an exception is thrown, additional information may be found in the Principia logs.

## `GeopotentialGetCoefficient`

```C#
  public XY GeopotentialGetCoefficient(
      int body_index,
      int degree,
      int order);
```

Returns the normalized geopotential coefficient of the given `degree` and `order` of the body whose `flightGlobalsIndex` is `body_index`.
For degree 𝑛 and order 𝑚, the `x` member of the result is 𝐶<sub>𝑛𝑚</sub> and the `y` member is 𝑆<sub>𝑛𝑚</sub>.

Throws an exception if:
- the Principia plugin is not started;
- there is no `CelestialBody` whose `flightGlobalsIndex` is `body_index`;
- the relation `0 ≤ order ≤ degree` is not satisfied.

### Notes
The coefficients 𝐶<sub>𝑛𝑚</sub> may be given as normalized or unnormalized coefficients (most often the former); callers should check the convention for their usage.
For Earth, the normalized value of 𝐶<sub>32</sub> is about 9.0476×10<sup>-07</sup>;
the *unnormalized* value is 3.0904×10<sup>-07</sup>.

The zonal harmonics 𝐶<sub>𝑛0</sub> are often given as 𝐽<sub>𝑛</sub>.
𝐽<sub>𝑛</sub> is always given *unnormalized*, 𝐽<sub>𝑛</sub> = −𝐶<sub>𝑛0</sub> with the *unnormalized* value of 𝐶<sub>𝑛0</sub>.

With the *normalized* value of 𝐶<sub>𝑛0</sub>, this becomes 𝐽<sub>𝑛</sub> = −𝐶<sub>𝑛0</sub> √(2𝑛 + 1).

### Example: computing 𝐽<sub>2</sub> for Earth
```C#
var principia = Principia.Get();
CelestialBody earth = FlightGlobals.GetHomeBody();
var c20_s20 = principia.Call("GeopotentialGetCoefficient")(earth.flightGlobalsIndex, 2, 0);
double c20 = c20_s20.GetValue<double>("x");
double j2 = -c20 * Math.Sqrt(5);
```

## `GeopotentialGetReferenceRadius`

```C#
  public XY GeopotentialReferenceRadius(
      int body_index);
```

Returns the value in metres of the reference radius of the geopotential model for the body whose `flightGlobalsIndex` is `body_index`.

Throws an exception if:
- the Principia plugin is not started;
- there is no `CelestialBody` whose `flightGlobalsIndex` is `body_index`.

### Example: computing the precession of the ascending node due to 𝐽<sub>2</sub> (in radians per second)
```C#
double J2NodalPrecession(Orbit orbit) {
  var principia = Principia.Get();
  var c20_s20 = principia.Call("GeopotentialGetCoefficient")(
      orbit.referenceBody.flightGlobalsIndex, 2, 0);
  double c20 = c20_s20.GetValue<double>("x");
  double j2 = -c20 * Math.Sqrt(5);
  double reference_radius = principia.Call<double>("GeopotentialGetReferenceRadius")(
      orbit.referenceBody.flightGlobalsIndex);
  double μ = orbit.referenceBody.gravParameter;
  return -3.0 / 2.0 * orbit.meanMotion *
      Math.Pow(referenceRadius / orbit.semiLatusRectum, 2) * Math.Cos(orbit.inclination);
}
```

# Appendix: reflection utilities

```C#
// This class provides the following extension methods on all objects:
// — obj.Call("name")(args).
// — obj.GetValue("name");
// — obj.SetValue("name", value);
// The following generics are equivalent to casting the result of the
// non-generic versions, with better error messages:
// — obj.Call<T>("name")(args).
// — obj.GetValue<T>("name");
public static class Reflection {
  // Returns the value of the property or field of |obj| with the given name.
  public static T GetValue<T>(this object obj, string name) {
    if (obj == null) {
      throw new NullReferenceException(
          $"Cannot access {typeof(T).FullName} {name} on null object");
    }
    Type type = obj.GetType();
    object result = null;
    FieldInfo field = type.GetField(name, public_instance);
    PropertyInfo property = type.GetProperty(name, public_instance);
    if (field != null) {
      result = field.GetValue(obj);
    } else if (property != null) {
      result = property.GetValue(obj, index : null);
    } else {
      throw new MissingMemberException(
          $"No public instance field or property {name} in {type.FullName}");
    }
    try {
      return (T)result;
    } catch (Exception exception) {
      throw new InvalidCastException(
          $@"Could not convert the value of {
              (field == null ? "property" : "field")} {
              (field?.FieldType ?? property.PropertyType).FullName} {
              type.FullName}.{name}, {result}, to {typeof(T).FullName}",
          exception);
    }
  }

  public static void SetValue<T>(this object obj, string name, T value) {
    if (obj == null) {
      throw new NullReferenceException(
          $"Cannot access {typeof(T).FullName} {name} on null object");
    }
    Type type = obj.GetType();
    FieldInfo field = type.GetField(name, public_instance);
    PropertyInfo property = type.GetProperty(name, public_instance);
    if (field == null && property == null) {
      throw new MissingMemberException(
          $"No public instance field or property {name} in {type.FullName}");
    }
    try {
      field?.SetValue(obj, value);
      property?.SetValue(obj, value, index : null);
    } catch (Exception exception) {
      throw new ArgumentException(
          $@"Could not set {
              (field == null ? "property" : "field")} {
              (field?.FieldType ?? property.PropertyType).FullName} {
              type.FullName}.{name} to {typeof(T).FullName} {value}",
          exception);
    }
  }

  public static object GetValue(this object obj, string name) {
    return obj.GetValue<object>(name);
  }

  public delegate T BoundMethod<T>(params object[] args);

  public static BoundMethod<T> Call<T>(this object obj, string name) {
    Type type = obj.GetType();
    MethodInfo method = type.GetMethod(name, public_instance);
    if (method == null) {
     throw new KeyNotFoundException(
         $"No public instance method {name} in {obj.GetType().FullName}");
    }
    return args => {
      object result = method.Invoke(obj, args);
      try {
        return (T)result;
      } catch (Exception exception) {
        throw new InvalidCastException(
            $@"Could not convert the result of {
                method.ReturnType.FullName} {
                type.FullName}.{name}(), {result}, to {typeof(T).FullName}",
            exception);
      }
    };
  }

  public static BoundMethod<object> Call(this object obj, string name) {
    return obj.Call<object>(name);
  }

  private const BindingFlags public_instance =
      BindingFlags.Public | BindingFlags.Instance;
}

// Principia-specific utilities.
public static class Principia {
  public static string AssemblyName() {
    foreach (var loaded_assembly in AssemblyLoader.loadedAssemblies) {
      if (loaded_assembly.assembly.GetName().Name == "ksp_plugin_adapter") {
        return loaded_assembly.assembly.FullName;
      }
    }
    throw new DllNotFoundException(
        "ksp_plugin_adapter not in AssemblyLoader.loadedAssemblies");
  }

  public static Type GetType(string name) {
    return Type.GetType(
      $"principia.ksp_plugin_adapter.{name}, {AssemblyName()}");
  }

  // principia.ksp_plugin_adapter.ExternalInterface.Get().
  public static object Get() {
    return GetType("ExternalInterface")
        .GetMethod("Get")
        .Invoke(null, null);
  }
}
```