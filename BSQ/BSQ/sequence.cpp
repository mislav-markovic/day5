#include "pch.h"
#include "sequence.h"

namespace sequence
{
  double sequence::evaluate(double input) const
  {
    return std::accumulate(blocks_.cbegin(), blocks_.cend(), 0., [](auto const& input, double acc) {return input.apply(acc); });
  }

  void sequence::add_block(block::block block)
  {
    blocks_.emplace_back(std::move(block));
  }

  void sequence::delete_block(const unsigned position)
  {
    auto it = blocks_.begin();
    std::advance(it, position);
    blocks_.erase(it);
  }

  void sequence::move_to_front(const unsigned position)
  {
    auto it = blocks_.begin();
    std::advance(it, position);
    std::rotate(blocks_.begin(), it, it + 1);
  }

  double sequence::evaluate_file(std::filesystem::path input_file) const
  {
    //TODO
  }

  void sequence::show_sequence() const
  {
    //TODO
  }
}
