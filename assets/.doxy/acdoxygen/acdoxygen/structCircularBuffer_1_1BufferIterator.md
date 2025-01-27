

# Struct CircularBuffer::BufferIterator

**template &lt;bool isConst&gt;**



[**ClassList**](annotated.md) **>** [**BufferIterator**](structCircularBuffer_1_1BufferIterator.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::conditional&lt; isConst, constCircularBuffer&lt; value\_type &gt; \*, [**CircularBuffer**](classCircularBuffer.md)&lt; value\_type &gt; \* &gt;::type | [**cbuf\_pointer**](#typedef-cbuf_pointer)  <br> |
| typedef ptrdiff\_t | [**difference\_type**](#typedef-difference_type)  <br> |
| typedef std::random\_access\_iterator\_tag | [**iterator\_category**](#typedef-iterator_category)  <br> |
| typedef std::conditional&lt; isConst, constvalue\_type \*, value\_type \* &gt;::type | [**pointer**](#typedef-pointer)  <br> |
| typedef std::conditional&lt; isConst, constvalue\_type &, value\_type & &gt;::type | [**reference**](#typedef-reference)  <br> |
| typedef T | [**value\_type**](#typedef-value_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BufferIterator**](#function-bufferiterator-12) () <br> |
|   | [**BufferIterator**](#function-bufferiterator-22) (const BufferIterator&lt; false &gt; & it) <br> |
|  bool | [**operator!=**](#function-operator) (const BufferIterator & other) const<br> |
|  reference | [**operator\***](#function-operator_1) () <br> |
|  BufferIterator & | [**operator++**](#function-operator_2) () <br> |
|  BufferIterator | [**operator++**](#function-operator_3) (int) <br> |
|  BufferIterator & | [**operator+=**](#function-operator_4) (difference\_type n) <br> |
|  BufferIterator & | [**operator--**](#function-operator_5) () <br> |
|  BufferIterator | [**operator--**](#function-operator_6) (int) <br> |
|  BufferIterator & | [**operator-=**](#function-operator_7) (difference\_type n) <br> |
|  pointer | [**operator-&gt;**](#function-operator_8) () <br> |
|  bool | [**operator&lt;**](#function-operator_9) (const BufferIterator & other) const<br> |
|  bool | [**operator&lt;=**](#function-operator_10) (const BufferIterator & other) const<br> |
|  bool | [**operator==**](#function-operator_11) (const BufferIterator & other) const<br> |
|  bool | [**operator&gt;**](#function-operator_12) (const BufferIterator & other) const<br> |
|  bool | [**operator&gt;=**](#function-operator_13) (const BufferIterator & other) const<br> |
|  reference | [**operator[]**](#function-operator_14) (size\_type index) <br> |




























## Public Types Documentation




### typedef cbuf\_pointer 

```C++
typedef std::conditional<isConst,constCircularBuffer<value_type>*,CircularBuffer<value_type>*>::type CircularBuffer< T >::BufferIterator< isConst >::cbuf_pointer;
```




<hr>



### typedef difference\_type 

```C++
typedef ptrdiff_t CircularBuffer< T >::BufferIterator< isConst >::difference_type;
```




<hr>



### typedef iterator\_category 

```C++
typedef std::random_access_iterator_tag CircularBuffer< T >::BufferIterator< isConst >::iterator_category;
```




<hr>



### typedef pointer 

```C++
typedef std::conditional<isConst,constvalue_type*,value_type*>::type CircularBuffer< T >::BufferIterator< isConst >::pointer;
```




<hr>



### typedef reference 

```C++
typedef std::conditional<isConst,constvalue_type&,value_type&>::type CircularBuffer< T >::BufferIterator< isConst >::reference;
```




<hr>



### typedef value\_type 

```C++
typedef T CircularBuffer< T >::BufferIterator< isConst >::value_type;
```




<hr>
## Public Functions Documentation




### function BufferIterator [1/2]

```C++
inline BufferIterator::BufferIterator () 
```




<hr>



### function BufferIterator [2/2]

```C++
inline BufferIterator::BufferIterator (
    const BufferIterator< false > & it
) 
```




<hr>



### function operator!= 

```C++
inline bool BufferIterator::operator!= (
    const BufferIterator & other
) const
```




<hr>



### function operator\* 

```C++
inline reference BufferIterator::operator* () 
```




<hr>



### function operator++ 

```C++
inline BufferIterator & BufferIterator::operator++ () 
```




<hr>



### function operator++ 

```C++
inline BufferIterator BufferIterator::operator++ (
    int
) 
```




<hr>



### function operator+= 

```C++
inline BufferIterator & BufferIterator::operator+= (
    difference_type n
) 
```




<hr>



### function operator-- 

```C++
inline BufferIterator & BufferIterator::operator-- () 
```




<hr>



### function operator-- 

```C++
inline BufferIterator BufferIterator::operator-- (
    int
) 
```




<hr>



### function operator-= 

```C++
inline BufferIterator & BufferIterator::operator-= (
    difference_type n
) 
```




<hr>



### function operator-&gt; 

```C++
inline pointer BufferIterator::operator-> () 
```




<hr>



### function operator&lt; 

```C++
inline bool BufferIterator::operator< (
    const BufferIterator & other
) const
```




<hr>



### function operator&lt;= 

```C++
inline bool BufferIterator::operator<= (
    const BufferIterator & other
) const
```




<hr>



### function operator== 

```C++
inline bool BufferIterator::operator== (
    const BufferIterator & other
) const
```




<hr>



### function operator&gt; 

```C++
inline bool BufferIterator::operator> (
    const BufferIterator & other
) const
```




<hr>



### function operator&gt;= 

```C++
inline bool BufferIterator::operator>= (
    const BufferIterator & other
) const
```




<hr>



### function operator[] 

```C++
inline reference BufferIterator::operator[] (
    size_type index
) 
```




<hr>## Friends Documentation





### friend CircularBuffer&lt; T &gt; 

```C++
class BufferIterator::CircularBuffer< T > (
    CircularBuffer < T >
) 
```




<hr>



### friend operator+ 

```C++
inline BufferIterator BufferIterator::operator+ (
    BufferIterator lhsiter,
    difference_type n
) 
```




<hr>



### friend operator+ 

```C++
inline BufferIterator BufferIterator::operator+ (
    difference_type n,
    BufferIterator rhsiter
) 
```




<hr>



### friend operator- 

```C++
inline BufferIterator BufferIterator::operator- (
    BufferIterator lhsiter,
    difference_type n
) 
```




<hr>



### friend operator- 

```C++
inline difference_type BufferIterator::operator- (
    const BufferIterator & lhsiter,
    const BufferIterator & rhsiter
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/CircularBuffer.h`

