

# Class CircularBuffer

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**CircularBuffer**](classCircularBuffer.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef BufferIterator&lt; true &gt; | [**const\_iterator**](#typedef-const_iterator)  <br> |
| typedef BufferIterator&lt; false &gt; | [**iterator**](#typedef-iterator)  <br> |
| typedef T | [**value\_type**](#typedef-value_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CircularBuffer**](#function-circularbuffer-13) (size\_t size) <br> |
|   | [**CircularBuffer**](#function-circularbuffer-23) (const [**CircularBuffer**](classCircularBuffer.md) & other) <br> |
|   | [**CircularBuffer**](#function-circularbuffer-33) ([**CircularBuffer**](classCircularBuffer.md) && other) noexcept<br> |
|  const\_reference | [**at**](#function-at-12) (size\_type index) const<br> |
|  reference | [**at**](#function-at-22) (size\_type index) <br> |
|  reference | [**back**](#function-back-12) () <br> |
|  const\_reference | [**back**](#function-back-22) () const<br> |
|  iterator | [**begin**](#function-begin-12) () <br> |
|  const\_iterator | [**begin**](#function-begin-22) () const<br> |
|  size\_type | [**buffer\_size**](#function-buffer_size) () const<br> |
|  size\_type | [**capacity**](#function-capacity) () const<br> |
|  const\_iterator | [**cbegin**](#function-cbegin) () noexcept const<br> |
|  const\_iterator | [**cend**](#function-cend) () noexcept const<br> |
|  void | [**clear**](#function-clear) () <br> |
|  const\_pointer | [**data**](#function-data) () const<br> |
|  bool | [**empty**](#function-empty) () const<br> |
|  iterator | [**end**](#function-end-12) () <br> |
|  const\_iterator | [**end**](#function-end-22) () const<br> |
|  reference | [**front**](#function-front-12) () <br> |
|  const\_reference | [**front**](#function-front-22) () const<br> |
|  bool | [**full**](#function-full) () const<br> |
|  [**CircularBuffer**](classCircularBuffer.md) & | [**operator=**](#function-operator) (const [**CircularBuffer**](classCircularBuffer.md) & other) <br> |
|  [**CircularBuffer**](classCircularBuffer.md) & | [**operator=**](#function-operator_1) ([**CircularBuffer**](classCircularBuffer.md) && other) noexcept<br> |
|  const\_reference | [**operator[]**](#function-operator_2) (size\_type index) const<br> |
|  reference | [**operator[]**](#function-operator_3) (size\_type index) <br> |
|  void | [**pop\_front**](#function-pop_front) () <br> |
|  void | [**push\_back**](#function-push_back-12) (const value\_type & data) <br> |
|  void | [**push\_back**](#function-push_back-22) (value\_type && data) noexcept<br> |
|  iterator | [**rbegin**](#function-rbegin-12) () noexcept<br> |
|  const\_iterator | [**rbegin**](#function-rbegin-22) () noexcept const<br> |
|  iterator | [**rend**](#function-rend-12) () noexcept<br> |
|  const\_iterator | [**rend**](#function-rend-22) () noexcept const<br> |
|  size\_type | [**size**](#function-size) () const<br> |




























## Public Types Documentation




### typedef const\_iterator 

```C++
typedef BufferIterator<true> CircularBuffer< T >::const_iterator;
```




<hr>



### typedef iterator 

```C++
typedef BufferIterator<false> CircularBuffer< T >::iterator;
```




<hr>



### typedef value\_type 

```C++
typedef T CircularBuffer< T >::value_type;
```




<hr>
## Public Functions Documentation




### function CircularBuffer [1/3]

```C++
inline explicit CircularBuffer::CircularBuffer (
    size_t size
) 
```




<hr>



### function CircularBuffer [2/3]

```C++
inline CircularBuffer::CircularBuffer (
    const CircularBuffer & other
) 
```




<hr>



### function CircularBuffer [3/3]

```C++
inline CircularBuffer::CircularBuffer (
    CircularBuffer && other
) noexcept
```




<hr>



### function at [1/2]

```C++
inline const_reference CircularBuffer::at (
    size_type index
) const
```




<hr>



### function at [2/2]

```C++
inline reference CircularBuffer::at (
    size_type index
) 
```




<hr>



### function back [1/2]

```C++
inline reference CircularBuffer::back () 
```




<hr>



### function back [2/2]

```C++
inline const_reference CircularBuffer::back () const
```




<hr>



### function begin [1/2]

```C++
inline iterator CircularBuffer::begin () 
```




<hr>



### function begin [2/2]

```C++
inline const_iterator CircularBuffer::begin () const
```




<hr>



### function buffer\_size 

```C++
inline size_type CircularBuffer::buffer_size () const
```




<hr>



### function capacity 

```C++
inline size_type CircularBuffer::capacity () const
```




<hr>



### function cbegin 

```C++
inline const_iterator CircularBuffer::cbegin () noexcept const
```




<hr>



### function cend 

```C++
inline const_iterator CircularBuffer::cend () noexcept const
```




<hr>



### function clear 

```C++
inline void CircularBuffer::clear () 
```




<hr>



### function data 

```C++
inline const_pointer CircularBuffer::data () const
```




<hr>



### function empty 

```C++
inline bool CircularBuffer::empty () const
```




<hr>



### function end [1/2]

```C++
inline iterator CircularBuffer::end () 
```




<hr>



### function end [2/2]

```C++
inline const_iterator CircularBuffer::end () const
```




<hr>



### function front [1/2]

```C++
inline reference CircularBuffer::front () 
```




<hr>



### function front [2/2]

```C++
inline const_reference CircularBuffer::front () const
```




<hr>



### function full 

```C++
inline bool CircularBuffer::full () const
```




<hr>



### function operator= 

```C++
inline CircularBuffer & CircularBuffer::operator= (
    const CircularBuffer & other
) 
```




<hr>



### function operator= 

```C++
inline CircularBuffer & CircularBuffer::operator= (
    CircularBuffer && other
) noexcept
```




<hr>



### function operator[] 

```C++
inline const_reference CircularBuffer::operator[] (
    size_type index
) const
```




<hr>



### function operator[] 

```C++
inline reference CircularBuffer::operator[] (
    size_type index
) 
```




<hr>



### function pop\_front 

```C++
inline void CircularBuffer::pop_front () 
```




<hr>



### function push\_back [1/2]

```C++
inline void CircularBuffer::push_back (
    const value_type & data
) 
```




<hr>



### function push\_back [2/2]

```C++
inline void CircularBuffer::push_back (
    value_type && data
) noexcept
```




<hr>



### function rbegin [1/2]

```C++
inline iterator CircularBuffer::rbegin () noexcept
```




<hr>



### function rbegin [2/2]

```C++
inline const_iterator CircularBuffer::rbegin () noexcept const
```




<hr>



### function rend [1/2]

```C++
inline iterator CircularBuffer::rend () noexcept
```




<hr>



### function rend [2/2]

```C++
inline const_iterator CircularBuffer::rend () noexcept const
```




<hr>



### function size 

```C++
inline size_type CircularBuffer::size () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/utils/CircularBuffer.h`

