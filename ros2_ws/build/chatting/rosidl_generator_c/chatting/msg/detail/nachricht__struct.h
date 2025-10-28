// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from chatting:msg/Nachricht.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "chatting/msg/nachricht.h"


#ifndef CHATTING__MSG__DETAIL__NACHRICHT__STRUCT_H_
#define CHATTING__MSG__DETAIL__NACHRICHT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'user'
// Member 'text'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Nachricht in the package chatting.
typedef struct chatting__msg__Nachricht
{
  rosidl_runtime_c__String user;
  rosidl_runtime_c__String text;
} chatting__msg__Nachricht;

// Struct for a sequence of chatting__msg__Nachricht.
typedef struct chatting__msg__Nachricht__Sequence
{
  chatting__msg__Nachricht * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} chatting__msg__Nachricht__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CHATTING__MSG__DETAIL__NACHRICHT__STRUCT_H_
