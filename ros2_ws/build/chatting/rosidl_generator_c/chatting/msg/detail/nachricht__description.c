// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from chatting:msg/Nachricht.idl
// generated code does not contain a copyright notice

#include "chatting/msg/detail/nachricht__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_chatting
const rosidl_type_hash_t *
chatting__msg__Nachricht__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb5, 0x86, 0xae, 0x0f, 0x25, 0xe6, 0x2e, 0x11,
      0x7f, 0x0a, 0xd5, 0xc6, 0x3e, 0xb5, 0x16, 0xa2,
      0x98, 0xe2, 0x1c, 0x3c, 0x1f, 0x79, 0xc0, 0x5e,
      0x47, 0x28, 0xbc, 0x87, 0x73, 0x4e, 0xf6, 0xc3,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char chatting__msg__Nachricht__TYPE_NAME[] = "chatting/msg/Nachricht";

// Define type names, field names, and default values
static char chatting__msg__Nachricht__FIELD_NAME__user[] = "user";
static char chatting__msg__Nachricht__FIELD_NAME__text[] = "text";

static rosidl_runtime_c__type_description__Field chatting__msg__Nachricht__FIELDS[] = {
  {
    {chatting__msg__Nachricht__FIELD_NAME__user, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {chatting__msg__Nachricht__FIELD_NAME__text, 4, 4},
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
chatting__msg__Nachricht__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {chatting__msg__Nachricht__TYPE_NAME, 22, 22},
      {chatting__msg__Nachricht__FIELDS, 2, 2},
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
chatting__msg__Nachricht__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {chatting__msg__Nachricht__TYPE_NAME, 22, 22},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 23, 23},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
chatting__msg__Nachricht__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *chatting__msg__Nachricht__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
