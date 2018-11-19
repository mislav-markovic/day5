#pragma once
#include <sstream>

namespace operation
{
  enum class type
  {
    identity, addition, multiplication, power, limit, condition
  };

  struct identity_op final
  {
    [[nodiscard]] double operator()(const double input) const noexcept { return input; }
    [[nodiscard]] std::string string() const { return std::string{}; }
  };

  struct addition_op final
  {
    explicit addition_op(const double constant) : constant_{constant}
    {
    }

    [[nodiscard]] double operator()(const double input) const noexcept { return input + constant_; }
    [[nodiscard]] std::string string() const { return std::to_string(constant_); }
  private:
    double constant_;
  };

  struct multiplication_op final
  {
    explicit multiplication_op(const double constant) : constant_{constant}
    {
    }

    [[nodiscard]] double operator()(const double input) const noexcept { return input * constant_; }
    [[nodiscard]] std::string string() const { return std::to_string(constant_); }
  private:
    double constant_;
  };

  struct power_op final
  {
    explicit power_op(const double constant) : constant_{constant}
    {
    }

    [[nodiscard]] double operator()(const double input) const noexcept { return std::pow(input, constant_); }
    [[nodiscard]] std::string string() const { return std::to_string(constant_); }
  private:
    double constant_;
  };

  struct limit_op final
  {
    explicit limit_op(const double min, const double max) : min_{min}, max_{max}
    {
    }

    [[nodiscard]] double operator()(const double input) const noexcept { return std::clamp(input, min_, max_); }

    [[nodiscard]] std::string string() const
    {
      std::stringstream ss{};
      ss << "[" << min_ << ", " << max_ << "]";
      return ss.str();
    }

  private:
    double min_;
    double max_;
  };

  struct condition_op final
  {
    explicit condition_op(const double constant) : constant_{constant}
    {
    }

    [[nodiscard]] double operator()(const double input) const noexcept
    {
      const auto diff = input - constant_;
      return std::abs(diff) < std::numeric_limits<double>::epsilon() ? 0 : diff > 0 ? 1 : -1;
    }

    [[nodiscard]] std::string string() const { return std::to_string(constant_); }
  private:
    double constant_;
  };
}
