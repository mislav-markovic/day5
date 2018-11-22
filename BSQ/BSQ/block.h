#pragma once
#include "operation.h"

namespace block
{
  class block_specialization
  {
  public:
    [[nodiscard]] virtual auto operator()() const -> std::string = 0;
    [[nodiscard]] virtual auto operator()(double) const noexcept -> double = 0;
    virtual ~block_specialization();
  };

  template <typename Operation>
  class impl : public block_specialization
  {
    Operation op_;
  public:
    template <typename... Args>
    explicit impl(Args ... args) : op_{Operation{args...}}
    {
    }

    explicit impl() : op_{Operation{}}
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
    explicit block(std::unique_ptr<block_specialization> impl, std::string name);
    double apply(double input) const noexcept;
    std::string display() const;
  };

  std::string block_name(operation::type block_type);

  template <typename T, typename ... Ts>
  std::unique_ptr<block_specialization> create_impl(const operation::type block_type, T arg, Ts ... args)
  {
    switch (block_type)
    {
    case operation::type::identity: return std::make_unique<impl<operation::identity_op>>();
    case operation::type::addition: return std::make_unique<impl<operation::addition_op>>(args...);
    case operation::type::multiplication: return std::make_unique<impl<operation::multiplication_op>>(args...);
    case operation::type::power: return std::make_unique<impl<operation::power_op>>(args...);
    case operation::type::limit: return std::make_unique<impl<operation::limit_op>>(args...);
    case operation::type::condition: return std::make_unique<impl<operation::condition_op>>(arg, args...);
    }
  }

  template <typename... Us>
  block create_block(const operation::type block_type, Us ... args)
  {
    return block{create_impl(block_type, args...), block_name(block_type)};
  }
}
