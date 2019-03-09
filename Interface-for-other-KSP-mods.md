*This is a draft of the API documentation.
The API is not yet implemented.*

Principia provides an API that allows other mods to take its effects into account.

Mods should use the interface by reflection.

The interface is provided by an assembly whose `AssemblyName.Name` is `principia.ksp_plugin_adapter` (the actual file name is different, currently `ksp_plugin_adapter.dll` in the `Principia` directory; callers should not depend on the file name).

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
We give sample declarations with fields below, however, *it is unspecified whether the members are fields or properties*; interfacing mods should accept either by reflection.

Not accepting both will cause future breakage in the event we need to change between fields and properties.  Accepting both will keep calling code operational when these refactorings take place.

It is also unspecified whether the interface types are value types or reference types (`struct` or `class`).
If they are reference types, they have a default constructor.
Since the types are boxed when accessed by reflection, this mostly does not matter.
When constructing an object of an interface type to pass it as a parameter to an interface function, callers should use [`Activator.CreateInstance(Type)`](https://docs.microsoft.com/en-us/dotnet/api/system.activator.createinstance?view=netframework-4.7.2#System_Activator_CreateInstance_System_Type_).

## `XY`
```C#
public struct XY {
  public double x;
  public double y;
}
```

# Interface functions

The example usages of the interface functions given in this section make use of some utilities (classes `Principia` and `Reflection`) to limit the reflection boilerplate at the call site.
We have tried to make the identifiers e See the appendix for their definition.

The types of the exceptions thrown by erroneous interface calls are unspecified.
When an exception is thrown, additional information may be found in the Principia logs.

## `GeopotentialGetCoefficient`

```C#
  public XY GeopotentialGetCoefficient(
      int body_index,
      int degree,
      int order);
```

Returns the *normalized* geopotential coefficient of the given `degree` and `order` of the body whose `flightGlobalsIndex` is `body_index`.
For degree 𝑛 and order 𝑚, the `x` member of the result is 𝐶<sub>𝑛𝑚</sub> and the `y` member is 𝑆<sub>𝑛𝑚</sub>.

Throws an exception if:
- the Principia plugin is not started;
- there is no `CelestialBody` whose `flightGlobalsIndex` is `body_index`;
- the relation `0` ≤ `order` ≤ `degree` is not satisfied.

### Notes
The coefficients 𝐶<sub>𝑛𝑚</sub> and 𝑆<sub>𝑛𝑚</sub> may be given as normalized or unnormalized coefficients (most often the former).
See the [IERS conventions (2010), chapter 6](https://www.iers.org/SharedDocs/Publikationen/EN/IERS/Publications/tn/TechnNote36/tn36_079.pdf?__blob=publicationFile&v=1) for definition of the normalized and unnormalized coefficients.
While the IERS conventions use an overline to denote normalization, the normalized coefficients are often referred to as 𝐶<sub>𝑛𝑚</sub> as well.

Callers should check the convention for their usage, and unnormalize the result of `GeopotentialGetCoefficient` as needed.

For Earth, the normalized value of 𝐶<sub>32</sub> is about 9.0476×10<sup>−7</sup>, while
the unnormalized value is 3.0904×10<sup>−7</sup>.

The zonal harmonics 𝐶<sub>𝑛0</sub> are often given as 𝐽<sub>𝑛</sub>.
𝐽<sub>𝑛</sub> is always given *unnormalized*, 𝐽<sub>𝑛</sub> = −𝐶<sub>𝑛0</sub> with the *unnormalized* value of 𝐶<sub>𝑛0</sub>.

With the *normalized* value of 𝐶<sub>𝑛0</sub>, this becomes 𝐽<sub>𝑛</sub> = −𝐶<sub>𝑛0</sub> √(2𝑛 + 1).

### Example: computing 𝐽<sub>2</sub> for Earth
```C#
var principia = Principia.Get();
CelestialBody earth = FlightGlobals.GetHomeBody();
var c20_s20 = Reflection.Call(principia, "GeopotentialGetCoefficient")(
    earth.flightGlobalsIndex, 2, 0);
double c20 = Reflection.GetFieldOrPropertyValue<double>(c20_s20, "x");
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

### Notes

The reference radius is the quantity denoted by 𝑎<sub>𝑒</sub> in the [IERS conventions (2010), chapter 6](https://www.iers.org/SharedDocs/Publikationen/EN/IERS/Publications/tn/TechnNote36/tn36_079.pdf?__blob=publicationFile&v=1).

### Example: computing the precession of the ascending node due to 𝐽<sub>2</sub> (in radians per second)
```C#
double J2NodalPrecession(Orbit orbit) {
  var principia = Principia.Get();
  var c20_s20 = Reflection.Call(principia, "GeopotentialGetCoefficient")(
      orbit.referenceBody.flightGlobalsIndex, 2, 0);
  double c20 = Reflection.GetFieldOrPropertyValue<double>(c20_s20, "x");
  double j2 = -c20 * Math.Sqrt(5);
  double reference_radius =
      Reflection.Call<double>(principia, "GeopotentialGetReferenceRadius")(
          orbit.referenceBody.flightGlobalsIndex);
  double μ = orbit.referenceBody.gravParameter;
  return -3.0 / 2.0 * orbit.meanMotion *
      Math.Pow(referenceRadius / orbit.semiLatusRectum, 2) *
      Math.Cos(orbit.inclination * Math.PI / 180);
}
```

# Appendix: reflection utilities

```C#
// Principia-specific utilities.
public static class Principia {
  public static string AssemblyName() {
    foreach (var loaded_assembly in AssemblyLoader.loadedAssemblies) {
      if (loaded_assembly.assembly.GetName().Name == "principia.ksp_plugin_adapter") {
        return loaded_assembly.assembly.FullName;
      }
    }
    throw new DllNotFoundException(
        "principia.ksp_plugin_adapter not in AssemblyLoader.loadedAssemblies");
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

// This class provides the following methods:
// — Reflection.Call(obj, "name")(args);
// — Reflection.GetFieldOrPropertyValue(obj, "name");
// — Reflection.SetFieldOrPropertyValue(obj, "name", value).
// The following generics are equivalent to casting the result of the
// non-generic versions, with better error messages:
// — Reflection.Call<T>(obj, "name")(args) for (T)Reflection.Call(obj, "name")(args);
// — Reflection.GetFieldOrPropertyValue<T>(obj, "name") for
//   (T)Reflection.GetFieldOrPropertyValue(obj, "name").
public static class Reflection {
  // Returns the value of the property or field of |obj| with the given name.
  public static T GetFieldOrPropertyValue<T>(object obj, string name) {
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

  public static void SetFieldOrPropertyValue<T>(object obj, string name, T value) {
    if (obj == null) {
      throw new NullReferenceException(
          $"Cannot set {typeof(T).FullName} {name} on null object");
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
              type.FullName}.{name} to {typeof(T).FullName} {
              value?.GetType().FullName ?? "null"} {value}",
          exception);
    }
  }

  public static object GetFieldOrPropertyValue(object obj, string name) {
    return GetFieldOrPropertyValue<object>(obj, name);
  }

  public delegate T BoundMethod<T>(params object[] args);

  public static BoundMethod<T> Call<T>(object obj, string name) {
    if (obj == null) {
      throw new NullReferenceException($"Cannot call {name} on null object");
    }
    Type type = obj.GetType();
    MethodInfo method = type.GetMethod(name, public_instance);
    if (method == null) {
     throw new KeyNotFoundException(
         $"No public instance method {name} in {type.FullName}");
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

  public static BoundMethod<object> Call(object obj, string name) {
    return Call<object>(obj, name);
  }

  private const BindingFlags public_instance =
      BindingFlags.Public | BindingFlags.Instance;
}
```