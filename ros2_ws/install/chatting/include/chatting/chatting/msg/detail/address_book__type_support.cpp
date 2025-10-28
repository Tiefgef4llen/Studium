// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from chatting:msg/AddressBook.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "chatting/msg/detail/address_book__functions.h"
#include "chatting/msg/detail/address_book__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace chatting
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void AddressBook_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) chatting::msg::AddressBook(_init);
}

void AddressBook_fini_function(void * message_memory)
{
  auto typed_message = static_cast<chatting::msg::AddressBook *>(message_memory);
  typed_message->~AddressBook();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AddressBook_message_member_array[2] = {
  {
    "user",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(chatting::msg::AddressBook, user),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "text",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(chatting::msg::AddressBook, text),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AddressBook_message_members = {
  "chatting::msg",  // message namespace
  "AddressBook",  // message name
  2,  // number of fields
  sizeof(chatting::msg::AddressBook),
  false,  // has_any_key_member_
  AddressBook_message_member_array,  // message members
  AddressBook_init_function,  // function to initialize message memory (memory has to be allocated)
  AddressBook_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AddressBook_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AddressBook_message_members,
  get_message_typesupport_handle_function,
  &chatting__msg__AddressBook__get_type_hash,
  &chatting__msg__AddressBook__get_type_description,
  &chatting__msg__AddressBook__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace chatting


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<chatting::msg::AddressBook>()
{
  return &::chatting::msg::rosidl_typesupport_introspection_cpp::AddressBook_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, chatting, msg, AddressBook)() {
  return &::chatting::msg::rosidl_typesupport_introspection_cpp::AddressBook_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
