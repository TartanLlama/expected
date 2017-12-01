# Header file `expected.hpp`<a id="expected.hpp"></a>

<pre><code class="language-cpp">#define <a href='doc_expected.html#expected.hpp'>TL_EXPECTED_HPP</a>

#define <a href='doc_expected.html#expected.hpp'>TL_EXPECTED_VERSION_MAJOR</a>

#define <a href='doc_expected.html#expected.hpp'>TL_EXPECTED_VERSION_MINOR</a>

#define <a href='doc_expected.html#expected.hpp'>TL_MONOSTATE_INPLACE_MUTEX</a>

#define <a href='doc_expected.html#expected.hpp'>TL_TRAITS_MUTEX</a>

#define <a href='doc_expected.html#expected.hpp'>TL_OPTIONAL_EXPECTED_MUTEX</a>

namespace <a href='doc_expected.html#expected.hpp'>tl</a>
{
    class <a href='doc_expected.html#tl::monostate'>monostate</a>;
    
    struct <a href='doc_expected.html#tl::in_place_t'>in_place_t</a>;
    
    constexpr <a href='doc_expected.html#tl::in_place_t'>in_place_t{}</a> <a href='doc_expected.html#tl::in_place'>in_place</a>;
    
    template &lt;class E&gt;
    class <a href='doc_expected.html#tl::unexpected-E-'>unexpected</a>;
    
    template &lt;class E&gt;
    constexpr bool <a href='doc_expected.html#tl::operator==(constunexpected-E-&,constunexpected-E-&)'>operator==</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);
    template &lt;class E&gt;
    constexpr bool <a href='doc_expected.html#tl::operator==(constunexpected-E-&,constunexpected-E-&)'>operator!=</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);
    template &lt;class E&gt;
    constexpr bool <a href='doc_expected.html#tl::operator==(constunexpected-E-&,constunexpected-E-&)'>operator&lt;</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);
    template &lt;class E&gt;
    constexpr bool <a href='doc_expected.html#tl::operator==(constunexpected-E-&,constunexpected-E-&)'>operator&lt;=</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);
    template &lt;class E&gt;
    constexpr bool <a href='doc_expected.html#tl::operator==(constunexpected-E-&,constunexpected-E-&)'>operator&gt;</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);
    template &lt;class E&gt;
    constexpr bool <a href='doc_expected.html#tl::operator==(constunexpected-E-&,constunexpected-E-&)'>operator&gt;=</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);
    
    template &lt;class E&gt;
    <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a> <a href='doc_expected.html#tl::make_unexpected(E&&)'>make_unexpected</a>(E&amp;&amp; e);
    
    struct <a href='doc_expected.html#tl::unexpect_t'>unexpect_t</a>;
    
    constexpr <a href='doc_expected.html#tl::unexpect_t'>unexpect_t{}</a> <a href='doc_expected.html#tl::unexpect'>unexpect</a>;
    
    template &lt;class E&gt;
    class <a href='doc_expected.html#expected.hpp'>bad_expected_access</a>;
    
    template &lt;class T, class E&gt;
    class <a href='doc_expected.html#tl::expected-T,E-'>expected</a>;
    
    template &lt;class T, class E, class U, class F&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator==</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;U, F&gt;</a>&amp; rhs);
    
    template &lt;class T, class E, class U, class F&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator!=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;U, F&gt;</a>&amp; rhs);
    
    template &lt;class T, class E, class U, class F&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;U, F&gt;</a>&amp; rhs);
    
    template &lt;class T, class E, class U, class F&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;U, F&gt;</a>&amp; rhs);
    
    template &lt;class T, class E, class U, class F&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;U, F&gt;</a>&amp; rhs);
    
    template &lt;class T, class E, class U, class F&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;U, F&gt;</a>&amp; rhs);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator==</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const U&amp; v);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator==</a>(const U&amp; v, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator!=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const U&amp; v);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator!=</a>(const U&amp; v, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const U&amp; v);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;</a>(const U&amp; v, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const U&amp; v);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;=</a>(const U&amp; v, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const U&amp; v);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;</a>(const U&amp; v, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const U&amp; v);
    
    template &lt;class T, class E, class U&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;=</a>(const U&amp; v, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator==</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator==</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator!=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator!=</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&lt;=</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e);
    
    template &lt;class T, class E&gt;
    constexpr bool <a href='doc_expected.html#expected.hpp'>operator&gt;=</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; e, const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; x);
    
    template &lt;class T, class E, 'hidden'&gt;
    void <a href='doc_expected.html#expected.hpp'>swap</a>(<a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; lhs, <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;T, E&gt;</a>&amp; rhs) noexcept(noexcept(lhs.swap(rhs)));
}</code></pre>

## Class `tl::monostate`<a id="tl::monostate"></a>

<pre><code class="language-cpp">class monostate
{
};</code></pre>

Used to represent an expected with no data

## Struct `tl::in_place_t`<a id="tl::in_place_t"></a>

<pre><code class="language-cpp">struct in_place_t
{
    <a href='doc_expected.html#tl::in_place_t'>in_place_t</a>() = default;
};</code></pre>

A tag type to tell expected to construct its value in-place

## Variable `tl::in_place`<a id="tl::in_place"></a>

<pre><code class="language-cpp">constexpr <a href='doc_expected.html#tl::in_place_t'>in_place_t{}</a> in_place;</code></pre>

A tag to tell expected to construct its value in-place

## Class template `tl::unexpected`<a id="tl::unexpected-E-"></a>

<pre><code class="language-cpp">template &lt;class E&gt;
class unexpected
{
public:
    <a href='doc_expected.html#tl::unexpected-E-'>unexpected</a>() = delete;
    
    constexpr <a href='doc_expected.html#tl::unexpected-E-'>unexpected</a>(const E&amp; e);
    
    constexpr <a href='doc_expected.html#tl::unexpected-E-'>unexpected</a>(E&amp;&amp; e);
    
    constexpr const E&amp; <a href='doc_expected.html#tl::unexpected-E-::value()const&'>value</a>() const &amp;;
    E&amp; <a href='doc_expected.html#tl::unexpected-E-::value()const&'>value</a>() &amp;;
    E&amp;&amp; <a href='doc_expected.html#tl::unexpected-E-::value()const&'>value</a>() &amp;&amp;;
};</code></pre>

Used as a wrapper to store the unexpected value

### Function `tl::unexpected::value`<a id="tl::unexpected-E-::value()const&"></a>

<pre><code class="language-cpp">(1)  constexpr const E&amp; value() const &amp;;

(2)  E&amp; value() &amp;;

(3)  E&amp;&amp; value() &amp;&amp;;</code></pre>

*Returns*: the contained value

-----

## Comparison operator `tl::operator==`<a id="tl::operator==(constunexpected-E-&,constunexpected-E-&)"></a>

<pre><code class="language-cpp">(1)  template &lt;class E&gt;
     constexpr bool operator==(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);

(2)  template &lt;class E&gt;
     constexpr bool operator!=(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);

(3)  template &lt;class E&gt;
     constexpr bool operator&lt;(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);

(4)  template &lt;class E&gt;
     constexpr bool operator&lt;=(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);

(5)  template &lt;class E&gt;
     constexpr bool operator&gt;(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);

(6)  template &lt;class E&gt;
     constexpr bool operator&gt;=(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; lhs, const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>&amp; rhs);</code></pre>

Compares two unexpected objects

Simply compares lhs.value() to rhs.value()

## Function template `tl::make_unexpected`<a id="tl::make_unexpected(E&&)"></a>

<pre><code class="language-cpp">template &lt;class E&gt;
<a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a> make_unexpected(E&amp;&amp; e);</code></pre>

Create an `unexpected` from `e`, deducing the return type

*Example:* auto e1 = tl::make\_unexpected(42); unexpected\<int\> e2 (42); //same semantics

## Struct `tl::unexpect_t`<a id="tl::unexpect_t"></a>

<pre><code class="language-cpp">struct unexpect_t
{
    <a href='doc_expected.html#tl::unexpect_t'>unexpect_t</a>() = default;
};</code></pre>

A tag type to tell expected to construct the unexpected value

## Variable `tl::unexpect`<a id="tl::unexpect"></a>

<pre><code class="language-cpp">constexpr <a href='doc_expected.html#tl::unexpect_t'>unexpect_t{}</a> unexpect;</code></pre>

A tag to tell expected to construct the unexpected value

## Class template `tl::expected`<a id="tl::expected-T,E-"></a>

<pre><code class="language-cpp">template &lt;class T, class E&gt;
class expected
{
public:
    using <a href='doc_expected.html#tl::expected-T,E-'>value_type</a> = T;
    
    using <a href='doc_expected.html#tl::expected-T,E-'>error_type</a> = E;
    
    using <a href='doc_expected.html#tl::expected-T,E-'>unexpected_type</a> = <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;E&gt;</a>;
    
    template &lt;class F&gt;
    constexpr auto and_then(F &amp;&amp;f) &amp;;
    template &lt;class F&gt;
    constexpr auto and_then(F &amp;&amp;f) &amp;&amp;;
    template &lt;class F&gt;
    constexpr auto and_then(F &amp;&amp;f) const &amp;;
    template &lt;class F&gt;
    constexpr auto and_then(F &amp;&amp;f) const &amp;&amp;;
    
    template &lt;class F&gt; constexpr auto map(F &amp;&amp;f) &amp;;
    template &lt;class F&gt; constexpr auto map(F &amp;&amp;f) &amp;&amp;;
    template &lt;class F&gt; constexpr auto map(F &amp;&amp;f) const &amp;;
    template &lt;class F&gt; constexpr auto map(F &amp;&amp;f) const &amp;&amp;;
    
    template &lt;class F&gt; constexpr auto map_error(F &amp;&amp;f) &amp;;
    template &lt;class F&gt; constexpr auto map_error(F &amp;&amp;f) &amp;&amp;;
    template &lt;class F&gt; constexpr auto map_error(F &amp;&amp;f) const &amp;;
    template &lt;class F&gt; constexpr auto map_error(F &amp;&amp;f) const &amp;&amp;;
    
    template &lt;class F&gt;
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a> <a href='doc_expected.html#tl::expected-T,E-::or_else(F&&)&'>or_else</a>(F&amp;&amp; f) &amp;;
    
    template &lt;class F&gt;
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a> <a href='doc_expected.html#tl::expected-T,E-'>or_else</a>(F&amp;&amp; f) &amp;&amp;;
    
    template &lt;class F&gt;
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a> <a href='doc_expected.html#tl::expected-T,E-'>or_else</a>(F&amp;&amp; f) const &amp;;
    
    template &lt;class F&gt;
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a> <a href='doc_expected.html#tl::expected-T,E-'>or_else</a>(F&amp;&amp; f) const &amp;&amp;;
    
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a>() = default;
    
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp; rhs) = default;
    
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a>(<a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp;&amp; rhs) = default;
    
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp; <a href='doc_expected.html#tl::expected-T,E-'>operator=</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp; rhs) = default;
    
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp; <a href='doc_expected.html#tl::expected-T,E-'>operator=</a>(<a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp;&amp; rhs) = default;
    
    template &lt;class ... Args, 'hidden' ... = nullptr&gt;
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a>(<a href='doc_expected.html#tl::in_place_t'>in_place_t</a>, Args&amp;&amp;... args);
    
    template &lt;class U, class ... Args, 'hidden' ... = nullptr&gt;
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a>(<a href='doc_expected.html#tl::in_place_t'>in_place_t</a>, <a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::initializer_list%3cU%3e'>std::initializer_list&lt;U&gt;</a> il, Args&amp;&amp;... args);
    
    EXPLICIT constexpr expected(const unexpected&lt;G&gt; &amp;e);
    EXPLICIT constexpr expected(unexpected&lt;G&gt; &amp;&amp;e);
    
    template &lt;class ... Args, 'hidden' ... = nullptr&gt;
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a>(<a href='doc_expected.html#tl::unexpect_t'>unexpect_t</a>, Args&amp;&amp;... args);
    
    template &lt;class U, class G, 'hidden', 'hidden'&gt;
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a>(const <a href='doc_expected.html#tl::expected-T,E-'>expected&lt;U, G&gt;</a>&amp; rhs);
    
    template &lt;class U, class G, 'hidden', 'hidden'&gt;
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a>(<a href='doc_expected.html#tl::expected-T,E-'>expected&lt;U, G&gt;</a>&amp;&amp; rhs);
    
    template &lt;class U = T, 'hidden', 'hidden'&gt;
    constexpr <a href='doc_expected.html#tl::expected-T,E-'>expected</a>(U&amp;&amp; v);
    
    template &lt;class U = T, 'hidden', 'hidden'&gt;
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp; <a href='doc_expected.html#tl::expected-T,E-'>operator=</a>(U&amp;&amp; v);
    
    template &lt;class G = E, 'hidden'&gt;
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp; <a href='doc_expected.html#tl::expected-T,E-'>operator=</a>(const <a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;G&gt;</a>&amp; rhs);
    
    template &lt;class G = E, 'hidden'&gt;
    <a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp; <a href='doc_expected.html#tl::expected-T,E-'>operator=</a>(<a href='doc_expected.html#tl::unexpected-E-'>unexpected&lt;G&gt;</a>&amp;&amp; rhs) noexcept;
    
    template &lt;class ... Args, 'hidden' ... = nullptr&gt;
    void <a href='doc_expected.html#tl::expected-T,E-'>emplace</a>(Args&amp;&amp;... args);
    
    template &lt;class U, class ... Args, 'hidden' ... = nullptr&gt;
    void <a href='doc_expected.html#tl::expected-T,E-'>emplace</a>(<a href='http://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=std::initializer_list%3cU%3e'>std::initializer_list&lt;U&gt;</a> il, Args&amp;&amp;... args);
    
    void <a href='doc_expected.html#tl::expected-T,E-'>swap</a>(<a href='doc_expected.html#tl::expected-T,E-'>expected</a>&amp; rhs) noexcept(std::is_nothrow_move_constructible&lt;T&gt;::value&amp;&amp;noexcept(swap(std::declval&lt;T&amp;&gt;(), std::declval&lt;T&amp;&gt;()))&amp;&amp;std::is_nothrow_move_constructible&lt;E&gt;::value&amp;&amp;noexcept(swap(std::declval&lt;E&amp;&gt;(), std::declval&lt;E&amp;&gt;())));
    
    constexpr const T* <a href='doc_expected.html#tl::expected-T,E-::operator--()const'>operator-&gt;</a>() const;
    T* <a href='doc_expected.html#tl::expected-T,E-::operator--()const'>operator-&gt;</a>();
    
    constexpr const T&amp; <a href='doc_expected.html#tl::expected-T,E-::operator*()const&'>operator*</a>() const &amp;;
    T&amp; <a href='doc_expected.html#tl::expected-T,E-::operator*()const&'>operator*</a>() &amp;;
    constexpr const T&amp;&amp; <a href='doc_expected.html#tl::expected-T,E-::operator*()const&'>operator*</a>() const &amp;&amp;;
    T&amp;&amp; <a href='doc_expected.html#tl::expected-T,E-::operator*()const&'>operator*</a>() &amp;&amp;;
    
    constexpr bool <a href='doc_expected.html#tl::expected-T,E-::has_value()const'>has_value</a>() const noexcept;
    constexpr <a href='doc_expected.html#tl::expected-T,E-::has_value()const'>operator bool</a>() const noexcept;
    
    constexpr const T&amp; <a href='doc_expected.html#tl::expected-T,E-::value()const&'>value</a>() const &amp;;
    T&amp; <a href='doc_expected.html#tl::expected-T,E-::value()const&'>value</a>() &amp;;
    constexpr const T&amp;&amp; <a href='doc_expected.html#tl::expected-T,E-::value()const&'>value</a>() const &amp;&amp;;
    T&amp;&amp; <a href='doc_expected.html#tl::expected-T,E-::value()const&'>value</a>() &amp;&amp;;
    
    constexpr const E&amp; <a href='doc_expected.html#tl::expected-T,E-::error()const&'>error</a>() const &amp;;
    E&amp; <a href='doc_expected.html#tl::expected-T,E-::error()const&'>error</a>() &amp;;
    constexpr const E&amp;&amp; <a href='doc_expected.html#tl::expected-T,E-::error()const&'>error</a>() const &amp;&amp;;
    E&amp;&amp; <a href='doc_expected.html#tl::expected-T,E-::error()const&'>error</a>() &amp;&amp;;
    
    template &lt;class U&gt;
    constexpr T <a href='doc_expected.html#tl::expected-T,E-::value_or(U&&)const&'>value_or</a>(U&amp;&amp; v) const &amp;;
    template &lt;class U&gt;
    T <a href='doc_expected.html#tl::expected-T,E-::value_or(U&&)const&'>value_or</a>(U&amp;&amp; v) &amp;&amp;;
};</code></pre>

An `expected<T, E>` object is an object that contains the storage for another object and manages the lifetime of this contained object `T`. Alternatively it could contain the storage for another unexpected object `E`. The contained object may not be initialized after the expected object has been initialized, and may not be destroyed before the expected object has been destroyed. The initialization state of the contained object is tracked by the expected object.

### Function template `tl::expected::and_then`<a id="tl::expected-T,E-::and_then(F&&)&"></a>

<pre><code class="language-cpp">(1)  template &lt;class F&gt;
     constexpr auto and_then(F &amp;&amp;f) &amp;;

(2)  template &lt;class F&gt;
     constexpr auto and_then(F &amp;&amp;f) &amp;&amp;;

(3)  template &lt;class F&gt;
     constexpr auto and_then(F &amp;&amp;f) const &amp;;

(4)  template &lt;class F&gt;
     constexpr auto and_then(F &amp;&amp;f) const &amp;&amp;;</code></pre>

Carries out some operation which returns an expected on the stored object if there is one. \\requires `std::invoke(std::forward<F>(f), value())` returns a `std::expected<U>` for some `U`. \\returns Let `U` be the result of `std::invoke(std::forward<F>(f), value())`. Returns a `std::expected<U>`. The return value is empty if `*this` is empty, otherwise the return value of `std::invoke(std::forward<F>(f), value())` is returned.

### Function template `tl::expected::map`<a id="tl::expected-T,E-::map(F&&)&"></a>

<pre><code class="language-cpp">(1)  template &lt;class F&gt; constexpr auto map(F &amp;&amp;f) &amp;;

(2)  template &lt;class F&gt; constexpr auto map(F &amp;&amp;f) &amp;&amp;;

(3)  template &lt;class F&gt; constexpr auto map(F &amp;&amp;f) const &amp;;

(4)  template &lt;class F&gt; constexpr auto map(F &amp;&amp;f) const &amp;&amp;;</code></pre>

Carries out some operation on the stored object if there is one.

*Returns*: Let `U` be the result of `std::invoke(std::forward<F>(f), value())`. Returns a `std::expected<U,E>`. If `*this` is unexpected, the result is `*this`, otherwise an `expected<U,E>` is constructed from the return value of `std::invoke(std::forward<F>(f), value())` and is returned.

### Function template `tl::expected::map_error`<a id="tl::expected-T,E-::map_error(F&&)&"></a>

<pre><code class="language-cpp">(1)  template &lt;class F&gt; constexpr auto map_error(F &amp;&amp;f) &amp;;

(2)  template &lt;class F&gt; constexpr auto map_error(F &amp;&amp;f) &amp;&amp;;

(3)  template &lt;class F&gt; constexpr auto map_error(F &amp;&amp;f) const &amp;;

(4)  template &lt;class F&gt; constexpr auto map_error(F &amp;&amp;f) const &amp;&amp;;</code></pre>

Carries out some operation on the stored unexpected object if there is one.

*Returns*: Let `U` be the result of `std::invoke(std::forward<F>(f), value())`. Returns a `std::expected<T,U>`. If `*this` has an expected value, the result is `*this`, otherwise an `expected<T,U>` is constructed from `make_unexpected(std::invoke(std::forward<F>(f), value()))` and is returned.

### Function template `tl::expected::or_else`<a id="tl::expected-T,E-::or_else(F&&)&"></a>

<pre><code class="language-cpp">(1)  template &lt;class F&gt;
     <a href='doc_expected.html#tl::expected-T,E-'>expected</a> or_else(F&amp;&amp; f) &amp;;</code></pre>

Calls `f` if the expectd is in the unexpected state

*Requires*: `std::invoke_result_t<F>` must be void or convertible to `expcted<T,E>`.

*Effects*: If `*this` has a value, returns `*this`. Otherwise, if `f` returns `void`, calls `std::forward<F>(f)` and returns `std::nullopt`. Otherwise, returns `std::forward<F>(f)()`.

### Function template `tl::expected::expected`<a id="tl::expected-T,E-::expected(constunexpected-G-&)"></a>

<pre><code class="language-cpp">(1)  EXPLICIT constexpr expected(const unexpected&lt;G&gt; &amp;e);

(2)  EXPLICIT constexpr expected(unexpected&lt;G&gt; &amp;&amp;e);</code></pre>

### Operator `tl::expected::operator->`<a id="tl::expected-T,E-::operator--()const"></a>

<pre><code class="language-cpp">(1)  constexpr const T* operator-&gt;() const;

(2)  T* operator-&gt;();</code></pre>

*Returns*: a pointer to the stored value

*Requires*: a value is stored

### Operator `tl::expected::operator*`<a id="tl::expected-T,E-::operator*()const&"></a>

<pre><code class="language-cpp">(1)  constexpr const T&amp; operator*() const &amp;;

(2)  T&amp; operator*() &amp;;

(3)  constexpr const T&amp;&amp; operator*() const &amp;&amp;;

(4)  T&amp;&amp; operator*() &amp;&amp;;</code></pre>

*Returns*: the stored value

*Requires*: a value is stored

### Function `tl::expected::has_value`<a id="tl::expected-T,E-::has_value()const"></a>

<pre><code class="language-cpp">(1)  constexpr bool has_value() const noexcept;

(2)  constexpr operator bool() const noexcept;</code></pre>

*Returns*: whether or not the optional has a value

### Function `tl::expected::value`<a id="tl::expected-T,E-::value()const&"></a>

<pre><code class="language-cpp">(1)  constexpr const T&amp; value() const &amp;;

(2)  T&amp; value() &amp;;

(3)  constexpr const T&amp;&amp; value() const &amp;&amp;;

(4)  T&amp;&amp; value() &amp;&amp;;</code></pre>

*Returns*: the contained value if there is one, otherwise throws \[bad\_expected\_access\]

### Function `tl::expected::error`<a id="tl::expected-T,E-::error()const&"></a>

<pre><code class="language-cpp">(1)  constexpr const E&amp; error() const &amp;;

(2)  E&amp; error() &amp;;

(3)  constexpr const E&amp;&amp; error() const &amp;&amp;;

(4)  E&amp;&amp; error() &amp;&amp;;</code></pre>

*Returns*: the unexpected value

*Requires*: there is an unexpected value

### Function template `tl::expected::value_or`<a id="tl::expected-T,E-::value_or(U&&)const&"></a>

<pre><code class="language-cpp">(1)  template &lt;class U&gt;
     constexpr T value_or(U&amp;&amp; v) const &amp;;

(2)  template &lt;class U&gt;
     T value_or(U&amp;&amp; v) &amp;&amp;;</code></pre>

*Returns*: the stored value if there is one, otherwise returns `u`

-----

-----
