

# File ImGuiFileDialog.h



[**FileList**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**UI**](dir_1ecaf06ce723c740944fb523b6bd2c55.md) **>** [**ImGuiFileDialog.h**](ImGuiFileDialog_8h.md)

[Go to the source code of this file](ImGuiFileDialog_8h_source.md)



* `#include "ImGuiFileDialogConfig.h"`
* `#include <stdint.h>`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**IGFD\_Selection**](structIGFD__Selection.md) <br> |
| struct | [**IGFD\_Selection\_Pair**](structIGFD__Selection__Pair.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef int | [**IGFD\_FileStyleFlags**](#typedef-igfd_filestyleflags)  <br> |
| enum  | [**IGFD\_FileStyleFlags\_**](#enum-igfd_filestyleflags_)  <br> |
| typedef void(\* | [**IGFD\_PaneFun**](#typedef-igfd_panefun)  <br> |
| typedef struct [**IGFD\_Selection**](structIGFD__Selection.md) | [**IGFD\_Selection**](#typedef-igfd_selection)  <br> |
| typedef struct [**IGFD\_Selection\_Pair**](structIGFD__Selection__Pair.md) | [**IGFD\_Selection\_Pair**](#typedef-igfd_selection_pair)  <br> |
| typedef struct ImGuiFileDialog | [**ImGuiFileDialog**](#typedef-imguifiledialog)  <br> |
| typedef int | [**ImGuiFileDialogFlags**](#typedef-imguifiledialogflags)  <br> |
| enum  | [**ImGuiFileDialogFlags\_**](#enum-imguifiledialogflags_)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_ClearFilesStyle**](#function-igfd_clearfilesstyle) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_CloseDialog**](#function-igfd_closedialog) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API ImGuiFileDialog \* | [**IGFD\_Create**](#function-igfd_create) (void) <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_Destroy**](#function-igfd_destroy) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API bool | [**IGFD\_DisplayDialog**](#function-igfd_displaydialog) (ImGuiFileDialog \* vContext, const char \* vKey, ImGuiWindowFlags vFlags, ImVec2 vMinSize, ImVec2 vMaxSize) <br> |
|  IMGUIFILEDIALOG\_API char \* | [**IGFD\_GetCurrentFileName**](#function-igfd_getcurrentfilename) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API char \* | [**IGFD\_GetCurrentFilter**](#function-igfd_getcurrentfilter) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API char \* | [**IGFD\_GetCurrentPath**](#function-igfd_getcurrentpath) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API char \* | [**IGFD\_GetFilePathName**](#function-igfd_getfilepathname) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API bool | [**IGFD\_GetFileStyle**](#function-igfd_getfilestyle) (ImGuiFileDialog \* vContext, IGFD\_FileStyleFlags vFileStyleFlags, const char \* vFilter, ImVec4 \* vOutColor, char \*\* vOutIconText, ImFont \*\* vOutFont) <br> |
|  IMGUIFILEDIALOG\_API [**IGFD\_Selection**](structIGFD__Selection.md) | [**IGFD\_GetSelection**](#function-igfd_getselection) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API void \* | [**IGFD\_GetUserDatas**](#function-igfd_getuserdatas) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API bool | [**IGFD\_IsKeyOpened**](#function-igfd_iskeyopened) (ImGuiFileDialog \* vContext, const char \* vCurrentOpenedKey) <br> |
|  IMGUIFILEDIALOG\_API bool | [**IGFD\_IsOk**](#function-igfd_isok) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API bool | [**IGFD\_IsOpened**](#function-igfd_isopened) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_OpenDialog**](#function-igfd_opendialog) (ImGuiFileDialog \* vContext, const char \* vKey, const char \* vTitle, const char \* vFilters, const char \* vPath, const char \* vFileName, const int vCountSelectionMax, void \* vUserDatas, ImGuiFileDialogFlags vFlags) <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_OpenDialog2**](#function-igfd_opendialog2) (ImGuiFileDialog \* vContext, const char \* vKey, const char \* vTitle, const char \* vFilters, const char \* vFilePathName, const int vCountSelectionMax, void \* vUserDatas, ImGuiFileDialogFlags vFlags) <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_OpenPaneDialog**](#function-igfd_openpanedialog) (ImGuiFileDialog \* vContext, const char \* vKey, const char \* vTitle, const char \* vFilters, const char \* vPath, const char \* vFileName, const IGFD\_PaneFun vSidePane, const float vSidePaneWidth, const int vCountSelectionMax, void \* vUserDatas, ImGuiFileDialogFlags vFlags) <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_OpenPaneDialog2**](#function-igfd_openpanedialog2) (ImGuiFileDialog \* vContext, const char \* vKey, const char \* vTitle, const char \* vFilters, const char \* vFilePathName, const IGFD\_PaneFun vSidePane, const float vSidePaneWidth, const int vCountSelectionMax, void \* vUserDatas, ImGuiFileDialogFlags vFlags) <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_Selection\_DestroyContent**](#function-igfd_selection_destroycontent) ([**IGFD\_Selection**](structIGFD__Selection.md) \* vSelection) <br> |
|  IMGUIFILEDIALOG\_API [**IGFD\_Selection**](structIGFD__Selection.md) | [**IGFD\_Selection\_Get**](#function-igfd_selection_get) () <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_Selection\_Pair\_DestroyContent**](#function-igfd_selection_pair_destroycontent) ([**IGFD\_Selection\_Pair**](structIGFD__Selection__Pair.md) \* vSelection\_Pair) <br> |
|  IMGUIFILEDIALOG\_API [**IGFD\_Selection\_Pair**](structIGFD__Selection__Pair.md) | [**IGFD\_Selection\_Pair\_Get**](#function-igfd_selection_pair_get) () <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_SetFileStyle**](#function-igfd_setfilestyle) (ImGuiFileDialog \* vContext, IGFD\_FileStyleFlags vFileStyleFlags, const char \* vFilter, ImVec4 vColor, const char \* vIconText, ImFont \* vFont) <br> |
|  IMGUIFILEDIALOG\_API void | [**IGFD\_SetFileStyle2**](#function-igfd_setfilestyle2) (ImGuiFileDialog \* vContext, IGFD\_FileStyleFlags vFileStyleFlags, const char \* vFilter, float vR, float vG, float vB, float vA, const char \* vIconText, ImFont \* vFont) <br> |
|  IMGUIFILEDIALOG\_API bool | [**IGFD\_WasKeyOpenedThisFrame**](#function-igfd_waskeyopenedthisframe) (ImGuiFileDialog \* vContext, const char \* vKey) <br> |
|  IMGUIFILEDIALOG\_API bool | [**IGFD\_WasOpenedThisFrame**](#function-igfd_wasopenedthisframe) (ImGuiFileDialog \* vContext) <br> |
|  IMGUIFILEDIALOG\_API void | [**SetLocales**](#function-setlocales) (ImGuiFileDialog \* vContext, const int vCategory, const char \* vBeginLocale, const char \* vEndLocale) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**API**](ImGuiFileDialog_8h.md#define-api)  <br> |
| define  | [**IMGUIFILEDIALOG\_API**](ImGuiFileDialog_8h.md#define-imguifiledialog_api)  <br> |
| define  | [**IMGUIFILEDIALOG\_VERSION**](ImGuiFileDialog_8h.md#define-imguifiledialog_version)  `"v0.6.5"`<br> |

## Public Types Documentation




### typedef IGFD\_FileStyleFlags 

```C++
typedef int IGFD_FileStyleFlags;
```




<hr>



### enum IGFD\_FileStyleFlags\_ 

```C++
enum IGFD_FileStyleFlags_ {
    IGFD_FileStyle_None = 0,
    IGFD_FileStyleByTypeFile = (1 << 0),
    IGFD_FileStyleByTypeDir = (1 << 1),
    IGFD_FileStyleByTypeLink = (1 << 2),
    IGFD_FileStyleByExtention = (1 << 3),
    IGFD_FileStyleByFullName = (1 << 4),
    IGFD_FileStyleByContainedInFullName = (1 << 5)
};
```




<hr>



### typedef IGFD\_PaneFun 

```C++
typedef void(* IGFD_PaneFun) (const char *, void *, bool *);
```




<hr>



### typedef IGFD\_Selection 

```C++
typedef struct IGFD_Selection IGFD_Selection;
```




<hr>



### typedef IGFD\_Selection\_Pair 

```C++
typedef struct IGFD_Selection_Pair IGFD_Selection_Pair;
```




<hr>



### typedef ImGuiFileDialog 

```C++
typedef struct ImGuiFileDialog ImGuiFileDialog;
```




<hr>



### typedef ImGuiFileDialogFlags 

```C++
typedef int ImGuiFileDialogFlags;
```




<hr>



### enum ImGuiFileDialogFlags\_ 

```C++
enum ImGuiFileDialogFlags_ {
    ImGuiFileDialogFlags_None = 0,
    ImGuiFileDialogFlags_ConfirmOverwrite = (1 << 0),
    ImGuiFileDialogFlags_DontShowHiddenFiles = (1 << 1),
    ImGuiFileDialogFlags_DisableCreateDirectoryButton = (1 << 2),
    ImGuiFileDialogFlags_HideColumnType = (1 << 3),
    ImGuiFileDialogFlags_HideColumnSize = (1 << 4),
    ImGuiFileDialogFlags_HideColumnDate = (1 << 5),
    ImGuiFileDialogFlags_NoDialog = (1 << 6),
    ImGuiFileDialogFlags_ReadOnlyFileNameField = (1 << 7),
    ImGuiFileDialogFlags_CaseInsensitiveExtention = (1 << 8),
    ImGuiFileDialogFlags_Modal = (1 << 9),
    ImGuiFileDialogFlags_Default = ImGuiFileDialogFlags_ConfirmOverwrite
};
```




<hr>
## Public Functions Documentation




### function IGFD\_ClearFilesStyle 

```C++
IMGUIFILEDIALOG_API void IGFD_ClearFilesStyle (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_CloseDialog 

```C++
IMGUIFILEDIALOG_API void IGFD_CloseDialog (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_Create 

```C++
IMGUIFILEDIALOG_API ImGuiFileDialog * IGFD_Create (
    void
) 
```




<hr>



### function IGFD\_Destroy 

```C++
IMGUIFILEDIALOG_API void IGFD_Destroy (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_DisplayDialog 

```C++
IMGUIFILEDIALOG_API bool IGFD_DisplayDialog (
    ImGuiFileDialog * vContext,
    const char * vKey,
    ImGuiWindowFlags vFlags,
    ImVec2 vMinSize,
    ImVec2 vMaxSize
) 
```




<hr>



### function IGFD\_GetCurrentFileName 

```C++
IMGUIFILEDIALOG_API char * IGFD_GetCurrentFileName (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_GetCurrentFilter 

```C++
IMGUIFILEDIALOG_API char * IGFD_GetCurrentFilter (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_GetCurrentPath 

```C++
IMGUIFILEDIALOG_API char * IGFD_GetCurrentPath (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_GetFilePathName 

```C++
IMGUIFILEDIALOG_API char * IGFD_GetFilePathName (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_GetFileStyle 

```C++
IMGUIFILEDIALOG_API bool IGFD_GetFileStyle (
    ImGuiFileDialog * vContext,
    IGFD_FileStyleFlags vFileStyleFlags,
    const char * vFilter,
    ImVec4 * vOutColor,
    char ** vOutIconText,
    ImFont ** vOutFont
) 
```




<hr>



### function IGFD\_GetSelection 

```C++
IMGUIFILEDIALOG_API IGFD_Selection IGFD_GetSelection (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_GetUserDatas 

```C++
IMGUIFILEDIALOG_API void * IGFD_GetUserDatas (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_IsKeyOpened 

```C++
IMGUIFILEDIALOG_API bool IGFD_IsKeyOpened (
    ImGuiFileDialog * vContext,
    const char * vCurrentOpenedKey
) 
```




<hr>



### function IGFD\_IsOk 

```C++
IMGUIFILEDIALOG_API bool IGFD_IsOk (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_IsOpened 

```C++
IMGUIFILEDIALOG_API bool IGFD_IsOpened (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function IGFD\_OpenDialog 

```C++
IMGUIFILEDIALOG_API void IGFD_OpenDialog (
    ImGuiFileDialog * vContext,
    const char * vKey,
    const char * vTitle,
    const char * vFilters,
    const char * vPath,
    const char * vFileName,
    const int vCountSelectionMax,
    void * vUserDatas,
    ImGuiFileDialogFlags vFlags
) 
```




<hr>



### function IGFD\_OpenDialog2 

```C++
IMGUIFILEDIALOG_API void IGFD_OpenDialog2 (
    ImGuiFileDialog * vContext,
    const char * vKey,
    const char * vTitle,
    const char * vFilters,
    const char * vFilePathName,
    const int vCountSelectionMax,
    void * vUserDatas,
    ImGuiFileDialogFlags vFlags
) 
```




<hr>



### function IGFD\_OpenPaneDialog 

```C++
IMGUIFILEDIALOG_API void IGFD_OpenPaneDialog (
    ImGuiFileDialog * vContext,
    const char * vKey,
    const char * vTitle,
    const char * vFilters,
    const char * vPath,
    const char * vFileName,
    const IGFD_PaneFun vSidePane,
    const float vSidePaneWidth,
    const int vCountSelectionMax,
    void * vUserDatas,
    ImGuiFileDialogFlags vFlags
) 
```




<hr>



### function IGFD\_OpenPaneDialog2 

```C++
IMGUIFILEDIALOG_API void IGFD_OpenPaneDialog2 (
    ImGuiFileDialog * vContext,
    const char * vKey,
    const char * vTitle,
    const char * vFilters,
    const char * vFilePathName,
    const IGFD_PaneFun vSidePane,
    const float vSidePaneWidth,
    const int vCountSelectionMax,
    void * vUserDatas,
    ImGuiFileDialogFlags vFlags
) 
```




<hr>



### function IGFD\_Selection\_DestroyContent 

```C++
IMGUIFILEDIALOG_API void IGFD_Selection_DestroyContent (
    IGFD_Selection * vSelection
) 
```




<hr>



### function IGFD\_Selection\_Get 

```C++
IMGUIFILEDIALOG_API IGFD_Selection IGFD_Selection_Get () 
```




<hr>



### function IGFD\_Selection\_Pair\_DestroyContent 

```C++
IMGUIFILEDIALOG_API void IGFD_Selection_Pair_DestroyContent (
    IGFD_Selection_Pair * vSelection_Pair
) 
```




<hr>



### function IGFD\_Selection\_Pair\_Get 

```C++
IMGUIFILEDIALOG_API IGFD_Selection_Pair IGFD_Selection_Pair_Get () 
```




<hr>



### function IGFD\_SetFileStyle 

```C++
IMGUIFILEDIALOG_API void IGFD_SetFileStyle (
    ImGuiFileDialog * vContext,
    IGFD_FileStyleFlags vFileStyleFlags,
    const char * vFilter,
    ImVec4 vColor,
    const char * vIconText,
    ImFont * vFont
) 
```




<hr>



### function IGFD\_SetFileStyle2 

```C++
IMGUIFILEDIALOG_API void IGFD_SetFileStyle2 (
    ImGuiFileDialog * vContext,
    IGFD_FileStyleFlags vFileStyleFlags,
    const char * vFilter,
    float vR,
    float vG,
    float vB,
    float vA,
    const char * vIconText,
    ImFont * vFont
) 
```




<hr>



### function IGFD\_WasKeyOpenedThisFrame 

```C++
IMGUIFILEDIALOG_API bool IGFD_WasKeyOpenedThisFrame (
    ImGuiFileDialog * vContext,
    const char * vKey
) 
```




<hr>



### function IGFD\_WasOpenedThisFrame 

```C++
IMGUIFILEDIALOG_API bool IGFD_WasOpenedThisFrame (
    ImGuiFileDialog * vContext
) 
```




<hr>



### function SetLocales 

```C++
IMGUIFILEDIALOG_API void SetLocales (
    ImGuiFileDialog * vContext,
    const int vCategory,
    const char * vBeginLocale,
    const char * vEndLocale
) 
```




<hr>
## Macro Definition Documentation





### define API 

```C++
#define API 
```




<hr>



### define IMGUIFILEDIALOG\_API 

```C++
#define IMGUIFILEDIALOG_API 
```




<hr>



### define IMGUIFILEDIALOG\_VERSION 

```C++
#define IMGUIFILEDIALOG_VERSION `"v0.6.5"`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/UI/ImGuiFileDialog.h`

