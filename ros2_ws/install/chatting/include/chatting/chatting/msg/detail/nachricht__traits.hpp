// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from chatting:msg/Nachricht.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "chatting/msg/nachricht.hpp"


#ifndef CHATTING__MSG__DETAIL__NACHRICHT__TRAITS_HPP_
#define CHATTING__MSG__DETAIL__NACHRICHT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "chatting/msg/detail/nachricht__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace chatting
{

namespace msg
{

inline void to_flow_style_yaml(
  const Nachricht & msg,
  std::ostream & out)
{
  out << "{";
  // member: user
  {
    out << "user: ";
    rosidl_generator_traits::value_to_yaml(msg.user, out);
    out << ", ";
  }

  // member: text
  {
    out << "text: ";
    rosidl_generator_traits::value_to_yaml(msg.text, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Nachricht & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: user
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "user: ";
    rosidl_generator_traits::value_to_yaml(msg.user, out);
    out << "\n";
  }

  // member: text
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "text: ";
    rosidl_generator_traits::value_to_yaml(msg.text, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Nachricht & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace chatting

namespace rosidl_generator_traits
{

[[deprecated("use chatting::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const chatting::msg::Nachricht & msg,
  std::ostream & out, size_t indentation = 0)
{
  chatting::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use chatting::msg::to_yaml() instead")]]
inline std::string to_yaml(const chatting::msg::Nachricht & msg)
{
  return chatting::msg::to_yaml(msg);
}

template<>
inline const char * data_type<chatting::msg::Nachricht>()
{
  return "chatting::msg::Nachricht";
}

template<>
inline const char * name<chatting::msg::Nachricht>()
{
  return "chatting/msg/Nachricht";
}

template<>
struct has_fixed_size<chatting::msg::Nachricht>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<chatting::msg::Nachricht>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<chatting::msg::Nachricht>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CHATTING__MSG__DETAIL__NACHRICHT__TRAITS_HPP_
