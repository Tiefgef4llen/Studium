// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from chatting:msg/AddressBook.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "chatting/msg/address_book.hpp"


#ifndef CHATTING__MSG__DETAIL__ADDRESS_BOOK__STRUCT_HPP_
#define CHATTING__MSG__DETAIL__ADDRESS_BOOK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__chatting__msg__AddressBook __attribute__((deprecated))
#else
# define DEPRECATED__chatting__msg__AddressBook __declspec(deprecated)
#endif

namespace chatting
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AddressBook_
{
  using Type = AddressBook_<ContainerAllocator>;

  explicit AddressBook_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->user = "";
      this->text = "";
    }
  }

  explicit AddressBook_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : user(_alloc),
    text(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->user = "";
      this->text = "";
    }
  }

  // field types and members
  using _user_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _user_type user;
  using _text_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _text_type text;

  // setters for named parameter idiom
  Type & set__user(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->user = _arg;
    return *this;
  }
  Type & set__text(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->text = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    chatting::msg::AddressBook_<ContainerAllocator> *;
  using ConstRawPtr =
    const chatting::msg::AddressBook_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<chatting::msg::AddressBook_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<chatting::msg::AddressBook_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      chatting::msg::AddressBook_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<chatting::msg::AddressBook_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      chatting::msg::AddressBook_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<chatting::msg::AddressBook_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<chatting::msg::AddressBook_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<chatting::msg::AddressBook_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__chatting__msg__AddressBook
    std::shared_ptr<chatting::msg::AddressBook_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__chatting__msg__AddressBook
    std::shared_ptr<chatting::msg::AddressBook_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AddressBook_ & other) const
  {
    if (this->user != other.user) {
      return false;
    }
    if (this->text != other.text) {
      return false;
    }
    return true;
  }
  bool operator!=(const AddressBook_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AddressBook_

// alias to use template instance with default allocator
using AddressBook =
  chatting::msg::AddressBook_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace chatting

#endif  // CHATTING__MSG__DETAIL__ADDRESS_BOOK__STRUCT_HPP_
