// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from chatting:msg/Nachricht.idl
// generated code does not contain a copyright notice
#ifndef CHATTING__MSG__DETAIL__NACHRICHT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define CHATTING__MSG__DETAIL__NACHRICHT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "chatting/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "chatting/msg/detail/nachricht__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_chatting
bool cdr_serialize_chatting__msg__Nachricht(
  const chatting__msg__Nachricht * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_chatting
bool cdr_deserialize_chatting__msg__Nachricht(
  eprosima::fastcdr::Cdr &,
  chatting__msg__Nachricht * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_chatting
size_t get_serialized_size_chatting__msg__Nachricht(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_chatting
size_t max_serialized_size_chatting__msg__Nachricht(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_chatting
bool cdr_serialize_key_chatting__msg__Nachricht(
  const chatting__msg__Nachricht * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_chatting
size_t get_serialized_size_key_chatting__msg__Nachricht(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_chatting
size_t max_serialized_size_key_chatting__msg__Nachricht(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_chatting
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, chatting, msg, Nachricht)();

#ifdef __cplusplus
}
#endif

#endif  // CHATTING__MSG__DETAIL__NACHRICHT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
