

# Class AIAC::Utils::HoleToolheadAxisExporter



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Utils**](namespaceAIAC_1_1Utils.md) **>** [**HoleToolheadAxisExporter**](classAIAC_1_1Utils_1_1HoleToolheadAxisExporter.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ExportCoordinates**](#function-exportcoordinates) () <br>_Export and write the hole and toolhead coordinates._  |
|  void | [**ExportHoleAxis**](#function-exportholeaxis) () <br>_Export the hole coordinates._  |
|  void | [**ExportToolheadAxis**](#function-exporttoolheadaxis) () <br>_Export the toolhead coordinates._  |
|  std::string | [**GetCurrentTimestamp**](#function-getcurrenttimestamp) () <br>_Get the current timestamp._  |
|   | [**HoleToolheadAxisExporter**](#function-holetoolheadaxisexporter) (const std::string & basePath) <br> |
|  void | [**WriteBufferToFile**](#function-writebuffertofile) () <br>_Write the buffer to a file._  |
|  void | [**WriteCoordToBuffer**](#function-writecoordtobuffer) (const std::string & itemType, std::string itemName, const std::string & pointType, std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; goPoint) <br>_Write the coordinates to a .log file._  |
|   | [**~HoleToolheadAxisExporter**](#function-holetoolheadaxisexporter) () = default<br> |




























## Public Functions Documentation




### function ExportCoordinates 

_Export and write the hole and toolhead coordinates._ 
```C++
void AIAC::Utils::HoleToolheadAxisExporter::ExportCoordinates () 
```




<hr>



### function ExportHoleAxis 

_Export the hole coordinates._ 
```C++
void AIAC::Utils::HoleToolheadAxisExporter::ExportHoleAxis () 
```




<hr>



### function ExportToolheadAxis 

_Export the toolhead coordinates._ 
```C++
void AIAC::Utils::HoleToolheadAxisExporter::ExportToolheadAxis () 
```




<hr>



### function GetCurrentTimestamp 

_Get the current timestamp._ 
```C++
std::string AIAC::Utils::HoleToolheadAxisExporter::GetCurrentTimestamp () 
```





**Returns:**

A string representing the current timestamp 





        

<hr>



### function HoleToolheadAxisExporter 

```C++
explicit AIAC::Utils::HoleToolheadAxisExporter::HoleToolheadAxisExporter (
    const std::string & basePath
) 
```




<hr>



### function WriteBufferToFile 

_Write the buffer to a file._ 
```C++
void AIAC::Utils::HoleToolheadAxisExporter::WriteBufferToFile () 
```



The data is written in the following format: ItemType,ItemName,PointType,X,Y,Z 


        

<hr>



### function WriteCoordToBuffer 

_Write the coordinates to a .log file._ 
```C++
void AIAC::Utils::HoleToolheadAxisExporter::WriteCoordToBuffer (
    const std::string & itemType,
    std::string itemName,
    const std::string & pointType,
    std::shared_ptr< GOPoint > goPoint
) 
```





**Parameters:**


* `itemType` Type of the item (toolhead or hole) 
* `pointType` Type of the point (start or end) 
* `goPoint` Pointer to the [**GOPoint**](classAIAC_1_1GOPoint.md) object to get the coordinates from 




        

<hr>



### function ~HoleToolheadAxisExporter 

```C++
AIAC::Utils::HoleToolheadAxisExporter::~HoleToolheadAxisExporter () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/HoleToolheadAxisExporter.h`

