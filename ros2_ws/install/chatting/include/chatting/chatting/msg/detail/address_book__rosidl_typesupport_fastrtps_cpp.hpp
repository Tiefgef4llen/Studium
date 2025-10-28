// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from chatting:msg/AddressBook.idl
// generated code does not contain a copyright notice

#ifndef CHATTING__MSG__DETAIL__ADDRESS_BOOK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define CHATTING__MSG__DETAIL__ADDRESS_BOOK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "chatting/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "chatting/msg/detail/address_book__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace chatting
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_chatting
cdr_serialize(
  const chatting::msg::AddressBook & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_chatting
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  chatting::msg::AddressBook & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_chatting
get_serialized_size(
  const chatting::msg::AddressBook & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_chatting
max_serialized_size_AddressBook(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_chatting
cdr_serialize_key(
  const chatting::msg::AddressBook & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_chatting
get_serialized_size_key(
  const chatting::msg::AddressBook & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_chatting
max_serialized_size_key_AddressBook(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace chatting

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_chatting
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, chatting, msg, AddressBook)();

#ifdef __cplusplus
}
#endif

#endif  // CHATTING__MSG__DETAIL__ADDRESS_BOOK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
