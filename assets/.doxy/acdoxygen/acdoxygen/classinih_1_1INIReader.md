

# Class inih::INIReader



[**ClassList**](annotated.md) **>** [**inih**](namespaceinih.md) **>** [**INIReader**](classinih_1_1INIReader.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  const std::unordered\_map&lt; std::string, std::string &gt; | [**Get**](#function-get-13) (std::string section) const<br> |
|  T | [**Get**](#function-get-23) (const std::string & section, const std::string & name) <br>_Return the value of the given key in the given section._  |
|  T | [**Get**](#function-get-33) (const std::string & section, const std::string & name, T & default\_v) <br>_Return the value of the given key in the given section, return default if not found._  |
|  std::vector&lt; T &gt; | [**GetVector**](#function-getvector-12) (const std::string & section, const std::string & name) <br>_Return the value array of the given key in the given section._  |
|  std::vector&lt; T &gt; | [**GetVector**](#function-getvector-22) (const std::string & section, const std::string & name, const std::vector&lt; T &gt; & default\_v) <br>_Return the value array of the given key in the given section, return default if not found._  |
|   | [**INIReader**](#function-inireader-13) () <br> |
|   | [**INIReader**](#function-inireader-23) (std::string filename) <br> |
|   | [**INIReader**](#function-inireader-33) (FILE \* file) <br> |
|  void | [**InsertEntry**](#function-insertentry-12) (const std::string & section, const std::string & name, const T & v) <br> |
|  void | [**InsertEntry**](#function-insertentry-22) (const std::string & section, const std::string & name, const std::vector&lt; T &gt; & vs) <br> |
|  const std::set&lt; std::string &gt; | [**Keys**](#function-keys) (std::string section) const<br>_Return the list of keys in the given section._  |
|  int | [**ParseError**](#function-parseerror) () const<br> |
|  const std::set&lt; std::string &gt; | [**Sections**](#function-sections) () const<br>_Return the list of sections found in ini file._  |
|  void | [**UpdateEntry**](#function-updateentry-12) (const std::string & section, const std::string & name, const T & v) <br> |
|  void | [**UpdateEntry**](#function-updateentry-22) (const std::string & section, const std::string & name, const std::vector&lt; T &gt; & vs) <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  int | [**\_error**](#variable-_error)  <br> |
|  std::unordered\_map&lt; std::string, std::unordered\_map&lt; std::string, std::string &gt; &gt; | [**\_values**](#variable-_values)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  const bool | [**BoolConverter**](#function-boolconverter) (std::string s) const<br> |
|  T | [**Converter**](#function-converter) (const std::string & s) const<br> |
|  std::string | [**V2String**](#function-v2string) (const T & v) const<br> |
|  std::string | [**Vec2String**](#function-vec2string) (const std::vector&lt; T &gt; & v) const<br> |


## Protected Static Functions

| Type | Name |
| ---: | :--- |
|  int | [**ValueHandler**](#function-valuehandler) (void \* user, const char \* section, const char \* name, const char \* value) <br> |


## Public Functions Documentation




### function Get [1/3]

```C++
inline const std::unordered_map< std::string, std::string > inih::INIReader::Get (
    std::string section
) const
```




<hr>



### function Get [2/3]

_Return the value of the given key in the given section._ 
```C++
template<typename T>
inline T inih::INIReader::Get (
    const std::string & section,
    const std::string & name
) 
```





**Parameters:**


* `section` The section name 
* `name` The key name 



**Returns:**

The value of the given key in the given section 





        

<hr>



### function Get [3/3]

_Return the value of the given key in the given section, return default if not found._ 
```C++
template<typename T>
inline T inih::INIReader::Get (
    const std::string & section,
    const std::string & name,
    T & default_v
) 
```





**Parameters:**


* `section` The section name 
* `name` The key name 
* `default_v` The default value 



**Returns:**

The value of the given key in the given section, return default if not found 





        

<hr>



### function GetVector [1/2]

_Return the value array of the given key in the given section._ 
```C++
template<typename T>
inline std::vector< T > inih::INIReader::GetVector (
    const std::string & section,
    const std::string & name
) 
```





**Parameters:**


* `section` The section name 
* `name` The key name 



**Returns:**

The value array of the given key in the given section.


For example: 
```C++
[section]
key = 1 2 3 4
```
 
```C++
const auto vs = ini.GetVector<std::vector<int>>("section", "key");
// vs = {1, 2, 3, 4}
```
 


        

<hr>



### function GetVector [2/2]

_Return the value array of the given key in the given section, return default if not found._ 
```C++
template<typename T>
inline std::vector< T > inih::INIReader::GetVector (
    const std::string & section,
    const std::string & name,
    const std::vector< T > & default_v
) 
```





**Parameters:**


* `section` The section name 
* `name` The key name 
* `default_v` The default value 



**Returns:**

The value array of the given key in the given section, return default if not found




**See also:** [**INIReader::GetVector**](classinih_1_1INIReader.md#function-getvector-12) 



        

<hr>



### function INIReader [1/3]

```C++
inline inih::INIReader::INIReader () 
```




<hr>



### function INIReader [2/3]

```C++
inline inih::INIReader::INIReader (
    std::string filename
) 
```




<hr>



### function INIReader [3/3]

```C++
inline inih::INIReader::INIReader (
    FILE * file
) 
```




<hr>



### function InsertEntry [1/2]

```C++
template<typename T>
inline void inih::INIReader::InsertEntry (
    const std::string & section,
    const std::string & name,
    const T & v
) 
```




<hr>



### function InsertEntry [2/2]

```C++
template<typename T>
inline void inih::INIReader::InsertEntry (
    const std::string & section,
    const std::string & name,
    const std::vector< T > & vs
) 
```




<hr>



### function Keys 

_Return the list of keys in the given section._ 
```C++
inline const std::set< std::string > inih::INIReader::Keys (
    std::string section
) const
```





**Parameters:**


* `section` The section name 



**Returns:**

The list of keys in the given section 





        

<hr>



### function ParseError 

```C++
inline int inih::INIReader::ParseError () const
```




<hr>



### function Sections 

_Return the list of sections found in ini file._ 
```C++
inline const std::set< std::string > inih::INIReader::Sections () const
```





**Returns:**

The list of sections found in ini file 





        

<hr>



### function UpdateEntry [1/2]

```C++
template<typename T>
inline void inih::INIReader::UpdateEntry (
    const std::string & section,
    const std::string & name,
    const T & v
) 
```




<hr>



### function UpdateEntry [2/2]

```C++
template<typename T>
inline void inih::INIReader::UpdateEntry (
    const std::string & section,
    const std::string & name,
    const std::vector< T > & vs
) 
```




<hr>
## Protected Attributes Documentation




### variable \_error 

```C++
int inih::INIReader::_error;
```




<hr>



### variable \_values 

```C++
std::unordered_map<std::string, std::unordered_map<std::string, std::string> > inih::INIReader::_values;
```




<hr>
## Protected Functions Documentation




### function BoolConverter 

```C++
inline const bool inih::INIReader::BoolConverter (
    std::string s
) const
```




<hr>



### function Converter 

```C++
template<typename T>
inline T inih::INIReader::Converter (
    const std::string & s
) const
```




<hr>



### function V2String 

```C++
template<typename T>
inline std::string inih::INIReader::V2String (
    const T & v
) const
```




<hr>



### function Vec2String 

```C++
template<typename T>
inline std::string inih::INIReader::Vec2String (
    const std::vector< T > & v
) const
```




<hr>
## Protected Static Functions Documentation




### function ValueHandler 

```C++
static inline int inih::INIReader::ValueHandler (
    void * user,
    const char * section,
    const char * name,
    const char * value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/Ini.h`

