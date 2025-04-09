

# Class glob::glob



[**ClassList**](annotated.md) **>** [**glob**](namespaceglob.md) **>** [**glob**](classglob_1_1glob.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::string | [**dir\_path**](#variable-dir_path)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**close**](#function-close) () <br> |
|  std::string | [**current\_match**](#function-current_match) () const<br> |
|   | [**glob**](#function-glob-12) (const std::string & pattern) <br> |
|  bool | [**is\_valid**](#function-is_valid) () const<br> |
|  bool | [**next**](#function-next) () <br> |
|  void | [**open**](#function-open) (const std::string & pattern) <br> |
|   | [**operator bool**](#function-operator-bool) () const<br> |
|   | [**~glob**](#function-glob) () <br> |




























## Public Attributes Documentation




### variable dir\_path 

```C++
std::string glob::glob::dir_path;
```




<hr>
## Public Functions Documentation




### function close 

```C++
void glob::glob::close () 
```




<hr>



### function current\_match 

```C++
std::string glob::glob::current_match () const
```




<hr>



### function glob [1/2]

```C++
glob::glob::glob (
    const std::string & pattern
) 
```




<hr>



### function is\_valid 

```C++
bool glob::glob::is_valid () const
```




<hr>



### function next 

```C++
bool glob::glob::next () 
```




<hr>



### function open 

```C++
void glob::glob::open (
    const std::string & pattern
) 
```




<hr>



### function operator bool 

```C++
inline glob::glob::operator bool () const
```




<hr>



### function ~glob 

```C++
glob::glob::~glob () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/glob.h`

