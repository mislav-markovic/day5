#include "pch.h"
#include  "block.h"
#include  <string>

namespace block
{
  block_specialization::~block_specialization() = default;

  block::block(std::unique_ptr<block_specialization> impl, std::string name) : name_{std::move(name)}, block_type_{std::move(impl)}
  {
  }

  double block::apply(const double input) const noexcept
  {
    return block_type_->operator()(input);
  }

  std::string block::display() const
  {
    return block_type_->operator()();
  }

  std::string block_name(const operation::type block_type)
  {
    using namespace std::string_literals;
    switch (block_type)
    {
    case operation::type::identity: return "identity"s;
    case operation::type::addition: return "addition"s;
    case operation::type::multiplication: return "multiplication"s;
    case operation::type::power: return "power"s;
    case operation::type::limit: return "limit"s;
    case operation::type::condition: return "condition"s;
    }
  }
}
