

# File utils.h



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**utils.h**](utils_8h.md)

[Go to the source code of this file](utils_8h_source.md)



* `#include <opencv2/opencv.hpp>`
* `#include <string>`
* `#include <iostream>`
* `#include <filesystem>`
* `#include <sys/stat.h>`
* `#include <ctime>`
* `#include <sstream>`
* `#include "AIAC/Log.h"`
* `#include "glm/glm.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CopyFile**](#function-copyfile) (const std::string & source, const std::string & destination) <br>_Copy the file from source to destination._  |
|  std::string | [**GetCurrentDateTime**](#function-getcurrentdatetime) () <br>_Get current date/time, format is YYYY-MM-DD.HH:mm._  |
|  long | [**GetCurrentTimestamp**](#function-getcurrenttimestamp) () <br>_Get current timestamp in milliseconds._  |
|  std::string | [**GetFileNameFromPath**](#function-getfilenamefrompath) (const std::string & path, bool withExtension=true) <br>_Get the name of the file from the given path._  |
|  std::vector&lt; std::string &gt; | [**GetFilePaths**](#function-getfilepaths) (const std::string & dirPath, const std::string & extension) <br>_Get all file paths with the given extension in the given directory._  |
|  std::vector&lt; std::string &gt; | [**GetFolderPaths**](#function-getfolderpaths) (const std::string & dirPath) <br>_Get all sub-folders' paths in the given directory._  |
|  bool | [**IsFileExist**](#function-isfileexist) (const std::string & name) <br>_Check if the given file exists._  |
|  std::vector&lt; std::string &gt; | [**ParseConfigFile**](#function-parseconfigfile) (const std::string & configPath, const std::string & entryName) <br>_Parse the config file and get the file paths._  |




























## Public Functions Documentation




### function CopyFile 

_Copy the file from source to destination._ 
```C++
inline void CopyFile (
    const std::string & source,
    const std::string & destination
) 
```





**Parameters:**


* `source` the source file path 
* `destination` the destination file path 




        

<hr>



### function GetCurrentDateTime 

_Get current date/time, format is YYYY-MM-DD.HH:mm._ 
```C++
inline std::string GetCurrentDateTime () 
```




<hr>



### function GetCurrentTimestamp 

_Get current timestamp in milliseconds._ 
```C++
inline long GetCurrentTimestamp () 
```




<hr>



### function GetFileNameFromPath 

_Get the name of the file from the given path._ 
```C++
inline std::string GetFileNameFromPath (
    const std::string & path,
    bool withExtension=true
) 
```




<hr>



### function GetFilePaths 

_Get all file paths with the given extension in the given directory._ 
```C++
inline std::vector< std::string > GetFilePaths (
    const std::string & dirPath,
    const std::string & extension
) 
```





**Parameters:**


* `dirPath` 
* `extension` 




        

<hr>



### function GetFolderPaths 

_Get all sub-folders' paths in the given directory._ 
```C++
inline std::vector< std::string > GetFolderPaths (
    const std::string & dirPath
) 
```





**Parameters:**


* `folderPath` 




        

<hr>



### function IsFileExist 

_Check if the given file exists._ 
```C++
inline bool IsFileExist (
    const std::string & name
) 
```





**Parameters:**


* `name` 




        

<hr>



### function ParseConfigFile 

_Parse the config file and get the file paths._ 
```C++
inline std::vector< std::string > ParseConfigFile (
    const std::string & configPath,
    const std::string & entryName
) 
```





**Parameters:**


* `configPath` 
* `entryName` 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/utils.h`

