#pragma once
#include "block.h"


namespace sequence
{
  class sequence final
  {
  private:
    std::vector<block::block> blocks_;
  public:
    [[nodiscard]] double evaluate(double input) const noexcept;
    void add_block(block::block block);
    void delete_block(unsigned int position);
    void move_to_front(unsigned int position);
    void show_sequence(std::ostream & sink) const;
    void evaluate_file(std::filesystem::path input_file) const;
  };
  
}
