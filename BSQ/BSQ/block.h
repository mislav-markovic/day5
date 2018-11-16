#pragma once

namespace block
{
  namespace operations
  {
    inline auto identity_func = [](const double in) { return in; };
    inline auto addition_func = [](const double in, const double parameter) { return in + parameter; };
    inline auto multiplication_func = [](const double in, const double parameter) { return in * parameter; };
    inline auto power_func = [](const double in, const double parameter) { return std::pow(in, parameter); };
    inline auto limit_func = [](const double in, const double min, const double max) { return std::clamp(in, min, max); };
    inline auto condition_func = [](const double in, const double parameter)
    {
      return in == parameter ? 0. : in < parameter ? -1. : 1;
    };
  }

  enum class type
  {
    identity,
    addition,
    multiplication,
    power,
    limit,
    condition
  };

  class block_specialization
  {
  public:
    virtual double func(double input) const = 0;
    virtual void display(std::ostream& output) const = 0;
    virtual ~block_specialization() = 0;
  };

  template<class Predicate, typename... Args>
  class impl : block_specialization
  {
  private:
    Predicate func_;
    std::tuple<Args...> parameters_;
  public:
    explicit impl(Predicate&& func, Args&&... args) : func_{std::forward<Predicate>(func)}, parameters_{std::forward<Args>(args)...}
    {      
    }

    double func(double input) const override
    {
      return func_(input, parameters_...);
    }
  };

  template <typename... Args>
  std::unique_ptr<block_specialization> create_block(const type block_to_create, Args... parameters)
  {
    switch (block_to_create)
    {
    case type::identity: return std::make_unique<impl>(operations::identity_func, parameters...);
    case type::addition: return std::make_unique<impl>(operations::addition_func, parameters...);
    case type::multiplication: return std::make_unique<impl>(operations::multiplication_func, parameters...);
    case type::power: return std::make_unique<impl>(operations::power_func, parameters...);
    case type::limit: return std::make_unique<impl>(operations::limit_func, parameters...);
    case type::condition: return std::make_unique<impl>(operations::condition_func, parameters...);
    default: throw std::invalid_argument("Unknown block specialization");
    }
  }

  class block final
  {
  private:
    unsigned int position_;
    std::unique_ptr<block_specialization> block_type_;

  public:
    block(unsigned int position, type block_type);
    block(block&& other) noexcept = default;
    block(block const& other) = delete;
    double apply(double input) const;
    void show() const;
  };
}
