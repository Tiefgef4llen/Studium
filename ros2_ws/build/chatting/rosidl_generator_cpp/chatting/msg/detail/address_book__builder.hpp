// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from chatting:msg/AddressBook.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "chatting/msg/address_book.hpp"


#ifndef CHATTING__MSG__DETAIL__ADDRESS_BOOK__BUILDER_HPP_
#define CHATTING__MSG__DETAIL__ADDRESS_BOOK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "chatting/msg/detail/address_book__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace chatting
{

namespace msg
{

namespace builder
{

class Init_AddressBook_text
{
public:
  explicit Init_AddressBook_text(::chatting::msg::AddressBook & msg)
  : msg_(msg)
  {}
  ::chatting::msg::AddressBook text(::chatting::msg::AddressBook::_text_type arg)
  {
    msg_.text = std::move(arg);
    return std::move(msg_);
  }

private:
  ::chatting::msg::AddressBook msg_;
};

class Init_AddressBook_user
{
public:
  Init_AddressBook_user()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AddressBook_text user(::chatting::msg::AddressBook::_user_type arg)
  {
    msg_.user = std::move(arg);
    return Init_AddressBook_text(msg_);
  }

private:
  ::chatting::msg::AddressBook msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::chatting::msg::AddressBook>()
{
  return chatting::msg::builder::Init_AddressBook_user();
}

}  // namespace chatting

#endif  // CHATTING__MSG__DETAIL__ADDRESS_BOOK__BUILDER_HPP_
