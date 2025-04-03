

# Class AIAC::Config



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Config**](classAIAC_1_1Config.md)




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const std::string | [**AC\_INFO\_MODEL**](#variable-ac_info_model)   = `"ACInfoModel"`<br> |
|  const std::string | [**ALIGN\_FLIP**](#variable-align_flip)   = `"AlignFlip"`<br> |
|  const std::string | [**ALIGN\_OFFSET**](#variable-align_offset)   = `"AlignOffset"`<br> |
|  const std::string | [**ALIGN\_ROTATION**](#variable-align_rotation)   = `"AlignRotation"`<br> |
|  const std::string | [**CACHED\_TOOLHEAD**](#variable-cached_toolhead)   = `"CachedToolhead"`<br> |
|  const std::string | [**CAM\_FLIP\_HORIZONTAL**](#variable-cam_flip_horizontal)   = `"CamFlipHorizontal"`<br> |
|  const std::string | [**CAM\_FLIP\_VERTICAL**](#variable-cam_flip_vertical)   = `"CamFlipVertical"`<br> |
|  const std::string | [**CAM\_ID**](#variable-cam_id)   = `"CamID"`<br> |
|  const std::string | [**CAM\_PARAMS\_FILE**](#variable-cam_params_file)   = `"CamParamsFile"`<br> |
|  const std::string | [**CONFIG\_FILE**](#variable-config_file)   = `"ConfigFile"`<br> |
|  const std::string | [**DATASET\_DIR**](#variable-dataset_dir)   = `"DatasetDir"`<br> |
|  const std::string | [**LINK\_MODE**](#variable-link_mode)   = `"LinkMode"`<br> |
|  const std::string | [**MAP\_FILE**](#variable-map_file)   = `"MapFile"`<br> |
|  const std::string | [**NAME**](#variable-name)   = `"Name"`<br> |
|  const std::string | [**RECONSTRUCT\_CONFIG\_DEFAULT\_FILE**](#variable-reconstruct_config_default_file)   = `"ReconstructConfigDefaultFile"`<br> |
|  const std::string | [**RESOLUTION**](#variable-resolution)   = `"Resolution"`<br> |
|  const std::string | [**SAVE\_DIR\_MAPS**](#variable-save_dir_maps)   = `"SaveDirMaps"`<br> |
|  const std::string | [**SCALE\_FACTOR**](#variable-scale_factor)   = `"ScaleFactor"`<br> |
|  const std::string | [**SCANNED\_MODEL**](#variable-scanned_model)   = `"ScannedModel"`<br> |
|  const std::string | [**SEC\_AIAC**](#variable-sec_aiac)   = `"AIAC"`<br> |
|  const std::string | [**SEC\_TEST**](#variable-sec_test)   = `"Test"`<br> |
|  const std::string | [**SEC\_TOUCH\_MONITOR\_SPECS**](#variable-sec_touch_monitor_specs)   = `"TouchMonitorSpecs"`<br> |
|  const std::string | [**SEC\_TSLAM**](#variable-sec_tslam)   = `"TSlam"`<br> |
|  const std::string | [**SEC\_TTOOL**](#variable-sec_ttool)   = `"TTool"`<br> |
|  const std::string | [**SEC\_UTILS**](#variable-sec_utils)   = `"Utils"`<br> |
|  const std::string | [**STABILIZATION\_FRAME\_COUNT**](#variable-stabilization_frame_count)   = `"SaveDirMaps"`<br> |
|  const std::string | [**TTOOL\_ROOT\_PATH**](#variable-ttool_root_path)   = `"TToolRootPath"`<br> |
|  const std::string | [**UTILS\_PATH**](#variable-utils_path)   = `"UtilsPath"`<br> |
|  const std::string | [**VIDEO\_PATH**](#variable-video_path)   = `"VideoPath"`<br> |
|  const std::string | [**VocFile**](#variable-vocfile)   = `"VocFile"`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Config**](#function-config) (std::string filename, bool updateFile=true) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  T | [**Get**](#function-get-12) (const std::string & section, const std::string & name) <br> |
|  T | [**Get**](#function-get-22) (const std::string & section, const std::string & name, T && default\_v) <br> |
|  std::vector&lt; T &gt; | [**GetVector**](#function-getvector) (const std::string & section, const std::string & name, const std::vector&lt; T &gt; & default\_v) <br> |
|  void | [**InsertEntry**](#function-insertentry-12) (const std::string & section, const std::string & name, const T & v) <br> |
|  void | [**InsertEntry**](#function-insertentry-22) (const std::string & section, const std::string & name, const std::vector&lt; T &gt; & vs) <br> |
|  void | [**UpdateEntry**](#function-updateentry-12) (const std::string & section, const std::string & name, const T & v) <br> |
|  void | [**UpdateEntry**](#function-updateentry-22) (const std::string & section, const std::string & name, const std::vector&lt; T &gt; & vs) <br> |
|  void | [**WriteToFile**](#function-writetofile) (std::string writeFilename="") <br> |


























## Public Static Attributes Documentation




### variable AC\_INFO\_MODEL 

```C++
const std::string AIAC::Config::AC_INFO_MODEL;
```




<hr>



### variable ALIGN\_FLIP 

```C++
const std::string AIAC::Config::ALIGN_FLIP;
```




<hr>



### variable ALIGN\_OFFSET 

```C++
const std::string AIAC::Config::ALIGN_OFFSET;
```




<hr>



### variable ALIGN\_ROTATION 

```C++
const std::string AIAC::Config::ALIGN_ROTATION;
```




<hr>



### variable CACHED\_TOOLHEAD 

```C++
const std::string AIAC::Config::CACHED_TOOLHEAD;
```




<hr>



### variable CAM\_FLIP\_HORIZONTAL 

```C++
const std::string AIAC::Config::CAM_FLIP_HORIZONTAL;
```




<hr>



### variable CAM\_FLIP\_VERTICAL 

```C++
const std::string AIAC::Config::CAM_FLIP_VERTICAL;
```




<hr>



### variable CAM\_ID 

```C++
const std::string AIAC::Config::CAM_ID;
```




<hr>



### variable CAM\_PARAMS\_FILE 

```C++
const std::string AIAC::Config::CAM_PARAMS_FILE;
```




<hr>



### variable CONFIG\_FILE 

```C++
const std::string AIAC::Config::CONFIG_FILE;
```




<hr>



### variable DATASET\_DIR 

```C++
const std::string AIAC::Config::DATASET_DIR;
```




<hr>



### variable LINK\_MODE 

```C++
const std::string AIAC::Config::LINK_MODE;
```




<hr>



### variable MAP\_FILE 

```C++
const std::string AIAC::Config::MAP_FILE;
```




<hr>



### variable NAME 

```C++
const std::string AIAC::Config::NAME;
```




<hr>



### variable RECONSTRUCT\_CONFIG\_DEFAULT\_FILE 

```C++
const std::string AIAC::Config::RECONSTRUCT_CONFIG_DEFAULT_FILE;
```




<hr>



### variable RESOLUTION 

```C++
const std::string AIAC::Config::RESOLUTION;
```




<hr>



### variable SAVE\_DIR\_MAPS 

```C++
const std::string AIAC::Config::SAVE_DIR_MAPS;
```




<hr>



### variable SCALE\_FACTOR 

```C++
const std::string AIAC::Config::SCALE_FACTOR;
```




<hr>



### variable SCANNED\_MODEL 

```C++
const std::string AIAC::Config::SCANNED_MODEL;
```




<hr>



### variable SEC\_AIAC 

```C++
const std::string AIAC::Config::SEC_AIAC;
```




<hr>



### variable SEC\_TEST 

```C++
const std::string AIAC::Config::SEC_TEST;
```




<hr>



### variable SEC\_TOUCH\_MONITOR\_SPECS 

```C++
const std::string AIAC::Config::SEC_TOUCH_MONITOR_SPECS;
```




<hr>



### variable SEC\_TSLAM 

```C++
const std::string AIAC::Config::SEC_TSLAM;
```




<hr>



### variable SEC\_TTOOL 

```C++
const std::string AIAC::Config::SEC_TTOOL;
```




<hr>



### variable SEC\_UTILS 

```C++
const std::string AIAC::Config::SEC_UTILS;
```




<hr>



### variable STABILIZATION\_FRAME\_COUNT 

```C++
const std::string AIAC::Config::STABILIZATION_FRAME_COUNT;
```




<hr>



### variable TTOOL\_ROOT\_PATH 

```C++
const std::string AIAC::Config::TTOOL_ROOT_PATH;
```




<hr>



### variable UTILS\_PATH 

```C++
const std::string AIAC::Config::UTILS_PATH;
```




<hr>



### variable VIDEO\_PATH 

```C++
const std::string AIAC::Config::VIDEO_PATH;
```




<hr>



### variable VocFile 

```C++
const std::string AIAC::Config::VocFile;
```




<hr>
## Public Functions Documentation




### function Config 

```C++
inline AIAC::Config::Config (
    std::string filename,
    bool updateFile=true
) 
```




<hr>
## Public Static Functions Documentation




### function Get [1/2]

```C++
template<typename T>
static inline T AIAC::Config::Get (
    const std::string & section,
    const std::string & name
) 
```




<hr>



### function Get [2/2]

```C++
template<typename T>
static inline T AIAC::Config::Get (
    const std::string & section,
    const std::string & name,
    T && default_v
) 
```




<hr>



### function GetVector 

```C++
template<typename T>
static inline std::vector< T > AIAC::Config::GetVector (
    const std::string & section,
    const std::string & name,
    const std::vector< T > & default_v
) 
```




<hr>



### function InsertEntry [1/2]

```C++
template<typename T>
static inline void AIAC::Config::InsertEntry (
    const std::string & section,
    const std::string & name,
    const T & v
) 
```




<hr>



### function InsertEntry [2/2]

```C++
template<typename T>
static inline void AIAC::Config::InsertEntry (
    const std::string & section,
    const std::string & name,
    const std::vector< T > & vs
) 
```




<hr>



### function UpdateEntry [1/2]

```C++
template<typename T>
static inline void AIAC::Config::UpdateEntry (
    const std::string & section,
    const std::string & name,
    const T & v
) 
```




<hr>



### function UpdateEntry [2/2]

```C++
template<typename T>
static inline void AIAC::Config::UpdateEntry (
    const std::string & section,
    const std::string & name,
    const std::vector< T > & vs
) 
```




<hr>



### function WriteToFile 

```C++
static inline void AIAC::Config::WriteToFile (
    std::string writeFilename=""
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Config.h`

