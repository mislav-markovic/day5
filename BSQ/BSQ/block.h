#pragma once
#include "operation.h"

namespace block
{
  class block_specialization
  {
  public:
    [[nodiscard]] virtual auto operator()() const -> std::string = 0;
    [[nodiscard]] virtual auto operator()(double) const noexcept -> double = 0;
    virtual ~block_specialization() = 0;
  };

  template <typename Operation>
  class impl : public block_specialization
  {
    Operation op_;
  public:
    explicit impl(Operation op) : op_{op}
    {
    }

    auto operator()() const -> std::string override { return op_.string(); }
    auto operator()(double input) const noexcept -> double override { return op_(input); }
  };

  class block final
  {
    std::string name_;
    std::unique_ptr<block_specialization> block_type_;
  public:
    explicit block(operation::type block_type);
    double apply(double input) const noexcept;
    std::string display() const;
  };
}
