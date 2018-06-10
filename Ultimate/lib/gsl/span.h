///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef GSL_SPAN_H
#define GSL_SPAN_H

#include <gsl/gsl_assert.h> // for Expects
#include <gsl/gsl_byte.h>   // for byte
#include <gsl/gsl_util.h>   // for narrow_cast, narrow

#include <algorithm> // for lexicographical_compare
#include <array>     // for array
#include <cstddef>   // for ptrdiff_t, size_t, nullptr_t
#include <iterator>  // for reverse_iterator, distance, random_access_...
#include <limits>
#include <stdexcept>
#include <type_traits> // for enable_if_t, declval, is_convertible, inte...
#include <utility>

#ifdef _MSC_VER
#pragma warning(push)

// turn off some warnings that are noisy about our Expects statements
#pragma warning(disable : 4127) // conditional expression is constant
#pragma warning(disable : 4702) // unreachable code

// blanket turn off warnings from CppCoreCheck for now
// so people aren't annoyed by them when running the tool.
// more targeted suppressions will be added in a future update to the GSL
#pragma warning(disable : 26481 26482 26483 26485 26490 26491 26492 26493 26495)

#if _MSC_VER < 1910
#pragma push_macro("constexpr")
#define constexpr /*constexpr*/

#endif                          // _MSC_VER < 1910
#endif                          // _MSC_VER

#ifdef GSL_THROW_ON_CONTRACT_VIOLATION
#define GSL_NOEXCEPT /*noexcept*/
#else
#define GSL_NOEXCEPT noexcept
#endif // GSL_THROW_ON_CONTRACT_VIOLATION

namespace gsl
{

// [views.constants], constants
constexpr const std::ptrdiff_t dynamic_extent = -1;

template <class ElementType, std::ptrdiff_t Extent = dynamic_extent>
class span;

// implementation details
namespace details
{
    template <class T>
    struct is_span_oracle : std::false_type
    {
    };

    template <class ElementType, std::ptrdiff_t Extent>
    struct is_span_oracle<gsl::span<ElementType, Extent>> : std::true_type
    {
    };

    template <class T>
    struct is_span : public is_span_oracle<std::remove_cv_t<T>>
    {
    };

    template <class T>
    struct is_std_array_oracle : std::false_type
    {
    };

    template <class ElementType, std::size_t Extent>
    struct is_std_array_oracle<std::array<ElementType, Extent>> : std::true_type
    {
    };

    template <class T>
    struct is_std_array : public is_std_array_oracle<std::remove_cv_t<T>>
    {
    };

    template <std::ptrdiff_t From, std::ptrdiff_t To>
    struct is_allowed_extent_conversion
        : public std::integral_constant<bool, From == To || From == gsl::dynamic_extent ||
                                                  To == gsl::dynamic_extent>
    {
    };

    template <class From, class To>
    struct is_allowed_element_type_conversion
        : public std::integral_constant<bool, std::is_convertible<From (*)[], To (*)[]>::value>
    {
    };

    template <class Span, bool IsConst>
    class span_iterator
    {
        using element_type_ = typename Span::element_type;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::remove_cv_t<element_type_>;
        using difference_type = typename Span::index_type;

        using reference = std::conditional_t<IsConst, const element_type_, element_type_>&;
        using pointer = std::add_pointer_t<reference>;

        span_iterator() = default;

        constexpr span_iterator(const Span* span, typename Span::index_type idx) GSL_NOEXCEPT
            : span_(span), index_(idx)
        {
            Expects(span == nullptr || (0 <= index_ && index_ <= span_->size()));
        }

        friend span_iterator<Span, true>;
        template<bool B, std::enable_if_t<!B && IsConst>* = nullptr>
        constexpr span_iterator(const span_iterator<Span, B>& other) GSL_NOEXCEPT
            : span_iterator(other.span_, other.index_)
        {
        }

        constexpr reference operator*() const GSL_NOEXCEPT
        {
            Expects(index_ != span_->size());
            return *(span_->data() + index_);
        }

        constexpr pointer operator->() const GSL_NOEXCEPT
        {
            Expects(index_ != span_->size());
            return span_->data() + index_;
        }

        constexpr span_iterator& operator++() GSL_NOEXCEPT
        {
            Expects(0 <= index_ && index_ != span_->size());
            ++index_;
            return *this;
        }

        constexpr span_iterator operator++(int) GSL_NOEXCEPT
        {
            auto ret = *this;
            ++(*this);
            return ret;
        }

        constexpr span_iterator& operator--() GSL_NOEXCEPT
        {
            Expects(index_ != 0 && index_ <= span_->size());
            --index_;
            return *this;
        }

        constexpr span_iterator operator--(int) GSL_NOEXCEPT
        {
            auto ret = *this;
            --(*this);
            return ret;
        }

        constexpr span_iterator operator+(difference_type n) const GSL_NOEXCEPT
        {
            auto ret = *this;
            return ret += n;
        }

        constexpr span_iterator& operator+=(difference_type n) GSL_NOEXCEPT
        {
            Expects((index_ + n) >= 0 && (index_ + n) <= span_->size());
            index_ += n;
            return *this;
        }

        constexpr span_iterator operator-(difference_type n) const GSL_NOEXCEPT
        {
            auto ret = *this;
            return ret -= n;
        }

        constexpr span_iterator& operator-=(difference_type n) GSL_NOEXCEPT { return *this += -n; }

        constexpr difference_type operator-(span_iterator rhs) const GSL_NOEXCEPT
        {
            Expects(span_ == rhs.span_);
            return index_ - rhs.index_;
        }

        constexpr reference operator[](difference_type n) const GSL_NOEXCEPT
        {
            return *(*this + n);
        }

        constexpr friend bool operator==(span_iterator lhs,
                                         span_iterator rhs) GSL_NOEXCEPT
        {
            return lhs.span_ == rhs.span_ && lhs.index_ == rhs.index_;
        }

        constexpr friend bool operator!=(span_iterator lhs,
                                         span_iterator rhs) GSL_NOEXCEPT
        {
            return !(lhs == rhs);
        }

        constexpr friend bool operator<(span_iterator lhs,
                                        span_iterator rhs) GSL_NOEXCEPT
        {
            Expects(lhs.span_ == rhs.span_);
            return lhs.index_ < rhs.index_;
        }

        constexpr friend bool operator<=(span_iterator lhs,
                                         span_iterator rhs) GSL_NOEXCEPT
        {
            return !(rhs < lhs);
        }

        constexpr friend bool operator>(span_iterator lhs,
                                        span_iterator rhs) GSL_NOEXCEPT
        {
            return rhs < lhs;
        }

        constexpr friend bool operator>=(span_iterator lhs,
                                         span_iterator rhs) GSL_NOEXCEPT
        {
            return !(rhs > lhs);
        }

    protected:
        const Span* span_ = nullptr;
        std::ptrdiff_t index_ = 0;
    };

    template <class Span, bool IsConst>
    constexpr span_iterator<Span, IsConst>
    operator+(typename span_iterator<Span, IsConst>::difference_type n,
              span_iterator<Span, IsConst> rhs) GSL_NOEXCEPT
    {
        return rhs + n;
    }

    template <class Span, bool IsConst>
    constexpr span_iterator<Span, IsConst>
    operator-(typename span_iterator<Span, IsConst>::difference_type n,
              span_iterator<Span, IsConst> rhs) GSL_NOEXCEPT
    {
        return rhs - n;
    }

    template <std::ptrdiff_t Ext>
    class extent_type
    {
    public:
        using index_type = std::ptrdiff_t;

        static_assert(Ext >= 0, "A fixed-size span must be >= 0 in size.");

        constexpr extent_type() GSL_NOEXCEPT {}

        template <index_type Other>
        constexpr extent_type(extent_type<Other> ext)
        {
            static_assert(Other == Ext || Other == dynamic_extent,
                          "Mismatch between fixed-size extent and size of initializing data.");
            Expects(ext.size() == Ext);
        }

        constexpr extent_type(index_type size) { Expects(size == Ext); }

        constexpr index_type size() const GSL_NOEXCEPT { return Ext; }
    };

    template <>
    class extent_type<dynamic_extent>
    {
    public:
        using index_type = std::ptrdiff_t;

        template <index_type Other>
        explicit constexpr extent_type(extent_type<Other> ext) : size_(ext.size())
        {
        }

        explicit constexpr extent_type(index_type size) : size_(size) { Expects(size >= 0); }

        constexpr index_type size() const GSL_NOEXCEPT { return size_; }

    private:
        index_type size_;
    };
} // namespace details

// [span], class template span
template <class ElementType, std::ptrdiff_t Extent>
class span
{
public:
    // constants and types
    using element_type = ElementType;
    using value_type = std::remove_cv_t<ElementType>;
    using index_type = std::ptrdiff_t;
    using pointer = element_type*;
    using reference = element_type&;

    using iterator = details::span_iterator<span<ElementType, Extent>, false>;
    using const_iterator = details::span_iterator<span<ElementType, Extent>, true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using size_type = index_type;

    constexpr static const index_type extent = Extent;

    // [span.cons], span constructors, copy, assignment, and destructor
    template <bool Dependent = false,
              // "Dependent" is needed to make "std::enable_if_t<Dependent || Extent <= 0>" SFINAE,
              // since "std::enable_if_t<Extent <= 0>" is ill-formed when Extent is greater than 0.
              class = std::enable_if_t<(Dependent || Extent <= 0)>>
    constexpr span() GSL_NOEXCEPT : storage_(nullptr, details::extent_type<0>())
    {
    }

    constexpr span(pointer ptr, index_type count) : storage_(ptr, count) {}

    constexpr span(pointer firstElem, pointer lastElem)
        : storage_(firstElem, std::distance(firstElem, lastElem))
    {
    }

    template <std::size_t N>
    constexpr span(element_type (&arr)[N]) GSL_NOEXCEPT
        : storage_(&arr[0], details::extent_type<N>())
    {
    }

    template <std::size_t N, class ArrayElementType = std::remove_const_t<element_type>>
    constexpr span(std::array<ArrayElementType, N>& arr) GSL_NOEXCEPT
        : storage_(&arr[0], details::extent_type<N>())
    {
    }

    template <std::size_t N>
    constexpr span(const std::array<std::remove_const_t<element_type>, N>& arr) GSL_NOEXCEPT
        : storage_(&arr[0], details::extent_type<N>())
    {
    }

    // NB: the SFINAE here uses .data() as a incomplete/imperfect proxy for the requirement
    // on Container to be a contiguous sequence container.
    template <class Container,
              class = std::enable_if_t<
                  !details::is_span<Container>::value && !details::is_std_array<Container>::value &&
                  std::is_convertible<typename Container::pointer, pointer>::value &&
                  std::is_convertible<typename Container::pointer,
                                      decltype(std::declval<Container>().data())>::value>>
    constexpr span(Container& cont) : span(cont.data(), narrow<index_type>(cont.size()))
    {
    }

    template <class Container,
              class = std::enable_if_t<
                  std::is_const<element_type>::value && !details::is_span<Container>::value &&
                  std::is_convertible<typename Container::pointer, pointer>::value &&
                  std::is_convertible<typename Container::pointer,
                                      decltype(std::declval<Container>().data())>::value>>
    constexpr span(const Container& cont) : span(cont.data(), narrow<index_type>(cont.size()))
    {
    }

    constexpr span(const span& other) GSL_NOEXCEPT = default;

    template <
        class OtherElementType, std::ptrdiff_t OtherExtent,
        class = std::enable_if_t<
            details::is_allowed_extent_conversion<OtherExtent, Extent>::value &&
            details::is_allowed_element_type_conversion<OtherElementType, element_type>::value>>
    constexpr span(const span<OtherElementType, OtherExtent>& other)
        : storage_(other.data(), details::extent_type<OtherExtent>(other.size()))
    {
    }

    ~span() GSL_NOEXCEPT = default;
    constexpr span& operator=(const span& other) GSL_NOEXCEPT = default;
    
    // [span.sub], span subviews
    template <std::ptrdiff_t Count>
    constexpr span<element_type, Count> first() const
    {
        Expects(Count >= 0 && Count <= size());
        return {data(), Count};
    }

    template <std::ptrdiff_t Count>
    constexpr span<element_type, Count> last() const
    {
        Expects(Count >= 0 && size() - Count >= 0);
        return {data() + (size() - Count), Count};
    }

    template <std::ptrdiff_t Offset, std::ptrdiff_t Count = dynamic_extent>
    constexpr span<element_type, Count> subspan() const
    {
        Expects((Offset >= 0 && size() - Offset >= 0) &&
                (Count == dynamic_extent || (Count >= 0 && Offset + Count <= size())));

        return {data() + Offset, Count == dynamic_extent ? size() - Offset : Count};
    }

    constexpr span<element_type, dynamic_extent> first(index_type count) const
    {
        Expects(count >= 0 && count <= size());
        return {data(), count};
    }

    constexpr span<element_type, dynamic_extent> last(index_type count) const
    {
        return make_subspan(size() - count, dynamic_extent, subspan_selector<Extent>{});
    }

    constexpr span<element_type, dynamic_extent> subspan(index_type offset,
                                                         index_type count = dynamic_extent) const
    {
        return make_subspan(offset, count, subspan_selector<Extent>{});
    }


    // [span.obs], span observers
    constexpr index_type size() const GSL_NOEXCEPT { return storage_.size(); }
    constexpr index_type size_bytes() const GSL_NOEXCEPT
    {
        return size() * narrow_cast<index_type>(sizeof(element_type));
    }
    constexpr bool empty() const GSL_NOEXCEPT { return size() == 0; }

    // [span.elem], span element access
    constexpr reference operator[](index_type idx) const
    {
        Expects(idx >= 0 && idx < storage_.size());
        return data()[idx];
    }

    constexpr reference at(index_type idx) const { return this->operator[](idx); }
    constexpr reference operator()(index_type idx) const { return this->operator[](idx); }
    constexpr pointer data() const GSL_NOEXCEPT { return storage_.data(); }

    // [span.iter], span iterator support
    constexpr iterator begin() const GSL_NOEXCEPT { return {this, 0}; }
    constexpr iterator end() const GSL_NOEXCEPT { return {this, size()}; }

    constexpr const_iterator cbegin() const GSL_NOEXCEPT { return {this, 0}; }
    constexpr const_iterator cend() const GSL_NOEXCEPT { return {this, size()}; }

    constexpr reverse_iterator rbegin() const GSL_NOEXCEPT { return reverse_iterator{end()}; }
    constexpr reverse_iterator rend() const GSL_NOEXCEPT { return reverse_iterator{begin()}; }

    constexpr const_reverse_iterator crbegin() const GSL_NOEXCEPT { return const_reverse_iterator{cend()}; }
    constexpr const_reverse_iterator crend() const GSL_NOEXCEPT { return const_reverse_iterator{cbegin()}; }

private:
    // this implementation detail class lets us take advantage of the
    // empty base class optimization to pay for only storage of a single
    // pointer in the case of fixed-size spans
    template <class ExtentType>
    class storage_type : public ExtentType
    {
    public:

        // checked parameter is needed to remove unnecessary null check in subspans
        template <class OtherExtentType>
        constexpr storage_type(pointer data, OtherExtentType ext, bool checked = false) : ExtentType(ext), data_(data)
        {
            Expects(((checked || !data) && ExtentType::size() == 0) ||
                    ((checked || data) && ExtentType::size() >= 0));
        }

        constexpr pointer data() const GSL_NOEXCEPT { return data_; }

    private:
        pointer data_;
    };

    storage_type<details::extent_type<Extent>> storage_;

    // The rest is needed to remove unnecessary null check in subspans
    constexpr span(pointer ptr, index_type count, bool checked) : storage_(ptr, count, checked) {}

    template <std::ptrdiff_t CallerExtent>
    class subspan_selector {};

    template <std::ptrdiff_t CallerExtent>
    span<element_type, dynamic_extent> make_subspan(index_type offset,
                                                    index_type count,
                                                    subspan_selector<CallerExtent>) const GSL_NOEXCEPT
    {
        span<element_type, dynamic_extent> tmp(*this);
        return tmp.subspan(offset, count);
    }

    span<element_type, dynamic_extent> make_subspan(index_type offset,
                                                    index_type count,
                                                    subspan_selector<dynamic_extent>) const GSL_NOEXCEPT
    {
        Expects(offset >= 0 && size() - offset >= 0);
        if (count == dynamic_extent)
        {
            return { data() + offset, size() - offset, true };
        }

        Expects(count >= 0 && size() - offset >= count);
        return { data() + offset,  count, true };
    }
};


// [span.comparison], span comparison operators
template <class ElementType, std::ptrdiff_t FirstExtent, std::ptrdiff_t SecondExtent>
constexpr bool operator==(span<ElementType, FirstExtent> l,
                          span<ElementType, SecondExtent> r)
{
    return std::equal(l.begin(), l.end(), r.begin(), r.end());
}

template <class ElementType, std::ptrdiff_t Extent>
constexpr bool operator!=(span<ElementType, Extent> l,
                          span<ElementType, Extent> r)
{
    return !(l == r);
}

template <class ElementType, std::ptrdiff_t Extent>
constexpr bool operator<(span<ElementType, Extent> l,
                         span<ElementType, Extent> r)
{
    return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}

template <class ElementType, std::ptrdiff_t Extent>
constexpr bool operator<=(span<ElementType, Extent> l,
                          span<ElementType, Extent> r)
{
    return !(l > r);
}

template <class ElementType, std::ptrdiff_t Extent>
constexpr bool operator>(span<ElementType, Extent> l,
                         span<ElementType, Extent> r)
{
    return r < l;
}

template <class ElementType, std::ptrdiff_t Extent>
constexpr bool operator>=(span<ElementType, Extent> l,
                          span<ElementType, Extent> r)
{
    return !(l < r);
}

namespace details
{
    // if we only supported compilers with good constexpr support then
    // this pair of classes could collapse down to a constexpr function

    // we should use a narrow_cast<> to go to std::size_t, but older compilers may not see it as
    // constexpr
    // and so will fail compilation of the template
    template <class ElementType, std::ptrdiff_t Extent>
    struct calculate_byte_size
        : std::integral_constant<std::ptrdiff_t,
                                 static_cast<std::ptrdiff_t>(sizeof(ElementType) *
                                                             static_cast<std::size_t>(Extent))>
    {
    };

    template <class ElementType>
    struct calculate_byte_size<ElementType, dynamic_extent>
        : std::integral_constant<std::ptrdiff_t, dynamic_extent>
    {
    };
}

// [span.objectrep], views of object representation
template <class ElementType, std::ptrdiff_t Extent>
span<const byte, details::calculate_byte_size<ElementType, Extent>::value>
as_bytes(span<ElementType, Extent> s) GSL_NOEXCEPT
{
    return {reinterpret_cast<const byte*>(s.data()), s.size_bytes()};
}

template <class ElementType, std::ptrdiff_t Extent,
          class = std::enable_if_t<!std::is_const<ElementType>::value>>
span<byte, details::calculate_byte_size<ElementType, Extent>::value>
as_writeable_bytes(span<ElementType, Extent> s) GSL_NOEXCEPT
{
    return {reinterpret_cast<byte*>(s.data()), s.size_bytes()};
}

//
// make_span() - Utility functions for creating spans
//
template <class ElementType>
constexpr span<ElementType> make_span(ElementType* ptr, typename span<ElementType>::index_type count)
{
    return span<ElementType>(ptr, count);
}

template <class ElementType>
constexpr span<ElementType> make_span(ElementType* firstElem, ElementType* lastElem)
{
    return span<ElementType>(firstElem, lastElem);
}

template <class ElementType, std::size_t N>
constexpr span<ElementType, N> make_span(ElementType (&arr)[N])
{
    return span<ElementType, N>(arr);
}

template <class Container>
constexpr span<typename Container::value_type> make_span(Container& cont)
{
    return span<typename Container::value_type>(cont);
}

template <class Container>
constexpr span<const typename Container::value_type> make_span(const Container& cont)
{
    return span<const typename Container::value_type>(cont);
}

template <class Ptr>
constexpr span<typename Ptr::element_type> make_span(Ptr& cont, std::ptrdiff_t count)
{
    return span<typename Ptr::element_type>(cont, count);
}

template <class Ptr>
constexpr span<typename Ptr::element_type> make_span(Ptr& cont)
{
    return span<typename Ptr::element_type>(cont);
}

// Specialization of gsl::at for span
template <class ElementType, std::ptrdiff_t Extent>
constexpr ElementType& at(span<ElementType, Extent> s, index i)
{
    // No bounds checking here because it is done in span::operator[] called below
    return s[i];
}

} // namespace gsl

#undef GSL_NOEXCEPT

#ifdef _MSC_VER
#if _MSC_VER < 1910
#undef constexpr
#pragma pop_macro("constexpr")

#endif // _MSC_VER < 1910

#pragma warning(pop)
#endif // _MSC_VER

#endif // GSL_SPAN_H

