

# Namespace inih



[**Namespace List**](namespaces.md) **>** [**inih**](namespaceinih.md)



[More...](#detailed-description)
















## Classes

| Type | Name |
| ---: | :--- |
| class | [**INIReader**](classinih_1_1INIReader.md) <br> |
| class | [**INIWriter**](classinih_1_1INIWriter.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef int(\* | [**ini\_handler**](#typedef-ini_handler)  <br> |
| typedef char \*(\* | [**ini\_reader**](#typedef-ini_reader)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**ini\_parse**](#function-ini_parse) (const char \* filename, ini\_handler handler, void \* user) <br> |
|  int | [**ini\_parse\_file**](#function-ini_parse_file) (FILE \* file, ini\_handler handler, void \* user) <br> |
|  int | [**ini\_parse\_stream**](#function-ini_parse_stream) (ini\_reader reader, void \* stream, ini\_handler handler, void \* user) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  char \* | [**find\_chars\_or\_comment**](#function-find_chars_or_comment) (const char \* s, const char \* chars) <br> |
|  char \* | [**lskip**](#function-lskip) (const char \* s) <br> |
|  char \* | [**rstrip**](#function-rstrip) (char \* s) <br> |
|  char \* | [**strncpy0**](#function-strncpy0) (char \* dest, const char \* src, size\_t size) <br> |


























## Detailed Description


Yet another .ini parser for modern c++ (made for cpp17), inspired and extend from @benhoyt's inih. See project page: [https://github.com/SSARCandy/ini-cpp](https://github.com/SSARCandy/ini-cpp) 


    
## Public Types Documentation




### typedef ini\_handler 

```C++
typedef int(* inih::ini_handler) (void *user, const char *section, const char *name, const char *value);
```




<hr>



### typedef ini\_reader 

```C++
typedef char *(* inih::ini_reader) (char *str, int num, void *stream);
```




<hr>
## Public Functions Documentation




### function ini\_parse 

```C++
inline int inih::ini_parse (
    const char * filename,
    ini_handler handler,
    void * user
) 
```




<hr>



### function ini\_parse\_file 

```C++
inline int inih::ini_parse_file (
    FILE * file,
    ini_handler handler,
    void * user
) 
```




<hr>



### function ini\_parse\_stream 

```C++
inline int inih::ini_parse_stream (
    ini_reader reader,
    void * stream,
    ini_handler handler,
    void * user
) 
```




<hr>
## Public Static Functions Documentation




### function find\_chars\_or\_comment 

```C++
static inline char * inih::find_chars_or_comment (
    const char * s,
    const char * chars
) 
```




<hr>



### function lskip 

```C++
static inline char * inih::lskip (
    const char * s
) 
```




<hr>



### function rstrip 

```C++
static inline char * inih::rstrip (
    char * s
) 
```




<hr>



### function strncpy0 

```C++
static inline char * inih::strncpy0 (
    char * dest,
    const char * src,
    size_t size
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/Ini.h`

