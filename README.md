
This simple example demonstrates how to serialize/deserialize a POD-type object to binary file with padding.

## POD Class

The POD class contains five members, two of which are reserved regions:

|name|width (bytes)|
|:--|:--:|
|m_flag|1|
|m_reserved_one|10|
|m_field_one|10|
|m_reserved_two|10|
|m_field_two|10|

As with all POD classes, you must initialize the object using aggregate initialization:

```
// Note: 
// 1. All members are zero-initialized so if you dont care 
//    the member can be initialised with empty braces
// 2. Ascii text can be initialized using a string literal

PodRecord podRecord { 
    true, 
    {}, // reserved
    {0xD,0xE,0xA,0xD, 0xB, 0xE, 0xE, 0xF},
    {}, // reserved
    "1.1.1.1"
};
```

## Serialization

The serialized binary file contains the following data:

![alt text](image-1.png)

Some noteworthy points:

- The class member widths are honoured regardless of the input width; the serialization automtically zero-pads the remaining bytes. If the input width exceeds the class member width it will cause an error at compile-time.
- Because we are using POD classes, the member declaration order must be mirrored when reading/writing in the serialization/deserialization operation.

Two examples of serialization/deserialization are shown. Both methods use streams:

1. Using overloaded insertion/extraction operators. 
   - The right hand operand is a user-defined object so the overloaded operator must be a non-member. Here we use `friend` to allow the operator to be placed within the class declaration.
2. Using member functions. 
   - Allows direct access to POD members from with the serialization/deserialization function.

I am torn between which method I prefer here: I like the stream syntax exposed to the user by the first method, but I prefer the encapsulation offered by the second method. In my opinion, having a non-member function as a custom object serializer/deserializer is an anti-pattern.


## Pretty Printing

A helper template function returns a string representation of any member in either hex or ascii.

```
// all outputs formatted as hex bytes
1
deadbeef00
312e312e312e31000

// last output formatted as ascii
1
deadbeef00
1.1.1.1
```
