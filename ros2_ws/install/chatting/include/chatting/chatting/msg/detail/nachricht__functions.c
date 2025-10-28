// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from chatting:msg/Nachricht.idl
// generated code does not contain a copyright notice
#include "chatting/msg/detail/nachricht__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `user`
// Member `text`
#include "rosidl_runtime_c/string_functions.h"

bool
chatting__msg__Nachricht__init(chatting__msg__Nachricht * msg)
{
  if (!msg) {
    return false;
  }
  // user
  if (!rosidl_runtime_c__String__init(&msg->user)) {
    chatting__msg__Nachricht__fini(msg);
    return false;
  }
  // text
  if (!rosidl_runtime_c__String__init(&msg->text)) {
    chatting__msg__Nachricht__fini(msg);
    return false;
  }
  return true;
}

void
chatting__msg__Nachricht__fini(chatting__msg__Nachricht * msg)
{
  if (!msg) {
    return;
  }
  // user
  rosidl_runtime_c__String__fini(&msg->user);
  // text
  rosidl_runtime_c__String__fini(&msg->text);
}

bool
chatting__msg__Nachricht__are_equal(const chatting__msg__Nachricht * lhs, const chatting__msg__Nachricht * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // user
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->user), &(rhs->user)))
  {
    return false;
  }
  // text
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->text), &(rhs->text)))
  {
    return false;
  }
  return true;
}

bool
chatting__msg__Nachricht__copy(
  const chatting__msg__Nachricht * input,
  chatting__msg__Nachricht * output)
{
  if (!input || !output) {
    return false;
  }
  // user
  if (!rosidl_runtime_c__String__copy(
      &(input->user), &(output->user)))
  {
    return false;
  }
  // text
  if (!rosidl_runtime_c__String__copy(
      &(input->text), &(output->text)))
  {
    return false;
  }
  return true;
}

chatting__msg__Nachricht *
chatting__msg__Nachricht__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  chatting__msg__Nachricht * msg = (chatting__msg__Nachricht *)allocator.allocate(sizeof(chatting__msg__Nachricht), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(chatting__msg__Nachricht));
  bool success = chatting__msg__Nachricht__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
chatting__msg__Nachricht__destroy(chatting__msg__Nachricht * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    chatting__msg__Nachricht__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
chatting__msg__Nachricht__Sequence__init(chatting__msg__Nachricht__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  chatting__msg__Nachricht * data = NULL;

  if (size) {
    data = (chatting__msg__Nachricht *)allocator.zero_allocate(size, sizeof(chatting__msg__Nachricht), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = chatting__msg__Nachricht__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        chatting__msg__Nachricht__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
chatting__msg__Nachricht__Sequence__fini(chatting__msg__Nachricht__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      chatting__msg__Nachricht__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

chatting__msg__Nachricht__Sequence *
chatting__msg__Nachricht__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  chatting__msg__Nachricht__Sequence * array = (chatting__msg__Nachricht__Sequence *)allocator.allocate(sizeof(chatting__msg__Nachricht__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = chatting__msg__Nachricht__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
chatting__msg__Nachricht__Sequence__destroy(chatting__msg__Nachricht__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    chatting__msg__Nachricht__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
chatting__msg__Nachricht__Sequence__are_equal(const chatting__msg__Nachricht__Sequence * lhs, const chatting__msg__Nachricht__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!chatting__msg__Nachricht__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
chatting__msg__Nachricht__Sequence__copy(
  const chatting__msg__Nachricht__Sequence * input,
  chatting__msg__Nachricht__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(chatting__msg__Nachricht);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    chatting__msg__Nachricht * data =
      (chatting__msg__Nachricht *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!chatting__msg__Nachricht__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          chatting__msg__Nachricht__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!chatting__msg__Nachricht__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
