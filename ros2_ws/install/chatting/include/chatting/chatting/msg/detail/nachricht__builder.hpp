// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from chatting:msg/Nachricht.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "chatting/msg/nachricht.hpp"


#ifndef CHATTING__MSG__DETAIL__NACHRICHT__BUILDER_HPP_
#define CHATTING__MSG__DETAIL__NACHRICHT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "chatting/msg/detail/nachricht__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace chatting
{

namespace msg
{

namespace builder
{

class Init_Nachricht_text
{
public:
  explicit Init_Nachricht_text(::chatting::msg::Nachricht & msg)
  : msg_(msg)
  {}
  ::chatting::msg::Nachricht text(::chatting::msg::Nachricht::_text_type arg)
  {
    msg_.text = std::move(arg);
    return std::move(msg_);
  }

private:
  ::chatting::msg::Nachricht msg_;
};

class Init_Nachricht_user
{
public:
  Init_Nachricht_user()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Nachricht_text user(::chatting::msg::Nachricht::_user_type arg)
  {
    msg_.user = std::move(arg);
    return Init_Nachricht_text(msg_);
  }

private:
  ::chatting::msg::Nachricht msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::chatting::msg::Nachricht>()
{
  return chatting::msg::builder::Init_Nachricht_user();
}

}  // namespace chatting

#endif  // CHATTING__MSG__DETAIL__NACHRICHT__BUILDER_HPP_
