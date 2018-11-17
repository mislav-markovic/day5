#include "pch.h"
#include  "block.h"

namespace block
{
  block::block(const unsigned position, const type block_type) : position_{position}, block_type_{create_block(block_type)}
  {
  }

  double block::apply(const double input) const
  {
    return block_type_->func(input);
  }

  void block::show() const
  {
    block_type_->display(std::cout);
  }

  block& block::operator=(block&& other) noexcept
  {
    if (this == &other) return *this;
    position_ = other.position_;
    block_type_ = std::move(other.block_type_);
    return *this;
  }

  block_specialization::~block_specialization() = default;
}
