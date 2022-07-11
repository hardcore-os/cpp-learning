#include <cstddef>          // for ptrdiff_t, size_t
#include <initializer_list> // for initializer_list
#include <type_traits>      // for is_signed, integral_constant
#include <utility>          // for exchange, forward


#if defined(__cplusplus) && (__cplusplus >= 201703L)
#define GSL_NODISCARD [[nodiscard]]
#else
#define GSL_NODISCARD
#endif // defined(__cplusplus) && (__cplusplus >= 201703L)


template <class F>
class final_action
{
public:
    static_assert(!std::is_reference<F>::value && !std::is_const<F>::value &&
                      !std::is_volatile<F>::value,
                  "Final_action should store its callable by value");

    explicit final_action(F f) noexcept : f_(std::move(f)) {}

    final_action(final_action&& other) noexcept
        : f_(std::move(other.f_)), invoke_(std::exchange(other.invoke_, false))
    {}

    final_action(const final_action&) = delete;
    final_action& operator=(const final_action&) = delete;
    final_action& operator=(final_action&&) = delete;

    // clang-format on
    ~final_action() noexcept
    {
        if (invoke_) f_();
    }

private:
    F f_;
    bool invoke_{true};
};

// finally() - convenience function to generate a final_action
template <class F>
GSL_NODISCARD final_action<typename std::remove_cv<typename std::remove_reference<F>::type>::type>
finally(F&& f) noexcept
{
    return final_action<typename std::remove_cv<typename std::remove_reference<F>::type>::type>(
        std::forward<F>(f));
}