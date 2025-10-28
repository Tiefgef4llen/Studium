// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from chatting:msg/AddressBook.idl
// generated code does not contain a copyright notice

#include "chatting/msg/detail/address_book__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_chatting
const rosidl_type_hash_t *
chatting__msg__AddressBook__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xab, 0xcb, 0xf8, 0xb2, 0x53, 0xef, 0xf6, 0xf9,
      0x59, 0x22, 0x16, 0x85, 0xa5, 0xe5, 0x58, 0x5f,
      0x7d, 0x1a, 0xb9, 0xa7, 0x08, 0x82, 0x94, 0x01,
      0xbf, 0x78, 0x23, 0xd4, 0xe5, 0xc0, 0xd8, 0xc1,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char chatting__msg__AddressBook__TYPE_NAME[] = "chatting/msg/AddressBook";

// Define type names, field names, and default values
static char chatting__msg__AddressBook__FIELD_NAME__user[] = "user";
static char chatting__msg__AddressBook__FIELD_NAME__text[] = "text";

static rosidl_runtime_c__type_description__Field chatting__msg__AddressBook__FIELDS[] = {
  {
    {chatting__msg__AddressBook__FIELD_NAME__user, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {chatting__msg__AddressBook__FIELD_NAME__text, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
chatting__msg__AddressBook__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {chatting__msg__AddressBook__TYPE_NAME, 24, 24},
      {chatting__msg__AddressBook__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string user\n"
  "string text";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
chatting__msg__AddressBook__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {chatting__msg__AddressBook__TYPE_NAME, 24, 24},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 23, 23},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
chatting__msg__AddressBook__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *chatting__msg__AddressBook__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
