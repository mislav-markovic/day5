#pragma once
#include "block.h"


namespace sequence
{
  class sequence final
  {
  private:
    std::vector<block::block> blocks_;
  public:
    double evaluate(double input) const;
    void add_block(block::block block);
    void delete_block(unsigned int position);
    void move_to_front(unsigned int position);
    void show_sequence() const;
    double evaluate_file(std::filesystem::path input_file) const;
  };
  
}
