#include "pch.h"
#include "sequence.h"
#include <fstream>
#include <iterator>

namespace sequence
{
	[[nodiscard]] double sequence::evaluate(double input) const noexcept
  {
    return std::accumulate(blocks_.cbegin(), blocks_.cend(), 0., [](double acc, auto const& input) { return input.apply(acc); });
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

  void sequence::evaluate_file(const std::filesystem::path input_file) const
  {
    std::ofstream output{"result.txt"};
    std::vector<double> v{};
    std::ifstream in_stream{input_file};
    auto start = std::istream_iterator<double>{in_stream};
    auto end = std::istream_iterator<double>{};
    std::copy(start, end, v.begin()); //read input from file
    std::transform(v.begin(), v.end(), v.begin(), [this](auto elem) { return evaluate(elem); }); //run seq on all inputs
    auto result = std::accumulate(v.cbegin(), v.cend(), std::string{}, [](std::string& acc, double elem) { return acc.append(std::to_string(elem)) + '\n'; }); //concat results with newline
    auto out_stream = std::ostream_iterator<char>{output}; //create iterator to file stream
    std::copy(result.cbegin(), result.cend(), out_stream); //copy result to file
  }

  void sequence::show_sequence(std::ostream & sink) const
  {
    //TODO
  }
}
