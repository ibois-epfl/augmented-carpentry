

# File Base.h



[**FileList**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Base.h**](Base_8h.md)

[Go to the source code of this file](Base_8h_source.md)



* `#include "AIAC/Log.h"`
* `#include "AIAC/Assert.h"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**AIAC**](namespaceAIAC.md) <br> |



















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**AIAC\_BIND\_EVENT\_FN**](Base_8h.md#define-aiac_bind_event_fn) (fn) `[this](auto&&... args) -&gt; decltype(auto) { return this-&gt;fn(std::forward&lt;decltype(args)&gt;(args)...); }`<br> |
| define  | [**AIAC\_EXPAND\_MACRO**](Base_8h.md#define-aiac_expand_macro) (x) `x`<br> |
| define  | [**AIAC\_STRINGIFY\_MACRO**](Base_8h.md#define-aiac_stringify_macro) (x) `#x`<br> |
| define  | [**BIT**](Base_8h.md#define-bit) (x) `(1 &lt;&lt; x)`<br> |

## Macro Definition Documentation





### define AIAC\_BIND\_EVENT\_FN 

```C++
#define AIAC_BIND_EVENT_FN (
    fn
) `[this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }`
```




<hr>



### define AIAC\_EXPAND\_MACRO 

```C++
#define AIAC_EXPAND_MACRO (
    x
) `x`
```




<hr>



### define AIAC\_STRINGIFY\_MACRO 

```C++
#define AIAC_STRINGIFY_MACRO (
    x
) `#x`
```




<hr>



### define BIT 

```C++
#define BIT (
    x
) `(1 << x)`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Base.h`

