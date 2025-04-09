

# File Ini.h



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**Ini.h**](Ini_8h.md)

[Go to the source code of this file](Ini_8h_source.md)



* `#include <ctype.h>`
* `#include <stdio.h>`
* `#include <string.h>`
* `#include <sys/stat.h>`
* `#include <algorithm>`
* `#include <cctype>`
* `#include <cstdlib>`
* `#include <fstream>`
* `#include <iostream>`
* `#include <iterator>`
* `#include <map>`
* `#include <set>`
* `#include <sstream>`
* `#include <string>`
* `#include <type_traits>`
* `#include <unordered_map>`
* `#include <vector>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**inih**](namespaceinih.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**INIReader**](classinih_1_1INIReader.md) <br> |
| class | [**INIWriter**](classinih_1_1INIWriter.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**HANDLER**](Ini_8h.md#define-handler) (u, s, n, v) `handler(u, s, n, v)`<br> |
| define  | [**INI\_INITIAL\_ALLOC**](Ini_8h.md#define-ini_initial_alloc)  `200`<br> |
| define  | [**INI\_INLINE\_COMMENT\_PREFIXES**](Ini_8h.md#define-ini_inline_comment_prefixes)  `";"`<br> |
| define  | [**INI\_MAX\_LINE**](Ini_8h.md#define-ini_max_line)  `2000`<br> |
| define  | [**INI\_START\_COMMENT\_PREFIXES**](Ini_8h.md#define-ini_start_comment_prefixes)  `";#"`<br> |
| define  | [**INI\_STOP\_ON\_FIRST\_ERROR**](Ini_8h.md#define-ini_stop_on_first_error)  `1`<br> |
| define  | [**MAX\_NAME**](Ini_8h.md#define-max_name)  `50`<br> |
| define  | [**MAX\_SECTION**](Ini_8h.md#define-max_section)  `50`<br> |
| define  | [**\_\_INIREADER\_H\_\_**](Ini_8h.md#define-__inireader_h__)  <br> |
| define  | [**\_\_INIREADER\_\_**](Ini_8h.md#define-__inireader__)  <br> |
| define  | [**\_\_INIWRITER\_H\_\_**](Ini_8h.md#define-__iniwriter_h__)  <br> |

## Macro Definition Documentation





### define HANDLER 

```C++
#define HANDLER (
    u,
    s,
    n,
    v
) `handler(u, s, n, v)`
```




<hr>



### define INI\_INITIAL\_ALLOC 

```C++
#define INI_INITIAL_ALLOC `200`
```




<hr>



### define INI\_INLINE\_COMMENT\_PREFIXES 

```C++
#define INI_INLINE_COMMENT_PREFIXES `";"`
```




<hr>



### define INI\_MAX\_LINE 

```C++
#define INI_MAX_LINE `2000`
```




<hr>



### define INI\_START\_COMMENT\_PREFIXES 

```C++
#define INI_START_COMMENT_PREFIXES `";#"`
```




<hr>



### define INI\_STOP\_ON\_FIRST\_ERROR 

```C++
#define INI_STOP_ON_FIRST_ERROR `1`
```




<hr>



### define MAX\_NAME 

```C++
#define MAX_NAME `50`
```




<hr>



### define MAX\_SECTION 

```C++
#define MAX_SECTION `50`
```




<hr>



### define \_\_INIREADER\_H\_\_ 

```C++
#define __INIREADER_H__ 
```




<hr>



### define \_\_INIREADER\_\_ 

```C++
#define __INIREADER__ 
```




<hr>



### define \_\_INIWRITER\_H\_\_ 

```C++
#define __INIWRITER_H__ 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/Ini.h`

