# Geometry framework

The geometry framework provides a unified infrastructure for handling all 3D objects in the scene, including CAD models, scanned models, and fabrication instructions. This framework enables easy interaction between application layers and 3D objects while being tightly integrated with the rendering system, which implicitly manages OpenGL resources, simplifying the workload for application layers.

## Usage of Geometry Framework
The geometry is organized into the following primitive shapes: point, line, circle, cylinder, polyline, triangle, mesh, and text. Each of them is a class (e.g., `GOPoint`, `GOLine`, `GOCircle`, etc.) that inherits the base class `GOPrimitive`, where "GO" stands for Geometry Object. The base class manages general attributes and provides interfaces such as visibility and transformation, while the subclasses handle their specific data and functions.

To initialize a `GO` object, instead of calling the constructor, one must use the static function `Add()` of the corresponding class to create an object. It returns a `std::shared_ptr<GO>` For example, to create a point at the origin:
```
std::shared_ptr<GOPoint> point = GOPoint::Add(0, 0, 0);
```

## GO Registry
The system maintains a global registry, `GORegistry`, to keep track of all GOs. When the `Add()` function is called, it acquires a unique UUID and registers itself in the global hash table. Since this table is accessible throughout the system, application layers can retrieve specific objects by their UUIDs or iterate through all objects to perform operations.

To retrieve a `GO` with id:
```
std::shared_ptr<T> obj = AIAC_GOREG->GetGO<GOPoint>(id);
```

To get all `GO`s in the registry:
```
std::vector<std::shared_ptr<GOPrimitive>> gos;
AIAC_GOREG->GetAllGOs(gos);
```
